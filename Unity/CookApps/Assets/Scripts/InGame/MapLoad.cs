using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Newtonsoft.Json;

[ExecuteInEditMode]
public class MapLoad : MonoBehaviour
{
	const float BLOCKWIDTH = 0.86f;
	const float BLOCKHEIGHT = 0.74f;

	readonly string BlockHivePath = "Prefab/BLOCK_HIVE";
	readonly string BlockObjPath = "Prefab/BLOCK";
	readonly string MapBasePath = "Map/{0}";

	public GameObject[] blocks;

	int row;
	int col;


	public int GetBlockIndex(GameObject go)
	{
		for (int i = 0; i < blocks.Length; i++)
		{
			if (blocks[i] == null || blocks[i].GetComponent<BlockHive>().blockobj == null) continue;


			if(blocks[i].GetComponent<BlockHive>().blockobj.gameObject == go)
			{
				return i;
			}
		}

		return -1;
	}

	public int GetHiveBlockIndex(GameObject go)
	{
		for (int i = 0; i < blocks.Length; i++)
		{
			if (blocks[i] == null) continue;


			if (blocks[i] == go)
			{
				return i;
			}
		}

		return -1;
	}


	public void SetBlock(string MapName)
	{
		string path = string.Format(MapBasePath, MapName);

		Map.SAVEBLOCKDATA data;
		data = JsonConvert.DeserializeObject<Map.SAVEBLOCKDATA>(Resources.Load<TextAsset>(path).text);

		LoadBlock(data,true);
	}

	public void LoadBlock(Map.SAVEBLOCKDATA SaveMapdata,bool InGameLoad = false)
	{
		row = SaveMapdata.row;
		col = SaveMapdata.col;

		blocks = new GameObject[row * col];

		Transform go_parent = this.gameObject.transform;

		float xposInterval = Mathf.Sqrt(BLOCKWIDTH / 2);
		float startxpos = (row * xposInterval) / 2 * -1 + (xposInterval / 2);
		float startypos = (row * BLOCKHEIGHT) / 2;
		float halfheight = BLOCKHEIGHT / 2;

		for (int r = 0; r < row; r++)
		{
			for (int c = 0; c < col; c++)
			{
				if(InGameLoad)
				{
					if(SaveMapdata.blocks[(r * row) + (c)].type == Map.BLOCKTYPPE.NONE)
					{
						blocks[(r * row) + (c)] = null;
						continue;
					}
				}
				GameObject HiveGo = Instantiate<GameObject>(Resources.Load<GameObject>(BlockHivePath));
				HiveGo.transform.parent = go_parent;
				HiveGo.transform.localPosition = Vector3.zero;
				float xpos = startxpos + (xposInterval * r);
				HiveGo.name = ((r * row) + c).ToString();
				int yInterval = r % 2;

				float ypos = startypos - (BLOCKHEIGHT * c) - (halfheight * yInterval);
				HiveGo.transform.localPosition = new Vector3(xpos, ypos, 0);

				blocks[(r * row) + (c)] = HiveGo;

				GameObject BlockGo = Instantiate<GameObject>(Resources.Load<GameObject>(BlockObjPath));

				BlockHive hive = HiveGo.GetComponent<BlockHive>();
				hive.SetBlockObject(BlockGo);
				hive.SetBlockColor(SaveMapdata.blocks[(r * row) + (c)].color);
				hive.SetBlockType(SaveMapdata.blocks[(r * row) + (c)].type);

				if(Game.instance != null) Game.instance.BlockPool.AddObjectNuse(BlockGo);


			}
		}
	}

	public void CreateBlock(int row, int col)
	{
		this.row = row;
		this.col = col;

		blocks = new GameObject[row* col];

		Transform go_parent = this.gameObject.transform;

		float xposInterval = Mathf.Sqrt(BLOCKWIDTH / 2);
		float startxpos = (row * xposInterval) / 2 * -1 + (xposInterval / 2);
		float startypos = (row * BLOCKHEIGHT) / 2;
		float halfheight = BLOCKHEIGHT / 2;

		for(int r = 0; r < row; r++)
		{
			for(int c = 0; c < col; c++)
			{
				GameObject HiveGo = Instantiate<GameObject>(Resources.Load<GameObject>(BlockHivePath));
				HiveGo.transform.parent = go_parent;
				HiveGo.transform.localPosition = Vector3.zero;
				float xpos = startxpos + (xposInterval * r);
				HiveGo.name = ((r * row) + c).ToString();
				int yInterval = r % 2;

				float ypos = startypos - (BLOCKHEIGHT * c) - (halfheight * yInterval);
				HiveGo.transform.localPosition = new Vector3(xpos, ypos, 0);

				blocks[(r * row) + (c)] = HiveGo;

				GameObject BlockGo = Instantiate<GameObject>(Resources.Load<GameObject>(BlockObjPath));

				BlockHive hive = HiveGo.GetComponent<BlockHive>();
				hive.SetBlockObject(BlockGo);
				//hive.SetBlockColor(SaveMapdata.blocks[(r * row) + (c)].color);
				//hive.SetBlockType(SaveMapdata.blocks[(r * row) + (c)].type);

				blocks[(r * row) + (c)] = HiveGo;
			}
		}
	}

	public int GetRowCount()
	{
		return row;
	}

	public int GetColCount()
	{
		return col;
	}

	
}
