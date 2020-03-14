using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Map
{
	public enum BLOCKTYPPE
	{
		NONE = 0,	// 해당 타입은 출력을 하지 않음.
		BLOCK,		// 블럭
		TOP,	// 팽이
	}

	public enum BLOCKCOLOR
	{
		NONE = 0,
		RED,
		GREEN,
		BLUE,
		YELLOW,
		PURPLE
	}
}