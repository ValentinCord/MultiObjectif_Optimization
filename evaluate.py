
import pygmo as pg
from pygmo import hypervolume
import numpy as np

ref_point = [100, 150, 150, 250]

with open("sol_8_4.txt", 'r') as fin: 
    n = int(fin.readline())

    front = [list(map(int,fin.readline().split())) for i in range(n)]

    hv = hypervolume(front)

    best_result = hv.compute(ref_point)

with open("test_8_4.txt", 'r') as fin: 
    n = int(fin.readline())

    front = [list(map(int,fin.readline().split())) for i in range(n)]

    hv = hypervolume(front)

    result = hv.compute(ref_point)

print(best_result/np.prod(ref_point))
print(result/np.prod(ref_point))
    
