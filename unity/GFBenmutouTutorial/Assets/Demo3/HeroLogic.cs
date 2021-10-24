using GameFramework;
using UnityGameFramework.Runtime;

public class HeroLogic : EntityLogic
{
    protected HeroLogic()
    {
    }

    protected override void OnShow(object userData)
    {
        base.OnShow(userData);
        Log.Info("显示Hero Prefab");
    }
}