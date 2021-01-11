using Entitas;

public class HelloWorldSystem : IInitializeSystem
{
    // always handy to keep a reference to the context
    // we're going to be interacting with it.
    private readonly GameContext _context;

    public HelloWorldSystem(Contexts contexts)
    {
        _context = contexts.game;
    }

    void IInitializeSystem.Initialize()
    {
        // Create an entity and give it a DebugMessageComponent with
        // the text "Hello World!" as its data.
        _context.CreateEntity().AddDebugMessage("Hello world");
    }
}