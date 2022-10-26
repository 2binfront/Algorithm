/**
 * @param {string[]} strs
 * @return {string}
 */
let longestCommonPrefix = function (strs) {
    let minLen = Infinity;
    let minIndex = -1;
    let pubPre = '';
    for (const i of strs) {
        if (i.length < minLen) {
            minLen = i.length;
            minIndex = strs.indexOf(i);
        }
    }
    for (let i = 0; i < strs[minIndex].length; i++) {
        for (const j of strs) {
            if (j[i] !== strs[minIndex][i]) {
                return pubPre
            }
        }
        pubPre += strs[minIndex][i];
    }
    return pubPre;
};

let test1 = ["flower", "flow", "flight"];
let ans1=longestCommonPrefix(test1);
console.log(ans1);