using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class GameClearCheck : MonoBehaviour
{
	private void OnTriggerEnter2D(Collider2D collision)
	{
		if(collision.CompareTag("Player"))
		{
			PostNetWork.PostNetWork.instance.RequetPostFunc(new PostNetWork.ActionMapClear() { userId = DataManager.instance.userId, mapId = DataManager.instance.stageId });
			
		}
	}
}
