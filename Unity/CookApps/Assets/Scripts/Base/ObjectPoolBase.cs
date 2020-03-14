using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ObjectPoolBase<T> where T : class
{
	Dictionary<T, bool> Pools = new Dictionary<T, bool>();	// value 가 true 일 경우에는 대여중.
	object o;

	public void AddObjectNuse(T add)	// 생성과 동시에 사용할 경우.
	{
		Pools.Add(add, true);
	}

	public void AddObject(T add)		// 풀만 생성할 경우.
	{
		Pools.Add(add, false);
	}

	public T GetPool()
	{
		lock (o)
		{
			foreach (var poolObject in Pools)
			{
				if (poolObject.Value == false)
				{
					Pools[poolObject.Key] = true;
					return poolObject.Key;
				}
			}
		}

		return null;
	}

	public void ReturnPool(T returnObject)
	{
		Pools[returnObject] = false;
	}
}
