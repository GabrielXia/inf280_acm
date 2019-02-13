def line2list():
    arr = [int(i) for i in raw_input().split()]
    return arr

# input 
T = input()
for t in range(T):
    N, P = line2list()
    list_forb = []
    for p in range(P):
        forb = raw_input()
        list_forb.append(forb)

    # find the smallest input 
    list_filter = []
    for index,forb in enumerate(list_forb):
        contain = False
        for index2,other in enumerate(list_forb):
            if index2 != index and forb.find(other) == 0:
                contain = True
                break
        if not contain:
            list_filter.append(forb)

    count = 2 ** N
    for i,forb in enumerate(list_filter):
        forb_len = len(forb)
        count -= 2**(N - forb_len)
    print('Case #' + str(t+1) + ': ' + str(count))

    