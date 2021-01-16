using Entitas;
using UnityEngine;

/// <summary>
/// 一个flag component，用于标识是否销毁
/// </summary>
[Game, Input, Ui]
public class DestroyedComponent : IComponent
{
}

[Game, Input, Ui]
public class ViewComponent : IComponent
{
    public GameObject gameObject;
}

/// <summary>
/// 表示即将要添加一个view component
/// </summary>
[Game, Input, Ui]
public class AssignViewComponent : IComponent
{
}