using System;
using UnityEngine;

public class RotateCapsule : MonoBehaviour
{
    private void Start()
    {
        // 结果死活不对
        // var local = new Vector3(0, 0, 90);
        // var world = transform.TransformPoint(local);
        // transform.rotation = Quaternion.Euler(world);
        // Debug.Log(world);
        
        // 直接指定local rotation也是可行的
        transform.localRotation = Quaternion.Euler(0, 0, 90);

        // Rotate有第三个参数，指定第一个参数的空间坐标是world还是local，默认是local，所以这个的表现符合预期
        transform.Rotate(Vector3.forward, 90);
    }
}