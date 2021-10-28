using UnityEngine;

namespace FlappyBird
{
    public class BulletData : EntityData
    {
        /// <summary>
        /// 发射位置
        /// </summary>
        public Vector2 ShootPosition { get; private set; }

        /// <summary>
        /// 飞行速度
        /// </summary>
        public float FlySpeed { get; private set; }

        public BulletData(int entityId, int typeId, Vector2 shootPosition, float flySpeed) : base(entityId, typeId)
        {
            ShootPosition = shootPosition;
            FlySpeed = flySpeed;
        }
    }
}