using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.IO;

public class UIMenu : UIManagerBase
{
	static readonly string stageinfopath = "Map/Stage/StageInfo";
	static readonly string stageinfoprefabpath = "Datas/Prefab/UIPrefab/Stage";

	StageInfo[] stageinfos;

	public GameObject StageInfoParent;

	static UIMenu _instance = null;
	public static new UIMenu instance
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
		stageinfos = JsonConvert.DeserializeObject<StageInfo[]>(Resources.Load<TextAsset>(stageinfopath).text);

		for(int i = 0; i < stageinfos.Length; i++)
		{
			GameObject go = Instantiate<GameObject>(Resources.Load(stageinfoprefabpath) as GameObject);
			StageInfoCell cell = go.GetComponentInChildren<StageInfoCell>();
			cell.SetStageText(stageinfos[i].StageNumber,stageinfos[i].Id);

			go.transform.parent = StageInfoParent.transform;
			go.transform.localPosition = Vector3.zero;
		}
	}
}
