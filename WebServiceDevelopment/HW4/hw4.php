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

	$name = $_POST['name'];
	$id = $_POST['id'];
	$pw = $_POST['password'];
	$gender = $_POST['gender'];

	// major array to major string by using implode built-in function
	$majors = $_POST['major'];
	$major_str = implode(", ", $majors);

	$year = $_POST['year'];
	$message = $_POST['message'];
	// if message is longer than 512 characters, make it truncated by using substr built-in function
	if(strlen($message) >= 512){
		$message = substr($message, 0, 512);
	}

	if(checkIDDuplicated($id, $conn)){
		echo "Duplicated ID";
	}else{
		addAttribute($name, $id, $pw, $gender, $major_str, $year, $message, $conn);
	}

	// return true if id was duplicated else return false
	function checkIDDuplicated($id, $conn){
		$qry = "SELECT id FROM user WHERE id='".$id."'";
		$result = mysqli_query($conn, $qry);
		$row = mysqli_fetch_array($result);
		// No such id in user table
		if($row == NULL)
			return FALSE;
		else
			return TRUE;
	}

	function addAttribute($name, $id, $pw, $gender, $major, $year, $message, $conn){
		$qry = "INSERT INTO `user` VALUES('".$name."', '".$id."', '".$pw."', '".$gender."', '".$major."', '".$year."', '".$message."')";
		$result = mysqli_query($conn, $qry);
		if($result == FALSE)
			echo "Add Attribute Failure";
	}

	function showTable($conn){
		$qry = "SELECT * FROM `user`";
		$result = mysqli_query($conn, $qry);
		while($row = mysqli_fetch_array($result)){
			echo "<tr>";
			echo "<th>".$row['NAME']."</th>";
			echo "<th>".$row['ID']."</th>";
			echo "<th>".$row['PASSWORD']."</th>";
			echo "<th>".$row['GENDER']."</th>";
			echo "<th>".$row['MAJOR']."</th>";
			echo "<th>".$row['YEAR']."</th>";
			echo "<th>".$row['MESSAGE']."</th>";
			echo "</tr>";
		}
	}
?>
<!DOCTYPE html>
<html>
	<head>
		<meta charset="utf-8"/>
		<title>HW4</title>
	</head>
	<body>
		<h3>Sign Up Result</h3>
		<table border="1">
			<caption>User List</caption>
			<tr>
				<th>Name</th>
				<th>ID</th>
				<th>Password</th>
				<th>Gender</th>
				<th>Major</th>
				<th>Year</th>
				<th>Message</th>
			</tr>
			<?php
				showTable($conn);
			?>
		</table>
	</body>
</html>