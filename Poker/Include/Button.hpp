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

class Button : public Component
{
    public:
        typedef std::shared_ptr<Button>		Ptr;
        typedef std::function<void()>		Callback;

		enum Type
		{
			Normal,
			Hover,
			Pressed,
			ButtonCount
		};

	public:
								Button(State::Context context);

        void					setCallback(Callback callback);
        void					setText(const std::string& text);
		void					setSize(sf::Vector2f size);

        virtual void			handleEvent(const sf::Event& event);
		virtual void			update();

    private:

		bool mouseOver();
		void mouseMoved();
		void mousePressed();
		void mouseReleased();

        virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void					changeState(Type buttonType);

    private:
		bool isPressed;

        Callback				mCallback;
		SoundPlayer				&mSounds;
        sf::RectangleShape		mShape;
		sf::Text				mText;
		sf::RenderWindow		&window;
};

}