using UniRx;
using UnityEngine;

public class Sample : MonoBehaviour
{
    private void Start()
    {
        ObservableWWW.Get("http://www.baidu.com").Subscribe(
            x => Debug.Log("123"),
            ex => Debug.Log("234")
        );
    }
}