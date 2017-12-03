#pragma once

#include <State.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <deck.h>
#include <Player.h>
#include <Panel.h>
#include <PlayerCodex.h>
#include <ViewableWorld.h>

#include <CommandQueue.hpp>
#include <Command.hpp>
#include <SceneNode.hpp>

#include <CircularContainer.h>

class Controller;

class GameState : public State, public ViewableWorld
{
	public:
							GameState(StateStack& stack, Context context);

		virtual void		draw();
		virtual bool		update(sf::Time dt);
		virtual bool		handleEvent(const sf::Event& event);

		void fold();
		void flip();
		void dealCard();
		void completeRound();

		inline const PlayerPanel& getPanel(int position) const
		{
			return *panels[position];
		}

		inline const player& getPlayer(std::string name) const
		{
			return codex->getPlayer(name);
		}

		inline const Deck& getDeck() const
		{
			return *deck;
		}

		inline sf::Time getTimeElapsed() const
		{
			return timeElapsed;
		}

	private:

		GUI::Container mGUIContainer;

		CircularContainer<Controller*> controllers;
		CircularContainer<PlayerPanel*> panels;

		PlayerCodex* codex;

		Deck* deck;
		
		SceneNode mSceneGraph;
		CommandQueue mCommandQueue;

		const sf::Time decisionTime = sf::seconds(3.f);
		sf::Time timeElapsed;
};