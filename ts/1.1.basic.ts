// 基础类型

// -------------------
// 模板字符串
let myName: string = "Tom";
let myAge: number = 25;
let sentence: string = `Hello my name is ${myName}
I'll be ${myAge + 1} years old next month`;
console.log(sentence);

// -------------------
// 空值
// JS中没有void概念，TS中可以用void表示函数的返回
function alertName(): void {
    alert("My name is light");
}

// -------------------
// 任意值(Any)
// 普通类型，赋值过程中不允许改变类型，任意值类型在赋值过程中可以改变类型
// let myFavoriateNumber: string = "light";
// myFavoriateNumber = 7; // 会报错
// 是any类型则可以
let myFavoriateNumber: any = "light";
myFavoriateNumber = 7;

// 类型推论
// 其实就是自动声明类型
let thisIsAString = "string";

// 联合类型
// 指定一个变量只可以是指定的几个类型，不能是其他类型
let thisIsNumOrStr: number | string;
// 当 TypeScript 不确定一个联合类型的变量到底是哪个类型的时候，我们只能访问此联合类型的所有类型里共有的属性或方法：
