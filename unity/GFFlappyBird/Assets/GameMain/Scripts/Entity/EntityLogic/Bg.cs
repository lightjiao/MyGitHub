using UnityEngine;

namespace FlappyBird
{
    public class Bg : Entity
    {
        private BgData m_BgData = null;

        private bool m_IsSpawn = false;

        protected override void OnShow(object userData)
        {
            base.OnShow(userData);

            m_BgData = (BgData) userData;
            CachedTransform.SetLocalPositionX(m_BgData.StartPosition);
        }

        protected override void OnUpdate(float elapseSeconds, float realElapseSeconds)
        {
            base.OnUpdate(elapseSeconds, realElapseSeconds);
            
            // 控制背景实体移动
            CachedTransform.Translate(Vector3.left * m_BgData.MoveSpeed * elapseSeconds, Space.World);
            if (CachedTransform.position.x <= m_BgData.SpawnTarget && m_IsSpawn == false)
            {
                // 显示背景实体
                GameEntry.Entity.ShowBg(new BgData(GameEntry.Entity.GenerateSerialId(), m_BgData.TypeId, m_BgData.MoveSpeed, 17.92f));
                m_IsSpawn = true;
            }

            if (CachedTransform.position.x < m_BgData.HideTarget && m_IsSpawn)
            {
                // OnHide(null);
                GameEntry.Entity.HideEntity(this);
            }
        }

        protected override void OnHide(object userData)
        {
            base.OnHide(userData);

            m_IsSpawn = false;
        }
    }
}