#include <iostream>
#include <fstream>

class Writer {
private:

    std::fstream fout;

public:

    Writer(const std::string& file1, const std::string& file2) {
        std::string header = "ArraySize,"
                             "selectionSort (0 to 5),selectionSort (0 to 4000),selectionSort (almost sorted),selectionSort (reversed),"
                             "bubbleSort (0 to 5),bubbleSort (0 to 4000),bubbleSort (almost sorted),bubbleSort (reversed),"
                             "binaryInsertionSort (0 to 5),binaryInsertionSort (0 to 4000),binaryInsertionSort (almost sorted),binaryInsertionSort (reversed),"
                             "countingSort (0 to 5),countingSort (0 to 4000),countingSort (almost sorted),countingSort (reversed),"
                             "radixSort (0 to 5),radixSort (0 to 4000),radixSort (almost sorted),radixSort (reversed),"
                             "heapSort (0 to 5),heapSort (0 to 4000),heapSort (almost sorted),heapSort (reversed),"
                             "quickSort (0 to 5),quickSort (0 to 4000),quickSort (almost sorted),quickSort (reversed),"
                             "mergeSort (0 to 5),mergeSort (0 to 4000),mergeSort (almost sorted),mergeSort (reversed)";
        fout.open(file1, std::ios::out);
        fout << header;
        fout.close();
        fout.open(file2, std::ios::out);
        fout << header;
        fout.close();
    }

    void writeResults(unsigned long long *arr, int count, int array_size, const std::string& file) {
        fout.open(file, std::ios::app);

        auto line = std::to_string(array_size);
        if (!fout.is_open())
            throw std::ios_base::failure("file not open");
        for (int i = 0; i < 32; ++i) {
            arr[i] /= count;
            line += "," + std::to_string(arr[i]);
        }
        fout << "\n" << line;

        fout.close();
    }

    /**
     * Запись массивов
     * @param ref - исходный массив
     * @param sorted - отсортированный массив
     * @param array_size - размер массива
     */
    void writeArrays(int *ref, int *sorted, int array_size) {
        fout.open("input.txt", std::ios::out);
        if (!fout.is_open())
            throw std::ios_base::failure("file not open");
        fout << ArrayManager::toString(ref, array_size);
        fout.close();

        fout.open("output.txt", std::ios::out);
        if (!fout.is_open())
            throw std::ios_base::failure("file not open");
        fout << ArrayManager::toString(sorted, array_size);
        fout.close();

    }
};
