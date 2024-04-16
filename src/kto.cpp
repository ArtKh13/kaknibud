#include <iostream>
#include <fstream>
#include <cstdio>

bool openFile(std::ifstream& file, const std::string& filename) {
    file.open(filename);
    if (!file.is_open()) {
        std::cout << "Файл не удалось открыть" << std::endl;
        return false;
    }
    return true;
}

int main() {
    std::cout << "Введите путь к файлу: ";
    std::string file;
    std::cin >> file;

    std::ifstream inFile;
    if (!openFile(inFile, file)) {
        std::cout << "Программа завершена из-за ошибки открытия файла" << std::endl;
        return 1;
    }

    int siz;
    inFile >> siz;
    if (siz <= 0) {
        std::cout << "Размер массива некорректен" << std::endl;
        inFile.close();
        return 1;
    }
    inFile.close();

    int* pdurik = new int[siz];
    if (!openFile(inFile, file)) {
        std::cout << "Программа завершена из-за ошибки открытия файла" << std::endl;
        delete[] pdurik;
        return 1;
    }

    int ona;
    inFile >> ona;
    for (int i = 0; i < siz; i++) {
        inFile >> pdurik[i];
    }
    inFile.close();

    std::cout << "Данные из файла:" << std::endl;
    for (int i = 0; i < siz; i++) {
        std::cout << pdurik[i] << " ";
    }
    std::cout << std::endl;

    int** megadurik = new int* [siz];
    int prev = pdurik[0];
    int now;
    int n = 0;
    int k = 1;
    megadurik[siz - 1] = new int[siz];
    for (int i = 1; i < siz; i++) {
        now = pdurik[i];
        if (prev < now) {
            megadurik[n] = new int[siz];
            int j = 1;
            megadurik[n][j] = prev;
            j++;
            while (prev < now && i < siz) {
                megadurik[n][j] = now;
                j++;
                prev = now;
                i++;
                if (i < siz)
                    now = pdurik[i];
            }
            megadurik[n][0] = j;
            n++;
        }
        else {
            megadurik[siz - 1][k] = prev;
            k++;
        }

        prev = now;
    }
    if (prev >= now) {
        megadurik[siz - 1][k] = now;
        k++;
    }
    megadurik[siz - 1][0] = k;

    std::cout << "Возрастающие массивы:" << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << "размер: [" << megadurik[i][0] - 1 << "] ";
        for (int j = 1; j < megadurik[i][0]; j++) {
            std::cout << megadurik[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "че не влезло:" << std::endl;
    for (int j = 1; j < k; j++) {
        std::cout << megadurik[siz - 1][j] << " ";
    }
    std::cout << std::endl;
    delete[] pdurik;
    for (int i = 0; i < n; i++) {
        delete[] megadurik[i];
    }
    delete[] megadurik;

    return 0;
}