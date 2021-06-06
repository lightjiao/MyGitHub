using Unity.Entities;
using Unity.Jobs;
using Unity.Transforms;

// 在entity可以移动之前，判断entity是否死亡，然后移除
[UpdateBefore(typeof(TransformSystemGroup))]
public class RemoveOnDeathSystem : SystemBase
{
    private EndSimulationEntityCommandBufferSystem commandBufferSystem;

    protected override void OnCreate()
    {
        base.OnCreate();
        commandBufferSystem = World.GetOrCreateSystem<EndSimulationEntityCommandBufferSystem>();
    }

    protected override void OnUpdate()
    {
        var entityCommandBuffer = commandBufferSystem.CreateCommandBuffer();

        // 入参 Entity entity 指代拥有这些Component的entity，
        Entities.ForEach((Entity entity, in HealthData healthData) =>
        {
            if (healthData.isDead)
            {
                entityCommandBuffer.DestroyEntity(entity);
            }
        }).Schedule();

        commandBufferSystem.AddJobHandleForProducer(this.Dependency);
    }
}