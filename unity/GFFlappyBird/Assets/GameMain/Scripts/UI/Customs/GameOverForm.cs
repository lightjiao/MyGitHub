using GameFramework;
using GameMain.Scripts.Event;
using UnityEngine.UI;
using UnityGameFramework.Runtime;

namespace FlappyBird
{
    public class GameOverForm : UGuiForm
    {
        public Text Score;

        protected override void OnOpen(object userData)
        {
            base.OnOpen(userData);

            var score = GameEntry.DataNode.GetNode("Score").GetData<VarInt>().Value.ToString();
            Score.text = $"总分：{score}";
        }

        protected override void OnClose(object userData)
        {
            base.OnClose(userData);
            Score.text = string.Empty;
        }

        public void OnRestartButtonClick()
        {
            Close(true);
            
            // 派发重新开始游戏的事件
            GameEntry.Event.Fire(this, ReferencePool.Acquire<RestartEventArgs>());
            
            // 显示小鸟
            GameEntry.Entity.ShowBird(new BirdData(GameEntry.Entity.GenerateSerialId(), 3, 5f));
        }

        public void OnReturnButtonClick()
        {
            Close(true);
            
            GameEntry.Event.Fire(this, ReferencePool.Acquire<ReturnMenuEventArgs>());
        }
    }
}