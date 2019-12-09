// Copyright 2019 Andronov Maxim
#include <random>
#include <vector>
#include "../../../modules/task_3/andronov_m_radix_with_batcher_split/radix_with_batcher_split.h"

std::vector<int> GetRandomVector(int size) {
    if (size < 1)
        throw - 1;

    std::vector <int> vec;

    vec.resize(size);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution <int> dist(-100, 100);

    for (int i = 0; i < size; i++)
        vec[i] = dist(gen);

    return vec;
}

unsigned char GetByte(int value, int number) {
    return (value >> (number * 8)) & 255;
}

std::vector<int> RadixSort(std::vector<int> array) {
    if (array.size() < 1)
        throw - 1;
    if (array.size() == 1)
        return array;

    std::vector<int> tmp(array.size());
    std::vector<int> counter(256, 0);
    std::vector<int> offset(256, 0);
    bool flag = true;

    for (int i = 0; i < 3; i++) {
        for (size_t j = 0; j < array.size(); j++) {
            unsigned char byte = GetByte(array[j], i);
            counter[byte]++;
        }
        offset[0] = 0;
        for (int k = 1; k < 256; k++) {
            offset[k] = counter[k - 1] + offset[k - 1];
        }
        for (size_t j = 0; j < array.size(); j++) {
            if (flag) {
                unsigned char value = GetByte(array[j], i);
                tmp[offset[value]] = array[j];
                offset[value]++;
            }
            else {
                int value = GetByte(tmp[j], i);
                array[offset[value]] = tmp[j];
                offset[value]++;
            }
        }
        flag = !flag;
        for (int k = 0; k < 256; k++) {
            counter[k] = 0;
        }
    }
    for (size_t j = 0; j < array.size(); j++) {
        char byte = (char)GetByte(array[j], 3);
        counter[byte + 128]++;
    }
    offset[0] = 0;
    for (int k = 1; k < 256; k++) {
        offset[k] = counter[k - 1] + offset[k - 1];
    }
    for (size_t j = 0; j < array.size(); j++) {
        char value = GetByte(tmp[j], 3);
        array[offset[value + 128]] = tmp[j];
        offset[value + 128]++;
    }

    return array;
}
