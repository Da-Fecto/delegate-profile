#How to Install
Grab a copy of the latest ProcessWire. Replace the install, modules and templates directories with those in this profile, as shown below:

/site-default/install/  
/site-default/modules/  
/site-default/templates/  

That is all there is to do. Install ProcessWire as per the instructions included with it and it will install the blog profile automatically.

---

#delegate profile

Basically the home & basic-page template have the same fields. 

- Home » **home template**
	- Basic-Page » **basic-page template**
	- Search » **search template**
	- Widgets » **widgets template** » **status:hidden**
		- widget-one, Left, Left widget » **widget-one template**
		- widget-two, Right, Right widget » **widget-two template**
	- 404 Page Not Found » **basic page template** » **status:hidden**
	- Admin
		- Settings » **settings template** » **status:hidden** » **no file** » **access:guest view pages**
			- Position left or right » **settings template** » **status:hidden** » **no file** » **access:guest view pages**
				- Left **setting template** » **no file**
				- Right **setting template** » **no file**
	- Trash

###defaults.inc

The home & basic-page templates include ./include/defaults.inc on top and on the bottom ./includes/main-view.inc. The defaults.inc is the file for common defaults, scripts & variables. Also there's living for commonly used functions & the 12 column classname generate thingy.

###the 12 column grid

On the home & basic-page pages you can check to disable the left & right widgets. If there are no left-widgets to render, then there's no use to render the column at all on the page. The content column then receives the width of the left-column. There are in total 12 columns, say the right column has a width of 3 and the left has a width of 4, then the leftover for the content column is 5. So if there are no left widgets, then the content colum is 9. Those numbers are set to their written equals or set to FALSE. 

	$column['one'] could be FALSE or one, two, three, four, five, etc.
	$column['two'] could be FALSE or one, two, three, four, five, etc.
	$column['three'] could be FALSE or one, two, three, four, five, etc.

###main-view.inc

The main-view.inc is the main markup file. In this file I'll check if "template-name.css" & "template-name.js" exists and the append them to the syles & scripts array before I output them with a foreach loop in the page head. This way I know that basic-page.css for example is always the last file & can overwrite previously set styles.

The grid uses the same source ordering approach as the [zurb foundation grid](http://foundation.zurb.com/docs/grid.php) uses. For mobile it's often a pre that the content column is showed first but on desktop there's plenty space to have a left column first. Thereby I think that Google loves content higher in the source more then if that content is a latecomer.

###widgets

The widgets are just chunks of HTML without `<head>, <body>` etc. So they can be rendered with the build in Processwire render() function. Nothin' special there.