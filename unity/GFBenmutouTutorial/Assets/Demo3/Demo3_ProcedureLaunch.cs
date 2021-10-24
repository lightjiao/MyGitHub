using GameFramework.DataTable;
using GameFramework.Event;
using GameFramework.Procedure;
using UnityGameFramework.Runtime;
using ProcedureOwner = GameFramework.Fsm.IFsm<GameFramework.Procedure.IProcedureManager>;

public class Demo3_ProcedureLaunch : ProcedureBase
{
    private bool loadDataTableSuccessFlag;

    protected override void OnEnter(ProcedureOwner procedureOwner)
    {
        base.OnEnter(procedureOwner);

        loadDataTableSuccessFlag = false;

        var scene = GameEntry.GetComponent<SceneComponent>();
        scene.LoadScene("Assets/Demo3/Demo3_Menu.unity", this);

        var gfEvent = GameEntry.GetComponent<EventComponent>();
        gfEvent.Subscribe(LoadDataTableSuccessEventArgs.EventId, OnLoadDataTableSuccess);

        var dataTable = GameEntry.GetComponent<DataTableComponent>();
        var heroDt = (DataTableBase) dataTable.CreateDataTable<DRHero>("DRHero");
        heroDt.ReadData("Assets/Demo3/Hero.csv", this);
    }

    protected override void OnUpdate(ProcedureOwner procedureOwner, float elapseSeconds, float realElapseSeconds)
    {
        base.OnUpdate(procedureOwner, elapseSeconds, realElapseSeconds);

        if (loadDataTableSuccessFlag) ChangeState<Demo3_ProcedureMenu>(procedureOwner);
    }

    private void OnLoadDataTableSuccess(object sender, GameEventArgs e)
    {
        loadDataTableSuccessFlag = true;

        Log.Info("OnLoadDataTableSuccess");

        var dt = GameEntry.GetComponent<DataTableComponent>();

        var heroDt = dt.GetDataTable<DRHero>();
        var heroes = heroDt.GetAllDataRows();
        foreach (var hero in heroes)
        {
            Log.Info($"{hero.Id}, {hero.Name}, {hero.Atk}");
        }
    }
}