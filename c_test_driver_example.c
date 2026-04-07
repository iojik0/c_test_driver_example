#include <stdio.h>
#pragma warning(disable : 4996)

int searchIndex(int length, const int array[], int result[]);
void testSearchIndex();

int main()
{
    int length;
    int array[20];
    int result[20];
    int count;
    // ввод размера массива
    printf("input length array [4-20] - ");
    scanf("%d", &length);
    if ((length < 4) || (length > 20)) {
        printf("invalid input");
        return -1;
    }
    printf("----------------------------------------------------------\n");
    // ввод элементов массива
    for (int i = 0; i < length; i++) {
        scanf("%d", &array[i]);
        if ((array[i] < 0) || (array[i] > 1000)) {
            printf("invalid input");
            return -1;
        }
    }
    printf("----------------------------------------------------------\n");
    // вызов функции searchIndex
    count = searchIndex(length, array, result);
    // вывод массива содержащего индексы элементом,
    // сумма соседних элементов которого максимальна
    for (int i = 0; i < count; i++) {
        printf("%d ",result[i]);
    }

    // проверка тестами
    printf("\n---------------------------test---------------------------\n");
    testSearchIndex();
    printf("----------------------------------------------------------\n");
    // выход из программы
    return 0;
}


// функция для поиска индексов которая возвращает их кол-во
int searchIndex(int length, const int array[], int result[]) {
    int sum = 0, maxSum = 0;

    // максимальная сумма соседних элементов
    for (int i = 1; i <= length - 2; i++) {
        sum = array[i - 1] + array[i + 1];
        if (maxSum <= sum) {
            maxSum = sum;
        }
    }
    // поиск всех элементов у которых сумма соседних
    // эл-ов равна максимальной сумме
    int k = 0;
    for (int i = 1; i < length - 1; i++) {
        // записываю индексы в массив
        if (array[i - 1] + array[i + 1] == maxSum) {
            result[k] = i;
            k++;
        }
    }
    return k;
}

// тестовый драйвер
void testSearchIndex() {
    // кол-во тестов
    #define TEST_COUNT 7

    char textNames[TEST_COUNT][50] = {
    "base case",                           // базовый случай
    "several indices with the same sum",   // несколько индексов с одинаковой суммой
    "all amounts are equal",               // все суммы равны
    "maximum amount at the beginning",     // максимальная сумма в начале  
    "maximum amount at the end",           // максимальная сумма в конце
    "identical array elements",            // одинаковые элементы массива
    "edge case"                            // граничный случай
    };

    // входные данные для тестирования
    int testArray[TEST_COUNT][20] = {
        {1,2,3,4,5},
        {10,1,10,1,10},
        {5,0,5,0,5},
        {1,100,1,0,1},
        {1,0,1,100,1},
        {7,7,7,7,7},
        {1,2,3,4}
    };

    int testLength[TEST_COUNT] = { 5,5,5,5,5,5,4 };

    int expResult[TEST_COUNT][20] = {
        {3},
        {1,3},
        {1,3},
        {2},
        {2},
        {1,2,3},
        {2}
    };

    int expCount[TEST_COUNT] = { 1,2,2,1,1,3,1 };

    int realCount[TEST_COUNT];
    int realResult[TEST_COUNT][20];

    int isOk;

    for (int i = 0; i < TEST_COUNT;i++) {
        // вызываем тестируемую функцию
        realCount[i] = searchIndex(testLength[i], testArray[i], realResult[i]);
        // сравниваем ожидаемый и реальный результат
        isOk = 1;
        for (int j = 0; j < expCount[i]; j++) {
            if (expResult[i][j] != realResult[i][j]) {
                isOk = 0;
            }
        }

        // результат теста
        if (isOk && expCount[i] == realCount[i]) {
            printf("\ntest %s passed\n", textNames[i]);

        }
        else {
            printf("\ntest %s failed: exp = { ", textNames[i]);
            for (int j = 0; j < expCount[i]; j++) {
                printf("%d ", expResult[i][j]);
            }
            printf("}, real = { ");
            for (int j = 0; j < realCount[i]; j++) {
                printf("%d ", realResult[i][j]);
            }
            printf(" }\n");

        }
    }
}
