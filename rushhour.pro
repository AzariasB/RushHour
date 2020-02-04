
QT              -= gui core
CONFIG          += c++17
QMAKE_CXXFLAGS  += -std=c++17

SOURCES += src/main.cpp \
            src/Car.cpp \
            src/Map.cpp \
            src/State.cpp

HEADERS += \
           src/Car.hpp \
           src/Map.hpp \
           src/Point.hpp \
           src/State.hpp
