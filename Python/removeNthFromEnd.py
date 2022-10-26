from os import link
from tokenize import Number
import dataStructure as ds
# 移除倒数第n个链表结点

def removeNthFromEnd(node: ds.ListNode, n: Number) -> ds.ListNode:
    p = node
    q = node
    for _ in range(n):
        if not p:
            return node
        p=p.next
    node.val-=1
    while p.next:
        p=p.next
        q=q.next
    q.next=q.next.next
    return node


linked = ds.LinkedList([1,2,3,4,5,6])
newhead = removeNthFromEnd(linked.head,2)

ds.printList(linked)
