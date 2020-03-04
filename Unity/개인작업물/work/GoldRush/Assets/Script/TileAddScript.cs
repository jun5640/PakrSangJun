using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[ExecuteInEditMode]

public class TileAddScript : MonoBehaviour
{
	public GameObject Origin;
	public GameObject parent;

	[ContextMenu("TileCreate")]
	public void CreateTile()
	{

		int x = -1;

		for(int i = 0; i < 15; i++)
		{
			GameObject go = Instantiate<GameObject>(Origin);
			go.transform.parent = parent.transform;
			go.transform.localPosition = new Vector3((float)(x + (0.16 * i)), 0, 0);
			//go.AddComponent<BoxCollider2D>();
			go.name = i.ToString();
		}
	}
}
