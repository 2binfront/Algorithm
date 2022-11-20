let arr = [
    { id: 1, name: '部门1', pid: 0 },
    { id: 2, name: '部门2', pid: 1 },
    { id: 3, name: '部门3', pid: 1 },
    { id: 4, name: '部门4', pid: 3 },
    { id: 5, name: '部门5', pid: 4 },
];

function arrayToTree(items) {
    const result = [];   // 存放结果集
    const itemMap = {};  // 
    for (const item of items) {
        const id = item.id;
        const pid = item.pid;

        if (!itemMap[id]) {
            itemMap[id] = {
                children: [],
            }
        }

        itemMap[id] = {
            ...item,
            children: itemMap[id]['children']
        }

        const treeItem = itemMap[id];

        if (pid === 0) {
            result.push(treeItem);
        } else {
            if (!itemMap[pid]) {
                itemMap[pid] = {
                    children: [],
                }
            }
            itemMap[pid].children.push(treeItem)
        }
    }
    return result;
}

function getChildren(data, result, pid) {
    for (const item of data) {
        if (item.pid === pid) {
            let tmp = { ...item, children: [] };
            result.push(tmp);
            getChildren(data, tmp.children, tmp.id);
        }
    }
}

function arrayToTree_recursive(data, pid = 0) {
    let result = [];
    getChildren(data, result, pid);
    return result;
}

console.log(JSON.stringify(arrayToTree_recursive(arr)));
console.log(JSON.stringify(arrayToTree(arr),null,4));
// util.inspect(arrayToTree(arr))