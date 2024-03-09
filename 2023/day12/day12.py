from itertools import product
from itertools import permutations
import re
import time
start_time = time.time()

arrangements = 0
with open("input.txt") as f:
    for line in f:
        #line = "????.######..#####. 1,6,5"
        nqm = line.count("?")
        x = line.split(" ")
        m = str(x[0])
        g = [int(x) for x in x[1].split(",")]

        #print("----")

        perm = product("#.", repeat = nqm)
        for i in list(perm):
            for j in i:
                m = m.replace("?", j, 1)
            y = re.findall("#+", m)
            if len(y) == len(g):
                z = [len(x) for x in y]
                if z == g:
                    arrangements += 1
            m = str(x[0])

print(f"Arrangements are {arrangements}")


end_time = time.time()
elapsed_time = end_time - start_time
print(f"Execution time: {elapsed_time:.6f} seconds")