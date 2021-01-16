using Entitas;
using Entitas.Unity;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// 表示是一个有 DestroyedComponent 的entity
/// </summary>
public interface IDestroyableEntity : IEntity, IDestroyedEntity, IViewEntity { }

// 告诉编译器，我们指定的这几个entity都实现了 IDestroyableEntity
public partial class GameEntity : IDestroyableEntity { }

public partial class InputEntity : IDestroyableEntity { }

public partial class UiEntity : IDestroyableEntity { }

public class MultiDestroySystem : MultiReactiveSystem<IDestroyableEntity, Contexts>
{
    public MultiDestroySystem(Contexts contexts) : base(contexts)
    {
    }

    protected override ICollector[] GetTrigger(Contexts contexts)
    {
        return new ICollector[] {
            contexts.game.CreateCollector(GameMatcher.Destroyed),
            contexts.input.CreateCollector(InputMatcher.Destroyed),
            contexts.ui.CreateCollector(UiMatcher.Destroyed),
        };
    }

    protected override bool Filter(IDestroyableEntity entity)
    {
        return entity.isDestroyed;
    }

    protected override void Execute(List<IDestroyableEntity> entities)
    {
        foreach (var e in entities)
        {
            if (e.hasView)
            {
                var go = e.view.gameObject;
                go.Unlink();
                Object.Destroy(go);
            }
            Debug.Log($"Destroyed Entity from {e.contextInfo.name} context");
            e.Destroy();
        }
    }
}