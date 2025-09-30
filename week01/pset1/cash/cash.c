// Calculate the least amount of change for a given owe
#include <cs50.h>
#include <stdio.h>

// Base value for each coin
#define QUATER 25
#define DIME 10
#define NICKEL 5
#define PENNY 1

int get_owe(void);
int get_change(int owe);
int cal_base(int owe, int base);

int main(void)
{
    // Get legal input for owe
    int owe = get_owe();
    // Calculate the number of coin for given owe
    int num_coin = get_change(owe);
    printf("%i\n", num_coin);
}

// Get positive number of owe
int get_owe(void)
{
    int owe;
    do
    {
        owe = get_int("Change owed: ");
    }
    while (owe < 0);
    return owe;
}

// Calculate the least number of coin by greedy alg.
int get_change(int owe)
{
    // Get coin numbers for each base respectively
    int quaters = cal_base(owe, QUATER);
    owe = owe - QUATER * quaters;

    int dimes = cal_base(owe, DIME);
    owe = owe - DIME * dimes;

    int nickels = cal_base(owe, NICKEL);
    owe = owe - NICKEL * nickels;

    int pennies = cal_base(owe, PENNY);

    int total_number = quaters + dimes + nickels + pennies;

    return total_number;
}

// Maximum coin numbers with value of base
int cal_base(int owe, int base)
{
    return owe / base;
}
