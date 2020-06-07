#include <stdio.h>

int day_of_year( int, int, int);

int main() {
    printf("%i\n", day_of_year(2020, 3, 28));
    return 0;
}

static int daytab[2][13] = {
        {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
        {0, 31 ,29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int isleap(int);

int day_of_year(int year, int month, int day)
{
    int leap = isleap(year);
    if (month > 12 || day > *(*daytab + (leap * 13 + month)) || day < 1)
        return -1;
    for (int i = 1; i < month; ++i)
        day += *(*daytab + (leap * 13 + i));

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

    for (i = 1; yearday > *(*daytab + (leap * 13 + i)) ; ++i) {
        yearday -= *(*daytab + (leap * 13 + i));
    }

    *pmonth = i;
    *pday = yearday;
}

int isleap(int year)
{
    return (year%4 == 0 && year%100) != 0 || year%400 == 0;
}
