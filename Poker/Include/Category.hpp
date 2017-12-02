#pragma once

// Entity/scene node category, used to dispatch commands
namespace Category
{
	enum Type
	{
		None				= 0,
		Deck				= 1 << 0,
		Player				= 1 << 1,
		//AlliedAircraft		= 1 << 2,
		//EnemyAircraft		= 1 << 3,
		//Pickup				= 1 << 4,
		//AlliedProjectile	= 1 << 5,
		//EnemyProjectile		= 1 << 6,
		//ParticleSystem		= 1 << 7,
		SoundEffect			= 1 << 8,
		AI					= 1 << 9,

		//Aircraft = PlayerAircraft | AlliedAircraft | EnemyAircraft,
		//Projectile = AlliedProjectile | EnemyProjectile,
	};
}