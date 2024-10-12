#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>

#define SIZE 30

struct sensor
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    double temperature;
};