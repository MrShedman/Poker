#pragma once

#include <Component.hpp>
#include <ResourceIdentifiers.hpp>
#include <State.hpp>
#include <ResourceHolder.hpp>
#include <SoundPlayer.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <vector>
#include <string>
#include <memory>
#include <functional>

namespace GUI
{
	class Toggle : public Component
	{
	public:
		typedef std::shared_ptr<Toggle>		Ptr;
		typedef std::function<void(bool)>	Callback;

		enum Type
		{
			Normal,
			Hover,
			Pressed,
			ButtonCount
		};


	public:
		Toggle(State::Context context);

		void					setCallback(Callback callback);
		void					setText(const std::string& offText, const std::string& onText);
		void					setSize(sf::Vector2f size);
		void					setState(bool flag);
		virtual void			handleEvent(const sf::Event& event);
		virtual void			update();

	private:

		bool mouseOver();
		void mouseMoved();
		void mousePressed();
		void mouseReleased();

		virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void					changeState(Type buttonType);
		void					updateText();

	private:
		bool isSelected;

		std::string				offText;
		std::string				onText;
		Callback				mCallback;
		sf::RectangleShape		mShape;
		sf::Text				mText;
		SoundPlayer				&mSounds;
		sf::RenderWindow		&window;
	};

}