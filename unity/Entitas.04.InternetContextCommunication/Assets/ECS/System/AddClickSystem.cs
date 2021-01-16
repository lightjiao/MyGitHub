using Entitas;
using System.Collections.Generic;

public sealed class AddClickSystem : ReactiveSystem<InputEntity>
{
    private readonly InputContext _context;

    public AddClickSystem(Contexts contexts) : base(contexts.input)
    {
        _context = contexts.input;
    }

    protected override ICollector<InputEntity> GetTrigger(IContext<InputEntity> context)
    {
        return context.CreateCollector(InputMatcher.Click);
    }

    protected override bool Filter(InputEntity entity)
    {
        return entity.hasInputId;
    }

    protected override void Execute(List<InputEntity> entities)
    {
        /// 通过 InputId 组件的entity找到
        foreach (var e in entities)
        {
            var obj = Contexts.sharedInstance.game.GetEntitiesWithName(e.inputId.value).SingleEntity();
            if (obj != null && obj.hasButtonState)
            {
                obj.ReplaceButtonState(!obj.buttonState.buttonState);
            }
            e.RemoveClick();
        }
    }
}