from sys import argv
from cs50 import SQL
import csv

#check for a valid command argument
if len(argv) != 2:
    print("INVALID COMMAND LINE ARGUMENT")
    exit

#db = SQL("sqlite:///students.db")

db = SQL("sqlite:///students.db")
#db.execute("CREATE TABLE students (id INTEGER PRIMARY KEY AUTOINCREMENT, first VARCHAR(255), middle VARCHAR(255), last VARCHAR(255), house VARCHAR(255), birth INTEGER)")

#open csv file in command line
with open(argv[1]) as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=",")
    firstrow = 0
    #check every row into csv file
    for row in csv_reader:
        #First row ignored, they are the titles
        if firstrow == 0:
            firstrow =+ 1
            continue
        #row[0] -> full name    row[1] -> House     row[2] -> birth
        #namelist[0] -> first name      namelist[1] -> middle name      namelist[2] -> last name
        namelist = row[0].split(" ")

        #check if name has middle name
        if len(namelist) == 3:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)", namelist[0], namelist[1], namelist[2], row[1], row[2])
        elif len(namelist) == 2:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, NULL, ?, ?, ?)", namelist[0], namelist[1], row[1], row[2])
        else:
            continue

csv_file.close()


