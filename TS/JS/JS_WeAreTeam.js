//总共有 n 个人在机房，每个人有一个标号（1 <= 标号 <= n），他们分成了多个团队，需要你根据收到的 m 条消息判定指定的两个人是否在一个团队中，具体的：
//1、消息构成为 a b c，整数 a、b 分别代表两个人的标号，整数 c 代表指令
//2、c == 0 代表 a 和 b 在一个团队内
//3、c == 1 代表需要判定 a 和 b 的关系，如果 a 和 b 是一个团队，输出一行’we are a team’, 如果不是，输出一行’we are not a team’
//4、c 为其他值，或当前行 a 或 b 超出 1~n 的范围，输出‘da pian zi’

function judgeTeam(str){
    const messages=str.split('\n');
    const n = parseInt(messages[0].split(' ')[0]);
    const m = parseInt(messages[0].split(' ')[1]);
    const groups=new Array(n);
    for(let i=0;i<n;i++){
        groups[i]=i;
    }
    const verifyList=[];
    for(let i=1;i<messages.length;i++){
        let n1 =parseInt(messages[i].split(' ')[0]);
        let n2 =parseInt(messages[i].split(' ')[1]);
        let n3 =parseInt(messages[i].split(' ')[2]);
        [n1, n2] = n1 < n2 ? [n1, n2] : [n2, n1];
        if(n3!==0){
            verifyList.push([n1,n2,n3]);
            continue;
        }else{
            groups[n2]=groups[n1];
        }
    }
    for(let i=0;i<verifyList.length;i++){
        if(verifyList[i][2]!==1){
            console.log('da pian zi');
        }else{
            if(groups[verifyList[i][0]]===groups[verifyList[i][1]]){
                console.log('team');
            }else{
                console.log('not team');
            }
        }
    }
}

const test1="5 6\n1 2 0\n1 2 1\n1 5 0\n2 3 1\n2 5 1\n1 3 2"
judgeTeam(test1)