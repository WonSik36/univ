#include "cv.hpp"
#include <iostream>
#include <opencv2/dnn.hpp>
#include <fstream>
using namespace cv;
using namespace std;
using namespace dnn;

int drawLine(vector<Vec2f> lines, float x, float y, float angle_th1, float angle_th2, Scalar color, Mat& result);

#define MOD 24
#define CAR_WARN_SIZE 12000
#define PERSON_WARN_SIZE 5000
#define MAIN

#ifdef MAIN
int main(int argc, char** argv){
	/* open video file */
	VideoCapture cap("Data/Stop_1.mp4");
	if (!cap.isOpened()) {
		cout << "can't open video file" << endl;
		return -1;
	}

	/* variable for playing video */
	Mat frame, hsv, front_mask, masked_frame;
	double fps = cap.get(CAP_PROP_FPS);
	int cnt = 0;

	/* variable for yolo */
	String modelConfiguration = "deep/yolov2.cfg";
	String modelBinary = "deep/yolov2.weights";
	vector<String> classNamesVec;
	Net net = readNetFromDarknet(modelConfiguration, modelBinary);
	ifstream classNamesFile("deep/coco.names");

	/* variable for tracking */
	Mat m_backproj;
	vector<Mat> m_model3d;
	vector<pair<int,Rect>> m_rc;
	const float hrange[] = { 0,180 };
	const float vrange[] = { 0,255 };
	const float srange[] = { 0,255 };
	const float* ranges[] = { hrange, srange, vrange }; // hue, saturation, brightness
	const int channels[] = { 0, 1, 2 };
	const int hist_sizes[] = { 16, 16, 16 };

	/* variable for line detection */
	float rho, theta, a, b, x0, y0;
	const float x_l = 100, x_r = 400, x_w = 280, y = 320;
	Mat roi_left_line, roi_right_line, roi_warn_line;
	Mat edge_left, edge_right, edge_warn;
	Point p1, p2;
	Rect rect_left(x_l, y, 250, 120);
	Rect rect_right(x_r, y, 250, 120);
	Rect rect_warn(x_w, y, 180, 80);
	vector<Vec2f> lines_left, lines_right, lines_warn;

	/* variable for warning */
	int FRONT_CAR_DEPARTURE = 0;
	int LANE_DEPARTURE = 0;
	int COLLISION_CAR = 0;
	int COLLISION_PEDESTRIAN = 0;
	int prev_car_size = 0;

	/* variable for record */
	/*VideoWriter writer;
	Size vSize = Size(cap.get(CAP_PROP_FRAME_WIDTH), cap.get(CAP_PROP_FRAME_HEIGHT));
	writer.open("output.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, vSize, true);*/

	/* initialization */
	{
		// make mask for front
		front_mask = Mat::zeros(Size(cap.get(CAP_PROP_FRAME_WIDTH), cap.get(CAP_PROP_FRAME_HEIGHT)), CV_8UC1);
		Point area[1][8];
		area[0][0] = Point(0, cap.get(CAP_PROP_FRAME_HEIGHT) / 6);
		area[0][1] = Point(cap.get(CAP_PROP_FRAME_WIDTH)-1, cap.get(CAP_PROP_FRAME_HEIGHT) / 6);
		area[0][2] = Point(cap.get(CAP_PROP_FRAME_WIDTH) - 1, cap.get(CAP_PROP_FRAME_HEIGHT) / 2);
		area[0][3] = Point(cap.get(CAP_PROP_FRAME_WIDTH)*3/5, cap.get(CAP_PROP_FRAME_HEIGHT) / 2);
		area[0][4] = Point(cap.get(CAP_PROP_FRAME_WIDTH) * 3 / 4, cap.get(CAP_PROP_FRAME_HEIGHT)-1);
		area[0][5] = Point(cap.get(CAP_PROP_FRAME_WIDTH) * 1 / 4, cap.get(CAP_PROP_FRAME_HEIGHT) - 1);
		area[0][6] = Point(cap.get(CAP_PROP_FRAME_WIDTH)*2/5, cap.get(CAP_PROP_FRAME_HEIGHT) / 2);
		area[0][7] = Point(0, cap.get(CAP_PROP_FRAME_HEIGHT) / 2);
			
		const Point* ppt[1] = { area[0] };
		int npt[] = { 8 };
		fillPoly(front_mask, ppt, npt, 1, Scalar(255), 8);

		// yolo
		if (classNamesFile.is_open()) {
			string className = "";
			while (std::getline(classNamesFile, className)) classNamesVec.push_back(className);
		}
	
		/* debugging */

		cout << "frame fps: " << cap.get(CAP_PROP_FPS) << endl;
		cout << "frame width: " << cap.get(CAP_PROP_FRAME_WIDTH) << endl;
		cout << "frame height: " << cap.get(CAP_PROP_FRAME_HEIGHT) << endl;
	}



	while (true) {
		/* get frame and convert color */
		cap >> frame;
		if (frame.empty()) break;
		frame.copyTo(masked_frame, front_mask);
		if (masked_frame.channels() == 4) cvtColor(frame, frame, COLOR_BGRA2BGR);
		cvtColor(frame, hsv, CV_BGR2HSV);

		/* ROI selection */
		/*roi_left_line = frame(rect_left);
		roi_right_line = frame(rect_right);*/
		roi_warn_line = frame(rect_warn);

		/* line detection */
		/*Canny(roi_left_line, edge_left, 50, 150, 3);
		Canny(roi_right_line, edge_right, 50, 150, 3);*/
		Canny(roi_warn_line, edge_warn, 50, 150, 3);
		/*HoughLines(edge_left, lines_left, 1, CV_PI / 180, 50);
		HoughLines(edge_right, lines_right, 1, CV_PI / 180, 50);*/
		HoughLines(edge_warn, lines_warn, 1, CV_PI / 180, 30);
		/*drawLine(lines_left, x_l, y, 50, 60, Scalar(0,255,0), frame);
		drawLine(lines_right, x_r, y, 135, 145, Scalar(0, 255, 0), frame);*/
		LANE_DEPARTURE = max(LANE_DEPARTURE, drawLine(lines_warn, x_w, y, 40, 50, Scalar(0, 0, 255), frame));
		LANE_DEPARTURE = max(LANE_DEPARTURE, drawLine(lines_warn, x_w, y, 140, 180, Scalar(0, 0, 255), frame));
		

		/* object detection */
		if (cnt % MOD == 0) {
			/* clear tracking queue */
			m_model3d.clear();
			m_rc.clear();

			/* object detection with yolo */
			Mat inputBlob = blobFromImage(masked_frame, 1 / 255.F, Size(416, 416), Scalar(), true, false);
			net.setInput(inputBlob, "data");                   //setthenetworkinput
			Mat detectionMat = net.forward("detection_out");   //computeoutput
			float confidenceThreshold = 0.24; //by default

			for (int i = 0; i < detectionMat.rows; i++) {
				const int probability_index = 5;
				const int probability_size = detectionMat.cols - probability_index;
				float* prob_array_ptr = &detectionMat.at<float>(i, probability_index);
				size_t objectClass = max_element(prob_array_ptr, prob_array_ptr + probability_size) - prob_array_ptr;
				//특정한물체가detection된확률
				float confidence = detectionMat.at<float>(i, (int)objectClass + probability_index);

				// if object is not person(0) and car(2) than continue
				if (objectClass != 0 && objectClass != 2)
					continue;

				//For drawing
				if (confidence > confidenceThreshold) {
					// drawing
					float x_center = detectionMat.at<float>(i, 0) * frame.cols;
					float y_center = detectionMat.at<float>(i, 1) * frame.rows;
					float width = detectionMat.at<float>(i, 2) * frame.cols;
					float height = detectionMat.at<float>(i, 3) * frame.rows;
					Point p1(cvRound(x_center - width / 2), cvRound(y_center - height / 2));
					Point p2(cvRound(x_center + width / 2), cvRound(y_center + height / 2));
					Rect object(p1, p2);
					rectangle(frame, object, Scalar(0, 0, 255), 2);

					if (object.x < 0 || object.x + object.width >= frame.cols)
						continue;

					if (object.y< 0 || object.y + object.height >= frame.rows)
						continue;

					// tracking
					Mat m_model3d_tmp;
					Mat mask = Mat::zeros(object.height,object.width, CV_8U);
					ellipse(mask, Point(width / 2, height / 2), Size(width / 2, height / 2), 0, 0, 360, 255, CV_FILLED);
					Mat roi(hsv, object);
					calcHist(&roi, 1, channels, mask, m_model3d_tmp, 3, hist_sizes, ranges);
					m_rc.push_back(make_pair(objectClass, object));
					m_model3d.push_back(m_model3d_tmp);

					// for person
					if (objectClass == 0) {
						cout << "person size: " << width * height << endl;
						if (width * height > PERSON_WARN_SIZE)
							COLLISION_PEDESTRIAN = (int)ceil(fps);
					}
					
					// for car
					if (objectClass == 2) {
						cout << "previous car size: " << prev_car_size << endl;
						cout << "current car size: " << width * height << endl;
						cout << "gap between car size: " << (width* height - prev_car_size) << endl;
						
						if (width * height > CAR_WARN_SIZE && (width * height - prev_car_size) > 2000)
							COLLISION_CAR = (int)ceil(fps);

						if (prev_car_size > CAR_WARN_SIZE && (prev_car_size - width * height) > 2000)
							FRONT_CAR_DEPARTURE = (int)ceil(fps);

						prev_car_size = width * height;
					}
				}
			}
		} else {
			/* object detection with tracking */
			for (int i = 0; i < m_rc.size(); i++) {
				calcBackProject(&hsv, 1, channels, m_model3d[i], m_backproj, ranges);
				meanShift(m_backproj, m_rc[i].second, TermCriteria(TermCriteria::EPS | TermCriteria::COUNT, 10, 1));
				rectangle(frame, m_rc[i].second, Scalar(0, 255, 0), 2, 4, 0);
				int objectClass = m_rc[i].first;
			}
		}
		

		/* handling warning sign */ 
		{
			if (FRONT_CAR_DEPARTURE > 0) {
				putText(frame, "Warning: Front car departure", Point(10, 25), FONT_HERSHEY_COMPLEX, 0.8, Scalar(0, 255, 0), 2, CV_AA);
				FRONT_CAR_DEPARTURE--;
			}
			if (LANE_DEPARTURE > 0) {
				putText(frame, "Warning: Lane departure", Point(10, 50), FONT_HERSHEY_COMPLEX, 0.8, Scalar(0, 255, 255), 2, CV_AA);
				LANE_DEPARTURE--;
			}
			if (COLLISION_CAR > 0) {
				putText(frame, "Warning: Collision with front car", Point(10, 75), FONT_HERSHEY_COMPLEX, 0.8, Scalar(0, 0, 255), 2, CV_AA);
				COLLISION_CAR--;
			}
			if (COLLISION_PEDESTRIAN > 0) {
				putText(frame, "Warning: Collision with pedestrian", Point(10, 100), FONT_HERSHEY_COMPLEX, 0.8, Scalar(0, 0, 255), 2, CV_AA);
				COLLISION_PEDESTRIAN--;
			}
		}

		/* imshow */
		imshow("Output", frame);


		/*imshow("left", edge_left);
		imshow("right", edge_right);
		imshow("warn", edge_warn);*/


		/* waitKey and update variable for loop */
		char ch = waitKey(1000 / fps);
		if (ch == 27) break; // ESC Key (exit)
		else if (ch == 32) { // SPACE Key (pause)
			while ((ch = waitKey(10)) != 32 && ch != 27);
			if (ch == 27) break;
		}

		cnt++;
		//writer.write(frame);
	}

	return 0;
}
#endif

int drawLine(vector<Vec2f> lines, float x, float y, float angle_th1, float angle_th2, Scalar color, Mat& result) {	
	float rho, theta, a, b, x0, y0;
	float avr_rho = 0., avr_theta = 0.;
	int count = 0;
	Point p1, p2;

	for (int i = 0; i < lines.size(); i++) {
		rho = lines[i][0];
		theta = lines[i][1];

		// filter angle of line
		if (theta < CV_PI / 180 * angle_th1 || theta > CV_PI / 180 * angle_th2) continue;

		avr_rho += rho;
		avr_theta += theta;
		count++;
	}

	if (avr_rho == 0 && avr_theta == 0)
		return 0;

	avr_rho /= count;
	avr_theta /= count;
	a = cos(avr_theta);
	b = sin(avr_theta);

	x0 = a * avr_rho;
	y0 = b * avr_rho;

	// draw line
	p1 = Point(cvRound(x0 + 1000 * (-b)) + x, cvRound(y0 + 1000 * a) + y);
	p2 = Point(cvRound(x0 - 1000 * (-b)) + x, cvRound(y0 - 1000 * a) + y);

	line(result, p1, p2, color, 2, CV_AA);

	return 10;
}