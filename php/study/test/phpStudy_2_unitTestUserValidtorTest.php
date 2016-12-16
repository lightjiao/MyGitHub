<?php
/**
 * Created by IntelliJ IDEA.
 * User: lights
 * Date: 2016/11/16
 * Time: 下午3:23
 */

var_dump(__FILE__);

include_once dirname(__DIR__)."/phpStudy_2_unitTest.php";

// 用户测试方法测试类
class ValidatorTest extends PHPUnit_Framework_TestCase
{
    /**@var Validator */
    private $validator;

    public function setUp()
    {
        $store = new UserStore();
        $store->addUser("jack", "jack@qq.com", "123");
        $this->validator = new Validator($store);
    }

    public function tearDown()
    {
    }

    // 简单的 断言
    public function testValidator_CorrectPass()
    {
        $this->assertTrue(
            $this->validator->validateUser("jack@qq.com", "123"),
            "Expecting successful validation!"
        );
    }

    // 模拟与桩
    public function testValidate_FalsePass()
    {
        // $store = $this->getMock('UserStore');  // depreate
        $store = $this->createMock('UserStore');  // 动态生成一个类

        $this->validator = new Validator($store);

        $store->expects($this->once())             // 期待调用一次   // 测试点_1
            ->method('notifyPasswordFailure')      // 调用的函数名称
            ->with($this->equalTo("jack@qq.com")); // 调用的入参


        $store->expects($this->any())   // 期待调用 零次 或者 任意次  // 测试点_2
            ->method('getUser')         // 调用的函数名称
            ->will($this->returnValue(array("email" => "jack@qq.com", "pass" => "right"))); // 函数返回值

        $this->validator->validateUser("jack@qq.com", "wrong");
    }
}