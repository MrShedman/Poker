#include <Button.hpp>
#include <iostream>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <Utility.h>

namespace GUI
{

Button::Button(State::Context context)
: mCallback()
, mShape(sf::Vector2f(240, 70))
, mText("", context.fonts->get(Fonts::Main), 35)
, window(*context.window)
, mSounds(*context.sounds)
, isPressed(false)
{
	changeState(Normal);

	mShape.setOutlineThickness(-5.f);
	mShape.setOutlineColor(sf::Color::Black);

	sf::FloatRect bounds = mShape.getLocalBounds();
	mText.setPosition(bounds.width / 2.f, bounds.height / 2.f - 5);
	mText.setFillColor(sf::Color::Black);
}

void Button::setCallback(Callback callback)
{
	mCallback = std::move(callback);
}

void Button::setText(const std::string& text)
{
	mText.setString(text);
	centreOrigin(mText);
}

void Button::setSize(sf::Vector2f size)
{
	mShape.setSize(size);
	sf::FloatRect bounds = mShape.getLocalBounds();
	mText.setPosition(bounds.width / 2.f, bounds.height / 2.f - 5);
}

void Button::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::MouseMoved)
	{
		mouseMoved();
	}
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		mousePressed();
	}
	if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
	{
		mouseReleased();
	}
}

void Button::update()
{	
	static float factor = 0.f;

	if (mouseOver())
	{
		sf::Uint8 rgb = static_cast<sf::Uint8>(std::abs(std::sin(factor)) * 255);
		mText.setFillColor(sf::Color(rgb, rgb, rgb));
		factor += 0.05f;
	}
	else
	{
		mText.setFillColor(sf::Color::Black);
	}
}

bool Button::mouseOver()
{
	return getTransform().transformRect(mShape.getLocalBounds()).contains(getMousePosition(window));
}

void Button::mouseMoved()
{
	if (mouseOver())
	{
		isPressed ? changeState(Pressed) : changeState(Hover);
	}
	else
	{
		changeState(Normal);
		isPressed = false;
	}
}

void Button::mousePressed()
{
	if (mouseOver())
	{
		changeState(Pressed);
		isPressed = true;

		mSounds.play(SoundEffect::Button);
	}
}

void Button::mouseReleased()
{
	if (mouseOver() && isPressed)
	{
		changeState(Hover);
		isPressed = false;
		mCallback();
	}
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mShape, states);
	target.draw(mText, states);
}

void Button::changeState(Type buttonType)
{
	sf::Color color;

	switch (buttonType)
	{

	case Pressed: color = sf::Color(255, 177, 0);  break;

	case Hover: color = sf::Color(181, 230, 29); break;

	case Normal: color = sf::Color(31, 177, 76);  break;

	}

	mShape.setFillColor(color);
}

}