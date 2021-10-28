using System;
using UnityEngine;

namespace FlappyBird
{
    public class Bird : Entity
    {
        private BirdData m_BirdData = null;

        /// <summary>
        /// 射击间隔
        /// </summary>
        private float m_ShootTime = 10f;

        /// <summary>
        /// 射击计时器
        /// </summary>
        private float m_ShootTimer = 0f;

        private Rigidbody2D m_Rigidbody = null;

        protected override void OnShow(object userData)
        {
            base.OnShow(userData);

            m_BirdData = (BirdData) userData;

            CachedTransform.localScale = Vector2.one * 2;
            if (m_Rigidbody == null)
            {
                m_Rigidbody = GetComponent<Rigidbody2D>();
            }

            m_ShootTimer = 0f;
        }

        protected override void OnUpdate(float elapseSeconds, float realElapseSeconds)
        {
            base.OnUpdate(elapseSeconds, realElapseSeconds);

            // 飞行
            if (Input.GetKeyDown(KeyCode.Space))
            {
                GameEntry.Sound.PlaySound(2);
                m_Rigidbody.velocity = new Vector2(0, m_BirdData.FlyForce);
            }
            
            // 射击
            m_ShootTimer += elapseSeconds;
            if (m_ShootTimer > m_ShootTime && Input.GetKeyDown(KeyCode.J))
            {
                m_ShootTimer = 0f;
                GameEntry.Sound.PlaySound(3);
                GameEntry.Entity.ShowBullet(new BulletData(GameEntry.Entity.GenerateSerialId(), 
                    4, 
                    CachedTransform.position + CachedTransform.right, 
                    6));
            }
        }

        private void OnTriggerEnter2D(Collider2D other)
        {
            GameEntry.Sound.PlaySound(1);
            GameEntry.Entity.HideEntity(this);
        }
    }
}