using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DrawRotate : MonoBehaviour
{
    public Transform VectorStart;
    public Transform VectorEnd;
    public Transform VectorRotateEnd;

    public float RotateAngle = 90;

    // Update is called once per frame
    void Update()
    {
        var vec = VectorEnd.position - VectorStart.position;
        vec = Quaternion.AngleAxis(RotateAngle, Vector3.up) * vec;

        VectorRotateEnd.position = VectorStart.position + vec;
    }
}
