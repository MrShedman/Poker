#pragma once

#include <vector>

template <typename T>
class CircularContainer
{
public:

	CircularContainer()
		:
		index(0),
		container()
	{

	}

	void push_back(const T &object)
	{
		container.push_back(object);
	}

	void push_back(T&& object)
	{
		container.push_back(std::move(object));
	}

	T& operator()()
	{
		return container[index];
	}

	T& operator[](int idx)
	{
		return container[idx];
	}

	const T& operator[](int idx) const
	{
		return container[idx];
	}

	void goForward()
	{
		increment(index);
	}

	void goBack()
	{
		decrement(index);
	}

	T& getCurrent()
	{
		return container[index];
	}

	T& getNext()
	{
		int tempIndex = index;

		increment(tempIndex);

		return container[tempIndex];
	}

	T& getPrevious()
	{
		int tempIndex = index;

		decrement(tempIndex);

		return container[tempIndex];
	}

private:

	void increment(int &idx)
	{
		++idx;

		if (idx >= static_cast<int>(container.size()))
		{
			idx = 0;
		}
	}

	void decrement(int &idx)
	{
		--idx;

		if (idx < 0)
		{
			idx = static_cast<int>(container.size()) - 1;
		}
	}

	int index;
	std::vector<T> container;
};