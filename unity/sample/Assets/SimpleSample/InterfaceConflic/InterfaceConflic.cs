using UnityEngine;

public class Data
{
}

internal interface IAGetter
{
    Data Get();
}

internal interface IBGetter
{
    Data Get();
}

public class ConflicGetter : IAGetter, IBGetter
{
    Data IAGetter.Get()
    {
        Debug.Log("IAGetter.Get()");
        return null;
    }

    Data IBGetter.Get()
    {
        Debug.Log("IBGetter.Get()");
        return null;
    }

    public void SayHello()
    {
        Debug.Log("Hello, InterfaceConflic");
    }
}

public class InterfaceConflic : MonoBehaviour
{
    private void Start()
    {
        var c = new ConflicGetter();
        c.SayHello();
        (c as IAGetter).Get();
        (c as IBGetter).Get();
    }
}