/**
 * leetcode 39 单词搜索
 * @param {character[][]} board
 * @param {string} word
 * @return {boolean}
 * 给定一个 m x n 二维字符网格 board 和一个字符串单词 word 。如果 word 存在于网格中，返回 true ；否则，返回 false 。
单词必须按照字母顺序，通过相邻的单元格内的字母构成，
其中“相邻”单元格是那些水平相邻或垂直相邻的单元格
。同一个单元格内的字母不允许被重复使用。
 */
let exist = function (board, word) {
    let m = board.length, n = board[0].length;
    let keyLen = word.length;
    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            if (dfs(i, j, 0)) {
                return true;
            }
        }
    }
    return false;

    function dfs(x, y, k) {
        //判断是否越界且是否相等当前关键字符
        if (x < 0 || x >= m || y < 0 || y > n || board[x][y] !== word[k]) {
            return false;
        }
        if (k === keyLen - 1) {
            return true;
        }
        board[x][y] = '\0';
        let res = dfs(x - 1, y, k + 1) || dfs(x + 1, y, k + 1) || dfs(x, y - 1, k + 1) || dfs(x, y + 1, k + 1);
        board[x][y] = word[k];
        return res;
    }
};

let testBoard = [["A", "B", "C", "E"], ["S", "F", "C", "S"], ["A", "D", "E", "E"]], testWord = "ABCCED"
console.log(exist(testBoard, testWord))