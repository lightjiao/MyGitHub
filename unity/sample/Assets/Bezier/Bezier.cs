using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(LineRenderer))]
public class Bezier : MonoBehaviour
{
    [SerializeField]
    public Transform StartPos;

    [SerializeField]
    public Transform EndPos;

    /// <summary>
    /// 弯曲程度
    /// </summary>
    [SerializeField]
    public float BlendDegree = 1;

    /// <summary>
    /// 根据起始点结束点和弯曲程度计算出来的中间的点
    /// </summary>
    [SerializeField]
    private Transform mediumPos; 

    
    private LineRenderer lineRenderer;
    private int layerOrder = 0;
    
    // 采样点数量，数量越密集，曲线越圆润，性能消耗也越大
    private int _segmentNum = 50;
 
    void Start()
    {
        if (!lineRenderer)
        {
            lineRenderer = GetComponent<LineRenderer>();
        }
        lineRenderer.sortingLayerID = layerOrder;
    }
 
    void Update()
    { 
        mediumPos.position = CalculateMediumPos(StartPos.position, EndPos.position, BlendDegree);
        DrawCurve();
    }

    /// <summary>
    /// 根据曲线弯曲程度求出中间的点的位置
    /// </summary>
    /// <param name="p0">起始点</param>
    /// <param name="p2">结束点</param>
    /// <param name="blendDegree">曲线弯曲程度</param>
    private Vector3 CalculateMediumPos(Vector3 p0, Vector3 p2, float blendDegree)
    {
        // 方案一, 求两点间的中间点，然后加上一个高度
        var h = (p2 - p0).magnitude;
        return (p2 + p0) / 2 + blendDegree * h * Vector3.up;
    }
 
    void DrawCurve()
    {
        int i = 1;
        lineRenderer.positionCount = _segmentNum;
        foreach (var item in GetBezierPoint(StartPos.position, mediumPos.position, EndPos.position, _segmentNum))
        {
            lineRenderer.SetPosition(i - 1, item);            
            i++;
        }
    }

    IEnumerable<Vector3> GetBezierPoint(Vector3 p0, Vector3 p1, Vector3 p2, int segmentNum)
    {
        for (int i = 1; i <= segmentNum; i++)
        {
            var t = i / (float)segmentNum;
            Vector3 pixel = CalculateCubicBezierPoint(t, p0, p1, p2);
            yield return pixel;
        }
    }
 
    Vector3 CalculateCubicBezierPoint(float t, Vector3 p0, Vector3 p1, Vector3 p2)
    {
        float u = 1 - t;
        float tt = t * t;
        float uu = u * u;
 
        Vector3 p = uu * p0;
        p += 2 * u * t * p1;
        p += tt * p2;
 
        return p;
    }
}