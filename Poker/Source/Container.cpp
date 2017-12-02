#include <Container.hpp>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace GUI
{

Container::Container()
: mChildren()
{
}

void Container::pack(Component::Ptr component)
{
	mChildren.push_back(component);
}

void Container::pack(std::initializer_list<Component::Ptr> components)
{
	for (auto &c : components)
	{
		mChildren.push_back(c);
	}
}

void Container::clear()
{
	mChildren.clear();
}

void Container::handleEvent(const sf::Event& event)
{
	for (auto &child : mChildren)
	{
		child->handleEvent(event);
	}
}

void Container::update()
{
	for (auto &child : mChildren)
	{
		child->update();
	}
}

void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

	for (auto &child : mChildren)
	{
		target.draw(*child, states);
	}
}

}