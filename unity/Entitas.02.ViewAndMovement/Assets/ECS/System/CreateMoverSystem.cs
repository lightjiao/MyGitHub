using Entitas;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// 响应右键和按键按下的Component
/// 并且创建一个entity，设置位置、方向和sprite
/// </summary>
public class CreateMoverSystem : ReactiveSystem<InputEntity>
{
    private readonly GameContext _gameContext;

    public CreateMoverSystem(Contexts contexts) : base(contexts.input)
    {
        _gameContext = contexts.game;
    }

    protected override ICollector<InputEntity> GetTrigger(IContext<InputEntity> context)
    {
        return context.CreateCollector(InputMatcher.AllOf(InputMatcher.RightMouse, InputMatcher.MouseDown));
    }

    protected override bool Filter(InputEntity entity)
    {
        return entity.hasMouseDown;
    }

    protected override void Execute(List<InputEntity> entities)
    {
        foreach (var e in entities)
        {
            var mover = _gameContext.CreateEntity();
            mover.isMover = true;
            mover.AddPosition(e.mouseDown.position);
            mover.AddDirection(Random.Range(0, 360));
            mover.AddSprite("Bee");
        }
    }
}