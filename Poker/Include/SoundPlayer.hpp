#pragma once

#include <ResourceHolder.hpp>
#include <ResourceIdentifiers.hpp>

#include <SFML/System/Vector2.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

#include <list>

class SoundPlayer : private sf::NonCopyable
{
	public:
									SoundPlayer();

		void						play(SoundEffect::ID effect);

		void						removeStoppedSounds();

		void						setVolume(float volume);
		float						getVolume() const;


	private:
		SoundBufferHolder			mSoundBuffers;
		std::list<sf::Sound>		mSounds;
		float						mVolume;
};