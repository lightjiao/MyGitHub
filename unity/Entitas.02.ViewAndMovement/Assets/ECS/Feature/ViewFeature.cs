public class ViewFeature : Feature
{
    public ViewFeature(Contexts contexts) : base("View Feature")
    {
        Add(new AddViewSystem(contexts));
        Add(new RenderSpriteSystem(contexts));
        Add(new RenderPositionSystem(contexts));
        Add(new RenderDirectionSystem(contexts));
    }
}