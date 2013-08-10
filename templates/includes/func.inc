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
 * Navigation
 * 
 * Full Options, 
 */

$options = array(
    'parent_class' => 'parent', // string (default 'parent') overwrite class name for current parent levels
    'current_class' => 'current', // string (default 'current') overwrite current class
    'has_children_class' => 'folder', // string (default 'has_children') overwrite class name for entries with children
    'levels' => false, // bool (default false) wether to output "level-1, level-2, ..." as css class in links
    'levels_prefix' => 'level-', // bool (default 'level-') prefix string that will be used for level class
    'max_levels' => 2, // int (default null) set the max level rendered
    'firstlast' => true, // bool (default false) puts last,first class to link items
    'collapsed' => false, // bool (default false) if you want to auto-collapse the tree you set this to true
    'show_root' => true, // bool (default false) set this to true if you want to rootPage to get prepended to the menu
    'selector' => '', // string (default '') define custom PW selector, you may sanitize values from user input
    'outer_tpl' => '<ul class="eight columns">||</ul>', // template string for the outer most wrapper. || will contain entries
    'inner_tpl' => '<div class="dropdown"><ul>||</ul></div>', // template string for inner wrappers. || will contain entries
    'list_tpl' => '<li%s>||</li>', // template string for the items. || will contain entries, %s will replaced with class="..." string
    'list_field_class' => '{template }', // string (default '') add custom classes to each list_tpl using tags like {field} i.e. {template} p_{id}
    'item_tpl' => '<a href="{url}">{title}</a>', // template string for the inner items. Use {anyfield} and {url}, i.e. {headline|title}, if field is of type image it will return url to image (first image if multiple)
    'item_current_tpl' => '<a href="{url}">{title}</a>', // template string for the current active inner items.
    'xtemplates' => 'basic', // specify templates i.e. "folder|placeholder" for pages that need different output.
    'xitem_tpl' => '<span>{title}</a>',
    'xitem_current_tpl' => '<span>{title}</span>'
);

$nav = $modules->get("MarkupSimpleNavigation");
$renderNav = $nav->render($options, $page, $home);

/**
 *
 *
 */
