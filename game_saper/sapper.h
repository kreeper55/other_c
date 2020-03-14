#include <time.h>
#include <windows.h>
#include <conio.h>
#include <locale.h>
#include "matrix.h"

//  структура - точка
//  используется в методе взятия координаты
typedef struct Point {
    int x;
    int y;
} Point;

// проверяет ячейку на мины вокруг ( выход за пределы возвращает 0 )
int check_mines_around(Matrix *matrix, int i, int j)
{
    // проверим на выход за пределы массива
    if ((i < 0) || (i >= matrix->rows) || (j < 0) || (j >= matrix->columns)) return 0;

    int count_mines = 0;
    int rows = matrix->rows;
    int columns = matrix->columns;
    //  каждая условие ниже, проверяет соседние с клеткой [i][j] на наличие мин
    if (((i - 1) >= 0) && ((j - 1) >= 0))
        if (matrix->field[i - 1][j - 1] == -1)  //  если нашли мину
            count_mines++;  //  прибавляем ее к счетчику

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

// проверяет ячейку на пустоту (1), выход за пределы массива возвращает 0
int empty_cell(Matrix *matrix, const int i, const int j)
{
    // проверим на выход за пределы массива
    if ((i < 0) || (i >= matrix->rows) || (j < 0) || (j >= matrix->columns)) return 0;
    if (matrix->field[i][j] == 0) return 1; //  если ячейка пуста, то истина = 1, иначе ложь = 0
    return 0;
}

// рекурсивная функция, которая открывает поля в точке попадания
void clean_cells(Matrix *matrix, Matrix *opened, const int i, const int j)
{
    // проверим на выход за пределы массива
    if ((i < 0) || (i >= matrix->rows) || (j < 0) || (j >= matrix->columns)) return;

    // проверим, не было ли открыто поле раньше
    if (!opened->field[i][j])
    {
        // откроем поле
        opened->field[i][j] = 1;

        // если поле пустое ( = 0), просто пооткрываем всех его соседей
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
        // если не пустое ( != 0) открываем только пустых ( = 0) соседей
        //  т.е откроет рядом с пустой ячейкой - ячейку с цифрой, которая обозночает, сколько мин вокруг нее
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

//  вывод кол-ва мин, времени с задержкой(задержка = скорости ввода координат)
//  игрового поля с соответствующими координатами, и инфо-ии как вводить координаты
void draw_matrix(HANDLE hConsole, Matrix *matrix, Matrix *opened, int amount_mines, int seconds)
{
    // кол-во оставшихся мин и время
    printf("\n");
    printf("amount mines: %d\n", amount_mines);
    //  вывод времени, CLOCKS_PER_SEC константа = 1 тик в секунду, она универсальна для каждого пк, поэтому надо
    //  в первом случае делим на 60, получаем минуты, во втором берем остаток от деления на 60 и получаем прошедшие секунды
    printf("current time: %d:%d", (int)((seconds / CLOCKS_PER_SEC) / 60), (seconds / CLOCKS_PER_SEC) % 60);

    printf("\n\n");
    SetConsoleTextAttribute(hConsole, 6);  // dark yellow text
    printf("   ");
    for (int j = 0; j < matrix->columns; j++)
    {
        //  если цифра меньше 10, то для нее нужно меньше места в символах
        //  (5 занимает 1 символ, число 10 - уже два и т.д.)
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
            //  проверяем, открыта ли данная ячейка i j
            if (opened->field[i][j])
            {
                SetConsoleTextAttribute(hConsole, 8);  // gray text
                //  если мина, рисуем звездочку
                if (matrix->field[i][j] == -1)
                {
                    SetConsoleTextAttribute(hConsole, 12);  // red text
                    printf("*  ");
                    SetConsoleTextAttribute(hConsole, 15);   // white text
                }
                else if (matrix->field[i][j] == 0)
                {
                    //  пустое место
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
                    //  число, обозночающее кол-во мин вокруг
                    printf("%d  ", matrix->field[i][j]);
                }
                SetConsoleTextAttribute(hConsole, 15);  // white text
            }
            else
            {
                SetConsoleTextAttribute(hConsole, 7);   // white text
                //  не раскрытые ячейки
                printf("#  ");
            }
        }
        printf("\n");
    }
}

// функция завершает игру, выведя одну из двух надписей "You Lose!" или "You Win!"
void game_result(HANDLE hConsole, int loser)
{
    printf("\n\t");
    //  Проверяем, выиграли мы или же проиграли
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

// открывает все поле с минами
void open_mines(Matrix *matrix, Matrix *opened)
{
    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->columns; j++)
        {
            //  если нашли мину, открываем её
            if (matrix->field[i][j] == -1)
            {
                opened->field[i][j] = 1;
            }
        }
    }
}

// проверяет, все ли поле открыто, кроме мин
int checkwin(Matrix *matrix, Matrix *opened)
{
    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->columns; j++)
        {
            //  т.е., если есть хоть одна клетка без мины
            //  и при этом она не открыта -> возвращаем ноль (еще не выиграли)
            if ((matrix->field[i][j] != -1) && (!opened->field[i][j]))
                return 0;
        }
    }
    return 1;
}

//  считываем координаты удара
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
            printf("You entered the wrong coordinates. Input example: \'2,1\'; \'10,13\' и т.д.)): ");

        is_correct = 1;
        x = 0;
        y = 0;

        //  считываем что ввели с клавиатуры
        scanf("%s", input_string);
        //  если ввели \'exit\' то выходим из игры в меню
        if (strcmp("exit", input_string) == 0)
        {
            point.x = -1;
            point.y = -1;
            return point;
        }

        //  тут мы проверяем правильность введенных данных
        //  в данном случае подразумевается ввод двух чисел через запятую
        //  все варианты: xx,yy; x,yy; xx,y; x,y
        if (input_string[1] == ',')
        {
            //  проверки на вход символа в нужный диапозон (от 48 до 57 числа от 0 -9)
            if ((input_string[0] >= 48) && (input_string[0] <= 57))
            {
                x = input_string[0] - 48;
            }
            else is_correct = 0;
            //  если хоть раз при вводе данных ошиблись
            //  и ввели некорректно, то начинаем считывать заного

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
        //  проверяем, чтобы заданный число было в диапозоне размера нашей игры
        if ((x < 0 || x > rows) || (y < 0 || y > columns))
            is_correct = 0;
    } while (!is_correct);  //  повторяем пока не введем корректно
    point.x = x;
    point.y = y;
    return point;
}

//  game loop
void Game(HANDLE hConsole, const int rows, const int columns, const int amount_mines)
{
    clock_t start;              //  переменная для начала отсчета времени(только проинициализировали)
    clock_t difference_time;    //  для расчета текущего времени
    int seconds_passed = 0;     //  будет указывать сколько времени прошло с момента первого удара

    system("cls");
    setlocale(0, "rus");

    //  инициализируем нужные переменные
    int temp1, temp2, is_gameover = 0;
    Point point;
    Matrix *matrix;
    Matrix *opened;
    //  выделяем память под матрицы
    matrix = init_matrix_zero(rows, columns);
    opened = init_matrix_zero(rows, columns);

    srand((int)time(NULL));
    //  привязываем наш рандом ко текущему времени
    //  чтобы сгенерировать псевдослучайные числа

    //  рисуем игровое поле
    draw_matrix(hConsole, matrix, opened, amount_mines, 0);
    //  считываем первые координаты
    point = get_coordinate(rows, columns);
    //  если зашли в игру и решили выйти написав \'exit\'
    if (point.x == -1 && point.y == -1)
        is_gameover = 3;    //  код завершения игры (выход)
    start = clock();        //  начинаем отсчет времени, после первого удара

    // заполняем массив поля минами
    for (int i = 0; i < amount_mines; i++)
    {
        do
        {
            //  генерируем мины в координатах темп1,2
            temp1 = rand() % rows;
            temp2 = rand() % columns;
        } while (matrix->field[temp1][temp2] != 0 || (point.x == temp1 && point.y == temp2));
        //  генерируем, пока не выставим все имеющиеся мины и так
        //  чтобы первый удар не совпадал с миной (безопасный выстрел так сказать)
        matrix->field[temp1][temp2]= -1;    //  ставим в эту координату мину
    }

    // заполняем массив поля цифрами
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (matrix->field[i][j] != -1)
            {
                //  в поле с координатой [i][j] ставим число мин вокруг
                matrix->field[i][j] = check_mines_around(matrix, i, j);
            }
        }
    }

    //  после первого удара очищаем соседние клетки, если это возможно
    clean_cells(matrix, opened, point.x, point.y);

    //  если после первого удара выиграли (если выбрали в кастомке одну мину на большом поле)
    if (checkwin(matrix, opened))
        is_gameover = 2;    //  код завершения игры (победа)

    // главный игровой цикл
    while(!is_gameover)
    {
        // чистим экран от старого рисунка
        system("cls");

        difference_time = clock() - start;      //  высчитываем сколько времени прошло с момента первого удара
        seconds_passed = (difference_time * 1000) / CLOCKS_PER_SEC; //  высчитываем время в секундах

        // рисуем поле
        draw_matrix(hConsole, matrix, opened, amount_mines, seconds_passed);
        printf("\n");
        // запрашиваем координаты удара
        point = get_coordinate(rows, columns);
        //  проверка на выход
        if (point.x == -1 && point.y == -1)
        {
            is_gameover = 3;
            break;
        }
        temp1 = point.x;
        temp2 = point.y;

        // далее проверяем все восемь окрестных полей на пустые клетки
        // и если надо показываем некий кусок поля
        clean_cells(matrix, opened, temp1, temp2);

        //  если подарвались на мине
        if (matrix->field[temp1][temp2] == -1)
            is_gameover = 1;    //  код завершения игры (проигрыш)
        //  если все пустые клетки(без мин) открыты
        if (checkwin(matrix, opened))
            is_gameover = 2;    //  победа
    }

    system("cls");

    difference_time = clock() - start;  //  высчитываем последний раз текущее время
    seconds_passed = (difference_time * 1000) / CLOCKS_PER_SEC; //  считаем прошедшее время игры до ее завершения
    if (is_gameover == 1)
        game_result(hConsole, 1);    // Проигрыш
    else if (is_gameover == 2)
    {
        game_result(hConsole, 0);    // Победа
        printf("You finished in %d:%d time\n",
               (seconds_passed / CLOCKS_PER_SEC) / 60, (seconds_passed / CLOCKS_PER_SEC) % 60);
                //  выводим потраченное время
    }
    else
    {
        printf("Exit to menu");
        return;
    }

    open_mines(matrix, opened);     //  после завершения игры (победа \ проигрыш) открываем поле с минами
    draw_matrix(hConsole, matrix, opened, amount_mines, seconds_passed);    //  рисуем поле
    //  очищаем память
    delete_matrix(&matrix);
    delete_matrix(&opened);
    //  ждем, когда пользователь нажмет любую кнопку, чтобы выйти в меню
    printf("press any key to main menu\n");
    getch();
}
