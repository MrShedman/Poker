#pragma once

#include <State.hpp>
#include <Container.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class MenuState : public State
{
	public:
								MenuState(StateStack& stack, Context context);

		virtual void			draw();
		virtual bool			update(sf::Time dt);
		virtual bool			handleEvent(const sf::Event& event);

	private:

		void initializeButtons();

		sf::Sprite				mBackgroundSprite;
		GUI::Container			mGUIContainer;
};