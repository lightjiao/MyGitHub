using Entitas;
using UnityEngine;

public class GameController : MonoBehaviour
{
    private Systems _systems;

    private void Start()
    {
        // get a reference to the contexts
        var contexts = Contexts.sharedInstance;

        // create the systems by creating individual features
        _systems = new Feature("Systems").Add(new TutorialSystems(contexts));

        // call
        _systems.Initialize();
    }

    private void Update()
    {
        // call Execute() on all the IExecutedSystems and
        // ReactiveSystems that were triggered last frame
        _systems.Execute();

        // call cleanup() on all the ICleanupSystems;
        _systems.Cleanup();
    }
}