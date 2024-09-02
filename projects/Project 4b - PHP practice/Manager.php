<?php
	class Manager extends Employee{

		private $department = "sales";

		public function __construct($name, $position, $salary){
			parent::__construct($name, $position, $salary);
		}

		public function set_department($department){
			$this->department = $department;
		}

		public function get_department(){
			return $this->department;
		}
	}
?>