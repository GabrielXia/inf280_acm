# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution:
    def reverseKGroup(self, head, k):
        if head is None:
            return None

        # count len
        length = 0
        tmp = head
        while tmp is not None:
            length += 1
            tmp = tmp.next

        if k > length:
            return head

        prev = head
        cur = head.next
        # next = cur.next
        # cur.next = head
        # prev = cur
        # cur = next

        # first term
        for i in range(k-1):
            if cur is not None:
                next = cur.next
                cur.next = prev
                prev = cur
                cur = next
        head.next = cur
        res = prev

        it = length // k
        pprev = head
        for j in range(it-1):
            prev = pprev.next
            cur = prev.next
            for i in range(k-1):
                next = cur.next
                cur.next = prev
                prev = cur
                cur = next
            tmp = pprev.next
            pprev.next = prev
            tmp.next = cur
            pprev = tmp

        return res
