using GameFramework.Procedure;
using UnityGameFramework.Runtime;
using ProcedureOwner = GameFramework.Fsm.IFsm<GameFramework.Procedure.IProcedureManager>;

public class Demo3_ProcedureMenu : ProcedureBase
{
    protected override void OnEnter(ProcedureOwner procedureOwner)
    {
        base.OnEnter(procedureOwner);

        var ui = GameEntry.GetComponent<UIComponent>();

        ui.OpenUIForm("Assets/Demo3/UI_Menu.prefab", "DefaultGroup");
    }
}