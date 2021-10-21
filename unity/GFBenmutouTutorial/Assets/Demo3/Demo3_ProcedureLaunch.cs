using GameFramework.Procedure;
using UnityGameFramework.Runtime;
using ProcedureOwner = GameFramework.Fsm.IFsm<GameFramework.Procedure.IProcedureManager>;

public class Demo3_ProcedureLaunch : ProcedureBase
{
    protected override void OnEnter(ProcedureOwner procedureOwner)
    {
        base.OnEnter(procedureOwner);

        var scene = GameEntry.GetComponent<SceneComponent>();
        scene.LoadScene("Assets/Demo3/Demo3_Menu.unity", this);
        // scene.LoadScene("Demo3_Menu", this);

        ChangeState<Demo3_ProcedureMenu>(procedureOwner);
    }
}