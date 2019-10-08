#include "min_column_matrix.h"
#include <random>
#include <mpi.h>

std::vector< std::vector<int> > GetRandomMatrix(int rows, int columns) {

    std::vector < std::vector<int> > matrix;

    matrix.resize(rows);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution <int> dist(-10, 10);

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < columns; j++)
            matrix[i].push_back(dist(gen));

    return matrix;
}

std::vector <int> GetSequentialMinValueColumn(std::vector < std::vector<int> > Matrix) {
    int rows = Matrix.size();
    int columns = Matrix[0].size();

    std::vector <int> result(columns);
    //���������� ��������� stl �����
    for (size_t i = 0; i < columns; i++) {
        int min = Matrix[0][i];
        for (size_t j = 1; j < rows; j++) {
            if (Matrix[j][i] < min)
                min = Matrix[j][i];
        }

        result[i] = min;
    }

    return result;
}

std::vector <int> GetParallelMinValueColumn(std::vector < std::vector<int> >& Matrix, int rows, 
                                                                int columns) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    const int delta = columns / size;
    const int delta_rem = columns % size;

    std::vector <int> result;

    std::vector <int> local_columns(delta*rows);

    if (rank == 0) {
        std::vector<int> tr_matrix;

        if (delta > 0) {//size > 1
            for (int i = delta_rem + delta; i < columns; i++) //i = 0
                for (int j = 0; j < rows; j++)
                    tr_matrix.push_back(Matrix[j][i]);
            for (int i = 0; i < size - 1; i++) //tag?
                MPI_Send(&tr_matrix[0] + delta * rows * i, delta*rows, MPI_INT, i + 1, 0, MPI_COMM_WORLD);
        }
    } else {        
        MPI_Status status;
        if (delta > 0) //?
            MPI_Recv(&local_columns[0], delta*rows, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    }

    if (rank == 0) {
        std::vector <int> local_tr_matrix;

        for (int i = 0; i < delta_rem + delta; i++) 
            for (int j = 0; j < rows; j++)
                local_tr_matrix.push_back(Matrix[j][i]);

        for (int i = 0; i < delta_rem + delta; i++)
            result.push_back(*std::min_element(local_tr_matrix.begin() + i * rows,
                local_tr_matrix.begin() + (i + 1) * rows));
        //if (delta_rem > 0) {//size > 1
        //    for (int i = 0; i < delta_rem; i++)
        //        for (int j = 0; j < rows; j++)
        //            local_tr_matrix.push_back(Matrix[j][i]);

        //    for (int i = 0; i < delta_rem; i++) {
        //        result.push_back(*std::min_element(local_tr_matrix.begin() + i * rows,
        //            local_tr_matrix.begin() + (i + 1) * rows)); //���������� � end?
        //    }

        //} else {
        //    for (int i = 0; i < delta; i++) //i < columns
        //        for (int j = 0; j < rows; j++)
        //            local_tr_matrix.push_back(Matrix[j][i]);

        //    for (int i = 0; i < delta; i++) {
        //        result.push_back(*std::min_element(local_tr_matrix.begin() + i * rows,
        //            local_tr_matrix.begin() + (i + 1) * rows)); //���������� � end?
        //    }
        //}

        if (delta > 0) {
            std::vector <int> local_result(delta);
            for (int i = 1; i < size; i++) {
                MPI_Status status;
                MPI_Recv(&local_result[0], delta, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
                //�������� status
                result.insert(result.end(), local_result.begin(), local_result.end());//!&!&!!&!&&!
            }
        }
    } else {
        if (delta > 0) {
            std::vector <int> local_result(delta);
            for (int i = 0; i < delta; i++) {
                local_result[i] = *std::min_element(local_columns.begin() + i * rows,
                    local_columns.begin() + (i + 1) * rows); //���������� � end?
            }
            MPI_Send(&local_result[0], delta, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    }

    return result;
}