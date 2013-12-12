#include <arduino.h>

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
	AnimatedLight();
	AnimatedLight(uint8_t r, uint8_t g, uint8_t b);

	uint8_t red();
	uint8_t green();
	uint8_t blue();

	AnimatedLightState state();

	void tick();
	Color randomizeColor();

private:
	void wait();
	void animate();

	Color _color;
	Color _animatingFrom;
	Color _animatingTo;

	uint16_t _tickCount;
	uint16_t _ticksToNextAnimation;

	AnimatedLightState _state;
};

#endif
