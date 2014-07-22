QT += widgets

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    osgridref.cpp

HEADERS += \
    mainwindow.h \
    osgridref.h

OTHER_FILES += \
    android/AndroidManifest.xml

RESOURCES +=

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
