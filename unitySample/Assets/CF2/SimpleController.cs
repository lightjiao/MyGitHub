using ControlFreak2;
using UnityEngine;

public class SimpleController : MonoBehaviour
{
    [SerializeField]
    private float m_Speed = 5f;

    private Vector3 m_Speed2;

    // Start is called before the first frame update
    private void Start()
    {
        m_Speed2 = new Vector3();
    }

    // Update is called once per frame
    private void Update()
    {
        var deltaPos = new Vector3();
        deltaPos += new Vector3(CF2Input.GetAxis("Horizontal"), 0, CF2Input.GetAxis("Vertical"));
        transform.localPosition += deltaPos * Time.fixedDeltaTime * m_Speed;

        if (CF2Input.GetKeyDown(KeyCode.Space))
        {
            Debug.Log("Hello space button.");
        }
    }
}