using Entitas;
using System.Collections.Generic;

public class CommandMoveSystem : ReactiveSystem<InputEntity>
{
    private readonly GameContext _gameContext;
    private readonly IGroup<GameEntity> _movers;

    public CommandMoveSystem(Contexts contexts) : base(contexts.input)
    {
        _movers = contexts.game.GetGroup(GameMatcher.AllOf(GameMatcher.Mover).NoneOf(GameMatcher.Move));
    }

    protected override ICollector<InputEntity> GetTrigger(IContext<InputEntity> context)
    {
        return context.CreateCollector(InputMatcher.AllOf(InputMatcher.LeftMouse, InputMatcher.MouseDown));
    }

    protected override bool Filter(InputEntity entity)
    {
        return entity.hasMouseDown;
    }

    protected override void Execute(List<InputEntity> entities)
    {
        foreach (InputEntity e in entities)
        {
            GameEntity[] movers = _movers.GetEntities();
            if (movers.Length <= 0) return;

            for (int i = 0; i < movers.Length; i++)
            {
                // 原来的实现是随机选一个Mover跟随
                //movers[Random.Range(0, movers.Length)].ReplaceMove(e.mouseDown.position);

                // 现在的实现是所有的mover都跟随
                movers[i].ReplaceMove(e.mouseDown.position);
            }
        }
    }
}