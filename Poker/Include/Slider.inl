
namespace GUI
{
	template<class T>
	Slider<T>::Slider(State::Context context)
		: mCallback()
		, mDisplayFunction()
		, mShape(sf::Vector2f(30, 70))
		, mOutline(sf::Vector2f(240, 70))
		, mText("", context.fonts->get(Fonts::Main), 35)
		, window(*context.window)
		, isPressed(false)
	{
		changeState(Normal);

		mOutline.setFillColor(sf::Color(150, 150, 150));
		mOutline.setOutlineThickness(-5.f);
		mOutline.setOutlineColor(sf::Color::Black);

		mShape.setOutlineThickness(-5.f);
		mShape.setOutlineColor(sf::Color::Black);

		mText.setFillColor(sf::Color::White);
		sf::FloatRect bounds = mOutline.getLocalBounds();
		mText.setPosition(bounds.width / 2.f, bounds.height / 2.f - 5);

		updateRange();
	}

	template<class T>
	void Slider<T>::setCallback(Callback callback)
	{
		mCallback = std::move(callback);
	}

	template<class T>
	void Slider<T>::setDisplayFunction(DisplayFunction func)
	{
		mDisplayFunction = std::move(func);
		setText(getDisplay());
	}

	template<class T>
	void Slider<T>::setPossibleValues(std::vector<T> values)
	{
		possibleValues = std::move(values);
	}

	template<class T>
	void Slider<T>::setCurrentValue(T value)
	{
		int size = static_cast<int>(possibleValues.size());

		for (int i = 0; i < size; ++i)
		{
			if (value == possibleValues[i])
			{
				float percent = static_cast<float>(i) / static_cast<float>((size - 1));

				float position = (maxRange - minRange) * percent + minRange;

				mShape.setPosition(position, mShape.getPosition().y);
			}
		}

		mCurrent = possibleValues[getIndex()];
	}

	template<class T>
	void Slider<T>::setText(const std::string& text)
	{
		mText.setString(text);
		centreOrigin(mText);
	}

	template<class T>
	void Slider<T>::updateRange()
	{
		float right = mOutline.getLocalBounds().left + mOutline.getLocalBounds().width;

		minRange = 0;
		maxRange = right - mShape.getSize().x;
	}

	template<class T>
	void Slider<T>::setSize(sf::Vector2f size)
	{
		mShape.setSize(sf::Vector2f(30, size.y));
		mOutline.setSize(size);
		sf::FloatRect bounds = mOutline.getLocalBounds();
		mText.setPosition(bounds.width / 2.f, bounds.height / 2.f - 5);

		updateRange();
	}

	template<class T>
	void Slider<T>::update()
	{

	}

	template<class T>
	int Slider<T>::getIndex()
	{
		float size = static_cast<float>(possibleValues.size() - 1);
		float percent = (mShape.getPosition().x - minRange) / (maxRange - minRange);

		float index = std::round(percent * size);
		
		clamp(index, 0.f, size);

		return static_cast<int>(index);
	}

	template<class T>
	std::string Slider<T>::getDisplay()
	{
		mCurrent = possibleValues[getIndex()];
		return mDisplayFunction(mCurrent);
	}

	template<class T>
	float Slider<T>::getOffset()
	{
		return getMousePosition(window).x - mShape.getPosition().x;
	}

	template<class T>
	void Slider<T>::handleEvent(const sf::Event& event)
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

	template<class T>
	bool Slider<T>::mouseOver(sf::FloatRect rect)
	{
		return getTransform().transformRect(rect).contains(getMousePosition(window));
	}

	template<class T>
	void Slider<T>::mouseMoved()
	{
		if (isPressed)
		{
			float newPos = getMousePosition(window).x - offset;
			float oldPos = newPos;

			clamp(newPos, minRange, maxRange);

			// if we are at edge calculate new offset
			if (oldPos != newPos)
			{
				offset = getOffset();
			}

			mShape.setPosition(newPos, mShape.getPosition().y);
			setText(getDisplay());
			mCallback(getIndex());
		}

		if (mouseOver(mShape.getGlobalBounds()))
		{
			isPressed ? changeState(Pressed) : changeState(Hover);
		}
		else
		{
			changeState(Normal);
			isPressed = false;
		}
	}

	template<class T>
	void Slider<T>::mousePressed()
	{
		if (mouseOver(mShape.getGlobalBounds()))
		{
			//find offset between first click and sliders top left corner
			offset = getOffset();

			changeState(Pressed);
			isPressed = true;
		}
		else if (mouseOver(mOutline.getGlobalBounds()))
		{
			float newPos = getMousePosition(window).x - getPosition().x - mShape.getSize().x / 2.f;

			clamp(newPos, minRange, maxRange);

			mShape.setPosition(newPos, mShape.getPosition().y);

			setText(getDisplay());

			mCallback(getIndex());

			offset = getOffset();

			changeState(Pressed);
			isPressed = true;
		}
	}

	template<class T>
	void Slider<T>::mouseReleased()
	{
		if (mouseOver(mShape.getGlobalBounds()) && isPressed)
		{
			changeState(Hover);
			isPressed = false;
		}
	}

	template<class T>
	void Slider<T>::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(mOutline, states);
		target.draw(mShape, states);
		target.draw(mText, states);
	}

	template<class T>
	void Slider<T>::changeState(Type buttonType)
	{
		sf::Color color;

		switch (buttonType)
		{

		case Pressed:	color = sf::Color(255, 177,  0); break;
		case Hover:		color = sf::Color(181, 230, 29); break;
		case Normal:	color = sf::Color( 31, 177, 76); break;

		}

		mShape.setFillColor(color);
	}

}