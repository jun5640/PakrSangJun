using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class UIGame : UIManagerBase
{
	public Text Goal;

	public GameObject Result;

	static UIGame _instance = null;
	public static new UIGame instance
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

	public void SetGoal(int value)
	{
		string msg = string.Format("Goal:{0}", value);
		Goal.text = msg;
		if (value == 0) Result.SetActive(true);
	}

	public void BtnRetry()
	{
		SceneManager.LoadScene("Game");
	}

	public void BtnExit()
	{
		SceneManager.LoadScene("Menu");
	}

}
