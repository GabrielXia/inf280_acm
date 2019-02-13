class Node(object):
    def __init__(self, data=None, next_node=None):
        self.data = data
        self.next = next_node
    

class LinkedList(object):
    def __init__(self, head=None):
        self.head = head
    
    def insert(self, data):
        # insert a new node to the head of list
        # return None
        # TODO 
        pass 

    def size(self):
        # return the size of linked list
        # TODO
        pass
    
    def search(self, data):
        # return the first index match data 
        # TODO
        pass

    def delete(self, data):
        # delete all the nodes that has data value
        # TODO
        pass