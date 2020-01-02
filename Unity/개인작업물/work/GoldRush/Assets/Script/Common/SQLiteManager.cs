using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using System.Data;

public class SQLiteManager : SingletonBase<SQLiteManager>
{

    SqliteDatabase DbCon;
    const string ResourcesRoot = "Assets/";

    public void Connect(string path)
    {
        //string DbPath = "URL=file" + Application.dataPath + path;

        string DbPath = path;
        DbCon = new SqliteDatabase(DbPath);

        if (DbCon.IsConnectionOpen)
        {

        }
        else
        {
            DbCon.Open();
        }
    }

    public void OnDestroy()
    {
        DbCon.Close();
        DbCon = null;
    }

    public T GetValue<T>(uint Idx) where T : new()
    {
        string[] @type = typeof(T).ToString().Split('.');
        string tableName = type[1];
        string sqlQuery = String.Format("SELECT * FROM {0} WHERE {1}", tableName, Idx.ToString());

        return DbCon.ExecuteQueryObject<T>(sqlQuery, tableName);
    }



    public string GetAssetPath(string path)
    {
#if UNITY_EDITOR
        if (AssetBundleManagerOptions.enableEditorAssets)
        {
            return ResourcesRoot + path;
        }
        else
#endif
        {
            return ResourcesRoot + path;
        }
    }
}
