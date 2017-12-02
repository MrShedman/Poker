#include <Toggle.h>
#include <iostream>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <Utility.h>

namespace GUI
{

Toggle::Toggle(State::Context context)
	: mCallback()
	, mShape(sf::Vector2f(240, 70))
	, mText("", context.fonts->get(Fonts::Main), 35)
	, window(*context.window)
	, mSounds(*context.sounds)
	, isSelected(false)
{
	changeState(Normal);
	mShape.setOutlineThickness(-5.f);
	mShape.setOutlineColor(sf::Color::Black);

	sf::FloatRect bounds = mShape.getLocalBounds();
	mText.setPosition(bounds.width / 2.f, bounds.height / 2.f - 5);
	mText.setFillColor(sf::Color::Black);
}

void Toggle::setCallback(Callback callback)
{
	mCallback = std::move(callback);
}

void Toggle::setText(const std::string& offText, const std::string& onText)
{
	this->offText = offText;
	this->onText = onText;

	updateText();
}

void Toggle::updateText()
{
	std::string text = isSelected ? onText : offText;
	mText.setString(text);
	centreOrigin(mText);
}

void Toggle::setSize(sf::Vector2f size)
{
	mShape.setSize(size);
	sf::FloatRect bounds = mShape.getLocalBounds();
	mText.setPosition(bounds.width / 2.f, bounds.height / 2.f - 5);
}
void Toggle::setState(bool flag)
{
	isSelected = flag;
	updateText();
	isSelected ? changeState(Pressed) : changeState(Normal);
}

void Toggle::handleEvent(const sf::Event& event)
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

void Toggle::update()
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

bool Toggle::mouseOver()
{
	return getTransform().transformRect(mShape.getLocalBounds()).contains(getMousePosition(window));
}

void Toggle::mouseMoved()
{
	if (mouseOver())
	{
		isSelected ? changeState(Pressed) : changeState(Hover);
	}
	else
	{
		isSelected ? changeState(Pressed) : changeState(Normal);
	}
}

void Toggle::mousePressed()
{
	if (mouseOver())
	{
		isSelected = !isSelected;
		isSelected ? changeState(Pressed) : changeState(Hover);
	
		updateText();
			
		mSounds.play(SoundEffect::Button);
	}
}

void Toggle::mouseReleased()
{
	if (mouseOver())
	{
		mCallback(isSelected);
	}
}

void Toggle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mShape, states);
	target.draw(mText, states);
}

void Toggle::changeState(Type buttonType)
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