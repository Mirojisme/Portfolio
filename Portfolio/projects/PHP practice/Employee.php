<!DOCTYPE html>
<html lang="en">

<head>
	<meta charset="UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<title>PHP Form</title>
	<link rel="stylesheet" href="../../css/style.css">
	<script defer src="js/app.js"></script>

</head>

<body>
	<div class="nav">
		<div class="navlogo">
			<a href="#"><img src="../../images/Richard.png"></a>
		</div>

		<div class="dropdown" style="float: right;">
			<button class="dropbtn" aria-label="Open Navigation Menu">
				<img src="../../images/icons/Nav.png">
			</button>
			<div class="ddcontent">
				<a href="#abtme"><img src="../../images/icons/information.png">  About Me</a>
				<a href="#exp"><img src="../../images/icons/briefcase.png">  Experience</a>
				<a href="#project"><img src="../../images/icons/project.png">  Projects</a>
				<a href="#skill"><img src="../../images/icons/skills.png">  Skills</a>
				<a href="#resume"><img src="../../images/icons/cv.png">  Resume</a>
				<a href="#edu"><img src="../../images/icons/graduation.png">  Education</a>
				<a href="#contact"><img src="../../images/icons/letter.png">  Contact</a>
			</div>
		</div>
	</div>
	<div class="container">
		<div class="content-small">
			<p>
				The Simple Calculator section of the HTML code is a form-based interface that allows users to perform
				basic arithmetic operations. Here is a breakdown of its components:
			</p>

			<p>Description of the Simple Calculator:</p>
			<ul>
				Form Structure:
				<li>
					The calculator is implemented using an HTML form element. The form uses the POST method to submit
					user input data to a server-side script (handle_operation.php) for processing when the form is
					submitted.
				</li>
				<li>The calculator includes two input fields for entering numbers</li>
				<li>Both fields are text input elements</li>
				<li>
					The form includes a dropdown menu, and users can choose the desired operation to apply to the input
					numbers.
				</li>
				<li>A submit button</li>
			</ul>
		</div>
		<div class="content-small">
			<h2>PHP Form</h2>
			<br />
			<?php
			require 'Manager.php';
			require 'Sales.php';

			$empName = $_POST['empName'];
			$empMoney = $_POST['empMoney'];
			$empTitle = $_REQUEST['empTitle'];

				class Employee{

					private $name;
					private $position;
					private $salary;

					public function __construct($name, $position, $salary){
						$this->name = $name;
						$this->position = $position;
						$this->salary = $salary;
					}
					function get_name(){
						return $this->name;
					}
					function get_position(){
						return $this->position;
					}
					function get_salary(){
						return $this->salary;
					}

				}

			$empInfo = new Manager($empName, $empTitle, $empMoney);
			echo "</br>";
			echo $empInfo->get_name() . "<br>";

			echo $empInfo->get_position() . "<br>";

			echo $empInfo->get_salary() . "<br>";

			echo $empInfo->get_department() . "<br>";

			$empInfo = new Sales($empName, $empTitle, $empMoney);
			echo "</br>";
			echo $empInfo->get_name() . "<br>";

			echo $empInfo->get_position() . "<br>";

			echo $empInfo->get_salary() . "<br>";

			echo $empInfo->get_bonus() . "<br>";

			echo '<p><form method="POST" action="phpform.html">
				<input type="submit" value="Go Back!"/></form></p>';
			?>
		</div>

	</div>


	<footer>
		<!--<p>&copy; 2024 Responsive Webpage</p>-->
	</footer>
</body>

</html>
