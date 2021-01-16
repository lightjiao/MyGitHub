using Entitas;
using Entitas.Unity;
using System.Collections.Generic;
using UnityEngine;

public interface IViewableEntity : IEntity, IViewEntity, IAssignViewEntity { }

public partial class GameEntity : IViewableEntity { }

public partial class InputEntity : IViewableEntity { }

public partial class UiEntity : IViewableEntity { }

public class MultiAddViewSystem : MultiReactiveSystem<IViewableEntity, Contexts>
{
    private readonly Transform _topViewContainer = new GameObject("Views").transform;
    private readonly Dictionary<string, Transform> _viewContainers = new Dictionary<string, Transform>();
    private readonly Contexts _contexts;

    public MultiAddViewSystem(Contexts contexts) : base(contexts)
    {
        _contexts = contexts;
        foreach (var context in contexts.allContexts)
        {
            var contextName = context.contextInfo.name;
            var contextViewContainer = new GameObject($"{contextName} Views").transform;
            contextViewContainer.SetParent(_topViewContainer);
            _viewContainers.Add(contextName, contextViewContainer);
        }
    }

    protected override ICollector[] GetTrigger(Contexts contexts)
    {
        return new ICollector[] {
            contexts.game.CreateCollector(GameMatcher.AssignView),
            contexts.input.CreateCollector(InputMatcher.AssignView),
            contexts.ui.CreateCollector(UiMatcher.AssignView)
        };
    }

    protected override bool Filter(IViewableEntity entity)
    {
        return entity.isAssignView && !entity.hasView;
    }

    protected override void Execute(List<IViewableEntity> entities)
    {
        foreach(var e in entities)
        {
            var contextName = e.contextInfo.name;
            var go = new GameObject($"{contextName} View");
            go.transform.SetParent(_viewContainers[contextName]);
            e.AddView(go);
            go.Link(e);
            e.isAssignView = false;
        }
    }
}