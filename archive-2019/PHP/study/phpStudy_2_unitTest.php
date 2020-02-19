<?php
/**
 * Created by IntelliJ IDEA.
 * User: lights
 * Date: 2016/11/16
 * Time: 上午10:37.
 */
class UserStore
{
    private $users = array();

    public function addUser($name, $email, $pass)
    {
        if (isset($this->users[$email])) {
            throw new Exception("User {$email} already in the sys!\n");
        }

        if (strlen($pass) < 2) {
            throw new Exception("pass too short\n");
        }

        $this->users[$email] = array(
            'pass' => $pass,
            'email' => $email,
            'name' => $name,
        );

        return true;
    }

    public function notifyPasswordFailure($email)
    {
        if (isset($this->users[$email])) {
            $this->users[$email]['failed'] = time(); // what is this ???
        }
    }

    public function getUser($email)
    {
        return $this->users[$email]; // 为什么要加一个括号？？？
    }
}

// 手工执行的测试
//
// $store = new UserStore();
// $store->addUser("jack", "jack@qq.com", "123");
// $user = $store->getUser("jack@qq.com");
// print_r($user);

// 手工测试类
class Validator
{
    private $store;

    public function __construct(UserStore $store)
    {
        $this->store = $store;
    }

    public function validateUser($email, $pass)
    {
        if (!is_array($user = $this->store->getUser($email))) {
            return false;
        }

        if ($user['pass'] == $pass) {
            return true;
        }

        $this->store->notifyPasswordFailure($email);

        return false;
    }
}
