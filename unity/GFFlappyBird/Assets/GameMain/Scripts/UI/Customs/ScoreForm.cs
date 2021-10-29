using GameFramework.Event;
using GameMain.Scripts.Event;
using UnityEngine.UI;
using UnityGameFramework.Runtime;

namespace FlappyBird
{
    public class ScoreForm : UGuiForm
    {
        public Text scoreText;

        /// <summary>
        /// 积分
        /// </summary>
        private int m_Score = 0;

        /// <summary>
        /// 积分计时器
        /// </summary>
        private float m_ScoreTimer = 0;

        protected override void OnOpen(object userData)
        {
            base.OnOpen(userData);

            GameEntry.Event.Subscribe(BirdDeadEventArgs.EventId, OnBirdDead);
            GameEntry.Event.Subscribe(AddScoreEventArgs.EventId, OnAddScore);
        }

        protected override void OnUpdate(float elapseSeconds, float realElapseSeconds)
        {
            base.OnUpdate(elapseSeconds, realElapseSeconds);

            m_ScoreTimer += elapseSeconds;
            if (m_ScoreTimer > 2f)
            {
                m_ScoreTimer = 0f;
                m_Score += 1;
                scoreText.text = m_Score.ToString();
            }
        }

        protected override void OnClose(object userData)
        {
            base.OnClose(userData);

            GameEntry.Event.Unsubscribe(BirdDeadEventArgs.EventId, OnBirdDead);
        }

        protected override void OnPause()
        {
            base.OnPause();

            m_Score = 0;
            m_ScoreTimer = 0f;
            scoreText.text = m_Score.ToString();
        }

        private void OnBirdDead(object sender, GameEventArgs e)
        {
            // 把积分写入到数据节点
            GameEntry.DataNode.GetOrAddNode("Score").SetData<VarInt>(m_Score);

            GameEntry.UI.OpenUIForm(UIFormId.GameOverForm);
        }

        private void OnAddScore(object sender, GameEventArgs e)
        {
            var ne = (AddScoreEventArgs) e;
            m_Score += ne.AddCount;
            scoreText.text = m_Score.ToString();
        }
    }
}