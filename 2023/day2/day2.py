import re

rgex_game = "^Game\s[0-9]*:"
sum_valid_games = 0
cubes_in_bag = [{"color": "red", "qty": 12, "rgex": "[0-9]*\sred"},
                {"color": "green", "qty": 13, "rgex": "[0-9]*\sgreen"},
                {"color": "blue", "qty": 14, "rgex": "[0-9]*\sblue"}]

# Read the file, line by line
with open("puzzle-input-day2.txt", "r") as file:
    sum_valid_games = 0
    for line in file:
        # Game Id of current line
        game = re.search(rgex_game, line)
        game_id = int(re.sub("\D", "", game.group()))

        # Break the sets of current line
        only_sets = re.sub(rgex_game, "", line).strip()
        sets = only_sets.split(";")

        def count_cubes(regex,set):
            """ Function to count cube colors by set"""
            x = re.search(regex, set)
            if x != None:
                #Isolate the number
                return(int(re.sub("\D", "", x.group()))) 
            else:
                return 0

        # Read each set and check each cube color quantity,
        # if a set have a number of cubes higher than the quantity
        # in the bag it'll invalidate de game and go to next game.
        cube_qty_high = False
        for set in sets:
            if cube_qty_high:
                break
            for cube in cubes_in_bag:
                y = count_cubes(cube["rgex"], set)
                # Check if the cube qty is higher than in bag
                if y > cube["qty"]:
                    cube_qty_high = True
                    break
                if (set == sets[-1] and cube == cubes_in_bag[-1] and
                    y <= cube["qty"]):
                    sum_valid_games += game_id
                    
print(sum_valid_games)
