<?php

// check if Modules are installed else install them.
foreach(array('MarkupCache','MarkupCSScompress') as $ClassName) {
	if(!$modules->isInstalled($ClassName)) {
		$modules->get($ClassName); // install
	}
}

$array = $session->get('MarkupCSScompress');

// check for $session
if( count($array)) {
	$files = $array['files'];
	$time = $array['time'];
	$cache_time = $time;
	$group = (int) $array['group'];
	$id = (int) $array['front']; // id of page in front
	$template = $pages->get($id)->template->name;
}


/**
 * Each file get it's own cache file with the URL as it's name.
 *
 */
$out = "";
$cachePath = '';
if(count($files)) {

	foreach($files as $key => $file) {
		
		// create $cache object
		$cache = $modules->get("MarkupCache");
		$cachedFileName = str_replace("/", "_", $file);
		
		// if there's no cache, store it with css url in the title
		if(!$data = $cache->get($cachedFileName, $time )) {
			
			$cache_time = 0;
			 
			// (array) put file & folders chunks in array 
			$fragments = explode( "/", $file );
			// (array) strip of unwanted, leave folders in array 
			$folders = array_slice($fragments, 1, sizeof($fragments) - 2);
			// (string) path to the CSS file, without the actual CSS file
			$path = $config->paths->root .implode("/", $folders );

			// load the Google Minify CSS class (small piece of it)
			require_once( $config->paths->MarkupCSScompress . "Minify/CSS.php" );

			$options = array(
				'preserveComments' => false,
				'currentDir' => $path,
            	'prependRelativePath' => null,
				);
			
			$css = new Minify_CSS;
			$data = $css->minify(file_get_contents($config->paths->root . $file), $options);
			
			// save created cache
			$cache->save($data);
		}
		
		$out .= $data;
	}
	
	// create template cache
	if($group) {

		$modified = false;

		$tplCache = $modules->get("MarkupCache");
		if(!$data = $cache->get($template, $time)) {
			$data = $out;
			$cache->save($data);
			$modified = true;
		}

		$groupCacheFile = $config->paths->cache . "MarkupCache/{$template}/{$template}.cache";
		if (file_exists($groupCacheFile)) {
			$groupCacheTime = filemtime($groupCacheFile);
		}
	}
}

header_remove(); 

// collect all output in buffer
if (substr_count($_SERVER['HTTP_ACCEPT_ENCODING'], 'gzip')) {
	ob_start("ob_gzhandler");
} else {
	ob_start();
}

if($group && !$modified) { 

   // print_r($session);
   //header('Expires: '.gmdate('D, d M Y H:i:s \G\M\T', time() + 1000000000));
   //header('HTTP/1.1 304 Not Modified');
}


header("Content-type: text/css; charset: UTF-8");



$language = "nl";
$tsstring = gmdate('D, d M Y H:i:s ', time()) . 'GMT';
$etag = $template;

$if_modified_since = isset($_SERVER['HTTP_IF_MODIFIED_SINCE']) ? $_SERVER['HTTP_IF_MODIFIED_SINCE'] : false;
$if_none_match = isset($_SERVER['HTTP_IF_NONE_MATCH']) ? $_SERVER['HTTP_IF_NONE_MATCH'] : false;
if ((($if_none_match && $if_none_match == $etag) || (!$if_none_match)) &&
    ($if_modified_since && $if_modified_since == $tsstring))
{
    header('HTTP/1.1 304 Not Modified');
    exit();
}
else
{
    header("Last-Modified: $tsstring");
    header("ETag: \"{$etag}\"");
}





echo $out;

// release the buffer & destroy the output
ob_end_flush();
