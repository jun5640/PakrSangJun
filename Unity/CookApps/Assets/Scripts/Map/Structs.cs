using System.Collections;
using System.Collections.Generic;
using UnityEngine;


namespace Map
{
	public class BLOCK
	{
		public BLOCKTYPPE type = BLOCKTYPPE.BLOCK;        // 블럭종류 (장해물과 블럭 구분)
		public BLOCKCOLOR color;        // 블럭색깔 (장해물이 아닐경우)

		public int DieCount = 0;		// 장해물의 목숨.
	}

	public class SAVEBLOCKDATA
	{
		public int row;
		public int col;

		public BLOCK[] blocks;
	}
}
