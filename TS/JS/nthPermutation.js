//给出集合 [1,2,3,...,n]，其所有元素共有 n! 种排列。
// 按大小顺序列出所有排列情况，并一一标记，当 n = 3 时, 所有排列如下：
// "123"
// "132"
// "213"
// "231"
// "312"
// "321"
// 给定 n 和 k，返回第 k 个排列。


const getPermutation = function (n, k) {
    const fictoria = new Array(n).fill(1);
    for (let i = n - 3; i >= 0; i--) {
        fictoria[i] = fictoria[i + 1] * (n - i - 1);
    }

    const path = [], visited = new Array(n).fill(0);
    function backTra(index = 0) {
        if (index === n) return;
        for (let i = 0; i < n; i++) {
            if (visited[i]) continue;
            if (k > fictoria[i]) {
                k -= fictoria[i];
                continue;
            }
            path.push(i + 1);
            visited[i] = 1;
            backTra(index + 1);
            return;
        }
    }
    backTra();
    return path.join('');
};

console.log(getPermutation(4,9))