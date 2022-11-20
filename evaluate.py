
import pygmo as pg
from pygmo import hypervolume
import numpy as np

ref_point = [900, 900, 900, 900]

with open("sol_8_4.txt", 'r') as fin: 
    n = int(fin.readline())

    front_a = [list(map(int,fin.readline().split())) for i in range(n)]

    hv = hypervolume(front_a)

    result_a = hv.compute(ref_point)

with open("test_8_4.txt", 'r') as fin: 
    n = int(fin.readline())

    front_b = [list(map(int,fin.readline().split())) for i in range(n)]

    hv = hypervolume(front_b)

    result_b = hv.compute(ref_point)

print(result_a/np.prod(ref_point))
print(result_b/np.prod(ref_point))

# comparing sol_a 

merge = set()

best_a = 0
bested_a = 0

best_b = 0
bested_b = 0

for sa in front_a: 
    dom_a = False 
    dom_b = False 

    dominant = True
    for sb in front_b: 
        for sia, sib in zip(sa, sb): 
            if sia < sib: 
                dom_a = True
            if sia > sib: 
                dom_b = True

        if dom_b and not dom_a: 
            dominant = False 
            break 
    
    if dominant: 
        merge.add(tuple(sa))
        best_a += 1
    else:
        bested_a += 1

print(len(merge))

for sb in front_b: 
    dom_a = False 
    dom_b = False 

    dominant = True
    for sa in front_a: 
        for sia, sib in zip(sa, sb): 
            if sia < sib: 
                dom_a = True
            if sia > sib: 
                dom_b = True

        if dom_a and not dom_b: 
            dominant = False 
            break 
    
    if dominant: 
        merge.add(tuple(sb))
        best_b += 1
    else:
        bested_b += 1

print(len(merge))

print(best_a, bested_a)
print(best_b, bested_b)

list_merge = [list(mi) for mi in merge]


hv = hypervolume(list_merge)

result_merge = hv.compute(ref_point)

print(result_merge/np.prod(ref_point))