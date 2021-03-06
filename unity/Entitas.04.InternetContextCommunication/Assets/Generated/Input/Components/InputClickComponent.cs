//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by Entitas.CodeGeneration.Plugins.ComponentEntityApiGenerator.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------
public partial class InputEntity {

    public ClickComponent click { get { return (ClickComponent)GetComponent(InputComponentsLookup.Click); } }
    public bool hasClick { get { return HasComponent(InputComponentsLookup.Click); } }

    public void AddClick(bool newState) {
        var index = InputComponentsLookup.Click;
        var component = (ClickComponent)CreateComponent(index, typeof(ClickComponent));
        component.state = newState;
        AddComponent(index, component);
    }

    public void ReplaceClick(bool newState) {
        var index = InputComponentsLookup.Click;
        var component = (ClickComponent)CreateComponent(index, typeof(ClickComponent));
        component.state = newState;
        ReplaceComponent(index, component);
    }

    public void RemoveClick() {
        RemoveComponent(InputComponentsLookup.Click);
    }
}

//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by Entitas.CodeGeneration.Plugins.ComponentMatcherApiGenerator.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------
public sealed partial class InputMatcher {

    static Entitas.IMatcher<InputEntity> _matcherClick;

    public static Entitas.IMatcher<InputEntity> Click {
        get {
            if (_matcherClick == null) {
                var matcher = (Entitas.Matcher<InputEntity>)Entitas.Matcher<InputEntity>.AllOf(InputComponentsLookup.Click);
                matcher.componentNames = InputComponentsLookup.componentNames;
                _matcherClick = matcher;
            }

            return _matcherClick;
        }
    }
}
