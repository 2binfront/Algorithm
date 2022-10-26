import { each } from "lodash";

export class ListNode {
    val: number;
    next: ListNode;
    constructor(val: number, next: ListNode = null) {
        this.val = val;
        this.next = next;
    }
}

export class LinkedList {
    constructor(arr: Array<number>) {
        const head: ListNode = new ListNode(0);
        let p: ListNode = head;
        let len: number = arr.length;

        head.val = len;
        for (let i = 0; i < len; i++) {
            p.next = new ListNode(i);
            p=p.next;
        }
    }
}