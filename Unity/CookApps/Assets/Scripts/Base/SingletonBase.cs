using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SingletonBase<T> : MonoBehaviour where T : SingletonBase<T>
{
    private static T m_Instance = null;
    private static bool applicationIsQuitting = false;
    private static object _lock = new object();
 
    public static T instance
    {
        get
        {
            if(applicationIsQuitting)
            {
                Debug.LogWarning("Singleton instance '" + typeof(T) +
                    "' already destroyed on application quit." +
                    "won`t create agin - returning null.");
                return null;
            }

            lock (_lock)
            {
                if (m_Instance == null)
                {
                    m_Instance = GameObject.FindObjectOfType(typeof(T)) as T;

                    if (m_Instance == null)
                    {
                        Debug.LogWarning("No instance of " + typeof(T).ToString() + ",a temporary one is created.");
                        m_Instance = new GameObject("Singleton of " + typeof(T).ToString(), typeof(T)).GetComponent<T>();

                        if(m_Instance == null)
                        {
                            Debug.LogError("Problem during the creation of " + typeof(T).ToString());
                        }

                        DontDestroyOnLoad(m_Instance);
                    }
                }
                return m_Instance;
            }
        }
    }

    private void Awake()
    {
        if(m_Instance == null)
        {
            m_Instance = this as T;
            m_Instance.Initializations();
        }
    }

    protected virtual void Initializations() { }

    protected virtual void Destroy() { }

    // Make sure the instance isn't referenced anymore when the user quit, just in case.
    private void OnApplicationQuit()
    {
        m_Instance = null;
#if !UNITY_EDITOR
		applicationIsQuitting = true;
#endif
    }

}
