public class TutorialSystems : Feature
{
    public TutorialSystems(Contexts contexts) : base("TutorialSystems")
    {
        // Add 的顺序就是执行的顺序
        Add(new HelloWorldSystem(contexts));
        Add(new SpawnCubeSystem(contexts));

        Add(new RotateCubeSystem(contexts));
        Add(new LogMouseClickSystem(contexts));
        Add(new DebugMessageSystem(contexts));

        Add(new CleanupDebugMessageSystem(contexts));
    }
}