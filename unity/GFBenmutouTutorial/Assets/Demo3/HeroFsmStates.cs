using GameFramework.Fsm;
using UnityEngine;
using UnityGameFramework.Runtime;

public class HeroIdleState : FsmState<HeroLogic>
{
    protected override void OnEnter(IFsm<HeroLogic> fsm)
    {
        Log.Info("进入Idle 状态");
    }

    protected override void OnUpdate(IFsm<HeroLogic> fsm, float elapseSeconds, float realElapseSeconds)
    {
        var inputVertical = Input.GetAxis("Vertical");
        if (false == Mathf.Approximately(inputVertical, 0f))
        {
            ChangeState<HeroWalkState>(fsm);
        }
    }
}

public class HeroWalkState : FsmState<HeroLogic>
{
    protected override void OnEnter(IFsm<HeroLogic> fsm)
    {
        Log.Info("进入 Walk 状态");
    }

    protected override void OnUpdate(IFsm<HeroLogic> fsm, float elapseSeconds, float realElapseSeconds)
    {
        var inputVertical = Input.GetAxis("Vertical");
        if (Mathf.Approximately(inputVertical, 0f))
        {
            ChangeState<HeroIdleState>(fsm);
        }
        else
        {
            Log.Info("保持行走");
        }
    }
}