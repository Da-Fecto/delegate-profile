<?php

/**
 * Main HTML view file
 *
 * All output variables set in the templates are rendered within this file.
 *
 * The custom template name styles & scripts are appended to the end of the scripts/styles
 * array so we can overwrite previously set styles & scripts.
 *
 */
 
if(!strlen($content)) $content = $page->body;

// if the current template has it's own custom stylesheet, then append it to the array
if(is_file("{$config->paths->templates}styles/{$page->template}.css")) {
	$config->styles->append("{$config->urls->templates}styles/{$page->template}.css");
}

// if the current template has it's own custom javascript file, then append it to the array
if(is_file("{$config->paths->templates}scripts/{$page->template}.js")) {
	$config->scripts->append("{$config->urls->templates}scripts/{$page->template}.js");
}

/**
 * HTML head
 * ---------------------------------------------------------------------------------------
 *
 */

// Collect the head in the variable $page->head for more flexibility
$page->head = "<!DOCTYPE html>";
$page->head .= "<!--[if lt IE 7]><html class='no-js lt-ie9 lt-ie8 lt-ie7'><![endif]-->";
$page->head .= "<!--[if IE 7]><html class='no-js lt-ie9 lt-ie8'><![endif]-->";
$page->head .= "<!--[if IE 8]><html class='no-js lt-ie9'><![endif]-->";
$page->head .= "<!--[if gt IE 8]><!--><html class='no-js'><!--<![endif]-->";
$page->head .= "<head>";
$page->head .= "<meta charset='utf-8' />";
$page->head .= "<meta http-equiv='X-UA-Compatible' content='IE=edge,chrome=1' />";
$page->head .= "<title>{$page->get('headline|title')}</title>";
$page->head .= "<meta name='viewport' content='width=device-width' />";

// attached only if there is a meta description set in the admin
if(strlen($page->metaDescription)) $page->head .= "<meta name='description' content='{$page->metaDescription}' />";

// output the collected styles
foreach($config->styles->unique() as $file) $page->head .= "<link rel='stylesheet' href='$file' />";

// try jQuery on google CDN else include local version
$page->head .= "<script src='//ajax.googleapis.com/ajax/libs/jquery/1/jquery.min.js'></script>";
$page->head .= "<script>window.jQuery || document.write('<script src=\"/site/templates/scripts/libs/jQuery.js\"><\/script>')</script>";

// output the collected scripts
foreach($config->scripts->unique() as $file) $page->head .=  "<script src='$file'></script>";

if($page->scripts) {
	$page->head .= "<script>";
	$page->head .= "	$(function() {";
	$page->head .= 			$page->scripts;
	$page->head .= "	});";
	$page->head .= "</script>";
}

$page->head .= "</head>";

// render the head.
echo preg_replace("/\s+/", " ", $page->head);

/**
 * HTML body
 * ---------------------------------------------------------------------------------------
 *
 */

echo "<body class='{$page->template}'>";

$search = htmlentities($input->whitelist('q'), ENT_QUOTES, 'UTF-8');

$page->search = "<div class='row'>";
$page->search .= "	<div class='column twelve'>";
$page->search .= "		<div class='panel'>";
$page->search .= "			<form id='search_form' action='{$config->urls->root}search/' method='get'>";
$page->search .= "				<input type='text' name='q' value='{$search}' />";
$page->search .= "				<button type='submit' id='search_submit'>Search</button>";
$page->search .= "			</form>";
$page->search .= "		</div>";
$page->search .= "	</div>";
$page->search .= "</div>";

echo preg_replace("/\s+/", " ", $page->search);

// create the columns, $column[$key] returns false if there are no widgets to render
$columns = "<div class='row'>";

// column 1
if($column['one']) {
	$columns .= "<div class='column {$column['one']} push-{$column['two']}'>";
	$columns .= "	<div class='panel'>";
	$columns .= "		<h3>Hi I'm {$column['one']}</h3>";
	$columns .= "		<p>I'm am the first column in the source, but my brother <strong>{$column['two']}</strong> pushed me to the center. My friend Google realy likes me.</p>";

	$columns .= $content;
	// render children if unchecked in admin
	$columns .= renderChildren($page);
	// render files if checked in admin
	$columns .= renderFiles($page);

	$columns .= "	</div>";
	$columns .= "</div>";
}

// column 2
if($column['two']) {
	$columns .= "<div class='column {$column['two']} pull-{$column['one']}'>";
	$columns .= "	<div class='panel'>";
	$columns .= "		<h3>Hello I'm {$column['two']}</h3>";
	$columns .= "		<p>My sister <strong>{$column['one']}</strong> pulled me to the left. I don't mind, cause I'd like to be aside.</p>";

	// render left widgets
	$exclude = $page->widgetsLeft;
	$widgets = $pages->find("parent=/widgets/, position=left, id!=$exclude");
	foreach($widgets as $widget) $columns .= "<div class='widget {$widget->template}'>" . $widget->render() . "</div>";

	$columns .= "	</div>";
	$columns .= "</div>";
}

// column 3
if($column['three']) {
	$columns .= "<div class='column {$column['three']} end'>";
	$columns .= "	<div class='panel'>";
	$columns .= "		<h3>And I'm {$column['three']}</h3>";
	$columns .= "		<p>I'm hugging my sister <strong>{$column['one']}</strong> in the browser. The true me and my brother <strong>{$column['one']}</strong> take our space in a row. My sister on the other hand has to do it with the leftovers.</p>";

	// render left widgets
	$exclude = $page->widgetsRight;
	$widgets = $pages->find("parent=/widgets/, position=right, id!=$exclude");
	foreach($widgets as $widget) $columns .= "<div class='widget {$widget->template}'>" . $widget->render() . "</div>";

	$columns .= "	</div>";
	$columns .= "</div>";
}

$columns .= "</div>";

// replace all multiple white-spaces, tabs and new-lines with just one space.
echo preg_replace("/\s+/", " ", $columns);

// echo a link to the admin if the user has the rights to edit the page.
if($page->editable()) echo "<a id='editpage' href='{$config->urls->admin}page/edit/?id={$page->id}'>edit</a>";

echo "</body>";
echo "</html>";


