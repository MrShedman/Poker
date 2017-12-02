#pragma once

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <memory>


namespace sf
{
	class Event;
}

namespace GUI
{

class Component : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
{
    public:
        typedef std::shared_ptr<Component> Ptr;


	public:
							Component();
        virtual				~Component();

        virtual bool		isActive() const;

        virtual void		handleEvent(const sf::Event& event) = 0;
		virtual void		update() = 0;

    private:
        bool				mIsActive;
};

}