#pragma once

#include <map>
#include "CustomObject.h"

using namespace std;

template <typename T>
class ObjectPool
{
protected:

	map<typename T::Enemy*, bool> m_Objects;
	
public:
	
	ObjectPool() {};
	//ObjectPool(const ObjectPool&) {};
	~ObjectPool() 
	{
		for (auto it = m_Objects.begin(); it != m_Objects.end(); it++)
		{
			delete it->first;
		}
		
		m_Objects.clear();
	};


	void SetPool(int objectCount)
	{
		for (int i = 0; i < objectCount; i++)
		{
			typename T::Enemy* add = new typename T::Enemy();
			m_Objects.insert(make_pair(add, false));
		}
	}
	
	//
	// PoolGet
	//

	typename T::Enemy* Pooling()
	{
		for (auto it = m_Objects.begin(); it != m_Objects.end(); it++)
		{
			if (it->second == false)
			{
				it->second = true;
				return it->first;
			}
		}
	}

	//
	// PoolRetun
	//
	void ReturnObject(typename T::Enemy* object)
	{
		for (auto it = m_Objects.begin(); it != m_Objects.end(); it++)
		{
			if (it->first == object)
			{
				it->second = false;
			}
		}
	}
};

