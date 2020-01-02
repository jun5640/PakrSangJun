using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class CharManager : MonoBehaviour
{
    public Animator ani;
    Battle.Animation state = Battle.Animation.Idle;
    Battle.Animation prevstate = Battle.Animation.Idle;


    private void Update()
    {
        
    }

    public void StateUpdate(Battle.Animation state)
    {
        this.state = state;
        if (this.state != prevstate)
        {
            AnimatorUpdate(state);
            prevstate = this.state;
        }
        
    }

    void AnimatorUpdate(Battle.Animation state)
    {
        Array ary = System.Enum.GetValues(typeof(Battle.Animation));

        for (int i = 0; i < ary.Length; i++)
        {
            int enumVal = (int)ary.GetValue(i);
            string enumName = System.Enum.GetName(typeof(Battle.Animation), enumVal);

            if((int)state == i)
            {
                ani.SetBool(enumName, true);
            }
            else
            {
                ani.SetBool(enumName, false);
            }
        }
    }
}
