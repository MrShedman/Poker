#include <State.hpp>
#include <StateStack.hpp>


State::Context::Context(sf::RenderWindow& window, TextureHolder& textures, ImageHolder &images, FontHolder& fonts, MusicPlayer& music, SoundPlayer& sounds)
: window(&window)
, textures(&textures)
, images(&images)
, fonts(&fonts)
, music(&music)
, sounds(&sounds)
{
}

State::State(StateStack& stack, Context context)
: mStack(&stack)
, mContext(context)
{
}

State::~State()
{
}

void State::requestStackPush(States::ID stateID)
{
	mStack->pushState(stateID);
}

void State::requestStackPop()
{
	mStack->popState();
}

void State::requestStateClear()
{
	mStack->clearStates();
}

State::Context State::getContext() const
{
	return mContext;
}