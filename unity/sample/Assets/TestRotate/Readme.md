# 验证一下Unity的旋转是左手螺旋还是右手螺旋

```
vec = Quaternion.AngleAxis(RotateAngle, Vector3.up) * vec;
```
上面这个向量是左手螺旋旋转：
大拇指朝Vector3.up 方向，RotateAngle的角度指代的就是其他四指指向的角度