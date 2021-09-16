using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MeshUVAdjuster : MonoBehaviour
{
    public MeshFilter meshFilter;

    private Mesh mCacheMesh;

    private Vector2[] mCacheUVArray;

    private void OnEnable()
    {
        MeshScaleCache();
    }

    private void Update()
    {
        MeshScaleUpdate();
    }

    // 缓存初始UV
    private void MeshScaleCache()
    {
        mCacheMesh = meshFilter.mesh;

        var meshUV = mCacheMesh.uv;
        mCacheUVArray = new Vector2[meshUV.Length];
        for (var i = 0; i < meshUV.Length; i++)
        {
            mCacheUVArray[i] = meshUV[i];
        }
    }

    private void MeshScaleUpdate()
    {
        const float MAX_X_SCALE = 5f;

        var scaleRatio = transform.lossyScale.x / MAX_X_SCALE;
        var uv = mCacheMesh.uv;
        for (var i = 0; i < uv.Length; i++)
        {
            uv[i].x = mCacheUVArray[i].x * scaleRatio;
        }

        mCacheMesh.uv = uv;
    }
}