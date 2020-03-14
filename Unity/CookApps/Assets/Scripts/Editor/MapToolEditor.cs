using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEditor;
using UnityEditor.SceneManagement;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.IO;
using Map;
using System;

public class MapToolEditor : EditorWindow
{
    [MenuItem("Tools/MapTool", false, 55)]

    static void DoIt()
    {
        MapToolEditor window = EditorWindow.GetWindow<MapToolEditor>("MapTool");
        window.Show();
    }


    /// <summary>
    /// 
    ///  에디터 관련 변수들.
    /// </summary>

    static GUIStyle ListBox = null;
    static GUIStyle ListBoxItem = null;
    static string dataPath = string.Empty;
    static string defaultDirectory = string.Empty;
    static string defaultName = "Map";
    static string defaultResourcePath = "Assets/Datas/";
    static string defaultOwnerPoints = defaultResourcePath + "Map/default.json";

    Vector2 m_Scroll1 = Vector2.zero;
    Vector2 m_Scroll2 = Vector2.zero;
    Vector2 m_Scroll3 = Vector2.zero;


	GameObject m_SelectBlock = null;
	MapLoad m_MapLoad;

	int m_RowSize = 0;
	int m_ColSize = 0;

	void OnEnable()
    {
        if (ListBox == null)
        {
            string background = EditorGUIUtility.isProSkin ? "Assets/Plugin/Editor/listbox@pro.png" : "Assets/Plugin/Editor/listbox@free.png";
            ListBox = new GUIStyle();
            ListBox.normal.background = AssetDatabase.LoadAssetAtPath<Texture2D>(background);
            ListBox.border = new RectOffset(1, 4, 0, 0);
        }
        if (ListBoxItem == null)
        {
            string background = EditorGUIUtility.isProSkin ? "Assets/Plugin/Editor/listboxitem@pro.png" : "Assets/Plugin/Editor/listboxitem@free.png";
            ListBoxItem = new GUIStyle();
            ListBoxItem.normal.textColor = ((!EditorGUIUtility.isProSkin) ? new Color32(0, 0, 0, 255) : new Color32(179, 179, 179, 255));
            ListBoxItem.active.background = AssetDatabase.LoadAssetAtPath<Texture2D>(background);
            ListBoxItem.active.textColor = Color.white;
            ListBoxItem.onNormal.background = ListBoxItem.active.background;
            ListBoxItem.onNormal.textColor = ListBoxItem.active.textColor;
            ListBoxItem.padding = new RectOffset(0, 0, 2, 2);
            ListBoxItem.margin = new RectOffset(0, 1, 0, 0);
        }
    }

    private void OnGUI()
    {
        GUILayout.BeginVertical();
        TopMenu();
        EditorGUILayout.Separator();
        
		//
		//
		//
		ViewTileInfo();
		m_Scroll1 = EditorGUILayout.BeginScrollView(m_Scroll1, GUILayout.Width(900), GUILayout.Height(400));
		GUILayout.BeginHorizontal();
		ViewBlockType();
		GUILayout.EndHorizontal();

		GUILayout.BeginHorizontal();
		ViewBlockColor();
		GUILayout.EndHorizontal();

		EditorGUILayout.EndScrollView();

		GUILayout.EndVertical();
	}


	void ViewBlockType()
	{
		Array ary = System.Enum.GetValues(typeof(BLOCKTYPPE));
		int len = ary.Length;

		EditorGUILayout.LabelField("BLOCKTYPE", GUILayout.Width(90));
			
		for (int i = 0; i < len; i++)
		{
			int enumVal = (int)ary.GetValue(i);
			string enumName = System.Enum.GetName(typeof(BLOCKTYPPE), enumVal);

			if (GUILayout.Button(enumName, EditorStyles.miniButton, GUILayout.Width(120)))
			{
				if(m_SelectBlock != null)
				{
					BlockHive info = m_SelectBlock.GetComponent<BlockHive>();
					if(info != null) info.SetBlockType((BLOCKTYPPE)enumVal);
				}
			}
		}	
	}

	void ViewBlockColor()
	{
		Array ary = System.Enum.GetValues(typeof(BLOCKCOLOR));
		int len = ary.Length;

		EditorGUILayout.LabelField("BLOCKCOLOR", GUILayout.Width(90));

		for (int i = 0; i < len; i++)
		{
			int enumVal = (int)ary.GetValue(i);
			string enumName = System.Enum.GetName(typeof(BLOCKCOLOR), enumVal);

			if (GUILayout.Button(enumName, EditorStyles.miniButton, GUILayout.Width(120)))
			{
				if (m_SelectBlock != null)
				{
					BlockHive info = m_SelectBlock.GetComponent<BlockHive>();
					if (info != null) info.SetBlockColor((BLOCKCOLOR)enumVal);
				}
			}
		}
	}


	void ViewTileInfo()
	{
		GUILayout.BeginVertical();

		GUILayout.EndVertical();

		GUILayout.BeginVertical();
		GUILayout.BeginHorizontal();

		EditorGUILayout.LabelField("Mapsize",GUILayout.Width(50));

		m_RowSize = EditorGUILayout.IntField(m_RowSize, GUILayout.Width(50));
		m_ColSize = EditorGUILayout.IntField(m_ColSize, GUILayout.Width(50));

		if (GUILayout.Button("Create", EditorStyles.miniButton, GUILayout.Width(50)))
		{
			m_MapLoad.CreateBlock(m_RowSize, m_ColSize);
		}

		GUILayout.EndHorizontal();
		GUILayout.EndVertical();
	}

    void TopMenu()
    {
        GUILayout.BeginHorizontal();

        if (GUILayout.Button("New", EditorStyles.miniButton, GUILayout.Width(50)))
        {
            dataPath = string.Empty;
            defaultDirectory = string.Empty;
            defaultName = "defaultMaps";

            EditorSceneManager.NewScene(NewSceneSetup.EmptyScene, NewSceneMode.Single);

			GameObject.Instantiate(AssetDatabase.LoadAssetAtPath<GameObject>("Assets/Resources/Prefab/Main Camera.prefab"));
			GameObject go = GameObject.Instantiate(AssetDatabase.LoadAssetAtPath<GameObject>("Assets/Resources/Prefab/Map.prefab"));
			m_MapLoad = go.GetComponent<MapLoad>();
		}

        if (GUILayout.Button("Load", EditorStyles.miniButton, GUILayout.Width(50)))
        {
            string path = EditorUtility.OpenFilePanel("Open", defaultDirectory, "json");

            if (!string.IsNullOrEmpty(path))
            {
                dataPath = path;
                defaultDirectory = Path.GetDirectoryName(path);
                defaultName = Path.GetFileName(path);

                EditorSceneManager.NewScene(NewSceneSetup.EmptyScene, NewSceneMode.Single);

				GameObject.Instantiate(AssetDatabase.LoadAssetAtPath<GameObject>("Assets/Resources/Prefab/Main Camera.prefab"));
				GameObject go = GameObject.Instantiate(AssetDatabase.LoadAssetAtPath<GameObject>("Assets/Resources/Prefab/Map.prefab"));
				m_MapLoad = go.GetComponent<MapLoad>();
				Load(path);
			}
        }

        if (GUILayout.Button("Save", EditorStyles.miniButton, GUILayout.Width(50)))
        {
			string path = EditorUtility.SaveFilePanel("Save", defaultDirectory, defaultName, "json");

			if (!string.IsNullOrEmpty(path))
			{
				Save(path);
			}
		}
		

		GUILayout.Label(dataPath, EditorStyles.miniLabel);
        GUILayout.EndHorizontal();
    }

	private void Update()
	{
		m_SelectBlock = Selection.activeGameObject;
	}

	void Save(string path)
	{
		try
		{
			SAVEBLOCKDATA data = new SAVEBLOCKDATA();

			
			data.blocks = new BLOCK[m_MapLoad.blocks.Length];
			data.row = m_MapLoad.GetRowCount();
			data.col = m_MapLoad.GetColCount();

			for(int i = 0; i < m_MapLoad.blocks.Length; i++)
			{
				data.blocks[i] = m_MapLoad.blocks[i].GetComponent<BlockHive>().GetBlockInfo();
			}


			File.WriteAllText(path, JsonConvert.SerializeObject(data));
		}
		catch (System.Exception e)
		{
			Debug.Log(e);
		}
	}

	void Load(string path)
	{
		SAVEBLOCKDATA data = new SAVEBLOCKDATA();
		try
		{
			data = JsonConvert.DeserializeObject<SAVEBLOCKDATA>(File.ReadAllText(path));
			m_MapLoad.LoadBlock(data);
		}
		catch (System.Exception e)
		{
			Debug.Log(e);
		}
	}
}

