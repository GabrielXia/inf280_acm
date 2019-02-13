def search (M, i1, j1, i2, j2, target, judge):
    print(judge)
    if i1 == i2 and j1 == j2:
        print(M[i1][j1])
        if M[i1][j1] == target:
            judge = True
    else:              
        row = i2 - i1 + 1
        col = j2 - j1 + 1
        newr = row // 2
        newc = col // 2
        if newr >= 1:
            if newc >= 1:
                search(M, i1, j1, i1+newr-1, j1+newc-1, target, judge)
                search(M, i1, j1+newc, i1+newr-1 ,j2, target, judge)
                search(M, i1+newr, j1, i2, j1+newc-1, target, judge)
                search(M, i1+newr, j1+newc, i2, j2, target, judge)
            else:
                search(M, i1, j1, i1+newr-1, j1, target, judge)
                search(M, i1+newr, j1, i2, j2, target, judge)
        else:
            search(M, i1, j1, i1, j1+newc-1, target, judge)
            search(M, i1, j1+newc, i2, j2, target, judge)
    return judge


