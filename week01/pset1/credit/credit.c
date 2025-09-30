// Calculate the validity of credit card number
// Step: get number, count digit, odd digit--add, even digit 0-4 multiply, 5-9 2i+1
#include <cs50.h>
#include <stdio.h>

long get_card();
void decide_company(int sum, int count, int left1, int left2);

int main(void)
{
    // Get positive input
    long card_num = get_card();

    // Calculate digits and luhn sum
    int digit_cnt = 0;
    int sum = 0, remainder = 0;

    // left1 for most left digit, left2 for second left digit
    int left1 = 0, left2 = 0;

    // Get each digit from right to left, save the most 2 left digit to decide company
    while (card_num > 0)
    {
        digit_cnt++;
        left2 = left1;
        remainder = card_num % 10;
        card_num /= 10;
        left1 = remainder;
        if (digit_cnt % 2 != 0)
        {
            sum += remainder;
        }
        else
        {
            if (remainder < 5)
            {
                sum += remainder * 2;
            }
            else
            {
                sum += 1 + (remainder - 5) * 2;
            }
        }
    }

    // If luhn sum valid, decide company by digits
    decide_company(sum, digit_cnt, left1, left2);
}

long get_card()
{
    long card_num = 0;
    do
    {
        card_num = get_long("Number: ");
    }
    while (card_num < 0);
    return card_num;
}

// Given luhn sum, card digits. Decide valid or not
void decide_company(int sum, int count, int left1, int left2)
{
    if (sum % 10 != 0)
    {
        printf("INVALID\n");
    }
    else
    {
        if (left1 == 4 && (count == 13 || count == 16))
        {
            printf("VISA\n");
        }
        else if (left1 == 5 && left2 < 6 && left2 > 0 && count == 16)
        {
            printf("MASTERCARD\n");
        }
        else if (left1 == 3 && (left2 == 4 || left2 == 7) && count == 15)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
}
