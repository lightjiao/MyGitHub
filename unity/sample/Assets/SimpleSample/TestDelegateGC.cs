using System;
using FGDKit.Base;
using UnityEngine;

public class TestDelegateGC : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        var action = ActionClosure.Create((a, b) => UDebug.Print(a + b), 1, 2);
        action.Invoke();
    }

    private void Invoker(Action action)
    {
        action?.Invoke();
    }

    private void AwesomeAction()
    {
    }
}