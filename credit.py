credit_number_str = " "
size = 0
check = number = 0
digit = digit1 = digit2 = 0
checksum = 0

#check for a valid input
while credit_number_str.isdecimal() == False:

    credit_number_str = input("Number: ")

#if it is a valid, convert str to int and get size
credit_number_int = int(credit_number_str)
size = len(credit_number_str)

#check a valid size number
if size not in [13, 14, 15, 16]:

    print("INVALID")

else:

    number = credit_number_int

    #get digit by digit from the whole number
    while number != 0:
        #get digit by digit - right to left
        digit = number % 10
        #check number of digits
        check += 1

        #when only remains two digits, save the second digit (left to right)
        if number < 100 and number > 9:
            digit2 = digit
        else: pass

        #when only remain one digit, save first digit
        if number < 10:
            digit1 = digit
        else: pass

        number = int(number / 10)

        #add every digit for get checksum
        if check % 2 == 0:
            if digit * 2 >= 10:
                temp1 = (digit * 2) % 10
                checksum = checksum + temp1 + 1
            else:
                checksum = checksum + (digit * 2)
        else:
            checksum = checksum + digit

    #print("NOPE {} {} {} {}".format(digit1, digit2, check, checksum))
    """
    //VISA          SIZE: 13 to 16      FIRST NUMBERS: 4
    //AMEX          SIZE: 15            FIRST NUMBERS: 34 or 37
    //MASTERCARD    SIZE: 16            FIRST NUMBERS: 51 to 55
    """

    #check for VISA conditions
    if digit1 == 4 and size in [13, 14, 15, 16] and checksum % 10 == 0:
        print("VISA")
    #check for AMERICAN EXPRESS conditions
    elif digit1 == 3 and digit2 in [4, 5, 6, 7] and size == 15 and checksum % 10 == 0:
        print("AMEX")
    #check for MASTERCARD conditions
    elif digit1 == 5 and digit2 in [1, 2, 3, 4, 5] and size == 16 and checksum % 10 == 0:
        print("MASTERCARD")
    #something else is an INVALID number
    else:
        print("INVALID")




