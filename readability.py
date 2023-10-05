def count_letters(text):
    abc = ["a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"]
    letters = 0
    for i in range(len(text)):
        for j in range(26):
            if (text[i].lower() == abc[j]):
                letters += 1
    return letters

def count_words(text):
    words = 1
    for i in range(len(text)):
        if (text[i] == ' '):
            words += 1
    return words

def count_sentences(text):
    sentences = 0
    for i in range(len(text)):
        if(text[i] == '.' or text[i] == '?' or text[i] == '!'):
            sentences += 1
    return sentences




inPut = input("Text: ")
ind = ((((count_letters(inPut)*100)/count_words(inPut)) * .0588) - (((count_sentences(inPut)*100)/count_words(inPut)) * .296)) - 15.8

ind = round(ind)
if (ind < 1):
    print("Before Grade 1")
elif(ind > 16):
    print("Grade 16+")
else:
    print("Grade " + str(ind))