#TextformatterImageInterceptor

Let editors use WYSIWYG images, but let you control the image size, aspect ratio & behaviour. 

## How to install

- Copy the TextformatterImageInterceptor.module file to your /site/modules/ directory (or place it in /site/modules/TextformatterImageInterceptor/). 
- Click *check for new modules* in ProcessWire Admin Modules screen. Click *install* for the module labeled: "Image Interceptor".
- Go to the module config screen and set the settings you wish.

## How to use
- Edit your *body* field in Setup > Fields (or whatever field(s) you will be placing controlled images in). On the *details* tab, find the *Text Formatters* field and select "Image Interceptor". Save.

## About the settings

- **Render Inline styles** 
	- If checked, some inline styles are added to the image.
- **High Density**
	- Double the pixel width of an image if the *percentage* is not set. *(fixed image size)*
	 

Default there are settings for landscape & portrait images. Squared images will inherit all settings belonging to portrait settings and there's a way to escape the default settings. 

But before we dive deeper in *tagged sets* I want to spread some light on the landscape/portrait settings. All images portrait/landscape wil get the class name .default

##### The settings:

- **Percentage**
	- The width of the image in percentage. This setting makes the image responsive or if left blank the image wil be fixed size. Images receive a .responsive and a .p-50 class (where 50 is the width in percentage)
- **Width**
	- The width of the image in pixels. So the width of the image in percentage and the pixel width combined wil be the key to pixel desity.
- **Alignment** 
	- There are 5 different ways to align an image. *left*, *center*, *right*, *inherit* (inherits from the WYSIWYG editor) and *not aligned*. 
	- If render inline styles is checked the aligment wil be set directly in the inline style of the image. Alignment classes wil be added to the image.
- **Aspect Ratio** (cropping)
	- if an aspect ratio is given, the image will be cropped to the given ratio. If you type 2:1 in the landscape settings. Images 800 pixels wide, will be croped to a 800x400 image. The image gets the following classes: *.cropped* and *.crop-2x1*	

- **Image Captions**
	- Type here your class name(s) for the caption. When a class name is provided and an image has a description, the image is wrapped (if not already) and *has-* is set in front of the class name(s). For the caption a div is created with the class name(s) and the image description as text.

Next to these settings. You can give custom classes to images. This way you can give it framework specific classes for example. And you're allowed to wrap the images with custom HTML. (Some frameworks needs additional HTML to make images more fancy) Then additional styles could be added to images if render inline styles is checked.

Note: If you use a wrapper or captions (wrapper will be created if none is set), the inline styles and specific width & alignment classes will be set to the wrapper and removed from the image. This way no duplication of styles wil take place.

## Tagged sets

Tagged sets are an image tag followed by settings specific for images with that tag.

To enable tagged sets, the image field need "Use Tags?" to be checked. Go to setup, then fields go to your image field and under the details tab check "Use Tags?". 

Taged sets are a good way to escape the default image behaviour. Say you have a bunch of nicely ordered images on the page, but you want to show a company logo on 150px floated left. With tagged sets it's no problem. type: (logo 150px left) on one line and you've created your first set.

If you want captions for a tagged set, keep in mind that captions need at least 1 class. The format to enter:
*caption.class-name*. 

For an image wrapper we use the same rules. The only difference is we start typing *wrapper* followed by class names starting with a dot. example: wrapper.logo.stand-out.

You can have a multitude of sets, every set on it's own line. Every set needs at least a *tag-name* and a *pixel width*.