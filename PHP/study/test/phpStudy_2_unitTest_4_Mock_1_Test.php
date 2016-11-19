<?php
/**
 * Created by IntelliJ IDEA.
 * User: lights
 * Date: 2016/11/19
 * Time: 上午11:04
 */

class SomeClass
{
    public function doSomething()
    {
        //
    }
    public function doSomething_2()
    {
        //
    }

    public function doSomething_3()
    {
        //
    }
}

class StubTest extends PHPUnit_Framework_TestCase
{
    public function testStub()
    {
        // 创建SomeClass 桩件
        $stub = $this->createMock(SomeClass::class);

        // 配置Mock
        $stub->expects($this->any())
            ->method('doSomething')
            ->willReturn('foo');  // will($this->returnValue($value)); // 后者的语法中可以使用变量

        // 调用 + 断言
        $this->assertEquals('foo', $stub->doSomething());


        // 配置mock 2
        $stub->expects($this->any())
            ->method('doSomething_2')
            ->will($this->returnArgument(0)); // returnSelf returnCallback returnMap ...

        $this->assertEquals('foo', $stub->doSomething_2('foo'));
        $this->assertEquals('bar', $stub->doSomething_2('bar'));


        // 配置mock_3 onConsecutiveCalls
        $stub->expects($this->any())
            ->method('doSomething_3')
            ->will($this->onConsecutiveCalls(1, 2, 3)); // 轮流返回值 1，2, 3

        $this->assertEquals(1, $stub->doSomething_3());
        $this->assertEquals(2, $stub->doSomething_3());
        $this->assertEquals(3, $stub->doSomething_3());
    }
}
