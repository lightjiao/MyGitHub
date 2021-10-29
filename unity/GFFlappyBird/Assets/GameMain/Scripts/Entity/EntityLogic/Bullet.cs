using System;
using GameFramework;
using GameFramework.Event;
using GameMain.Scripts.Event;
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
            
            // 监听小鸟死亡事件
            GameEntry.Event.Subscribe(BirdDeadEventArgs.EventId, OnBirdDead);
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

        protected override void OnHide(object userData)
        {
            base.OnHide(userData);
            // 取消监听
            GameEntry.Event.Unsubscribe(BirdDeadEventArgs.EventId, OnBirdDead);
        }
        
        
        private void OnBirdDead(object sender, GameEventArgs e)
        {
            // 小鸟死亡后隐藏自身（子弹）
            GameEntry.Entity.HideEntity(this);
        }

        private void OnTriggerEnter2D(Collider2D other)
        {
            // 隐藏管道与自身
            GameEntry.Sound.PlaySound(1);
            other.gameObject.SetActive(false);
            GameEntry.Entity.HideEntity(this);
            
            // 加分事件
            var e = ReferencePool.Acquire<AddScoreEventArgs>();
            GameEntry.Event.Fire(this, e.Fill(10));
        }
    }
}