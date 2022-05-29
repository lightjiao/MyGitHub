using System.Collections;
using System.Collections.Generic;
using Animancer;
using UnityEngine;

public class FindAnimancerPro : MonoBehaviour
{
    public GameObject go;
    
    

    // Start is called before the first frame update
    void Start()
    {
        var a = Object.FindObjectOfType<AnimancerComponent>();
        Debug.Log(a);
        Debug.Log($"a == null: {a == null}");
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
