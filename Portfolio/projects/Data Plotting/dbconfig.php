
<?php
$servername = "imc.kean.edu";
$username = "rangueir";
$password = "";
$dbname = "2024S_rangueir";

// Create connection
$conn = mysqli_connect($servername, $username, $password, $dbname);
// Check connection
if (!$conn) {
  die("Connection failed: " . mysqli_connect_error());
}



//mysqli_close($conn);
?>
