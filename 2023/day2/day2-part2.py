import re
sum_power = 0
rgex_game = "^Game\s[0-9]*:"
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

        # Search for the higest value for each color
        power_of_set = 1
        for cube in cubes_in_bag:
            highest_color = 0
            
            for set in sets:
                qty = count_cubes(cube["rgex"], set)
                #print("Game:",game_id, cube["color"], qty)
                if qty > highest_color:
                    highest_color = qty
                    
            power_of_set *= highest_color
            
        sum_power += power_of_set
    print(sum_power)
