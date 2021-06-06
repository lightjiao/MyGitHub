using Unity.Collections;
using Unity.Entities;
using Unity.Jobs;
using Unity.Physics;
using Unity.Physics.Systems;

// 在所有的物理计算结束之后再运行
//[UpdateInGroup(typeof(SimulationSystemGroup))]
//[UpdateAfter(typeof(EndFramePhysicsSystem))]
public class PickupOnTriggerSystem : JobComponentSystem
{
    /// <summary>
    /// Setting up the colliders and dynamic entities
    /// </summary>
    private BuildPhysicsWorld buildPhysicsWorld;

    /// <summary>
    /// actually run the simulation
    /// </summary>
    private StepPhysicsWorld stepPhysicsWorld;

    protected override void OnCreate()
    {
        base.OnCreate();

        buildPhysicsWorld = World.GetOrCreateSystem<BuildPhysicsWorld>();
        stepPhysicsWorld = World.GetOrCreateSystem<StepPhysicsWorld>();
    }

    //[BurstCompile] // burst 不在主线程运行（因为这个Systme用到了一些UnityEngine的代码，只会在主线程运行
    private struct PickupOnTriggerSystemJob : ITriggerEventsJob
    {
        // 因为是在Job中，所以需要 [ReadOnly]
        // 如果不设置 [ReadOnly] 的话，其他的job就不能访问它了，直到被释放所有权然后回到主线程（读写锁）
        [ReadOnly] public ComponentDataFromEntity<PickupTag> allPickUps;

        [ReadOnly] public ComponentDataFromEntity<PlayerTag> allPlayers;

        public void Execute(TriggerEvent triggerEvent)
        {
            var entityA = triggerEvent.EntityA;
            var entityB = triggerEvent.EntityB;

            if (allPickUps.HasComponent(entityA) && allPickUps.HasComponent(entityB))
            {
                return;
            }

            if (allPickUps.HasComponent(entityA) && allPlayers.HasComponent(entityB))
            {
                UnityEngine.Debug.Log($"Pickup Entity A:{entityA}, Collided with Player Entity B: {entityB}");
            }
            else if (allPickUps.HasComponent(entityB) && allPlayers.HasComponent(entityA))
            {
                UnityEngine.Debug.Log($"Player Entity A:{entityA}, Collided with Pickup Entity B: {entityB}");
            }
        }
    }

    protected override JobHandle OnUpdate(JobHandle inputDeps)
    {
        var job = new PickupOnTriggerSystemJob();
        job.allPickUps = GetComponentDataFromEntity<PickupTag>(true);
        job.allPlayers = GetComponentDataFromEntity<PlayerTag>(true);

        var jobHandle = job.Schedule(
            stepPhysicsWorld.Simulation,
            ref buildPhysicsWorld.PhysicsWorld,
            inputDeps
            );

        // 保证Job执行结束，将Job的内存所有权从 Native containers 返回给主线程
        // 保证线程安全
        jobHandle.Complete();

        return jobHandle;
    }
}