using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Creator : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        var t = Create<Mqnq>();
        t.SayHello();
    }

    public T Create<T>() where T : new()
    {
        var t = new T();
        return t;
    }

    // Update is called once per frame
    void Update()
    {

    }
}
