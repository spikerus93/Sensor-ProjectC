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

// Функция для чтения и проверки данных из файла CSV
void validateInputFile(const char *inputFilename)
{
    FILE *file = fopen(inputFilename, "r");
    if (file == NULL)
    {
        perror("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }

    char row[1024];
    int rowNumber = 0;
    bool isErrorFound = false;

    while (fgets(row, sizeof(row), file) != NULL)
    {
        rowNumber++;
        if (!checkCSVFormat(row, rowNumber))
        {
            isErrorFound = true;
        }
    }

    fclose(file);

    if (isErrorFound)
    {
        printf("Ошибки в файле CSV обнаружены.\n");
    }
    else
    {
        printf("Файл CSV проверен, ошибок не обнаружено.\n");
    }
}

// Функция для расчета средней температуры
double calculateAverageTemperature(struct sensor *info, int count)
{
    double sum = 0.0;
    for (int i = 0; i < count; ++i)
    {
        sum += info[i].temperature;
    }
    return sum / count;
}

// Функция для расчета минимальной температуры
double findMinimumTemperature(struct sensor *info, int count)
{
    double min = info[0].temperature;
    for (int i = 1; i < count; ++i)
    {
        if (info[i].temperature < min)
        {
            min = info[i].temperature;
        }
    }
    return min;
}

// Функция для расчета максимальной температуры
double findMaximumTemperature(struct sensor *info, int count)
{
    double max = info[0].temperature;
    for (int i = 1; i < count; ++i)
    {
        if (info[i].temperature > max)
        {
            max = info[i].temperature;
        }
    }
    return max;
}

// Функция для вывода статистики по месяцам
void displayMonthStatistics(struct sensor *info, int count)
{
    for (int i = 0; i < count; ++i)
    {
        double avg = calculateAverageTemperature(&info[i], count);
        double min = findMinimumTemperature(&info[i], count);
        double max = findMaximumTemperature(&info[i], count);
        printf("Месяц: %d\n", info[i].month);
        printf("Средняя температура: %.2lf\n", avg);
        printf("Минимальная температура: %.2lf\n", min);
        printf("Максимальная температура: %.2lf\n\n", max);
    }
}

// Функция для вывода статистики за год
void displayYearStatistics(struct sensor *info, int count)
{
    double totalSum = 0.0;
    for (int i = 0; i < count; ++i)
    {
        totalSum += info[i].temperature;
    }
    double annualAverage = totalSum / count;
    double min = findMinimumTemperature(info, count);
    double max = findMaximumTemperature(info, count);
    printf("Среднегодовая температура: %.2lf\n", annualAverage);
    printf("Минимальная температура: %.2lf\n", min);
    printf("Максимальная температура: %.2lf\n", max);
}

int main()
{
    setlocale(LC_ALL, "russian");

    int mode;
    printf("Выберите режим:\n1 - Ручной ввод данных\n2 - Проверка данных из файла\n");
    scanf("%d", &mode);

    switch (mode)
    {
    case 1:
    {
        struct sensor sensors[SIZE];
        int numRecords = AddInfo(sensors);

        // Записываем данные в файл
        FILE *file = fopen("sensordata.сsv", "w");
        if (file == NULL)
        {
            perror("Ошибка открытия файла");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < numRecords; i++)
        {
            fprintf(file, "%d;%d;%d;%d;%d;%.2lf\n", sensors[i].year, sensors[i].month, sensors[i].day, sensors[i].hour, sensors[i].minute, sensors[i].temperature);
        }

        fclose(file);
        break;

    case 2:
        validateInputFile("temperature_small.csv");
        break;

    default:
        printf("Неверный выбор режима. Программа завершена.");
        break;
    }
    }
    return 0;
}