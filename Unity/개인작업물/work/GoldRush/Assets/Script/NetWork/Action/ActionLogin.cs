using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace PostNetWork
{
	public class ActionLogin : BaseAction
	{
		public string Name = "hello";

		public override void Excute()
		{

		}
	}

	public class ActionLoginResult : BaseActionResult
	{
		public string data;

		public override void Excute()
		{
			Debug.Log(data);
			Debug.Log("ActionloginResult");
		}
	}

}
