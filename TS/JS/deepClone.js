function myDeepClone(data) {
    //记录对象防止循环引用
    const map = new WeakMap();

    //判断是否为对象
    function isobject(target) {
        return (typeof target === 'object' && target) || typeof target === 'function'
    }

    function clone(target) {
        if (!isobject(target)) {
            return target;
        }

        //为Date对象或正则对象时利用其构造函数返回副本
        if ([Date, RegExp].includes(target.constructor)) {
            return target.constructor(target);
        }

        if (typeof target === 'function') {
            return new Function('return ' + target.toString())();
        }

        //假如该对象已存在，则直接返回该对象
        if (map.has(target)) {
            return map.get(target);
        }

        if (target instanceof Map) {
            const result = new Map();
            map.set(target, result);
            target.forEach((val, key) => {
                if (isobject(val)) {
                    result.set(key, clone(val));
                } else {
                    result.set(key, val);
                }
            })
        }

        if (target instanceof Set) {
            const result = new Set();
            map.set(target, result);
            target.forEach((val) => {
                if (isobject(val)) {
                    result.add(clone(val));
                } else {
                    result.add(val);
                }
            })
        }

        //防止key为Symbol无法读取
        const keys = Reflect.ownKeys(target);
        const desc = Object.getOwnPropertyDescriptors(target);
        //浅拷贝
        const result = Object.create(Object.getPrototypeOf(target), desc);

        map.set(target, result);
        keys.forEach((key) => {
            if (isobject(target[key])) {
                result[key] = clone(target[key]);
            } else {
                result[key] = target[key];
            }
        });

        return result;
    }
    return clone(data);
}

// 测试数据项
let data = {
    age: 18,
    name: "liuruchao",
    education: ["小学", "初中", "高中", "大学", undefined, null],
    likesFood: new Set(["fish", "banana"]),
    friends: [
        { name: "summer", sex: "woman" },
        { name: "daWen", sex: "woman" },
        { name: "yang", sex: "man" }],
    work: {
        time: "2019",
        project: { name: "test", obtain: ["css", "html", "js"] }
    },
    play: function () { console.log("玩滑板"); }
}

let copy = myDeepClone(data);
copy