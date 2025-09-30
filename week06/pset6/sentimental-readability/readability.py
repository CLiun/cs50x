from cs50 import get_string


def main():
    text = get_string("Text: ")
    words = 1
    letters = 0
    sentences = 0
    for char in text:
        if char.isspace():
            words += 1
        if char.isalpha():
            letters += 1
        if char in ['.', '?', '!']:
            sentences += 1
    index = 0.0588 * letters / words * 100 - 0.296 * sentences / words * 100 - 15.8
    rank = round(index)

    if rank < 0:
        print("Before Grade 1")
    elif rank < 16:
        print(f"Grade {rank}")
    else:
        print("Grade 16+")


if __name__ == "__main__":
    main()
