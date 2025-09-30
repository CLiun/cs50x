from cs50 import get_float


def main():
    while True:
        owed = get_float("Owed: ")
        if owed > 0:
            break
    owed *= 100
    total = 0
    for base in [25, 10, 5, 1]:
        coins = owed // base
        total += coins
        owed = owed - base * coins
    print(int(total))


if __name__ == "__main__":
    main()
