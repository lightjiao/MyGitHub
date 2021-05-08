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

    // 重力 ( 3.92 对应到现实世界就是 9.8 )
    public float m_Gravity = 3.92f;

    private const float PI = 3.14159265f;
    [SerializeField]
    private float m_Angle_Vel; // 角速度(2 * PI / 周期)
    [SerializeField]
    private float m_rx, m_ry; // 相对于中心的x位置
    [SerializeField]
    private float m_vx, m_vy; // 分速度
    private bool m_IsFall; // 是否在往下掉落

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

        m_Angle_Vel *= 2;


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

        // 运动方向的向量
        var velocity = m_vx * Vector3.right + m_vy * Vector3.up;
        
        // 重力加速度对运动方向速度的影响
        var gravityOnVelocity = Vector3.Dot(m_Gravity * Vector3.down, velocity) / velocity.magnitude;
        velocity = velocity.normalized * (velocity.magnitude + gravityOnVelocity * Time.fixedDeltaTime);
        
        // 重力影响过后的速度换算成速度分量和角速度
        m_vx = Vector3.Dot(velocity, Vector3.right);
        m_vy = Vector3.Dot(velocity, Vector3.up);
        m_Angle_Vel = velocity.magnitude / m_R;

        // 最后施加向心力做圆周运动
        m_vx += -m_Angle_Vel * m_Angle_Vel * m_rx;
        m_vy += -m_Angle_Vel * m_Angle_Vel * m_ry;
    }
}