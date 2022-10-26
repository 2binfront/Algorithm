function parseIP(str:string):number{
    let parseStr:Array<string> = str.split('.');
    let ans:number = 0;
    for(const i of parseStr){
        ans = ans*256+parseInt(i);
    }
    return ans;

}

function parse2IP(num:number):string{
    let ansStr = '';
    for(let i=0;i<32;i++){
        let tmp = num%2;
        num = Math.floor(num / 2);
        ansStr+=tmp;
    }
    let ansArr = ansStr.split('');
    ansArr = ansArr.reverse();
    let ans='';
    ans = parseInt(ansArr.slice(0, 8).join(''), 2) + '.' + parseInt(ansArr.slice(8, 16).join(''), 2) + '.' + parseInt(ansArr.slice(16, 24).join(''), 2) + '.' + parseInt(ansArr.slice(24, 32).join(''), 2);
    return ans;
}

let IP1 ='10.3.3.193';
let ans1 = parseIP(IP1);


console.log(ans1,parse2IP(ans1))