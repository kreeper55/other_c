#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <time.h>
#include <windows.h>

// 3 вариант
const double sum_one = 2.0;

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

//  сумма ряда
double sum_task1(const double eps);

//  сумма ряда в точке Х
double sum_task2(const double eps, const double x, const double a);

double exp_a(const double x, const double a)
{
    return exp(x * log(a));
}

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    //  для выбора задания
    char task[1];

    //  for sum = 2
    double epsilon = 0.1;
    double sum = 0;

    //  for sum exp( x * log (a) )
    const float step = 0.1;     //  шаг
    const float start = -1.0;   //  начало отрезка
    const float end = 1.0;    //  конец отрезка
    srand(time(NULL));
    float a = (double) rand() / RAND_MAX;

    //  for 3 task
    int size_arr = 0, average = 0, was_symbol = 0, amount_symb = 0;
    char symbol;
    char* arr_symb = NULL;

    printf("выберите задание\n");
    printf("1) сумма ряда равная единице (1. / (2 ^ n))\n");
    printf("2) сумма ряда = a ^ x, где |x| < бесконечности \n");
    printf("3) найти в массиве символов среднюю длину последовательностей из двух или более символов\n");
    printf("0) -> Выход\n");
    scanf("%s", task);

    switch(task[0])
    {
        case '1':
            printf("сумма ряда равна = %-22.18f\n", sum_one);
            do
            {
                sum = sum_task1(epsilon);
                printf("EPSILON = %1.0e, sum = %-24.20f", epsilon, sum);
                printf("реальная точность = %1.16e\n", fabs(sum_one - sum));
                epsilon *= 0.1;     //  считаем для каждого эпсилон от 1.e-1 - 1.e-17
            } while (epsilon > 1.e-17);
            epsilon = 0.1;
            break;
        case '2':
            printf("\n\n");
            for (double x = start; x < end; x += step)
            {
                epsilon = 0.1;
                printf("\n\nx = %-4.5f, %f^(%-4.5f) = %-24.20f\n\n", x, a, x, exp_a(x, a));
                do
                {
                    sum = sum_task2(epsilon, x, a);
                    printf("EPSILON = %1.0e, sum = %-24.20f", epsilon, sum);
                    printf("реальная точность = %1.20e\n", fabs(log(x) - sum));
                    epsilon *= 0.1;
                } while (epsilon > 1.e-18);
                printf("нажмите Enter, чтобы родолжить\n\n");
                getchar();
            }
            epsilon = 0.1;
            break;
        case '3':
            printf("введите длину массива >> ");
            scanf("%d", &size_arr);

            arr_symb = (char*) malloc(size_arr * sizeof(char));

            for (int i = 0; i < size_arr; i++)
            {
                printf("введите символ: ");
                scanf("%s", &arr_symb[i]);
            }

            symbol = arr_symb[0];
            was_symbol = 1;
            for (int i = 1; i < size_arr; i++)
            {
                if (symbol == arr_symb[i])
                {
                    if (was_symbol)
                    {
                        average++;
                        was_symbol = 0;
                        amount_symb++;
                    }
                    average++;
                }
                else
                {
                    was_symbol = 1;
                    symbol = arr_symb[i];
                }
            }

            if (size_arr == average)
            {
                printf("среднея длина последовательностей из двух и более символов = %d\n", average);
            }
            else
            {
                average /= amount_symb;
                printf("среднея длина последовательностей из двух и более символов = %d\n", average);
            }
            free(arr_symb);
            break;
        case '0':
            printf("Выход\n");
            return 0;
        default :
            printf("Неверно выбрано задание, попробуйте снова\n");
            epsilon = 0.1;
            break;
        }
    printf("Выход\n");
    return 0;
}

//  сумма ряда
double sum_task1(const double eps)
{
    double current = 0.;
    double sum = 0.;
    unsigned long long n = 0;
    do
    {
        //  считаем текущее слагаемое
        current = 1. / pow_ull(2, n);
        //  прибавляем к общей сумме
        sum += current;
        n++;
    } while (current > eps && n < pow(10, 9));
    //  суммируем, пока текущий элемент больше заданного эпсилон (или пока итераций не больше 10^9)
    return sum;
}

/*
    сумма ряда равна = 2.000000000000000000
    EPSILON = 1e-001, iterations =     5 sum = 1.93750000000000000000, real precision = 6.2500000000e-002
    EPSILON = 1e-002, iterations =     8 sum = 1.99218750000000000000, real precision = 7.8125000000e-003
    EPSILON = 1e-003, iterations =    11 sum = 1.99902343750000000000, real precision = 9.7656250000e-004
    EPSILON = 1e-004, iterations =    15 sum = 1.99993896484375000000, real precision = 6.1035156250e-005
    EPSILON = 1e-005, iterations =    18 sum = 1.99999237060546870000, real precision = 7.6293945313e-006
    EPSILON = 1e-006, iterations =    21 sum = 1.99999904632568360000, real precision = 9.5367431641e-007
    EPSILON = 1e-007, iterations =    25 sum = 1.99999994039535520000, real precision = 5.9604644775e-008
    EPSILON = 1e-008, iterations =    28 sum = 1.99999999254941940000, real precision = 7.4505805969e-009
    EPSILON = 1e-009, iterations =    31 sum = 1.99999999906867740000, real precision = 9.3132257462e-010
    EPSILON = 1e-010, iterations =    35 sum = 1.99999999994179230000, real precision = 5.8207660913e-011
    EPSILON = 1e-011, iterations =    38 sum = 1.99999999999272400000, real precision = 7.2759576142e-012
    EPSILON = 1e-012, iterations =    41 sum = 1.99999999999909050000, real precision = 9.0949470177e-013
    EPSILON = 1e-013, iterations =    45 sum = 1.99999999999994320000, real precision = 5.6843418861e-014
    EPSILON = 1e-014, iterations =    48 sum = 1.99999999999999290000, real precision = 7.1054273576e-015
    EPSILON = 1e-015, iterations =    51 sum = 1.99999999999999910000, real precision = 8.8817841970e-016
    EPSILON = 1e-016, iterations =    55 sum = 2.00000000000000000000, real precision = 0.0000000000e+000
    EPSILON = 1e-017, iterations =    58 sum = 2.00000000000000000000, real precision = 0.0000000000e+000

    Из таблицы видим, что сумма ряда посчитана с точностью выше 10^-17 (действительная точность ^)
*/

//  сумма ряда в точке Х
double sum_task2(const double eps, const double x, const double a)
{
    double current = 0., sum = 0.;
    unsigned long long n = 0, fact = 1;
    do
    {
        //  считаем текущее слагаемое
        current = powl(x * log(a), n) / (fact);
        sum += current;
        n++;
        fact *= n;
    } while (fabs(current) > eps && n < pow(10, 8));
    //  выполняем пока текущее слагаемое по модулю больше заданного эпсилон
    //  либо пока число итераций не превысило 10^8
    return sum;
}


/*

x = -1.00000, 0.539537^(-1.00000) = 1.85344198647712900000

EPSILON = 1e-001, iterations =    4 sum = 1.84657234545822900000, real precision = 6.8696410189e-003
EPSILON = 1e-002, iterations =    5 sum = 1.85261259028579240000, real precision = 8.2939619134e-004
EPSILON = 1e-003, iterations =    6 sum = 1.85335801018764680000, real precision = 8.3976289482e-005
EPSILON = 1e-004, iterations =    7 sum = 1.85343466972242040000, real precision = 7.3167547086e-006
EPSILON = 1e-005, iterations =    8 sum = 1.85344142719956140000, real precision = 5.5927756759e-007
EPSILON = 1e-006, iterations =    9 sum = 1.85344194840752690000, real precision = 3.8069602137e-008
EPSILON = 1e-007, iterations =   10 sum = 1.85344198414180240000, real precision = 2.3353265988e-009
EPSILON = 1e-008, iterations =   11 sum = 1.85344198634676590000, real precision = 1.3036305369e-010
EPSILON = 1e-009, iterations =   12 sum = 1.85344198647045320000, real precision = 6.6757710471e-012
EPSILON = 1e-010, iterations =   13 sum = 1.85344198647681320000, real precision = 3.1574742820e-013
EPSILON = 1e-011, iterations =   13 sum = 1.85344198647681320000, real precision = 3.1574742820e-013
EPSILON = 1e-012, iterations =   14 sum = 1.85344198647711520000, real precision = 1.3766765505e-014
EPSILON = 1e-013, iterations =   15 sum = 1.85344198647712850000, real precision = 4.4408920985e-016
EPSILON = 1e-014, iterations =   16 sum = 1.85344198647712900000, real precision = 0.0000000000e+000
EPSILON = 1e-015, iterations =   16 sum = 1.85344198647712900000, real precision = 0.0000000000e+000
EPSILON = 1e-016, iterations =   17 sum = 1.85344198647712900000, real precision = 0.0000000000e+000
EPSILON = 1e-017, iterations =   18 sum = 1.85344198647712900000, real precision = 0.0000000000e+000
EPSILON = 1e-018, iterations =   18 sum = 1.85344198647712900000, real precision = 0.0000000000e+000


x = -0.90000, 0.539537^(-0.90000) = 1.74253334259240540000

EPSILON = 1e-001, iterations =    4 sum = 1.73808596387669940000, real precision = 4.4473787157e-003
EPSILON = 1e-002, iterations =    5 sum = 1.74204896848181770000, real precision = 4.8437411059e-004
EPSILON = 1e-003, iterations =    6 sum = 1.74248913147601980000, real precision = 4.4211116386e-005
EPSILON = 1e-004, iterations =    7 sum = 1.74252987149543470000, real precision = 3.4710969707e-006
EPSILON = 1e-005, iterations =    8 sum = 1.74253310357576560000, real precision = 2.3901663981e-007
EPSILON = 1e-006, iterations =    9 sum = 1.74253332793870140000, real precision = 1.4653704028e-008
EPSILON = 1e-007, iterations =   10 sum = 1.74253334178289170000, real precision = 8.0951378933e-010
EPSILON = 1e-008, iterations =   11 sum = 1.74253334255171490000, real precision = 4.0690562031e-011
EPSILON = 1e-009, iterations =   11 sum = 1.74253334255171490000, real precision = 4.0690562031e-011
EPSILON = 1e-010, iterations =   12 sum = 1.74253334259052920000, real precision = 1.8762769116e-012
EPSILON = 1e-011, iterations =   13 sum = 1.74253334259232550000, real precision = 7.9936057773e-014
EPSILON = 1e-012, iterations =   14 sum = 1.74253334259240230000, real precision = 3.1086244690e-015
EPSILON = 1e-013, iterations =   14 sum = 1.74253334259240230000, real precision = 3.1086244690e-015
EPSILON = 1e-014, iterations =   15 sum = 1.74253334259240540000, real precision = 0.0000000000e+000
EPSILON = 1e-015, iterations =   16 sum = 1.74253334259240570000, real precision = 2.2204460493e-016
EPSILON = 1e-016, iterations =   17 sum = 1.74253334259240570000, real precision = 2.2204460493e-016
EPSILON = 1e-017, iterations =   17 sum = 1.74253334259240570000, real precision = 2.2204460493e-016
EPSILON = 1e-018, iterations =   18 sum = 1.74253334259240570000, real precision = 2.2204460493e-016


x = -0.80000, 0.539537^(-0.80000) = 1.63826139269546030000

EPSILON = 1e-001, iterations =    4 sum = 1.63552144379160770000, real precision = 2.7399489039e-003
EPSILON = 1e-002, iterations =    5 sum = 1.63799552803611090000, real precision = 2.6586465935e-004
EPSILON = 1e-003, iterations =    6 sum = 1.63823978722500100000, real precision = 2.1605470459e-005
EPSILON = 1e-004, iterations =    7 sum = 1.63825988306163550000, real precision = 1.5096338248e-006
EPSILON = 1e-005, iterations =    8 sum = 1.63826130020726860000, real precision = 9.2488191772e-008
EPSILON = 1e-006, iterations =    9 sum = 1.63826138765145200000, real precision = 5.0440083221e-009
EPSILON = 1e-007, iterations =    9 sum = 1.63826138765145200000, real precision = 5.0440083221e-009
EPSILON = 1e-008, iterations =   10 sum = 1.63826139244762500000, real precision = 2.4783530783e-010
EPSILON = 1e-009, iterations =   11 sum = 1.63826139268438120000, real precision = 1.1079137607e-011
EPSILON = 1e-010, iterations =   12 sum = 1.63826139269500580000, real precision = 4.5452530628e-013
EPSILON = 1e-011, iterations =   13 sum = 1.63826139269544280000, real precision = 1.7541523789e-014
EPSILON = 1e-012, iterations =   13 sum = 1.63826139269544280000, real precision = 1.7541523789e-014
EPSILON = 1e-013, iterations =   14 sum = 1.63826139269545950000, real precision = 8.8817841970e-016
EPSILON = 1e-014, iterations =   15 sum = 1.63826139269546010000, real precision = 2.2204460493e-016
EPSILON = 1e-015, iterations =   15 sum = 1.63826139269546010000, real precision = 2.2204460493e-016
EPSILON = 1e-016, iterations =   16 sum = 1.63826139269546010000, real precision = 2.2204460493e-016
EPSILON = 1e-017, iterations =   17 sum = 1.63826139269546010000, real precision = 2.2204460493e-016
EPSILON = 1e-018, iterations =   17 sum = 1.63826139269546010000, real precision = 2.2204460493e-016


x = -0.70000, 0.539537^(-0.70000) = 1.54022900176106310000

EPSILON = 1e-001, iterations =    3 sum = 1.52521334876081640000, real precision = 1.5015653000e-002
EPSILON = 1e-002, iterations =    5 sum = 1.54009411206419420000, real precision = 1.3488969687e-004
EPSILON = 1e-003, iterations =    6 sum = 1.54021939478309840000, real precision = 9.6069779647e-006
EPSILON = 1e-004, iterations =    7 sum = 1.54022841370035950000, real precision = 5.8806070369e-007
EPSILON = 1e-005, iterations =    7 sum = 1.54022841370035950000, real precision = 5.8806070369e-007
EPSILON = 1e-006, iterations =    8 sum = 1.54022897020763440000, real precision = 3.1553428759e-008
EPSILON = 1e-007, iterations =    9 sum = 1.54022900025423490000, real precision = 1.5068282178e-009
EPSILON = 1e-008, iterations =   10 sum = 1.54022900169624170000, real precision = 6.4821481516e-011
EPSILON = 1e-009, iterations =   11 sum = 1.54022900175852650000, real precision = 2.5366375667e-012
EPSILON = 1e-010, iterations =   11 sum = 1.54022900175852650000, real precision = 2.5366375667e-012
EPSILON = 1e-011, iterations =   12 sum = 1.54022900176097210000, real precision = 9.1038288019e-014
EPSILON = 1e-012, iterations =   13 sum = 1.54022900176106000000, real precision = 3.1086244690e-015
EPSILON = 1e-013, iterations =   13 sum = 1.54022900176106000000, real precision = 3.1086244690e-015
EPSILON = 1e-014, iterations =   14 sum = 1.54022900176106290000, real precision = 2.2204460493e-016
EPSILON = 1e-015, iterations =   15 sum = 1.54022900176106290000, real precision = 2.2204460493e-016
EPSILON = 1e-016, iterations =   15 sum = 1.54022900176106290000, real precision = 2.2204460493e-016
EPSILON = 1e-017, iterations =   16 sum = 1.54022900176106290000, real precision = 2.2204460493e-016
EPSILON = 1e-018, iterations =   17 sum = 1.54022900176106290000, real precision = 2.2204460493e-016


x = -0.60000, 0.539537^(-0.60000) = 1.44806279904007560000

EPSILON = 1e-001, iterations =    3 sum = 1.43876055334844640000, real precision = 9.3022456916e-003
EPSILON = 1e-002, iterations =    4 sum = 1.44721824457149410000, real precision = 8.4455446858e-004
EPSILON = 1e-003, iterations =    5 sum = 1.44800106027003990000, real precision = 6.1738770036e-005
EPSILON = 1e-004, iterations =    6 sum = 1.44805902411872900000, real precision = 3.7749213466e-006
EPSILON = 1e-005, iterations =    7 sum = 1.44806260074577020000, real precision = 1.9829430542e-007
EPSILON = 1e-006, iterations =    8 sum = 1.44806278991186920000, real precision = 9.1282064130e-009
EPSILON = 1e-007, iterations =    9 sum = 1.44806279866616090000, real precision = 3.7391467700e-010
EPSILON = 1e-008, iterations =    9 sum = 1.44806279866616090000, real precision = 3.7391467700e-010
EPSILON = 1e-009, iterations =   10 sum = 1.44806279902628000000, real precision = 1.3795631304e-011
EPSILON = 1e-010, iterations =   11 sum = 1.44806279903961270000, real precision = 4.6296300127e-013
EPSILON = 1e-011, iterations =   12 sum = 1.44806279904006140000, real precision = 1.4210854715e-014
EPSILON = 1e-012, iterations =   12 sum = 1.44806279904006140000, real precision = 1.4210854715e-014
EPSILON = 1e-013, iterations =   13 sum = 1.44806279904007520000, real precision = 4.4408920985e-016
EPSILON = 1e-014, iterations =   14 sum = 1.44806279904007560000, real precision = 0.0000000000e+000
EPSILON = 1e-015, iterations =   14 sum = 1.44806279904007560000, real precision = 0.0000000000e+000
EPSILON = 1e-016, iterations =   15 sum = 1.44806279904007560000, real precision = 0.0000000000e+000
EPSILON = 1e-017, iterations =   16 sum = 1.44806279904007560000, real precision = 0.0000000000e+000
EPSILON = 1e-018, iterations =   16 sum = 1.44806279904007560000, real precision = 0.0000000000e+000


x = -0.50000, 0.539537^(-0.50000) = 1.36141175602215410000

EPSILON = 1e-001, iterations =    3 sum = 1.35611519650422400000, real precision = 5.2965595179e-003
EPSILON = 1e-002, iterations =    4 sum = 1.36100969366685030000, real precision = 4.0206235530e-004
EPSILON = 1e-003, iterations =    5 sum = 1.36138720894607150000, real precision = 2.4547076083e-005
EPSILON = 1e-004, iterations =    6 sum = 1.36141050331626890000, real precision = 1.2527058852e-006
EPSILON = 1e-005, iterations =    7 sum = 1.36141170112139260000, real precision = 5.4900761493e-008
EPSILON = 1e-006, iterations =    8 sum = 1.36141175391417720000, real precision = 2.1079769041e-009
EPSILON = 1e-007, iterations =    8 sum = 1.36141175391417720000, real precision = 2.1079769041e-009
EPSILON = 1e-008, iterations =    9 sum = 1.36141175595014550000, real precision = 7.2008621288e-011
EPSILON = 1e-009, iterations =   10 sum = 1.36141175601993900000, real precision = 2.2151169787e-012
EPSILON = 1e-010, iterations =   10 sum = 1.36141175601993900000, real precision = 2.2151169787e-012
EPSILON = 1e-011, iterations =   11 sum = 1.36141175602209240000, real precision = 6.1728400169e-014
EPSILON = 1e-012, iterations =   12 sum = 1.36141175602215280000, real precision = 1.3322676296e-015
EPSILON = 1e-013, iterations =   12 sum = 1.36141175602215280000, real precision = 1.3322676296e-015
EPSILON = 1e-014, iterations =   13 sum = 1.36141175602215440000, real precision = 2.2204460493e-016
EPSILON = 1e-015, iterations =   14 sum = 1.36141175602215440000, real precision = 2.2204460493e-016
EPSILON = 1e-016, iterations =   14 sum = 1.36141175602215440000, real precision = 2.2204460493e-016
EPSILON = 1e-017, iterations =   15 sum = 1.36141175602215440000, real precision = 2.2204460493e-016
EPSILON = 1e-018, iterations =   15 sum = 1.36141175602215440000, real precision = 2.2204460493e-016


x = -0.40000, 0.539537^(-0.40000) = 1.27994584949214670000

EPSILON = 1e-001, iterations =    3 sum = 1.27727727822814870000, real precision = 2.6685712640e-003
EPSILON = 1e-002, iterations =    4 sum = 1.27978326071940040000, real precision = 1.6258877275e-004
EPSILON = 1e-003, iterations =    5 sum = 1.27993789097316090000, real precision = 7.9585189858e-006
EPSILON = 1e-004, iterations =    6 sum = 1.27994552407210290000, real precision = 3.2542004380e-007
EPSILON = 1e-005, iterations =    6 sum = 1.27994552407210290000, real precision = 3.2542004380e-007
EPSILON = 1e-006, iterations =    7 sum = 1.27994583806951520000, real precision = 1.1422631507e-008
EPSILON = 1e-007, iterations =    8 sum = 1.27994584914096410000, real precision = 3.5118263852e-010
EPSILON = 1e-008, iterations =    9 sum = 1.27994584948254290000, real precision = 9.6038732522e-012
EPSILON = 1e-009, iterations =    9 sum = 1.27994584948254290000, real precision = 9.6038732522e-012
EPSILON = 1e-010, iterations =   10 sum = 1.27994584949191050000, real precision = 2.3625545964e-013
EPSILON = 1e-011, iterations =   10 sum = 1.27994584949191050000, real precision = 2.3625545964e-013
EPSILON = 1e-012, iterations =   11 sum = 1.27994584949214160000, real precision = 5.1070259133e-015
EPSILON = 1e-013, iterations =   12 sum = 1.27994584949214670000, real precision = 0.0000000000e+000
EPSILON = 1e-014, iterations =   12 sum = 1.27994584949214670000, real precision = 0.0000000000e+000
EPSILON = 1e-015, iterations =   13 sum = 1.27994584949214670000, real precision = 0.0000000000e+000
EPSILON = 1e-016, iterations =   14 sum = 1.27994584949214670000, real precision = 0.0000000000e+000
EPSILON = 1e-017, iterations =   14 sum = 1.27994584949214670000, real precision = 0.0000000000e+000
EPSILON = 1e-018, iterations =   15 sum = 1.27994584949214670000, real precision = 0.0000000000e+000


x = -0.30000, 0.539537^(-0.30000) = 1.20335480458824100000

EPSILON = 1e-001, iterations =    3 sum = 1.20224679852022100000, real precision = 1.1080060680e-003
EPSILON = 1e-002, iterations =    4 sum = 1.20330400984433350000, real precision = 5.0794743907e-005
EPSILON = 1e-003, iterations =    5 sum = 1.20335293582063230000, real precision = 1.8687676087e-006
EPSILON = 1e-004, iterations =    5 sum = 1.20335293582063230000, real precision = 1.8687676087e-006
EPSILON = 1e-005, iterations =    6 sum = 1.20335474719067890000, real precision = 5.7397562037e-008
EPSILON = 1e-006, iterations =    7 sum = 1.20335480307546820000, real precision = 1.5127727959e-009
EPSILON = 1e-007, iterations =    7 sum = 1.20335480307546820000, real precision = 1.5127727959e-009
EPSILON = 1e-008, iterations =    8 sum = 1.20335480455332800000, real precision = 3.4912961411e-011
EPSILON = 1e-009, iterations =    9 sum = 1.20335480458752440000, real precision = 7.1653794009e-013
EPSILON = 1e-010, iterations =    9 sum = 1.20335480458752440000, real precision = 7.1653794009e-013
EPSILON = 1e-011, iterations =   10 sum = 1.20335480458822790000, real precision = 1.3100631691e-014
EPSILON = 1e-012, iterations =   10 sum = 1.20335480458822790000, real precision = 1.3100631691e-014
EPSILON = 1e-013, iterations =   11 sum = 1.20335480458824100000, real precision = 0.0000000000e+000
EPSILON = 1e-014, iterations =   12 sum = 1.20335480458824120000, real precision = 2.2204460493e-016
EPSILON = 1e-015, iterations =   12 sum = 1.20335480458824120000, real precision = 2.2204460493e-016
EPSILON = 1e-016, iterations =   13 sum = 1.20335480458824120000, real precision = 2.2204460493e-016
EPSILON = 1e-017, iterations =   13 sum = 1.20335480458824120000, real precision = 2.2204460493e-016
EPSILON = 1e-018, iterations =   14 sum = 1.20335480458824120000, real precision = 2.2204460493e-016


x = -0.20000, 0.539537^(-0.20000) = 1.13134691307461300000

EPSILON = 1e-001, iterations =    3 sum = 1.13102375738044050000, real precision = 3.2315569417e-004
EPSILON = 1e-002, iterations =    3 sum = 1.13102375738044050000, real precision = 3.2315569417e-004
EPSILON = 1e-003, iterations =    4 sum = 1.13133700515683880000, real precision = 9.9079177742e-006
EPSILON = 1e-004, iterations =    5 sum = 1.13134666954625860000, real precision = 2.4352835437e-007
EPSILON = 1e-005, iterations =    5 sum = 1.13134666954625860000, real precision = 2.4352835437e-007
EPSILON = 1e-006, iterations =    6 sum = 1.13134690808055600000, real precision = 4.9940569458e-009
EPSILON = 1e-007, iterations =    7 sum = 1.13134691298676460000, real precision = 8.7848395225e-011
EPSILON = 1e-008, iterations =    7 sum = 1.13134691298676460000, real precision = 8.7848395225e-011
EPSILON = 1e-009, iterations =    8 sum = 1.13134691307326030000, real precision = 1.3526957332e-012
EPSILON = 1e-010, iterations =    8 sum = 1.13134691307326030000, real precision = 1.3526957332e-012
EPSILON = 1e-011, iterations =    9 sum = 1.13134691307459460000, real precision = 1.8429702209e-014
EPSILON = 1e-012, iterations =   10 sum = 1.13134691307461280000, real precision = 2.2204460493e-016
EPSILON = 1e-013, iterations =   10 sum = 1.13134691307461280000, real precision = 2.2204460493e-016
EPSILON = 1e-014, iterations =   11 sum = 1.13134691307461300000, real precision = 0.0000000000e+000
EPSILON = 1e-015, iterations =   11 sum = 1.13134691307461300000, real precision = 0.0000000000e+000
EPSILON = 1e-016, iterations =   12 sum = 1.13134691307461300000, real precision = 0.0000000000e+000
EPSILON = 1e-017, iterations =   12 sum = 1.13134691307461300000, real precision = 0.0000000000e+000
EPSILON = 1e-018, iterations =   13 sum = 1.13134691307461300000, real precision = 0.0000000000e+000


x = -0.10000, 0.539537^(-0.10000) = 1.06364792232779810000

EPSILON = 1e-001, iterations =    2 sum = 1.06170443609208600000, real precision = 1.9434862357e-003
EPSILON = 1e-002, iterations =    3 sum = 1.06360815480880720000, real precision = 3.9767518991e-005
EPSILON = 1e-003, iterations =    4 sum = 1.06364731077210490000, real precision = 6.1155569320e-007
EPSILON = 1e-004, iterations =    4 sum = 1.06364731077210490000, real precision = 6.1155569320e-007
EPSILON = 1e-005, iterations =    5 sum = 1.06364791479626360000, real precision = 7.5315345072e-009
EPSILON = 1e-006, iterations =    5 sum = 1.06364791479626360000, real precision = 7.5315345072e-009
EPSILON = 1e-007, iterations =    6 sum = 1.06364792225045760000, real precision = 7.7340578386e-011
EPSILON = 1e-008, iterations =    6 sum = 1.06364792225045760000, real precision = 7.7340578386e-011
EPSILON = 1e-009, iterations =    7 sum = 1.06364792232711710000, real precision = 6.8101080331e-013
EPSILON = 1e-010, iterations =    7 sum = 1.06364792232711710000, real precision = 6.8101080331e-013
EPSILON = 1e-011, iterations =    8 sum = 1.06364792232779280000, real precision = 5.3290705182e-015
EPSILON = 1e-012, iterations =    8 sum = 1.06364792232779280000, real precision = 5.3290705182e-015
EPSILON = 1e-013, iterations =    9 sum = 1.06364792232779790000, real precision = 2.2204460493e-016
EPSILON = 1e-014, iterations =    9 sum = 1.06364792232779790000, real precision = 2.2204460493e-016
EPSILON = 1e-015, iterations =   10 sum = 1.06364792232779790000, real precision = 2.2204460493e-016
EPSILON = 1e-016, iterations =   10 sum = 1.06364792232779790000, real precision = 2.2204460493e-016
EPSILON = 1e-017, iterations =   11 sum = 1.06364792232779790000, real precision = 2.2204460493e-016
EPSILON = 1e-018, iterations =   11 sum = 1.06364792232779790000, real precision = 2.2204460493e-016


x = 0.00000, 0.539537^(0.00000) = 0.99999999080532131000

EPSILON = 1e-001, iterations =    2 sum = 0.99999999080532131000, real precision = 0.0000000000e+000
EPSILON = 1e-002, iterations =    2 sum = 0.99999999080532131000, real precision = 0.0000000000e+000
EPSILON = 1e-003, iterations =    2 sum = 0.99999999080532131000, real precision = 0.0000000000e+000
EPSILON = 1e-004, iterations =    2 sum = 0.99999999080532131000, real precision = 0.0000000000e+000
EPSILON = 1e-005, iterations =    2 sum = 0.99999999080532131000, real precision = 0.0000000000e+000
EPSILON = 1e-006, iterations =    2 sum = 0.99999999080532131000, real precision = 0.0000000000e+000
EPSILON = 1e-007, iterations =    2 sum = 0.99999999080532131000, real precision = 0.0000000000e+000
EPSILON = 1e-008, iterations =    2 sum = 0.99999999080532131000, real precision = 0.0000000000e+000
EPSILON = 1e-009, iterations =    3 sum = 0.99999999080532131000, real precision = 0.0000000000e+000
EPSILON = 1e-010, iterations =    3 sum = 0.99999999080532131000, real precision = 0.0000000000e+000
EPSILON = 1e-011, iterations =    3 sum = 0.99999999080532131000, real precision = 0.0000000000e+000
EPSILON = 1e-012, iterations =    3 sum = 0.99999999080532131000, real precision = 0.0000000000e+000
EPSILON = 1e-013, iterations =    3 sum = 0.99999999080532131000, real precision = 0.0000000000e+000
EPSILON = 1e-014, iterations =    3 sum = 0.99999999080532131000, real precision = 0.0000000000e+000
EPSILON = 1e-015, iterations =    3 sum = 0.99999999080532131000, real precision = 0.0000000000e+000
EPSILON = 1e-016, iterations =    3 sum = 0.99999999080532131000, real precision = 0.0000000000e+000
EPSILON = 1e-017, iterations =    4 sum = 0.99999999080532131000, real precision = 0.0000000000e+000
EPSILON = 1e-018, iterations =    4 sum = 0.99999999080532131000, real precision = 0.0000000000e+000


x = 0.10000, 0.539537^(0.10000) = 0.94016070601833956000

EPSILON = 1e-001, iterations =    2 sum = 0.93829554551855654000, real precision = 1.8651604998e-003
EPSILON = 1e-002, iterations =    3 sum = 0.94019926536998277000, real precision = 3.8559351643e-005
EPSILON = 1e-003, iterations =    4 sum = 0.94016010937167682000, real precision = 5.9664666274e-007
EPSILON = 1e-004, iterations =    4 sum = 0.94016010937167682000, real precision = 5.9664666274e-007
EPSILON = 1e-005, iterations =    5 sum = 0.94016071339655560000, real precision = 7.3782160381e-009
EPSILON = 1e-006, iterations =    5 sum = 0.94016071339655560000, real precision = 7.3782160381e-009
EPSILON = 1e-007, iterations =    6 sum = 0.94016070594235046000, real precision = 7.5989103898e-011
EPSILON = 1e-008, iterations =    6 sum = 0.94016070594235046000, real precision = 7.5989103898e-011
EPSILON = 1e-009, iterations =    7 sum = 0.94016070601901003000, real precision = 6.7046368457e-013
EPSILON = 1e-010, iterations =    7 sum = 0.94016070601901003000, real precision = 6.7046368457e-013
EPSILON = 1e-011, iterations =    8 sum = 0.94016070601833424000, real precision = 5.3290705182e-015
EPSILON = 1e-012, iterations =    8 sum = 0.94016070601833424000, real precision = 5.3290705182e-015
EPSILON = 1e-013, iterations =    9 sum = 0.94016070601833945000, real precision = 1.1102230246e-016
EPSILON = 1e-014, iterations =    9 sum = 0.94016070601833945000, real precision = 1.1102230246e-016
EPSILON = 1e-015, iterations =   10 sum = 0.94016070601833945000, real precision = 1.1102230246e-016
EPSILON = 1e-016, iterations =   10 sum = 0.94016070601833945000, real precision = 1.1102230246e-016
EPSILON = 1e-017, iterations =   11 sum = 0.94016070601833945000, real precision = 1.1102230246e-016
EPSILON = 1e-018, iterations =   11 sum = 0.94016070601833945000, real precision = 1.1102230246e-016


x = 0.20000, 0.539537^(0.20000) = 0.88390216126809917000

EPSILON = 1e-001, iterations =    3 sum = 0.88420597850279170000, real precision = 3.0381723469e-004
EPSILON = 1e-002, iterations =    3 sum = 0.88420597850279170000, real precision = 3.0381723469e-004
EPSILON = 1e-003, iterations =    4 sum = 0.88389273058636075000, real precision = 9.4306817384e-006
EPSILON = 1e-004, iterations =    5 sum = 0.88390239498154111000, real precision = 2.3371344193e-007
EPSILON = 1e-005, iterations =    5 sum = 0.88390239498154111000, real precision = 2.3371344193e-007
EPSILON = 1e-006, iterations =    6 sum = 0.88390215644706593000, real precision = 4.8210332393e-009
EPSILON = 1e-007, iterations =    7 sum = 0.88390216135327881000, real precision = 8.5179641118e-011
EPSILON = 1e-008, iterations =    7 sum = 0.88390216135327881000, real precision = 8.5179641118e-011
EPSILON = 1e-009, iterations =    8 sum = 0.88390216126678300000, real precision = 1.3161693957e-012
EPSILON = 1e-010, iterations =    8 sum = 0.88390216126678300000, real precision = 1.3161693957e-012
EPSILON = 1e-011, iterations =    9 sum = 0.88390216126811727000, real precision = 1.8096635301e-014
EPSILON = 1e-012, iterations =   10 sum = 0.88390216126809895000, real precision = 2.2204460493e-016
EPSILON = 1e-013, iterations =   10 sum = 0.88390216126809895000, real precision = 2.2204460493e-016
EPSILON = 1e-014, iterations =   11 sum = 0.88390216126809917000, real precision = 0.0000000000e+000
EPSILON = 1e-015, iterations =   11 sum = 0.88390216126809917000, real precision = 0.0000000000e+000
EPSILON = 1e-016, iterations =   12 sum = 0.88390216126809917000, real precision = 0.0000000000e+000
EPSILON = 1e-017, iterations =   12 sum = 0.88390216126809917000, real precision = 0.0000000000e+000
EPSILON = 1e-018, iterations =   13 sum = 0.88390216126809917000, real precision = 0.0000000000e+000


x = 0.30000, 0.539537^(0.30000) = 0.83101008762982309000

EPSILON = 1e-001, iterations =    3 sum = 0.83202013020374788000, real precision = 1.0100425739e-003
EPSILON = 1e-002, iterations =    4 sum = 0.83096291856456173000, real precision = 4.7169065261e-005
EPSILON = 1e-003, iterations =    5 sum = 0.83101184456030197000, real precision = 1.7569304789e-006
EPSILON = 1e-004, iterations =    5 sum = 0.83101184456030197000, real precision = 1.7569304789e-006
EPSILON = 1e-005, iterations =    6 sum = 0.83101003318935562000, real precision = 5.4440467467e-008
EPSILON = 1e-006, iterations =    7 sum = 0.83101008907417817000, real precision = 1.4443550800e-009
EPSILON = 1e-007, iterations =    7 sum = 0.83101008907417817000, real precision = 1.4443550800e-009
EPSILON = 1e-008, iterations =    8 sum = 0.83101008759631723000, real precision = 3.3505864749e-011
EPSILON = 1e-009, iterations =    9 sum = 0.83101008763051365000, real precision = 6.9055872132e-013
EPSILON = 1e-010, iterations =    9 sum = 0.83101008763051365000, real precision = 6.9055872132e-013
EPSILON = 1e-011, iterations =   10 sum = 0.83101008762981032000, real precision = 1.2767564783e-014
EPSILON = 1e-012, iterations =   10 sum = 0.83101008762981032000, real precision = 1.2767564783e-014
EPSILON = 1e-013, iterations =   11 sum = 0.83101008762982331000, real precision = 2.2204460493e-016
EPSILON = 1e-014, iterations =   12 sum = 0.83101008762982309000, real precision = 0.0000000000e+000
EPSILON = 1e-015, iterations =   12 sum = 0.83101008762982309000, real precision = 0.0000000000e+000
EPSILON = 1e-016, iterations =   13 sum = 0.83101008762982309000, real precision = 0.0000000000e+000
EPSILON = 1e-017, iterations =   13 sum = 0.83101008762982309000, real precision = 0.0000000000e+000
EPSILON = 1e-018, iterations =   14 sum = 0.83101008762982309000, real precision = 0.0000000000e+000


x = 0.40000, 0.539537^(0.40000) = 0.78128303787806319000

EPSILON = 1e-001, iterations =    3 sum = 0.78364172047285130000, real precision = 2.3586825948e-003
EPSILON = 1e-002, iterations =    4 sum = 0.78113573742146891000, real precision = 1.4730045659e-004
EPSILON = 1e-003, iterations =    5 sum = 0.78129036772131288000, real precision = 7.3298432497e-006
EPSILON = 1e-004, iterations =    6 sum = 0.78128273461952746000, real precision = 3.0325853573e-007
EPSILON = 1e-005, iterations =    6 sum = 0.78128273461952746000, real precision = 3.0325853573e-007
EPSILON = 1e-006, iterations =    7 sum = 0.78128304861708020000, real precision = 1.0739017009e-008
EPSILON = 1e-007, iterations =    8 sum = 0.78128303754562556000, real precision = 3.3243763298e-010
EPSILON = 1e-008, iterations =    9 sum = 0.78128303788720455000, real precision = 9.1413543402e-012
EPSILON = 1e-009, iterations =    9 sum = 0.78128303788720455000, real precision = 9.1413543402e-012
EPSILON = 1e-010, iterations =   10 sum = 0.78128303787783704000, real precision = 2.2615243012e-013
EPSILON = 1e-011, iterations =   10 sum = 0.78128303787783704000, real precision = 2.2615243012e-013
EPSILON = 1e-012, iterations =   11 sum = 0.78128303787806830000, real precision = 5.1070259133e-015
EPSILON = 1e-013, iterations =   12 sum = 0.78128303787806308000, real precision = 1.1102230246e-016
EPSILON = 1e-014, iterations =   12 sum = 0.78128303787806308000, real precision = 1.1102230246e-016
EPSILON = 1e-015, iterations =   13 sum = 0.78128303787806319000, real precision = 0.0000000000e+000
EPSILON = 1e-016, iterations =   14 sum = 0.78128303787806319000, real precision = 0.0000000000e+000
EPSILON = 1e-017, iterations =   14 sum = 0.78128303787806319000, real precision = 0.0000000000e+000
EPSILON = 1e-018, iterations =   15 sum = 0.78128303787806319000, real precision = 0.0000000000e+000


x = 0.50000, 0.539537^(0.50000) = 0.73453161924537524000

EPSILON = 1e-001, iterations =    3 sum = 0.73907074931010219000, real precision = 4.5391300647e-003
EPSILON = 1e-002, iterations =    4 sum = 0.73417625127227160000, real precision = 3.5536797310e-004
EPSILON = 1e-003, iterations =    5 sum = 0.73455376664149929000, real precision = 2.2147396124e-005
EPSILON = 1e-004, iterations =    6 sum = 0.73453047226435964000, real precision = 1.1469810156e-006
EPSILON = 1e-005, iterations =    7 sum = 0.73453167006991171000, real precision = 5.0824536468e-008
EPSILON = 1e-006, iterations =    8 sum = 0.73453161727710503000, real precision = 1.9682702135e-009
EPSILON = 1e-007, iterations =    8 sum = 0.73453161727710503000, real precision = 1.9682702135e-009
EPSILON = 1e-008, iterations =    9 sum = 0.73453161931307442000, real precision = 6.7699179596e-011
EPSILON = 1e-009, iterations =   10 sum = 0.73453161924328092000, real precision = 2.0943247137e-012
EPSILON = 1e-010, iterations =   10 sum = 0.73453161924328092000, real precision = 2.0943247137e-012
EPSILON = 1e-011, iterations =   11 sum = 0.73453161924543420000, real precision = 5.8952842608e-014
EPSILON = 1e-012, iterations =   12 sum = 0.73453161924537380000, real precision = 1.4432899320e-015
EPSILON = 1e-013, iterations =   12 sum = 0.73453161924537380000, real precision = 1.4432899320e-015
EPSILON = 1e-014, iterations =   13 sum = 0.73453161924537536000, real precision = 1.1102230246e-016
EPSILON = 1e-015, iterations =   14 sum = 0.73453161924537536000, real precision = 1.1102230246e-016
EPSILON = 1e-016, iterations =   14 sum = 0.73453161924537536000, real precision = 1.1102230246e-016
EPSILON = 1e-017, iterations =   15 sum = 0.73453161924537536000, real precision = 1.1102230246e-016
EPSILON = 1e-018, iterations =   15 sum = 0.73453161924537536000, real precision = 1.1102230246e-016


x = 0.60000, 0.539537^(0.60000) = 0.69057777209216697000

EPSILON = 1e-001, iterations =    3 sum = 0.69830721671550045000, real precision = 7.7294446233e-003
EPSILON = 1e-002, iterations =    4 sum = 0.68984952423215851000, real precision = 7.2824786001e-004
EPSILON = 1e-003, iterations =    5 sum = 0.69063234008623597000, real precision = 5.4567994069e-005
EPSILON = 1e-004, iterations =    6 sum = 0.69057437622315143000, real precision = 3.3958690155e-006
EPSILON = 1e-005, iterations =    7 sum = 0.69057795285125856000, real precision = 1.8075909158e-007
EPSILON = 1e-006, iterations =    8 sum = 0.69057776368509383000, real precision = 8.4070731488e-009
EPSILON = 1e-007, iterations =    9 sum = 0.69057777243938900000, real precision = 3.4722202891e-010
EPSILON = 1e-008, iterations =    9 sum = 0.69057777243938900000, real precision = 3.4722202891e-010
EPSILON = 1e-009, iterations =   10 sum = 0.69057777207926974000, real precision = 1.2897238832e-011
EPSILON = 1e-010, iterations =   11 sum = 0.69057777209260229000, real precision = 4.3531844796e-013
EPSILON = 1e-011, iterations =   12 sum = 0.69057777209215354000, real precision = 1.3433698598e-014
EPSILON = 1e-012, iterations =   12 sum = 0.69057777209215354000, real precision = 1.3433698598e-014
EPSILON = 1e-013, iterations =   13 sum = 0.69057777209216742000, real precision = 4.4408920985e-016
EPSILON = 1e-014, iterations =   14 sum = 0.69057777209216697000, real precision = 0.0000000000e+000
EPSILON = 1e-015, iterations =   14 sum = 0.69057777209216697000, real precision = 0.0000000000e+000
EPSILON = 1e-016, iterations =   15 sum = 0.69057777209216697000, real precision = 0.0000000000e+000
EPSILON = 1e-017, iterations =   16 sum = 0.69057777209216697000, real precision = 0.0000000000e+000
EPSILON = 1e-018, iterations =   16 sum = 0.69057777209216697000, real precision = 0.0000000000e+000


x = 0.70000, 0.539537^(0.70000) = 0.64925409174042648000

EPSILON = 1e-001, iterations =    3 sum = 0.66135112268904594000, real precision = 1.2097030949e-002
EPSILON = 1e-002, iterations =    5 sum = 0.64937088340934834000, real precision = 1.1679166892e-004
EPSILON = 1e-003, iterations =    6 sum = 0.64924560066377468000, real precision = 8.4910766518e-006
EPSILON = 1e-004, iterations =    7 sum = 0.64925461958333952000, real precision = 5.2784291305e-007
EPSILON = 1e-005, iterations =    7 sum = 0.64925461958333952000, real precision = 5.2784291305e-007
EPSILON = 1e-006, iterations =    8 sum = 0.64925406307589884000, real precision = 2.8664527640e-008
EPSILON = 1e-007, iterations =    9 sum = 0.64925409312250948000, real precision = 1.3820830036e-009
EPSILON = 1e-008, iterations =   10 sum = 0.64925409168050208000, real precision = 5.9924398776e-011
EPSILON = 1e-009, iterations =   11 sum = 0.64925409174278681000, real precision = 2.3603341504e-012
EPSILON = 1e-010, iterations =   11 sum = 0.64925409174278681000, real precision = 2.3603341504e-012
EPSILON = 1e-011, iterations =   12 sum = 0.64925409174034110000, real precision = 8.5376150594e-014
EPSILON = 1e-012, iterations =   13 sum = 0.64925409174042914000, real precision = 2.6645352591e-015
EPSILON = 1e-013, iterations =   13 sum = 0.64925409174042914000, real precision = 2.6645352591e-015
EPSILON = 1e-014, iterations =   14 sum = 0.64925409174042625000, real precision = 2.2204460493e-016
EPSILON = 1e-015, iterations =   15 sum = 0.64925409174042636000, real precision = 1.1102230246e-016
EPSILON = 1e-016, iterations =   15 sum = 0.64925409174042636000, real precision = 1.1102230246e-016
EPSILON = 1e-017, iterations =   16 sum = 0.64925409174042636000, real precision = 1.1102230246e-016
EPSILON = 1e-018, iterations =   17 sum = 0.64925409174042636000, real precision = 1.1102230246e-016


x = 0.80000, 0.539537^(0.80000) = 0.61040319088843642000

EPSILON = 1e-001, iterations =    4 sum = 0.60815460393994147000, real precision = 2.2485869485e-003
EPSILON = 1e-002, iterations =    5 sum = 0.61062868855311192000, real precision = 2.2549766468e-004
EPSILON = 1e-003, iterations =    6 sum = 0.61038442931872516000, real precision = 1.8761569711e-005
EPSILON = 1e-004, iterations =    7 sum = 0.61040452515985144000, real precision = 1.3342714150e-006
EPSILON = 1e-005, iterations =    8 sum = 0.61040310801384878000, real precision = 8.2874587637e-008
EPSILON = 1e-006, iterations =    9 sum = 0.61040319545805843000, real precision = 4.5696220141e-009
EPSILON = 1e-007, iterations =    9 sum = 0.61040319545805843000, real precision = 4.5696220141e-009
EPSILON = 1e-008, iterations =   10 sum = 0.61040319066188375000, real precision = 2.2655266552e-010
EPSILON = 1e-009, iterations =   11 sum = 0.61040319089864004000, real precision = 1.0203615730e-011
EPSILON = 1e-010, iterations =   12 sum = 0.61040319088801542000, real precision = 4.2099657094e-013
EPSILON = 1e-011, iterations =   13 sum = 0.61040319088845252000, real precision = 1.6098233857e-014
EPSILON = 1e-012, iterations =   13 sum = 0.61040319088845252000, real precision = 1.6098233857e-014
EPSILON = 1e-013, iterations =   14 sum = 0.61040319088843598000, real precision = 4.4408920985e-016
EPSILON = 1e-014, iterations =   15 sum = 0.61040319088843653000, real precision = 1.1102230246e-016
EPSILON = 1e-015, iterations =   15 sum = 0.61040319088843653000, real precision = 1.1102230246e-016
EPSILON = 1e-016, iterations =   16 sum = 0.61040319088843653000, real precision = 1.1102230246e-016
EPSILON = 1e-017, iterations =   17 sum = 0.61040319088843653000, real precision = 1.1102230246e-016
EPSILON = 1e-018, iterations =   17 sum = 0.61040319088843653000, real precision = 1.1102230246e-016


x = 0.90000, 0.539537^(0.90000) = 0.57387710017813520000

EPSILON = 1e-001, iterations =    4 sum = 0.57031653891821577000, real precision = 3.5605612599e-003
EPSILON = 1e-002, iterations =    5 sum = 0.57427954404825299000, real precision = 4.0244387012e-004
EPSILON = 1e-003, iterations =    6 sum = 0.57383938098117371000, real precision = 3.7719196961e-005
EPSILON = 1e-004, iterations =    7 sum = 0.57388012100868302000, real precision = 3.0208305478e-006
EPSILON = 1e-005, iterations =    8 sum = 0.57387688892760291000, real precision = 2.1125053229e-007
EPSILON = 1e-006, iterations =    9 sum = 0.57387711329059810000, real precision = 1.3112462893e-008
EPSILON = 1e-007, iterations =   10 sum = 0.57387709944640375000, real precision = 7.3173145321e-010
EPSILON = 1e-008, iterations =   11 sum = 0.57387710021522731000, real precision = 3.7092107164e-011
EPSILON = 1e-009, iterations =   11 sum = 0.57387710021522731000, real precision = 3.7092107164e-011
EPSILON = 1e-010, iterations =   12 sum = 0.57387710017641291000, real precision = 1.7222889781e-012
EPSILON = 1e-011, iterations =   13 sum = 0.57387710017820914000, real precision = 7.3940853440e-014
EPSILON = 1e-012, iterations =   14 sum = 0.57387710017813243000, real precision = 2.7755575616e-015
EPSILON = 1e-013, iterations =   14 sum = 0.57387710017813243000, real precision = 2.7755575616e-015
EPSILON = 1e-014, iterations =   15 sum = 0.57387710017813542000, real precision = 2.2204460493e-016
EPSILON = 1e-015, iterations =   16 sum = 0.57387710017813531000, real precision = 1.1102230246e-016
EPSILON = 1e-016, iterations =   17 sum = 0.57387710017813531000, real precision = 1.1102230246e-016
EPSILON = 1e-017, iterations =   17 sum = 0.57387710017813531000, real precision = 1.1102230246e-016
EPSILON = 1e-018, iterations =   18 sum = 0.57387710017813531000, real precision = 1.1102230246e-016

*/
