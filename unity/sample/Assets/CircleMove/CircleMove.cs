using UnityEngine;


// 让物体进行圆周运动
// 用基于向心力的计算方法，支持增加重力
public class CircleMove : MonoBehaviour
{
    // 圆周运动的中心
    public Transform m_Center;

    // 旋转半径
    public float m_R;

    // 旋转一周的时间(秒)（周期）
    public float m_CircleTime;

    // 重力
    public float m_Gravity = 0f;

    private const float PI = 3.14159265f;
    private float m_Angle_Vel; // 角速度(2 * PI / 周期)
    private float m_rx, m_ry; // 相对于中心的x位置
    private float m_vx, m_vy; // 分速度

    private void Start()
    {
        // 开始时，球体永远在中心点的正下方
        var centerPos = m_Center.position;
        var curPos = centerPos;
        curPos.y -= m_R;
        transform.position = curPos;

        m_Angle_Vel = 2.0f * PI / (m_CircleTime * 60); // 一秒60帧
        m_rx = curPos.x - centerPos.x;
        m_ry = curPos.y - centerPos.y;

        m_vx = m_R * -m_Angle_Vel;
        m_vy = 0f;
    }

    private void FixedUpdate()
    {
        m_rx += m_vx;
        m_ry += m_vy;

        var centerPos = m_Center.position;
        var newCurPos = centerPos;
        newCurPos.x += m_rx;
        newCurPos.y += m_ry;
        transform.position = newCurPos;

        m_vx += -m_Angle_Vel * m_Angle_Vel * m_rx;
        m_vy += -m_Angle_Vel * m_Angle_Vel * m_ry;
    }
}