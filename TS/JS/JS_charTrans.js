//将输入的字符串（字符串仅包含小写字母’a’到’z’），按照如下规则，循环转换后输出：
//a->b,b->c,….y->z,z->a;若输入的字符串连续出现两个字母相同时，后一个字母连续转换2次。
//例如：aa转换成bc，zz转换为ab；当连续相同字母超过两个时，第三个出现的字母按第一次出现.

function charTrans(str) {
    let ans = '';
    for (let i = 0; i < str.length; i++) {
        let flag = 1;
        if (i > 0 && str[i] === str[i - 1]) {
            flag = 0
        }
        if (flag) {
            //先减去a的ascii码得到未转化为合法的序号，对26取余得到合法序号，再加上a的ascii码得到最终结果
            ans += String.fromCharCode((str[i].charCodeAt() + 1 - 'a'.charCodeAt()) % 26 + 'a'.charCodeAt());
        } else {
            ans += String.fromCharCode((str[i].charCodeAt() + 2 - 'a'.charCodeAt()) % 26 + 'a'.charCodeAt());
        }
    }
    return ans;
}

console.log(charTrans('azzb'))