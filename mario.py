text = 0
number = 0

#check for a valid input
while number < 1 or number > 8:

    text = input("Height: ")
    #if is a decimal convert str to int
    if text.isdecimal() == True:
        number = int(text)
    #if is an alphabetic, set 999
    elif text.isalpha() == True:
        number = 999
    #if something else, set 777
    else:
        number = 777

#print every level
for i in range(number):
    space = number - i - 1

    #print left side spaces
    for j in range(space):
        print(" ", end = '')

    #print left side #
    for k  in range(i + 1):
        print("#", end = ''),

    #print two central spaces
    print("  ", end = '')

    #print right side #
    for l  in range(i + 1):
        print("#", end = ''),

    #print right side spaces
    for m in range(space):
        print(" ", end = ''),
    #finish print actual level and jump to the next one
    else:
        print("")
