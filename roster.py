from sys import argv
from cs50 import SQL

if len(argv) != 2:
    print("COMMAND LINE ARGUMENTS ERROR")


db = SQL("sqlite:///students.db")

result = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first", argv[1])

for fila in result:
    if fila['middle'] == None:
        print("{} {}, born {}".format(fila['first'], fila['last'], fila['birth']))
    else:
        print("{} {} {}, born {}".format(fila['first'], fila['middle'], fila['last'], fila['birth']))

