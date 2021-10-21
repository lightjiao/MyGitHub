using UnityGameFramework.Runtime;

public class Demo3_UIMenuLogic : UIFormLogic
{
    protected override void OnOpen(object userData)
    {
        base.OnOpen(userData);

        Log.Info($"UI Open hello {this.name}");
    }
}