using Entitas.Unity;
using UnityEngine;
using UnityEngine.Events;
using UnityEngine.EventSystems;

public class ClickEvent : UnityEvent<ButtonWidget> { }

public class ButtonWidget : MonoBehaviour, IPointerClickHandler
{
    [SerializeField]
    protected Color onClickColour = Color.green;

    protected Color originalOffColour;
    protected Color offColour;

    public ClickEvent OnClick;
    private bool _state = false;

    void IPointerClickHandler.OnPointerClick(PointerEventData eventData)
    {
        OnClick?.Invoke(this);
    }

    //private void OnEnable()
    //{
    //    if (OnClick == null)
    //    {
    //        OnClick = new ClickEvent();
    //    }

    //    OnClick.AddListener(FindLocalNet)

    //    OnClick?.Invoke()
    //}

    public GameEntity GetGameEntity()
    {
        return gameObject.GetEntityLink().entity as GameEntity;
    }

    public string GetId()
    {
        return GetGameEntity().name.value;
    }

    public bool GetState()
    {
        return GetGameEntity().buttonState.buttonState;
    }

    public void SetState(bool state)
    {
        _state = state;
        var renderer = gameObject.GetComponent<Renderer>();
        if (renderer == null) return;

        offColour = _state ? onClickColour : originalOffColour;
        renderer.material.color = offColour;
    }
}