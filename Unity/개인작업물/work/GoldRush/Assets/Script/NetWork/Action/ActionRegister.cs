using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace PostNetWork
{
	public class ActionRegister : BaseAction
	{
		public string userId = "hello";
		public string userPassWord = "hello";

		public override void Excute()
		{

		}
	}

	public class ActionRegisterResult : BaseActionResult
	{
		public string data;

		public override void Excute()
		{
			Debug.Log(data);
			Debug.Log("ActionRegisterResult");
		}
	}

}
