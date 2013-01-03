<?php

/**
 * search template
 *
 */

include("./includes/defaults.inc"); 

if($q = $sanitizer->selectorValue($input->get->q)) {

	// Send our sanitized query 'q' variable to the whitelist where it will be
	// picked up and echoed in the search box by the head.inc file.
	$input->whitelist('q', $q); 

	// Search the title, body and sidebar fields for our query text.
	// Limit the results to 50 pages. 
	// Exclude results that use the 'admin' template. 
	$matches = $pages->find("title|body~=$q, limit=50"); 

	$count = count($matches); 

	if($count) {
		$content .= "<h2>Found $count pages matching your query:</h2>" . 
			"<ul class='nav'>";

		foreach($matches as $m) {
			$content .= "<li><p><a href='{$m->url}'>{$m->title}</a><br />{$m->summary}</p></li>";
		}

		$content .= "</ul>";

	} else {
		$content .= "<h2>Sorry, no results were found.</h2>";
	}
} else {
	$content .= "<h2>Please enter a search term in the search box (upper right corner)</h2>";
}

// Note that we stored our output in $content before printing it because we wanted to execute
// the search before including the header template. This is because the header template 
// displays the current search query in the search box (via the $input->whitelist) and 
// we wanted to make sure we had that setup before including the header template. 


include("./includes/main-view.inc"); 