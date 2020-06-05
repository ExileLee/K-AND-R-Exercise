#include <stdio.h>

int main() {
    printf("Hello, World!\n");
    return 0;
}

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31 ,29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int isleap(int);

int day_of_year(unsigned int year, unsigned int month, unsigned int day)
{
    int leap = isleap(year);
    if (month > 12 || day > daytab[leap][month] || day < 1)
        return -1;
    for (int i = 1; i < month; ++i)
        day += daytab[leap][i];

    return day;
}

void day_of_month(unsigned int year, unsigned int yearday, int *pmonth, int *pday)
{
    int i;
    int leap = isleap(year);
    int maxdays = 0;
    for (int j = 1; j <= 12; ++j) {
        maxdays += daytab[leap][j];
    }

    if (yearday > maxdays)
        return;

    for (i = 1; yearday > daytab[leap][i] ; ++i) {
        yearday -= daytab[leap][i];
    }

    *pmonth = i;
    *pday = yearday;
}

int isleap(int year)
{
    return year%4 == 0 && year%100 != 0 || year%400 == 0;
}
