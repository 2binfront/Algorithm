/**
 * leetcode 17 dfs
 * 给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。答案可以按 任意顺序 返回。
 *
 *  输入：digits = "23"
输出：["ad","ae","af","bd","be","bf","cd","ce","cf"]

输入：digits = ""
输出：[]
 * @param {string} digits
 * @return {string[]}
 */
var letterCombinations = function (digits) {
    const res = [];
    let combination = '';
    const map = {
        '2': 'abc',
        '3': 'def',
        '4': 'ghi',
        '5': 'jkl',
        '6': 'mno',
        '7': 'pqrs',
        '8': 'tuv',
        '9': 'wxyz',
    }
    function dfs(index = 0) {
        if (index === digits.length) {
            res.push(combination);
        }
        else {
            let mapletter = digits[index];
            for (const letter of map[mapletter]) {
                combination += letter;
                dfs(index + 1);
                combination = combination.slice(0, -1);

            }
        }
    }
    if (!digits) return [];

    dfs();
    return res;
};

let test1 = "23"
console.log(letterCombinations(test1))