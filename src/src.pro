include(../common.pri)

# Build shared library for deployment, static library for testing
TEMPLATE =  lib
contains(DEFINES, BB_TEST_BUILD) {
    CONFIG += static
} else {
    CONFIG += shared
}

QMAKE_LFLAGS += -Wl,--no-undefined -Wl,--as-needed

# Library name is libQtNfcSubset (or libQtNfcSubset-d for debug)
TARGET =    QtNfcSubset$${BIN_SUFFIX}
VERSION =   1

# Library depends on libQtCore
QT = core

# Non-test build also depends on libbps, and libscreen
#!contains(DEFINES, BB_TEST_BUILD) {
#    LIBS = -lbps -lscreen -lbb
#}

# Force a clean to delete object_script files (if present)
QMAKE_CLEAN += object_script.*

# Search paths for include files
INCLUDEPATH += \
    ../src/nfc \
    ../public/QtNfcSubset \

# Header files used to compile library - for dependency tracking
HEADERS = \
    nfc/*.h \
    ../public/QtNfcSubset/*.h \

# Source files used to compile library
SOURCES = \
    nfc/*.cpp \
