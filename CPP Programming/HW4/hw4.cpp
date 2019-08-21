#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib> // system("pause")
#include <ctime> // time()
#include <cctype> // toupper
#include <algorithm> // transform()
using namespace std; // Or use std::cout

// default congifure file name & default book information file
#define CONFIG_FILE "config.txt"
#define DEFAULT_SAVE_FILE "def_lib_file.txt"
#define NUMBER_BOOKS 50

typedef struct _book{
	string title;
	string author;
	string pYear;
	string edition;
	string borrower;
	int borrowed_days;
}Book;
int num_Book;

// main command function
void loadFile(Book* bList);
void saveFile(Book* bList);
void printList(Book* bList, int num);
void insertBook(Book* bList);
void lendBook(Book* bList);
int searchBook(Book* bList, string title);
void passDay(Book* bList);
void returnedBook(Book* bList);
void alarmReBook(Book* bList, int num);
void printCommand();

// helper function
string* strSplit(string subject, string split);
string strStrip(string subject);
int getLineNum(string fName);
int getCommand();
void workCmd(Book* bList, int cmd);

int main(void){
	Book bList[NUMBER_BOOKS];

	loadFile(bList);
	printList(bList, num_Book);
	
	int cmd;
	do{
		printCommand();
		cmd = getCommand();
		workCmd(bList, cmd);
	// loop until user command exit(=7)
	}while(cmd != 7);
	
	system("pause");
	return 0;
}

//load data from file to Book structure
void loadFile(Book* bList){
	ifstream inData;
	inData.open(CONFIG_FILE); // open config file
	time_t result = time(nullptr); // variable that have time infromation
	string cTime = asctime(localtime(&result)); // string of time
	string sFile = DEFAULT_SAVE_FILE; // name of book information file

	//if config file does not exist, than make config file
	if(!inData){
		inData.close();

		ofstream outData;
		outData.open(CONFIG_FILE);
		outData << cTime;
		outData << sFile;
		outData.close();
		num_Book = 0;
	}else{
		//read modification date and name of book information file from config file
		getline(inData, cTime);
		getline(inData, sFile);
		inData.close();

		// read book information from book information file
		num_Book = getLineNum(sFile);
		string line; // string that read line from file
		string* strArr; // string array that have splited string
		ifstream inData;
		inData.open(sFile);
		//Split string into array and insert its value to structure array
		for(int i=0; i<num_Book; i++){
			getline(inData, line);
			strArr = strSplit(line, ";");

			bList[i].title = strStrip(strArr[0]);
			bList[i].author = strStrip(strArr[1]);
			bList[i].pYear = strStrip(strArr[2]);
			bList[i].edition = strStrip(strArr[3]);
			bList[i].borrower = strStrip(strArr[4]);
			bList[i].borrowed_days = stoi(strStrip(strArr[5]));
			delete[] strArr;
		}
		inData.close();
	}
}

// save book list to file which was designated by user
void saveFile(Book* bList){
	string book;
	string fName;
	ofstream outData;
	time_t result = time(nullptr); // variable that have time infromation
	string cTime = asctime(localtime(&result)); // string of time

	cin >> fName;
	int i = fName.find(".txt");
	if(i != (fName.length() - 4))
		fName = fName + ".txt";

	outData.open(fName);
	for(i=0; i<num_Book; i++){
		book = bList[i].title +"; "+bList[i].author+"; "+bList[i].pYear+"; "+bList[i].edition+"; "+bList[i].borrower+"; "+to_string(bList[i].borrowed_days);
		outData<<book<<endl;
	}
	cout<<"Save book list to "<<fName<<" successfully"<<endl;
	cout<<endl;
	outData.close();

	outData.open(CONFIG_FILE);
	outData<<cTime;
	outData<<fName;
	outData.close();
}

// print book List
void printList(Book* bList, int num){
	for(int i=0; i<40; i++)
		cout<<"=";

	cout<<" Book Catalog ";

	for(int i=0; i<40; i++)
		cout<<"=";

	cout<<endl;

	cout<<" ";
	cout<<left<<setw(23)<<"Title";
	cout<<left<<setw(18)<<"Author";
	cout<<left<<setw(17)<<"Published Year";
	cout<<left<<setw(9)<<"Edition";
	cout<<left<<setw(12)<<"Borrower";
	cout<<left<<setw(13)<<"Days Borrowed"<<endl;

	for(int i=0; i<num; i++){
		cout<<" ";
		cout<<left<<setw(23)<<bList[i].title;
		cout<<left<<setw(18)<<bList[i].author;
		cout<<left<<setw(17)<<bList[i].pYear;
		cout<<left<<setw(9)<<bList[i].edition;
		cout<<left<<setw(12)<<bList[i].borrower;
		cout<<left<<setw(13)<<bList[i].borrowed_days<<endl;		
	}

	for(int i=0; i<44; i++)
		cout<<"=";

	cout<<" END ";

	for(int i=0; i<45; i++)
		cout<<"=";

	cout<<endl;
	alarmReBook(bList, num);
	cout<<endl;
}

// insert book to book list
// initiate borrower and borrowed days are None and 0
void insertBook(Book* bList){
	string cmd;
	getline(cin, cmd);

	string* strArr = strSplit(cmd, ";");

	bList[num_Book].title = strStrip(strArr[0]);
	bList[num_Book].author = strStrip(strArr[1]);
	bList[num_Book].pYear = strStrip(strArr[2]);
	bList[num_Book].edition = strStrip(strArr[3]);
	bList[num_Book].borrower = "None";
	bList[num_Book].borrowed_days = 0;

	cout<<endl;
	cout<<"Inserted "<<bList[num_Book].title<<" successfully!"<<endl;
	cout<<endl;

	num_Book++;
	delete[] strArr;
}

// get LEND command format and update book information
void lendBook(Book* bList){
	string cmd;
	getline(cin, cmd);

	string* strArr = strSplit(cmd, ";");
	string title = strStrip(strArr[0]);
	string person = strStrip(strArr[1]);
	int days = stoi(strStrip(strArr[2]));
	delete[] strArr;

	if(days <= 0){
		cout<<"  Lend for more days"<<endl;
	}

	int index = searchBook(bList, title);
	if(index == -1){
		cout<<"  NO SUCH BOOK!"<<endl;
	}else{
		if(bList[index].borrower.compare("None") == 0){
			bList[index].borrower = person;
			bList[index].borrowed_days = days;
			Book book = bList[index];
			printList(&book, 1);
		}
		else{
			cout<<"  Someone borrowed already"<<endl;
		}
	}
	cout<<endl;
}

// search book list by given title string
// if find title return index of book list, else return -1
int searchBook(Book* bList, string title){
	for(int i=0; i<num_Book; i++){
		if(title.compare(bList[i].title) == 0){
			return i;
		}
	}
	return -1;
}

// if some book has been borrowed, passday function makes borrowed days be subtracted 1 
void passDay(Book* bList){
	Book lentBooks[num_Book];
	int lent_num = 0;
	string none = "None";

	for(int i=0; i<num_Book; i++){
		if(none.compare(bList[i].borrower) != 0){
			bList[i].borrowed_days--;
			lentBooks[lent_num++] = bList[i];
		}
	}

	printList(lentBooks, lent_num);
}

// the Book borrowed was returned so make book's state have
// borrower -> None, borrowed days -> 0
void returnedBook(Book* bList){
	string title;
	getline(cin, title);
	int index = searchBook(bList, strStrip(title));

	if(index == -1){
		cout<<"  ATTENTION NO SUCH BOOK!"<<endl;
	}else{
		if(bList[index].borrower.compare("None") != 0){
			bList[index].borrower = "None";
			bList[index].borrowed_days = 0;
			Book book = bList[index];
			printList(&book, 1);
		}
		else{
			cout<<"  ATTENTION No one borrowed that book!!"<<endl;
		}
	}

	cout<<endl;
}

// alarm if borrowed book's days of borrwed is less than 0
void alarmReBook(Book* bList, int num){
	for(int i=0; i<num; i++){
		if(bList[i].borrowed_days == 0){
			if(bList[i].borrower.compare("None")!=0)
				cout<<bList[i].title<<" should be returned today by "<<bList[i].borrower<<endl;
		}
		else if(bList[i].borrowed_days < 0)
			cout<<bList[i].title<<" SHOULD HAVE BEEN RETURNED ALREADY by "<<bList[i].borrower<<endl;
	}
}

// print cammnd and format list
void printCommand(){
	for(int i=0; i<15; i++)
		cout<<"=";

	cout<<" Available Commands & Format ";

	for(int i=0; i<15; i++)
		cout<<"=";

	cout<<endl;
	cout<<endl;

	cout<<"1. INSERT BookTitle; Author; PubYear; Edition"<<endl;
	cout<<"2. LEND BookTitle; Person Borrowing; How many days"<<endl;
	cout<<"3. SAVE new_filename.txt"<<endl;
	cout<<"4. RETURNED BookTitle"<<endl;
	cout<<"5. PASSDAY"<<endl;
	cout<<"6. PRINT"<<endl;
	cout<<"7. EXIT"<<endl;

	cout<<endl;
	for(int i=0; i<59; i++)
		cout<<"=";
	cout<<endl;

	cout<<">>";
}

// split string to array by designated string split
// return string array
string* strSplit(string subject, string split){
	int num = 0;
	int hpos = 0, tpos= 0;
	int strlength = 0;

	// find split point and get number of string array
	while((tpos = subject.find(split, hpos)) != string::npos){
		num++;
		hpos = tpos+split.length();
		if(hpos >= subject.length()) break;
	}
	// when n split occur, n+1 things are splited
	num++;
	hpos = 0, tpos= 0;
	string* str_array = new string[num];
	// find split point and split it
	for(int i=0; i<num; i++){
		tpos = subject.find(split, hpos);
		strlength = tpos-hpos;
		str_array[i] = subject.substr(hpos, strlength);
		hpos = tpos+split.length();
	}

	return str_array;
}

// strip right & left free space
string strStrip(string subject){
	int i=0;
	string str = subject;

	// left strip
	while(str.find(" ", i) == i) i++;
	str = str.substr(i);

	// right strip
	i = str.length() - 1;
	while(str.find(" ", i) == i) i--;
	str = str.substr(0, i+1);

	return str;
}

// get file's line length
int getLineNum(string fName){
	ifstream  inData;
    inData.open(fName);

    if(!inData){
		cout<<"File opening error"<<endl;
		return -1;
	}

	int line = 0;
	string str;
	// getline function get line from stream into string
    while(getline(inData, str)){
    	line++;
	}
	inData.close();
	return line;	// except first line
}

// get command string and categorize it
int getCommand(){
	string cmd;
	int cmd_num = -1;

	cin>>cmd;
	transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper);
	if(cmd == "INSERT")
		cmd_num = 1;
	else if(cmd == "LEND")
		cmd_num = 2;
	else if(cmd == "SAVE")
		cmd_num = 3;
	else if(cmd == "RETURNED")
		cmd_num = 4;
	else if(cmd == "PASSDAY")
		cmd_num = 5;
	else if(cmd == "PRINT")
		cmd_num = 6;
	else if(cmd == "EXIT")
		cmd_num = 7;

	return cmd_num;
}

//get command and work command
void workCmd(Book* bList, int cmd){

	switch(cmd){
		case 1:
			insertBook(bList);
			printList(bList, num_Book);
			break;
		case 2:
			lendBook(bList);
			break;
		case 3:
			saveFile(bList);
			break;
		case 4:
			returnedBook(bList);
			break;
		case 5:
			passDay(bList);
			break;
		case 6:
			printList(bList, num_Book);
			break;
		case 7:
			cout<<"Exit the program"<<endl;
			cout<<"Bye~"<<endl;
			break;
		case -1:
			cout<<"Wrong command"<<endl;
			cout<<endl;
			// read input buffer all
			string buf;
			getline(cin, buf);
			break;
	}
}