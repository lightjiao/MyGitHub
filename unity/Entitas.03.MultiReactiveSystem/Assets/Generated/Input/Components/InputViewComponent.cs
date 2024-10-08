//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by Entitas.CodeGeneration.Plugins.ComponentEntityApiGenerator.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------
public partial class InputEntity {

    public ViewComponent view { get { return (ViewComponent)GetComponent(InputComponentsLookup.View); } }
    public bool hasView { get { return HasComponent(InputComponentsLookup.View); } }

    public void AddView(UnityEngine.GameObject newGameObject) {
        var index = InputComponentsLookup.View;
        var component = (ViewComponent)CreateComponent(index, typeof(ViewComponent));
        component.gameObject = newGameObject;
        AddComponent(index, component);
    }

    public void ReplaceView(UnityEngine.GameObject newGameObject) {
        var index = InputComponentsLookup.View;
        var component = (ViewComponent)CreateComponent(index, typeof(ViewComponent));
        component.gameObject = newGameObject;
        ReplaceComponent(index, component);
    }

    public void RemoveView() {
        RemoveComponent(InputComponentsLookup.View);
    }
}

//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by Entitas.CodeGeneration.Plugins.ComponentEntityApiInterfaceGenerator.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------
public partial class InputEntity : IViewEntity { }

//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by Entitas.CodeGeneration.Plugins.ComponentMatcherApiGenerator.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------
public sealed partial class InputMatcher {

    static Entitas.IMatcher<InputEntity> _matcherView;

    public static Entitas.IMatcher<InputEntity> View {
        get {
            if (_matcherView == null) {
                var matcher = (Entitas.Matcher<InputEntity>)Entitas.Matcher<InputEntity>.AllOf(InputComponentsLookup.View);
                matcher.componentNames = InputComponentsLookup.componentNames;
                _matcherView = matcher;
            }

            return _matcherView;
        }
    }
}
