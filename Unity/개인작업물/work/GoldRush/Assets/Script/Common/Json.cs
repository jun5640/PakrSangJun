using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Text;
using System;
using System.Runtime.Serialization.Formatters.Binary;
using System.IO;

[Serializable]
public class PlayerInfo
{       
    public string name;
    public int lives;
    public float strength;
}

public static class Json
{    
    public static T[] FromJson<T>(string json)
    {
        Wrapper<T> wrapper = JsonUtility.FromJson<Wrapper<T>>(json);
        return wrapper.items;
    }    
    
    public static string ToJson<T>(T[] array)
    {
        Wrapper<T> wrapper = new Wrapper<T>();
        wrapper.items = array;
        return JsonUtility.ToJson(wrapper);
    }

    public static string ToJson<T>(T[] array, bool prettyPrint)
    {
        Wrapper<T> wrapper = new Wrapper<T>();
        wrapper.items = array;
        return JsonUtility.ToJson(wrapper, prettyPrint);
    }

    [Serializable]
    private class Wrapper<T>
    {
        public T[] items;
    }
}


public static class BinaryJson
{
    public static void Save(string data, string filepath)
    {
        StringBuilder sb = new StringBuilder();

        foreach (char c in data.ToCharArray())
        {
            sb.Append(Convert.ToString(c, 2).PadLeft(8, '0'));
        }

        BinaryFormatter formatter = new BinaryFormatter();
        FileStream stream;
        if (File.Exists(Application.dataPath + "/Saves/" + filepath + ".bin"))
        {
            stream = new FileStream(Application.dataPath + "/Saves/" + filepath + ".bin", FileMode.Append);
        }
        else
        {
            stream = new FileStream(Application.dataPath + "/Saves/" + filepath + ".bin", FileMode.Create);
        }
        
        formatter.Serialize(stream, sb.ToString());
        stream.Close();
    }    

    public static string Load(string filepath)
    {
        if(!File.Exists(Application.dataPath + "/Saves/" + filepath + ".bin"))
            return null;
                
        BinaryFormatter formatter = new BinaryFormatter();
        FileStream stream = new FileStream(Application.dataPath + "/Saves/" + filepath + ".bin", FileMode.Open);
        String data = formatter.Deserialize(stream).ToString();
        stream.Close();
        List<Byte> byteList = new List<Byte>();
        for (int i = 0; i < data.Length; i += 8)
        {
            byteList.Add(Convert.ToByte(data.Substring(i, 8), 2));
        }
        Debug.Log(Encoding.ASCII.GetString(byteList.ToArray()));
        return Encoding.ASCII.GetString(byteList.ToArray());
    }
}