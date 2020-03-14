using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BlockObject : MonoBehaviour
{
	public Map.BLOCK m_blockInfo = new Map.BLOCK();

	

	private void OnMouseDown()
	{
		Game.instance.SelectBlock(this.gameObject, m_blockInfo.type);
	}

	private void OnMouseUp()
	{
		Game.instance.UnSelectBlock();
	}

	private void OnMouseOver()
	{
		Game.instance.MatchBlock(this.gameObject, m_blockInfo.type);
	}

}
