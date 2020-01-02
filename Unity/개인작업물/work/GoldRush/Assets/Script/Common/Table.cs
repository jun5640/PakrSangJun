using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Table
{
    public class CREATURE
    {
        public uint Id;
        public float movespeed; // 이동 속도
        public float power;     // 공격력  
        public int hp;          // 체력
        public float attackspeed;   // 공격 속도
    }

    public class USERCREATURE
    {
        public uint Id;
        public float movespeed; // 이동 속도
        public float power;     // 공격력  
        public int hp;          // 체력
        public float attackspeed;   // 공격 속도
    }
}
