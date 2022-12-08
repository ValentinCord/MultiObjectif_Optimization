
import pygmo as pg
from pygmo import hypervolume
import numpy as np

with open("test/a1.txt", 'r') as fin: 
    n = int(fin.readline())
    front_a = [list(map(int,fin.readline().split())) for i in range(n)]

with open("test/a2.txt", 'r') as fin: 
    n = int(fin.readline())
    front_b = [list(map(int,fin.readline().split())) for i in range(n)]

with open("test/a3.txt", 'r') as fin: 
    n = int(fin.readline())
    front_c = [list(map(int,fin.readline().split())) for i in range(n)]

# 1.05
ref_point = [100, 100, 100, 100]
for sa in front_a:
    for cnt, sai in enumerate(sa): 
        ref_point[cnt] = max(ref_point[cnt], sai)

for sb in front_b:
    for cnt, sbi in enumerate(sb): 
        ref_point[cnt] = max(ref_point[cnt], sbi)      

for sc in front_c:
    for cnt, sci in enumerate(sc): 
        ref_point[cnt] = max(ref_point[cnt], sci)  

ref_point = [pi * 1.05 for pi in ref_point]

hv = hypervolume(front_a)
result_a = hv.compute(ref_point)

hv = hypervolume(front_b)
result_b = hv.compute(ref_point)

hv = hypervolume(front_c)
result_c = hv.compute(ref_point)


print("hypervolume solution A: ", result_a/np.prod(ref_point))
print("hypervolume solution B: ", result_b/np.prod(ref_point))
print("a")
print("hypervolume solution C: ", result_c/np.prod(ref_point))
print("hello")
print("point de reference: ", ref_point)