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

//TEST(MIN_COLUMNS_MPI, ) {
//
//}
//
//TEST(MIN_COLUMNS_MPI, ) {
//
//}
//
//TEST(MIN_COLUMNS_MPI, ) {
//
//}

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


//#include <iostream>
//#include "min_column_matrix.h"
//#include <mpi.h>
//#include <fstream>
//
//int main(int argc, char** argv) {
//
//    MPI_Init(&argc, &argv);
//    
//    int rank;
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//
//    std::vector< std::vector<int> > Matrix;
//
//    if (rank == 0) {
//        Matrix = GetRandomMatrix(3, 3);
//
//        for (size_t i = 0; i < Matrix.size(); i++) {
//            for (size_t j = 0; j < Matrix[0].size(); j++) {
//                std::cout << Matrix[i][j] << " ";
//            }
//            std::cout << std::endl;
//        }
//
//        std::cout << std::endl;
//
//        std::vector <int> result = GetSequentialMinValueColumn(Matrix);
//
//        for (size_t i = 0; i < result.size(); i++)
//            std::cout << result[i] << " ";
//        std::cout << std::endl;
//        std::cout << std::endl;
//    }
//
//    std::vector<int> result_parall;
//
//    result_parall = GetParallelMinValueColumn(Matrix, 3, 3);
//
//    if (rank == 0) {
//        std::ofstream fout;
//        fout.open("C:/labs/laba1/res.txt");
//        for (int i = 0; i < result_parall.size(); i++) {
//            fout << result_parall[i] << " ";
//        }
//        fout << std::endl;
//        fout.close();
//    }
//
//    MPI_Finalize();
//
//    system("pause");
//
//    return 0;
//}