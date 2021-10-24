using GameFramework;
using GameFramework.Event;
using GameFramework.Procedure;
using UnityGameFramework.Runtime;
using ProcedureOwner = GameFramework.Fsm.IFsm<GameFramework.Procedure.IProcedureManager>;

public class Demo3_ProcedureMenu : ProcedureBase
{
    protected override void OnEnter(ProcedureOwner procedureOwner)
    {
        base.OnEnter(procedureOwner);

        var gfEvent = GameEntry.GetComponent<EventComponent>();
        gfEvent.Subscribe(OpenUIFormSuccessEventArgs.EventId, OnOpenUIFormSuccess);

        var ui = GameEntry.GetComponent<UIComponent>();
        ui.OpenUIForm("Assets/Demo3/UI_Menu.prefab", "DefaultGroup", this);

        Log.Info("ProcedureMenu OnEnter last");

        /*
         * 预期的 async/await 写法：
         * var result = await ui.OpenUIForm()
         * if (result.success)
         * {
         *      OnOpenUIFormSuccess
         * }
         */

        var entity = GameEntry.GetComponent<EntityComponent>();
        entity.ShowEntity<HeroLogic>(1, "Assets/Demo3/HeroCube.prefab", "EntityGroup");

        gfEvent.Subscribe(WebRequestSuccessEventArgs.EventId, WebRequestSuccess);
        var webRequest = GameEntry.GetComponent<WebRequestComponent>();
        webRequest.AddWebRequest("https://www.baidu.com", this);
    }

    private void WebRequestSuccess(object sender, GameEventArgs e)
    {
        var ne = (WebRequestSuccessEventArgs) e;
        Log.Info("Response: " + Utility.Converter.GetString(ne.GetWebResponseBytes()));
    }

    private void OnOpenUIFormSuccess(object sender, GameEventArgs e)
    {
        var ne = (OpenUIFormSuccessEventArgs) e;
        if (ne.UserData != this)
        {
            return;
        }

        Log.Info("UI Menu: 打开UI成功的事件");
    }
}