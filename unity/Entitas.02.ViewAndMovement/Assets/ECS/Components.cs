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
    public GameObject gameobject;
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

// 表示Entity移动结束
[Game]
public class MoveCompleteComponent : IComponent
{
}

#region 输入相关的Component

// Unique表示只有一个
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