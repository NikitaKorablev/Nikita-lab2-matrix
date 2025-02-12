#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
    TDynamicMatrix<int> m1(10); m1[0][0] = 1;
    TDynamicMatrix<int> m2(m1);
    EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
    TDynamicMatrix<int>  m1(10);
    TDynamicMatrix<int> m2(m1);
    m1[0][0] = 1;
    EXPECT_EQ(0, m2[0][0]);
}

TEST(TDynamicMatrix, can_get_size)
{
    int sz = 10;
    TDynamicMatrix<int> m1(sz);
    EXPECT_EQ(sz, m1.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
    TDynamicMatrix<int> m(1);
    int k = 10;
    m[0][0] = k;
    EXPECT_EQ(k, m[0][0]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
    TDynamicMatrix<int> m(10);
    ASSERT_ANY_THROW(m[0][-1] = 0);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
    TDynamicMatrix<int> m(10);
    ASSERT_ANY_THROW(m[0][1000] = 0);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
    TDynamicMatrix<int> m(5);
    ASSERT_NO_THROW(m = m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
    int sz = 10;
    TDynamicMatrix<int> m1(sz); m1[0][0] = 1;
    TDynamicMatrix<int> m2(sz);
    m2 = m1;
    EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
    int sz = 3;
    TDynamicMatrix<int> m1(sz);
    TDynamicMatrix<int> m2(2);
    m2 = m1;
    EXPECT_EQ(sz, m2.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
    TDynamicMatrix<int> m1(10); m1[0][0] = 1;
    TDynamicMatrix<int> m2(5);
    m2 = m1;
    EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
    int sz = 10;
    TDynamicMatrix<int> m1(sz);
    TDynamicMatrix<int> m2(sz);
    ASSERT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
    TDynamicMatrix<int> m(10);
    ASSERT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
    TDynamicMatrix<int> m1(5);
    TDynamicMatrix<int> m2(10);
    ASSERT_FALSE(m1 == m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
    int sz = 10;
    TDynamicMatrix<int> m1(sz); m1[0][0] = 1;
    TDynamicMatrix<int> m2(sz); m2[0][0] = 1;
    EXPECT_NO_THROW(m1 + m2);
    EXPECT_EQ(2, (m1 + m2)[0][0]);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
    TDynamicMatrix<int> m1(5);
    TDynamicMatrix<int> m2(10);
    ASSERT_ANY_THROW(m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
    int sz = 10;
    TDynamicMatrix<int> m1(sz); m1[0][0] = 2;
    TDynamicMatrix<int> m2(sz); m2[0][0] = 1;
    EXPECT_NO_THROW(m1-m2);
    EXPECT_EQ(1, (m1 - m2)[0][0]);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
    TDynamicMatrix<int> m1(5);
    TDynamicMatrix<int> m2(10);
    ASSERT_ANY_THROW(m1 - m2);
}

TEST(TDynamicMatrix, can_multiply_scalar_by_matrix)
{
    int val = 5;
    TDynamicMatrix<int> m(5);
    m[0][1] = 1;
    m = m * val;

    EXPECT_EQ(val, m[0][1]);
}

TEST(TDynamicMatrix, can_multiply_matrices_with_equal_size)
{
    int sz = 2;
    TDynamicMatrix<int> m1(sz);
    m1[0][0] = 1; m1[0][1] = 2;
    m1[1][0] = 2; m1[1][1] = 1;
    TDynamicMatrix<int> m2(sz);
    m2[0][0] = 2; m2[0][1] = 1;
    m2[1][0] = 1; m2[1][1] = 2;

    TDynamicMatrix<int> m3(sz);
    m3[0][0] = 4; m3[0][1] = 5;
    m3[1][0] = 5; m3[1][1] = 4;

    EXPECT_EQ(m3, m1 * m2);
}

