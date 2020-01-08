using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEditor;
using UnityEditor.SceneManagement;
//using Newtonsoft.Json;
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

        public Map.Map map;

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

    Map.Map m_Map = null;

    Vector2 m_Scroll1 = Vector2.zero;
    Vector2 m_Scroll2 = Vector2.zero;
    Vector2 m_Scroll3 = Vector2.zero;

    GameObject mMapManager = null;
    RectTransform mEnvInstance = null;

    Map.Tile m_SelectTile = null;

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
        GUILayout.BeginHorizontal();
        //
        //
        //
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

            GameObject.Instantiate(AssetDatabase.LoadAssetAtPath<GameObject>("Assets/Resources/Datas/Prefab/MapTool/GameObj.prefab"));
            GameObject.Instantiate(AssetDatabase.LoadAssetAtPath<GameObject>("Assets/Resources/Datas/Prefab/MapTool/GameUI.prefab"));

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
                GameObject.Instantiate(AssetDatabase.LoadAssetAtPath<GameObject>("Assets/Script/Battle/Editor/BattleUI.prefab"));
                GameObject.Instantiate(AssetDatabase.LoadAssetAtPath<GameObject>("Assets/Script/Battle/Editor/BattleEditor.prefab"));

               
            }
        }

        if (GUILayout.Button("Save", EditorStyles.miniButton, GUILayout.Width(50)))
        {
            string path = EditorUtility.SaveFilePanel("Save", defaultDirectory, defaultName, "json");
            if (!string.IsNullOrEmpty(path))
            {
                dataPath = path;
                defaultDirectory = Path.GetDirectoryName(path);
            }
        }

        GUILayout.Label(dataPath, EditorStyles.miniLabel);
        GUILayout.EndHorizontal();
    }



    void StageList()
    {
        //if(m_Map == null || m_St)
    }
}

