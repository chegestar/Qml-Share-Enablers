/*
 * This file is part of Handset UX Share user interface
 *
 * Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies). All rights reserved.
 * Contact: Jukka Tiihonen <jukka.tiihonen@nokia.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to 
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense,     
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER  
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS  
 * IN THE SOFTWARE. 
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
