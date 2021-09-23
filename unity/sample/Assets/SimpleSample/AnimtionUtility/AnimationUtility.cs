using Animancer;
using UnityEngine;

/// <summary>
/// 测试一下 AnimationUtility 的几个API到底是啥
/// </summary>
public class AnimationUtility : MonoBehaviour
{
    [SerializeField] private AnimationClip clip;

    private AnimancerComponent animancer;

    private void Awake()
    {
        // 可以理解为 AnimationClip 存储的是 CurveBind + Curve
        // CurveBind 含义是GameObject中对应的属性，比如 Transform.m_Position.x，
        //                 或者子物体（表现为路径）的属性，比如 ChildOne.Transform.m_Position.x
        // Curve 就是一个Bind对应的曲线

        animancer = GetComponent<AnimancerComponent>();

        animancer.Play(clip);
        
        // var a = UnityEditor.AnimationUtility.GetObjectReferenceCurve(clip, EditorCurveBinding.FloatCurve());
        var curveBindings = UnityEditor.AnimationUtility.GetCurveBindings(clip);
        print(curveBindings);
        var c = UnityEditor.AnimationUtility.GetEditorCurve(clip, curveBindings[0]);

        // 不过，什么是一个ObjectReferenceCurveBiding 就不是很懂了
        var d = UnityEditor.AnimationUtility.GetObjectReferenceCurveBindings(clip);
        
        print(d);
    }
}