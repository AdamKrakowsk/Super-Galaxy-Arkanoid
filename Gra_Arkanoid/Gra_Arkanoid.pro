TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Ball.cpp \
        Block.cpp \
        Bonus.cpp \
        Game.cpp \
        HighScore.cpp \
        Menu.cpp \
        Object.cpp \
        Paddle.cpp \
        Shop.cpp \
        SoundManager.cpp \
        Timer.cpp \
        main.cpp
INCLUDEPATH += "C:/SFML-2.5.1/include"
LIBS += -L"C:/SFML-2.5.1/lib"
CONFIG(debug, debug|release){
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}

HEADERS += \
    Ball.h \
    Block.h \
    Bonus.h \
    Game.h \
    HighScore.h \
    Menu.h \
    Object.h \
    Paddle.h \
    Shop.h \
    SoundManager.h \
    Timer.h
