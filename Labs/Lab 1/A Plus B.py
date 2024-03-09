# f = open("input.txt", "r")
# g = open("output.txt", "w")
n = int(input().strip())


for i in range(n):
    s = sum([int(x) for x in input().strip().split()])
    print(s)