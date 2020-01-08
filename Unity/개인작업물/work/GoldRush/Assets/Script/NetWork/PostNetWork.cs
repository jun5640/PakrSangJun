using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Text;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using UnityEngine.Networking;


namespace PostNetWork
{
	public class PostNetWork : SingletonBase<PostNetWork>
	{
		string url = "http://localhost:15001";

		public void RequetPostFunc(BaseAction @action)
		{
			StartCoroutine(RequestPost(@action));
		}

		IEnumerator RequestPost(BaseAction @action)
		{
			@action.Excute();

			var request = new UnityWebRequest(url, "POST");
			string bodyJsonString = JsonConvert.SerializeObject(@action);

			byte[] bodyRaw = Encoding.UTF8.GetBytes(bodyJsonString);
			request.uploadHandler = (UploadHandler)new UploadHandlerRaw(bodyRaw);
			request.downloadHandler = (DownloadHandler)new DownloadHandlerBuffer();
			request.SetRequestHeader("Content-Type", "application/json");

			yield return request.SendWebRequest();

			Debug.Log("Status Code: " + request.responseCode);
		}

	}
}
