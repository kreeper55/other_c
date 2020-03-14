#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

int guessed[4]; //  загаданное число
int entered[4]; //  предпологаемое число

const int len_name = 20;    //  максимальная длина имени (для рекордов в одиночке)

//  определеяем размер таблицы (кол-во символов для вывода)
typedef unsigned long ul;
ul size_table = 1024ul;
char* table = NULL; //  определяем саму таблицу

//  определяем структуру Игрок
typedef struct Player Player;
struct Player
{
    int bulls;
    int cows;
    int turns;
};

//  инициализируем нового игрока
Player new_player()
{
    Player player;
    player.bulls = 0;
    player.cows = 0;
    player.turns = 0;
    return player;
}

//  проверка, содержится ли уже число в загаданном
//  для генератора, чтобы не было повторений чисел
int contains(const int value)
{
    for(int i = 0; i < 4; i++)
    {
        if(guessed[i] == value) //  значит в загаданном числе уже есть это значение
        {
            return 1;
        }
    }
    return 0;
}

//  возвращает длину строки
ul str_length(const char* str)
{
    ul count = 0;
    while (str[count] != '\0')  //  этот символ означает конец строки
    {
        count++;
    }
    return count;
}

//  генерируем псевдослучайное число
void random_number()
{
    srand(time(NULL));  //  чтобы рандомить числа
    int r = 0;
    for(int i = 0; i < 4; i++)
    {
        r = 0;
        do
        {
            r = rand() % 10;    //  числа  от 0 - 9
        }
        while (contains(r));
        guessed[i] = r; //  записываем число в загаданное
    }
}

//  ввод чисел
int input_number(const int is_hide)
{
    int count = 0;
    char temp;
    //  для корректного ввода и чтобы мусора не было
    for (int i = 0; i < 4; i++)
    {
        entered[i] = -1;
        if (is_hide)    //  это для хотсита, когда загадывает слово игрок
        {
            guessed[i] = -1;
        }
    }

    printf("\n\nвведите число (1 2 3 4) >> ");
    while (count < 4)
    {
        temp = getch(); //  данная фукция считывает без вывода на экран
        if (temp == 'q')    //  если нажмем q - выйдем из игры
        {
            return -1;
        }
        else if (temp == 8 && count > 0)    //  это символ backspace, если ввели не то число
        {
            if (is_hide)
            {
                guessed[count] = -1;
                count--;
                printf("\b\b \b");  //  стираем предыдущее число
            }
            else
            {
                entered[count] = -1;
                count--;
                printf("\b\b \b");
            }
        }
        if (temp >= 48 && temp <= 57)   //  если в этом диапозоне, то ввели число от 0 - 9
        {
            for (int i = count; i >= 0; i--)    //  данный цикл нужен для того, чтобы мы не могли записать одинаковые числа
            {
                if (is_hide)
                {
                    //  если встретили хоть одно число, которое уже было введено, то ставим темпу знак "-"
                    if (guessed[i] == (temp - 48))
                    {
                        temp = '-';
                        break;
                    }
                }
                else
                {
                    //  аналогично выше
                    if (entered[i] == (temp - 48))
                    {
                        temp = '-';
                        break;
                    }
                }
            }

            if (temp != '-')    //  записываем число в массив если введенный символ не повторялся
            {
                if (is_hide)
                {
                    guessed[count] = temp - 48;
                    printf("# ");   //  выводим вместо числа, решетку, чтобы наше загаданное число не увидели
                }
                else
                {
                    entered[count] = temp - 48;
                    printf("%d ", entered[count]);  //  выводим число
                }
                count++;
            }
        }
    }

    printf("\n");
    return 1;
}

//  печатаем таблицу
void print_table(const Player player)
{
    system("cls");

    char temp[4];

    //  это можешь убрать, первое это для рамки, второе для проверки игры (выводит загаданное пк число)
    //  printf("┌ │ ─ ├ ┼ ┤ ┐ └ ┘ ┬ ┴");
    //  printf("загаданное число = (%d%d%d%d)\n", guessed[0], guessed[1], guessed[2], guessed[3]);

    //  проверка выделенной памяти
    if ((str_length(table) + 500) > size_table)
    {
        //  если памяти под строку table не хватает памяти, выделяем новую в 2 раза больше
        size_table *= 2;
        table = (char*)realloc(table, size_table * sizeof(char));
    }

    //  для вывода начала таблицы, далее идет отрисовка рамки в середине таблицы
    if (player.turns == 1)
    {
        strcat(table, "\n");
        strcat(table, "┌─────┬───────┬──────┬───────┐\n");
        strcat(table, "│ ход │ число │ быки │коровы │\n");
        strcat(table, "├─────┼───────┼──────┼───────┤\n");
    }
    else
    {
        strcat(table, "├─────┼───────┼──────┼───────┤\n");
    }

    //  для корректного вывода шагов (чтобы не съезжала таблица, съедет только если ходов будет больше 999)
    if (player.turns < 10)
    {
        strcat(table, "│   ");
    }
    else
    {
        if (player.turns < 100)
        {
            strcat(table, "│  ");
        }
        else
        {
            strcat(table, "│ ");
        }
    }
    //  переводим int в char и прибавляем к строке table м далее аналогично с др переменными
    itoa(player.turns, temp, 10);
    strcat(table, temp);

    strcat(table, " │  ");
    for (int i = 0; i < 4; i++)
    {
        //  записываем число в строку
        itoa(entered[i], temp, 10);
        strcat(table, temp);
    }

    strcat(table, " │   ");
    itoa(player.bulls, temp, 10);
    strcat(table, temp);

    strcat(table, "  │   ");
    itoa(player.cows, temp, 10);
    strcat(table, temp);
    strcat(table, "   │\n");
    strcat(table, "├─────┼───────┼──────┼───────┤\n");

    //  закроет табличку, если игрок выйграл (т.е. 4 быка)
    if (player.bulls == 4)
    {
        strcat(table, "└─────┴───────┴──────┴───────┘\n");
    }
    printf(table);  //  вывод самой таблицы
/*
    printf("  ход   число   быки  коровы  \n");
    printf("┌─────┬───────┬──────┬───────┐\n");
    printf("│ %3d │"" %5d │ %3d  │ %3d   │\n", turn, number, bulls, cows);
    printf("├─────┼───────┼──────┼───────┤\n");
*/
}

//  сортировка рекордов (с ПК) по кол-ву ходов, чем меньше тем лучше
void sort_records(int* turns, char** names, const int amount_records)
{
    int sorted = 0, temp_int = 0, j = 0;
    char temp_name[len_name];
    while (!sorted) //  сортировка пузырьком, пока есть что сортировать, сортируем
    {
        sorted = 1;
        for (int i = 0; i < amount_records - j - 1; i++)
        {
            if (turns[i] > turns[i + 1])
            {
                //  меняем местами кол-во ходов и имена
                temp_int = turns[i];
                turns[i] = turns[i + 1];
                turns[i + 1] = temp_int;

                strcpy(temp_name, names[i]);
                strcpy(names[i], names[i + 1]);
                strcpy(names[i + 1], temp_name);

                sorted = 0;
            }
        }
    }
}

//  вывод рекордов
void output_records(int* turns, char** names, const int amount_records)
{
    system("cls");

    //  это для вывода инфо в конкретных значениях в консольке
    COORD position;
    position.X = 20;
    position.Y = 3;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
    printf("Таблица рекордов (single)");
    position.Y += 2;
    position.X -= 10;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);

    for (int i = 0; i < amount_records; i++)
    {
        //  первые три записи в рекордах будут выделены своим цветом
        switch(i)
        {
        case 0:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
            break;
        case 1:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
            break;
        case 2:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
            break;
        default:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            break;
        }
        printf("игрок %-22s отгадал число за %d шагов", names[i], turns[i]);
        position.Y++;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
    }
}

//  записать рекорды в файл
void save_record(const char* name, const int turns)
{
    FILE* file; //  создаем указатель на файл и открываем его с доступом append
    file = fopen("table-records.dat", "a");
    if (file == NULL)
    {
        printf("не удалось открыть таблицу рекордов\n");
        return;
    }
    fprintf(file, "%s %d\n", name, turns);  //  записываем инфо о победителе

    fclose(file);   //  закрываем файл
}

//  читаем файл с рекордами
void read_records()
{
    FILE* file; //  указ-ль на файл
    int amount_records = 0;
    file = fopen("table-records.dat", "r");
    if (file == NULL)
    {
        printf("не удалось открыть таблицу рекордов\n");
        Sleep(2000);
        return;
    }
    char buffer[len_name + 5];
    while (fgets(buffer, len_name + 5, file) != NULL)
    {
        //  считаем, сколько всего у нас победителей в файле
        amount_records++;
    }
    rewind(file);   //  возвращаемся в начало айла для дальнейшего чтения из него

    if (amount_records == 0)
    {
        printf("файл с таблицей рекордов пуст\n");
        Sleep(2000);
        return;
    }

    //  выделяем память под кол-во ходов и имена
    int* turns = (int*) malloc(amount_records * sizeof(int));
    char** names = (char**) malloc(amount_records * sizeof(char*));
    for (int i = 0; i < amount_records; i++)
    {
        names[i] = (char*) malloc(len_name * sizeof(char));
    }

    int i = 0;
    while (i < amount_records)
    {
        //  считываем из файла все записи построчно
        fscanf(file, "%s%d", names[i], &turns[i]);
        i++;
    }

    sort_records(turns, names, amount_records); //  сортируем рекорды
    output_records(turns, names, amount_records);   //  выводим рекорды

    //  высвобождаем память
    for (int i = 0; i < amount_records; i++)
    {
        free(names[i]);
    }
    free(names);
    free(turns);
    names = NULL;
    turns = NULL;

    printf("\n\nнажмите Enter для выхода в меню..");
    getchar();  //  чтобы программа преждевременно не закрылась
    getchar();
    fclose(file);   //  закрываем файл
}

//  вывод результатов и сохранение их в файл
void game_over(const int turns)
{
    printf("\nВы победили!\n");
    printf("\nВведите свое имя >> ");
    char* name = (char*)malloc(len_name * sizeof(char));

    scanf("%s", name);
    save_record(name, turns);
    free(name);

    printf("press any key\n");
    getchar();
}

//  вывод результатов для игры на двух человек
void game_over_hotseat(const Player player1, const Player player2)
{
    //  проверяем, у кого для отгадывания числа понадобилось меньше ходов
    if (player1.turns < player2.turns)
    {
        printf("\n\n\n");
        printf("Победа за Первым игроком!!!\n");
        printf("Первый игрок отгадал число за %d ходов\n", player1.turns);
        printf("Когда Второму потребовалось %d ходов\n", player2.turns);
        printf("\n");
    }
    else if (player1.turns > player2.turns)
    {
        printf("\n\n\n");
        printf("Победа за Вторым игроком!!!\n");
        printf("Второй игрок отгадал число за %d ходов\n", player2.turns);
        printf("Когда Первому потребовалось %d ходов\n", player1.turns);
        printf("\n");
    }
    else
    {
        printf("\n\n\n");
        printf("В этой игре вышла ничья\n");
        printf("Оба игрока отгадали загаданные друг другом числа за %d ходов\n", player1.turns);
        printf("\n");
    }

    printf("Нажмите Enter, чтобы выйти в меню..\n");
    getchar();
    getchar();
}

//  игра с ПК
void game_pc()
{
    system("cls");

    int is_gameover = 0;
    Player player = new_player();   //  создаем игрока
    table = (char*)malloc(size_table * sizeof(char));   //  выделяем память под таблицу
    memset(table, 0, sizeof(char)); //  лучше почитать в инете про это
    strcat(table, "        Быки и Коровы         \n");

    random_number();    //  генерируем число

    //  game loop
    while (!is_gameover)
    {
        player.bulls = 0;
        player.cows = 0;

        if (input_number(0) == -1)
        {
            //  проверка при вводе числа на выход
            return;
        }

        //  проверяется, отгадали ли число или нет
        for (int i = 0; i < 4; i++)
        {
            if (entered[i] == guessed[i])
            {
                player.bulls++;
            }
            else if (contains(entered[i]))
            {
                player.cows++;
            }
        }

        player.turns++;
        print_table(player);

        //  если угадали число, то выходим из game loop
        if (player.bulls == 4)
        {
            is_gameover = 1;
        }
    }
    game_over(player.turns);
    free(table);    //  очищаем память
}

//  для игры вдвоем
void game_hotseat()
{
    system("cls");
    Player players[2];  //   создаем массив структур (двух игроков)

    table = (char*)malloc(size_table * sizeof(char));
    memset(table, 0, sizeof(char));
    strcat(table, "        Быки и Коровы         \n");

    int is_gameover = 0;

    //  игра пройдет два раза, сначала для первого игрока, потом для второго
    for (int i = 0; i < 2; i++)
    {
        players[i] = new_player();  //  инициализируем все переменные
        char temp[1];
        strcat(table, "Сейчас отгадывает число Игрок ");
        itoa((i + 1), temp, 10);
        strcat(table, temp);
        strcat(table, "\n\n");

        printf("Игрок %d, загадайте число для Игрока %d\n", (2 - i), (i + 1));

        if (input_number(1) == -1)
        {
            //  загадываем число для другого игрока и тут же проверяем на выход из игры
            return;
        }

        is_gameover = 0;
        players[i].turns = 0;   //  тот же game loop что и для игры с ПК
        while (!is_gameover)
        {
            players[i].bulls = 0;
            players[i].cows = 0;

            printf("\nСейчас отгадывает число Игрок %d", (i + 1));
            if (input_number(0) == -1)
            {
                return;
            }

            for (int j = 0; j < 4; j++)
            {
                if (entered[j] == guessed[j])
                {
                    players[i].bulls++;
                }
                else if (contains(entered[j]))
                {
                    players[i].cows++;
                }
            }

            players[i].turns++;
            print_table(players[i]);

            if (players[i].bulls == 4)
            {
                is_gameover = 1;
            }
        }
        if (i == 0)
        {
            strcat(table, "\n\nСледующий игрок..\n");
        }
    }
    game_over_hotseat(players[0], players[1]);
    free(table);    //  очищаем память
}

//  печать содержимого меню
void print_menu()
{
    system("cls");
    COORD position;
    position.X = 30;
    position.Y = 5;

    //  для печати в центре устанавливаем позицию курсора
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
    printf("Меню");
    position.Y += 3;
    position.X -= 10;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
    printf("1. Начать игру с ПК.\n");

    position.Y++;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
    printf("2. Начать совместную игру.\n");

    position.Y++;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
    printf("3. Рекорды.\n");

    position.Y++;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
    printf("4. Выход.\n");

    position.Y += 3;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
    printf(">>  ");
}

int main()
{
    //  Устанавливаем кодировку UTF-8 для корректного вывода рамок, кириллицы
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleTitle("Bulls and Cows");

    char key;
    //  меню, тыкаем число, enter и выывается выбранная процедура
    while(TRUE)
    {
        print_menu();
        scanf("%c", &key);
        switch(key)
        {
        case '1':
            game_pc();
            break;
        case '2':
            game_hotseat();
            break;
        case '3':
            read_records();
            break;
        case '4':
            return 0;
        default:
            break;
        }
    }
    return 0;
}
