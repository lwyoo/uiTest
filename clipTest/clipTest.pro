QT += quick
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \

#RESOURCES += qml.qrc
DISTFILES += \
    main.qml \
    mainType2.qml \
    POP_UP_BOTTOM_W.png \
    POP_UP_TOP_R.png \
    POP_UP_BOTTOM_R.png \
    POP_UP_BOTTOM_W.png \
    POP_UP_TOP_R.png \
    POP_UP_TOP_W.png \
    POP_UP_BOTTOM_R.png \
    POP_UP_BOTTOM_W.png \
    POP_UP_MIDDLE_BG.png \
    POP_UP_TOP_R.png \
    POP_UP_TOP_W.png \
    SCC_IMG_LANE_BG.png \
    SCC_IMG_SCC_CAR_CD_01.png \
    SCC_IMG_SCC_CAR_CD_02.png \
    SCC_IMG_SCC_CAR_CD_03.png \
    SCC_IMG_SCC_CAR_CD_04.png \
    SCC_IMG_SCC_CAR_HM_01.png \
    SCC_IMG_SCC_CAR_HM_02.png \
    SCC_IMG_SCC_CAR_HM_03.png \
    SCC_IMG_SCC_CAR_HM_04.png \
    LDWS_IMG_LANE_LEFT_GRAY.png \
    LDWS_IMG_LANE_LEFT_WHITE.png \
    LDWS_IMG_LANE_LEFT_YELLOW.png \
    LDWS_IMG_LANE_RIGHT_GRAY.png \
    LDWS_IMG_LANE_RIGHT_WHITE.png \
    LDWS_IMG_LANE_RIGHT_YELLOW.png


# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
