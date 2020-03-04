using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Map
{

	public class MapTile
	{
		public int Id;					// 타일넘버
		public string path;				// 경로
		public bool IsTrigger;			// 캐릭터와 충돌 여부.
	}

}

public class StageInfo
{
	public int Id;
	public string StageNumber;

}