<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<title>Richard Angueira</title>
	<link rel="stylesheet" href="css/style.css">
	<script defer src="js/app.js"></script>

</head>
<body>

	<div class="nav">
		<div class="navlogo">
			<a href="#"><img src="images/Richard.png"></a>
		</div>
		
		<div class="dropdown" style="float: right;">
			<button class="dropbtn">
				<img src="images/icons/Nav.png">
			</button>
			<div class="ddcontent">
				<a href="#abtme"><img src="images/icons/information.png">  About Me</a>
				<a href="#exp"><img src="images/icons/briefcase.png">  Experience</a>
				<a href="#project"><img src="images/icons/project.png">  Projects</a>
				<a href="#skill"><img src="images/icons/skills.png">  Skills</a>
				<a href="#resume"><img src="images/icons/cv.png">  Resume</a>
				<a href="#edu"><img src="images/icons/graduation.png">  Education</a>
				<a href="#contact"><img src="images/icons/letter.png">  Contact</a>
			</div>
		</div>
	</div>

	<div class="container">
		<?php # handle_form.php
			//Validation of input data, check empty

			//retrieve and cast the data by using $_REQUEST or $_POST and name of the textboxes
			$num1 = $_POST['number1'];
			$num2 = $_POST['number2'];
			$operation = $_REQUEST['operation'];


			//Checks to see if both inputs are numeric and not Null
			if (is_numeric($num1) and is_numeric($num2)) {
			echo "<p> You want to $operation '$num1' and '$num2'</p>";

				if ($operation == "add"){
					$result = $num1+$num2;
					// Print the submitted information:
					echo "<p> The result is $result<p>";
				}
				elseif ($operation == "subtract") {
					$result = $num1-$num2;
					// Print the submitted information:
					echo "<p> The result is $result<p>";
				}
				elseif ($operation == "multiply") {
					$result = $num1*$num2;
					// Print the submitted information:
					echo "<p> The result is $result<p>";
				}
				elseif ($operation == "divide") {
					if ($num2 == "0") {
						// Print division by 0 error:
						echo "<p> Well you can't divide by 0... idiot.<p>";
					} else { 
						$result = $num1/$num2;
						// Print the submitted information:
						echo "<p> The result is $result<p>";
					}
				}
				elseif ($operation == "mod"){
					if ($num2 == "0") {
						// Print division by 0 error:
						echo "<p> Well you can't divide by 0... idiot.<p>";
					} else { 
						$result = $num1%$num2;
						// Print the submitted information:
						echo "<p> The result is $result<p>";
					}
				}
	
			} else {
				// Print numerical value error:
				echo "<p> Please input numerical values only...<p>";
			}

			echo '<form method="POST" action="Arithmetic.htm">
				<input type="submit" value="Go Back!"/></form>';

			?>
	</div>


	<footer>
		<!--<p>&copy; 2024 Responsive Webpage</p>-->
	</footer>
</body>
</html>