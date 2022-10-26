
from typing import List


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class LinkedList:
    def __init__(self,targetList:List[int]) -> None:
        self.head = ListNode(0)
        p=self.head
        for i in targetList:
            p.next =ListNode(i)
            p=p.next
            self.head.val+=1


def printList(targetList: LinkedList):
    head = targetList.head
    while head:
        print(head.val)
        head=head.next
