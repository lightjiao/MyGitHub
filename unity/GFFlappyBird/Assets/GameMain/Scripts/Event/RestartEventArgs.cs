using GameFramework.Event;

namespace GameMain.Scripts.Event
{
    public class RestartEventArgs : GameEventArgs
    {
        public static readonly int EventId = typeof(RestartEventArgs).GetHashCode();

        public override int Id => EventId;

        public override void Clear()
        {
        }
    }

    public class ReturnMenuEventArgs : GameEventArgs
    {
        public static readonly int EventId = typeof(ReturnMenuEventArgs).GetHashCode();

        public override int Id => EventId;

        public override void Clear()
        {
        }
    }
}