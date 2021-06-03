using Unity.Entities;
using Unity.Jobs;
using Unity.Mathematics;
using Unity.Transforms;

public class PlayerMoveSystem : SystemBase
{
    protected override void OnUpdate()
    {
        var deltaTime = Time.DeltaTime;

        Entities.ForEach((ref Translation pos, in MoveData moveData) =>
        {
            var normalizedDir = math.normalizesafe(moveData.direction);
            pos.Value += normalizedDir * moveData.speed * deltaTime;
        }
        ).Run();
    }
}