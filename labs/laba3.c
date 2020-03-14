#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

//  ������� 3   ��� - 0011
//  ����� ��������� �� ��������, ������� � ������,
//  ������ �������� ����� ����������� �� �����������, ������� � �����


/*
    ��� ������ �������� ����� ���������� ��������� ��������:
    ������������� ����� ���� ���� �� ��������;
    ����������� ������� ��������� �����;
    ������������� ����� � �������������� ������� �� ��������. ��� �����
    ����� ������� ������ �������� � ��� ���������� ������������ �������� � ������� ��������, �� ������� ������ ����;
    ����������� ������ ����� � �������, ��������� � ������� ��������, ������������� ����� ���������� � �������������� ����.
    �����-��������� ���������� � ������� (����� ���� ����� ���� ��� � �����).
*/

//  ��������� (���������� ���� � ������������ ����� �����)
#define WORDS 32
#define MAX_LEN 12

//  ������ ����
// WORDS = 32
const char arr_of_words[WORDS][MAX_LEN] = {"�������", "�������", "���",     "����", "�������",  "�������",  "�������", "�������",
                                            "������", "����",  "�������", "������", "������",    "������",   "������", "�������",
                                            "�����",  "�����",   "������",  "�����", "����������", "��������", "��������", "����������",
                                            "����", "�����", "�����", "������", "����", "������", "�����������", "������"};

//  ��������� ����� ������
int str_length(const char* str);

//  ��������� ���� ����� (�� ASCII �������)
//  if str1 < str2 => -1
//  if str1 == str2 => 0
//  if str1 > str2 => 1
int str_comparison(const char* str1, const char* str2);

//  ��������� ����� �� ��������
void sort_word(char* word);

//  ��������� ������� ����, � ������� ����������� (�� ASCII �������, �.� a < b < c < .. < z)
void sort_words_by_indeces(int* arr_index, const char arr_words[WORDS][MAX_LEN]);

//  ������� ��� ���������� ��������� � ������
void print_anagram(const int* arr_index, const char sorted[WORDS][MAX_LEN]);

int main()
{
    //  ������������� ����������
    setlocale(0, "rus");
    char sorted[WORDS][MAX_LEN];    //  ������ ������� �������� ������� �� ������������ ������� ���� � �����������
    int* arr_index_sorted = NULL;   //  ��� ���������� ���� �� ��������
    arr_index_sorted = (int*)malloc(WORDS * sizeof(int));   //  �������� ������

    printf("������ ����\n\n");
    for (int i = 0; i < WORDS; i++)
    {
        arr_index_sorted[i] = i;    //  � ������ ��� ����� ����� �� ������� 0 - N
        for (int j = 0; j < MAX_LEN; j++)
            sorted[i][j] = arr_of_words[i][j];  //  �������� �����
        printf("[%d] = %-12s", arr_index_sorted[i], arr_of_words[i]);
        if ((i + 1) % 4 == 0)
            printf("\n");
    }

    //  ������� ��������������� ����� �� ��������. (�.� � > � > ... > � > � > �)
    printf("\n\n__________���������������_�����_��_��������__________\n\n");
    for (int i = 0; i < WORDS; i++)
    {
        //  ��������� ������ ����� �� ��������
        sort_word(sorted[i]);
        printf("%-12s", sorted[i]);
        if ((i + 1) % 4 == 0)
            printf("\n");
    }
    printf("\n_____________________________________________________\n\n");

    //  ��������� �� �����������. (�.�. � < � < � < .. < �) ������� ������� ���� ����� ������������ �� ����� "�"
    //  ��������� ������� �� ������
    sort_words_by_indeces(arr_index_sorted, sorted);

    //  �������� ���������
    print_anagram(arr_index_sorted, sorted);

    //  ������������ ������, ���������� ��� ������ ��������
    free(arr_index_sorted);

    printf("\n������� ������� Enter ����� �����\n");
    getchar();

/*
    �������� ����������������� ������� ��������� ����� �� ����������
    tests for str_comparison

    printf("%s == %s ? %d\n", "�����", "���", strcmp("�����", "���"));
    printf("%s == %s ? %d\n", "���", "����", strcmp("���", "����"));
    printf("%s == %s ? %d\n", "�����", "���", str_comparison("�����", "���"));
    printf("%s == %s ? %d\n", "���", "����", str_comparison("���", "����"));

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

//  ��������� ����� ������
int str_length(const char* str)
{
    int count = 0;
    //  ���� �� ����� ������, ������� ���-�� ��������
    while (str[count] != '\0')
        count++;
    return count;
}

//  ��������� ���� ����� (�� ASCII �������)
//  if str1 < str2 => -1
//  if str1 == str2 => 0
//  if str1 > str2 => 1
int str_comparison(const char* str1, const char* str2)
{
    //  ���� �� ����� ����� �� �����, ����������  i-e �������
    for (int i = 0; i < str_length(str1) && i < str_length(str2); i++)
    {
        if (str1[i] < str2[i])
            return -1;
        else if (str1[i] > str2[i])
            return 1;
    }

    //  �� ������, ���� ������ � ������� �����, ������ ���� �� ����� ������ ������
    //  �������������, ���� � 1 ������ ����� ������, ��� � ������, �� 1 ������ 2 � �.�.
    if (str_length(str1) > str_length(str2))
        return 1;
    else if (str_length(str1) < str_length(str2))
        return -1;
    else
        return 0;
}

//  ��������� ����� �� ��������
void sort_word(char* word)
{
    char buff = ' ';
    int sorted = 0, i = 0;
    //  ���� �� ���� �� ����� � �������, ������ ������ �� �����������, ������ ��� ��� �������������
    while(!sorted)
    {
        sorted = 1;
        //  ������ �� ����� �� ������ �� ������� �������������� ������� (������� ������ ����� ������� �� ��� ���, ���� �� �������� i)
        for (int j = 0; j < str_length(word) - 1 - i; j++)
        {
            //  ���������� ���������, ���� ����� ������� ������� �� �����, �� ���-�� �� �������� (�� ��������)
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

//  ��������� ������� ����, � ������� ����������� (�� ASCII �������, �.� a < b < c < .. < z)
void sort_words_by_indeces(int* arr_index, const char arr_words[WORDS][MAX_LEN])
{
    int buff = 0, sorted = 0, i = 0;
    while (!sorted)  //  �� ����� �����������, ���� �� ��������� ������� sorted == 1 (�.�. � ��� ������, ����� �� ���� �� ������ � �������)
    {
        sorted = 1;
        //  ������ �� ����� ������� � �����, �� ������� �����, ������� ��� �� ��������� (������� ���� j > i)
        for (int j = WORDS - 1; j > i; j--)
        {
            //  ���������, ����� �� ������� �������� �� j ����� ������ ��� ����� �� ������� �������� �� j - 1
            //  ��������� �� ������� �������� ������ ��� ���� ������ ��������, � ������ ���� - ���
            if (str_comparison(arr_words[arr_index[j]], arr_words[arr_index[j - 1]]) == -1)
            {
                //  ������ �������� ������� (�������) �� �����������
                buff = arr_index[j];
                arr_index[j] = arr_index[j - 1];
                arr_index[j - 1] = buff;
                sorted = 0;
            }
        }
        i++;
    }
}

//  ������� ��� ���������� ��������� � ������
void print_anagram(const int* arr_index, const char sorted[WORDS][MAX_LEN])
{
    printf("\n");
    printf("______________���������________________\n\n");

    for (int i = 0, j = 0; i < WORDS; i++)
    {
        //  ���������� ����� ������� ����� �� ��������, ���� ��� �� �������� �����������, �� �������� �� ��������� ������
        if (str_comparison(sorted[arr_index[i]], sorted[arr_index[j]]) != 0)
            printf("\n");

        //  ������� ����� ����� ���
        printf("%-12s", arr_of_words[arr_index[i]]);

        //  ����� ��� ����, ����� �� ������ �������� �� ���������� �� ��������� ������
        if (i != 0)
            j++;
    }
    printf("\n");
    printf("______________________________________");
}
