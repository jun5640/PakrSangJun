using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Map;


[ExecuteInEditMode]
public class MapTileCell : MonoBehaviour
{
	public SpriteRenderer spriterender;
	public BoxCollider2D col2d;
	public int Id;



	private void OnEnable()
	{
		if(spriterender == null) spriterender = this.GetComponent<SpriteRenderer>();
		if(col2d == null)col2d = this.GetComponent<BoxCollider2D>();
	}

	public void CellUpdate(MapTile tile)
	{
		spriterender.sprite = Resources.Load<Sprite>(tile.path);
		col2d.isTrigger = tile.IsTrigger;
		Id = tile.Id;
	}
}
