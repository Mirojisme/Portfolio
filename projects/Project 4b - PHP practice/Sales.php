<?php
	class Sales extends Employee{

		private $bonus = "10%";

		public function __construct($name, $position, $salary){
			parent::__construct($name, $position, $salary);
		}

		public function set_bonus($bonus){
			$this->bonus = $bonus;
		}

		public function get_bonus(){
			return $this->bonus;
		}		
	}

?>