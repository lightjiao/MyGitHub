using Entitas;
using Entitas.CodeGeneration.Attributes;
using UnityEngine;

[Input]
public sealed class ClickComponent : IComponent
{
    public bool state;
}

[Input]
public sealed class InputIdComponent : IComponent
{
    /// <summary>
    /// EntityIndex 标识 在生成代码的时候，这个字段的值可以用于找到具体的entity列表
    /// GetEntitiesWithInputId()
    /// 指定了多个字段，会为每个字段单独生成不同的方法
    /// </summary>
    [EntityIndex]
    public string value;
}

[Game]
public sealed class NameComponent : IComponent
{
    [EntityIndex]
    public string value;
}

[Game]
public sealed class ButtonStateComponent : IComponent
{
    public bool buttonState;
}