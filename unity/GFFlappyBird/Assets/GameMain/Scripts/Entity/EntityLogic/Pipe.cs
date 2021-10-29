using GameFramework.Event;
using GameMain.Scripts.Event;
using UnityEngine;

namespace FlappyBird
{
    public class Pipe : Entity
    {
        private PipeData m_PipeData;

        private Transform m_UpPipe;
        private Transform m_DownPipe;

        protected override void OnShow(object userData)
        {
            base.OnShow(userData);

            m_PipeData = (PipeData) userData;

            CachedTransform.SetLocalPositionX(10f);

            if (m_UpPipe == null || m_DownPipe == null)
            {
                m_UpPipe = transform.Find("UpPipe");
                m_DownPipe = transform.Find("DownPipe");
            }

            m_UpPipe.SetLocalPositionY(m_PipeData.Offsetup);
            m_DownPipe.SetLocalPositionY(m_PipeData.Offsetdown);

            GameEntry.Event.Subscribe(RestartEventArgs.EventId, OnRestart);
        }

        protected override void OnUpdate(float elapseSeconds, float realElapseSeconds)
        {
            base.OnUpdate(elapseSeconds, realElapseSeconds);

            CachedTransform.Translate(Vector3.left * m_PipeData.MoveSpeed * elapseSeconds, Space.World);
            if (CachedTransform.position.x <= m_PipeData.HideTarget)
            {
                GameEntry.Entity.HideEntity(this);
            }
        }

        protected override void OnHide(object userData)
        {
            base.OnHide(userData);
            m_UpPipe.gameObject.SetActive(true);
            m_DownPipe.gameObject.SetActive(true);
        }

        private void OnRestart(object sender, GameEventArgs e)
        {
            GameEntry.Entity.HideEntity(this);
        }
    }
}