<?php
/**
 * Created by IntelliJ IDEA.
 * User: lights
 * Date: 2016/11/19
 * Time: 上午9:40.
 */
class FixtureTest extends PHPUnit_Framework_TestCase
{
    public static function setUpBeforeClass()
    {
        fwrite(STDOUT, __METHOD__."\n");
    }

    protected function setUp()
    {
        fwrite(STDOUT, __METHOD__."\n");
    }

    protected function assertPreConditions()
    {
        fwrite(STDOUT, __METHOD__."\n");
    }

    public function testOne()
    {
        fwrite(STDOUT, __METHOD__."\n");
        $this->assertTrue(true);
    }

    public function testTwo()
    {
        fwrite(STDOUT, __METHOD__."\n");
        $this->assertTrue(true);
    }

    protected function assertPostConditions()
    {
        fwrite(STDOUT, __METHOD__."\n");
    }

    protected function tearDown()
    {
        fwrite(STDOUT, __METHOD__."\n");
    }

    public static function tearDownAfterClass()
    {
        fwrite(STDOUT, __METHOD__."\n");
    }

    protected function onNotSuccessfulTest($e)
    {
        fwrite(STDOUT, __METHOD__."\n");
        throw $e;
    }
}
