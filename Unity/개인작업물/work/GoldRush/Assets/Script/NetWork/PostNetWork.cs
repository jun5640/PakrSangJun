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
		//string url = "http://localhost:15001";
		string url = "http://13.125.231.219:56365";

		JsonToActionConverter m_JsonToActionConverter = new JsonToActionConverter();

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

			string text = request.downloadHandler.text.Trim();

			BaseActionResult result = JsonConvert.DeserializeObject<BaseAction>(text, m_JsonToActionConverter) as BaseActionResult;
			result.Excute();
			if (result.action != null) result.action();

			Debug.Log(text);
		}

	}
}
