//Copyright 2019 Andronov Maxim

#ifndef MODULES_TASK_1_ANDRONOV_M_MIN_COLUMN_MATRIX
#define MODULES_TASK_1_ANDRONOV_M_MIN_COLUMN_MATRIX

#include <vector>

std::vector < std::vector<int> > GetRandomMatrix(int rows, int column);
//проверить со ссылкой на Matrix
std::vector <int> GetSequentialMinValueColumn(std::vector < std::vector<int> > Matrix); 

std::vector <int> GetParallelMinValueColumn(std::vector < std::vector<int> >& Matrix, int rows,
    int columns);

#endif //MODULES_TASK_1_ANDRONOV_M_MIN_COLUMN_MATRIX
