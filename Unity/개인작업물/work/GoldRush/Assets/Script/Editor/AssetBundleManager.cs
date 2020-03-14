using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;

public class AssetBundleManager : EditorWindow
{
	[MenuItem("Tools/AssetBundleManager", false, 55)]

	static void DoIt()
	{
		AssetBundleManager window = EditorWindow.GetWindow<AssetBundleManager>("AssetBundleManager");
		window.Show();
	}


}
