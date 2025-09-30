#include <cs50.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    string name;
    string number;
}people;

int main(void)
{
    people phone_book[2]={};
    phone_book[0].name = "Liu";
    phone_book[0].number = "1860";
    phone_book[1].name = "Cheng";
    phone_book[1].number = "6580";

    string s = get_string("Name: ");
    for (int i = 0; i < 2; i++)
    {
        if (strcmp(phone_book[i].name, s) == 0)
        {
            printf("Number: %s\n", phone_book[i].number);
            return 0;
        }
    }
    printf("Not Found.\n");
    return 1;
}
