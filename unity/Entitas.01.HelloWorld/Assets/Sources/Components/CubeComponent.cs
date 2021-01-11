using Entitas;
using UnityEngine;

[Game]
public class CubeComponent : IComponent
{
    public GameObject cube;
    public int size;
    public Vector3 position;
    public Vector3 rotateAmount;
}