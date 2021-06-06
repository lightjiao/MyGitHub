using Unity.Entities;

[GenerateAuthoringComponent]
public struct HealthData : IComponentData
{
    public int currentValue;
    public bool isDead;
}