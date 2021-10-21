using GameFramework.Procedure;
using UnityGameFramework.Runtime;
using ProcedureOwner = GameFramework.Fsm.IFsm<GameFramework.Procedure.IProcedureManager>;

public class Demo2_ProcedureLaunch : ProcedureBase
{
    protected override void OnEnter(ProcedureOwner procedureOwner)
    {
        base.OnEnter(procedureOwner);

        Log.Debug("初始");

        var scene = UnityGameFramework.Runtime.GameEntry.GetComponent<SceneComponent>();
        scene.LoadScene("Assets/Demo2/Demo2_Menu.unity", this);
        ChangeState<Demo2_ProcedureMenu>(procedureOwner);
    }
}