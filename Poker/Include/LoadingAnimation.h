#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class loadingShape : public sf::Drawable, public sf::Transformable
{
public:
	loadingShape()
		:
		pi(3.14159265359f),
		stopped(true),
		direction(true),
		pc(0)
	{
		shape.setPointCount(2);
			
		shape.setFillColor(sf::Color(0, 255, 0));
	}

	loadingShape(float x, float y, float radius, sf::Time time)
		:
	x(x),
	y(y),
	radius(radius),
	time(time),
	pi(static_cast<float>(3.14159265359)),
	stopped(true),
	direction(true)
	{		
		init();
	}

	const loadingShape& operator = (const loadingShape& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		radius = rhs.radius;
		direction = rhs.direction;
		time = rhs.time;

		init();
		
		return *this;
	}

	void reset()
	{
		init();
	}

	void start()
	{
		reset();
		clock.restart();
		stopped = false;
	}

	void setClockWise()
	{
		direction = true;	
	}

	void setAntiClockWise()
	{
		direction = false;
	}

	float smoothstep(float fx)
	{
		return fx * fx * fx * (fx * (fx * 6 - 15) + 10);
	}

	void update()
	{
		if (!stopped)
		{
			factor = clock.getElapsedTime().asSeconds() / time.asSeconds();
			
			if (factor > 1.f)
			{
				factor = 1.f;
				stopped = true;
			}
			else if (factor > 0.7f)
			{
				shape.setFillColor(sf::Color(255,  static_cast<sf::Uint8>(255 - ((factor - 0.7f) * 850.f)), 0));
			}
			else if (factor > 0.4f)
			{
				shape.setFillColor(sf::Color(static_cast<sf::Uint8>(850.f * (factor - 0.4f)), 255, 0));
			}

			factor *= 2 * (direction ? pi : -pi);

			shape.setPointCount(pc + 1);

			float dx = x + std::sin(factor) * radius;
			float dy = y - std::cos(factor) * radius;

			shape.setPoint(pc++, sf::Vector2f(dx, dy));
		}
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(shape, states);
	}

private:

	int pc;

	float x;
	float y;

	float radius;
	float factor;

	const float pi;

	bool direction;
	bool stopped;

	void init()
	{
		pc = 0;

		stopped = true;

		shape.setPointCount(2);
		shape.setPoint(pc++, sf::Vector2f(static_cast<float>(x), static_cast<float>(y)));
		shape.setPoint(pc++, sf::Vector2f(static_cast<float>(x), static_cast<float>(y - radius)));

		shape.setFillColor(sf::Color(0, 255, 0));
	}

	sf::Clock clock;
	sf::Time time;

	sf::ConvexShape shape;
};