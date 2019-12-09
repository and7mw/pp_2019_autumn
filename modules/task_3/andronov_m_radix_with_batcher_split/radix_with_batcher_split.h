// Copyright 2019 Andronov Maxim
#ifndef MODULES_TASK_3_ANDRONOV_M_RADIX_WITH_BATCHER_SPLIT_
#define MODULES_TASK_3_ANDRONOV_M_RADIX_WITH_BATCHER_SPLIT_

#include <mpi.h>
#include <vector>

std::vector<int> GetRandomVector(int size);

unsigned char GetByte(int value, int number);

std::vector<int> RadixSort(std::vector<int> array);

#endif  // MODULES_TASK_3_ANDRONOV_M_RADIX_WITH_BATCHER_SPLIT_
