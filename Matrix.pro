TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

HEADERS += \
    Matrix/Algorithms.hpp \
    Matrix/Aliases.h \
    Matrix/Arrays.hpp \
    Matrix/Base.hpp \
    Matrix/Base.tcc \
    Matrix/Cond.hpp \
    Matrix/Container.hpp \
    Matrix/Conversions.hpp \
    Matrix/Diagonal_elems.hpp \
    Matrix/Enums.hpp \
    Matrix/Exception.hpp \
    Matrix/Expression.hpp \
    Matrix/Expression.tcc \
    Matrix/Generated.hpp \
    Matrix/Io.hpp \
    Matrix/Iterator.hpp \
    Matrix/Linarg.hpp \
    Matrix/Math.hpp \
    Matrix/Matrix.hpp \
    Matrix/Matrix.tcc \
    Matrix/Matrix_initializer.hpp \
    Matrix/Matrix_initializer.tcc \
    Matrix/Matrix_size.hpp \
    Matrix/Matrix_size.tcc \
    Matrix/Minor.hpp \
    Matrix/Minor.tcc \
    Matrix/Minor_initializer.hpp \
    Matrix/Minor_initializer.tcc \
    Matrix/Operations.hpp \
    Matrix/Random.hpp \
    Matrix/Sparse_matrix.hpp \
    Matrix/Sparse_matrix.tcc \
    Matrix/Traits.hpp \
    Matrix/Triangular_fill.hpp \
    Matrix/Triangular_matrix.hpp \
    Matrix/Triangular_matrix.tcc \
    Matrix/Trivec.hpp \
    Matrix/Unbounded_matrix.hpp \
    Matrix/Unbounded_matrix.tcc \
    Matrix/Vector.hpp \
    Matrix/Vector.tcc

INCLUDEPATH += D:\Libraries\armadillo-8.600.0\include
DEPENDPATH += D:\Libraries\armadillo-8.600.0\include
