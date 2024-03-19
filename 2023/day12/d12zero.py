import re

argmts = 0

def rec(g, n, m = "", start = 0):
    if start == len(g):
        return
    global argmts
    # print(g)

    if g.find("?") == -1:
        nl = re.findall("#+", g)
        nln = [len(x) for x in nl]
        print(g, nln)
        if nln == n:
            argmts += 1

    # print(nln)
    # print(m)

    while g[start] == "." or start < len(g):
        m += "."
        start += 1

    while g[start] == "#" or start < len(g):
        m += "#"
        start += 1

    if g[start] == "?":
        m += "#"
        rec(g.replace("?", "#", 1), n, m, start + 1 )
        m += "."
        rec(g.replace("?", ".", 1), n, m, start + 1)

with open("example1.txt", "r") as f:
    for line in f:
        start = 0
        # line = "???.### 1,1,3"
        # line = ".??..??...?##. 1,1,3"
        # ?#?#?#?#?#?#?#? 1,3,1,6
        # ????.#...#... 4,1,1
        # ????.######..#####. 1,6,5
        # ?###???????? 3,2,1
        g, n = line.split(" ")
        n = [int(x) for x in n.split(",")]
        rec(g, n, start = 0)

print(argmts)