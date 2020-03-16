using System.Collections;
using System.Collections.Generic;
using UnityEngine;


[ExecuteInEditMode]
public class BlockHive : MonoBehaviour
{
	public SpriteRenderer m_renderer;
	//public GameObject PoolObject;
	public BlockObject blockobj;

	Sprite top = null;
	Sprite circle = null;

	readonly string img_top_path = "Image/top";
	readonly string img_circle_path = "Image/Circle";

	public void InitData(bool poolreturn = true)
	{
		if(poolreturn) blockobj.gameObject.transform.parent = Game.instance.gameObject.transform;
		m_renderer = null;
		blockobj = null;
	}

	public void SetBlockObject(GameObject go,bool setZeroPos = true)
	{
		if(go == null)
		{
			Debug.LogError("go null");
			return;
		}
		m_renderer = go.GetComponent<SpriteRenderer>();
		blockobj = go.GetComponent<BlockObject>();

		go.transform.parent = this.gameObject.transform;
		if (setZeroPos) go.transform.localPosition = Vector3.zero;
	}

	public void SetBlockType(Map.BLOCKTYPPE type)
	{
		blockobj.m_blockInfo.type = type;
		//PoolObject.GetComponent<BlockEvent>().type = type;

		if (type == Map.BLOCKTYPPE.TOP)
		{
			if(top == null)
			{
				top = Resources.Load<Sprite>(img_top_path);
			}
			m_renderer.sprite = top;
			blockobj.m_blockInfo.DieCount = 2;
			SetBlockColor(Map.BLOCKCOLOR.NONE, false);
		}
		else if(type == Map.BLOCKTYPPE.BLOCK)
		{
			if (circle == null)
			{
				circle = Resources.Load<Sprite>(img_circle_path);
			}
			m_renderer.sprite = circle;
		}
		UpdateBlock();
	}

	public Map.BLOCK GetBlockInfo()
	{
		return blockobj.m_blockInfo;
	}


	public void SetBlockColor(Map.BLOCKCOLOR color, bool IsBlock = true)
	{
		if(IsBlock) blockobj.m_blockInfo.color = color;

		switch(color)
		{
			case Map.BLOCKCOLOR.BLUE:
				m_renderer.color = Color.blue;
				break;
			case Map.BLOCKCOLOR.GREEN:
				m_renderer.color = Color.green;
				break;
			case Map.BLOCKCOLOR.PURPLE:
				m_renderer.color = Color.magenta;
				break;
			case Map.BLOCKCOLOR.RED:
				m_renderer.color = Color.red;
				break;
			case Map.BLOCKCOLOR.YELLOW:
				m_renderer.color = Color.yellow;
				break;
			case Map.BLOCKCOLOR.NONE:
				m_renderer.color = Color.white;
				break;
		}

		//PoolObject.GetComponent<BlockEvent>().color = m_blockInfo.color;
	}

	void UpdateBlock()
	{
		if(blockobj.m_blockInfo.type == Map.BLOCKTYPPE.NONE)
		{
			this.gameObject.SetActive(false);
		}
		else
		{
			this.gameObject.SetActive(true);
		}
	}

}
