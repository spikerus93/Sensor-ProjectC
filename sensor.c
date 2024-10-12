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

// Функция для получения данных от пользователя
int AddInfo(struct sensor *info)
{
    int counter = 0;
    printf("Введите данные в следующем формате: YEAR;MONTH;DAY;HOUR;MINUTE;TEMPERATURE\n");

    while (1)
    {
        printf("Информация для сенсора №%d:\n", counter + 1);

        int year;
        int month;
        int day;
        int hour;
        int minute;
        double temperature;

        if (scanf("%d;%d;%d;%d;%d;%lf\n", &year, &month, &day, &hour, &minute, &temperature) != 6 || counter == SIZE)
        {
            // Если сканер вернул ошибку или количество объема данных достингуто, тогда выходим из цикла
            printf("Неверный ввод...\n");
            break;
        }
        AddRecord(info, counter++, year, month, day, hour, minute, temperature);
    }

    return counter;
}