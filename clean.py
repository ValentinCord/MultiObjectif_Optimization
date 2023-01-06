
sol = []
with open('sol/kev/3.txt', 'r') as fin: 
    n = int(fin.readline())

    for i in range(n):
        _, a, b, c, d = fin.readline().split(' ')

        sol.append([a,b,c,d])

with open('sol/kev/3.txt', 'w') as fout: 
    fout.write(str(n) + '\n')

    for i in range(n): 
        fout.write(sol[i][0] + ' ' + sol[i][1] + ' ' + sol[i][2] + ' ' + sol[i][3])
