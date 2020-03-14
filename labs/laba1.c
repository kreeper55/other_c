#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// 3 % 15 + 10 = 13 �������

#define ARR_SIZE 10    //  ������ �����
#define NUMBER_SYSTEM 13     //  ������� ���������

const char alphabet[] = {   '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                            'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

//  ���������� ��� unsigned long long int ��� �������� ������
typedef unsigned long long ull;

//  ������� ���������� ����� � ������� (��� ������� �����)
ull pow_ull(const int number, const int degree)
{
    ull result = 1;
    for (int i = 0; i < degree; i++)
        result *= number;
    return result;
}

//  ����� �����(�����) � �������� ������� ���������
void print_numeral(const int numeral);

//  ����� �����
void print_number(const int* number);

//  ����������� �����
void copy_num(const int* copy, int* number);

//  ����� ����� � �������� ������� ���������
void sum_num(const int* number_left, const int* number_right, int* sum);

//  �������� �����
void difference_num(const int* number_left, const int* number_right, int* sum);

//  �������������� �����(������) �� �����(� ���������� ��)
void init_arr_num(ull decimal_number, int* arr_number);

//  ��������� �����(�� �������) � ���������� ���� unsigned long long
void save_num(const int* arr_number, ull* decimal_number);

//  ��������� � 13-������ �� (��� ������ � ����)
void to_thirteen_system(char* thirteen_number);

//  ������� � �������� �� (��� ������ � ����)
ull to_binary_sys(int number);

//  ������ � ���� ������� ��
//  10-� 2-� 16-� 13-�
void create_table();

//  �����
int main()
{
    setlocale(0, "rus");
    //  �������������� ����� ��� ������
    int number1[] = {0, 0, 0, 12, 5, 12, 12, 0, 1, 11};
    int number2[] = {0, 0, 2, 10, 2, 3, 12, 4, 7, 9};
    int number3[] = {12, 12, 1, 8, 10, 11, 6, 0, 10, 7};
    int number4[ARR_SIZE];  // for init
    int result[ARR_SIZE];   //  ��� ���������� ����, �������� �����
    int is_equal = 1;       //  ��� �������� ������
    int all_is_equal = 1;   //  ��� �������� ���� ������

    //  ������� ����� � ��������� �� � ��� ���
    printf("\n���� 1. ������ �����\n");
    print_numeral(0);
    printf("\t ��� = 0\n");
    print_numeral(8);
    printf("\t ��� = 8\n");
    print_numeral(10);
    printf("\t ��� = 10\n");
    print_numeral(12);
    printf("\t ��� = 12\n");

    //  �������� ������� ����� ��� ������� ��������� (��� �� ����������� �� ������)
    print_numeral(13);
    printf("\n");
    print_numeral(-3);
    printf("_____________________________________\n");

    //  ������� �����, ������� �������� ����
    printf("\n���� 2. ������ �����\n");
    printf("number1 = ");
    print_number(number1);
    printf("\n");
    printf("number2 = ");
    print_number(number2);
    printf("\n");
    printf("number3 = ");
    print_number(number3);
    printf("\n");
    printf("�������� �� number2 � number4\n");
    copy_num(number2, number4);
    printf("number4 = ");
    print_number(number4);
    printf("\n");
    printf("_____________________________________\n");

    //  �������������� ����� � ������� ���������� (�� 10 � 13 ��)
    printf("\n���� 3. ����� �� 10-� �� � 13-� ��\n");
    int test3_1[] = {0, 0, 12, 10, 12, 4, 9, 12, 0, 1};
    int test3_2[] = {12, 12, 12, 12, 12, 12, 12, 12, 12, 0};
    is_equal = 1;
    ull long_num_1 = 805841856llu;
    init_arr_num(long_num_1, number4);
    printf("1) ����� � 10-� �� = %d\n ����� � 13-� �� = ", long_num_1);
    print_number(number4);
    printf("\n");
    //  ���������� ���� ����� � ���, ��� ������ ����������
    for (int i = 0; i < ARR_SIZE; i++)
    {
        if (test3_1[i] != number4[i])
        {
            all_is_equal = 0;
            is_equal = 0;
            break;
        }
    }
    //  ������� ��������� ��������� ����
    if (is_equal)
        printf("���� 3_1 �������\n");
    else
        printf("���� 3_1 ��������\n");

    printf("\n");
    ull long_num_2 = 137858491836llu;     //  ������������ ����� ������ � ������ ��������
    init_arr_num(long_num_2, number4);    //  ����-� ����� � 13 ������� ������ � 10�
    printf("2) ����� � 10-� �� = %llu\n ����� � 13-� �� = ", long_num_2);
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
        printf("���� 3_2 �������\n");
    else
        printf("���� 3_2 ��������\n");
    printf("\n");
    printf("_____________________________________\n");

    //  ��������� ��� ������������ ����� � 13 ��
    printf("\n���� 4. ����� ����� � 13 ��\n");
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
        printf("���� 4 �������");
    else
        printf("���� 4 ��������");
    printf("\n");
    printf("_____________________________________\n");

    //  �������� ��������� � 13 ��
    printf("\n���� 5. �������� ����� � 13-� ��\n");
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
        printf("���� 5 �������");
    else
        printf("���� 5 ��������");
    printf("\n");
    printf("_____________________________________\n");

    //  ��������� ����� �� 13 � 10 ��
    printf("\n���� 6. ��������� ����� \n(������� ������������ � ���� ������� � ���������� \n");
    int test6[ARR_SIZE];
    copy_num(number3, test6);
    ull test6_long = 137148164537llu;
    ull* variable = (ull*)malloc(sizeof(ull));
    save_num(test6, variable);
    printf("��������� ����� = %llu \n�������� �� ����� ���� = %llu\n", test6_long, *variable);
    if (test6_long == *variable)
    {
        printf("���� 6 �������");
    }
    else
    {
        all_is_equal = 0;
        printf("���� 6 ��������");
    }
    free(variable);
    printf("\n");
    printf("_____________________________________\n");

    //  ���� ��� ����� ��������, �� ������� �� ����� ��������������� ���������
    if (all_is_equal)
        printf("��� ����� �������� �������\n");
    else
        printf("�� ��� ����� ��������\n");

    printf("\n���� ������ ������� � ����. \n\n");
    create_table();    //  ������� �������� � 10, 2, 16, 13 ��

    printf("\n������� Enter ����� �����\n");
    getchar();
    return 0;
}

//  ����� �����(�����) � �������� ������� ���������
void print_numeral(const int numeral)
{
    //  �������� �� ��������
    if (numeral >= 0 && numeral < NUMBER_SYSTEM)
        printf("%c", alphabet[numeral]);
    //  ���� ������ ��������, ������� ����� �� ������ ��������
}

//  ����� �����
void print_number(const int* number)
{
    for (int i = 0; i < ARR_SIZE; i++)
        print_numeral(number[i]);
    //  ������� ���������� �����
}

//  ����������� �����
void copy_num(const int* copy, int* number)
{
    for (int i = 0; i < ARR_SIZE; i++)
        number[i] = copy[i];
    //  �������� ������ ������� � ������ arr
}

//  ����� ����� � �������� ������� ���������
void sum_num(const int* number_left, const int* number_right, int* sum)
{
    int discharge = 0;  //  ������
    for (int i = ARR_SIZE - 1; i >= 0; i--)
    {
        //  ���� ����� ����� ������ ������� ������� ���������
        if (number_left[i] + number_right[i] + discharge >= NUMBER_SYSTEM)
        {
            //  �� ���������� ����� ���� ������ � ����� ������� �� ������� �� ����� = ������� ���������
            sum[i] = (number_left[i] + number_right[i] + discharge) % NUMBER_SYSTEM;
            //  ��������� ������� �������
            discharge = 1;
        }
        else
        {
            //  � ���� ������, ����� ��� �������� ����� ������ ������� ������� ���������
            sum[i] = number_left[i] + number_right[i] + discharge;
            //  �������� ������
            discharge = 0;
        }
    }
}

//  �������� �����
void difference_num(const int* number_left, const int* number_right, int* sum)
{
    int discharge = 0;  //  ���������� ������
    for (int i = ARR_SIZE - 1; i >= 0; i--)
    {
        //  ���������, ������ �� ����� ����� ������� � ������ ���������� ��������
        if ((number_left[i] - discharge) - number_right[i] >= 0)
        {
            sum[i] = (number_left[i] - discharge) - number_right[i];
            discharge = 0;
        }
        //  � ������, ����� ��� ��������� ����� ����� ������ ������� � ����� �������� ������
        else
        {
            sum[i] = number_left[i] + NUMBER_SYSTEM - number_right[i] - discharge;
            discharge = 1;
        }
    }
}

//  �������������� �����(������) �� �����(� ���������� ��)
void init_arr_num(ull decimal_number, int* arr_number)
{
    int i = ARR_SIZE - 1;

    //  ���� �� ������ �����
    while (decimal_number > 0 && i >= 0)
    {
        //  ����� ��������� ����� ����� �� ������ ��
        arr_number[i] = decimal_number % NUMBER_SYSTEM;
        //  ������� ��������� ����������� �����
        decimal_number /= NUMBER_SYSTEM;
        i--;
    }

    for (int j = i; j >= 0; j--)
        arr_number[j] = 0;
    //  �������� ���������� ��������
}

//  ��������� �����(�� �������) � ���������� ���� unsigned long long
void save_num(const int* arr_number, ull* decimal_number)
{
    *decimal_number = 0;
    int j = ARR_SIZE - 1;
    for (int i = 0; i < ARR_SIZE; i++, j--)
        *decimal_number = *decimal_number + arr_number[i] * pow_ull(NUMBER_SYSTEM, j);
    //  ��������� ����� � ���������� ��
}

//  ��������� � 13-������ �� (��� ������ � ����)
void to_thirteen_system(char* thirteen_number)
{
    for (int i = 1, j = 1; i < 26; i++, j += 2)
    {
        thirteen_number[j - 1] = alphabet[i / NUMBER_SYSTEM];   //  �������� ������ �����
        thirteen_number[j] = alphabet[i % NUMBER_SYSTEM];       //  �������� ������ �����
    }
}

//  ������� � �������� �� (��� ������ � ����)
ull to_binary_sys(int number)
{
    ull binary_number = 0;
    int i = 0;
    while (number > 0)
    {
        //  ��������� ����� � �������� ��
        binary_number += (number % 2) * pow_ull(10, i);
        //  ��������� ����� ������ (���� ����� ������� �� ���, ������ ����� ��������� ��������
        number >>= 1;
        i++;
    }
    return binary_number;
}

//  ������ � ���� ������� ��
//  10-� 2-� 16-� 13-�
void create_table()
{
    int binary_arr[25];     //  ������ ��� ������ ����� � 2-� ��
    char thirteen_sys[50];    //  ������ ��� ������ ����� � 13-� ��
    to_thirteen_system(thirteen_sys);  //  ������� ����� � 13-� ��
    int j = 1;

    // ��������� ��������� �� ����
    FILE *filePointer;

    //  ��������� �������, � ������� �������� �����
    filePointer = fopen("table.dat", "w");

    //  ��������� ��������� �� ����
    //  ���� ���� �� ���� ��������� (� ��������� w ������ �� �����
    //  ���� �� ����������, �� ��� �������
    if (filePointer == NULL)
    {
        printf( "table.dat ���� ������� �� ����������." );
        return;
    }
    printf("���� ������� ������.\n");
    //  ���������� � ���� �������
    fprintf(filePointer, "  DEC    BIN   HEX  13  \n");
    fprintf(filePointer, "------------------------\n");
    for (int i = 1; i < 26; i++)
    {
        binary_arr[i - 1] = to_binary_sys(i);
        fprintf(filePointer, "| %2d | %5d | %2x |", i, binary_arr[i - 1], i);
        //  ������� ���������� ���� � �������
        fprintf(filePointer, " %c%c |\n", thirteen_sys[j - 1], thirteen_sys[j]);
        j += 2;
    }
    fprintf(filePointer, "------------------------");
    fclose(filePointer);

    printf("������ ������� �������� � ���� table.dat\n");
    printf("���� ������� ������.");
}
