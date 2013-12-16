#include <arduino.h>
#include <Adafruit_NeoPixel.h>
#include <hsvcolor.h>

#ifndef AMINATED_LIGHT_H
#define ANIMATED_LIGHT_H

enum AnimatedLightState {
	WAITING,
	ANIMATING
};

class AnimatedLight
{
public:
	AnimatedLight(Adafruit_NeoPixel *strip, uint8_t pixel);

	AnimatedLightState state();

	void tick();
	RGBColor randomizeColor();

private:
	void wait();
	void animate();

	Adafruit_NeoPixel *_strip;
	uint8_t _pixel;
	RGBColor _animatingFrom;
	RGBColor _animatingTo;

	uint16_t _tickCount;
	uint16_t _ticksToNextAnimation;

	AnimatedLightState _state;
};

#endif
