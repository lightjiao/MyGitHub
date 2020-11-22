function LearnFunction() {
    // 函数是JS中的一等公民
    // ! 在TS中, 输入多余的或者少于要求的参数，是不被允许的

    // 这种写法叫函数声明(Function Declaration)
    function sum(x: number, y: number): number {
        return x + y;
    }

    // 这种写法叫函数表达式(Function Expression)
    let mySum = function (x: number, y: number): number {
        return x + y;
    };

    // ! 用接口定义函数的形状, 这种写法看不懂
    interface ISearchFunc {
        (source: string, substring: string): boolean;
    }
    let mySearch: ISearchFunc;
    mySearch = function (source: string, substring: string): boolean {
        return source.search(substring) !== -1;
    };

    // 如何定义可选参数, 用 ? 表示可选
    function buildName(firstName: string, lastName?: string): string {
        if (lastName) {
            return firstName + " " + lastName;
        } else {
            return firstName;
        }
    }
    let tomcat = buildName("tom", "cat");
    let tom = buildName("tom");

    // 参数默认值
    // ES6中，我们允许给函数的参数添加默认值，TS会将添加了默认值的参数识别为可选参数
    function buildName2(firstName: string, lastName: string = "cat"): string {
        return firstName + " " + lastName;
    }
    // 此时就不受【可选参数必须在必选参数后面】的限制了
    function buildName3(firstName: string = "Tom", lastName: string): string {
        return firstName + " " + lastName;
    }
    let tomcat3 = buildName("tom", "cat");
    let tom3 = buildName(undefined, "cat");

    // 剩余参数
    // ES6中, 可以使用 ...rest 的方式来获取函数中的剩余参数
    // ...rest 参数只能是最后一个参数
    function pushToArray(array: any[], ...items: any[]): void {
        items.forEach(function (item) {
            array.push(item);
        });
    }

    // 重载
    // 重载允许一个函数接受不同数量或类型的参数时，做出不同的处理
    function reverse(x: number): number;
    function reverse(x: string): string;
    function reverse(x: number | string): number | string {
        if (typeof x === "number") {
            return Number(x.toString().split("").reverse().join(""));
        } else if (typeof x === "string") {
            return x.split("").reverse().join("");
        }
    }
}
