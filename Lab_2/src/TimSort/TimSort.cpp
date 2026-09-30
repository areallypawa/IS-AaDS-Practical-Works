#include "TimSort.h"

TimSort::TimSort(int* array, int n) {
    arr = array;
    size = n;

    runCapacity = n > 0 ? n : 1;
    runs = new Run[runCapacity];

    runCount = 0;
}

void TimSort::insertionSort(int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

int TimSort::getMinRun(int n) {
    int remainder = 0;

    while (n >= MIN_MERGE) {
        remainder |= n & 1;
        n >>= 1;
    }

    return n + remainder;
}

int TimSort::findRun(int start) {
    if (start >= size - 1)
        return 1;

    int end = start + 1;

    if (arr[end] >= arr[start]) {
        while (
            end < size &&
            arr[end] >= arr[end - 1]
            ) {
            end++;
        }

        int length = end - start;

        printStep(
            "Найден возрастающий natural run: "
            "начало = " + std::to_string(start) +
            ", длина = " + std::to_string(length)
        );

        printRange(start, end - 1);

        return length;
    }

    while (
        end < size &&
        arr[end] < arr[end - 1]
        ) {
        end++;
    }

    int length = end - start;

    printStep(
        "Найден убывающий natural run: "
        "начало = " + std::to_string(start) +
        ", длина = " + std::to_string(length)
    );

    printRange(start, end - 1);

    int left = start;
    int right = end - 1;

    while (left < right) {
        int temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;

        left++;
        right--;
    }

    printStep("Убывающий run развернут:");

    printRange(start, end - 1);

    return length;
}

void TimSort::pushRun(int start, int length) {
    runs[runCount].start = start;
    runs[runCount].length = length;

    runCount++;

    printStep(
        "Run добавлен в стек: "
        "start = " + std::to_string(start) +
        ", length = " + std::to_string(length)
    );

    std::cout << "Стек run'ов: ";

    for (int i = 0; i < runCount; i++) {
        std::cout
            << "["
            << runs[i].start
            << ", "
            << runs[i].length
            << "] ";
    }

    std::cout << "\n";
}

void TimSort::extendRun(
    int start,
    int currentLength,
    int targetLength
) {
    printStep(
        "Run расширяется: "
        + std::to_string(currentLength)
        + " -> "
        + std::to_string(targetLength)
    );

    int end = start + targetLength - 1;

    if (end >= size)
        end = size - 1;

    insertionSort(start, end);

    printStep("После insertion sort:");

    printRange(start, end);
}


void TimSort::mergeCollapse() {
    while (runCount > 1) {
        bool merged = false;

        if (runCount >= 3) {
            int A = runs[runCount - 3].length;
            int B = runs[runCount - 2].length;
            int C = runs[runCount - 1].length;

            if (A <= B + C || B <= C) {
                if (A < C) {
                    mergeAt(runCount - 3);
                }
                else {
                    mergeAt(runCount - 2);
                }

                merged = true;
            }
        }

        if (!merged && runCount >= 2) {
            int A = runs[runCount - 2].length;
            int B = runs[runCount - 1].length;

            if (A <= B) {
                mergeAt(runCount - 2);
                merged = true;
            }
        }

        if (!merged)
            break;
    }
}

void TimSort::mergeForceCollapse() {
    while (runCount > 1) {
        int index = runCount - 2;

        if (
            runCount >= 3 &&
            runs[runCount - 3].length <
            runs[runCount - 1].length
            ) {
            index--;
        }

        mergeAt(index);
    }
}

int TimSort::gallopRight(
    int value,
    int* temp,
    int length
) {
    int low = 0;
    int high = length;

    while (low < high) {
        int middle = low + (high - low) / 2;

        if (temp[middle] <= value)
            low = middle + 1;
        else
            high = middle;
    }

    return low;
}

int TimSort::gallopLeft(
    int value,
    int* temp,
    int length
) {
    int low = 0;
    int high = length;

    while (low < high) {
        int middle = low + (high - low) / 2;

        if (temp[middle] < value)
            low = middle + 1;
        else
            high = middle;
    }

    return low;
}

void TimSort::merge(
    int left,
    int middle,
    int right
) {
    int leftSize = middle - left + 1;
    int rightSize = right - middle;

    int* leftArray = new int[leftSize];
    int* rightArray = new int[rightSize];

    for (int i = 0; i < leftSize; i++)
        leftArray[i] = arr[left + i];

    for (int i = 0; i < rightSize; i++)
        rightArray[i] = arr[middle + 1 + i];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < leftSize && j < rightSize) {
        if (leftArray[i] <= rightArray[j]) {
            arr[k++] = leftArray[i++];
        }
        else {
            arr[k++] = rightArray[j++];
        }
    }

    while (i < leftSize)
        arr[k++] = leftArray[i++];

    while (j < rightSize)
        arr[k++] = rightArray[j++];

    delete[] leftArray;
    delete[] rightArray;
}

void TimSort::mergeWithGalloping(
    int left,
    int middle,
    int right
) {
    int leftSize = middle - left + 1;
    int rightSize = right - middle;

    printStep(
        "Начинается merge: "
        "левый run [" +
        std::to_string(left) + ", " +
        std::to_string(middle) + "], "
        "правый run [" +
        std::to_string(middle + 1) + ", " +
        std::to_string(right) + "]"
    );

    int* leftArray = new int[leftSize];
    int* rightArray = new int[rightSize];

    for (int i = 0; i < leftSize; i++)
        leftArray[i] = arr[left + i];

    for (int i = 0; i < rightSize; i++)
        rightArray[i] = arr[middle + 1 + i];

    int i = 0;
    int j = 0;
    int k = left;

    int leftWins = 0;
    int rightWins = 0;

    while (i < leftSize && j < rightSize) {
        if (leftArray[i] <= rightArray[j]) {
            arr[k++] = leftArray[i++];
            leftWins++;
            rightWins = 0;
        }
        else {
            arr[k++] = rightArray[j++];
            rightWins++;
            leftWins = 0;
        }

        if (leftWins >= GALLOP_THRESHOLD &&
            i < leftSize) {

            int count = gallopRight(
                rightArray[j],
                leftArray + i,
                leftSize - i
            );

            printStep(
                "Включён galloping mode для левого run. "
                "Переносится элементов: "
                + std::to_string(count)
            );

            for (int x = 0; x < count; x++) {
                arr[k++] = leftArray[i++];
            }

            leftWins = 0;
        }

        if (rightWins >= GALLOP_THRESHOLD &&
            j < rightSize) {

            int count = gallopLeft(
                leftArray[i],
                rightArray + j,
                rightSize - j
            );

            printStep(
                "Включён galloping mode для правого run. "
                "Переносится элементов: "
                + std::to_string(count)
            );

            for (int x = 0; x < count; x++) {
                arr[k++] = rightArray[j++];
            }

            rightWins = 0;
        }
    }

    while (i < leftSize)
        arr[k++] = leftArray[i++];

    while (j < rightSize)
        arr[k++] = rightArray[j++];

    delete[] leftArray;
    delete[] rightArray;

    printStep("Merge завершён.");

    printRange(left, right);
}

void TimSort::mergeAt(int index) {
    int left = runs[index].start;
    int leftLength = runs[index].length;

    int right = runs[index + 1].start;
    int rightLength = runs[index + 1].length;

    int end = right + rightLength - 1;

    printStep(
        "Объединение run'ов: "
        "[start = " + std::to_string(left) +
        ", length = " + std::to_string(leftLength) +
        "] + "
        "[start = " + std::to_string(right) +
        ", length = " + std::to_string(rightLength) +
        "]"
    );

    mergeWithGalloping(
        left,
        right - 1,
        end
    );

    runs[index].length =
        leftLength + rightLength;

    for (int i = index + 1; i < runCount - 1; i++) {
        runs[i] = runs[i + 1];
    }

    runCount--;

    printStep(
        "После merge получен run длиной "
        + std::to_string(runs[index].length)
    );
}

void TimSort::sort() {
    if (size <= 1)
        return;

    runCount = 0;

    printStep("========== НАЧАЛО TIMSORT ==========");

    std::cout << "Исходный массив:\n";
    printArray();

    int minRun = getMinRun(size);

    printStep(
        "Размер массива: "
        + std::to_string(size)
    );

    printStep(
        "Рассчитанный minRun = "
        + std::to_string(minRun)
    );

    int current = 0;

    while (current < size) {
        printStep(
            "Поиск natural run с позиции "
            + std::to_string(current)
        );

        int runLength = findRun(current);

        if (runLength < minRun) {
            int targetLength = minRun;

            if (current + targetLength > size)
                targetLength = size - current;

            extendRun(
                current,
                runLength,
                targetLength
            );

            runLength = targetLength;
        }

        pushRun(
            current,
            runLength
        );

        mergeCollapse();

        current += runLength;
    }

    printStep("Все natural run'ы найдены.");

    printStep(
        "Запуск принудительного объединения оставшихся run'ов"
    );

    mergeForceCollapse();

    printStep("========== TIMSORT ЗАВЕРШЁН ==========");

    std::cout << "Отсортированный массив:\n";
    printArray();
}

void TimSort::printStep(const std::string& message) {
    if (!showSteps)
        return;

    std::cout << "\n[TimSort] " << message << "\n";
}

void TimSort::printRange(int left, int right) {
    if (!showSteps)
        return;

    std::cout << "Массив: ";

    for (int i = 0; i < size; i++) {
        if (i == left)
            std::cout << "[ ";

        std::cout << arr[i] << " ";

        if (i == right)
            std::cout << "] ";
    }

    std::cout << "\n";
}

void TimSort::printArray() const {
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }

    std::cout << "\n";
}

void TimSort::print() const {
    printArray();
}

TimSort::~TimSort() {
    delete[] runs;
}