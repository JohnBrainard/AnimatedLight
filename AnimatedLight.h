#include <arduino.h>
#include <Adafruit_NeoPixel.h>

#ifndef AMINATED_LIGHT_H
#define ANIMATED_LIGHT_H

enum AnimatedLightState {
	WAITING,
	ANIMATING
};

typedef struct {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
} Color;

class AnimatedLight
{
public:
	AnimatedLight(Adafruit_NeoPixel *strip, uint8_t pixel);

	AnimatedLightState state();

	void tick();
	Color randomizeColor();

private:
	void wait();
	void animate();

	Adafruit_NeoPixel *_strip;
	uint8_t _pixel;
	Color _animatingFrom;
	Color _animatingTo;

	uint16_t _tickCount;
	uint16_t _ticksToNextAnimation;

	AnimatedLightState _state;
};

#endif
