# douh for the share-widgets...
CONFIG += qt debug plugin link_pkgconfig share-widgets 
TEMPLATE = lib
#PKGCONFIG +=

QT += declarative

# profiling
CONFIG(profiling) {
    message(Building with profiling)
    QMAKE_CXXFLAGS += -ftest-coverage -fprofile-arcs
    LIBS += -lgcov
}

LIBS += -lshare-ui-common-declarative

QMAKE_CXXFLAGS += -O2 -Werror -Wall

VER_MAJ=0
VER_MIN=2
VER_PAT=0

TARGET = qml-share-ui

DEPENDPATH  += ./src

INCLUDEPATH += . \
               ./src 

VPATH += $$DEPENDPATH $$INCLUDEPATH

OBJECTS_DIR = ./obj
MOC_DIR = ./moc
DESTDIR = ./out
QMAKE_CLEAN += obj/* \
               out/* \
               moc/*

OTHER_FILES += src/ui.qml

qml.files += src/ui.qml
qml.path = /usr/share/share-ui-declarative/


include (share-ui-sources.pri)

# Install binary application
target.path = /usr/lib/share-ui/implementations

INSTALLS += target qml
