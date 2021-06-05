using Unity.Entities;
using Unity.Jobs;
using Unity.Mathematics;
using Unity.Transforms;

public class FaceDirectionSystem : SystemBase
{
    protected override void OnUpdate()
    {
        var deltaTime = Time.DeltaTime;
        Entities.ForEach((ref Rotation rot, in Translation pos, in MoveData moveData) =>
        {
            if (moveData.direction.Equals(float3.zero))
            {
                return;
            }

            var targetRotation = quaternion.LookRotationSafe(moveData.direction, math.up());
            rot.Value = math.slerp(rot.Value, targetRotation, moveData.turnSpeed);
        }).Run();
    }
}