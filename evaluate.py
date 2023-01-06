
import pygmo as pg
from pygmo import hypervolume
import numpy as np

with open("sol/kev/30.txt", 'r') as fin: 
    n = int(fin.readline())
    front_a = [list(map(int,fin.readline().split())) for i in range(n)]

with open("sol/tanguy/30.txt", 'r') as fin: 
    n = int(fin.readline())
    front_b = [list(map(int,fin.readline().split())) for i in range(n)]

# 1.05
ref_point = [100, 100, 100, 100]
for sa in front_a:
    for cnt, sai in enumerate(sa): 
        ref_point[cnt] = max(ref_point[cnt], sai)

for sb in front_b:
    for cnt, sbi in enumerate(sb): 
        ref_point[cnt] = max(ref_point[cnt], sbi)      

ref_point = [pi * 1.05 for pi in ref_point]

hv = hypervolume(front_a)
result_a = hv.compute(ref_point)

hv = hypervolume(front_b)
result_b = hv.compute(ref_point)


print("hypervolume solution A: ", result_a/np.prod(ref_point))
print("hypervolume solution B: ", result_b/np.prod(ref_point))

# comparing sol_a 

merge = set()

best_a = 0
bested_a = 0

commun = 0

best_b = 0
bested_b = 0

for sa in front_a: 
    dominant = True
    for sb in front_b: 
        dom_a = False 
        dom_b = False 
        for sia, sib in zip(sa, sb): 
            if sia < sib: 
                dom_a = True
            if sia > sib: 
                dom_b = True
        
        if sa == sb: 
            commun += 1
                
        if dom_b and not dom_a: 
            dominant = False 
            break 
    
    if dominant: 
        merge.add(tuple(sa))
        best_a += 1
    else:
        bested_a += 1

for sb in front_b: 
    
    dominant = True
    for sa in front_a: 
        dom_a = False 
        dom_b = False 
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

print("nombre de solution en A: ", len(front_a))
print("nombre de solution en B: ", len(front_b))
print("nombre de solution en A et B: ", len(merge))

print("nombre de solutions dominantes de A: ", best_a)
print("nombre de solutions dominées en A: ", bested_a)


print("nombre de solutions dominantes de B: ", best_b)
print("nombre de solutions dominées en B: ", bested_b)

list_merge = [list(mi) for mi in merge]


hv = hypervolume(list_merge)

result_merge = hv.compute(ref_point)

print("hypervolume pour A et B: ",result_merge/np.prod(ref_point))
print("nombre de solutions commune en A et B: ", commun)