// Copyright 2019 Andronov Maxim
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "./min_column_matrix.h"

TEST(MPI_Min_Columns, Incorrect_Arguments_Create_Matrix) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::vector< std::vector<int> > Matrix;

    if (rank == 0) {
        ASSERT_ANY_THROW(GetRandomMatrix(0, 1));
    }
}

TEST(MPI_Min_Columns, Incorrect_Arguments_Seq_Min) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::vector< std::vector<int> > Matrix;

    if (rank == 0) {
        ASSERT_ANY_THROW(GetSequentialMinValueColumn(Matrix);
    }
}

TEST(MPI_Min_Columns, Incorrect_Arguments_Parall_Min) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::vector< std::vector<int> > Matrix;

    if (rank == 0) {
        Matrix = GetRandomMatrix(2, 2);
    }

    ASSERT_ANY_THROW(GetParallelMinValueColumn(Matrix, 1, 1));
}

TEST(MPI_Min_Columns, Test_On_Size_1) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::vector< std::vector<int> > Matrix;

    if (rank == 0) {
        Matrix = GetRandomMatrix(1, 1);
    }

    std::vector<int> result_parall = GetParallelMinValueColumn(Matrix, 1, 1);

    if (rank == 0) {
        std::vector <int> result = GetSequentialMinValueColumn(Matrix);
        ASSERT_EQ(result, result_parall);
    }
}

TEST(MPI_Min_Columns, Test_On_Size_1) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::vector< std::vector<int> > Matrix;

    if (rank == 0) {
        Matrix = GetRandomMatrix(1, 1);
    }

    std::vector<int> result_parall = GetParallelMinValueColumn(Matrix, 1, 1);

    if (rank == 0) {
        std::vector <int> result = GetSequentialMinValueColumn(Matrix);
        ASSERT_EQ(result, result_parall);
    }
}

TEST(MPI_Min_Columns, Test_On_Size_2) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::vector< std::vector<int> > Matrix;

    if (rank == 0) {
        Matrix = GetRandomMatrix(2, 2);
    }

    std::vector<int> result_parall = GetParallelMinValueColumn(Matrix, 2, 2);

    if (rank == 0) {
        std::vector <int> result = GetSequentialMinValueColumn(Matrix);
        ASSERT_EQ(result, result_parall);
    }
}

TEST(MPI_Min_Columns, Test_On_Size_3) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::vector< std::vector<int> > Matrix;

    if (rank == 0) {
        Matrix = GetRandomMatrix(3, 3);
    }

    std::vector<int> result_parall = GetParallelMinValueColumn(Matrix, 3, 3);

    if (rank == 0) {
        std::vector <int> result = GetSequentialMinValueColumn(Matrix);
        ASSERT_EQ(result, result_parall);
    }
}

TEST(MPI_Min_Columns, Test_On_Size_4) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::vector< std::vector<int> > Matrix;

    if (rank == 0) {
        Matrix = GetRandomMatrix(4, 4);
    }

    std::vector<int> result_parall = GetParallelMinValueColumn(Matrix, 4, 4);

    if (rank == 0) {
        std::vector <int> result = GetSequentialMinValueColumn(Matrix);
        ASSERT_EQ(result, result_parall);
    }
}

TEST(MPI_Min_Columns, Test_On_Size_51) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::vector< std::vector<int> > Matrix;

    if (rank == 0) {
        Matrix = GetRandomMatrix(51, 51);
    }

    std::vector<int> result_parall = GetParallelMinValueColumn(Matrix, 51, 51);

    if (rank == 0) {
        std::vector <int> result = GetSequentialMinValueColumn(Matrix);
        ASSERT_EQ(result, result_parall);
    }
}



int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);

    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners& listeners =
        ::testing::UnitTest::GetInstance()->listeners();

    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());

    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
    return RUN_ALL_TESTS();
}

