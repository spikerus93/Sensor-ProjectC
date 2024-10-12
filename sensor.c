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

// Функция для проверки строки на соответствие формату CSV
bool checkCSVFormat(char *row, int rowNumber)
{
    // Разделитель по умолчанию для формата CSV
    const char *separator = ",";
    char *token = strtok(row, separator);
    int columnIndex = 0;

    while (token != NULL)
    {
        if (columnIndex == 5)
        {
            // Пятый элемент - температура
            double temperature;
            if (sscanf(token, "%lf", &temperature) != 1)
            {
                printf("Ошибка в строке %d: неправильный формат температуры.\n", rowNumber);
                return false;
            }
        }
        else if (columnIndex >= 6)
        {
            // Больше пяти колонок - ошибка
            printf("Ошибка в строке %d: слишком много колонок.\n", rowNumber);
            return false;
        }
        columnIndex++;
        token = strtok(NULL, separator);
    }

    if (columnIndex != 6)
    {
        // Недостаточно колонок
        printf("Ошибка в строке %d: недостаточно колонок.\n", rowNumber);
        return false;
    }

    return true;
}