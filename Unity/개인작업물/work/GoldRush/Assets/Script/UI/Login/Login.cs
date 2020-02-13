using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Login : SingletonBase<Login>
{

	public Text Text_Result;
	string user_id;
	string user_pass;


	public void InputUserId(string text)
	{
		user_id = text;
	}

	public void InputUserPass(string text)
	{
		user_pass = text;
	}

	public void Btn_Login()
	{
		PostNetWork.PostNetWork.instance.RequetPostFunc(new PostNetWork.ActionLogin() { userId = user_id, userPassWord = user_pass });
	}

	public void Btn_Reg()
	{
		PostNetWork.PostNetWork.instance.RequetPostFunc(new PostNetWork.ActionRegister() { userId = user_id, userPassWord = user_pass });
	}
}
