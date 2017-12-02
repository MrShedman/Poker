#pragma once

#include <Component.hpp>
#include <ResourceIdentifiers.hpp>
#include <State.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <Utility.h>

#include <vector>
#include <string>
#include <memory>
#include <functional>

namespace GUI
{

template<class T>
class Slider : public Component
{
public:
	typedef std::shared_ptr<Slider>			Ptr;
	typedef std::function<void(int)>		Callback;
	typedef std::function<std::string(T)>	DisplayFunction;

	enum Type
	{
		Normal,
		Hover,
		Pressed,
		ButtonCount
	};

public:

	Slider(State::Context context);

	void					setCallback(Callback callback);
	void					setText(const std::string& text);
	void					setSize(sf::Vector2f size);

	void					setDisplayFunction(DisplayFunction func);
	void					setCurrentValue(T value);
	void					setPossibleValues(std::vector<T> values);

	virtual void			handleEvent(const sf::Event& event);
	virtual void			update();

private:

	bool					mouseOver(sf::FloatRect rect);
	void					mouseMoved();
	void					mousePressed();
	void					mouseReleased();

	void					changeState(Type buttonType);
	void					updateRange();

	int						getIndex();
	float					getOffset();
	std::string				getDisplay();

	virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:

	bool					isPressed;
	float					minRange;
	float					maxRange;
	float					offset;

private:

	T						mCurrent;
	std::vector<T>			possibleValues;
	DisplayFunction			mDisplayFunction;
	Callback				mCallback;

private:

	sf::RectangleShape		mOutline;
	sf::RectangleShape		mShape;
	sf::Text				mText;
	sf::RenderWindow		&window;
};

}

#include <Slider.inl>