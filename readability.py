
#get input
ok = False
while ok == False:
    text = input("Text: ")
    if len(text) > 7:
        ok = True

letters = words = sentences = 0
avgletters = avgsentences = index = 0.0

#check every character
for x in text:
    #check and count for an alphabetic character
    if x.isalpha() == True:
        letters += 1
    #check and count for every word
    elif x == " ":
        words += 1
    #check and count for every sentence
    elif x in [".", "!", "?"]:
        sentences += 1
    else: pass

#add the last word (close to a point)
if len(text) > 0:
    words += 1

#get avg letter for hundred words
avgletters = (letters / words) * 100
#get avg sentences for hundred words
avgsentences = (sentences / words) * 100

#calculate index = 0.0588 * L - 0.296 * S - 15.8
index = (0.0588 * avgletters) - (0.296 * avgsentences) - 15.8
indexint = round(index)

#print results
if indexint < 1 or words < 5:
    print("Before Grade 1")
elif indexint >= 16:
    print("Grade 16+")
else:
    print(f"Grade {indexint}")



#print(f"{letters} {words} {sentences} {avgletters} {avgsentences} {index} {indexint}")
