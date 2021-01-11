using UnityEngine;

public class AutoAim : MonoBehaviour
{
    [SerializeField]
    private Transform target;

    // Update is called once per frame
    private void Update()
    {
        var currentQ = transform.rotation;
        var targetQ = Quaternion.LookRotation(target.position);
        var lerpQ = Quaternion.Lerp(currentQ, targetQ, 0.01f);
        //target.position - transform.position

        //transform.localEulerAngles
        //transform.eulerAngles
        //transform.Rotate

        transform.rotation = lerpQ;
    }
}