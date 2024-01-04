valid_digits = ["one", "two", "three", "four", "five",
                "six", "seven", "eight", "nine", "0",
                "1", "2", "3","4", "5", "6", "7", "8", "9"]

digits_to_replace = {"one" : "1", "two": "2", "three": "3",
                     "four": "4", "five": "5", "six": "6",
                     "seven": "7", "eight": "8", "nine": "9"}

with open("puzzle-input.txt", "r") as file:
    sum_calibration_values = 0
      
    for line in file:
        digits_found_indexed = {}
        digits_of_line = []
        def find_digit(digit, from_index=0):
            """ Look for valid digits in line with the
            start index and store.
            """
            index_of_digit = line.find(digit, from_index)
            if index_of_digit == -1:
                return
            digits_found_indexed[index_of_digit] = digit
            find_digit(digit, index_of_digit + 1)

        # Search for valid digits in current line
        for digit in valid_digits:
            find_digit(digit)

        # Store the digits by index order
        for digit in sorted(digits_found_indexed):
            digits_of_line.append(digits_found_indexed[digit])

        # Replace the first digit with number if necessary
        if digits_of_line[0] in digits_to_replace:
            digits_of_line[0] = digits_to_replace[digits_of_line[0]]

        # Replace the last digit by number if necessary
        if digits_of_line[-1] in digits_to_replace:
            digits_of_line[-1] = digits_to_replace[digits_of_line[-1]]

        # Concatenated the first and last digit of line and sum
        # with previous calibration value
        sum_calibration_values += int(digits_of_line[0] +
                                      digits_of_line[-1])

print(sum_calibration_values)
