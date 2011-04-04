/* This file is part of nokia-share-ui
 *
 * Copyright © 2010 Nokia Corporation and/or its subsidiary(-ies).
 * All rights reserved.
 * Contact: Jukka Tiihonen <jukka.t.tiihonen@nokia.com>
 *
 * This software, including documentation, is protected by copyright controlled
 * by Nokia Corporation. All rights are reserved. Copying, including
 * reproducing, storing, adapting or translating, any or all of this material
 * requires the prior written consent of Nokia Corporation. This material also
 * contains confidential information which may not be disclosed to others
 * without the prior written consent of Nokia.
 */

#include "qmlshareui.h"


#include <QDebug>
#include <QTimer>

#include <ShareUIDeclarative/itemcontainer.h>
#include <ShareUIDeclarative/pluginloader.h>
#include <ShareUIDeclarative/methodbase.h>

#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include <QDeclarativeView>
#include <QDeclarativeEngine>
#include <QDeclarativeContext>

QMLShareUi::QMLShareUi(QObject * parent) :
    ShareWidgets::UiImplementationBase (parent), m_application(0), m_mainWindow(0) {
}

QMLShareUi::~QMLShareUi() {
    if (m_mainWindow) {
        m_mainWindow->close();
        delete m_mainWindow;
        m_mainWindow = 0;
    }

    if (m_application) {
        delete m_application;
        m_application = 0;
    }
}

QApplication * QMLShareUi::application (int & argc, char ** argv) {

    if (!m_application) {
        m_application = new QApplication(argc, argv);
    }

    return m_application;
}

bool QMLShareUi::showUI (ShareUI::PluginLoader * loader,
                           const ShareUI::ItemContainer * container)
{

    if (!m_mainWindow) {
        m_mainWindow = new QMainWindow();

        QWidget *centralWidget = new QWidget(m_mainWindow);

        QDeclarativeView *view = new QDeclarativeView(centralWidget);
        view->setResizeMode(QDeclarativeView::SizeRootObjectToView);

        QVBoxLayout *layout = new QVBoxLayout(centralWidget);
        layout->addWidget(view);
        m_mainWindow->setCentralWidget(centralWidget);


        ShareUIDeclarative::ItemContainer *ic = new ShareUIDeclarative::ItemContainer(container, m_mainWindow);
        ShareUIDeclarative::PluginLoader *pl = new ShareUIDeclarative::PluginLoader(loader, m_mainWindow);
        loader->loadPlugins();

        view->rootContext()->setContextProperty("context_itemContainer", ic);
        view->rootContext()->setContextProperty("context_pluginLoader", pl);
        view->setSource(QUrl::fromLocalFile("/usr/share/share-ui-declarative/ui.qml"));
    }

    m_mainWindow->showFullScreen();

    return true;

}

void QMLShareUi::closeWindow() {
    m_mainWindow->close();
    delete m_mainWindow;
    m_mainWindow = 0;

}

Q_EXPORT_PLUGIN2(qml-share-ui, QMLShareUi)
