# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

def sort_two_k(s1, s2, k):
    # return the one after the last one
    

class Solution:
    def sortList(self, head):
        """
        :type head: ListNode
        :rtype: ListNode
        """
        length = 0
        tmp = head
        while tmp is not None:
            tmp = tmp.next
            length += 1

        k = 2
        while k < length:


            k *= 2
        
        