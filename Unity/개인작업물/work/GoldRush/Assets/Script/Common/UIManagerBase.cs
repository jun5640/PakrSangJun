using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UIManagerBase : MonoBehaviour
{
	static UIManagerBase _instance = null;
	public static UIManagerBase instance
	{
		get { return _instance; }
	}

	public virtual void Setup()
	{
		_instance = this;
	}


	private void OnEnable()
	{
		_instance = this;
	}
}
