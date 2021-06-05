using Unity.Entities;
using Unity.Jobs;
using Unity.Mathematics;
using Unity.Transforms;

[UpdateAfter(typeof(TransformSystemGroup))]
public class FaceDirectionSystem : SystemBase
{
    protected override void OnUpdate()
    {
        Entities
            .ForEach((ref Rotation rot, in Translation pos, in MoveData moveData) =>
            {
                FaceDirection(ref rot, moveData);
            }).Schedule();
    }

    /// <summary>
    ///
    /// </summary>
    /// <param name="rot"></param>
    /// <param name="moveData"></param>
    /// <remarks>
    /// 由于这个方法被 Entities.ForEach() 中的lambda引用，所以必须是 static 方法
    /// </remarks>

    private static void FaceDirection(ref Rotation rot, in MoveData moveData)
    {
        if (moveData.direction.Equals(float3.zero))
        {
            return;
        }

        var targetRotation = quaternion.LookRotationSafe(moveData.direction, math.up());
        rot.Value = math.slerp(rot.Value, targetRotation, moveData.turnSpeed);
    }
}