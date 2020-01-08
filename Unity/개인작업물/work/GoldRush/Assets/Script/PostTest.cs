using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PostTest : MonoBehaviour
{
    void Start()
    {
		PostNetWork.PostNetWork.instance.RequetPostFunc(new PostNetWork.ActionLogin());
	}
}
