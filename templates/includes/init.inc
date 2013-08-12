<?php

/**
 *	Global variables, styles & scripts
 * ---------------------------------------------------------------------------------------
 */

setlocale(LC_TIME, 'NL_nl');
$language = 'nl';

/**
 * Styles and JavaScripts
 *
 */

// Strip out styles not belonging to the front-end
foreach($config->styles->unique() as $file) {
	if (stripos($file, $config->urls->templates) === false) {
		$config->styles->remove($file);
	}
}

// Stylesheets
$config->styles->append("{$config->urls->templates}css/gumby.css");
$config->styles->append("{$config->urls->templates}css/style.css");
if(is_file("{$config->paths->templates}css/{$page->template->name}.css")) {
	$config->styles->prepend("{$config->urls->templates}css/{$page->template->name}.css");
}

// JavaScripts
$config->scripts->append("{$config->urls->templates}js/libs/gumby.min.js");
$config->scripts->append("{$config->urls->templates}js/libs/ui/gumby.navbar.js");
$config->scripts->append("{$config->urls->templates}js/plugins.js");
$config->scripts->append("{$config->urls->templates}js/main.js");
if(is_file("{$config->paths->templates}js/{$page->template->name}.js")) {
	$config->styles->append("{$config->urls->templates}js/{$page->template->name}.js");
}

/**
 * Variables
 *
 */

// Access to homepage
$home = $pages->get(1);
// Title for title tag
$browserTitle = $home === $page ? $home->get('headline|title') : "{$page->get('headline|title')} - {$home->get('headline|title')}";
$content = ""; 
/**
 * Global functions
 *
 */

require_once("./includes/func.inc");