function LearnArray() {
    // 数组的类型

    // 1 类型+方括号 的表示法
    let fibonacci: number[] = [1, 1, 2, 3, 5];
    // ! 数组的项中不允许出现其他的类型

    // 2 数组泛型
    let fibonacci2: Array<number> = [1, 1, 2, 3, 5];

    // 3 用接口表示数组
    interface INumberArray {
        [x: number]: number;
    }
    let fibonacci3: INumberArray = [1, 1, 2, 3, 5];

    // 4. 类数组(Array-like Object)
    // 类数组不是数组类型
    function sum() {
        // 这样写不对, arguments 变量是一个类数组
        // let args: number[] = arguments;

        let args: {
            [x: number]: number;
            length: number;
            callee: Function;
        } = arguments;
    }
}
