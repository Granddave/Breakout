QT          += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = Breakout
TEMPLATE    = app

CONFIG      += c++11

SOURCES     += main.cpp\
               breakout.cpp\
               Block.cpp\
               Boll.cpp\
               powerup.cpp\
               powerupInvisible.cpp\
               powerupRacket.cpp\
               powerupSpeed.cpp\
               Racket.cpp\
               Score.cpp

HEADERS     += breakout.h\
               Block.h\
               Boll.h\
               defines.h\
               powerup.h\
               powerupInvisible.h\
               powerupRacket.h\
               powerupSpeed.h\
               Racket.h\
               Score.h

FORMS       += breakout.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES   += res.qrc
