using System;
using UnityEngine;

namespace FlappyBird
{
    public class Bullet : Entity
    {
        private BulletData m_BulletData;

        protected override void OnShow(object userData)
        {
            base.OnShow(userData);
            m_BulletData = (BulletData) userData;
            
            CachedTransform.SetLocalScaleX(1.8f);
            CachedTransform.position = m_BulletData.ShootPosition;
        }

        protected override void OnUpdate(float elapseSeconds, float realElapseSeconds)
        {
            base.OnUpdate(elapseSeconds, realElapseSeconds);
            
            CachedTransform.Translate(Vector2.right * m_BulletData.FlySpeed * elapseSeconds, Space.World);
            
            // 到达最大飞行距离
            if (CachedTransform.position.x >= 9.1f)
            {
                GameEntry.Entity.HideEntity(this);
            }
        }

        private void OnTriggerEnter2D(Collider2D other)
        {
            // 隐藏管道与自身
            GameEntry.Sound.PlaySound(1);
            other.gameObject.SetActive(false);
            GameEntry.Entity.HideEntity(this);
        }
    }
}