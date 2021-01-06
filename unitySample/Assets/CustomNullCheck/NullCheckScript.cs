using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NullCheckScript : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        var GO = GameObject.CreatePrimitive(PrimitiveType.Cube);
        Debug.Log($"Create GO");
        Debug.Log($"GO == null: {GO == null}");
        Debug.Log($"GO is null: {GO is null}");

        DestroyImmediate(GO);
        Debug.Log($"Destroy(GO);");
        Debug.Log($"GO == null: {GO == null}");
        Debug.Log($"GO is null: {GO is null}");

        GO = null;
        Debug.Log($"GO = null;");
        Debug.Log($"GO == null: {GO == null}");
        Debug.Log($"GO is null: {GO is null}");
    }
}
