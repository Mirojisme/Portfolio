<!doctype html>
<html lang="en">
<head>
	<meta charset="utf-8">
	<title>Calculation Result</title>
</head>
<body>
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
</body>
</html>