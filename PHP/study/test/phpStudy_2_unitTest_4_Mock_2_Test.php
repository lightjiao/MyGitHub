<?php
/**
 * Created by IntelliJ IDEA.
 * User: lights
 * Date: 2016/11/19
 * Time: 下午12:57
 */

use PHPUnit\Framework\TestCase;

// 测试用类
class Subject
{
    protected $observers = [];
    protected $name;

    public function __construct($name)
    {
        $this->name = $name;
    }

    public function getName()
    {
        return $this->name;
    }

    public function attach(Observer $observer)
    {
        $this->observers[] = $observer;
    }

    protected function notify($argument)
    {
        foreach ($this->observers as $observer) {
            $observer->update($argument);
        }
    }

    public function doSomething()
    {
        // 做点什么
        // ...

        // 通知观察者发生了些什么
        $this->notify('something');
    }

    public function doSomethingBad()
    {
        foreach ($this->observers as $observer) {
            $observer->reportError(42, 'Something bad happened', $this);
        }
    }

    // 其他方法。
}

// 测试用类
class Observer
{
    public function update($argument)
    {
        // 做点什么。
    }

    public function reportError($errorCode, $errorMessage, Subject $subject)
    {
        // 做点什么。
    }

    // 其他方法。
}


// 测试用特性
trait TestTrait
{
    public function concreteMethod()
    {
        return $this->abstractMethod();
    }

    public abstract function abstractMethod();
}



// 单元测试方法
class SubjectTest extends TestCase
{
    public function testObserversAreUpdated()
    {
        // 为 Observer 类建立仿件对象，只模仿 update() 方法。
        $observer = $this->getMockBuilder(Observer::class)
            ->setMethods(['update'])
            ->getMock();

        // 建立预期状况：update() 方法将会被调用一次，
        // 并且将以字符串 'something' 为参数。
        $observer->expects($this->once())  //TODO 测试点 表示update() 期待执行一次
            ->method('update')
            ->with($this->equalTo('something'));

        /**以上为建立测试预测条件，下面的语句才开始正式的测试*/


        // 创建 Subject 对象，并将模仿的 Observer 对象连接其上。
        $subject = new Subject('My subject');
        $subject->attach($observer);

        // 在 $subject 对象上调用 doSomething() 方法，
        // 预期将以字符串 'something' 为参数调用
        // Observer 仿件对象的 update() 方法。
        $subject->doSomething();
    }

    public function testErrorReported()
    {
        // 为observer 类建立仿件，对 reportError() 方法进行模仿
        $observer = $this->getMockBuilder(Observer::class)
            ->setMethods(['reportError'])
            ->getMock();

        $observer->expects($this->once()) //TODO 测试点 表示reportError() 期待执行一次
            ->method('reportError')
            ->with(
                $this->greaterThan(0),
                $this->stringContains('Something Bad'),
                $this->anything()
            );

        /**以上为建立测试预测条件，下面的语句才开始正式的测试*/


        $subject = new Subject('My subject');
        $subject->attach($observer);

        // doSomethingBad 方法应当会通过（observer的）reportError() 方法
        // 向observer报告错误.
        $subject->doSomethingBad();
    }


    public function testFunctionCallTwoTimesWithSpecificArguments()
    {
        $mock = $this->getMockBuilder(stdClass::class)
            ->setMethods(['set'])
            ->getMock();

        $mock->expects($this->exactly(3))
            ->method('set')
            ->withConsecutive(
                [$this->equalTo('foo'), $this->greaterThan(0)],
                [$this->equalTo('bar'), $this->greaterThan(0)],
                ['test', $this->greaterThan(0)]
            );
        // so what is the diff between 'str' and $this->equalTo('str) ??

        $mock->set('foo', 2);
        $mock->set('bar', 3);
        $mock->set('test', 4);

    }


    /**
     * this is very import
     */
    public function testCallback()
    {
        // 为 Observer 类建立仿件，模仿 reportError() 方法
        $observer = $this->getMockBuilder(Observer::class)
            ->setMethods(['reportError'])
            ->getMock();

        $observer->expects($this->once())
            ->method('reportError')
            ->with(
                $this->greaterThan(0),
                $this->stringContains('Something'),
                $this->callback(
                    function($obj)
                    {
                        return is_callable([$obj, 'getName']) && $obj->getName() == 'My subject';
                    }
                )
            );

        $subject = new Subject('My subject');
        $subject->attach($observer);

        // doSomethingBad() 方法应当会通过（observer的）reportError()方法
        // 向 observer 报告错误。
        $subject->doSomethingBad();
    }


    /**
     * Prophecy
     * Prophecy 是个“极为自我却又非常强大且灵活的 PHP 对象模仿框架。
     * 虽然一开始是为了满足 phpspec2 的需要而建立的，但它足够灵活，可以用最小代价用于任何测试框架内。”
     *
     * 更具体可以参考官方文档 https://github.com/phpspec/prophecy#how-to-use-it
     */
    public function testObserversAreUpdated_2()
    {
        $subject = new Subject('My subject');

        // 为observer 建立预言(prophcey)
        $observer = $this->prophesize(Observer::class);

        // 建立预期状况，update 方法将会被调用一次， 并且以something为参数
        $observer->update('something')->shouldBecalled();

        // 揭示预言, 并将仿件绑定到对象主体上
        $subject->attach($observer->reveal());

        $subject->doSomething();
    }




    /**
     * Mock the Trait
     * getMockForTrait() 方法返回一个使用了特定特质(trait)的仿件对象。
     * 给定特质的所有抽象方法将都被模仿。这样就能对特质的具体方法进行测试。
     *
     * 类似的还有getAbstractClass方法....
     */
    public function testConcreteMethod()
    {
        $mock = $this->getMockForTrait(TestTrait::class);

        $mock->expects($this->once())
            ->method('abstractMethod')
            ->will($this->returnValue(true));

        $this->assertTrue($mock->abstractMethod());
    }
}

