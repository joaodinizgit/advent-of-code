import re

r = "\: | \|"
s = "[0-9]+"
total_points = 0

def c(m):
    t = 0
    for i in m[1]:
        if i in m[0]:
            t += 1
    if t > 0:
        points = 2**(t - 1)
        return points
    return 0

with open("day4/input.txt", "r") as f:
    for line in f:
        x = re.split(r, line)
        L = []
        for i in range(1, len(x)):
            L.append(re.findall(s, x[i]))
        total_points += c(L)

print(total_points)