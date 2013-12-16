#include "hsvcolor.h"

struct HSVColor;
struct RGBColor;

typedef unsigned char uint8_t;

RGBColor RGBColorNew(uint8_t red, uint8_t green, uint8_t blue)
{
	RGBColor color = { red, green, blue };
	return color;
}

HSVColor HSVColorNew(uint8_t hue, uint8_t saturation, uint8_t value)
{
	HSVColor color = { hue, saturation, value };
	return color;
}

RGBColor HSVToRGB(HSVColor hsvColor)
{
	RGBColor rgbColor;

	uint8_t region, remainder, p, q, t;

	if (hsvColor.saturation == 0)
	{
		rgbColor.red = hsvColor.value;
		rgbColor.green = hsvColor.value;
		rgbColor.blue = hsvColor.value;
		return rgbColor;
	}

	region = hsvColor.hue / 43;
	remainder = (hsvColor.hue - (region * 43)) * 6;

	p = (hsvColor.value * (255 - hsvColor.saturation)) >> 8;
	q = (hsvColor.value * (255 - ((hsvColor.saturation * remainder) >> 8))) >> 8;
	t = (hsvColor.value * (255 - ((hsvColor.saturation * (255 - remainder)) >> 8))) >> 8;

	switch (region)
	{
		case 0:
			rgbColor.red = hsvColor.value;
			rgbColor.green = t;
			rgbColor.blue = p;
			break;

		case 1:
			rgbColor.red = q;
			rgbColor.green = hsvColor.value;
			rgbColor.blue = p;
			break;

		case 2:
			rgbColor.red = p;
			rgbColor.green = hsvColor.value;
			rgbColor.blue = t;
			break;

		case 3:
			rgbColor.red = p;
			rgbColor.green = q;
			rgbColor.blue = hsvColor.value;
			break;

		case 4:
			rgbColor.red = t;
			rgbColor.green = p;
			rgbColor.blue = hsvColor.value;
			break;

		default:
			rgbColor.red = hsvColor.value;
			rgbColor.green = p;
			rgbColor.blue = q;
	}

	return rgbColor;
}
