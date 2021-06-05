using Unity.Burst;
using Unity.Collections;
using Unity.Entities;
using Unity.Jobs;
using Unity.Mathematics;
using Unity.Transforms;

public class TargetToDirectionSystem : SystemBase
{
    protected override void OnUpdate()
    {
        Entities
            .WithAll<ChaserTag>()
            .WithNone<PlayerTag>()
            .ForEach((ref Rotation rot, ref MoveData movedata, in Translation pos, in TargetData targetData) =>
            {
                var allPos = GetComponentDataFromEntity<Translation>(true);

                if (false == allPos.HasComponent(targetData.targetEntity))
                {
                    return;
                }

                var tarPos = allPos[targetData.targetEntity];

                var dirToTarget = tarPos.Value - pos.Value;
                movedata.direction = dirToTarget;
            }).Schedule();
    }
}
