using GameFramework.Event;

namespace GameMain.Scripts.Event
{
    public class AddScoreEventArgs : GameEventArgs
    {
        public static readonly int EventId = typeof(AddScoreEventArgs).GetHashCode();

        public override int Id => EventId;

        /// <summary>
        /// 加分数量
        /// </summary>
        public int AddCount { get; private set; }

        /// <summary>
        /// 填充事件
        /// </summary>
        /// <param name="addCount"></param>
        /// <returns></returns>
        public AddScoreEventArgs Fill(int addCount)
        {
            AddCount = addCount;

            return this;
        }

        public override void Clear()
        {
            AddCount = 0;
        }
    }
}