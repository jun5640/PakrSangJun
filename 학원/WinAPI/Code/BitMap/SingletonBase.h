#pragma once

template <typename T>
class SingletonBase
{
protected:
	static T* _Instance;

	SingletonBase() {};
	SingletonBase(const SingletonBase&) {};
	~SingletonBase() {} ;

public:

	void Release()
	{
		delete _Instance;
	}

	static T* Instance()
	{
		if (_Instance == nullptr)
		{
			_Instance = new T;
		}
		return _Instance;
	}
};

