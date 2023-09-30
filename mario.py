height = 4
while(True):
    try:
        height = int(input("Height: "))
        if (height > 0 and height < 9 ):
            break
    except ValueError:
        None


num = 1
for x in range(height):
    for i in range (height-num):
        print(' ',end = '')
    for y in range(num):
        print('#', end = '')
    print('  ', end = '')
    for z in range(num):
        print('#', end = '')
    num += 1
    print()