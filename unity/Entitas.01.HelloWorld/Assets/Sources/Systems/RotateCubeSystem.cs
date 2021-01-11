using Entitas;
using UnityEngine;

public class RotateCubeSystem : IExecuteSystem
{
    // always handy to keep a reference to the context
    // we're going to be interacting with it.
    private readonly GameContext _context;

    private readonly IGroup<GameEntity> cubes;

    public RotateCubeSystem(Contexts contexts)
    {
        _context = contexts.game;
        cubes = _context.GetGroup(GameMatcher.Cube);
    }

    void IExecuteSystem.Execute()
    {
        foreach (var e in cubes.GetEntities())
        {
            e.cube.cube.transform.Rotate(e.cube.rotateAmount * Time.deltaTime);
        }
    }
}