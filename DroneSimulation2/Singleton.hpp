#pragma once


template <typename T>
class Singleton
{
private:
	static T instance;
public:
	static T& get_instance()
	{
		return instance;
	}
};

#define INSTANCE_INITIALIZE(T) T Singleton<T>::instance;