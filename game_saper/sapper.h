#include <time.h>
#include <windows.h>
#include <conio.h>
#include <locale.h>
#include "matrix.h"

//  ��������� - �����
//  ������������ � ������ ������ ����������
typedef struct Point {
    int x;
    int y;
} Point;

// ��������� ������ �� ���� ������ ( ����� �� ������� ���������� 0 )
int check_mines_around(Matrix *matrix, int i, int j)
{
    // �������� �� ����� �� ������� �������
    if ((i < 0) || (i >= matrix->rows) || (j < 0) || (j >= matrix->columns)) return 0;

    int count_mines = 0;
    int rows = matrix->rows;
    int columns = matrix->columns;
    //  ������ ������� ����, ��������� �������� � ������� [i][j] �� ������� ���
    if (((i - 1) >= 0) && ((j - 1) >= 0))
        if (matrix->field[i - 1][j - 1] == -1)  //  ���� ����� ����
            count_mines++;  //  ���������� �� � ��������

    if (i - 1 >= 0)
        if (matrix->field[i - 1][j] == -1)
            count_mines++;

    if ((i - 1 >= 0) &&   (j + 1 < columns))
        if (matrix->field[i - 1][j + 1] == -1)
            count_mines++;

    if (j - 1 >= 0)
        if (matrix->field[i][j - 1] == -1)
            count_mines++;

    if (j + 1 < columns)
        if (matrix->field[i][j + 1] == -1)
            count_mines++;

    if ((i + 1 < rows) && (j - 1 >= 0))
        if (matrix->field[i + 1][j - 1] == -1)
            count_mines++;

    if (i + 1 < rows)
        if (matrix->field[i + 1][j] == -1)
            count_mines++;

    if ((i + 1 < rows) && (j + 1 < columns))
        if (matrix->field[i + 1][j + 1] == -1)
            count_mines++;

    return count_mines;
}

// ��������� ������ �� ������� (1), ����� �� ������� ������� ���������� 0
int empty_cell(Matrix *matrix, const int i, const int j)
{
    // �������� �� ����� �� ������� �������
    if ((i < 0) || (i >= matrix->rows) || (j < 0) || (j >= matrix->columns)) return 0;
    if (matrix->field[i][j] == 0) return 1; //  ���� ������ �����, �� ������ = 1, ����� ���� = 0
    return 0;
}

// ����������� �������, ������� ��������� ���� � ����� ���������
void clean_cells(Matrix *matrix, Matrix *opened, const int i, const int j)
{
    // �������� �� ����� �� ������� �������
    if ((i < 0) || (i >= matrix->rows) || (j < 0) || (j >= matrix->columns)) return;

    // ��������, �� ���� �� ������� ���� ������
    if (!opened->field[i][j])
    {
        // ������� ����
        opened->field[i][j] = 1;

        // ���� ���� ������ ( = 0), ������ ����������� ���� ��� �������
        if (matrix->field[i][j] == 0)
        {
            clean_cells(matrix, opened, i - 1,    j - 1   );
            clean_cells(matrix, opened, i - 1,    j       );
            clean_cells(matrix, opened, i - 1,    j + 1   );
            clean_cells(matrix, opened, i,        j - 1   );
            clean_cells(matrix, opened, i,        j + 1   );
            clean_cells(matrix, opened, i + 1,    j - 1   );
            clean_cells(matrix, opened, i + 1,    j       );
            clean_cells(matrix, opened, i + 1,    j + 1   );
        }
        // ���� �� ������ ( != 0) ��������� ������ ������ ( = 0) �������
        //  �.� ������� ����� � ������ ������� - ������ � ������, ������� ����������, ������� ��� ������ ���
        else
        {
            if (empty_cell(matrix, i - 1, j - 1))
                clean_cells(matrix, opened, i - 1, j - 1);

            if (empty_cell(matrix, i - 1, j))
                clean_cells(matrix, opened, i - 1, j);

            if (empty_cell(matrix, i - 1, j + 1))
                clean_cells(matrix, opened, i - 1, j + 1);

            if (empty_cell(matrix, i, j - 1))
                clean_cells(matrix, opened, i, j - 1);

            if (empty_cell(matrix, i , j + 1))
                clean_cells(matrix, opened, i, j + 1);

            if (empty_cell(matrix, i + 1, j - 1))
                clean_cells(matrix, opened, i + 1, j - 1);

            if (empty_cell(matrix, i + 1, j))
                clean_cells(matrix, opened, i + 1, j);

            if (empty_cell(matrix, i + 1, j + 1))
                clean_cells(matrix, opened, i + 1, j + 1);
        }
    }
}

//  ����� ���-�� ���, ������� � ���������(�������� = �������� ����� ���������)
//  �������� ���� � ���������������� ������������, � ����-�� ��� ������� ����������
void draw_matrix(HANDLE hConsole, Matrix *matrix, Matrix *opened, int amount_mines, int seconds)
{
    // ���-�� ���������� ��� � �����
    printf("\n");
    printf("amount mines: %d\n", amount_mines);
    //  ����� �������, CLOCKS_PER_SEC ��������� = 1 ��� � �������, ��� ������������ ��� ������� ��, ������� ����
    //  � ������ ������ ����� �� 60, �������� ������, �� ������ ����� ������� �� ������� �� 60 � �������� ��������� �������
    printf("current time: %d:%d", (int)((seconds / CLOCKS_PER_SEC) / 60), (seconds / CLOCKS_PER_SEC) % 60);

    printf("\n\n");
    SetConsoleTextAttribute(hConsole, 6);  // dark yellow text
    printf("   ");
    for (int j = 0; j < matrix->columns; j++)
    {
        //  ���� ����� ������ 10, �� ��� ��� ����� ������ ����� � ��������
        //  (5 �������� 1 ������, ����� 10 - ��� ��� � �.�.)
        if (j < 10)
            printf("%d  ", j);
        else
            printf("%d ", j);
    }
    printf("\n");
    SetConsoleTextAttribute(hConsole, 7);  // white text
    for (int i = 0; i < matrix->rows; i++)
    {
        SetConsoleTextAttribute(hConsole, 6);  // dark yellow text
        if (i < 10)
            printf("%d  ", i);
        else
            printf("%d ", i);
        SetConsoleTextAttribute(hConsole, 7);  // white text
        for (int j = 0; j < matrix->columns; j++)
        {
            //  ���������, ������� �� ������ ������ i j
            if (opened->field[i][j])
            {
                SetConsoleTextAttribute(hConsole, 8);  // gray text
                //  ���� ����, ������ ���������
                if (matrix->field[i][j] == -1)
                {
                    SetConsoleTextAttribute(hConsole, 12);  // red text
                    printf("*  ");
                    SetConsoleTextAttribute(hConsole, 15);   // white text
                }
                else if (matrix->field[i][j] == 0)
                {
                    //  ������ �����
                    printf(".  ");
                }
                else
                {
                    switch (matrix->field[i][j])
                    {
                    case 1:
                        SetConsoleTextAttribute(hConsole, 1);
                        break;
                    case 2:
                        SetConsoleTextAttribute(hConsole, 2);
                        break;
                    case 3:
                        SetConsoleTextAttribute(hConsole, 4);
                        break;
                    case 4:
                        SetConsoleTextAttribute(hConsole, 5);
                        break;
                    case 5:
                        SetConsoleTextAttribute(hConsole, 3);
                        break;
                    case 6:
                        SetConsoleTextAttribute(hConsole, 10);
                        break;
                    case 7:
                        SetConsoleTextAttribute(hConsole, 11);
                        break;
                    case 8:
                        SetConsoleTextAttribute(hConsole, 12);
                        break;
                    default:
                        break;
                    }
                    //  �����, ������������ ���-�� ��� ������
                    printf("%d  ", matrix->field[i][j]);
                }
                SetConsoleTextAttribute(hConsole, 15);  // white text
            }
            else
            {
                SetConsoleTextAttribute(hConsole, 7);   // white text
                //  �� ��������� ������
                printf("#  ");
            }
        }
        printf("\n");
    }
}

// ������� ��������� ����, ������ ���� �� ���� �������� "You Lose!" ��� "You Win!"
void game_result(HANDLE hConsole, int loser)
{
    printf("\n\t");
    //  ���������, �������� �� ��� �� ���������
    if(loser)
    {
        SetConsoleTextAttribute(hConsole, 12);  // red text
        printf("You Lose\n");
        SetConsoleTextAttribute(hConsole, 7);  // white text
    }
    else
    {
        SetConsoleTextAttribute(hConsole, 10);  // red text
        printf("You Win !!!\n");
        SetConsoleTextAttribute(hConsole, 7);  // white text
    }
}

// ��������� ��� ���� � ������
void open_mines(Matrix *matrix, Matrix *opened)
{
    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->columns; j++)
        {
            //  ���� ����� ����, ��������� �
            if (matrix->field[i][j] == -1)
            {
                opened->field[i][j] = 1;
            }
        }
    }
}

// ���������, ��� �� ���� �������, ����� ���
int checkwin(Matrix *matrix, Matrix *opened)
{
    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->columns; j++)
        {
            //  �.�., ���� ���� ���� ���� ������ ��� ����
            //  � ��� ���� ��� �� ������� -> ���������� ���� (��� �� ��������)
            if ((matrix->field[i][j] != -1) && (!opened->field[i][j]))
                return 0;
        }
    }
    return 1;
}

//  ��������� ���������� �����
Point get_coordinate(const int rows, const int columns)
{
    int x, y, is_correct = 1;
    char input_string[6];
    Point point;
    do
    {
        if (is_correct)
            printf("Enter coordinate for hit(row,column (example \'4,11\')): ");
        else
            printf("You entered the wrong coordinates. Input example: \'2,1\'; \'10,13\' � �.�.)): ");

        is_correct = 1;
        x = 0;
        y = 0;

        //  ��������� ��� ����� � ����������
        scanf("%s", input_string);
        //  ���� ����� \'exit\' �� ������� �� ���� � ����
        if (strcmp("exit", input_string) == 0)
        {
            point.x = -1;
            point.y = -1;
            return point;
        }

        //  ��� �� ��������� ������������ ��������� ������
        //  � ������ ������ ��������������� ���� ���� ����� ����� �������
        //  ��� ��������: xx,yy; x,yy; xx,y; x,y
        if (input_string[1] == ',')
        {
            //  �������� �� ���� ������� � ������ �������� (�� 48 �� 57 ����� �� 0 -9)
            if ((input_string[0] >= 48) && (input_string[0] <= 57))
            {
                x = input_string[0] - 48;
            }
            else is_correct = 0;
            //  ���� ���� ��� ��� ����� ������ ��������
            //  � ����� �����������, �� �������� ��������� ������

            if ((input_string[2] >= 48) && (input_string[2] <= 57))
            {
                y = input_string[2] - 48;
                if ((input_string[3] >= 48) && (input_string[3] <= 57))
                {
                    y = y * 10 + input_string[3] - 48;
                }
            }
            else is_correct = 0;
        }
        else
        {
            if ((input_string[0] >= 48) && (input_string[0] <= 57))
            {
                x = input_string[0] - 48;
                if ((input_string[1] >= 48) && (input_string[1] <= 57))
                {
                    x = x * 10 + input_string[1] - 48;
                }
                else is_correct = 0;
            }
            else is_correct = 0;

            if ((input_string[3] >= 48) && (input_string[3] <= 57))
            {
                y = input_string[3] - 48;
                if ((input_string[4] >= 48) && (input_string[4] <= 57))
                {
                    y = y * 10 + input_string[4] - 48;
                }
            }
            else is_correct = 0;
        }
        //  ���������, ����� �������� ����� ���� � ��������� ������� ����� ����
        if ((x < 0 || x > rows) || (y < 0 || y > columns))
            is_correct = 0;
    } while (!is_correct);  //  ��������� ���� �� ������ ���������
    point.x = x;
    point.y = y;
    return point;
}

//  game loop
void Game(HANDLE hConsole, const int rows, const int columns, const int amount_mines)
{
    clock_t start;              //  ���������� ��� ������ ������� �������(������ �������������������)
    clock_t difference_time;    //  ��� ������� �������� �������
    int seconds_passed = 0;     //  ����� ��������� ������� ������� ������ � ������� ������� �����

    system("cls");
    setlocale(0, "rus");

    //  �������������� ������ ����������
    int temp1, temp2, is_gameover = 0;
    Point point;
    Matrix *matrix;
    Matrix *opened;
    //  �������� ������ ��� �������
    matrix = init_matrix_zero(rows, columns);
    opened = init_matrix_zero(rows, columns);

    srand((int)time(NULL));
    //  ����������� ��� ������ �� �������� �������
    //  ����� ������������� ��������������� �����

    //  ������ ������� ����
    draw_matrix(hConsole, matrix, opened, amount_mines, 0);
    //  ��������� ������ ����������
    point = get_coordinate(rows, columns);
    //  ���� ����� � ���� � ������ ����� ������� \'exit\'
    if (point.x == -1 && point.y == -1)
        is_gameover = 3;    //  ��� ���������� ���� (�����)
    start = clock();        //  �������� ������ �������, ����� ������� �����

    // ��������� ������ ���� ������
    for (int i = 0; i < amount_mines; i++)
    {
        do
        {
            //  ���������� ���� � ����������� ����1,2
            temp1 = rand() % rows;
            temp2 = rand() % columns;
        } while (matrix->field[temp1][temp2] != 0 || (point.x == temp1 && point.y == temp2));
        //  ����������, ���� �� �������� ��� ��������� ���� � ���
        //  ����� ������ ���� �� �������� � ����� (���������� ������� ��� �������)
        matrix->field[temp1][temp2]= -1;    //  ������ � ��� ���������� ����
    }

    // ��������� ������ ���� �������
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (matrix->field[i][j] != -1)
            {
                //  � ���� � ����������� [i][j] ������ ����� ��� ������
                matrix->field[i][j] = check_mines_around(matrix, i, j);
            }
        }
    }

    //  ����� ������� ����� ������� �������� ������, ���� ��� ��������
    clean_cells(matrix, opened, point.x, point.y);

    //  ���� ����� ������� ����� �������� (���� ������� � �������� ���� ���� �� ������� ����)
    if (checkwin(matrix, opened))
        is_gameover = 2;    //  ��� ���������� ���� (������)

    // ������� ������� ����
    while(!is_gameover)
    {
        // ������ ����� �� ������� �������
        system("cls");

        difference_time = clock() - start;      //  ����������� ������� ������� ������ � ������� ������� �����
        seconds_passed = (difference_time * 1000) / CLOCKS_PER_SEC; //  ����������� ����� � ��������

        // ������ ����
        draw_matrix(hConsole, matrix, opened, amount_mines, seconds_passed);
        printf("\n");
        // ����������� ���������� �����
        point = get_coordinate(rows, columns);
        //  �������� �� �����
        if (point.x == -1 && point.y == -1)
        {
            is_gameover = 3;
            break;
        }
        temp1 = point.x;
        temp2 = point.y;

        // ����� ��������� ��� ������ ��������� ����� �� ������ ������
        // � ���� ���� ���������� ����� ����� ����
        clean_cells(matrix, opened, temp1, temp2);

        //  ���� ����������� �� ����
        if (matrix->field[temp1][temp2] == -1)
            is_gameover = 1;    //  ��� ���������� ���� (��������)
        //  ���� ��� ������ ������(��� ���) �������
        if (checkwin(matrix, opened))
            is_gameover = 2;    //  ������
    }

    system("cls");

    difference_time = clock() - start;  //  ����������� ��������� ��� ������� �����
    seconds_passed = (difference_time * 1000) / CLOCKS_PER_SEC; //  ������� ��������� ����� ���� �� �� ����������
    if (is_gameover == 1)
        game_result(hConsole, 1);    // ��������
    else if (is_gameover == 2)
    {
        game_result(hConsole, 0);    // ������
        printf("You finished in %d:%d time\n",
               (seconds_passed / CLOCKS_PER_SEC) / 60, (seconds_passed / CLOCKS_PER_SEC) % 60);
                //  ������� ����������� �����
    }
    else
    {
        printf("Exit to menu");
        return;
    }

    open_mines(matrix, opened);     //  ����� ���������� ���� (������ \ ��������) ��������� ���� � ������
    draw_matrix(hConsole, matrix, opened, amount_mines, seconds_passed);    //  ������ ����
    //  ������� ������
    delete_matrix(&matrix);
    delete_matrix(&opened);
    //  ����, ����� ������������ ������ ����� ������, ����� ����� � ����
    printf("press any key to main menu\n");
    getch();
}
