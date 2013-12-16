#include "AnimatedLight.h"

AnimatedLight::AnimatedLight(Adafruit_NeoPixel *strip, uint8_t pixel)
{
	_pixel = pixel;
	_strip = strip;
	_animatingFrom = RGBColorNew(0, 0, 0);
	_animatingTo = randomizeColor();
	_state = ANIMATING;

	strip->setPixelColor(pixel, 0, 0, 0);
}

AnimatedLightState AnimatedLight::state()
{
	return this->_state;
}

RGBColor AnimatedLight::randomizeColor()
{
	HSVColor hsvColor = { random(0, 360), 255, 255 };
	return HSVToRGB(hsvColor);
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
		int16_t redDiff = _animatingTo.red - _animatingFrom.red;
		int16_t greenDiff = _animatingTo.green - _animatingFrom.green;
		int16_t blueDiff = _animatingTo.blue - _animatingFrom.blue;

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
		_ticksToNextAnimation = random(150, 300);
		_state = WAITING;
	}
}
