<?php
/**
 * Created by IntelliJ IDEA.
 * User: lights
 * Date: 2016/11/18
 * Time: 下午12:59.
 */
class StackTest extends PHPUnit_Framework_TestCase
{
    /*
     * 单元测试_1 依赖 @depends
     * 用@depends 标注来表达依赖关系
     * 默认情况下，生产者所产生的返回值将“原样”传递给相应的消费者。
     * 这意味着，如果生产者返回的是一个对象，那么传递给消费者的将是一个指向此对象的引用。
     * 如果需要传递对象的副本而非引用，则应当用 @depends clone 替代 @depends。
     */
    public function testEmpty()
    {
        $stack = [];
        $this->assertEmpty($stack);

        return $stack;
    }

    /**
     * @depends testEmpty
     */
    public function testPush(array $stack)
    {
        array_push($stack, 'foo');
        $this->assertEquals('foo', $stack[count($stack) - 1]);
        $this->assertEquals(1, count($stack));  // count? this->count?

        return $stack;
    }

    /**
     * @depends testPush
     */
    public function testPop(array $stack)
    {
        $this->assertEquals('foo', array_pop($stack));
        $this->assertEquals(0, count($stack));
    }

    /*
     * 单元测试_2 多依赖情况的单元测试
     */
    public function testProducerOne()
    {
        $this->assertTrue(true);

        return 'one';
    }

    public function testProducerTwo()
    {
        $this->assertFalse(false);

        return 'two';
    }

    /**
     * @depends testProducerOne
     * @depends testProducerTwo
     */
    public function testConsumer()
    {
        // var_dump(__LINE__);
        $this->assertEquals(
            ['one', 'two'],
            func_get_args()
        );
    }

    /*
     * 单元测试_3 数据供给器
     */
    public function additionProvider()
    {
        return [
            'adding zeros' => [0, 0, 0],
            'zero plus one' => [0, 1, 1],
            'one plus zero' => [0, 1, 1],
            'one plus one ' => [1, 1, 2],
        ];
    }

    /**
     * @dataProvider additionProvider
     */
    public function testAdd($a, $b, $expected)
    {
        $this->assertEquals($expected, $a + $b);
    }

    /*
     * 单元测试_4 数据供给器 + 依赖 (供给器有限)
     * 如果测试同时从 @dataProvider 方法和一个或多个 @depends 测试接收数据，
     * 那么来自于数据供给器的参数将先于来自所依赖的测试的。
     * 来自于所依赖的测试的参数对于每个数据集都是一样的
     */
    public function provider()
    {
        // return [['provider1'], ['provider2']];
        // 这种情况下会返回两次参数给后续的函数，是两次而不是两个
        return [['provider1']];
    }

    /**
     * @depends testProducerOne
     * @depends testProducerTwo
     * @dataProvider provider
     */
    public function testConsumer_()
    {
        $this->assertEquals(
            ['provider1', 'one', 'two'],
            func_get_args()
        );
    }

    /*
     * 单元测试_5 对异常进行测试
     */

    /**
     * @expectedException
     */
    public function testException()
    {
        // $this->expectException(self::throwException("aaa")); // 不是很懂这里的语法

        self::throwException(new Exception('aaa'));
    }

    /**
     * @expectedException \PHPUnit_Framework_Error
     */
    public function testFailingInclude()
    {
        include_once 'asdasfbsadfhjadhsdjkansdkshfio';
    }

    /*
     * 单元测试_6 数据的比较方法
     */
    public function testArray()
    {
        $this->assertEquals(
            [1, 2, 3], // 此处的 数字1 和字符 '1' 被视为相等，需要传入额外的入参
            ['1', 2, 3]
        );

        $this->assertSame([1, 2, 3], [1, 2, 3]); // 会显示的表示 1 与 '1' 不一样
    }
}
