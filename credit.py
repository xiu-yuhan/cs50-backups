
cardNum = int(input("Number: "))

#checks for invalid length of numbers
if(cardNum >10000000000000000 or cardNum < 1000000000000):
    print("INVALID")
else:
    sum = 0

    #gets the value for every other digit in the card number, then multiplys it by 2
    #then adds that value to sum
    i = int(cardNum/10)
    while(i > 0):
        if (i%10*2 > 9):
            sum = int(sum + (((i%10)*2)/10) + (((i%10)*2)%10))
        else:
            sum = int(sum + ((i%10)*2))
        i = int(i/100)


    #adds the digits in the card number that weren't multiplyed by 2 to the total sum
    n = cardNum
    while(n > 0):
        sum = int(sum + (n%10))
        n = int(n/100)


    #checks if the card is valid from our providers
    while(cardNum>100):
        cardNum = int(cardNum/10)

    if (int(sum%10)==0 and int(cardNum/10) == 4):
        print("VISA")

    elif(int(sum%10)==0 and (cardNum == 37 or cardNum == 34)):
        print("AMEX")

    elif(int(sum%10)==0 and cardNum >50 and cardNum < 56):
        print("MASTERCARD")

    else:
        print("INVALID")
