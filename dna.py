from sys import argv
import csv

# N° database column
column = 0
# N° matched values
winner = 0
# winner column number
matched = 0

AGATC = TCTAG = 0
AATG = GATA = TATC = GAAA = TCTG = 0
TTTTTTCT = 0
temp1 = temp2 = temp3 = temp4 = temp5 = 0
temp6 = temp7 = temp8 = temp9 = temp10 = 0
flag = [0, 0, 0, 0, 0, 0, 0, 0, 0]
flags = ['AGATC', 'TTTTTTCT', 'AATG', 'TCTAG', 'GATA', 'TATC', 'GAAA', 'TCTG']

# open sequences file
sequences = open(argv[2], "r")
# read dna sequence
char = sequences.read()
size = len(char)

# check eight letters sequence
for i in range(size - 9):
    if char[i] == 'T' and char[i + 1] == 'T' and char[i + 2] == 'T' and char[i + 3] == 'T' and char[i + 4] == 'T' and char[i + 5] == 'T' and char[i + 6] == 'C' and char[i + 7] == 'T':
        temp1 = i + 8
        TTTTTTCT += 1
    elif i == temp1 and i != 0:
        if TTTTTTCT > temp2:
            temp2 = TTTTTTCT
            TTTTTTCT = 0
        else:
            TTTTTTCT = 0
    else:
        pass
    # print(TTTTTTCT, i)
TTTTTTCT = temp2
temp1 = temp2 = 0

# check five letters sequence
for i in range(size - 6):
    if char[i] == 'A' and char[i + 1] == 'G' and char[i + 2] == 'A' and char[i + 3] == 'T'and char[i + 4] == 'C':
        temp1 = i + 5
        AGATC += 1
    elif i == temp1 and i != 0:
        if AGATC > temp2:
            temp2 = AGATC
            AGATC = 0
        else:
            AGATC = 0
    else:
        pass
    # print(AGATC, i)

    if char[i] == 'T' and char[i + 1] == 'C' and char[i + 2] == 'T' and char[i + 3] == 'A'and char[i + 4] == 'G':
        temp3 = i + 5
        TCTAG += 1
    elif i == temp3 and i != 0:
        if TCTAG > temp4:
            temp4 = TCTAG
            TCTAG = 0
        else:
            TCTAG = 0
    else:
        pass
    # print(TCTAG, i)
AGATC = temp2
TCTAG = temp4
temp1 = temp2 = temp3 = temp4 = 0

# check four letters sequence
for i in range(size - 5):
    if char[i] == 'A' and char[i + 1] == 'A' and char[i + 2] == 'T' and char[i + 3] == 'G':
        temp1 = i + 4
        AATG += 1
    elif i == temp1 and i != 0:
        if AATG > temp2:
            temp2 = AATG
            AATG = 0
        else:
            AATG = 0
    else:
        pass
    # print(AATG, i)


    if char[i] == 'G' and char[i + 1] == 'A' and char[i + 2] == 'T' and char[i + 3] == 'A':
        temp3 = i + 4
        GATA += 1
    elif i == temp3 and i != 0:
        if GATA > temp4:
            temp4 = GATA
            GATA = 0
        else:
            GATA = 0
    else:
        pass
    # print(GATA, i)


    if char[i] == 'T' and char[i + 1] == 'A' and char[i + 2] == 'T' and char[i + 3] == 'C':
        temp5 = i + 4
        TATC += 1
    elif i == temp5 and i != 0:
        if TATC > temp6:
            temp6 = TATC
            TATC = 0
        else:
            TATC = 0
    else:
        pass
    # print(TATC, i)


    if char[i] == 'G' and char[i + 1] == 'A' and char[i + 2] == 'A' and char[i + 3] == 'A':
        temp7 = i + 4
        GAAA += 1
    elif i == temp7 and i != 0:
        if GAAA > temp8:
            temp8 = GAAA
            GAAA = 0
        else:
            GAAA = 0
    else:
        pass
    # print(GAAA, i)


    if char[i] == 'T' and char[i + 1] == 'C' and char[i + 2] == 'T' and char[i + 3] == 'G':
        temp9 = i + 4
        TCTG += 1
    elif i == temp9 and i != 0:
        if TCTG > temp10:
            temp10 = TCTG
            TCTG = 0
        else:
            TCTG = 0
    else:
        pass
    # print(TCTG, i)
AATG = temp2
GATA = temp4
TATC = temp6
GAAA = temp8
TCTG = temp10

# print(f"AGATC: {AGATC}, TTTTTTCT: {TTTTTTCT}, AATG: {AATG}, TCTAG: {TCTAG}, GATA: {GATA}, TATC: {TATC}, GAAA: {GAAA}, TCTG: {TCTG} ln 145")

# read dna databases
with open(argv[1]) as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    # get every row in dna database
    for row in csv_reader:
        # column zero get dna sequences order
        if column == 0:
            test = len(row)
            for i in range(test):
                if row[i] == 'AGATC':
                    flag[1] = i
                elif row[i] == 'TTTTTTCT':
                    flag[2] = i
                elif row[i] == 'AATG':
                    flag[3] = i
                elif row[i] == 'TCTAG':
                    flag[4] = i
                elif row[i] == 'GATA':
                    flag[5] = i
                elif row[i] == 'TATC':
                    flag[6] = i
                elif row[i] == 'GAAA':
                    flag[7] = i
                elif row[i] == 'TCTG':
                    flag[8] = i
                else:
                    pass
            column += 1
            continue

        # print(type(row[1]))
        # print(type(AGATC))

        # columns greater than zero
        for i in range(9):
            if flag[i] == 0:
                continue
            if i == 1:
                if int(row[flag[i]]) == AGATC:
                    winner += 1
            if i == 2:
                if int(row[flag[i]]) == TTTTTTCT:
                    winner += 1
            if i == 3:
                if int(row[flag[i]]) == AATG:
                    winner += 1
            if i == 4:
                if int(row[flag[i]]) == TCTAG:
                    winner += 1
            if i == 5:
                if int(row[flag[i]]) == GATA:
                    winner += 1
            if i == 6:
                if int(row[flag[i]]) == TATC:
                    winner += 1
            if i == 7:
                if int(row[flag[i]]) == GAAA:
                    winner += 1
            if i == 8:
                if int(row[flag[i]]) == TCTG:
                    winner += 1

        # check sequences number euqlity between database and sequence
        if winner == (len(row) - 1):
            matched = column
            print(row[0])

        winner = 0
        column += 1
        # print(f"Column: {column} row: {row}")


    # print(f"{matched}")
    if matched == 0:
        print("No match")

    # print(f"Column: {column} row[1]: {row[2]}")

csv_file.close()





