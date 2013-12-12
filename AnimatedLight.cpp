#include "AnimatedLight.h"

const Color BLACK = { 0, 0, 0 };
const Color RED = { 255, 0, 0 };
const Color ORANGE = { 255, 64, 0 };
const Color YELLOW = { 255, 225, 0 };
const Color GREEN = { 0, 255, 0 };
const Color BLUE = { 0, 0, 255 };
const Color PURPLE = { 255, 0, 255 };

const Color PINK = { 255, 32, 32};
const Color CYAN = { 0, 255, 255 };

const Color* COLORS[] = { &RED, &ORANGE, &YELLOW, &GREEN, &BLUE, &PURPLE, &PINK, &CYAN };

AnimatedLight::AnimatedLight(Adafruit_NeoPixel *strip, uint8_t pixel)
{
	_pixel = pixel;
	_strip = strip;
	_animatingFrom = BLACK;
	_animatingTo = randomizeColor();
	_state = WAITING;
	_ticksToNextAnimation;
}

AnimatedLightState AnimatedLight::state()
{
	return this->_state;
}

Color AnimatedLight::randomizeColor()
{
	int numColors = sizeof(COLORS) / sizeof(Color*);
	return *COLORS[random(0, numColors)];
}

void AnimatedLight::tick()
{
	this->_tickCount++;

	switch (this->_state)
	{
	case WAITING:
		this->wait();
		break;

	case ANIMATING:
		this->animate();
		break;
	}
}

void AnimatedLight::wait()
{
	if (this->_tickCount > _ticksToNextAnimation)
	{
		_ticksToNextAnimation = 0;
		_tickCount = 0;
		_state = ANIMATING;
	}
}

void AnimatedLight::animate()
{
	if (_tickCount < 30)
	{
		int redDiff = _animatingTo.red - _animatingFrom.red;
		int greenDiff = _animatingTo.green - _animatingFrom.green;
		int blueDiff = _animatingTo.blue - _animatingFrom.blue;

		_strip->setPixelColor(_pixel,
			min(255, _animatingFrom.red + ((redDiff / 30) * _tickCount)),
			min(255, _animatingFrom.green + ((greenDiff / 30) * _tickCount)),
			min(255, _animatingFrom.blue + ((blueDiff / 30) * _tickCount)));
	}
	else
	{
		_animatingFrom = _animatingTo;
		_animatingTo = randomizeColor();

		_tickCount = 0;
		_ticksToNextAnimation = random(30, 300);
		_state = WAITING;
	}
}
