const numIslands = function (grid) {
    const rows = grid.length, cols = grid[0].length;
    let count = 0;
    const visited = [];
    for (let i = 0; i < rows; i++) {
        let tmp = new Array(cols).fill(0);
        visited.push(tmp);
    }

    for (let i = 0; i < rows; i++)
        for (let j = 0; j < cols; j++) {
            if (visited[i][j]) {
                continue;
            }
            visited[i][j] = 1;
            if (grid[i][j] === "1") {
                count++;
                adjoin(i, j);
            }
        }

    function adjoin(x, y) {
        for (const [a, b] of [[-1, 0], [1, 0], [0, 1], [0, -1]]) {
            if (x + a >= 0 && x + a < rows && y + b >= 0 && y + b < cols && !visited[x + a][y + b] && grid[x + a][y + b] === "1") {
                visited[x + a][y + b] = 1;
                adjoin(x + a, y + b);
            }
        }
        return;
    }
    return count;

};

const grid1 = [
    ["1", "1", "1", "1", "0"],
    ["1", "1", "0", "1", "0"],
    ["1", "1", "0", "0", "0"],
    ["0", "0", "0", "0", "0"]
]

console.log(numIslands(grid1))