<?php

/**
 * Widget system & columns
 * -----------------------
 *
 * The scripts below produce the $column and the $widgets array.
 *
 * @$column (array)
 *
 * 		The $column array contains the css class names for the widths or is NULL if there
 * 		are no widgets to render.
 *	
 *		example:
 *
 *		$column = array(
 *			"one" => 'three columns',
 *			"two" => 'nine columns',
 *			"three" => 'null',
 *			);
 *
 * @$widgets (array)
 *		
 *		The $widgets array can contain PageArrays of widgets (pages located under /widgets/)
 *		Each widget page has a templates and a position field. The position is the column
 *		position and the templates is an ASM select to select one or more template(s) where 
 *		the widget should be rendered. Two Page arrays are created, one for the left and 
 *		one for the right.
 *
 *		example:
 *
 *		$widgets = array(
 *			"one" => (PageArray) $widgetsColumnOne, // or NULL if there are no widgets.
 *			"three" => 'null', // or a PageArray of pages under /widgets/ with position left.
 *			);
 *
 */

$parent = $pages->get("template=widgets");
$widgetsColumnOne = $pages->find("parent={$parent}, templates={$page->template->id}, id!={$page->left}, position.name=left");
$widgetsColumnThree = $pages->find("parent={$parent}, templates={$page->template->id}, id!={$page->right}, position.name=right");

// All widgets are allowed to have their own styles and scripts.
foreach(array($widgetsColumnOne, $widgetsColumnThree) as $widgets) {
    foreach($widgets as $widget) {
        if(is_file("{$config->paths->templates}css/{$widget->template->name}.css")) {
            $config->styles->append("{$config->urls->templates}css/{$widget->template->name}.css");
        }
        if(is_file("{$config->paths->templates}js/{$widget->template->name}.js")) {
            $config->scripts->append("{$config->urls->templates}js/{$widget->template->name}.js");
        }
    }
}

$widthOne = count($widgetsColumnOne) ? $parent->columns->min : 0;
$widthThree = count($widgetsColumnThree) ? $fields->columns->data['maxValue'] - $parent->columns->max : 0;

$column = array(
	'one' => $widthOne,
	'two' =>  $fields->columns->data['maxValue'] - ( $widthOne + $widthThree),
	'three' => $widthThree,
	);

$widgets = array();
$widgets['one'] = $widthOne > 0 ? $widgetsColumnOne : null;
$widgets['three'] = $widthThree > 0 ? $widgetsColumnThree : null;

$numbers = array( null, 'one', 'two', 'three', 'four', 'five', 'six', 'seven', 'eight', 'nine', 'ten', 'eleven', 'twelve' );
	
foreach($column as $key => $value) $column[$key] = $numbers[$value];

/**
 *
 *
 */


