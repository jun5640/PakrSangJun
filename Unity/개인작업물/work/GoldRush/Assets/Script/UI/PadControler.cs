using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PadControler : MonoBehaviour
{
    public GameObject Avater;       // 패드와 연동되어 움직일 캐릭터

    Vector3 OriginPos;
    bool isOnPress = false;

    const float limitDist = 20f;
    float Speed = 0.01f;

    public UILabel view;

    public delegate void MoveCallBack(Battle.Animation state);
    public event MoveCallBack callback;


    //
    // 스크립트 정상 작동 확인용 코드.
    //

    public CharManager charmanager;



    public void Start()
    {
        //SQLiteManager.instance.Connect(SQLiteManager.instance.GetAssetPath("Table/Table.db"));

        //Table.CREATURE tbCreature = SQLiteManager.instance.GetValue<Table.CREATURE>(1);

        //Debug.Log(tbCreature.Hp);
        //Debug.Log(tbCreature.Ani[0]);
        //Debug.Log(tbCreature.Ani[1]);
        //Debug.Log(tbCreature.Ani[2]);
        if (charmanager != null)
        {
            callback += charmanager.StateUpdate;
        }
    }

    public void InitAvater(GameObject go)
    {
        Avater = go;
    }

    void OnPress(bool state)
    {
        if (state)
        {
            Debug.Log("BtnDown");
            OriginPos = this.transform.localPosition;
            isOnPress = state;

        }
        else
        {
            Debug.Log("BtnUp");

            this.transform.localPosition = OriginPos;
            isOnPress = state;
        }
    }

    private void Update()
    {
        if(isOnPress)
        {
            Vector3 Dirvec = this.transform.localPosition - OriginPos;

            if (Dirvec.magnitude > limitDist)
            {
                Dirvec = Dirvec.normalized;
                this.transform.localPosition = OriginPos + (Vector3)Dirvec * limitDist;
            }

            Dirvec = Dirvec.normalized;

            

            //
            // 무브도 콜백으로 옮겨야 할듯.
            //

            Avater.transform.localPosition += (Vector3)Dirvec * Speed;

            if(Dirvec.x < 0)
            {
                callback(Battle.Animation.Left);
            }
            else if(Dirvec.x > 0)
            {
                callback(Battle.Animation.Right);
            }
            else
            {
                callback(Battle.Animation.Idle);
            }
        }
        else
        {
            callback(Battle.Animation.Idle);
        }
    }

    void OnDrag(Vector2 delta)
    {

        this.transform.localPosition += (Vector3)delta;
        
        //if(Avater != null)
        //{
        //    Vector3 Dirvec = this.transform.localPosition - OriginPos;
        //    Dirvec = Dirvec.normalized;
        //    Avater.transform.localPosition += (Vector3)Dirvec * 0.01f;
        //}
    }

    public void OnBtnA()
    {
        Debug.Log("ButtonA");
        view.text = "ButtonA";
    }

    public void OnBtnB()
    {
        Debug.Log("ButtonB");
        view.text = "ButtonB";
    }
}
