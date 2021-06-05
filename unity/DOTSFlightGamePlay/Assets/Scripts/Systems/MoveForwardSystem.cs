using Unity.Entities;
using Unity.Jobs;
using Unity.Mathematics;
using Unity.Transforms;

public class MoveForwardSystem : SystemBase
{
    protected override void OnUpdate()
    {
        var deltaTime = Time.DeltaTime;
        Entities
            .WithAny<AsteriodTag, ChaserTag>()
            .WithNone<PlayerTag>()
            .ForEach((ref Translation pos, in MoveData moveData, in Rotation rot) =>
        {
            var forwardDir = math.forward(rot.Value);
            pos.Value += forwardDir * moveData.speed * deltaTime;
        }).ScheduleParallel();
    }
}