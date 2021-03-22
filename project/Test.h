#include "ArrayManager.h"
#include "Sort.h"
#include "Writer.h"
#include <string>
#include <chrono>

class Test {
private:
    int *refArr0to5;
    int *refArr0to4000;
    int *refArrAlmostSorted;
    int *refArrReversed;

    Writer wr = Writer("data50-300.csv", "data100-4100.csv");

    /**
     * Холостые прогоны сортировок, чтобы оптимизирующий
     * компилятор провел оптимизацию
     */
    static void idleRuns() {
        void (*sortMethods[8])(int *, int) = {Sort::selectionSort, Sort::bubbleSort, Sort::binaryInsertionSort,
                                              Sort::countingSort, Sort::radixSort, Sort::heapSort,
                                              Sort::quickSort, Sort::mergeSort};
        int *arr = new int[1000];
        int *buf = new int[1000];

        // Запускаем каждую сортировку пять раз для разных массивов
        for (int i = 0; i < 5; ++i) {
            ArrayManager::createRandomArray(arr, 1000, 1000);
            for (auto m : sortMethods) {
                ArrayManager::copyArray(arr, buf, 1000);
                m(buf, 1000);
            }
        }
    }

    /**
     * Тестирование части массива
     * @param count - количество элементов
     * @return - результуты измерени
     */
    void testStep(unsigned long long *res, int count) {
        void (*sortMethods[8])(int *, int) = {Sort::selectionSort, Sort::bubbleSort, Sort::binaryInsertionSort,
                                              Sort::countingSort, Sort::radixSort, Sort::heapSort,
                                              Sort::quickSort, Sort::mergeSort};
        auto refArrays = {refArr0to5, refArr0to4000, refArrAlmostSorted, refArrReversed};

        int *buf = new int[count];
        int *ref = new int[count];
        int i = 0;
        for (auto m : sortMethods) {
            for (auto arr : refArrays) {
                ArrayManager::copyArray(arr, buf, count);
                ArrayManager::copyArray(arr, ref, count);
                // Включаем счетчик времени
                auto start = std::chrono::high_resolution_clock::now();
                m(buf, count);
                // Выключаем счетчик времени
                auto elapsed = std::chrono::high_resolution_clock::now() - start;

                if (!ArrayManager::assertSorted(ref, buf, count)) {
                    std::cout << "ref: " << ArrayManager::toString(arr, count) << std::endl;
                    std::cout << "buf: " << ArrayManager::toString(buf, count) << std::endl;
                    std::cout << "not sorted " << i << std::endl;
                }

                unsigned long long time = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
                // Записываем результат
                res[i++] += time;
            }
        }

    }

    /**
     * Запуск тестирования для массивов
     */
    void startTest() {
        idleRuns();
        auto *res = new unsigned long long[32];
        // от 50 до 300, шаг 50
        for (int i = 50; i <= 300; i += 50) {
            ArrayManager::resetArray(res, 32);
            for (int j = 0; j < 100; ++j)
                testStep(res, i);
            wr.writeResults(res, 100, i, "data50-300.csv");
        }

        // от 100 до 4100, шаг 1000
        for (int i = 100; i <= 4100; i += 1000) {
            ArrayManager::resetArray(res, 32);
            for (int j = 0; j < 100; ++j)
                testStep(res, i);
            wr.writeResults(res, 100, i,"data100-4100.csv");
        }
    }

public:
    /**
     * Заполнение референтных массивов и запуск тестирования
     */
    void start() {
        refArr0to5 = new int[4100];
        refArr0to4000 = new int[4100];
        refArrAlmostSorted = new int[4100];
        refArrReversed = new int[4100];

        ArrayManager::createRandomArray(refArr0to5, 5);
        ArrayManager::createRandomArray(refArr0to4000, 4000);
        ArrayManager::createAlmostSortedArray(refArrAlmostSorted);
        ArrayManager::createReversedArray(refArrReversed);

        startTest();

        delete[] refArr0to5;
        delete[] refArr0to4000;
        delete[] refArrAlmostSorted;
        delete[] refArrReversed;
    }
};
