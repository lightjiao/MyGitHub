using Entitas;
using Entitas.CodeGeneration.Attributes;
using UnityEngine;

[Game]
public class PositionComponent : IComponent
{
    public Vector2 value;
}

[Game]
public class DirectionComponent : IComponent
{
    public float value;
}

// 持有GameObject
[Game]
public class ViewComponent : IComponent
{
    public GameObject gameObject;
}

// 存储Sprite
[Game]
public class SpriteComponent : IComponent
{
    public string name;
}

// 表示可以移动的Entity
[Game]
public class MoverComponent : IComponent
{
}

// 表示移动的目标点
[Game]
public class MoveComponent : IComponent
{
    public Vector2 target;
}

/// <summary>
/// 表示Entity移动结束
/// 不是单纯的将MoveComponent移除掉来表示移动停止，移动停止有可能是因为移动被其他系统终止了，
/// 比如换了一个移动目标，或者单纯的将移动取消掉
/// 所以需要有一个表示移动Complete的组件
/// </summary>

[Game]
public class MoveCompleteComponent : IComponent
{
}

#region 输入相关的Component

/// <summary>
/// Unique的含义表示全局唯一，可以直接在Context中访问（即Singleton类型的Component）
/// </summary>
[Input, Unique]
public class LeftMouseComponent : IComponent
{
}

[Input, Unique]
public class RightMouseComponent : IComponent
{
}

[Input]
public class MouseDownComponent : IComponent
{
    public Vector2 position;
}

[Input]
public class MouseUpComponent : IComponent
{
    public Vector2 position;
}

[Input]
public class MousePositionComponent : IComponent
{
    public Vector2 position;
}


#endregion 输入相关的Component