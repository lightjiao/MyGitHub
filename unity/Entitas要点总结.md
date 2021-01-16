### Entitas中的ECS

略



### 安装后要做的事情

需要对每个定义的component生成代码，在Tools/Jenny/Preferences

Jenny的Preferences需要设置Contex的数量，用于Component分类（比如分为Game、Input、UI）



### Entitas中独有的概念

#### Context：

创建和管理Entity的集合，所有Entity其实都保存在这里

#### Group：

- 将保存在Context中的Entity做分类，重复访问带有缓存

- Group带有event接口，可以对有Entity变化的时候做出反应，比如新增了一个Entity的时候，这个System可以做一些初始化的操作？

#### Collector

提供了一个对Group中的变化做出反应的类。比如对添加了一个`PositionComponent`的Entity做出反应可以这样写：

```c#
var group = gameContext.GetGroup(GameMatcher.Position);
var collector = group.CreateCollector(GroupEvent.Added); // Group监听添加事件

// 对collector做出反应
foreach(var e in collector.collectedEntities) {
    // 对刚刚添加了Position组件的Entity做一些事情
}
collector.ClearCollectedEntities();

// 停止监听
collector.Deactivate();
```

自带的ReactiveSystem类，`Trigger()`函数返回的就是一个监听`GroupEvent.Added` 的collector



### ❗关于自动化测试

https://github.com/sschmid/Entitas-CSharp/wiki/How-to-setup-a-new-Github-project-with-Unity-and-tests

先跳过不看



### 关于Entitas中System的分类

- `ISystem`，所有System的base interface
- `IInitializeSystem`，只有一个`Initialize()`方法，应当用于开始时执行一次的System
- `IExecuteSystem`，只有一个`Execute()`方法，应当用于每帧执行的System
- `ICleanupSystem`，只有一个`Cleanup()`方法，应当在execute后执行clean的系统，是用于每帧执行的
- `ITearnDownSystem`，只有一个`TearDown()`方法，应当用于结束时执行一次的system，整个System结束
- `IReactiveSystem`，继承于 `IExecuteSystem`，包含 `Active() Deactivate() Clear()` 三个方法，暂无说明
- `JobSystem`多线程调用Execute的系统，暂略
- `MultiReactiveSystem<TEntity, TContexts>` 继承于`IReactiveSystem`，`ReactiveSystem`在指定的Collector有变化的时候才执行，并且只传入有变化的entity。常用于对entity修改的反应，比如entity的位置修改了，那么就去修改与之关联的`gameobject.transform.position`
- `ReactiveSystem<TEntity>` 继承于 `IReactiveSystem`，同上
- `System :IInitializeSystem, IExecuteSystem, ICleanupSystem, ITearDownSystem `，一个封装的便于管理其他system的类，比如就是Feature啦
- 以上说的那么多系统，都可以再自定义添加，比如添加一个`AwakeSytem`专门用于在Awake中执行一些初始化操作



### HelloWorld Totutial总结

- 创建一个`DebugMessageComponent`类，只包含一个打印信息的字符串字段

- 创建一个 `DebugMessageSystem : ReactiveSystem`类，这种System不需要每帧执行，只对`DebugMessageComponent`类添加的时候做出反应，然后就不再执行了，并且`DebugMessageComponent`执行结束后需要被删掉
- 多个System组合在一起可以形成一个Feature，方便在主循环中管理不同的Feature，Feature同时还提供了可视化的Debug工具



### 简单的View与Movement教程

#### 疑问

- **声明Component时，`Unique`是什么含义？**

  表示的是单例，单例的Component可以直接访问带这个Component的Entity，而不需要创建Entity

- 为什么MoveSystem更新的时候，是ReplaceComponent，而不是将原来的Component赋值

  主要是触发 RenderPositionSystem : ReactiveSystem 更新位置和方向


#### 梳理一下当点击了右键，发生了什么吧

- GameController 是一个monobehaviour，不断的执行每个System的Init、Execute、Cleanup

- EmitInputSystem监听Input类的输入，每帧获取鼠标位置，右键点击时，Replace RigheMouseEntity 的`MouseDownComponent`

- CreateMoverSystem是一个ReactiveSystem

  它构造的时候调用`GetTrigger()`函数获取一个collector并保存

  每帧执行时，便利collector，对经过`Filter()`的entity获取到一个buffer中，并且清空collector

  `Execute(buffer)`

  CreateMoverSystem Trigger 获取有 RightMouse 和 MouseDown 的entity，也就是包含RightMouseComponent的RightMouseEntity

  这个filter其实有一些意义不明，获取是为了安全？

  execute中，对每一个entity执行创建mover的entity，并且添加mover、position、direction、sprite的component（其实也就只创建了一个啦）

- 接下来轮到ViewSystem出场了

- AddViewSystem，监听有sprite变化，filter出有sprite但没有view的entity，为这些entity添加一个view（即UnityGameObject，用于添加一个sprite），并将GameObject与这个entity关联起来

  这个关联起来会发生什么呢？

  官方的解释是说可以在Unity的Inspector中看到具体的某一个GameObject里有包含的Entity信息（便于调试）

- RenderSpriteSystem，监听sprite有变化的entity，filter出有view的

  把sprite中定义的精灵真的加载一个资源到view中可以看到

- #### 综上，这样一个小蜜蜂就创建出来了！那么小蜜蜂又是怎样动起来的呢？

#### 左键点击的时候发生了什么

- EmitInputSystem将鼠标左键的输入记录下来

- CommandMoveSystem，统计有Mover（右键创建出来的就有Mover）但没有Move的entity，监听有鼠标左键和鼠标按下的entity（其实只有一个），filter出MouseDown

  对统计好的所有Mover，添加Move，赋值为鼠标左键的位置

  > 这里限制了，不会重复对已经有Move的entity再添加Move，所以小蜜蜂不会一直跟着鼠标左键的点击

- MoveSystem，统计有move和movecomplete的entity

  每帧执行，对所有有Move的entity，让entity的Positin组件按帧移动到Move的位置，通过ReplacePosition和ReplaceDirection

  对移动到目标点的的entity删除Move组件，添加MoveComplete组件

  移动结束后，再把MoveComplete移除掉

- RenderPosition，监听position有变化，filter出有view的entity

  把position中的位置信息真的赋值给view（gameobject.transform）

- RenderDirectionSystem，监听direction有变化，filter有view的entity

  

### MultiReactiveSystem Tutorial教程总结

Entitas 0.42版本引入了这个System，可以使得一个ReactiveSystem同时在多个Context（上下文）对实体进行操作。比如一个销毁Entity的系统就是在多个Context（上下文）中生效的，视图系统也同样如此。

- 对于定义了多个context的component，Entitas在生成代码时，会额外生成一个interface，来表示包含这个component的entity，这样写代码的时候，有一层interface的抽象就不用区分这个Entity是来自哪个Context

  （比如下面这个component表示`Game` `UI` `Input`三个Context的Entity都可以使用）

  ```c#
  // 定义了一个多个context都可以用的component
  [Game, Input, Ui]
  public class DestroyedComponent : IComponent 
  {
  }
  
  // 会生成这样一个接口
  // 这个接口会包含 isDestroyed 属性是因为这个接口表示的是 拥有 DestroyedComponent 的 Entity, 而 DestroyedComponent 是一个flag component
  public partial interface IDestroyedEntity 
  {
      bool isDestroyed { get; set; }
  }
  ```

  

### Inter Context communication 教程总结

- `[EntityIndex]` 属性，加在Component的字段上，然后可以用这个字段的内容查找到具体的entity列表

  

