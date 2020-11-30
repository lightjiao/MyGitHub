using UnityEngine;

public class LerpMove : MonoBehaviour
{
    public Transform origin;
    public Transform target;
    public float lerpValue;

    // Update is called once per frame
    private void Update()
    {
        var newPos = Vector3.Lerp(origin.position, target.position, lerpValue);
        transform.position = newPos;
    }
}