#include <QtTest/QTest>

#include "Linarg.hpp"

// add necessary includes here


class Matrix_tests : public QObject
{
    Q_OBJECT

public:
    Matrix_tests();
    ~Matrix_tests();

private slots:
    void size_test_1();
    void size_test_2();
    void size_test_3();
    void size_test_4();
    void size_test_5();
    void size_test_6();
    void size_test_7();
    void square_test();
    void not_square_test();

    void data_test_1();
    void data_test_2();
    void fill_zeros_test();
    void fill_ones_test();

    void diagonal_test();
    void not_diagonal_test();
    void unit_test();
    void not_unit_test();

    void oper_compare_test();
    void oper_plus_test();

private:

    bool data_check(int* array,  linarg::Matrix<int> mat)
    {
        auto iter = mat.begin();

        for(std::size_t i = 0; iter != mat.end(); ++iter, ++i)
        {
            if(*iter != array[i])
            {
                return false;
            }
        }

        return true;
    }
};

Matrix_tests::Matrix_tests()
{

}

Matrix_tests::~Matrix_tests()
{

}

void Matrix_tests::size_test_1()
{
    linarg::Matrix<int> mat(5, 3);

    using size_type = linarg::Matrix<int>::size_type;

    const size_type req_rows = 5;
    const size_type req_cols = 3;

    QVERIFY( (mat.rows() == req_rows) && (mat.cols() == req_cols) );
}

void Matrix_tests::size_test_2()
{
    linarg::Mat_size size(2, 10);

    linarg::Matrix<int> mat(size);

    using size_type = typename linarg::Matrix<int>::size_type;

    const size_type req_rows = 2;
    const size_type req_cols = 10;

    QVERIFY( (mat.rows() == req_rows) && (mat.cols() == req_cols) );
}

void Matrix_tests::size_test_3()
{
    linarg::Matrix<double> mat
    {
        {2.13224, 3.50001, 2.24002},
        {5.52102, 8.01122, 3.21103}
    };

    using size_type = linarg::Matrix<double>::size_type;

    const size_type req_rows = 2;
    const size_type req_cols = 3;

    QVERIFY( (mat.rows() == req_rows) && (mat.cols() == req_cols) );
}

void Matrix_tests::size_test_4()
{
    linarg::Matrix<double> mat{2.33, 6.543, 3.213, 5.423, 6.4876, 2.01};

    using size_type = linarg::Matrix<double>::size_type;

    const size_type req_rows = 1;
    const size_type req_cols = 6;

    QVERIFY( (mat.rows() == req_rows) && (mat.cols() == req_cols) );
}

void Matrix_tests::size_test_5()
{
    linarg::Matrix<double> mat(linarg::rd::randrd_mt19937_mat(3, 4, 0.2, 1.7));

    using size_type = linarg::Matrix<double>::size_type;

    const size_type req_rows = 3;
    const size_type req_cols = 4;

    QVERIFY( (mat.rows() == req_rows) && (mat.cols() == req_cols) );
}

void Matrix_tests::size_test_6()
{
    auto fun = []{ return 3.14; };

    linarg::Matrix<double> mat(5, 5, fun);

    using size_type = typename linarg::Matrix<double>::size_type;

    size_type req_rows = 5;
    size_type req_cols = 5;

    QVERIFY( (mat.rows() == req_rows) && (mat.cols() == req_cols) );
}

void Matrix_tests::size_test_7()
{
    linarg::Matrix<int> mat
    {
        {2, 3, 4, 7},
        {6, 5, 4, 2},
        {54,23,76,1},
        {76,34,12,65},
        {8, 7, 34,12}
    };

    linarg::Mat_size size = mat.size();

    QVERIFY( (size.rows_ == mat.rows()) && size.cols_ == mat.cols() );
}

void Matrix_tests::square_test()
{
    linarg::Matrix<int> square_mat(4, 4);

    QVERIFY(square_mat.is_square());
}

void Matrix_tests::not_square_test()
{
    linarg::Matrix<int> not_square_mat(2, 3);

    QVERIFY(!not_square_mat.is_square());
}

void Matrix_tests::data_test_1()
{
    linarg::Matrix<int> mat
    {
        {3,4,5,6},
        {4,3,2,6},
        {6,1,5,0}
    };

    int array[] = { 3,4,6,4,3,1,5,2,5,6,6,0 };

    bool is_same_data = data_check(array, mat);

    QVERIFY(is_same_data);
}

void Matrix_tests::data_test_2()
{
    linarg::Matrix<int> mat{3,2,5,7,4,3};

    int array[] = {3,2,5,7,4,3};

    bool is_same_data = data_check(array, mat);

    QVERIFY(is_same_data);
}

void Matrix_tests::fill_zeros_test()
{
    linarg::Matrix<int> mat
    {
        {5,3,2,5},
        {6,3,4,2},
        {6,4,3,2}
    };

    mat.fill_zeros();

    const std::size_t size = 12;

    int array[size] = { };

    bool is_same_data = data_check(array, mat);

    QVERIFY(is_same_data);
}

void Matrix_tests::fill_ones_test()
{
    linarg::Matrix<int> mat
    {
        {5,3,2,5},
        {6,3,4,2},
        {6,4,3,2}
    };

    mat.fill_ones();

    const std::size_t size = 12;

    int array[size];

    std::fill(array, array + size, 1);

    bool is_same_data = data_check(array, mat);

    QVERIFY(is_same_data);
}

void Matrix_tests::diagonal_test()
{
    linarg::Matrix<int> mat
    {
        {1,0,0,0},
        {0,1,0,0},
        {0,0,1,0},
        {0,0,0,1}
    };

    QVERIFY(mat.is_diagonal());
}

void Matrix_tests::not_diagonal_test()
{
    linarg::Matrix<int> mat
    {
        {0,4,5,0},
        {0,5,0,6},
        {6,1,0,0},
        {4,0,7,0}
    };

    QVERIFY(!mat.is_diagonal());
}

void Matrix_tests::unit_test()
{
    linarg::Matrix<int> mat
    {
        {1,0,0,0},
        {0,1,0,0},
        {0,0,1,0},
        {0,0,0,1}
    };

    QVERIFY(mat.is_unit());
}

void Matrix_tests::not_unit_test()
{
    linarg::Matrix<int> mat
    {
        {1,4,5,0},
        {0,1,0,6},
        {6,1,5,0},
        {4,0,7,1}
    };

    QVERIFY(!mat.is_unit());
}

void Matrix_tests::oper_compare_test()
{
    linarg::Matrix<int> A
    {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };

    linarg::Matrix<int> B
    {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };

    bool compare = (A == B);

    QVERIFY(compare);
}

void Matrix_tests::oper_plus_test()
{
    linarg::Matrix<int> A
    {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };

    linarg::Matrix<int> B(3, 3);
    B.fill_ones();

    linarg::Matrix<int> C = A + B;

    linarg::Matrix<int> R
    {
        {2,3,4},
        {5,6,7},
        {8,9,10}
    };

    QVERIFY(C == R);
}

QTEST_MAIN(Matrix_tests)

#include "tst_matrix_tests.moc"
