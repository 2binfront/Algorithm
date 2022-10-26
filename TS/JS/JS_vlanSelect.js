/*
    Vlan是一种为局域网设备进行逻辑划分的技术
    为了标识不同的vlan 引入了vlan id 1~4094之间的整数
    定义一个vlan id 的资源池
    资源池中连续的vlan用开始vlan-结束vlan表示，
    不连续的用单个整数表示
    所有的vlan用英文逗号连接起来
    现有一个vlan资源池，业务需要从资源池中申请一个vlan
    需要你输出从vlan资源池中移除申请的vlan后的资源池

    输入描述
    第一行为字符串格式的vlan资源池
    第二行为业务要申请的vlan 
    vlan的取值范围1~4094

    输出描述
    从输入vlan资源池中移除申请的vlan后
    字符串格式的vlan资源池
    输出要求满足题目中要求的格式，
    并且要求从小到大升序输出
    如果申请的vlan不在原资源池，输出升序排序的原资源池的字符串即可

    示例
    输入
    5,1-3
    10
    输出
    1-3,5
    资源池中有1 2 3 5
    申请的资源不在资源池中
    将原池升序输出为1-3,5

    输入
    20-21,15,18,30,5-10
    15
    输出
    5-10,18,20-21,30

    输入池中vlan数量范围为2~2094的整数
    资源池中vlan不重复且合法1~2094的整数
    输入是乱序的
     */

function vlanDistribute(input) {
    const inputCheck = input.split('\n');
    const poolArr = inputCheck[0].split(',');
    const request = parseInt(inputCheck[1]);
    const pooset = [];
    for (let item of poolArr) {
        if (item.indexOf('-') !== -1) {
            item = item.split('-');
            for (let i = parseInt(item[0]); i <= parseInt(item[1]); i++) {
                pooset.push(i);
            }
        } else {
            pooset.push(parseInt(item));
        }
    }
    pooset.filter(el => {
        if (el !== request) return el;
    })
    pooset.sort((a, b) => a - b);
    let start = pooset[0], end = pooset[0];
    const ans = [];
    for (let i = 1; i < pooset.length; i++) {
        if (pooset[i] - end === 1) {
            end = pooset[i];

        } else {
            if (start === end) {
                ans.push(start + '');
                start = pooset[i];
                end = pooset[i];
            } else {
                ans.push(start + '-' + end);
                start = pooset[i];
                end = pooset[i];
            }
        }
    }
    if (start === end) {
        ans.push(start + '');
    } else {
        ans.push(start + '-' + end);
    }
    console.log(ans.join(','));
}

const test1 = '20-21,15,18,30,5-10\n15';
vlanDistribute(test1);