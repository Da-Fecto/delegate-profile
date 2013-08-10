
// for keeping track of window resizes
var collagePlusResizeTimer = null;
var collagePlusCounter = 0;

function initCollagePlus() { 

	var $container = $("#select_images"); 
	var $images = $container.find("img");
	collagePlusCounter++;

	if(collagePlusCounter == 1) $images.each(function() {
		var $img = $(this);
		var file = $img.attr('src');
		file = file.substring(file.lastIndexOf('/')+1);
		$img.parent('a').parent('li').attr('data-caption', file); 
	}); 

	$container.removeWhitespace().collagePlus({
		'targetHeight': 200,
		'fadeSpeed': 'fast',
		'effect': 'effect-4',
		'direction': 'vertical',
		'allowPartialLastRow': true
		});

	if(collagePlusCounter == 1) $container.collageCaption({
		'speed': 0
	});

	$(window).bind('resize', function() {
		if(collagePlusResizeTimer) clearTimeout(collagePlusResizeTimer);
		collagePlusResizeTimer = setTimeout('initCollagePlus()', 200);
	});

}

$(document).ready(function() {
	// ensures it still works when the iframe src attr is changed
	// by pwimage plugin for TinyMCE or CKEditor
	setTimeout('initCollagePlus()', 100); 
}); 

