#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <malloc.h>
#include "sapper.h"

const int max_size_rows = 25;
const int max_size_columns = 35;
// c �������� ������ 24(�������)

// ��������� ���..
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

//  ��������� ������ ����
typedef char menu_item[10];
const int amount_item = 3;
menu_item item_name[] = {"Game", "Readme", "Exit"};

//  ��������� ������ ���������
typedef char complexity[10];
const int amount_complexity = 4;
complexity complexity_item[] = {"Beginner", "Middle", "Expert", "Custom"};

//  ������� ��� ������ ����
const int indent_top = 2;
const int indent_left = 2;

//  ����� ����. � ���� � ����������
void print_readme(HANDLE hConsole)
{
    system("cls");
    for (int i = 0; i < indent_top; i++)
        printf("\n");

    printf("���������� � ���� �������������� �����������\n");
    printf("�����-���� ������������ ����� ���������� ����\n");
    printf("������� ������ - ����� �������� ����\n");
    printf("������� ESC - ����� �� ����\n\n");
    printf("����� ��������� � ���� �������������� �����������\n");
    printf("�����-���� ������������ ����� ���������� � ������� ������ �����\n");
    printf("��� ������������� ������, ����� ������ ��������� ������ ����� ������\n");
    printf("��� �� ������ �� ����������� (>> number ENTER)\n\n");
    printf("���������� � ����\n");
    printf("����� �������� ����������, ����� ������ ���\n");
    printf("����������� ����� ����� �������: �����1,�����2\n");
    printf("����� ����� � �������� ����, �������� \'exit\'\n\n\n");
    printf("������� ������� ESC, ����� ��������� � ����\n");
    while(GetAsyncKeyState(VK_ESCAPE) == 0) //  ���������� ��������� ������� ������� ESC
        Sleep(100); //  �������� ����� �� 0.1 �������
}

void print_menu(const int pointer, HANDLE hConsole)
{
    system("cls");  // ������� �����

    //  ������ ������
    for (int i = 0; i < indent_top; i++)
        printf("\n");

    for (int i = 0; i < amount_item; i++)
    {
        //  ������ �����
        for (int j = 0; j < indent_left; j++)
            printf(" ");

        //  ���� ������� ������ ���� � ����������� �� ����� � ���������
        //  � ������ ������ ���� �����
        SetConsoleTextAttribute(hConsole, 15);
        if (pointer == i)
        {
            //  ������ ��������� �� ��� ��������, �� ������� ��������� �������
            SetConsoleTextAttribute(hConsole, 10);
            printf("\\->  %s\n", item_name[i]);
        }
        else
        {
            printf("  %s\n", item_name[i]);
        }
    }
}

//  ������� ��� ������ ������ ���������
//  ���������� ����� �� 1 - amount_complexity
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

        //  ��������� ������� ������
        //  ������� �����, ������� ����(������������), ������� ������(�����) � ������(�����)
        if (GetAsyncKeyState(VK_UP) != 0)
        {
            is_pressed = 1;
            //  ������ ������� �����, ��������� �������� ����� �� �������
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

//  ������� ��������� ���������� ������ � �����
int stoi(char *str)
{
    int result = 0;

    for (int i = 0; i < strlen(str); i++)
    {
        //  ���� ������ ����� � ������ ���������, ������ ��� ���� �� ���� 0-9
        if (str[i] >= 48 && str[i] <= 57)
        {
            //  ���� �� ����� �-������� �����, �� ��������� ���������� ������ �� ������
            result = result * 10 + str[i] - 48;
        }
        else return -1; //  ���������� -1 ���� ��������� ���� �� ���� ������ ��� ����� ���������
    }

    return result;
}

int main()
{
    // ����� o��� ��������� ��� ��������� �������� ������
    HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    setlocale(0, "rus");    //  ������ ������� ����

    SetConsoleTitle("Game Sapper"); //  ������ �������� ������ ������� (������������ ������ ����)
    int pointer = 1, complexity = 0, is_pressed = 1;
    int rows_custom = rows_beginner, columns_custom = columns_beginner, mines_custom = mines_beginner;
    char temp[3];   //  ����������� ��� �������� ������ � ����� ��� ��������� �����

    while (TRUE) {
        if (is_pressed)
        {
            is_pressed = 0;
            print_menu(pointer, hConsole);  //  �������� ����
        }

        //  ��� �� ��������� ������� �������
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
        else if (GetAsyncKeyState(VK_RIGHT) != 0) //  ������ ������� ������
        {
            is_pressed = 1;
            if (pointer == 0)
            {
                Sleep(200);
                complexity = change_complexity(hConsole);   //  �������� ���������
                switch (complexity) //  � ����������� �� ��������� ���������, ������������ �����
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
                        //  ���� ������� �� �� �������������
                        printf("Enter amount rows, columns, mines\n");
                        printf("maximum values: %d, %d respectively\n", max_size_rows, max_size_columns);
                        printf("mines are calculate separately\n");
                        printf("Enter amount rows: ");  //  ������ ��������� ���������
                        scanf("%s", temp);  //  ��������� � ����������
                        rows_custom = stoi(temp);
                        printf("Enter amount columns: ");
                        scanf("%s", temp);
                        columns_custom = stoi(temp);
                        printf("Enter amount mines: ");
                        scanf("%s", temp);
                        mines_custom = stoi(temp);

                        //  ��������� ������������ ��������� ������
                        //  � ������, ���� ������� �������, ������������� ��������� �������� �� ����������� �������������
                        if (rows_custom > max_size_rows || rows_custom <= 0)
                            rows_custom = max_size_rows;
                        if (columns_custom > max_size_columns || columns_custom <= 0)
                            columns_custom = max_size_columns;
                        //  ���� �� ����������� � ����������� �� ������� ����� (~20% ��� �� ��� �����)
                        if (mines_custom >= rows_custom * columns_custom || mines_custom <= 0)
                            mines_custom = (int) (0.2 * rows_custom * columns_custom);
                        Game(hConsole, rows_custom, columns_custom, mines_custom);  //  ��������� ���� � ������ �������
                        break;
                    default : break;
                }
            }
            else if (pointer == 1)
            {
                is_pressed = 1;
                //  �������� �����
                print_readme(hConsole);
            }
            else break;
        }
        else if (GetAsyncKeyState(VK_ESCAPE) != 0)
        {
            is_pressed = 1;
            //  ������� �� ����
            break;
        }

        Sleep(120); //  �������� ����� �� 0.2 �������
                    //  ����� ��������� �� ��������� \ �������������� ��� ������ ������ ���� �������
    }
    return 0;
}
