using Entitas;
using UnityEngine;

/// <summary>
/// 将Unity内置的Input系统映射到InputComponent中（which is Unique/Singleton）
/// </summary>
public class EmitInputSystem : IInitializeSystem, IExecuteSystem
{
    private readonly InputContext _context;
    private InputEntity _leftMouseEntity;
    private InputEntity _rightMouseEntity;

    public EmitInputSystem(Contexts contexts)
    {
        /// Component中可以声明标签，
        /// 目前有Game和Input两种，用于区分不同的Context（上下文）
        /// 构造函数传递参数是所有的contexts
        _context = contexts.input;
    }

    void IInitializeSystem.Initialize()
    {
        _context.isLeftMouse = true;
        _leftMouseEntity = _context.leftMouseEntity;

        _context.isRightMouse = true;
        _rightMouseEntity = _context.rightMouseEntity;
    }

    void IExecuteSystem.Execute()
    {
        var mousePosition = Camera.main.ScreenToWorldPoint(Input.mousePosition);

        /// Unique 的Component会直接创建独立的Entity，即 _context.leftMouseEntity
        /// Entity中再添加Component
        /// 即 _leftMouseEntity.ReplaceMouseDown() 这个Component
        /// Replace 可以触发 ReactiveSystem，实现按键的响应

        // left mouse button
        if (Input.GetMouseButtonDown(0))
        {
            _leftMouseEntity.ReplaceMouseDown(mousePosition);
        }

        if (Input.GetMouseButton(0))
        {
            _leftMouseEntity.ReplaceMousePosition(mousePosition);
        }

        if (Input.GetMouseButtonUp(0))
        {
            _leftMouseEntity.ReplaceMouseUp(mousePosition);
        }

        // right mouse button
        if (Input.GetMouseButtonDown(1))
        {
            _rightMouseEntity.ReplaceMouseDown(mousePosition);
        }

        if (Input.GetMouseButton(1))
        {
            _rightMouseEntity.ReplaceMousePosition(mousePosition);
        }

        if (Input.GetMouseButtonUp(1))
        {
            _rightMouseEntity.ReplaceMouseUp(mousePosition);
        }
    }
}