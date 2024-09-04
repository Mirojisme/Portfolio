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

echo '<p><form method="POST" action="Main.html">
    <input type="submit" value="Go Back!"/></form></p>';
?>
