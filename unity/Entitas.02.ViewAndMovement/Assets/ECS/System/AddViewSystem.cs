using Entitas;
using Entitas.Unity;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// 识别出有SpriteComponent但是没有GameObject（也就是没有ViewComponent）的Entity，
/// 通过用Entitas内置的 EntityLink 函数将GameObject与Entity链接起来，
/// </summary>
public class AddViewSystem : ReactiveSystem<GameEntity>
{
    // 关联的view的GameObject的层级管理类，单纯的管理到一起，不做状态记录
    private readonly Transform _viewContainer = new GameObject("Game Views").transform;

    // 上下文，Entity的工厂类
    private readonly GameContext _context;

    public AddViewSystem(Contexts contexts) : base(contexts.game)
    {
        _context = contexts.game;
    }

    // 只处理有SpriteComponent的Entity
    protected override ICollector<GameEntity> GetTrigger(IContext<GameEntity> context)
    {
        return context.CreateCollector(GameMatcher.Sprite);
    }

    // 进一步筛选不执行的Entity
    protected override bool Filter(GameEntity entity)
    {
        return entity.hasSprite && !entity.hasView;
    }

    // 系统实现
    protected override void Execute(List<GameEntity> entities)
    {
        foreach (var e in entities)
        {
            GameObject go = new GameObject("Game View");
            go.transform.SetParent(_viewContainer, false);
            e.AddView(go);
            go.Link(e); // 注意这个函数仅在 Entitas.Unity namespace 中
        }
    }
}