//Copyright 2019 Andronov Maxim
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include "./min_column_matrix.h"

TEST(MIN_COLUMNS_MPI, Test_On_Size_3) {
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

TEST(MIN_COLUMNS_MPI, Test_On_Size_4) {
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
