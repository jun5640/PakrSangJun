using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEditor;
using UnityEditor.SceneManagement;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.IO;


public class MapToolEditor : EditorWindow
{
    [MenuItem("Tools/MapTool", false, 55)]

    static void DoIt()
    {
        MapToolEditor window = EditorWindow.GetWindow<MapToolEditor>("MapTool");
        window.Show();
    }



    class EditorStage
    {

        //
        // 각 방마다 저장된 몹들 정보.
        //

       // public Map.Map map;

        public EditorStage()
        {

        }

        
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

	//Map.Map m_Map = null;
	string TileId = "";
	Map.MapTile mMapTile = null;

    Vector2 m_Scroll1 = Vector2.zero;
    Vector2 m_Scroll2 = Vector2.zero;
    Vector2 m_Scroll3 = Vector2.zero;

    GameObject mMapManager = null;
	MapToolScript mMapToolScript = null;
    RectTransform mEnvInstance = null;

    Map.Tile m_SelectTile = null;

	Texture[] TileTexture;

	bool EditorModeOn = false;
	bool MultiSelectOn = false;

	GameObject selectTile;


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
		DrawImag();
		GUILayout.EndHorizontal();
		EditorGUILayout.EndScrollView();

		GUILayout.EndVertical();
	}


	void DrawImag()
	{
		if(mMapToolScript != null)
		{
			for (int i = 0; i < mMapToolScript.TileInfos.Length; i++)
			{
				if(TileTexture[i] == null)
				{ 
					TileTexture[i] = Resources.Load<Texture>(mMapToolScript.TileInfos[i].path);
				}
				GUILayout.Box(TileTexture[i]);
				if(GUILayout.Button((mMapToolScript.TileInfos[i].Id - 1).ToString(), EditorStyles.miniButton, GUILayout.Width(30)))
				{
					TileId = (mMapToolScript.TileInfos[i].Id - 1).ToString();
				}
				if((i + 1) % 15 == 0)
				{
					GUILayout.EndHorizontal();
					GUILayout.BeginHorizontal();
				}
			}	
		}	
	}


	void ViewTileInfo()
	{
		GUILayout.BeginVertical();

		EditorGUILayout.LabelField("EditorModeOn:", EditorModeOn.ToString());
		EditorGUILayout.LabelField("MultiSelectModeOn:", MultiSelectOn.ToString());

		GUILayout.EndVertical();

		GUILayout.BeginVertical();

		EditorGUILayout.LabelField("Id:", TileId);

		GUILayout.EndVertical();

		if (!string.IsNullOrEmpty(TileId)) mMapTile = mMapToolScript.GetTileInfo(int.Parse(TileId));
		else mMapTile = null;

		if (mMapTile != null)
		{
			GUILayout.BeginVertical();
			EditorGUILayout.LabelField("img_path:", mMapTile.path);
			GUILayout.EndVertical();
			GUILayout.BeginVertical();
			EditorGUILayout.LabelField("IsCrash", mMapTile.IsTrigger.ToString());
			GUILayout.EndVertical();
		}
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

            GameObject.Instantiate(AssetDatabase.LoadAssetAtPath<GameObject>("Assets/Resources/Datas/Prefab/MapTool/Character.prefab"));
            GameObject.Instantiate(AssetDatabase.LoadAssetAtPath<GameObject>("Assets/Resources/Datas/Prefab/MapTool/GameUI.prefab"));
			GameObject.Instantiate(AssetDatabase.LoadAssetAtPath<GameObject>("Assets/Resources/Datas/Prefab/MapTool/MainCamera.prefab"));
			mMapManager = GameObject.Instantiate(AssetDatabase.LoadAssetAtPath<GameObject>("Assets/Resources/Datas/Prefab/MapTool/Tile_Grid.prefab"));
			mMapToolScript = mMapManager.AddComponent<MapToolScript>();
			mMapToolScript.LoadTileinfo();
			TileTexture = new Texture[mMapToolScript.TileInfos.Length];

			//mMapManager = GameObject.Find("MapManager");
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

				GameObject.Instantiate(AssetDatabase.LoadAssetAtPath<GameObject>("Assets/Resources/Datas/Prefab/MapTool/Character.prefab"));
				GameObject.Instantiate(AssetDatabase.LoadAssetAtPath<GameObject>("Assets/Resources/Datas/Prefab/MapTool/GameUI.prefab"));
				GameObject.Instantiate(AssetDatabase.LoadAssetAtPath<GameObject>("Assets/Resources/Datas/Prefab/MapTool/MainCamera.prefab"));
				mMapManager = GameObject.Instantiate(AssetDatabase.LoadAssetAtPath<GameObject>("Assets/Resources/Datas/Prefab/MapTool/Tile_Grid.prefab"));
				mMapToolScript = mMapManager.AddComponent<MapToolScript>();
				mMapToolScript.LoadTileinfo();
				TileTexture = new Texture[mMapToolScript.TileInfos.Length];
				Load(path);
			}
        }

        if (GUILayout.Button("Save", EditorStyles.miniButton, GUILayout.Width(50)))
        {
			string path = EditorUtility.SaveFilePanel("Save", defaultDirectory, defaultName, "json");
			//PrefabUtility.SaveAsPrefabAsset(mMapManager, path);

			if (!string.IsNullOrEmpty(path))
			{
				Save(path);
			}
		}

		if (GUILayout.Button("EditorModeSwitch", EditorStyles.miniButton, GUILayout.Width(150)))
		{
			EditorModeOn = !EditorModeOn;
		}



		if (GUILayout.Button("MultiselectModeSwitch", EditorStyles.miniButton, GUILayout.Width(150)))
		{
			MultiSelectOn = !MultiSelectOn;
		}

		GUILayout.Label(dataPath, EditorStyles.miniLabel);
        GUILayout.EndHorizontal();
    }

	private void Update()
	{
		if (EditorModeOn)
		{
			if (MultiSelectOn)
			{
				GameObject[] go = Selection.gameObjects;

				for (int i = 0; i < go.Length; i++)
				{
					MapTileCell cell = go[i].GetComponentInChildren<MapTileCell>();
					if (cell != null && mMapTile != null) cell.CellUpdate(mMapTile);
				}
			}
			else
			{
				selectTile = Selection.activeGameObject;

				if (selectTile != null)
				{
					MapTileCell cell = selectTile.GetComponentInChildren<MapTileCell>();
					if (cell != null && mMapTile != null) cell.CellUpdate(mMapTile);
				}
			}
		}
	}

	void Save(string path)
	{
		try
		{
			int[] TileIndex = new int[mMapToolScript.Maps.Count];
			for(int i = 0; i < mMapToolScript.Maps.Count; i++)
			{
				TileIndex[i] = mMapToolScript.Maps[i].Id;
			}
		

			File.WriteAllText(path, JsonConvert.SerializeObject(TileIndex));
		}
		catch (System.Exception e)
		{
			Debug.Log(e);
		}
	}

	void Load(string path)
	{
		int[] index;
		try
		{
			index = JsonConvert.DeserializeObject<int[]>(File.ReadAllText(path));
			mMapToolScript.TileLoad(index);
		}
		catch (System.Exception e)
		{
			Debug.Log(e);
		}
	}
}

