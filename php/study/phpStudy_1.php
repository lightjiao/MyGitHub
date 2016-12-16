<?php
/**
 * Created by IntelliJ IDEA.
 * User: lights
 * Date: 16/10/24
 * Time: 下午2:46
 */

$x = 5;

function MyTest_1_global()
{
    global $x;
    $y = 0;
    echo "test param in function \n";
    echo "param x is:" . $x . "\n";
    echo "param y is:" . $y . "\n\n";
}


function MyTest_2_Static()
{
    static $z = 0;
    echo "$z\n";
    $z ++;
}

$car = array("Volvo", "BMW", "SAAB");

//echo "my car is a {$car[0]}\n";
function MyTest_3_var_dump()
{
    $x = 567;
    var_dump($x);

    $x = -123;
    var_dump($x);

    $x = 0x8C; //16进制
    var_dump($x);

    $x = 047;  //8进制
    var_dump($x);

    $x = 1.123;
    var_dump($x);

    $x = 2.4e3;
    var_dump($x);

    $x = 8E-2;
    var_dump($x);

    $x = array("a", "b", "c");
    var_dump($x); //这里会输出整个的数组结果和结构 ＊ 印象深刻

    $x = NULL;
    var_dump($x); //结果就是NULL， NULL是一个特殊的数据类型
}


class Car
{
    var $color;

    function Car($color = "green")
    {
        $this->color = $color;
    }

    function what_color()
    {
        return $this->color;
    }
}

function MyTest_4_string_about()
{
    echo strlen("Hello") . "\n";

    echo strpos("Hello World", "World") . "\n"; //查找第二个字符串在第一个字符串中的pos
}

/* define() 函数
 * 首个参数定义常量的名称
 * 第二个参数定义常量的值
 * 可选的第三个参数规定常量名是否对大小写敏感。默认是 false */
define("GREETING", "Wellcome to EasyOps");          //这是一个大小写敏感的常量，常量自动属于全局变量，可以当作宏 来理解
define("GREETING_2", "Wellcome to EasyOps", true);  //第三个参数表示 这是一个大小写不敏感的常量

function MyTest_5_define()
{
    echo GREETING . "\n";
    echo GREETINg . "\n"; //不输出 Wellcome to EasyOps， 直接输出字符串"GREETINg"
    echo GREETING_2 . "\n";
    echo GREETIng_2 . "\n";
}

function MyTest_6_string_dot()
{
    $a = "Hello ";
    $a .= "world";
    $b = $a . " _tail";
    echo $a . "\n";
    echo $b . "\n";
}

function MyTest_7_operation()
{
    $a = 10;
    echo $a++ . "\n"; // 10 后递增：先返回$a， 然后$a 加一递增
    echo $a . "\n";   // 11

    $a = 10;
    echo ++$a . "\n"; // 11 前递增：$a 加一递增，然后返回$a
    echo $a . "\n";   // 11
}

function MyTest_8_xor()
{
    //逻辑运算符 与：and，&&；或：or，||； 非：！； 亦或：xor ($x xor $y:如果$x 和$y 有且仅有一个为true，则返回true)
    $x = true;
    $y = true;
    var_dump($x xor $y);

    $x = false;
    $y = false;
    var_dump($x xor $y);

    $x = true;
    $y = false;
    var_dump($x xor $y);
}

function MyTest_9_operation_puls()
{
    //数组相关的运算符
    // $x +   $y ：不覆盖重复的键
    // $x ==  $y ：$x 和$y 拥有相同的键／值对，则返回true
    // $x === $y ：如果$x 和$y 拥有相同的键／值 对，且顺序相同类型相同，则返回true
    // !=  :如果 $x 不等于 $y，则返回 true。
    // !== :如果 $x 与 $y 完全不同，则返回 true。
    $a  = array("a" => "red",   "b" => "green");
    $a2 = array("a" => "red",   "b" => "green");
    $a3 = array("b" => "green", "a" => "red");

    $b  = array("c" => "blue",  "d" => "yello");

    $z  = $a + $b;
    var_dump($z);
    var_dump($a == $a2);
    var_dump($a == $b);
    var_dump($a === $a2);
    var_dump($a === $a3);
}

function MyTest_10_foreach()
{
    $color = array("red", "orange", "yello", "green", "qing", "blue", "......");
    foreach ($color as $value)
    {
        echo $value."\n";
    }

    echo count($color) . "\n";

    $age = array("Bill"=>"35", "Jack"=>"18", "rose"=>20);
    foreach ($age as $key => $value)
    {
        echo "Key = ". $key. ", Value = ". $value. "\n";
    }
}

function MyTest_11_sort()
{
/* sort() - 以升序对数组排序
 * rsort() - 以降序对数组排序
 * asort() - 根据值，以升序对关联数组进行排序
 * ksort() - 根据键，以升序对关联数组进行排序
 * arsort() - 根据值，以降序对关联数组进行排序
 * krsort() - 根据键，以降序对关联数组进行排序*/
}

$globle_param_1 = 1;
$globle_param_2 = 2;

function MyTest_12_super_globle()
{
    //echo $GLOBALS["globle_param_1"] . "\n"; // $GLOBLES 存储了所有的全局变量，甚至可以创建全局变量
    $GLOBALS["globle_param_3"] = 100;

    //$_SERVER 保存关于报头、路径和脚本位置的信息
    echo $_SERVER["PHP_SELF"] ."\n"; // 返回当前脚本的文件名
    echo $_SERVER["SERVER_NAME"] . "\n";
    echo $_SERVER["HTTP_HOST"] . "\n";
    echo $_SERVER["SCRIPT_URI"] . "\n";
    echo $_SERVER["SCRIPT_FILENAME"] . "\n";
    echo $_SERVER["SCRIPT_NAME"] . "\n";
}

function MyTest_13_POST_GET()
{
    //$_REQUEST 用于手机HTML 表单提交的数据
    //下面的例子展示了一个包含输入字段及提交按钮的表单，当用户通过点击提交按钮来提交数据时，
    //表单数据将发送到<form> 标签的action属性中指定的脚本文件。 在这个例子中，我们指定文件本身来处理表单数据。
    //然后我们可以使用 超级全局变量 $_REQUEST 来手机input字段的值：
    /*
    <html>
    <body>
        <form method="post" action="<?php echo $_SERVER['PHP_SELF'];?>">
            Name: <input type="text" name="fname">
            <input type="submit">
        </form>

        <?php
            $name = $_REQUEST['fname'];
            echo $name;
        ?>
    </body>
    </html>
    */

    //$_POST 广泛用于收集提交 method = "post"  的HTML 表单后的表单数据。 $_POST 也常用语传递变量
    //示例 同 $_REQUEST

    //$_GET 可以用于收集提交 HTML 表单 (method = "get") 之后的表单数据
    //      也可以用于手机URL 中发送的数据
    //假设我们有一张页面含有带参数的超链接 ：<a href="test_get.php?subject=PHP&web=W3school.com.cn">测试 $GET</a>
    //当用户点击链接，参数 "subject" 和 "web" 会被发送到 "test_get.php" ，然后在"test_get.php" 通过 $_GET 就可以访问这些值了
    //下面是 test_get.php 中的代码
    //echo "Study " . $_GET['subject'] . " at " . $_GET['web'];

    /*
    GET vs. POST
    GET 和 POST 都创建数组（例如，array( key => value, key2 => value2, key3 => value3, ...)）。此数组包含键/值对，其中的键是表单控件的名称，而值是来自用户的输入数据。
    GET 和 POST 被视作 $_GET 和 $_POST。它们是超全局变量，这意味着对它们的访问无需考虑作用域 - 无需任何特殊代码，您能够从任何函数、类或文件访问它们。
    $_GET 是通过 URL 参数传递到当前脚本的变量数组。
    $_POST 是通过 HTTP POST 传递到当前脚本的变量数组。

    何时使用 GET？
    通过 GET 方法从表单发送的信息对任何人都是可见的（所有变量名和值都显示在 URL 中）。GET 对所发送信息的数量也有限制。限制在大于 2000 个字符。不过，由于变量显示在 URL 中，把页面添加到书签中也更为方便。
    GET 可用于发送非敏感的数据。
    注释：绝不能使用 GET 来发送密码或其他敏感信息！

    何时使用 POST？
    通过 POST 方法从表单发送的信息对其他人是不可见的（所有名称/值会被嵌入 HTTP 请求的主体中），并且对所发送信息的数量也无限制。
    此外 POST 支持高阶功能，比如在向服务器上传文件时进行 multi-part 二进制输入。
    不过，由于变量未显示在 URL 中，也就无法将页面添加到书签。
    提示：开发者偏爱 POST 来发送表单数据。
    接下来让我们看看如何安全地处理 PHP 表单！
    */
}

// 一个验证URL 的正则表达式
if (!preg_match("/\b(?:(?:https?|ftp):\/\/|www\.)[-a-z0-9+&@#\/%?=~_|!:,.;]*[-a-z0-9+&@#\/%=~_|]/i",$website))
{
    $websiteErr = "无效的 URL";
}

function MyTest_14_Arry_Plus()
{
    $a = array(
        array(1,2,3),
        array("a", "b", "c"),
        array("+", "-", "*")
    );
    foreach ($a as $arr)
    {
        foreach ($arr as $value)
        {
            echo $value . "\n";
        }
    }
}

date_default_timezone_set("Asia/Shanghai");

function MyTest_15_date()
{
    echo "today is " . date("Y/m/d h:i:s a") . "\n";

    $d1 = strtotime("20170128");
    $d2 = ceil(($d1 - time()) / 60/ 60/ 24);
    echo "the day to spring festival is ". $d2 . "\n";
}

function MyTest_16_fp()
{
    //echo readfile("webdictionary.txt"). "\n";

    $myfile = fopen("webdictionary.txt", "r") or die("unable to open file\n");

    while (!feof($myfile))
    {
        echo fgets($myfile);
    }
    //echo fread($myfile, filesize("webdictionary.txt")) . "\n";
    fclose($myfile);
}

function checknum($num)
{
    if ($num > 1)
    {
        throw new Exception("value must be 1 or below");
    }
    return true;
}

function MyTest_17_err()
{
    try
    {
        checknum(2);
    }
    catch (Exception $e)
    {
        echo "message: " . $e->getMessage() . "\n";
    }
}

/****************************/
class customException extends Exception
{
    public function errorMessage()
    {
        //error message
        $errorMsg = 'Error on line '.$this->getLine().' in '.$this->getFile()
            .': '.$this->getMessage().' is not a valid E-Mail address';
        return $errorMsg;
    }
}

function MyTest_18_errclass()
{
    $email = "someone@example...com";

    try
    {
        //check if
        if(filter_var($email, FILTER_VALIDATE_EMAIL) === FALSE)
        {
            //throw exception if email is not valid
            throw new customException($email);
        }
    }

    catch (customException $e)
    {
        //display custom message
        echo $e->errorMessage();
    }
}


function MyTest_19_filter()
{
    $int = 123;
    if (!filter_var($int, FILTER_VALIDATE_INT)) {
        echo("Integer is not valid \n");
    }

    //验证一个 整数是否在范围内
    $init_option = array(
        "options" => array(
            "min_range" => 0,
            "max_range" => 256
        )
    );
    if (!filter_var($int, FILTER_VALIDATE_INT, $init_option)) {
        echo "integer is not valid";
    }

    //过滤多个输出
    $filters = array(
        "name" => array(
            "filter" => FILTER_SANITIZE_STRING //这里 A, 这里没有对字符串作校验的方法么？ 或者写入一个正则表达式
        ),
        // "name" => "/^[a-zA-Z ]$/", just like this
        "age" => array(
            "filter" => FILTER_VALIDATE_INT,
            "options" => array(
                "min_range" => 1,
                "max_range" => 120
            )
        ),
        "email" => FILTER_VALIDATE_EMAIL       // 这里 B ，A和B为什么不一样，因为 filter 类型不一样吗？
    );
    //$result = filter_input_array(INPUT_GET, $filters);
    $arr = array("age"=>100, "name"=>"@@@@", "email"=>"abc@qq.com");
    $result = filter_var_array($arr, $filters); //input 函数一定要换成var_arry() 的，如果强行伪装调用input_arry() 要怎么调用呢？
    if (!$result["age"])
    {
        echo "Age must be a number between 1 and 120.\n";
    }
    elseif (!$result["email"])
    {
        echo "email is not valid " . $_GET["email"] . "\n";
    }
    elseif (!$result["name"])
    {
        echo "name balabala~~";
    }
    else
    {
        //echo "User input is valid \n";
    }


    //使用 Filter Callback 调用自定义的函数作过滤
    $string = "Hello_world_!";
    echo filter_var($string, FILTER_CALLBACK, array("options"=>"conver_toSpace")) . "\n";

}
function conver_toSpace($string)
{
    return str_replace("_", " ", $string);
}


function makeRange_err($length)
{
    $dataset = [];
    for ($i =0; $i < $length; $i++)
    {
        //$dataset[] = $i;
        yield $i;
    }

    //return $dataset;
}
function MyTest_20_generator()
{
    foreach (makeRange_err(10) as $v)
    {
        echo $v . "\n";
    }
}


function enclosePerson($name)
{
    return function($command) use($name)
    {
        return sprintf("%s, %s\n", $name, $command);
    };
}
function MyTest_21_bibao()
{
    $jack = enclosePerson('Jack');
    echo $jack('where are you from?');
}


class App
{
    protected $routes = array();

    public function addRoute($routePath, $routeCallback)
    {
        $this->routes[$routePath] = $routeCallback->bindTo($this, __CLASS__);
    }

    public function dispatch($currentPath)
    {
        foreach ($this->routes as $routePath => $callback)
        {
            if ($routePath === $currentPath)
            {
                $callback();
            }
        }

        echo $this->responseBody;
    }
}
function MyTest_22_bindTo()
{
    $app = new App(); // new App; 也可以;
    $app->addRoute('user/jack', function (){
        $this->responseBody = "{'name', 'jack'}";
    });

    $app->dispatch('user/jack');
}

function MyTest_23_HTML()
{
    $html = "<p><script>alter('hello');</script>></p>";
    echo htmlspecialchars($html) . "\n";
    echo htmlentities($html, ENT_QUOTES, 'UTF-8'). "\n";
}


function MyTest_24_SQL()
{
    $pdo = new PDO(
        'mysql:host=127.0.0.1;dbname=books;port=3306;charset=utf8', //实际上配置信息的这种写法不安全，安全的做法是将配置信息单独写在一个文件中并且独立于项目之外
        'USERNAME',
        'PASSWORD'
    );

    $pdo->beginTransaction(); //开始事务
    $sql = "select * from users where email = :email";
    $statement = $pdo->prepare($sql);
    $email = filter_input(INPUT_GET, "email");
    $statement->bindValue(":email", $email);         //安全的绑定sql参数的方法，防止sql 注入攻击 比如 "1 or 1 = 1"等，bindValue() 第三个参数是限制数据的类型的，默认为字符串
    $statement->execute();
    while (($result = $statement->fetch(PDO::FETCH_ASSOC)) != false) //FETCH_ASSOC:令fetch()、fetchAll()返回一个关联的数组。数组的键是数据库的列名 ————二维数组？
    {
        echo $result['email'];
    }
    $pdo->commit(); //提交事务

    $sql2 = "select * from users where id = :id";
    $statement2 = $pdo->prepare($sql2);
    $userid = filter_input(INPUT_GET, "id");
    $statement2->bindValue(":id", $userid, PDO::PARAM_INT); // 常见的PDO数据类型还有, PARAM_BOOL, PARAM_NULL, PARAM_STR
    $statement2->execute();
    $results = $statement2->fetchAll(PDO::FETCH_ASSOC); //处理小型结果集可以使用fetchAll，其他情况建议使用fetch
    foreach ($results as $result)
    {
        echo $result;
    }
}

function MyTest_25_globalException(Exception $e)
{
    echo $e->getCode() ." : " . $e->getMessage();
}

//set_exception_handler("MyTest_25_globalException");

function MyTest_26_Slice()
{

}

class GlobalStream {
    private $pos;
    private $stream;
    public function stream_open($path, $mode, $options, &$opened_path) {
        $url = parse_url($path);
        $this->stream = &$GLOBALS[$url["host"]];
        $this->pos = 0;
        if (!is_string($this->stream)) return false;
        return true;
    }
    public function stream_read($count) {
        $p=&$this->pos;
        $ret = substr($this->stream, $this->pos, $count);
        $this->pos += strlen($ret);
        return $ret;
    }
    public function stream_write($data){
        $l=strlen($data);
        $this->stream =
            substr($this->stream, 0, $this->pos) .
            $data .
            substr($this->stream, $this->pos += $l);
        return $l;
    }
    public function stream_tell() {
        return $this->pos;
    }
    public function stream_eof() {
        return $this->pos >= strlen($this->stream);
    }
    public function stream_seek($offset, $whence) {
        $l=strlen($this->stream);
        switch ($whence) {
            case SEEK_SET: $newPos = $offset; break;
            case SEEK_CUR: $newPos = $this->pos + $offset; break;
            case SEEK_END: $newPos = $l + $offset; break;
            default: return false;
        }
        $ret = ($newPos >=0 && $newPos <=$l);
        if ($ret) $this->pos=$newPos;
        return $ret;
    }
}stream_wrapper_register('global', 'GlobalStream') or die('Failed to register protocol global://');



function MyTest_27_register_stream()
{
    $myvar = "";

    $fp = fopen("global://myvar", "r+");
    echo $fp;

    var_dump($myvar);
    fwrite($fp, "line1 ");
    fwrite($fp, "line2 ");
    fwrite($fp, "line3 ");

    rewind($fp);
    while (!feof($fp)) {
        echo fgets($fp) . "\n";
    }
    fclose($fp);
    var_dump($myvar);
}

class s_tr
{
    public $m_s;

    function __construct($s)
    {
        $this->m_s = $s;
    }

    function add($s)
    {
        $this->m_s .= $s;
        //return $this;
    }
}


/**
 * @param $s s_tr
 */
function aprint($s)
{
    $s->add("*");
    var_dump($s);
}

class Product
{
    public $name;
    public $price;

    function __construct($name, $price)
    {
        $this->name = $name;
        $this->price = $price;
    }
}

function otest1 ($a)
{
    echo( '一个参数' );
}

function otest2 ( $a, $b)
{
    echo( '二个参数' );
}

function otest3 ( $a ,$b,$c)
{
    echo( '三个啦' );
}

function otest (){
    $args = func_get_args();
    $num = func_num_args();
    call_user_func_array( 'otest'.$num, $args  );
}
// otest("11");
// otest("11","22");
// otest("11","22","33");

abstract class DomainObj
{
    private $groupe;
    public function __construct()
    {
        $this->groupe = static::getGroup(); //static 关键字指的是 具体 被调用的类 而不是包含类
        // var_dump($this->groupe);
        // var_dump("DomainObj");
    }

    static function create()
    {
        // return new self();
        return new static();
    }

    static function getGroup()
    {
        return "default";
    }
}

class User extends DomainObj
{
    static function getGroup()
    {
        return "User";
    }
}


function classData(ReflectionClass $class)
{
    $details = "";
    $name = $class->getName();

    if ($class->isUserDefined()) {
        $details .= "$name is user defined\n";
    }

    if ($class->isInternal()) {
        $details .= "$name is build-in\n";
    }
}

class ReflectionUtil
{
    static function getClassSource(ReflectionClass $class) {
        $path = $class->getFileName();
        $lines = @file($path);
        $from = $class->getStartLine();
        $to = $class->getEndLine();
        $len = $to - $from + 1;
        return implode(array_slice($lines, $from - 1, $len));
    }
}

// $portClass = new ReflectionClass("User");
// var_dump(ReflectionUtil::getClassSource($portClass));

$arr = array(1, 2, 3, 4);
var_dump($arr + array(5, 6, 7));
