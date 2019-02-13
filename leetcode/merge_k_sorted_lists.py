# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

def merge2(node1, node2):
    ptr1 = node1
    ptr2 = node2
    if node1 is None and node2 is None:
        return None
    elif node1 is None:
        return node2
    elif node2 is None:
        return node1
    else:
        pass
    if ptr1.val <= ptr2.val:
        res = ptr1
        ptr1 = ptr1.next
    else:
        res = ptr2
        ptr2 = ptr2.next
    ptr3 = res
    while (ptr1 is not None) and (ptr2 is not None):
        if ptr1.val <= ptr2.val:
            ptr3.next = ptr1
            ptr1 = ptr1.next
        else:
            ptr3.next = ptr2
            ptr2 = ptr2.next
        ptr3 = ptr3.next
    if ptr1 is None:
        ptr3.next = ptr2
    if ptr2 is None:
        ptr3.next = ptr1
    return res


class Solution:
    def mergeKLists(self, lists):
        """
        :type lists: List[ListNode]
        :rtype: ListNode
        """
        k = len(lists)
        if k == 0: return None
        while k > 1:
            #import pdb; pdb.set_trace()
            res = list()
            for i in range(0, k, 2):
                if i == k-1:
                    res.append(lists[i])
                else:
                    res.append(merge2(lists[i], lists[i+1]))
            lists = list(res)
            k = len(lists)
        return lists[0]