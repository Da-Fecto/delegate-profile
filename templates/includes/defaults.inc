<?php

/**
 * File for common defaults, scripts & variables 
 * ---------------------------------------------------------------------------------------
 */

$page->scripts = false;
$homepage = $pages->get("/");
$content = '';

/**
 *	Setting stylesheets & javascripts
 * ---------------------------------------------------------------------------------------
 */

// stylesheets
$config->styles->append($config->urls->templates . "styles/default.css");

// javascripts
$config->scripts->append($config->urls->templates . "scripts/default.js");

// $scripts is rendered in the html tag <script /> ( within the document ready function )
$page->scripts = false;

/**
 * Global functions
 * ---------------------------------------------------------------------------------------
 *
 */

// render children
function renderChildren($page) {
	$output = '';
	if(count($page->children()) && $page->disableChildren === 0) {
		$output .= '<ul class="list-children">';
		foreach($page->children() as $child) $output .= "<li class='{$child->template}'><a href='{$child->url}' title='{$child->headline}'>{$child->title}</a></li>";
		$output .= '</ul>';
	}
	return $output;
}

// render children
function renderFiles($page) {
	$output = '';
	if(count($page->files) && $page->renderFiles === 1) {
		$output .= '<ul class="list-files">';
		foreach($page->files as $file) $output .= "<li class='{$file->ext}'><a href='{$file->url}'>{$file->get('description|name')}</a></li>";
		$output .= '</ul>';
	}
	return $output;
}

// navigation

function siteMap($page, $i=0) {

		$output = isset($output) ? $output : ''; $i++;
	
        $output .= "<li class='level-{$i}'><a href='{$page->url}'>{$page->title}</a>";
        if($page->numChildren) {
                $output .= "<ul>";
                foreach($page->children as $child) $output .= siteMap($child, $i);
                $output .= "</ul>";
        }
        $output .= "</li>";
        return $output;
}

$navigation = '<ul>' . siteMap($homepage) . '</ul>';

/**
 * The grid
 *
 * In total there are 12 columns. $firstColumn adapts her width from the leftovers from
 * $secondColumn and $thirdColumn combined.
 *
 */

// amount of columns depending on the availability of the widgets.
$col2 = (count($pages->find("parent=/widgets/, position=left")) == count($page->widgetsLeft)) ? 0 : 3;
$col3 = (count($pages->find("parent=/widgets/, position=right")) == count($page->widgetsRight)) ? 0 : 4;

$columns = array(
	// used as content column
	'one' => 12 - ($col2 + $col3),
	'two' => $col2,
	'three' => $col3,
	);

$column = array();
$cssNames = array(null,'one','two','three','four','five','six','seven','eight','nine','ten','eleven','twelve'); 
foreach($columns as $key => $value) $column[$key] = $cssNames[$value]; 

