using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Newtonsoft.Json;
using Newtonsoft.Json.Converters;
using Newtonsoft.Json.Linq;
using Map;
using UnityEditor;

[ExecuteInEditMode]
public class MapToolScript : MonoBehaviour
{
	public Map.MapTile[] TileInfos;
	public List<MapTileCell> Maps;

	public int index;
	private Camera mainCamera; // 메인 카메라

	[ContextMenu("LoadTileInfo")]
	public void LoadTileinfo()
	{
		if (Maps != null)
		{
			Maps.Clear();
		}
		string text = Resources.Load<TextAsset>("Map/Json/TileInfo").text;
		TileInfos = JsonConvert.DeserializeObject<Map.MapTile[]>(text);
		mainCamera = GameObject.Find("MainCamera(Clone)").GetComponent<Camera>();
		MapTileCell[] cell = this.GetComponentsInChildren<MapTileCell>();
		Maps = new List<MapTileCell>(cell);
	}

	public void OnEnable()
	{
		if(Application.isEditor)
		{
			LoadTileinfo();
		}
	}

	public void TileLoad(int[] index)
	{
		for (int i = 0; i < index.Length; i++)
		{
			Maps[i].CellUpdate(GetTileInfo(index[i] - 1));
		}

	}

	public MapTile GetTileInfo(int index)
	{
		if(index < 0 && index >= TileInfos.Length) return null;
		return TileInfos[index];
	}


}
