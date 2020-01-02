using UnityEngine;
using UnityEditor;
using System;
using System.IO;
using System.Collections.Generic;

public class MapCreate : EditorWindow
{
    [MenuItem("TileMapEditor/MapCreate")]
    static void Init()
    {
        MapCreate window = (MapCreate)EditorWindow.GetWindow(typeof(MapCreate));
        window.Show();
    }

    void OnGUI()
    {        

        if (GUILayout.Button("Save"))
        {
            Save();
        }
        if (GUILayout.Button("Load"))
        {
            Load();
        }
    }

    void Save()
    {
        PlayerInfo[] playerInfo = new PlayerInfo[2];
                
        playerInfo[0] = new PlayerInfo();
        playerInfo[0].name = "12341234";
        playerInfo[0].lives = 5;
        playerInfo[0].strength = 25.0f;
        
        playerInfo[1] = new PlayerInfo();
        playerInfo[1].name = "1235235";
        playerInfo[1].lives = 3;
        playerInfo[1].strength = 30.2f;
        
        string toJson = Json.ToJson(playerInfo, prettyPrint: true);
        
        BinaryJson.Save(toJson, "base");
    }

    void Load()
    {
        BinaryJson.Load("base");        
    }
}