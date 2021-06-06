using Unity.Collections;
using Unity.Entities;
using Unity.Jobs;
using Unity.Physics;
using Unity.Physics.Systems;

[UpdateAfter(typeof(EndFramePhysicsSystem))]
[UpdateBefore(typeof(RemoveOnDeathSystem))]
public class DeathOnCollisionSystem : JobComponentSystem
{
    private BuildPhysicsWorld buildPhysicsWorld;
    private StepPhysicsWorld stepPhysicsWorld;

    protected override void OnCreate()
    {
        base.OnCreate();
        buildPhysicsWorld = World.GetOrCreateSystem<BuildPhysicsWorld>();
        stepPhysicsWorld = World.GetOrCreateSystem<StepPhysicsWorld>();
    }

    private struct DeathOnCollisionSystemJob : ICollisionEventsJob
    {
        [ReadOnly] public ComponentDataFromEntity<DeathColliderTag> deathColliderGroup;
        [ReadOnly] public ComponentDataFromEntity<ChaserTag> chaserGroup;

        // 这个数据需要写
        public ComponentDataFromEntity<HealthData> healthGroup;

        public void Execute(CollisionEvent collisionEvent)
        {
            var entityA = collisionEvent.EntityA;
            var entityB = collisionEvent.EntityB;

            var aIsChaser = chaserGroup.HasComponent(entityA);
            var aIsDeathCollider = deathColliderGroup.HasComponent(entityA);
            var bIsChaser = chaserGroup.HasComponent(entityB);
            var bIsDeathCollider = deathColliderGroup.HasComponent(entityB);

            if (aIsDeathCollider && bIsChaser)
            {
                var modifiedHealth = healthGroup[entityB];
                modifiedHealth.isDead = true;
                healthGroup[entityB] = modifiedHealth;
            }

            if (aIsChaser && bIsDeathCollider)
            {
                var modifiedHealth = healthGroup[entityA];
                modifiedHealth.isDead = true;
                healthGroup[entityA] = modifiedHealth;
            }
        }
    }

    protected override JobHandle OnUpdate(JobHandle inputDeps)
    {
        var job = new DeathOnCollisionSystemJob();
        job.deathColliderGroup = GetComponentDataFromEntity<DeathColliderTag>(true);
        job.chaserGroup = GetComponentDataFromEntity<ChaserTag>(true);
        job.healthGroup = GetComponentDataFromEntity<HealthData>(false);

        var jobHandle = job.Schedule(stepPhysicsWorld.Simulation, ref buildPhysicsWorld.PhysicsWorld,
            inputDeps);
        jobHandle.Complete();

        return jobHandle;
    }
}