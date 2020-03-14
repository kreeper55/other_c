#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// 3 % 15 + 10 = 13 вариант

#define ARR_SIZE 10    //  размер числа
#define NUMBER_SYSTEM 13     //  система счисления

const char alphabet[] = {   '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                            'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

//  определяем тип unsigned long long int для удобства записи
typedef unsigned long long ull;

//  функция возведения числа в степень (для больших чисел)
ull pow_ull(const int number, const int degree)
{
    ull result = 1;
    for (int i = 0; i < degree; i++)
        result *= number;
    return result;
}

//  вывод числа(буквы) в заданной системе счисления
void print_numeral(const int numeral);

//  вывод числа
void print_number(const int* number);

//  копирование числа
void copy_num(const int* copy, int* number);

//  сумма чисел в заданной системе счисления
void sum_num(const int* number_left, const int* number_right, int* sum);

//  разность чисел
void difference_num(const int* number_left, const int* number_right, int* sum);

//  инициализируем число(массив) по числу(в десятичной СС)
void init_arr_num(ull decimal_number, int* arr_number);

//  сохраняем число(из массива) в переменную типа unsigned long long
void save_num(const int* arr_number, ull* decimal_number);

//  переводим в 13-ричную СС (для записи в файл)
void to_thirteen_system(char* thirteen_number);

//  перевод в двоичную СС (для записи в файл)
ull to_binary_sys(int number);

//  запись в файл таблицы СС
//  10-я 2-я 16-я 13-я
void create_table();

//  тесты
int main()
{
    setlocale(0, "rus");
    //  инициализируем числа для тестов
    int number1[] = {0, 0, 0, 12, 5, 12, 12, 0, 1, 11};
    int number2[] = {0, 0, 2, 10, 2, 3, 12, 4, 7, 9};
    int number3[] = {12, 12, 1, 8, 10, 11, 6, 0, 10, 7};
    int number4[ARR_SIZE];  // for init
    int result[ARR_SIZE];   //  для вычисления сумм, разности чисел
    int is_equal = 1;       //  для проверки тестов
    int all_is_equal = 1;   //  для проверки всех тестов

    //  выводим числа в диапозоне СС и вне его
    printf("\nТЕСТ 1. Печать цифры\n");
    print_numeral(0);
    printf("\t код = 0\n");
    print_numeral(8);
    printf("\t код = 8\n");
    print_numeral(10);
    printf("\t код = 10\n");
    print_numeral(12);
    printf("\t код = 12\n");

    //  пытаемся вывести число вне данного диапозона (они не отобразятся на экране)
    print_numeral(13);
    printf("\n");
    print_numeral(-3);
    printf("_____________________________________\n");

    //  выводим числа, которые объявили выше
    printf("\nТЕСТ 2. Печать числа\n");
    printf("number1 = ");
    print_number(number1);
    printf("\n");
    printf("number2 = ");
    print_number(number2);
    printf("\n");
    printf("number3 = ");
    print_number(number3);
    printf("\n");
    printf("копируем из number2 в number4\n");
    copy_num(number2, number4);
    printf("number4 = ");
    print_number(number4);
    printf("\n");
    printf("_____________________________________\n");

    //  инициализируем число с помощью переменной (из 10 в 13 СС)
    printf("\nТЕСТ 3. число из 10-й СС в 13-ю СС\n");
    int test3_1[] = {0, 0, 12, 10, 12, 4, 9, 12, 0, 1};
    int test3_2[] = {12, 12, 12, 12, 12, 12, 12, 12, 12, 0};
    is_equal = 1;
    ull long_num_1 = 805841856llu;
    init_arr_num(long_num_1, number4);
    printf("1) число в 10-й СС = %d\n число в 13-й СС = ", long_num_1);
    print_number(number4);
    printf("\n");
    //  сравниваем наше число с тем, что должно получиться
    for (int i = 0; i < ARR_SIZE; i++)
    {
        if (test3_1[i] != number4[i])
        {
            all_is_equal = 0;
            is_equal = 0;
            break;
        }
    }
    //  выводим результат сравнения выше
    if (is_equal)
        printf("ТЕСТ 3_1 ПРОЙДЕН\n");
    else
        printf("ТЕСТ 3_1 ПРОВАЛЕН\n");

    printf("\n");
    ull long_num_2 = 137858491836llu;     //  максимальное число длиной в десять символов
    init_arr_num(long_num_2, number4);    //  иниц-м число в 13 большим числом в 10й
    printf("2) число в 10-й СС = %llu\n число в 13-й СС = ", long_num_2);
    print_number(number4);
    printf("\n");
    for (int i = 0; i < ARR_SIZE; i++)
    {
        if (test3_2[i] != number4[i])
        {
            all_is_equal = 0;
            is_equal = 0;
            break;
        }
    }
    if (is_equal)
        printf("ТЕСТ 3_2 ПРОЙДЕН\n");
    else
        printf("ТЕСТ 3_2 ПРОВАЛЕН\n");
    printf("\n");
    printf("_____________________________________\n");

    //  проверяем как складываются числа в 13 СС
    printf("\nТЕСТ 4. СУММА ЧИСЕЛ В 13 СС\n");
    int test4[] = {0, 0, 3, 9, 8, 3, 11, 4, 9, 7};
    is_equal = 1;
    print_number(number1);
    printf(" + ");
    print_number(number2);
    sum_num(number1, number2, result);
    printf(" = ");
    print_number(result);
    printf("\n");
    for (int i = 0; i < ARR_SIZE; i++)
    {
        if (test4[i] != result[i])
        {
            all_is_equal = 0;
            is_equal = 0;
            break;
        }
    }
    if (is_equal)
        printf("ТЕСТ 4 ПРОЙДЕН");
    else
        printf("ТЕСТ 4 ПРОВАЛЕН");
    printf("\n");
    printf("_____________________________________\n");

    //  проверка вычитания в 13 СС
    printf("\nТЕСТ 5. РАЗНОСТЬ ЧИСЕЛ В 13-Й СС\n");
    int test5[] = {12, 11, 11, 11, 8, 7, 6, 9, 2, 11};
    is_equal = 1;
    print_number(number3);
    printf(" - ");
    print_number(number2);
    difference_num(number3, number2, result);
    printf(" = ");
    print_number(result);
    printf("\n");
    for (int i = 0; i < ARR_SIZE; i++)
    {
        if (test5[i] != result[i])
        {
            all_is_equal = 0;
            is_equal = 0;
            break;
        }
    }
    if (is_equal)
        printf("ТЕСТ 5 ПРОЙДЕН");
    else
        printf("ТЕСТ 5 ПРОВАЛЕН");
    printf("\n");
    printf("_____________________________________\n");

    //  сохраняем число из 13 в 10 СС
    printf("\nТЕСТ 6. сохраняем число \n(которое представлено в виде массива в переменную \n");
    int test6[ARR_SIZE];
    copy_num(number3, test6);
    ull test6_long = 137148164537llu;
    ull* variable = (ull*)malloc(sizeof(ull));
    save_num(test6, variable);
    printf("ожидаемое число = %llu \nполучили на самом деле = %llu\n", test6_long, *variable);
    if (test6_long == *variable)
    {
        printf("ТЕСТ 6 ПРОЙДЕН");
    }
    else
    {
        all_is_equal = 0;
        printf("ТЕСТ 6 ПРОВАЛЕН");
    }
    free(variable);
    printf("\n");
    printf("_____________________________________\n");

    //  если все тесты пройдены, то выводим на экран соответствующее сообщение
    if (all_is_equal)
        printf("ВСЕ ТЕСТЫ ПРОЙДЕНЫ УСПЕШНО\n");
    else
        printf("НЕ ВСЕ ТЕСТЫ ПРОЙДЕНЫ\n");

    printf("\nТЕСТ запись таблицы в файл. \n\n");
    create_table();    //  создаем табличку с 10, 2, 16, 13 СС

    printf("\nНажмите Enter чтобы выйти\n");
    getchar();
    return 0;
}

//  вывод числа(буквы) в заданной системе счисления
void print_numeral(const int numeral)
{
    //  проверка на диапозон
    if (numeral >= 0 && numeral < NUMBER_SYSTEM)
        printf("%c", alphabet[numeral]);
    //  если прошли проверку, выводим число из нашего алфавита
}

//  вывод числа
void print_number(const int* number)
{
    for (int i = 0; i < ARR_SIZE; i++)
        print_numeral(number[i]);
    //  выводим поочередно число
}

//  копирование числа
void copy_num(const int* copy, int* number)
{
    for (int i = 0; i < ARR_SIZE; i++)
        number[i] = copy[i];
    //  копируем каждый элемент в массив arr
}

//  сумма чисел в заданной системе счисления
void sum_num(const int* number_left, const int* number_right, int* sum)
{
    int discharge = 0;  //  разряд
    for (int i = ARR_SIZE - 1; i >= 0; i--)
    {
        //  если сумма чисел больше размера системы счисления
        if (number_left[i] + number_right[i] + discharge >= NUMBER_SYSTEM)
        {
            //  то складываем числа плюс разряд и берем остаток от деления на число = системе счисления
            sum[i] = (number_left[i] + number_right[i] + discharge) % NUMBER_SYSTEM;
            //  запомнили перенос разряда
            discharge = 1;
        }
        else
        {
            //  в ином случае, когда при сложении число меньше размера системы счисления
            sum[i] = number_left[i] + number_right[i] + discharge;
            //  зануляем разряд
            discharge = 0;
        }
    }
}

//  разность чисел
void difference_num(const int* number_left, const int* number_right, int* sum)
{
    int discharge = 0;  //  занимаемый разряд
    for (int i = ARR_SIZE - 1; i >= 0; i--)
    {
        //  проверяем, больше ли левое число правого с учетом занимаемых разрядов
        if ((number_left[i] - discharge) - number_right[i] >= 0)
        {
            sum[i] = (number_left[i] - discharge) - number_right[i];
            discharge = 0;
        }
        //  в случае, когда при вычитании левое число меньше правого и нужно занимать разряд
        else
        {
            sum[i] = number_left[i] + NUMBER_SYSTEM - number_right[i] - discharge;
            discharge = 1;
        }
    }
}

//  инициализируем число(массив) по числу(в десятичной СС)
void init_arr_num(ull decimal_number, int* arr_number)
{
    int i = ARR_SIZE - 1;

    //  пока не прочли число
    while (decimal_number > 0 && i >= 0)
    {
        //  берем последнюю цифру числа по модулю СС
        arr_number[i] = decimal_number % NUMBER_SYSTEM;
        //  убираем последнюю прочитанную цифру
        decimal_number /= NUMBER_SYSTEM;
        i--;
    }

    for (int j = i; j >= 0; j--)
        arr_number[j] = 0;
    //  зануляем оставшиеся элементы
}

//  сохраняем число(из массива) в переменную типа unsigned long long
void save_num(const int* arr_number, ull* decimal_number)
{
    *decimal_number = 0;
    int j = ARR_SIZE - 1;
    for (int i = 0; i < ARR_SIZE; i++, j--)
        *decimal_number = *decimal_number + arr_number[i] * pow_ull(NUMBER_SYSTEM, j);
    //  переводим число в десятичную СС
}

//  переводим в 13-ричную СС (для записи в файл)
void to_thirteen_system(char* thirteen_number)
{
    for (int i = 1, j = 1; i < 26; i++, j += 2)
    {
        thirteen_number[j - 1] = alphabet[i / NUMBER_SYSTEM];   //  получаем первую цифру
        thirteen_number[j] = alphabet[i % NUMBER_SYSTEM];       //  получаем вторую цифру
    }
}

//  перевод в двоичную СС (для записи в файл)
ull to_binary_sys(int number)
{
    ull binary_number = 0;
    int i = 0;
    while (number > 0)
    {
        //  переводим число в двоичную СС
        binary_number += (number % 2) * pow_ull(10, i);
        //  побитовый сдвиг вправо (тоже самое деление на два, только менее затратное действие
        number >>= 1;
        i++;
    }
    return binary_number;
}

//  запись в файл таблицы СС
//  10-я 2-я 16-я 13-я
void create_table()
{
    int binary_arr[25];     //  массив для записи числа в 2-й СС
    char thirteen_sys[50];    //  массив для записи числа в 13-й СС
    to_thirteen_system(thirteen_sys);  //  перевод числа в 13-ю СС
    int j = 1;

    // объявляем указатель на файл
    FILE *filePointer;

    //  открываем таблицу, с режимом открытия файла
    filePointer = fopen("table.dat", "w");

    //  проверяем указатель на нулл
    //  если файл не смог открыться (с атрибутом w такого не будет
    //  если не существует, он его создаст
    if (filePointer == NULL)
    {
        printf( "table.dat файл открыть не получилось." );
        return;
    }
    printf("Файл успешно открыт.\n");
    //  записываем в файл таблицу
    fprintf(filePointer, "  DEC    BIN   HEX  13  \n");
    fprintf(filePointer, "------------------------\n");
    for (int i = 1; i < 26; i++)
    {
        binary_arr[i - 1] = to_binary_sys(i);
        fprintf(filePointer, "| %2d | %5d | %2x |", i, binary_arr[i - 1], i);
        //  красиво записываем файл в таблицу
        fprintf(filePointer, " %c%c |\n", thirteen_sys[j - 1], thirteen_sys[j]);
        j += 2;
    }
    fprintf(filePointer, "------------------------");
    fclose(filePointer);

    printf("Данные успешно записаны в файл table.dat\n");
    printf("Файл успешно закрыт.");
}
