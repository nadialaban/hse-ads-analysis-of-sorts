#include <iostream>
#include <random>

class ArrayManager {
public:
    /**
     * Заполнения массива случайными числами в диапазоне
     * @param arr - массив
     * @param bound - граница
     */
    static void createRandomArray(int *arr, int bound, int array_size = 4100) {
        srand(time(nullptr));
        for (int i = 0; i < array_size; ++i) {
            arr[i] = random() % (bound + 1);
        }
    }

    /**
     * Заполнение почти отсортированного массива
     * @param arr - массив
     */
    static void createAlmostSortedArray(int *arr, int array_size = 4100) {
        srand(time(nullptr));

        for (int i = 0; i < 4100; ++i) {
            arr[i] = i + 1;
        }

        // В каждой сотне меняем два элемента местами
        for (int i = 0; i < array_size; i += 100) {
            auto a = i + random() % 100,
                    b = i + random() % 100;
            if (a != b)
                std::swap(arr[a], arr[b]);
        }
    }

    /**
     * Заполнение отсортированного в обратном порядке массива
     * @param arr - массив
     */
    static void createReversedArray(int *arr) {
        for (int i = 0; i < 4100; ++i) {
            arr[i] = 4100 - i;
        }
    }

    /**
     * Копирование эталонного массива в рабочий
     * @param arr - эталонный массив
     * @param buf - рабочий массив
     * @param count - нужное количество элементов
     */
    static void copyArray(const int *arr, int *buf, int count) {
        for (int i = 0; i < count; ++i) {
            buf[i] = arr[i];
        }
    }

    /**
     * Зануление массива
     * @param arr - массив
     * @param array_size - размер массива
     */
    static void resetArray(int *arr, int array_size) {
        for (int i = 0; i < array_size; ++i) {
            arr[i] = 0;
        }
    }

    /**
     * Зануление массива
     * @param arr - массив
     * @param array_size - размер массива
     */
    static void resetArray(unsigned long long *arr, int array_size) {
        for (int i = 0; i < array_size; ++i) {
            arr[i] = 0;
        }
    }

    /**
     * Проверка массиыв нв отсортированность
     * @param arr - массив
     * @param array_size - размер массива
     * @return
     */
    static bool assertSorted(int *ref, const int *arr, int array_size) {
        std::sort(ref, ref + array_size);
        for (int i = 0; i < array_size; ++i) {
            if (arr[i] != ref[i])
                return false;
        }
        return true;
    }

    /**
     * Массив в строку
     * @param arr - массив
     * @param array_size - размер массива
     * @return строковое представление массива
     */
    static std::string toString(const int *arr, int array_size, char del = ' ') {
        std::string str;
        for (int i = 0; i < array_size; ++i) {
            str += del + std::to_string(arr[i]) ;
        }
        return str;
    }
};
