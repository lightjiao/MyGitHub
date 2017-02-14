<?php
/**
 * Created by IntelliJ IDEA.
 * User: lights
 * Date: 2016/11/17
 * Time: 下午4:30
 */

// 因为ElasticSearch 有一些字符比较特殊需要用 \ 转义，比如 + 转换成 \+ ；
function escapeElasticSearchReservedChars($string)
{

    // 因为"\"字符本身也需要转义，所以需要连续的两个"\" 表示 "\"；
    $regex = "/[\\+\\-\\=\\&\\|\\!\\(\\)\\{\\}\\[\\]\\^\\\"\\~\\*\\<\\>\\?\\:\\\\\\/]/";
    $string = preg_replace_callback ($regex,
        function ($matches) {
            return "\\" . $matches[0];
        }, $string);
    return $string;
}
/**
 * output:  The next chars should be escaped\: \+ \- \= \&\& \|\| \> \< \! \( \) \{ \} \[ \] \^ \" \~ \* \? \: \\ \/ Did it work\?
 */
function test_escapeElasticSearchReservedChars_main()
{
    $string = "The next chars should be escaped: + - = && || > < ! ( ) { } [ ] ^ \" ~ * ? : \ / Did it work?";
    echo escapeElasticSearchReservedChars($string);
    echo "\n";
}

/**
 * @memo 第一个测试代码入口
 */
function test_main_1()
{
    test_escapeElasticSearchReservedChars_main();
}


