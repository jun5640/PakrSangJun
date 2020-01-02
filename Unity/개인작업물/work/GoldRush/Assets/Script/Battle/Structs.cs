using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Map
{

    public class Map
    {
        public Stage[] stages;  // 구성 스테이지
    }

    public class Stage
    {
        public string name;
        public List<Tile> tiles = new List<Tile>();
    }

    public class Tile
    {

        public uint idx;

        public TileState m_state;
        public TileMoveState m_movestate;
        public Sprite m_sprite;

        public bool ImageUpdate()
        {

            //
            //저장 된 타일 정보를 보러 오는 곳 혹은 에디어테에서 갱신 하는 곳.
            //


            return true;
        }
    }
}