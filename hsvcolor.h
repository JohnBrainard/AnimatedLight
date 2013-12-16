#ifndef HSVTORGB_H
#define HSVTORGB_H

/**
 * Code inspired by @fins response here:
 * http://stackoverflow.com/questions/3018313/algorithm-to-convert-rgb-to-hsv-and-hsv-to-rgb-in-range-0-255-for-both
 */

typedef unsigned char uint8_t;

struct RGBColor
{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
};

struct HSVColor
{
	uint8_t hue;
	uint8_t saturation;
	uint8_t value;
};

RGBColor HSVToRGB(HSVColor hsvColor);
HSVColor HSVColorNew(uint8_t hue, uint8_t saturation, uint8_t value);
RGBColor RGBColorNew(uint8_t red, uint8_t green, uint8_t blue);

#endif
