import re

r = "\: | \|"
s = "[0-9]+"
total_points = 0
M = []
t = 0       # total scratchcards

def toM(m):
    M.append(list(range(m[0] + 1, m[0] + m[1] + 1)))

def scratch(m):
    def r(m):
        global t
        t += len(m)
        for i in m:
            if len(M[i - 1]) > 0:
                r(M[i - 1])

    for i in M:
        r(i)
    print(f"Total scratchcards are: {t + len(m)}.")


def points(m):
    w = 0       # w: count winning numbers
    for i in m[2]:
        if i in m[1]:
            w += 1
    if w > 0:
        points = 2**(w - 1)
        return [points, w]
    return [0, w]


with open("day4/input.txt", "r") as f:
    for line in f:
        x = re.split(r, line)
        L = []
        for i in range(len(x)):
            L.append(re.findall(s, x[i]))
        p = points(L)
        total_points += p[0]                # cal total points. Part 1
        toM([int(L[0][0]), p[1]])           # make a copy of cards to M[]


print(f"Total points: {total_points}.")
scratch(M)          # calc total scratchs cards. Part 2