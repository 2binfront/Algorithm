// const text = 'message is {{msg+aa}},hhh'
// const reg = /\{\{(.+?)\}\}/g;
// //分割插值表达式
// let pices = text.split(reg);

// //console.log(pices);

// //匹配插值表达式
// let matches = text.match(reg);

// console.log(pices,matches)

// let tokens = [];
// pices.forEach(item => {
//     if (matches && matches.indexOf("{{" + item + "}}") > -1) {
//         tokens.push("(" + item + ")")
//     } else {
//         tokens.push('`' + item + '`')
//     }
// });
// console.log(tokens.join('+'));

// function timeID(wait) {
//     let timeout;
//     return function () {
//         if (timeout) clearTimeout(timeout);
//         console.log(timeout, typeof timeID);
//         timeout = setTimeout(() => {
//             console.log(timeout, typeof timeID);
//         }, wait);
//         console.log(timeout, typeof timeID);
//     }
// }

// timeID(5)();
// // timeID(5)();
// // timeID(5)();

// function alertFunction(val) {
//     console.log("Hello!" + val); //Hello!12345
// }

// var myVar = setTimeout(alertFunction, 1000, 12345);

// console.log(myVar);//v8中 返回整型id数值

// function testfn1(...arr){
//     return ()=>{
//         console.log(arr?.[0]?.(...arr.slice().splice(2,2)))
//     }
// }

// a=testfn1((num1,num2)=>num1+num2,1,2,3,4)
// b=a()
// console.log(b)

// let a='';
// a+='b'
// a += String.fromCharCode(('z'.charCodeAt() + 2) % ('a'.charCodeAt()))
// console.log(('z'.charCodeAt() + 2) % ('a'.charCodeAt()) ,a)

const around = [[-1, 0], [1, 0], [0, 1], [0, -1]];
for ([a, b] of around) {
    console.log(a,b)
}
