using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

namespace PostNetWork
{
	public class ActionMapClear : BaseAction
	{
		public string userId = "";
		public string mapId = "";

		public override void Excute()
		{

		}
	}

	public class ActionMapClearResult : BaseActionResult
	{
		public string data;
		public string result;

		public override void Excute()
		{
			Debug.Log(data);
			Debug.Log("ActionMapClearResult");

			
			if (string.IsNullOrEmpty(data))
			{
				
			}
			else
			{
				if(result == "Success")
				DataManager.instance.SetUserData(data);
			}

			SceneManager.LoadScene("Menu");

		}
	}

}
