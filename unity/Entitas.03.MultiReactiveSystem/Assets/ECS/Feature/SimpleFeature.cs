public class SimpleFeature : Feature
{
    public SimpleFeature(Contexts contexts) : base("Simple Feature")
    {
        Add(new MultiDestroySystem(contexts));
        Add(new MultiAddViewSystem(contexts));
    }
}