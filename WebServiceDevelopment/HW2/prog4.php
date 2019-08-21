<?php

	$db_host = "localhost";
	$db_user = "root";
	$db_pw = "tmfl3fkdzk4";
	$db_name = "class_web";
	$conn = mysqli_connect($db_host, $db_user, $db_pw, $db_name);

	if(mysqli_connect_errno($conn)){
		echo "Database connection failed: ".mysqli_connect_error();
	}else{
		//echo "Database connected";
	}

	$result = mysqli_query($conn, "SELECT * FROM csee_student WHERE major1 = 'CS'");

	echo "<h3>Student table who major in CS</h3>";
	echo "<table border = '1'>";
	echo "<tr><th>Student Number</th><th>Semester</th><th>Name</th><th>Major1</th><th>Major2</th></tr>";

	while($row = mysqli_fetch_array($result)){
		$student_no = $row['student_no'];
		$semester = $row['semester'];
		$name = $row['name'];
		$major1 = $row['major1'];
		$major2 = $row['major2'];

		echo "<tr><td>".$student_no."</td><td>".$semester."</td><td>".$name."</td><td>".$major1."</td><td>".$major2."</td></tr>";
	}

	mysqli_close($conn);
?>