#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "RUS");

    double x;              // показание датчика
    double Q;              // индикатор процесса
    double LCL = 8;        // нижняя граница
    double UCL = 22;       // верхняя граница
    double sum = 0;        // сумма всех Q
    double min = 0;        // минимум
    double max = 0;        // максимум
    double avg;            // среднее
    int count = 0;         // сколько ввели
    int bad = 0;           // сколько отклонились >20%
    int i;                 // счётчик цикла
    int n;                 // сколько чисел введём

    printf("Введите количество показаний: ");
    scanf("%d", &n);

    //первый цикл: ввод, Q, контроль
    for (i = 0; i < n; i++) {
        printf("X%d = ", i + 1);
        scanf("%lf", &x);

        // кусочная функция Q(x)
        if (x < 3) {
            Q = 4 * x;             // x < 3
        }
        else if (x < 7) {
            Q = 2 * x + 6;         // 3 <= x < 7
        }
        else {
            Q = x + 13;            // x >= 7
        }

        count = count + 1;
        sum = sum + Q;

        // мин и макс
        if (count == 1) {
            min = Q;
            max = Q;
        }
        else {
            if (Q < min) min = Q;
            if (Q > max) max = Q;
        }

        // контроль границ
        printf("Q = %.3f -> ", Q);
        if (Q < LCL) {
            printf("ПРЕДУПРЕЖДЕНИЕ (ниже LCL)\n");
        }
        else if (Q > UCL) {
            printf("ПРЕДУПРЕЖДЕНИЕ (выше UCL)\n");
        }
        else {
            printf("НОРМА\n");
        }
    }

    avg = sum / count;             // среднее

    // ---- второй цикл: считаем отклонения >20% ----
    printf("\nВведите те же %d чисел ещё раз:\n", n);
    for (i = 0; i < n; i++) {
        printf("X[%d] = ", i + 1);
        scanf("%lf", &x);

        if (x < 3) {
            Q = 4 * x;
        }
        else if (x < 7) {
            Q = 2 * x + 6;
        }
        else {
            Q = x + 13;
        }

        // отклонение от среднего больше 20%
        if (Q > avg * 1.2 || Q < avg * 0.8) {
            bad = bad + 1;
        }
    }

    printf("\n      СТАТИСТИКА      \n");
    printf("Количество : %d\n", count);
    printf("Среднее    : %.3f\n", avg);
    printf("Минимум    : %.3f\n", min);
    printf("Максимум   : %.3f\n", max);
    printf("Отклонение : %d\n", bad);

    return 0;
}
