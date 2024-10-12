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

// Функция для добавления новой записи
void AddRecord(struct sensor *info, int index, int year, int month, int day, int hour, int minute, double temperature)
{
    info[index].year = year;
    info[index].month = month;
    info[index].day = day;
    info[index].hour = hour;
    info[index].minute = minute;
    info[index].temperature = temperature;
}