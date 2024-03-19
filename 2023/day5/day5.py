import re

almanac = {}
locations = []

def main():
    with open("input.txt", "r") as file:
        for line in file:
            text = re.match("[^0-9\\n\s\\:]+", line)
            if text:
                key = text.group(0)
                almanac[key] = []

            numbers = [int(x) for x in re.findall("[0-9]+", line)]
            if numbers:
                almanac[key] += [numbers]

    seeds = almanac["seeds"][0].copy()

    for key in almanac.keys():
        if key != "seeds":
            seeds = conversor_one(seeds, key)
    print(f"Part 1 answer: {(min(seeds))}")

    # Calculating Part 2
    s = almanac["seeds"][0]

    # Verify 10 pairs in a step of 20,000 to obtain approximated lower location.
    # Lower values is more precise, but slow processing.
    for i in range(0, len(s), 2):
        r = s[i], s[i] + s[i+1]
        lower_location(r, 20000)

    print(f"Approximated value found: {locations[0][0]} within {locations[0][2]}, around the number: {locations[0][1]}")

    r = (locations[0][1] - 1000,
         locations[0][1] + 0,)

    lower_location(r, 1)
    print(f"Part 2 answer: Lower location is {locations[0][0]}")


def lower_location(r, steps):
    for seed in range(r[0], r[1], steps):
        f = seed
        for key in almanac.keys():
            if key != "seeds":
                seed = conversor_two(seed, key)
        global locations
        locations.append([seed, f, r])
        locations = [min(locations)]

    return


def conversor_two(seed, key):
    for numbers in almanac[key]:
        if seed >= numbers[1] and seed < numbers[1] + numbers[2]:
            return seed - numbers[1] + numbers[0]

    return seed


def conversor_one(seeds, key):
    temp = []
    for seed in seeds:
        inRange = False
        for numbers in almanac[key]:
            if seed >= numbers[1] and seed < numbers[1] + numbers[2]:
                temp.append(seed - numbers[1] + numbers[0])
                inRange = True
                break
        if inRange == False:
            temp.append(seed)

    return temp


main()

# The answers from the input.txt file are:
# Part 1: 650599855
# Part 2: 1240035