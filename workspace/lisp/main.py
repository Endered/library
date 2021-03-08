
def func(n):
    edges = []
    for i in range(n):
        for j in range(i+1,n):
            edges.append((i,j))
    print(n,len(edges))

    for i in edges:
        for j in i:
            print(j,end=" ")
        print()
