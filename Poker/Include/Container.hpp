#pragma once

#include <Component.hpp>
#include <vector>
#include <memory>
#include <State.hpp>


namespace GUI
{

class Container : public Component
{
    public:
        typedef std::shared_ptr<Container> Ptr;
            

	public:
		Container();

        void				pack(Component::Ptr component);

		void				pack(std::initializer_list<Component::Ptr> components);

		void				clear();

        virtual void		handleEvent(const sf::Event& event);
		virtual void		update();

    private:
        virtual void		draw(sf::RenderTarget& target, sf::RenderStates states) const;

  
    private:
        std::vector<Component::Ptr>		mChildren;
};

}