using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Battle
{
    public enum Animation
    {
        Idle = 0,
        //Down,
        Left,
        Right,
        //Up,
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