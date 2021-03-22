#include <iostream>

class Utility {
public:
    /**
     * Бинарный поиск
     * @param arr - массив
     * @param item - элемент, который мы ищем
     * @param left - левая граница
     * @param right - правая граница
     * @return Индекс элемента
     */
    static int binarySearch(int *arr, int val, int l, int r) {
        int mid = (r - l) / 2 + l;

        if (arr[mid] == val)
            return mid;
        if (r - l == 0)
            return r + (arr[r] < val ? 1 : 0);

        if (arr[mid] > val) {
            r = (mid - 1) < l ? l : (mid - 1);
            return binarySearch(arr, val, l, r);
        }
        l = (mid + 1) > r ? r : (mid + 1);
        return binarySearch(arr, val, l, r);
    }

    /**
     * Вычисление размера буффера для сортировки подсчетом
     * @param numbers - массив
     * @param array_size - размер массива
     * @param min - минимум
     * @param max - максимум
     * @return размер буффера
     */
    static int findBufferSize(const int *numbers, int array_size, int &min) {
        int max = -1;
        for (int i = 0; i < array_size; ++i) {
            if (min > numbers[i])
                min = numbers[i];
            if (max < numbers[i])
                max = numbers[i];
        }
        return max - min + 1;
    }

    /**
     * Получение цифры по разряду в 256ричной сс
     * @param index - разряд
     * @param val - число
     * @return цифрв
     */
    static int getDigitByIndex(int index, int val) {
        return (val >> (8 * index)) & 255;
    }

    /**
     * Сортировка подсчетом по цифре в 256ричной сс
     * @param numbers - массив чисел
     * @param array_size - размер массива
     * @param index - цифра числа, по которому мы мортируем
     */
    static void countingSort256(int *arr, int array_size, int index) {
        auto *res = new int[array_size];
        int *buf = new int[256];

        // Зануляем вспоомгательный массив
        ArrayManager::resetArray(buf, 256);

        // Считаем элементы
        for (int i = 0; i < array_size; ++i) {
            buf[getDigitByIndex(index, arr[i])]++;
        }

        // Считаем частичные суммы
        for (int i = 254; i >= 0; --i) {
            buf[i] += buf[i + 1];
        }

        // Считаем отсортированный массив
        for (int i = 0; i < array_size; ++i) {
            res[array_size - buf[getDigitByIndex(index, arr[i])]] = arr[i];
            buf[getDigitByIndex(index, arr[i])]--;
        }

        // Записываем отсортированный массив
        ArrayManager::copyArray(res, arr, array_size);

        delete[] res;
        delete[] buf;
    }

    /**
     * Вспомогательный метод для построения кучи от узда
     * @param heap - куча
     * @param index - мндекс узла
     * @param array_size - размер массива
     */
    static void heapify(int *heap, int index, int array_size) {
        int l = 2 * index + 1;
        int r = 2 * index + 2;

        // Ищем индекс минимального значения
        int minimal = (l < array_size && heap[l] > heap[index]) ? l : index;
        if (r < array_size && heap[r] > heap[minimal])
            minimal = r;

        // Если узел неправильный, меняем нужные значения и перестраиваем кучу
        if (minimal != index) {
            std::swap(heap[index], heap[minimal]);
            if (minimal * 2 + 1 < array_size) {
                heapify(heap, minimal, array_size);
            }
        }
    }

    /**
     * Построение кучи
     * @param numbers - массив чисел
     * @param heap_size - размер массива
     */
    static void buildHeap(int *numbers, int heap_size) {
        for (int i = (heap_size - 1) / 2; i > -1; --i)
            heapify(numbers, i, heap_size);
    }

    /**
     * Слияние двух массиовов
     * @param arr - массив
     * @param left
     * @param right
     */
    static void merge(int *arr, int array_size, int left, int right) {
        int middle, start, final, j;
        int *mas = new int[array_size];

        // Вычисление среднего элемента
        middle = (left + right) / 2;
        // Начало левой и правой частей
        start = left;
        final = middle + 1;

        // Проходим по массиву
        for (j = left; j <= right; j++)
            if ((start <= middle) && ((final > right) || (arr[start] < arr[final]))) {
                mas[j] = arr[start];
                start++;
            } else {
                mas[j] = arr[final];
                final++;
            }

        // Копируем результат
        for (j = left; j <= right; j++)
            arr[j] = mas[j];

        delete[] mas;
    }

};
