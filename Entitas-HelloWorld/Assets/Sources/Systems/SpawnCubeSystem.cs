using Entitas;
using System.Collections.Generic;
using UnityEngine;

public class SpawnCubeSystem : IInitializeSystem
{
    // always handy to keep a reference to the context
    // we're going to be interacting with it.
    private readonly GameContext _context;

    public SpawnCubeSystem(Contexts contexts)
    {
        _context = contexts.game;
    }

    void IInitializeSystem.Initialize()
    {
        // 假装读表
        // 创建一些Cube
        var cubeSizes = new List<int>
        {
            2
        };

        foreach (var size in cubeSizes)
        {
            var go = GameObject.CreatePrimitive(PrimitiveType.Cube);
            go.transform.localScale = new Vector3(size, size, size);
            go.transform.position = new Vector3(size, size, size);

            var e = _context.CreateEntity();
            e.AddCube(go, size, new Vector3(size, size, size), new Vector3(size, size, size) * 10);
        }
    }
}