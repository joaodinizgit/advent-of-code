import re

D = {}
temp_seed = []
seed = []

def main():
    with open("day5/input.txt", "r") as f:
        # Organize the file's data in a dictionary: D{}.
        for line in f:
            x = re.match("[^0-9\\n\s\\:]+", line)
            if x: 
                key = x.group(0)
                D[key] = []                        

            numbers = re.findall("[0-9]+", line)
            if numbers:
                D[key] += [numbers]


    # Copy seed to a new list in int: seed[].
    for item in D["seeds"][0]:
        seed.append(int(item))

    # Find the lower location number
    for key in D.keys():
        if key != "seeds":
            u(seed, key)

    print(min(seed))


# Part 1
def u(s, k):
    for i in s:
        inRange = False
        for j in D[k]:
            if i >= int(j[1]) and i <= int(j[1]) + int(j[2]) - 1:
                y = i - int(j[1]) + int(j[0])
                temp_seed.append(y)
                inRange = True
        if inRange == False:
            temp_seed.append(i)

    global seed
    seed.clear()
    seed = temp_seed.copy()
    temp_seed.clear()



main()