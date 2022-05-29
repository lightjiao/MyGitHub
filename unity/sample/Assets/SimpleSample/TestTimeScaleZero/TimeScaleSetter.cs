using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TimeScaleSetter : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        Time.timeScale = 0;
    }

    // Update is called once per frame
    void Update()
    {
        Debug.Log($"Update: Time.deltaTime: {Time.deltaTime}, " +
                  $"Time.unscaledDeltaTime: {Time.unscaledDeltaTime}" + 
                  $"Time.realtimeSinceStartup: {Time.realtimeSinceStartup} + " +
                  $"Time.frameCount: {Time.frameCount}");
    }
}