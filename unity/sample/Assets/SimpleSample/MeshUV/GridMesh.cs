using System.Collections;
using UnityEngine;

/// <summary>
/// 自定义一个网格的Mesh
/// </summary>
[RequireComponent(typeof(MeshFilter), typeof(MeshRenderer))]
public class GridMesh : MonoBehaviour
{
    public int xSize = 10;
    public int ySize = 5;

    private Vector3[] vertices;
    private Mesh mesh;

    private void Awake()
    {
        Generate();
    }

    private void Generate()
    {
        GetComponent<MeshFilter>().mesh = mesh = new Mesh();
        mesh.name = "Procedural Grid";

        vertices = new Vector3[(xSize + 1) * (ySize + 1)];
        var uv = new Vector2[vertices.Length];
        var tangents = new Vector4[vertices.Length];
        var tangent = new Vector4(1f, 0f, 0f, -1f);
        for (int i = 0, y = 0; y <= ySize; y++)
        {
            for (int x = 0; x <= xSize; x++, i++)
            {
                vertices[i] = new Vector3(x, y);
                uv[i] = new Vector2((float) x / xSize, (float) y / ySize);
                // uv[i] = new Vector2(Random.value, Random.value);
                tangents[i] = tangent;
            }
        }

        mesh.vertices = vertices;

        // 虽然我们设置了Mesh的材质，但不指定UV坐标的话，贴图材质找不到合适的方式“贴”在模型上
        mesh.uv = uv;

        mesh.tangents = tangents;

        int[] triangles = new int[xSize * ySize * 6];
        for (int ti = 0, vi = 0, y = 0; y < ySize; y++, vi++)
        {
            for (int x = 0; x < xSize; x++, ti += 6, vi++)
            {
                triangles[ti] = vi;
                triangles[ti + 3] = triangles[ti + 2] = vi + 1;
                triangles[ti + 4] = triangles[ti + 1] = vi + xSize + 1;
                triangles[ti + 5] = vi + xSize + 2;
            }
        }

        mesh.triangles = triangles;

        // 重新计算顶点的法线
        // 通过计算与顶点连接的三角形的法线，对它们求平均并归一化，即为当前顶点的法线
        mesh.RecalculateNormals();
    }

    private void OnDrawGizmos()
    {
        if (vertices == null) return;
        foreach (var vec in vertices)
        {
            Gizmos.DrawSphere(vec + transform.position, 0.1f);
        }
    }
}