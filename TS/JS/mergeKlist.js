/**
 * 将多个升序排列的链表合并到一个升序链表并返回
 */
/**
 * 单向列表定义
 * @param {*} val 
 * @param {*} next 
 */
function ListNode(val, next) {
    this.val = (val ? val : 0);
    this.next = (next ? next : null)
}

let printList = function (node) {
    while (node) {
        console.log(node.val);
        node = node.next;
    }
    return;
}

/**
 * @param {ListNode[]} lists
 * @return {ListNode}
 */
//应该是成环了
let mergeKLists = function (lists) {
    let merge2lists = function (a1, b1) {
        let a = a1, b = b1;
        if (!a || !b) {
            return a ? a : b;
        }
        dummy = new ListNode(-1);
        let p = dummy;
        while (a && b) {
            if (a.val > b.val) {
                p.next = b;
                b = b.next;

            } else {
                p.next = a;
                a = a.next;
            }
            p = p.next;
        }
        p.next = (a ? a : b);
        // delete p;
        //printList(dummy);
        return dummy.next;
    }

    let merge = function (start, end) {
        if (start === end) {
            return lists[start];
        } else if (start > end) {
            return null;
        }
        let mid = (start + end) >> 1;
        return merge2lists(merge(start, mid), merge(mid + 1, end));
    }

    return merge(0, lists.length - 1)
};

let a1 = new ListNode(1);
let a2 = new ListNode(4);
let a3 = new ListNode(5);
a1.next = a2;
a2.next = a3;

let b1 = new ListNode(1);
let b2 = new ListNode(3);
let b3 = new ListNode(4);
b1.next = b2;
b2.next = b3;

let c1 = new ListNode(2);
let c2 = new ListNode(6);
c1.next = c2;

let arr = [a1, b1, c1];
let ans = mergeKLists(arr);



printList(ans);