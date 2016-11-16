<?php
/**
 * Created by IntelliJ IDEA.
 * User: lights
 * Date: 2016/11/16
 * Time: 下午3:23
 */

var_dump(__FILE__);

include_once dirname(__DIR__)."/phpStudy_2_unionTest.php";

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

    public function testValidator_CorrectPass()
    {
        $this->assertTrue(
            $this->validator->validateUser("jack@qq.com", "123"),
            "Expecting successful validation!"
        );
    }
}