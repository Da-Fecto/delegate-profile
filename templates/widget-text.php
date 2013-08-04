<?php

/**
 * Text widget template
 *
 */

// $page, variable of the mother Page
$motherPage = $page->motherPage; 
// Stop direct access for guests. 
if(!$motherPage && !$user->isLoggedin()) throw new Wire404Exception();

// default variables containing HTML
$title = !$page->checkbox ? "<h4>$page->title</h4>" : null; // render or not to render
$body = $page->body;

/**
 * Start Output
 *
 */

echo $title;
echo $body;
