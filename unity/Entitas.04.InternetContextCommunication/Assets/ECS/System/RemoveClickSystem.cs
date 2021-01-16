using Entitas;
using System.Collections.Generic;

public sealed class RemoveClickSystem : ReactiveSystem<InputEntity>
{
    private readonly InputContext _context;

    public RemoveClickSystem(Contexts contexts) : base(contexts.input)
    {
        _context = contexts.input;
    }

    protected override ICollector<InputEntity> GetTrigger(IContext<InputEntity> context)
    {
        return context.CreateCollector(new TriggerOnEvent<InputEntity>(InputMatcher.Click, GroupEvent.Removed));
    }

    protected override bool Filter(InputEntity entity)
    {
        return entity.isEnabled;
    }

    protected override void Execute(List<InputEntity> entities)
    {
        foreach (var e in entities)
        {
            e.Destroy();
        }
    }
}