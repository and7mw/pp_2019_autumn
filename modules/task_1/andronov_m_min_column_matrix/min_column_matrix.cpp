// Copyright 2019 Andronov Maxim
#include <mpi.h>
#include <random>
#include <algorithm>
#include <vector>
#include "../../../modules/task_1/andronov_m_min_column_matrix/min_column_matrix.h"

std::vector< std::vector<int> > GetRandomMatrix(int rows, int columns) {
    if (rows < 1 || columns < 1)
        throw - 1;

    std::vector < std::vector<int> > matrix;

    matrix.resize(rows);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution <int> dist(-100, 100);

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            matrix[i].push_back(dist(gen));

    return matrix;
}

std::vector <int> GetSequentialMinValueColumn(std::vector < std::vector<int> > Matrix) {
    int rows = Matrix.size();
    int columns = Matrix[0].size();

    if (rows < 1 || columns < 1)
        throw - 1;

    std::vector <int> result(columns);

    for (int i = 0; i < columns; i++) {
        int min = Matrix[0][i];
        for (int j = 1; j < rows; j++) {
            if (Matrix[j][i] < min)
                min = Matrix[j][i];
        }

        result[i] = min;
    }

    return result;
}

std::vector <int> GetParallelMinValueColumn(std::vector < std::vector<int> > Matrix, int rows, int columns) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int Error = 0;
    if (rank == 0) {
        if (rows != Matrix.size() || columns != Matrix[0].size()) {
            Error = 1;
            for (int i = 1; i < size; i++)
                MPI_Send(&Error, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    } else {
        MPI_Status status;
        MPI_Recv(&Error, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    }

    if (Error == 1)
        throw - 1;

    const int delta = columns / size;
    const int delta_rem = columns % size;

    std::vector <int> result;

    std::vector <int> local_columns(delta*rows);

    if (rank == 0) {
        std::vector<int> tr_matrix;

        if (delta > 0) {
            for (int i = delta_rem + delta; i < columns; i++)
                for (int j = 0; j < rows; j++)
                    tr_matrix.push_back(Matrix[j][i]);
            for (int i = 0; i < size - 1; i++)
                MPI_Send(&tr_matrix[0] + delta * rows * i, delta*rows, MPI_INT, i + 1, 0, MPI_COMM_WORLD);
        }
    } else {
        MPI_Status status;
        if (delta > 0)
            MPI_Recv(&local_columns[0], delta*rows, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    }

    if (rank == 0) {
        std::vector <int> local_tr_matrix;

        for (int i = 0; i < delta_rem + delta; i++)
            for (int j = 0; j < rows; j++)
                local_tr_matrix.push_back(Matrix[j][i]);

        for (int i = 0; i < delta_rem + delta; i++)
            result.push_back(*min_element(local_tr_matrix.begin() + i * rows,
                                        local_tr_matrix.begin() + (i + 1) * rows));

        if (delta > 0) {
            std::vector <int> local_result(delta);
            for (int i = 1; i < size; i++) {
                MPI_Status status;
                MPI_Recv(&local_result[0], delta, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
                result.insert(result.end(), local_result.begin(), local_result.end());
            }
        }
    } else {
        if (delta > 0) {
            std::vector <int> local_result(delta);
            for (int i = 0; i < delta; i++) {
                local_result[i] = *min_element(local_columns.begin() + i * rows,
                    local_columns.begin() + (i + 1) * rows);
            }
            MPI_Send(&local_result[0], delta, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    }

    return result;
}

