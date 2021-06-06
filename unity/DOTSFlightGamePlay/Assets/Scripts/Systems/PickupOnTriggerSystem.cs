using Unity.Collections;
using Unity.Entities;
using Unity.Jobs;
using Unity.Physics;
using Unity.Physics.Systems;

/**
 * EntityCommandBuffer
 * - DOTS 中创建或者销毁 Component、Entity 都会影响结构的变化（影响数据在内存中的布局）
 * - 所有结构变化（structural change）都需要通过EntityManager
 * - 所有数据都以 Archetype 的形式组织，添加/删除Entiy、添加/删除Component，内存数据就需要移动到其他Chunk
 * - 结构的变化（创建删除Entity、创建删除Component）不能在 Job 中使用
 * !!
 * - 所以我们需要 EntityCommandBuffer（ECB），它是一个存储command的buffer
 * - 不能在Job中执行的行为，可以放到CommandBuffer，然后在Job结束后在主线程执行
 * - 在EntityDebugger中可以看到有一些内置的CommandBuffer
 *  - BeginInitializationEntityCommandBufferSystem
 *  - EntInitializationEntityCommandBufferSystem
 *  - BeginSimulationEntityCommandBufferSystem
 *  - EndSimulationEntityCommandBufferSystem
 *  - 我们可以实现自己的ECBSystem，但一般情况下这些内置的也足够用了
 * - 一般一个SystemGroup都会有两个ECBSystem，一个Begin，一个End
 */

// 在所有的物理计算结束之后再运行
//[UpdateAfter(typeof(EndFramePhysicsSystem))]
[UpdateAfter(typeof(FixedStepSimulationSystemGroup))]
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

    private EndSimulationEntityCommandBufferSystem commandBufferSystem;

    protected override void OnCreate()
    {
        base.OnCreate();

        buildPhysicsWorld = World.GetOrCreateSystem<BuildPhysicsWorld>();
        stepPhysicsWorld = World.GetOrCreateSystem<StepPhysicsWorld>();
        commandBufferSystem = World.GetOrCreateSystem<EndSimulationEntityCommandBufferSystem>();
    }

    //[BurstCompile] // burst 不在主线程运行（因为这个Systme用到了一些UnityEngine的代码，只会在主线程运行
    private struct PickupOnTriggerSystemJob : ITriggerEventsJob
    {
        // 因为是在Job中，所以需要 [ReadOnly]
        // 如果不设置 [ReadOnly] 的话，其他的job就不能访问它了，直到被释放所有权然后回到主线程（读写锁）
        [ReadOnly] public ComponentDataFromEntity<PickupTag> allPickUps;

        [ReadOnly] public ComponentDataFromEntity<PlayerTag> allPlayers;

        public EntityCommandBuffer entityCommandBuffer;

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
                
                //UnityEngine.Debug.Log($"Pickup Entity A:{entityA}, Collided with Player Entity B: {entityB}");
                entityCommandBuffer.DestroyEntity(entityA);
            }
            else if (allPickUps.HasComponent(entityB) && allPlayers.HasComponent(entityA))
            {
                //UnityEngine.Debug.Log($"Player Entity A:{entityA}, Collided with Pickup Entity B: {entityB}");
                entityCommandBuffer.DestroyEntity(entityB);
            }
        }
    }

    protected override JobHandle OnUpdate(JobHandle inputDeps)
    {
        // 注意这里要在Entity的 PhysicsShape 组件中设置 CollisionResponse = RaiseTriggerEvents
        // 不然不会触发这个Job
        var job = new PickupOnTriggerSystemJob();
        job.allPickUps = GetComponentDataFromEntity<PickupTag>(true);
        job.allPlayers = GetComponentDataFromEntity<PlayerTag>(true);
        job.entityCommandBuffer = commandBufferSystem.CreateCommandBuffer();

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