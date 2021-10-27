using UnityEngine;

namespace FlappyBird
{
    public class PipeData : EntityData
    {
        public float MoveSpeed { get; private set; }

        /// <summary>
        /// 上管道偏移
        /// </summary>
        public float Offsetup { get; private set; }

        /// <summary>
        /// 下管道偏移
        /// </summary>
        public float Offsetdown { get; private set; }

        public float HideTarget { get; private set; }

        public PipeData(int entityId, int typeId, float moveSpeed) : base(entityId, typeId)
        {
            MoveSpeed = moveSpeed;
            Offsetup = Random.Range(4.1f, 7f);
            Offsetdown = Random.Range(-3f, -4.5f);
            HideTarget = -9.4f;
        }
    }
}