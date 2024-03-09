# f = open("input.txt", "r")
# g = open("output.txt", "w")
n,c = input().strip().split()
n = int(n)
c = int(c)
L=[]

l1=[x for x in input().strip().split()]
l2=[x for x in input().strip().split()]


for i in range(n):
    L.append((int(l1[i]), int(l2[i]), (int(l1[i])/int(l2[i]))))
    
L = sorted(L, key = lambda x: x[2], reverse=True)

total_value = 0
total_weight = 0
items_in_backpack = []

for value, weight, ratio in L:
    if c >= weight:
        items_in_backpack.append((weight, value))
        total_value += value
        total_weight += weight
        c -= weight 
    else:
        fraction = c / weight
        items_in_backpack.append((c, fraction * value))
        total_value += fraction * value
        total_weight += c
        break


print(total_value)