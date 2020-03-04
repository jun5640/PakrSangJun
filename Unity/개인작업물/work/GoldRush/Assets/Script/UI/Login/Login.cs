using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Login : UIManagerBase
{

	public Text Text_Result;
	string user_id;
	string user_pass;

	static Login _instance = null;
	public static new Login instance
	{
		get { return _instance; }
	}

	private void OnEnable()
	{
		_instance = this;
	}

	private void Awake()
	{
		this.Setup();
	}

	public override void Setup()
	{
		base.Setup();
	}

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
		DataManager.instance.userId = user_id;
		PostNetWork.PostNetWork.instance.RequetPostFunc(new PostNetWork.ActionLogin() { userId = user_id, userPassWord = user_pass });
	}

	public void Btn_Reg()
	{
		PostNetWork.PostNetWork.instance.RequetPostFunc(new PostNetWork.ActionRegister() { userId = user_id, userPassWord = user_pass });
	}
}
