using GameFramework;
using GameFramework.Fsm;
using UnityGameFramework.Runtime;

public class HeroLogic : EntityLogic
{
    private IFsm<HeroLogic> m_HeroFsm;
    private FsmComponent Fsm;

    protected HeroLogic()
    {
    }

    protected override void OnInit(object userData)
    {
        base.OnInit(userData);

        Fsm = GameEntry.GetComponent<FsmComponent>();

        // 这个英雄的所有状态类
        var heroStates = new FsmState<HeroLogic>[]
        {
            new HeroIdleState(),
            new HeroWalkState(),
        };

        // 创建状态机
        m_HeroFsm = Fsm.CreateFsm(this, heroStates);

        // 启动状态机
        m_HeroFsm.Start<HeroIdleState>();
    }

    protected override void OnShow(object userData)
    {
        base.OnShow(userData);
        Log.Info("显示Hero Prefab");
    }
}