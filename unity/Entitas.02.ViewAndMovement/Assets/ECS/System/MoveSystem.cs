using Entitas;
using UnityEngine;

public class MoveSystem : IExecuteSystem, ICleanupSystem
{
    private readonly IGroup<GameEntity> _movers;
    private readonly IGroup<GameEntity> _moveCompletes;
    private const float _speed = 4f;// 移动系统固定的移动速度

    public MoveSystem(Contexts contexts)
    {
        _movers = contexts.game.GetGroup(GameMatcher.Move);
        _moveCompletes = contexts.game.GetGroup(GameMatcher.MoveComplete);
    }

    void IExecuteSystem.Execute()
    {
        foreach (var e in _movers.GetEntities())
        {
            var dir = e.move.target - e.position.value;
            var newPosition = e.position.value + dir.normalized * _speed * Time.deltaTime;

            // 为什么是replacePosition，而不是position = value
            e.ReplacePosition(newPosition);

            var angle = Mathf.Atan2(dir.y, dir.x) * Mathf.Rad2Deg;
            e.ReplaceDirection(angle);

            float dist = dir.magnitude;
            if (dist <= 0.5f)
            {
                e.RemoveMove();
                e.isMoveComplete = true;
            }
        }
    }

    void ICleanupSystem.Cleanup()
    {
        foreach (var e in _moveCompletes.GetEntities())
        {
            e.isMoveComplete = false;
        }
    }
}