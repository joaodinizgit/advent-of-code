import re
matrix = []
sum_part_numbers = 0
sum_all_gear_ratios = 0

# Open the file and copy to matrix variable, line by line
# except new line character.
with open("input.txt", "r") as file:
    for line in file:
        y = re.search(".+", line)
        matrix.append(y.group())

def part_number(number, line):
    """ Look if the number have symbols adjacent. """
    
    line_below = line + 1
    line_above = line - 1
    posi_check = list(range(number.start() - 1, number.end() + 1))
    
    # Check if the number have symbol on left side.
    if (number.start() > 0
        and re.search("[^.\d]", matrix[line][number.start() - 1])):
        return(int(number.group()))

    # Check if the number have symbol on right side.
    if ((number.end() < len(matrix[line])) and
        re.search("[^.\d]", matrix[line][number.end()])):
        return(int(number.group()))
    
    # Check for symbols in line above and below the number.
    for index in posi_check:
        if index >= 0 and index < len(matrix) - 1:
            if line == 0:
                if re.search("[^.\d]", matrix[line_below][index]):
                    return(int(number.group()))
            elif line < len(matrix) - 1:
                if (re.search("[^.\d]", matrix[line_below][index]) or
                    re.search("[^.\d]", matrix[line_above][index])):
                    return(int(number.group()))
            else:
                if re.search("[^.\d]", matrix[line_above][index]):
                    return(int(number.group()))

                
def gear_ratios(symbol, line):
    """ Function to determine if the symbol is a gear
    it must have only two adjacent numbers """
    
    adjacent_numbers = 0
    multiply_ratios = 1
    line_above = line - 1
    line_below = line + 1
    symbol_index = symbol.start()

    # posi_check is a list of indexes that are adjacent to symbol.
    posi_check = list(range(symbol.start() - 1, symbol.end() + 1))

    # Determine a list of valid indexes to check for numbers.
    for number in posi_check:
        if number < 0 or number >= len(matrix[line]) :
            posi_check.remove(number)

    # Look for numbers indexes positions on the line "above" the symbol.
    if line_above >= 0 :
        for number in re.finditer("\d+", matrix[line_above]):
            # Check if any number's index is in symbol adjacent
            # indexes(posi_check).
            for index in list(range(number.start(), number.end())):
                if index in posi_check:
                    adjacent_numbers += 1
                    multiply_ratios *= int(number.group())
                    break
             
    # Look for numbers indexes position on line "below" the symbol
    if line_below < len(matrix):
        for number in re.finditer("\d+", matrix[line_below]):
            # Check if any number's index is in symbol adjacent
            # indexes(posi_check).
            for index in list(range(number.start(), number.end())):
                if index in posi_check:
                    adjacent_numbers += 1
                    multiply_ratios *= int(number.group())
                    break

    # Look for numbers indexes position on left or right from the symbol.
    for number in re.finditer("\d+", matrix[line]):
        if number.end() - 1 == posi_check[0]:
            adjacent_numbers += 1
            multiply_ratios *= int(number.group())
        elif number.start() == posi_check[-1]:
            adjacent_numbers += 1
            multiply_ratios *= int(number.group())
        
    # Check if the symbol have "exactly" two adjacent numbers.
    if adjacent_numbers == 2:
        return multiply_ratios
        
        
# (PART 1) Loop on every line looking for numbers
for line in range(len(matrix)):
    # For each number found in line, send to part_number function
    for number in re.finditer("\d+", matrix[line]):
        y = part_number(number, line)
        if y != None:
            sum_part_numbers += y
print("Sum of all Part Numbers: ", sum_part_numbers)
            

# (PART 2) Find sum of all Gear Ratios
for line in range(len(matrix)):
    # For each symbol found in line, send to gear_ratios function
    for symbol in re.finditer("\*", matrix[line]):
        y = gear_ratios(symbol, line)
        if y != None:
            sum_all_gear_ratios += y
print("Sum of all Gears Ratios: ", sum_all_gear_ratios)
        
