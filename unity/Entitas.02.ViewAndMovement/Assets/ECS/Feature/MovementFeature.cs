public class MovementFeature : Feature
{
    public MovementFeature(Contexts contexts) : base("Movement Feature")
    {
        Add(new MoveSystem(contexts));
    }
}