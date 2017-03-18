#-------------------------------------------------
#
# Project created by QtCreator 2017-03-13T18:08:27
#
#-------------------------------------------------

RC_FILE = BatchStabilizer.rc

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BatchStabilizer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp \
    settingsDialog.cpp \
    tasks/deshaker_pass1.cpp \
    tasks/deshaker_generic.cpp \
    tasks_list.cpp \
    tasks/deshaker_pass2.cpp \
    tasks/mpeg_conversion.cpp

HEADERS  += \
    settingsDialog.h \
    tasks/tasks_base.h \
    action_result.h \
    tasks/deshaker_pass1.h \
    tasks/deshaker_generic.h \
    tasks_list.h \
    deshaker_configuration.h \
    tasks/deshaker_pass2.h \
    tasks/mpeg_conversion.h

FORMS    += \
    settingsDialog.ui

install_it.path = $${OUT_PWD}
install_it.files += $${PWD}/sys_tray_icon.ico

INSTALLS += install_it
