card = input("Number: ")
bits = len(card)

flip = 0
digit_sum = 0
for i in reversed(card):
    if flip == 0:
        flip = 1
        digit_sum += int(i) - 0
    else:
        flip = 0
        even = int(i) - 0
        if even <5:
            even *= 2
        else:
            even = 1 + 2 * (even - 5)
        digit_sum += even

if (digit_sum % 10) == 0:
    if bits in [13, 16] and card[0] == '4':
        print("VISA")
    elif (bits == 15) and (card[0:2] in ['34', '37']):
        print("AMEX")
    elif (bits == 16) and (int(card[0:2]) in range(51, 56)):
        print("MASTERCARD")
    else:
        print("INVALID")
else:
    print("INVALID")

