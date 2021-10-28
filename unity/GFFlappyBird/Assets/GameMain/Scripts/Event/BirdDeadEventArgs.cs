using GameFramework.Event;

namespace GameMain.Scripts.Event
{
    public class BirdDeadEventArgs : GameEventArgs
    {
        public static readonly int EventId = typeof(BirdDeadEventArgs).GetHashCode();

        public override int Id => EventId;

        public override void Clear()
        {
        }
    }
}