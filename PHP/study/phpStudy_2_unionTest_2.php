<?php
/**
 * Created by IntelliJ IDEA.
 * User: lights
 * Date: 2016/11/18
 * Time: 下午12:59
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
    public function testEmpty(){
        $stack = [];
        $this->assertEmpty($stack);

        return $stack;
    }

     /**
     * @depends testEmpty
     */
    public function testPush(array $stack){
        array_push($stack, 'foo');
        $this->assertEquals('foo', $stack[count($stack) - 1]);
        $this->assertEquals(1, count($stack));  // count? this->count?

        return $stack;
    }

    /**
     * @depends testPush
     */
    public function testPop(array $stack){
        $this->assertEquals('foo', array_pop($stack));
        $this->assertEquals(0, count($stack));
    }






    /*
     * 单元测试_2 多依赖情况的单元测试
     */
    public function testProducerOne(){
        $this->assertTrue(true);
        return 'one';
    }
    public function testProducerTwo(){
        $this->assertFalse(false);
        return 'two';
    }

    /**
     * @depends testProducerOne
     * @depends testProducerTwo
     */
    public function testConsumer(){
        // var_dump(__LINE__);
        $this->assertEquals(
            ['one', 'two'],
            func_get_args()
        );
    }




    /*
     * 单元测试_3 数据供给器
     */
    public function additionProvider(){
        return [
            "adding zeros" => [0, 0, 0],
            "zero plus one" => [0, 1, 1],
            "one plus zero" => [0, 1, 1],
            "one plus one " => [1, 1, 3]
        ];
    }

    /**
     * @dataProvider additionProvider
     */
    public function testAdd($a, $b, $expected)
    {
        $this->assertEquals($expected, $a + $b);
    }
}