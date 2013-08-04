
# RangeSlider module for ProcessWire 2.+

Forum thread:
[RangeSlider Thread](http://processwire.com/talk/topic/972-jquery-ui-range-slider-fieldtype/page__hl__rangeslider)

## How does it work

This fieldtype let's you create slider input fields in the admin
using the built in jQuery UI Slider. You can use it as a regular
single value slider, or enable range which gives you two number.

### Output the values in templates

If used as single value slider
    `echo $page->fieldname`

If ranged slider is enabled
    `echo $page->fieldname->min`
    `echo $page->fieldname->max`

### Use in selectors strings

With a regular single value slider
    `$pages->find("range=120");`

If range slider is enabled
    `$pages->find("range.min>=100, range.max<120");`


## It comes with various settings.

- range enable
- width of slider (%)
- min value
- max value
- default value
- step
- prefix for displayed value(s)
- suffix for displayed value(s)



## How to install

1. Download and place the RangeSlider folder in:
/site/modules/

2. In the admin control panel, go to Modules. At the bottom of the
screen, click the "Check for New Modules" button.

3. Now scroll to the RangeSlider Fieldtype module and click "Install".

4. Create a new Field with the new "RangeSlider" Fieldtype. Once saved
you can configure the fieldtype, with various options under "Details" tab.
