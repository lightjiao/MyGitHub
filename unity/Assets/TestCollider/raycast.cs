using UnityEngine;

public class raycast : MonoBehaviour
{
    public Collider m_collider;

    // Start is called before the first frame update
    private void Start()
    {
        m_collider = GetComponent<Collider>();
    }

    private void FixedUpdate()
    {
        Debug.Log($"FixedUpdate(): {Time.fixedDeltaTime}");
    }

    // Update is called once per frame
    private void Update()
    {
        Debug.Log($"Update(): {Time.deltaTime}");
        RaycastHit result = new RaycastHit();
        var hit = SingleCast(-Vector3.up, Vector3.zero, -1, ref result);
        if (hit)
        {
            //print(result.point);
            // print(result.distance);
        }
    }

    public bool SingleCast(Vector3 direction, Vector3 offset, int layers, ref RaycastHit result)
    {
        var sphereCollider = m_collider as SphereCollider;
        var radius = sphereCollider.radius;
        var origin = sphereCollider.transform.TransformPoint(sphereCollider.center) + offset;
        if (Physics.SphereCast(origin, radius, direction.normalized, out result, direction.magnitude, layers, QueryTriggerInteraction.Ignore))
        {
            return true;
        }

        return false;
    }
}