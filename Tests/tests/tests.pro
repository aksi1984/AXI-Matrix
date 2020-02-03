QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG += c++17
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_matrix_tests.cpp

INCLUDEPATH += D:\Documents\Projects\Matrix\Matrix
DEPENDPATH += D:\Documents\Projects\Matrix\Matrix
