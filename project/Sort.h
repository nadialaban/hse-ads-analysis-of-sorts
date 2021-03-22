#include "Utility.h"

class Sort {
public:
// Итерационные сортировки
    /**
     * Сортировка выбором минимума
     * @param arr - массив чисел
     * @param size - размер массива
     */
    static void selectionSort(int *arr, int array_size) {
        int index;
        for (size_t i = 0; i < array_size - 1; i++) {
            index = i;

            // ищем идекс минимального элемента в неотсортированной части массива
            for (size_t j = i + 1; j < array_size; j++)
                if (arr[j] < arr[index])
                    index = j;

            // ставим минимальный элемент в конец отсортированной части массива0
            if (i != index)
                std::swap(arr[index], arr[i]);
        }
    }

    /**
     * Сортировка пузырьком
     * @param arr - массив чисел
     * @param size - размер массива
     */
    static void bubbleSort(int *arr, int array_size) {
        // Проходимся по массиву и "поднимаем" элементы с наименьшим значениями
        for (size_t i = 0; i < array_size - 1; ++i)
            for (size_t j = array_size - 1; j > i; --j)
                if (arr[j] < arr[j - 1])
                    std::swap(arr[j], arr[j - 1]);
    }

    /**
     * Сортировка бинарными вставками
     * @param arr - массив чисел
     * @param size - размер массива
     */
    static void binaryInsertionSort(int *arr, int array_size) {
        int val, new_index;
        for (int i = 1; i < array_size; ++i) {
            val = arr[i];
            // Находим место  для элемента в отсортированной части массива
            new_index = Utility::binarySearch(arr, val, 0, i - 1);
            // двигаем элемент на нужное место
            for (int j = i - 1; j > new_index - 1; --j)
                if (arr[j] != arr[j + 1])
                    std::swap(arr[j], arr[j + 1]);
        }
    }

// Линейные сортировки
    /**
     * Устойчивая сортировка подсчетом
     * @param arr - массив чисел
     * @param size - размер массива
     */
    static void countingSort(int *arr, int array_size) {
        int min = INT_MAX;
        int k = Utility::findBufferSize(arr, array_size, min);
        int res[array_size];
        // Тут индекс значения A[i] - min
        int buf[k];

        // Зануляем вспоомгательный массив
        ArrayManager::resetArray(buf, k);

        // Считаем элементы
        for (int i = 0; i < array_size; ++i) {
            buf[arr[i] - min]++;
        }

        // Считаем частичные суммы
        for (int i = k - 2; i >= 0; --i) {
            buf[i] += buf[i + 1];
        }

        // Считаем отсортированный массив
        for (int i = array_size - 1; i >= 0; --i) {
            res[array_size - buf[arr[i] - min]] = arr[i];
            buf[arr[i] - min]--;
        }

        // Записываем отсортированный массив
        ArrayManager::copyArray(res, arr, array_size);
    }

    /**
     * Цифровая сортировка
     * @param arr
     * @param size
     */
    static void radixSort(int *arr, int array_size) {
        int8_t maxCountOfDigits = 1;
        // Находим самое большое число
        int max = 0;
        for (int i = 0; i < array_size; ++i)
            if (arr[i] > arr[max])
                max = i;

        // Находим максимальное количество разрядов
        for (int i = 3; i >= 0; --i) {
            if (Utility::getDigitByIndex(i, arr[max]) != 0) {
                maxCountOfDigits = i + 1;
                break;
            }
        }

        // Сортируем по каждой цифре
        for (int i = 0; i < maxCountOfDigits; ++i)
            Utility::countingSort256(arr, array_size, i);
    }

// Рекурсивные сортировки
    /**
     * Сортировка кучей
     * @param arr - массив
     * @param array_size - размер массива
     */
    static void heapSort(int *arr, int array_size) {
        int heap_size = array_size;
        Utility::buildHeap(arr, heap_size);
        for (int i = 0; i < array_size; ++i) {
            Utility::heapify(arr, 0, heap_size);
            heap_size--;
            std::swap(arr[0], arr[heap_size]);
        }
    }

    /**
     * Запуск сортировки слияением
     * @param arr - масив
     * @param array_size - размер массива
     */
    static void mergeSort(int *arr, int array_size) {
        mergeSort(arr, array_size, 0, array_size - 1);
    }

    /**
     * Запуск быстрой сортировки
     * @param arr - масив
     * @param array_size - размер массива
     */
    static void quickSort(int *arr, int array_size) {
        quickSort(arr, 0, array_size - 1);
    }

private:
    /**
     * Сортировка слиянием
     * @param arr
     * @param left
     * @param right
     */
    static void mergeSort(int *arr, int array_size, int left, int right) {
        if (left < right) {
            int middle = (left + right) / 2;
            mergeSort(arr, array_size, left, middle); //сортировка левой части
            mergeSort(arr, array_size, middle + 1, right); //сортировка правой части
            Utility::merge(arr, array_size, left, right); //слияние двух частей
        }
    }

    /**
     * Быстрая сортировка со средним опорным элементом
     * @param arr - массив
     * @param left - левая границв
     * @param right - правая граница
     */
    static void quickSort(int *arr, int left, int right) {
        int p = arr[(left + right) / 2],
                l = left,
                r = right;

        while (l <= r) {
            while (arr[l] < p && l < right)
                l++;
            while (arr[r] > p && r > left)
                r--;
            if (l <= r) {
                std::swap(arr[l], arr[r]);
                l++;
                r--;
            }
        }

        if (left < r)
            quickSort(arr, left, r);
        if (right > l)
            quickSort(arr, l, right);
    }

};
