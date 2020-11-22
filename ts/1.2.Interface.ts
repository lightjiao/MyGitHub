// 对象的类型  -- 接口
// 可用于对类的一部分行为进行抽象，
// !也常用于对【对象的形状(shape)】进行描述
interface IPerson {
    name: string;
    age: number;
}

// 定义的变量比接口 少 或者 多一些属性都是不允许的
// 赋值的时候，变量的形状必须和接口的形状保持一致
let tom: IPerson = {
    name: "jack",
    age: 22,
};

// 可选属性
interface IPerson2 {
    name: string;
    age?: number; // 这个属性可填可不填，但仍然不允许添加未定义的属性
}

// 任意属性
interface IPerson3 {
    name: string;
    [x: string]: string; // key为string, value为string
    [y: number]: string; // key为number, value为string
}
let newStu: IPerson3 = {
    name: "rose",
    gender: "female",
    // tall: 123,
    111: "222",
};

// 只读
// ! 只读的约束在于第一次给对象赋值，而不是给属性赋值的时候
interface IPerson4 {
    readonly id?: number;
    name: string;
}
let jack: IPerson4 = {
    name: "aaa",
};
// jack.id = 111; // 不允许赋值，因为jack已经第一次被赋值了
