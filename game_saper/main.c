#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <malloc.h>
#include "sapper.h"

const int max_size_rows = 25;
const int max_size_columns = 35;
// c размером шрифта 24(консоли)

// Параметры для..
//  BEGINNER
const int rows_beginner = 8;
const int columns_beginner = 8;
const int mines_beginner = 10;

//  MIDDLE
const int rows_middle = 12;
const int columns_middle = 16;
const int mines_middle = 32;

//  EXPERT
const int rows_expert = 20;
const int columns_expert = 25;
const int mines_expert = 99;

//  Контейнер итемов меню
typedef char menu_item[10];
const int amount_item = 3;
menu_item item_name[] = {"Game", "Readme", "Exit"};

//  Контейнер итемов сложности
typedef char complexity[10];
const int amount_complexity = 4;
complexity complexity_item[] = {"Beginner", "Middle", "Expert", "Custom"};

//  Отступы для итемов меню
const int indent_top = 2;
const int indent_left = 2;

//  Вывод инфо. о игре и управлении
void print_readme(HANDLE hConsole)
{
    system("cls");
    for (int i = 0; i < indent_top; i++)
        printf("\n");

    printf("Управление в меню осуществляется стрелочками\n");
    printf("вверх-вниз переключение между элементами меню\n");
    printf("стрелка вправо - выбор элемента меню\n");
    printf("клавиша ESC - выход из меню\n\n");
    printf("Выбор сложности в меню осуществляется стрелочками\n");
    printf("вверх-вниз переключение между элементами и стрелка вправо выбор\n");
    printf("при настраиваемом режиме, можно ввести начальные данные через пробел\n");
    printf("или же каждый по отдельности (>> number ENTER)\n\n");
    printf("Управление в игре\n");
    printf("Чтобы отметить координату, нужно ввести два\n");
    printf("двухзначных числа через запятую: число1,число2\n");
    printf("чтобы выйти с игрового поля, напишите \'exit\'\n\n\n");
    printf("нажмите клавишу ESC, чтобы вернуться в меню\n");
    while(GetAsyncKeyState(VK_ESCAPE) == 0) //  асинхронно считываем нажатие клавиши ESC
        Sleep(100); //  усыпляем поток на 0.1 секунду
}

void print_menu(const int pointer, HANDLE hConsole)
{
    system("cls");  // очищаем экран

    //  отступ сверху
    for (int i = 0; i < indent_top; i++)
        printf("\n");

    for (int i = 0; i < amount_item; i++)
    {
        //  отступ слева
        for (int j = 0; j < indent_left; j++)
            printf(" ");

        //  текс атрибут меняет цвет в зависимости от числа в параметре
        //  в данном случае ярко белый
        SetConsoleTextAttribute(hConsole, 15);
        if (pointer == i)
        {
            //  рисуем стрелочку на том элементе, на который указывает поинтер
            SetConsoleTextAttribute(hConsole, 10);
            printf("\\->  %s\n", item_name[i]);
        }
        else
        {
            printf("  %s\n", item_name[i]);
        }
    }
}

//  функция для выбора уровня сложности
//  возвращает число от 1 - amount_complexity
int change_complexity(HANDLE hConsole)
{
    int pointer = 0, is_pressed = 1;
    while (TRUE) {
        if (is_pressed)
        {
            is_pressed = 0;
            system("cls");

            for (int i = 0; i < indent_top; i++)
                printf("\n");

            for (int i = 0; i < amount_complexity; i++)
            {
                for (int j = 0; j < indent_left; j++)
                    printf(" ");

                SetConsoleTextAttribute(hConsole, 15);
                if (pointer == i)
                {
                    SetConsoleTextAttribute(hConsole, 10);
                    printf("\\->  %d) %s\n", (i + 1), complexity_item[i]);
                }
                else
                {
                    printf("  %d) %s\n", (i + 1), complexity_item[i]);
                }
            }
            SetConsoleTextAttribute(hConsole, 15);
        }

        //  Проверяем нажатие клавиш
        //  стрелка вверх, стрелка вниз(переключение), стрелка вправо(выбор) и эскейп(выход)
        if (GetAsyncKeyState(VK_UP) != 0)
        {
            is_pressed = 1;
            //  нажали стрелку вверх, указатель сместили вверх на единицу
            pointer = (pointer == 0 ? amount_complexity - 1 : pointer - 1);
        }
        else if (GetAsyncKeyState(VK_DOWN) != 0)
        {
            is_pressed = 1;
            pointer = (pointer == amount_complexity - 1 ? 0 : pointer + 1);
        }
        else if (GetAsyncKeyState(VK_RIGHT) != 0)
        {
            is_pressed = 1;
            return (pointer + 1);
        }
        else if (GetAsyncKeyState(VK_ESCAPE) != 0)
        {
            is_pressed = 1;
            return -1;
        }

        Sleep(120);
    }
}

//  функция переводит полученную строку в число
int stoi(char *str)
{
    int result = 0;

    for (int i = 0; i < strlen(str); i++)
    {
        //  если символ лежит в данном диапозоне, значит это одна из цифр 0-9
        if (str[i] >= 48 && str[i] <= 57)
        {
            //  если мы ввели н-значное число, то домножаем предыдущий разряд на десять
            result = result * 10 + str[i] - 48;
        }
        else return -1; //  возвращаем -1 если встретили хотя бы один символ вне этого диапозона
    }

    return result;
}

int main()
{
    // хэндл oкна необходим для рисования цветного текста
    HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    setlocale(0, "rus");    //  задаем русский язык

    SetConsoleTitle("Game Sapper"); //  задаем название вверху консоли (отображаться вместо пути)
    int pointer = 1, complexity = 0, is_pressed = 1;
    int rows_custom = rows_beginner, columns_custom = columns_beginner, mines_custom = mines_beginner;
    char temp[3];   //  понадобится для перевода строки в число при кастомной карте

    while (TRUE) {
        if (is_pressed)
        {
            is_pressed = 0;
            print_menu(pointer, hConsole);  //  печатаем меню
        }

        //  так же проверяем нажатые клавиши
        if (GetAsyncKeyState(VK_UP) != 0)
        {
            is_pressed = 1;
            pointer = (pointer == 0 ? amount_item - 1 : pointer - 1);
        }
        else if (GetAsyncKeyState(VK_DOWN) != 0)
        {
            is_pressed = 1;
            pointer = (pointer == amount_item - 1 ? 0 : pointer + 1);
        }
        else if (GetAsyncKeyState(VK_RIGHT) != 0) //  нажали стрелку вправо
        {
            is_pressed = 1;
            if (pointer == 0)
            {
                Sleep(200);
                complexity = change_complexity(hConsole);   //  выбираем сложность
                switch (complexity) //  в зависимости от выбранной сложности, генерируется карта
                {
                    case 1:
                        Game(hConsole, rows_beginner, columns_beginner, mines_beginner);
                        break;
                    case 2:
                        Game(hConsole, rows_middle, columns_middle, mines_middle);
                        break;
                    case 3:
                        Game(hConsole, rows_expert, columns_expert, mines_expert);
                        break;
                    case 4:
                        //  Если выбрали ур сл настраиваемый
                        printf("Enter amount rows, columns, mines\n");
                        printf("maximum values: %d, %d respectively\n", max_size_rows, max_size_columns);
                        printf("mines are calculate separately\n");
                        printf("Enter amount rows: ");  //  вводим начальные параметры
                        scanf("%s", temp);  //  считываем с клавиатуры
                        rows_custom = stoi(temp);
                        printf("Enter amount columns: ");
                        scanf("%s", temp);
                        columns_custom = stoi(temp);
                        printf("Enter amount mines: ");
                        scanf("%s", temp);
                        mines_custom = stoi(temp);

                        //  проверяем корректность введенных данных
                        //  в случае, если введены неверно, устанавливаем начальные значения на максимально установленные
                        if (rows_custom > max_size_rows || rows_custom <= 0)
                            rows_custom = max_size_rows;
                        if (columns_custom > max_size_columns || columns_custom <= 0)
                            columns_custom = max_size_columns;
                        //  мины же вычисляются в зависимости от размера карты (~20% мин на всю карту)
                        if (mines_custom >= rows_custom * columns_custom || mines_custom <= 0)
                            mines_custom = (int) (0.2 * rows_custom * columns_custom);
                        Game(hConsole, rows_custom, columns_custom, mines_custom);  //  запускаем игру с нашими данными
                        break;
                    default : break;
                }
            }
            else if (pointer == 1)
            {
                is_pressed = 1;
                //  печатаем ридми
                print_readme(hConsole);
            }
            else break;
        }
        else if (GetAsyncKeyState(VK_ESCAPE) != 0)
        {
            is_pressed = 1;
            //  выходим из меню
            break;
        }

        Sleep(120); //  усыпляем поток на 0.2 секунды
                    //  чтобы программа не считывала \ перерисовывала нон стопом каждую долю секунды
    }
    return 0;
}
