#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

//  вариант 3   код - 0011
//  буквы сортируем по убыванию, начиная с начала,
//  массив индексов нужно сортировать по возрастанию, начиная с конца


/*
    Для поиска анаграмм нужно произвести следующие действия:
    отсортировать буквы всех слов по алфавиту;
    реализовать функцию сравнения строк;
    отсортировать слова с сортированными буквами по алфавиту. Для этого
    нужно создать массив индексов и при сортировке переставлять элементы в массиве индексов, не изменяя массив слов;
    просмотреть массив строк в порядке, указанном в массиве индексов, повторяющиеся слова напечатать в первоначальном виде.
    Слова-анаграммы печатаются в строчку (таких слов может быть два и более).
*/

//  константы (количесвто слов и максимальная длина слова)
#define WORDS 32
#define MAX_LEN 12

//  массив слов
// WORDS = 32
const char arr_of_words[WORDS][MAX_LEN] = {"мориста", "осрамит", "кот",     "море", "тросами",  "сиротам",  "сортами", "соритам",
                                            "ласков", "бобёр",  "майский", "словак", "славок",    "сковал",   "музыка", "строима",
                                            "видал",  "вдали",   "юпитер",  "влади", "акварелист", "владение", "давление", "кавалерист",
                                            "фрау", "ягуар", "яруга", "аконит", "фура", "катион", "трубопровод", "тоника"};

//  возвращет длину строки
int str_length(const char* str);

//  сравнение двух строк (по ASCII таблице)
//  if str1 < str2 => -1
//  if str1 == str2 => 0
//  if str1 > str2 => 1
int str_comparison(const char* str1, const char* str2);

//  сортируем слово по алфавиту
void sort_word(char* word);

//  сортирует индексы слов, в порядке возрастания (по ASCII таблице, т.е a < b < c < .. < z)
void sort_words_by_indeces(int* arr_index, const char arr_words[WORDS][MAX_LEN]);

//  выводим все одинаковые анаграммы в строку
void print_anagram(const int* arr_index, const char sorted[WORDS][MAX_LEN]);

int main()
{
    //  инициализация переменных
    setlocale(0, "rus");
    char sorted[WORDS][MAX_LEN];    //  массив который заполним словами из константного массива слов и отсортируем
    int* arr_index_sorted = NULL;   //  для сортировки слов по индексам
    arr_index_sorted = (int*)malloc(WORDS * sizeof(int));   //  выделили память

    printf("Список слов\n\n");
    for (int i = 0; i < WORDS; i++)
    {
        arr_index_sorted[i] = i;    //  в начале все слова стоят по порядку 0 - N
        for (int j = 0; j < MAX_LEN; j++)
            sorted[i][j] = arr_of_words[i][j];  //  копируем слова
        printf("[%d] = %-12s", arr_index_sorted[i], arr_of_words[i]);
        if ((i + 1) % 4 == 0)
            printf("\n");
    }

    //  выводим отсортированные слова по убыванию. (т.е я > ю > ... > в > б > а)
    printf("\n\n__________ОТСОРТИРОВАННЫЕ_СЛОВА_ПО_АЛФАВИТУ__________\n\n");
    for (int i = 0; i < WORDS; i++)
    {
        //  сортируем каждое слово по алфавиту
        sort_word(sorted[i]);
        printf("%-12s", sorted[i]);
        if ((i + 1) % 4 == 0)
            printf("\n");
    }
    printf("\n_____________________________________________________\n\n");

    //  сортируем по возрастанию. (т.е. а < б < в < .. < я) поэтому первыми идут слова начинающиеся на букву "а"
    //  сортируем индексы по словам
    sort_words_by_indeces(arr_index_sorted, sorted);

    //  печатаем анаграммы
    print_anagram(arr_index_sorted, sorted);

    //  высвобождаем память, выделенную под массив индексов
    free(arr_index_sorted);

    printf("\nНажмите клавишу Enter чтобы выйти\n");
    getchar();

/*
    проверял работоспособность функции сравнения строк со встроенной
    tests for str_comparison

    printf("%s == %s ? %d\n", "огонь", "абя", strcmp("огонь", "абя"));
    printf("%s == %s ? %d\n", "абя", "маяк", strcmp("абя", "маяк"));
    printf("%s == %s ? %d\n", "огонь", "абя", str_comparison("огонь", "абя"));
    printf("%s == %s ? %d\n", "абя", "маяк", str_comparison("абя", "маяк"));

    printf("str, str %d, strcmp: %d\n", str_comparison("str", "str"), strcmp("str", "str"));
    printf("st{12r, st{12r %d, strcmp: %d\n", str_comparison("st{12r", "st{12r"), strcmp("st{12r", "st{12r"));
    printf("\'\', \'\' %d, strcmp: %d\n", str_comparison("", ""), strcmp("", ""));
    printf("str1, str %d, strcmp: %d\n", str_comparison("str1", "str"), strcmp("str1", "str"));
    printf("str, str1 %d, strcmp: %d\n", str_comparison("str", "str1"), strcmp("str", "str1"));
    printf("ssr, str %d, strcmp: %d\n", str_comparison("ssr", "str"), strcmp("ssr", "str"));
    printf("sur, str %d, strcmp: %d\n", str_comparison("sur", "str"), strcmp("sur", "str"));
    printf("str, ssr %d, strcmp: %d\n", str_comparison("str", "ssr"), strcmp("str", "ssr"));
    printf("str, sur %d, strcmp: %d\n", str_comparison("str", "sur"), strcmp("str", "sur"));
*/

    return 0;
}

//  возвращет длину строки
int str_length(const char* str)
{
    int count = 0;
    //  пока не конец строки, считаем кол-во символов
    while (str[count] != '\0')
        count++;
    return count;
}

//  сравнение двух строк (по ASCII таблице)
//  if str1 < str2 => -1
//  if str1 == str2 => 0
//  if str1 > str2 => 1
int str_comparison(const char* str1, const char* str2)
{
    //  пока не конец одной из строк, сравниваем  i-e символы
    for (int i = 0; i < str_length(str1) && i < str_length(str2); i++)
    {
        if (str1[i] < str2[i])
            return -1;
        else if (str1[i] > str2[i])
            return 1;
    }

    //  на случай, если первые Н символы равны, значит одна из строк больше другой
    //  следовательно, если у 1 строки длина меньше, чем у второй, то 1 меньше 2 и т.д.
    if (str_length(str1) > str_length(str2))
        return 1;
    else if (str_length(str1) < str_length(str2))
        return -1;
    else
        return 0;
}

//  сортируем слово по алфавиту
void sort_word(char* word)
{
    char buff = ' ';
    int sorted = 0, i = 0;
    //  если ни разу не зашли в условие, значит ничего не сортировали, значит все уже отсортировано
    while(!sorted)
    {
        sorted = 1;
        //  бегаем по циклу от начала до первого непроверенного символа (поэтому читаем слева направо до тех пор, пока не встретим i)
        for (int j = 0; j < str_length(word) - 1 - i; j++)
        {
            //  сортировка пузырьком, если рядом стоящие символы не равны, то как-то их сдвигаем (по убыванию)
            if (word[j] < word[j + 1])
            {
                buff = word[j];
                word[j] = word[j + 1];
                word[j + 1] = buff;
                sorted = 0;
            }
        }
        i++;
    }
}

//  сортирует индексы слов, в порядке возрастания (по ASCII таблице, т.е a < b < c < .. < z)
void sort_words_by_indeces(int* arr_index, const char arr_words[WORDS][MAX_LEN])
{
    int buff = 0, sorted = 0, i = 0;
    while (!sorted)  //  мы будем сортировать, пока не выполнено условие sorted == 1 (т.е. в том случае, когда ни разу на войдем в условие)
    {
        sorted = 1;
        //  бегаем по циклу начиная с конца, до первого слова, которое еще не проверили (поэтому пока j > i)
        for (int j = WORDS - 1; j > i; j--)
        {
            //  проверяем, слово от массива индексов на j месте меньше чем слово от массива индексов на j - 1
            //  проверяем от массива индексов потому что этот массив меняется, а массив слов - нет
            if (str_comparison(arr_words[arr_index[j]], arr_words[arr_index[j - 1]]) == -1)
            {
                //  меняем значения местами (индексы) по возрастанию
                buff = arr_index[j];
                arr_index[j] = arr_index[j - 1];
                arr_index[j - 1] = buff;
                sorted = 0;
            }
        }
        i++;
    }
}

//  выводим все одинаковые анаграммы в строку
void print_anagram(const int* arr_index, const char sorted[WORDS][MAX_LEN])
{
    printf("\n");
    printf("______________АНАГРАММЫ________________\n\n");

    for (int i = 0, j = 0; i < WORDS; i++)
    {
        //  сравниваем рядом стоящие слова на награммы, если они не являются анаграммами, то печатаем на следующей строке
        if (str_comparison(sorted[arr_index[i]], sorted[arr_index[j]]) != 0)
            printf("\n");

        //  выводим слова через таб
        printf("%-12s", arr_of_words[arr_index[i]]);

        //  нужно для того, чтобы на первой итерации не переходить на следующую строку
        if (i != 0)
            j++;
    }
    printf("\n");
    printf("______________________________________");
}
