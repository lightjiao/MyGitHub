using UnityEngine;

/// <summary>
/// 从能量守恒角度实现单摆运动
/// </summary>
public class CircleMove2 : MonoBehaviour
{
    private const float PI = 3.14159265f;

    // 圆周运动的中心
    public Transform m_Center;

    // 重力 ( 3.92 对应到现实世界就是 9.8 )
    public float m_Gravity = 9.8f;

    private float m_E;  // 总能量
    private float m_T;  // 动能
    private float m_V;  // 势能
    private float m_L;  // 绳长，半径
    private readonly float m_Mass = 1f; // 质量
    private float m_e;

    private float m_rx, m_ry; // 相对于中心的x位置
    private float m_vx, m_vy; // 分速度

    private void Start()
    {
        var centerPos = m_Center.position;
        var curPos = transform.position;
        var theta = Vector3.Angle(Vector3.down, curPos - centerPos) * Mathf.Deg2Rad;

        m_L = (curPos - centerPos).magnitude;

        // 计算能量守恒
        m_T = 0;
        m_V = m_Mass * m_Gravity * m_L * (1 - Mathf.Cos(theta));
        m_E = m_T + m_V;
        m_e = m_E / (m_Mass * m_Gravity * m_L);

        // 计算圆周运动的初始状态
        m_rx = curPos.x - centerPos.x;
        m_ry = curPos.y - centerPos.y;
        m_vx = 0f;
        m_vy = 0f;
    }

    private void FixedUpdate()
    {
        var centerPos = m_Center.position;
        var curPos = transform.position;

        // 单摆公式：根据角度计算出当前的角速度
        var theta = Vector3.Angle(Vector3.down, curPos - centerPos) * Mathf.Deg2Rad;
        var sqrtValue = 2 * m_Gravity / m_L * (m_e - 1 + Mathf.Cos(theta));
        sqrtValue = Mathf.Max(0, sqrtValue); // 原本不应该计算出小于0的数，但由于浮点数计算精度问题会出现小于0的数，强行约束一下
        var angle_Vel = Mathf.Sqrt(sqrtValue);

        // 最后施加向心力做圆周运动
        m_vx += -angle_Vel * angle_Vel * m_rx;
        m_vy += -angle_Vel * angle_Vel * m_ry;

        // 角速度移动
        m_rx += m_vx;
        m_ry += m_vy;

        var newCurPos = centerPos;
        newCurPos.x += m_rx;
        newCurPos.y += m_ry;
        transform.position = newCurPos;
    }
}