using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

namespace PostNetWork
{
	public class ActionLogin : BaseAction
	{
		public string userId = "hello";
		public string userPassWord = "hello";

		public override void Excute()
		{

		}
	}

	public class ActionLoginResult : BaseActionResult
	{
		public string data;
		public string result;

		public override void Excute()
		{
			Debug.Log(data);
			Debug.Log("ActionloginResult");

			if (string.IsNullOrEmpty(data))
			{
				Login.instance.Text_Result.text = "Failed";	
			}
			else
			{
				DataManager.instance.SetUserData(data);
				Login.instance.Text_Result.text = result;
				SceneManager.LoadScene("Menu");
			}
		}
	}

}
