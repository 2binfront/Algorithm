function bridge(input) {
    let inputArray = input.split('\n');
    /**
     * 待实现函数，在此函数中填入答题代码
     * doFunc()
     */
    //数据结构求桥数量。。
    const vNum = parseInt(inputArray[0]), edgeNum = parseInt(inputArray[1]);
    const raw = new Array(vNum).fill(0);
    const G = [];
    for (let i = 0; i < vNum; i++) G.push(raw);
    let bridgeNum = 0;
    const visited = new Array(vNum).fill(0);
    //初始化图
    for (let i = 2; i < inputArray.length; i++) {
        let tmparr = inputArray[i].split(' ');
        let n1 = parseInt(tmparr[0])
        let n2 = parseInt(tmparr[1]);
        G[n1][n2] = 1;
        G[n2][n1] = 1;
    }

    for (let i = 0; i < vNum; i++) {
        for (let j = i + 1; j < vNum; j++) {
            if (G[i][j] === 0) {
                continue;
            } else {
                G[i][j] = 0;
                if (!accessable(i, j)) {
                    bridgeNum += 1;
                }
                G[i][j] = 1;
            }
        }
    }

    function accessable(x, y) {
        if (G[x][y]) {
            return true;
        }
        for (let i = 0; i < vNum; i++) {
            if (visited[i]) continue;
            if (G[x][i]) {
                visited[i] = 1;
                if (accessable(i, y)) {
                    return true;
                }
                visited[i] = 0;
            }
        }
    }

    console.log(bridgeNum / 2);

}

bridge('4\n3\n0 1\n0 2\n0 3');