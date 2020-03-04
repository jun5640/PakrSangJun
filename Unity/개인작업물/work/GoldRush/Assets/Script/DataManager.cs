using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

public class DataManager : SingletonBase<DataManager>
{
	public string stage;
	public string stageId;

	public string userId;

	private UserData.UserData userData;

	public void SetUserData(string jsondata)
	{
		userData = JsonConvert.DeserializeObject<UserData.UserData>(jsondata);
	}

	public void SetMapData(string jsondata)
	{
		userData.clearmaps = JsonConvert.DeserializeObject<int[]>(jsondata);
	}


	public bool StageEnterCheck(int value)
	{
		if(value <= userData.clearmaps.Length+1)
		{
			return true;
		}

		return false;
	}

}
