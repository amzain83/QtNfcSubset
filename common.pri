# Enable debug and release mode by default and
# disable moc keywords that conflict with 3rd parties
CONFIG += debug_and_release no_keywords

# Detect debug or release build
CONFIG(debug, debug|release) {
    BUILD_MODE = debug
} else {
    BUILD_MODE = release
}

# The release/debug binary file name suffix
CONFIG(debug, debug|release) {
    BIN_SUFFIX = _g
} else {
    BIN_SUFFIX =
}

# Detect target platform
blackberry-armv7le* {
  	PLATFORM = armv7le
    DEFINES += NFC_NDEF_LIBRARY
}

# Detect emulator platform
blackberry-x86* {
    PLATFORM = x86
    DEFINES += NFC_NDEF_LIBRARY
}

# Detect host platform
win32|macx|linux* {
    PLATFORM = host
    DEFINES += BB_TEST_BUILD
}

# Notify about undetected platform
isEmpty(PLATFORM) {
    error("Unsupported platform")
}

# Organize where build output goes
isEmpty(DESTDIR) {
        DESTDIR=$$PWD/build/$${PLATFORM}/$${BUILD_MODE}
}
OBJECTS_DIR =   $${DESTDIR}/.obj
MOC_DIR =       $${DESTDIR}/.moc

# Treat all warnings as errors and hide all 
# symbols by default (i.e. require explicit export)
QMAKE_CXXFLAGS += -Werror -Wno-error=deprecated-declarations -fvisibility=hidden

# For test builds, search QNX headers last and
# force 32-bit compilation
contains(DEFINES, BB_TEST_BUILD) {
    QMAKE_CXXFLAGS += -m32 -idirafter \'$(QNX_TARGET)/usr/include\'
    QMAKE_LFLAGS += -m32
}
