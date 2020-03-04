using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class StageInfoCell : MonoBehaviour
{
	public Text StageText;

	private int Id;

	public void SetStageText(string text,int idValue)
	{
		StageText.text = text;
		Id = idValue;
	}

	public void OnClick()
	{
		if (DataManager.instance.StageEnterCheck(Id))
		{
			DataManager.instance.stage = StageText.text;
			DataManager.instance.stageId = Id.ToString();
			SceneManager.LoadScene("Game");
		}
	}
}
