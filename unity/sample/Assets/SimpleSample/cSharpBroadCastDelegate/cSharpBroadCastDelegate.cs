using UnityEngine;
using System;

public class Hello
{
    public bool ReturnTrue()
    {
        return true;
    }

    public bool ReturnFalse()
    {
        return false;
    }
}

public class cSharpBroadCastDelegate : MonoBehaviour 
{
    Func<bool> condition;

    private void Start() 
    {
        var h1 = new Hello();
        var h2 = new Hello();

        condition += h2.ReturnFalse;
        condition += h1.ReturnTrue;

        var ret = condition?.Invoke();
        Debug.Log("condition ret: " + ret);
    }
}