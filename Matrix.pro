TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

HEADERS += \
    include/Axi.hpp \
    include/Common/Visitor.hpp \
    include/Exceptions/Exception.hpp \
    include/IO/IO.hpp \
    include/Matrix/Algorithms.hpp \
    include/Matrix/Aliases.h \
    include/Matrix/Base.hpp \
    include/Matrix/Base.tcc \
    include/Matrix/Cond.hpp \
    include/Matrix/Container.hpp \
    include/Matrix/Conversions.hpp \
    include/Matrix/Diagonal_elems.hpp \
    include/Matrix/Enums.hpp \
    include/Matrix/Expression.hpp \
    include/Matrix/Expression.tcc \
    include/Matrix/Generated.hpp \
    include/Matrix/Index.hpp \
    include/Matrix/Io.hpp \
    include/Matrix/Iterator.hpp \
    include/Matrix/Linarg.hpp \
    include/Matrix/Math.hpp \
    include/Matrix/Matrix.h.autosave \
    include/Matrix/Matrix.hpp \
    include/Matrix/Matrix.tcc \
    include/Matrix/Matrix_initializer.hpp \
    include/Matrix/Matrix_initializer.tcc \
    include/Matrix/Matrix_size.hpp \
    include/Matrix/Matrix_size.tcc \
    include/Matrix/Operations.hpp \
    include/Matrix/Random.hpp \
    include/Matrix/Sparse_matrix.hpp \
    include/Matrix/Sparse_matrix.tcc \
    include/Matrix/Square_matrix.hpp.autosave \
    include/Matrix/Square_matrix.tcc.autosave \
    include/Matrix/Submatrix.hpp \
    include/Matrix/Submatrix.tcc \
    include/Matrix/Tags.hpp \
    include/Matrix/Traits.hpp \
    include/Matrix/Triangular_fill.hpp \
    include/Matrix/Triangular_matrix.hpp \
    include/Matrix/Triangular_matrix.tcc \
    include/Matrix/Unbounded_matrix.hpp \
    include/Matrix/Unbounded_matrix.tcc \
    include/Matrix/iterator_traits.hpp \
    include/Storage/Arrays.hpp \
    include/Tensor/Cube.hpp \
    include/Tensor/Cube.tcc \
    include/Tensor/Cube_subview.hpp \
    include/Tensor/Cube_subview.tcc \
    include/Tensor/Cube_subview_elems_fill.hpp \
    include/Tensor/Tensor.hpp \
    include/Tensor/Tensor.tcc \
    include/Tensor/Tensor_size.hpp \
    include/Vector/Vector.hpp \
    include/Vector/Vector.tcc

INCLUDEPATH += D:\Libraries\armadillo-8.600.0\include
DEPENDPATH += D:\Libraries\armadillo-8.600.0\include
