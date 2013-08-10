<?php








?><!doctype html>
<!-- paulirish.com/2008/conditional-stylesheets-vs-css-hacks-answer-neither/ -->
<!--[if lt IE 7]> <html class="no-js ie6 oldie" lang="<?=$language ?>"> <![endif]-->
<!--[if IE 7]>    <html class="no-js ie7 oldie" lang="<?=$language ?>"> <![endif]-->
<!--[if IE 8]>    <html class="no-js ie8 oldie" lang="<?=$language ?>"> <![endif]-->
<!--[if IE 9]>    <html class="no-js ie9" lang="<?=$language ?>"> <![endif]-->
<!-- Consider adding an manifest.appcache: h5bp.com/d/Offline -->
<!--[if gt IE 8]><!--> <html class="no-js" lang="<?=$language?>" itemscope itemtype="http://schema.org/Product"> <!--<![endif]-->
<head>
    <meta charset="utf-8">

    <!-- Use the .htaccess and remove these lines to avoid edge case issues.
       More info: h5bp.com/b/378 -->
    <meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1">

    <title><?=$browserTitle ?></title>
    <meta name="description" content="<?=$page->get("headline|title") ?>" />
    <meta name="author" content="humans.txt">

    <link rel="shortcut icon" href="favicon.png" type="image/x-icon" />

    <!-- Facebook Metadata /-->
    <meta property="fb:page_id" content="" />
    <meta property="og:image" content="" />
    <meta property="og:description" content=""/>
    <meta property="og:title" content=""/>

    <!-- Google+ Metadata /-->
    <meta itemprop="name" content="">
    <meta itemprop="description" content="">
    <meta itemprop="image" content="">

    <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1">

	<?=$modules->get('MarkupCSScompress')->render()?>

   <script src="<?=$config->urls->templates ?>js/libs/modernizr-2.6.2.min.js"></script>
</head>
<body class='<?=$page->template->name?>'>

<div class="row">
	<div class='columns twelve'>
		<h2>Amet Egestas</h2>
		<p>Vivamus sagittis lacus vel augue laoreet rutrum faucibus dolor auctor. Nullam id dolor id nibh ultricies vehicula ut id elit. Praesent commodo cursus magna, vel scelerisque nisl consectetur et. Vestibulum id ligula porta felis euismod semper. Fusce dapibus, tellus ac cursus commodo, tortor mauris condimentum nibh, ut fermentum massa justo sit amet risus. Curabitur blandit tempus porttitor.</p>
	</div>
</div>

<div class="navbar" id="main-nav" gumby-fixed="top">
	<div class="row">
		<a class="toggle" gumby-trigger="#main-nav > .row > ul" href="#"><i class="icon-menu"></i></a>
		<?= $renderNav ?>
	</div>
</div>

<div id="content" class="row">

<?php 

	/**
	 * Column One
	 *
	 */
	
	if($column['one']) { 
		echo "<div class='widgets {$column['one']} columns'>";
		foreach($widgets['one'] as $widget) {			
			$widget->set('motherPage', $page);
			echo "<div class='widget {$widget->template->name}'>";
			echo $widget->render();
			echo "</div>";
		} 
		echo "</div>";
		echo "<!-- .{$column['one']} -->";
	}
	
	/**
	 * Column Two
	 *
	 */
	
	if($column['two']) {
		echo "<div class='{$column['two']} columns'>";
		echo $content;
		echo "</div>";
		echo "<!-- .{$column['two']} -->";
	}

	/**
	 * Column Three
	 *
	 */
	
	if($column['three']) { 
		echo "<div class='widgets {$column['three']} columns'>";
		foreach($widgets['three'] as $widget) {
			$widget->set('motherPage', $page);
			echo "<div class='widget {$widget->template->name}'>";
			echo $widget->render();
			echo "</div>";
		} 
		echo "</div>";
		echo "<!-- .{$column['three']} -->";
	}
?>
	
</div>

<!-- Grab Google CDN's jQuery, fall back to local if offline -->
<!-- 2.0 for modern browsers, 1.10 for .oldie -->
<script>
	var oldieCheck = Boolean(document.getElementsByTagName('html')[0].className.match(/\soldie\s/g));
	if(!oldieCheck) {
		document.write('<script src="//ajax.googleapis.com/ajax/libs/jquery/2.0.2/jquery.min.js"><\/script>');
	} else {
		document.write('<script src="//ajax.googleapis.com/ajax/libs/jquery/1.10.1/jquery.min.js"><\/script>');
	}
</script>
<script>
if(!window.jQuery) {
	if(!oldieCheck) {
		document.write('<script src="js/libs/jquery-2.0.2.min.js"><\/script>');
	} else {
  		document.write('<script src="js/libs/jquery-1.10.1.min.js"><\/script>');
	}
}
</script>

<?php foreach($config->scripts->unique() as $file) echo "<script src='{$file}'></script>\n"; ?>

<!--[if lt IE 7 ]>
<script src="//ajax.googleapis.com/ajax/libs/chrome-frame/1.0.3/CFInstall.min.js"></script>
<script>window.attachEvent('onload',function(){CFInstall.check({mode:'overlay'})})</script>
<![endif]-->

<?php if($page->editable()) echo "<div id='edit' class='pretty medium primary btn icon-left icon-pencil'><a href='/processwire/page/edit/?id={$page->id}'>Edit</a></div>"; ?>

</body>
</html>
