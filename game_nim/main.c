#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>
#include <locale.h>
#include "logs.h"

//  число кучек со спичками
#define SIZE_HEAPS 6
int heaps[SIZE_HEAPS];
//  это отступы по краям (для вывода инфо на экране)
const int margin_top = 3;
const int margin_left = 4;
const int margin_rigth = 70;

//  объявление всех функция и процедур
int nim_sum();  //  ним сумма, для алгоритма ПК
int check_matches();    //  проверка условий игры (остались ли еще спички)
int input_number();     //  ввод входных данных с последующей проверкой
void print_menu();      //  вывод меню на экран (по середине)
void game_pc();         //  игра против ПК
void game_hotseat();    //  игра друг против друга на одном устройстве
void AI_move(int* heap, int* matches);  //  логика хода ПК
void take_matches(const int this_heap, const int matches);  //  взятие спичек из кучи
void print_heaps(const int* heaps, const int select_heap, const int take_mathes);   //  отрисовка кучек на экране
void print_result_game(const int progress, const int winner);   //  вывод победителя на экран
void print_logs(const Player_log player_log1, const Player_log player_log2, const int is_player);   //  логи игры отрисовываются на экране

//  точка входа (основная программа)
int main()
{
    //  устанавливаем кодировку для консоли
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    //  название загаловка консоли
    SetConsoleTitle("Game Nim");

    char key;
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
        case '4':
            return 0;
        default:
            break;
        }
    }
    return 0;
}

//  вывод меню на экран
void print_menu()
{
    system("cls");
    COORD position; //  перемещение курсора в консоли
    position.X = 30;
    position.Y = 5;

    //  ставим курсор в консоли
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

    position.Y++;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
    printf("4. Выход.\n");

    position.Y += 3;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
    printf(">>  ");
}

//  игра против ПК
void game_pc()
{
    int current_player = 0, heap = 0, matches = 0;
    Player_log players_log[2];  //  для сохранения логов игры и дальнейшего вывода на экран
    //  инициализируем переменные
    players_log[0] = init_player_log(0);
    players_log[1] = init_player_log(0);

    srand(time(NULL));  //  привязываем текущее время к рандому, чтобы генерировать псевдо случайные числа
    for (int i = 0; i < SIZE_HEAPS; i++)
    {
        //  генерируем ПСЧ от 3 до 9
        heaps[i] = rand() % 7 + 3;
    }

    //  game loop (пока есть хотя бы одна спичка)
    while (check_matches() != 0)
    {
        system("cls");
        //  вывод логов игры и отрисовка кучек со спичками
        print_logs(players_log[0], players_log[1], current_player % 2);
        print_heaps(heaps, heap - 1, matches);

        //  проверяем, кто сейчас должен ходить
        if (current_player % 2 == 0)
        {
            printf("Очередь игрока\n");
            printf("Выберите кучу и количество спичек,\nкоторые хотите забрать: ");

            //  ввод данных (номер кучи)
            do
            {
                heap = input_number();
                if (heap == -1) { return; }
            } while (heaps[heap - 1] == 0 || heap > SIZE_HEAPS);

            //  ввод данных (количество спичек)
            do
            {
                matches = input_number();
                if (matches == -1) { return; }
            } while (matches > heaps[heap - 1]);
        }
        else    //  ход ПК
        {
            //  выделяем память под временные переменные
            int* temp_heap = (int*)malloc(sizeof(int));
            int* temp_matches = (int*)malloc(sizeof(int));
            printf("Ход ПК..");
            AI_move(temp_heap, temp_matches);   //  ход ПК, выбор кучи и кол-ва спичек
            heap = *temp_heap;          //  записываем в локальные переменные то, что выбрал ПК
            matches = *temp_matches;
            free(temp_heap);        //  освобождаем память
            free(temp_matches);     //  освобождаем память
            Sleep(1000);            //  усыпляем поток на секунду, чтобы сделать вид ,что ПК думает
        }

        //  добавляем в логи данные
        add_log(&players_log[current_player % 2], heap, matches);
        take_matches(heap - 1, matches);    //  забираем из кучи спички
        current_player++;   //  и кол-во ходов и оно же считает чей ход
    }

    system("cls");  //  очищаем экран
    print_logs(players_log[0], players_log[1], current_player % 2); //  выводим логи игры последнего хода
    print_heaps(heaps, heap - 1, matches);  //  выводим кучи (спичек нет, все забрали)
    print_result_game(current_player, 1);   //  выводим результаты игры
    delete_player_log(players_log);         //  очищаем память (удаляем логи)
}

//  игрок против игрока на одном устройстве
//  то же самое что и с ПК
void game_hotseat()
{
    int progress = 0, heap = 0, matches = 0;
    Player_log players_log[2];
    players_log[0] = init_player_log(0);
    players_log[1] = init_player_log(0);

    srand(time(NULL));
    for (int i = 0; i < SIZE_HEAPS; i++)
    {
        heaps[i] = rand() % 7 + 3;
    }

    while (check_matches() != 0)
    {
        system("cls");
        print_logs(players_log[0], players_log[1], -1);
        print_heaps(heaps, heap - 1, matches);
        printf("Очередь игрока %d\n", progress % 2 + 1);
        printf("Выберите кучу и количество спичек,\nкоторые хотите забрать: ");

        do
        {
            heap = input_number();
            if (heap == -1) { return; }
        } while (heaps[heap - 1] == 0 || heap > SIZE_HEAPS);

        do
        {
            matches = input_number();
            if (matches == -1) { return; }
        } while (matches > heaps[heap - 1]);

        add_log(&players_log[progress % 2], heap, matches);
        take_matches(heap - 1, matches);
        progress++;
    }

    system("cls");
    print_logs(players_log[0], players_log[1], -1);
    print_heaps(heaps, heap - 1, matches);
    print_result_game(progress, -1);
    delete_player_log(players_log);
}

//  выводим кучи со спичками на экран
void print_heaps(const int* heaps, const int select_heap, const int take_matches)
{
    //  нужен для форматированного вывода текста в консоль
    HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE);
    const int count_heap_in_line = 3;   //  максимальное кол-во куч выводимое в ряд в консоли
    int padding_top = margin_top;   //  отступы сверху и слева
    int padding_left = margin_left;
    COORD position;

    position.Y = padding_top - 2;
    position.X = padding_left + 4;
    SetConsoleCursorPosition(h_console, position);
    printf("Кучки со спичками");

    position.Y = padding_top;
    position.X = padding_left;
    //  printf("┌ │ ─ ├ ┼ ┤ ┐ └ ┘ ┬ ┴"); //  символы для отрисовки рамок

    //  рисуем кучи в специальных рамках
    for (int i = 0; i < SIZE_HEAPS; i++)
    {
        SetConsoleTextAttribute(h_console, 15);
        SetConsoleCursorPosition(h_console, position);
        position.Y++;
        //  если эту кучу выбирали и из нее забирали спички, то подсвечиваем ее цветом
        if (select_heap == i && take_matches != 0)
        {
            SetConsoleTextAttribute(h_console, 4);
            printf("-%d ┌───┐ ", take_matches); //  указываем кол-во забранных спичек
        }
        else
        {
            printf("   ┌───┐ ");
        }

        SetConsoleCursorPosition(h_console, position);
        position.Y++;
        printf("  ┌┘   └┐");
        SetConsoleCursorPosition(h_console, position);
        position.Y++;
        printf("%d │ %2d¡ │", (i + 1), heaps[i]);
        SetConsoleCursorPosition(h_console, position);
        position.Y++;
        printf("  └┐   ┌┘");
        SetConsoleCursorPosition(h_console, position);
        position.Y++;
        printf("   └───┘ ");

        if ((i + 1) % count_heap_in_line == 0 || (i + 1 == SIZE_HEAPS)) //  для вывода n куч в m столбцов
        {
            padding_top += 6;
            padding_left = margin_left;
            position.Y = padding_top;
            position.X = padding_left;
            SetConsoleCursorPosition(h_console, position);
        }
        else
        {
            padding_left += 15;
            position.X = padding_left;
            position.Y = padding_top;
            SetConsoleCursorPosition(h_console, position);
        }
    }
    SetConsoleTextAttribute(h_console, 15);
}

//  ним сумма
int nim_sum()
{
    int res = 0;
    for (int i = 0; i < SIZE_HEAPS; i++)
    {
        //  сумма всех спичек по модулю два
        res = res ^ heaps[i];
    }
    return res;
}

//  ИИ ПК
void AI_move(int* heap, int* matches)
{
    const int nim = nim_sum();
    int count = 1;
    //  если ним сумма равно 0, то ПК находится в выигрышной позиции
    if (nim == 0)
    {
        //  ИИ ищет первую кучу, в которой есть спички и забирает 1 спичку
        while (heaps[count - 1] == 0 && count <= SIZE_HEAPS)
        {
            count++;
        }
        *heap = count;
        *matches = 1;
    }
    else
    {
        //  ИИ высчитывает, сколько спичек и из какой кучи нужно взять, чтобы привести ним сумму к 0
        while (((heaps[count - 1] ^ nim) >= heaps[count - 1]) && (count <= SIZE_HEAPS))
        {
            count++;
        }
        *heap = count;
        *matches = heaps[count - 1] - (heaps[count - 1] ^ nim);
    }
}

//  ввод данных
int input_number()
{
    int number = -1;
    char temp = ' ';

    //  проверка на то, что введено число и нажата клавиша Enter
    while (temp != 13 && number == - 1)
    {
        temp = getchar();
        if (temp == 'q')
        {
            //  выход из игры в меню по клавишу q
            return -1;
        }

        if (temp == 8 && number > 0)
        {
            //  проверка на нажатие клавишы backspace
            number = -1;
            printf("\b\b \b");  //  стираем последний символ
        }

        if (temp >= 49 && temp <= 57)
        {
            //  проверяем, входит ли наш символ в данный диапозон (от 1 - 9)
            number = temp - 48; //  переводим тип char к int
        }
    }
    return number;
}

//  процедура взятия спичек
void take_matches(const int this_heap, const int matches)
{
    //  проверка на граничные условия
    if (matches < 1 || this_heap > SIZE_HEAPS || this_heap < 0)
    {
        return;
    }
    else if (heaps[this_heap] <= matches)
    {
        //  если так получится, что хотим взять спичек больше, чем имеется в данной куче
        //  мы возьмем все спички из этой кучи
        heaps[this_heap] = 0;
    }
    else
    {
        //  забираем спички из кучи
        heaps[this_heap] -= matches;
    }
}

//  проверка спичек
int check_matches()
{
    for (int i = 0; i < SIZE_HEAPS; i++)
    {
        //  если есть хоть одна спичка возвращаем 1 (т.е. не конец игры)
        if (heaps[i] != 0) { return 1;}
    }
    return 0;
}

//  вывод результатов
void print_result_game(const int progress, const int winner)
{
    printf("\nХодов совершено: %d\n", progress);
    if (winner == -1)
    {
        //  заходим сюда если играем PvP
        printf("Победил %s!\n", (progress % 2 != 0 ? "Первый Игрок" : "Второй Игрок"));
    }
    else
    {
        //  заходим если играем player vs PC
        if (progress % 2 != 0)
        {
            printf("Победил Игрок!\n");
        }
        else
        {
            printf("Победил Компьютер!\n");
        }
    }
    printf("Нажмите Enter чтобы выйти в меню..");
    getchar();
    getchar();
}

//  вывод логов игры
void print_logs(const Player_log player_log1, const Player_log player_log2, const int is_player)
{
    //  для форматированного вывода текста в консоль
    HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position; //  сюда будем записывать координаты, куда нужно выводить
    int padding_top = margin_top;       //  отступы
    int padding_right = margin_rigth;

    position.Y = padding_top - 2;
    position.X = padding_right - 20;
    SetConsoleCursorPosition(h_console, position);
    printf("Информация о ходах игроков");

    position.Y = padding_top - 1;
    position.X = padding_right - 20;
    SetConsoleCursorPosition(h_console, position);

    for (int i = 0; i < player_log1.size + player_log2.size; i++)
    {
        position.Y++;
        position.X = padding_right - 20;
        SetConsoleCursorPosition(h_console, position);

        if (is_player == -1)    //  проверяем что это хотсит
        {
            if (i % 2 == 0)
            {
                //  >> - это побитовый сдвиг влево, по сути то же деление на два
                printf("Игрок %d выбрал кучу: %d и взял спичек: %d", i % 2 + 1,
                        player_log1.select_heap[i >> 1], player_log1.take_matches[i >> 1]);
            }
            else
            {
                printf("Игрок %d выбрал кучу: %d и взял спичек: %d", i % 2 + 1,
                        player_log2.select_heap[i >> 1], player_log2.take_matches[i >> 1]);
            }
        }
        else
        {
            if (i % 2 == 0)
            {
                printf("Игрок выбрал кучу: %d и взял спичек: %d",
                        player_log1.select_heap[i >> 1], player_log1.take_matches[i >> 1]);

            }
            else
            {
                printf("Компьютер выбрал кучу: %d и взял спичек: %d",
                        player_log2.select_heap[i >> 1], player_log2.take_matches[i >> 1]);

            }
        }
    }
}
