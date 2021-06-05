using Unity.Entities;

[UpdateInGroup(typeof(SimulationSystemGroup))]
[UpdateBefore(typeof(TargetToDirectionSystem))]
public class AssignPlayerToTargetSystem : SystemBase
{
    protected override void OnStartRunning()
    {
        AssignPlayer();
    }

    protected override void OnUpdate()
    {
    }

    private void AssignPlayer()
    {
        //var playerQuery = GetEntityQuery(typeof(PlayerTag));
        var playerQuery = GetEntityQuery(ComponentType.ReadOnly<PlayerTag>());

        //var playerEntity = playerQuery.ToEntityArray(Allocator.Temp)[0];
        var playerEntity = playerQuery.GetSingletonEntity();

        Entities
            .WithAll<ChaserTag>()
            .ForEach((ref TargetData targetData) =>
            {
                if (playerEntity != Entity.Null)
                {
                    targetData.targetEntity = playerEntity;
                }
            }).Schedule();
    }
}