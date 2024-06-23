def generate_list(n):
    n_list = [1]
    for i in range(2, n+1):
        n_list.append(n_list[-1] + i)
    return n_list

def generate_matrix(s):
    s_matrix = []
    s_matrix.append(s)
    while len(s_matrix[-1][1::]) > 0:
        m = []
        for i in s_matrix[-1][1::]:
            m.append(i-1)
        s_matrix.append(m)
    return s_matrix


g = generate_list(int(input()))
for s in generate_matrix(g):
    for o in s:
        print(o,end=" ")
    if len(s)>1:
        print()

