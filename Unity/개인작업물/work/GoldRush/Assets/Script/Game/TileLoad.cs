using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Newtonsoft.Json;
using System.IO;

public class TileLoad : MonoBehaviour
{
	public List<MapTileCell> Maps;
	public Map.MapTile[] TileInfos;
	string path = "Map/Stage/{0}";

	private void Awake()
	{
		InitTile();
	}

	private void Start()
	{
		LoadMap();
	}

	public void InitTile()
	{
		string text = Resources.Load<TextAsset>("Map/Json/TileInfo").text;
		TileInfos = JsonConvert.DeserializeObject<Map.MapTile[]>(text);
		MapTileCell[] cell = this.GetComponentsInChildren<MapTileCell>();
		Maps = new List<MapTileCell>(cell);
	}

	void LoadMap()
	{
		int[] indexs;
		indexs = JsonConvert.DeserializeObject<int[]>(Resources.Load<TextAsset>(string.Format(path,DataManager.instance.stage)).text);
		LoadMap(indexs);
	}

	void LoadMap(int[] index)
	{
		for (int i = 0; i < index.Length; i++)
		{
			Maps[i].CellUpdate(GetTileInfo(index[i] - 1));
		}
	}

	public Map.MapTile GetTileInfo(int index)
	{
		if (index < 0 && index >= TileInfos.Length) return null;
		return TileInfos[index];
	}
}
