// Copyright 2019 Andronov Maxim
#include <random>
#include <vector>
#include "../../../modules/task_3/andronov_m_radix_with_batcher_split/radix_with_batcher_split.h"

#include <iostream>

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
            } else {
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

std::vector<int> EvenSplit(std::vector<int> arr1, std::vector<int> arr2) {
    int arr1_size = arr1.size();
    int arr2_size = arr2.size();
    int result_size = arr1_size / 2 + arr2_size / 2 + arr1_size % 2 + arr2_size % 2;
    std::vector<int> result(result_size);
    int i = 0;
    int j = 0, k = 0;

    while ((j < arr1_size) && (k < arr2_size)) {
        if (arr1[j] <= arr2[k]) {
            result[i] = arr1[j];
            j += 2;
        }
        else {
            result[i] = arr2[k];
            k += 2;
        }
        i++;
    }

    if (j >= arr1_size) {
        for (int l = k; l < arr2_size; l += 2) {
            result[i] = arr2[l];
            i++;
        }
    }
    else {
        for (int l = j; l < arr1_size; l += 2) {
            result[i] = arr1[l];
            i++;
        }
    }

    return result;
}

std::vector<int> OddSplit(std::vector<int> arr1, std::vector<int> arr2) {
    int arr1_size = arr1.size();
    int arr2_size = arr2.size();
    int result_size = arr1_size / 2 + arr2_size / 2;
    std::vector<int> result(result_size);
    int i = 0;
    int j = 1, k = 1;

    while ((j < arr1_size) && (k < arr2_size)) {
        if (arr1[j] <= arr2[k]) {
            result[i] = arr1[j];
            j += 2;
        }
        else {
            result[i] = arr2[k];
            k += 2;
        }
        i++;
    }

    if (j >= arr1_size) {
        for (int l = k; l < arr2_size; l += 2) {
            result[i] = arr2[l];
            i++;
        }
    }
    else {
        for (int l = j; l < arr1_size; l += 2) {
            result[i] = arr1[l];
            i++;
        }
    }

    return result;
}

//arr1 - четные   arr2 - нечетные
std::vector<int> EvenOddSplit(std::vector<int> arr1, std::vector<int> arr2) {
    int arr1_size = arr1.size();
    int arr2_size = arr2.size();
    int result_size = arr1_size + arr2_size;
    std::vector<int> result(result_size);
    int i = 0, j = 0, k = 0;

    while ((j < arr1_size) && (k < arr2_size)) {
        result[i] = arr1[j];
        result[i + 1] = arr2[k];
        i += 2;
        j++;
        k++;
    }

    if ((k >= arr2_size) && (j < arr1_size)) {
        for (int l = i; l < result_size; l++) {
            result[l] = arr1[j];
            j++;
        }
    }

    for (int i = 0; i < result_size - 1; i++) {
        if (result[i] > result[i + 1])
            std::swap(result[i], result[i + 1]);
    }

    return result;
}

std::vector<int> ParallelRadixSortBatcherSplit(std::vector<int> array, int size_arr) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size == 1)
        return RadixSort(array);
    
    MPI_Comm MPI_COMM_TASK = MPI_COMM_NULL;

    if (size_arr < size) {
        MPI_Group global_group, new_group;
        MPI_Comm_group(MPI_COMM_WORLD, &global_group);
        std::vector<int> new_group_ranks;
        for (int i = 0; i < size_arr; i++)
            new_group_ranks.push_back(i);
        MPI_Group_incl(global_group, size, new_group_ranks.data(), &new_group);
        MPI_Comm_create(MPI_COMM_WORLD, new_group, &MPI_COMM_TASK);

    } else {
        MPI_COMM_TASK = MPI_COMM_WORLD;
    }

    if (MPI_COMM_TASK != MPI_COMM_NULL) {
        MPI_Comm_size(MPI_COMM_TASK, &size);
        MPI_Comm_rank(MPI_COMM_TASK, &rank);

        int delta = size_arr / size;
        int delta_rem = size_arr % size;

        std::vector<int> sendcounts(size, delta);

        int elemnts_count = delta_rem;
        int it = 0;
        while (elemnts_count != 0) {
            sendcounts[it]++;
            it++;
            elemnts_count--;
        }

        std::vector<int> displ(size, 0);
        displ[0] = 0;
        for (int i = 1; i < size; i++) {
            displ[i] = displ[i - 1] + sendcounts[i - 1]; //check this!!!
        }
        
        std::vector<int> local_array(displ[rank]);

        MPI_Scatterv(&array[0], &sendcounts[0], &displ[0], MPI_INT, &local_array[0],
            displ[rank], MPI_INT, 0, MPI_COMM_TASK);

        ////test
        //for (int i = 0; i < local_array.size(); i++)
        //    std::cout << local_array[i] << " ";
        //std::cout << std::endl;
        ////test


        return array;//local_array;
    }
    

    if (MPI_COMM_TASK == MPI_COMM_NULL)
        return array;
}