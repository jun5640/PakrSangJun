using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Control : MonoBehaviour
{
    private Behavior behavior; // 캐릭터의 행동 스크립트
    private Camera mainCamera; // 메인 카메라
    private Vector3 targetPos; // 캐릭터의 이동 타겟 위치

    private void Start()
    {
        behavior = GetComponent<Behavior>();
        mainCamera = GameObject.Find("Main Camera").GetComponent<Camera>();
    }

    private void Update()
    {
        // 마우스 입력을 받았을 때
        if(Input.GetMouseButtonUp(0))
        {
            //마우스로 찍은 위치의 좌표값을 가져온다.
            Ray ray = mainCamera.ScreenPointToRay(Input.mousePosition);
            RaycastHit hit;

            if(Physics.Raycast(ray, out hit, 10000f))
            {
                targetPos = hit.point;
            }
        }

        //캐릭터가 움직이고 있다면
        if(behavior.Run(targetPos))
        {
            //회전도 같이 시켜준다.
            behavior.Turn(targetPos);
        }
        else
        {
            //캐릭터의 애니메이션.
            //behavior.SetAnim(PlayerAnim.ANIM_IDLE);
        }
    }
}
