import numpy as np

def line2list():
    arr = [int(i) for i in raw_input().split()]
    return arr

T = input()
for t in range(T):
    N, Q = line2list()
    x1,x2,a1,b1,c1,m1 = line2list()
    y1,y2,a2,b2,c2,m2 = line2list()
    z1,z2,a3,b3,c3,m3 = line2list()

    xi= np.zeros((2, N),dtype=np.int64)
    xi[0,0], xi[0,1], xi[1,0],xi[1,1] = x1, x2, y1, y2
    for n in range(2, N):
        xi[0, n] = (a1 * xi[0, n-1] + b1 * xi[0, n -2] + c1) % m1
        xi[1, n] = (a2 * xi[1, n-1] + b2 * xi[1, n -2] + c2) % m2
    l = np.min(xi, axis=0) + 1
    r = np.max(xi, axis=0) + 1
    l.sort()
    r.sort()
    lp = N - 1
    rp = N - 2
    rank2k = dict()
    rank_init = 1
    rank2k[rank_init] = (r[-1], 1) # rank to score, k
    rank_tmp = rank_init # current rank
    # k d_rank / d_score
    while lp >= 0 and rp >= 0:
        if rp > 0:
            if l[lp] < r[rp]:
                score_b, k_b = rank2k[rank_tmp]
                rank = rank_tmp + k_b * (score_b - r[rp]) 
                rank2k[rank] = (r[rp], k_b + 1)
                rank_tmp = rank
                rp -= 1
            elif l[lp] > r[rp]:
                import pdb; pdb.set_trace() # TODO
                score_b, k_b = rank2k[rank_tmp]
                rank = rank_tmp + k_b * (score_b - l[lp])
                rank2k[rank] = (l[lp], k_b - 1)
                rank_tmp = rank
                lp -= 1
            else:
                score_b, k_b = rank2k[rank_tmp]
                rank = rank_tmp + k_b * (score_b - l[lp])
                rank2k[rank] = (l[lp], k_b)
                rank_tmp = rank
                lp -= 1
                rp -= 1
        elif rp == 0:
            score_b, k_b = rank2k[rank_tmp]
            rank = rank_tmp + k_b * (score_b - l[lp])
            rank2k[rank] = (l[lp], k_b - 1)
            rank_tmp = rank
            lp -= 1    
    rank_list = rank2k.keys()
    rank_list.sort()

    import pdb; pdb.set_trace()

    out = 0
    z = np.zeros(max(Q, 2), dtype=np.int64)
    z[0], z[1] = z1, z2
    for q in range(Q):
        if q > 2:
            z[q] = (a3 * z[q-1] + b3 * z[q-2] + c3) % m3
        k = z[q] + 1
        s = -1
        e = len(rank_list)
        while s + 1 < e:
            se = (s + e) // 2
            if k == rank_list[se]:
                s = se
                break
            elif k < rank_list[se]:
                e = se
            elif k > rank_list[se]:
                s = se
        if s <= -1: print('error')
        elif s == len(rank_list) -1: ai = 0
        else:
            ri = rank_list[s]
            score, k_b = rank2k[ri]
            ai = score - k_b * (k - ri)
        out += ai * (q + 1)
    print('Case #' + str(T+1) + ': ' + str(out))
        

