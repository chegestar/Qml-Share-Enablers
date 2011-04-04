#-------------------------------------------------
#
# Project created by QtCreator 2011-03-16T14:39:59
#
#-------------------------------------------------

QT       += core gui

# install locations
INSTALL_INC  = $$INSTALL_ROOT/$$[QT_INSTALL_PREFIX]/include
INSTALL_BIN  = $$INSTALL_ROOT/$$[QT_INSTALL_BINS]
INSTALL_LIB  = $$INSTALL_ROOT/$$[QT_INSTALL_LIBS]


TARGET = share-ui-common-declarative
TEMPLATE = lib

# or any other way to get DBUS_SERVICE defined
CONFIG += share-widgets

# makes sure symbols are exported when building the library and imported when
# built against, see share-ui-common-declarative.h
DEFINES += SHAREUICOMMONDECLARATIVE_LIBRARY

# needed for making thumbnails in shareditem.cpp
LIBS += -lthumbnailer

DEPENDPATH += ./src
INCLUDEPATH += . ./src

SOURCES += itemcontainer.cpp \
           shareditem.cpp \
           pluginloader.cpp \
           methodbase.cpp


HEADERS += ShareUIDeclarative/itemcontainer.h \
           ShareUIDeclarative/shareditem.h \
           ShareUIDeclarative/pluginloader.h \
           ShareUIDeclarative/methodbase.h \
           share-ui-common-declarative_global.h


# Install the built shared object
target.path = $$INSTALL_LIB
INSTALLS += target

# Install public headers
pubheaders.path = $$INSTALL_INC/ShareUIDeclarative
pubheaders.files = ShareUIDeclarative/*
INSTALLS += pubheaders
