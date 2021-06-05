using Unity.Entities;
using Unity.Jobs;
using Unity.Mathematics;
using Unity.Transforms;

public class SpinnerSystem : SystemBase
{
    protected override void OnUpdate()
    {
        var deltaTime = Time.DeltaTime;
        Entities
            .WithAll<SpinnerTag>()
            .WithNone<PlayerTag>()
            .ForEach((ref Rotation rot, in MoveData moveData) =>
        {
            var normalizedRot = math.normalize(rot.Value);
            var angleToRotate = quaternion.AxisAngle(math.up(), moveData.turnSpeed * deltaTime);

            rot.Value = math.mul(normalizedRot, angleToRotate);
        }).ScheduleParallel();
    }
}