using System.Linq;
using System.Collections.Generic;
using UnityEngine;
using Random = UnityEngine.Random;

/// <summary>
/// 说是通过Lerp模拟抛物线获取随机值
/// 但画出来的曲线很奇怪，反正不是正态分布，像是一个被拉直了的正弦函数
/// </summary>
public class LerpRandom : MonoBehaviour
{
    /// <summary>
    /// 这里的averageOffset模拟了弧线中心位置的偏移
    /// </summary>
    [SerializeField] private float averageOffset = 0f;

    /// <summary>
    /// alpha模拟了弧线的陡峭程度
    /// </summary>
    [SerializeField] private float alpha = 2f;

    [SerializeField] private int pointNum = 50;

    // 曲线在水平面的长度
    [SerializeField] private float arcHorizontalLength = 10;

    private LineRenderer lineRenderer;

    private void Awake()
    {
        lineRenderer = GetComponent<LineRenderer>();
    }

    // Update is called once per frame
    private void Update()
    {
        lineRenderer.positionCount = pointNum;
        lineRenderer.SetPositions(ArcGenerateByLerp().ToArray());
    }

    /// <summary>
    /// 这个是原函数，随机的获取数值
    /// 这里的averageOffset模拟了弧线中心位置的偏移，alpha模拟了弧线的陡峭程度
    /// </summary>
    /// <param name="averageOffset"></param>
    /// <param name="alpha"></param>
    /// <returns></returns>
    private float Random01_Arc(float averageOffset = 0, float alpha = 2f)
    {
        var r1 = Random.value;
        var t1 = Mathf.Lerp(0, 1, r1);
        var t2 = Mathf.Lerp(1, 0, r1);
        var tFinal = Mathf.Lerp(t1, t2, r1) * alpha; // 得到弧线的点并乘以系数，系数越高越陡峭
        var r2 = Mathf.Lerp(r1, 0.5f, tFinal) + averageOffset;
        return r2;
    }

    /// <summary>
    /// 将上面的函数改造一下，展示出完整的点的位置
    /// </summary>
    /// <returns></returns>
    private IEnumerable<Vector3> ArcGenerateByLerp()
    {
        var deltaValue = 1.0f / pointNum;

        for (var i = 0; i < pointNum; i++)
        {
            var value = deltaValue * i;

            var pointX = i * arcHorizontalLength / pointNum;
            var pointY = GenArcPoint(value);
            Debug.Log(pointY);
            yield return new Vector3(pointX, pointY, 0);
        }
    }

    private float GenArcPoint(float arcLerpValue)
    {
        var t1 = Mathf.Lerp(0, 1, arcLerpValue);
        var t2 = Mathf.Lerp(1, 0, arcLerpValue);
        var tFinal = Mathf.Lerp(t1, t2, arcLerpValue) * alpha; // 得到弧线的点并乘以系数，系数越高越陡峭
        return Mathf.Lerp(arcLerpValue, 0.5f, tFinal);
    }
}