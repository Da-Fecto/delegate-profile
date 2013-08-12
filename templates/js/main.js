// Gumby is ready to go
Gumby.ready(function() {
	// console.log('Gumby is ready to go...', Gumby.debug());

	// placeholder polyfil
	if(Gumby.isOldie || Gumby.$dom.find('html').hasClass('ie9')) {
		$('input, textarea').placeholder();
	}
});

// Oldie document loaded
Gumby.oldie(function() {
	// console.log("This is an oldie browser...");
});

// Touch devices loaded
Gumby.touch(function() {
	console.log("This is a touch enabled device...");
});

// Document ready
$(function() {

	/**
	 * popup images helper
	 *
	 * Only load CSS & JS for images when needed.
	 *
	 */

	if($("a img").length) {
		Modernizr.load([{
		    load: ['/site/templates/js/jquery.magnific-popup.min.js', '/site/templates/css/magnific-popup.css'],
		    complete: function () {
				$("a img").parent().append("<div class='pop-up'><i class='icon-popup'></i></div>").addClass("magnific");
				$(".magnific").magnificPopup({
			   		type: 'image', 
			   		gallery: { enabled: true },
			   		removalDelay: 300,
					mainClass: 'popup-slide'
			   	});
		    }
		 }]);
	}

	/* avoid navbar jumping */
	var navHeight = $(".navbar").outerHeight();
	$(window).scroll(function(){
		$("#main-nav").removeAttr("style");
		$("#content").removeAttr("style");
		if($(".navbar").hasClass("fixed")) {
			$("#content").css({"paddingTop" : navHeight });
		} else if ($(".navbar").hasClass("unfixed")) {
			$("#content").css({"paddingTop" : 0 });
		}
	});
});

