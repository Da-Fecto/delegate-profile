<?php

/**
 * Class to hold a range slider
 *
 */
class RangeSlider extends WireData {


	public function __construct() {
		$this->set('min', '');
		$this->set('max', '');
	}

	public function set($key, $value) {

		if($key == 'min' || $key == 'max') {
			// if value isn't numeric, then it's not valid: make it blank
			if(!is_numeric($value)) $value = '';	

		}
		return parent::set($key, $value);
	}

	public function get($key) {
		return parent::get($key);
	}

	
}



