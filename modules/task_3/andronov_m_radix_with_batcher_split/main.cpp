// Copyright 2019 Andronov Maxim
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "../../../modules/task_3/andronov_m_radix_with_batcher_split/radix_with_batcher_split.h"
#include <iostream>

//TEST(Radix_With_Batcher_Split, can_create_vector) {
//    int rank;
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//
//    if (rank == 0) {
//        ASSERT_NO_THROW(GetRandomVector(1));
//    }
//}
//
//TEST(Radix_With_Batcher_Split, cant_create_vector_if_size_less_one) {
//    int rank;
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//
//    if (rank == 0) {
//        ASSERT_ANY_THROW(GetRandomVector(0));
//    }
//}
//
//TEST(Radix_With_Batcher_Split, get_correct_first_byte) {
//    int rank;
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//
//    if (rank == 0) {
//        int value = -583;
//        unsigned char exp = 185;
//        EXPECT_EQ(exp, GetByte(value, 0));
//    }
//}
//
//TEST(Radix_With_Batcher_Split, get_correct_second_byte) {
//    int rank;
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//
//    if (rank == 0) {
//        int value = -583;
//        unsigned char exp = 253;
//        EXPECT_EQ(exp, GetByte(value, 1));
//    }
//}
//
//TEST(Radix_With_Batcher_Split, get_correct_third_byte) {
//    int rank;
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//
//    if (rank == 0) {
//        int value = -583;
//        unsigned char exp = 255;
//        EXPECT_EQ(exp, GetByte(value, 2));
//    }
//}
//
//TEST(Radix_With_Batcher_Split, get_correct_fourth_byte_when_less_zero) {
//    int rank;
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//
//    if (rank == 0) {
//        int value = -583;
//        char exp = -1;
//        EXPECT_EQ(exp, (char)GetByte(value, 3));
//    }
//}
//
//TEST(Radix_With_Batcher_Split, get_correct_fourth_byte_when_more_zero) {
//    int rank;
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//
//    if (rank == 0) {
//        int value = 583;
//        char exp = 0;
//        EXPECT_EQ(exp, (char)GetByte(value, 3));
//    }
//}
//
//TEST(Radix_With_Batcher_Split, throw_radix_sort_with_0_elements) {
//    int rank;
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//
//    if (rank == 0) {
//        std::vector<int> vec;
//        ASSERT_ANY_THROW(RadixSort(vec));
//    }
//}

//TEST(Radix_With_Batcher_Split, radix_sort_with_1_elements) {
//    int rank;
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//
//    if (rank == 0) {
//        std::vector<int> vec, exp_vec;
//        vec = GetRandomVector(1);
//        exp_vec = vec;
//        std::sort(exp_vec.begin(), exp_vec.end());
//        vec = RadixSort(vec);
//
//        EXPECT_EQ(exp_vec, vec);
//    }
//}
//
//TEST(Radix_With_Batcher_Split, radix_sort_with_2_elements) {
//    int rank;
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//
//    if (rank == 0) {
//        std::vector<int> vec, exp_vec;
//        vec = GetRandomVector(2);
//        exp_vec = vec;
//        std::sort(exp_vec.begin(), exp_vec.end());
//        vec = RadixSort(vec);
//
//        EXPECT_EQ(exp_vec, vec);
//    }
//}
//
//TEST(Radix_With_Batcher_Split, radix_sort_with_3_elements) {
//    int rank;
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//
//    if (rank == 0) {
//        std::vector<int> vec, exp_vec;
//        vec = GetRandomVector(3);
//        exp_vec = vec;
//        std::sort(exp_vec.begin(), exp_vec.end());
//        vec = RadixSort(vec);
//
//        EXPECT_EQ(exp_vec, vec);
//    }
//}
//
//TEST(Radix_With_Batcher_Split, radix_sort_with_4_elements) {
//    int rank;
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//
//    if (rank == 0) {
//        std::vector<int> vec, exp_vec;
//        vec = GetRandomVector(4);
//        exp_vec = vec;
//        std::sort(exp_vec.begin(), exp_vec.end());
//        vec = RadixSort(vec);
//
//        EXPECT_EQ(exp_vec, vec);
//    }
//}
//
//TEST(Radix_With_Batcher_Split, radix_sort_with_5_elements) {
//    int rank;
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//
//    if (rank == 0) {
//        std::vector<int> vec, exp_vec;
//        vec = GetRandomVector(5);
//        exp_vec = vec;
//        std::sort(exp_vec.begin(), exp_vec.end());
//        vec = RadixSort(vec);
//
//        EXPECT_EQ(exp_vec, vec);
//    }
//}
//
//TEST(Radix_With_Batcher_Split, radix_sort_with_10_elements) {
//    int rank;
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//
//    if (rank == 0) {
//        std::vector<int> vec, exp_vec;
//        vec = GetRandomVector(10);
//        exp_vec = vec;
//        std::sort(exp_vec.begin(), exp_vec.end());
//        vec = RadixSort(vec);
//
//        EXPECT_EQ(exp_vec, vec);
//    }
//}

//TEST(Radix_With_Batcher_Split, radix_sort_with_100_elements) {
//    int rank;
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//
//    if (rank == 0) {
//        std::vector<int> vec, exp_vec;
//        vec = GetRandomVector(100);
//        exp_vec = vec;
//        std::sort(exp_vec.begin(), exp_vec.end());
//        vec = RadixSort(vec);
//
//        EXPECT_EQ(exp_vec, vec);
//    }
//}
//
//TEST(Radix_With_Batcher_Split, radix_sort_with_111_elements) {
//    int rank;
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//
//    if (rank == 0) {
//        std::vector<int> vec, exp_vec;
//        vec = GetRandomVector(111);
//        exp_vec = vec;
//        std::sort(exp_vec.begin(), exp_vec.end());
//        vec = RadixSort(vec);
//
//        EXPECT_EQ(exp_vec, vec);
//    }
//}

//TEST(CreateComm, qwe) {
//    MPI_Comm comm = MPI_COMM_NULL;;
//    MPI_Group global_group, new_group;
//
//    MPI_Comm_group(MPI_COMM_WORLD, &global_group);
//    std::vector<int> new_group_ranks;
//    for (int i = 0; i < 2; i++)
//        new_group_ranks.push_back(i);
//    MPI_Group_incl(global_group, 2, new_group_ranks.data(), &new_group);
//    MPI_Comm_create(MPI_COMM_WORLD, new_group, &comm);
//
//    int size1, size2;
//
//    comm = MPI_COMM_WORLD;
//    MPI_Comm_size(comm, &size1);
//    MPI_Comm_size(MPI_COMM_WORLD, &size2);
//
//    
//
//    EXPECT_EQ(2, size1);
//
//    EXPECT_EQ(3, size2);
//}

TEST(Radix_With_Batcher_Split, sort) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> array;
    const int size = 150;
    if (rank == 0) {
        array = GetRandomVector(size);
    }

    std::vector<int> result_array = ParallelRadixSortBatcherSplit(array, size);
    if (rank == 0) {
        sort(array.begin(), array.end());
        EXPECT_EQ(array, result_array);
    }
}

//TEST(Radix_With_Batcher_Split, ) {
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
