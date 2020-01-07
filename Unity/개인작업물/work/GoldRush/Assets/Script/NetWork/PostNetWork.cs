using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;
using System.Text;
using Newtonsoft.Json;

public class PostNetWork : SingletonBase<PostNetWork>
{
	string url = "http://localhost:15001";

	public void RequetPostFunc()
	{
		StartCoroutine(RequestPost());
	}

	class ActionLogin
	{
		public string Name = "hello";
		public string klass = "ActionLogin";
	}

	IEnumerator RequestPost()
	{
		ActionLogin action = new ActionLogin();
		
		var request = new UnityWebRequest(url, "POST");
		string bodyJsonString = JsonConvert.SerializeObject(action);

		byte[] bodyRaw = Encoding.UTF8.GetBytes(bodyJsonString);
		request.uploadHandler = (UploadHandler)new UploadHandlerRaw(bodyRaw);
		request.downloadHandler = (DownloadHandler)new DownloadHandlerBuffer();
		request.SetRequestHeader("Content-Type", "application/json");

		yield return request.SendWebRequest();

		Debug.Log("Status Code: " + request.responseCode);
	}

}
