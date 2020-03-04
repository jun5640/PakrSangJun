using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Battle
{
    public enum Animation
    {
		IsIdle = 0,
		IsMoveUp,
		IsMoveDown,
		IsMoveLeft,
		IsMoveRight,
    }
}

namespace Map
{
    public enum TileState
    {
        None = 0,
        Wall,
        ScrectWall,
        InteractiveWalll,
    }

    public enum TileMoveState
    {
        None = 0,
        MoveAble,
    }

      
}