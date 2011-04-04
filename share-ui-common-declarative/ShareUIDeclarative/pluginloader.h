
/*
 * This file is part of Handset UX Share user interface
 *
 * Copyright (c) 2010 Nokia Corporation and/or its subsidiary(-ies).
 * Contact: Jukka Tiihonen <jukka.t.tiihonen@nokia.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU Lesser General Public License,
 * version 2.1, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef SHAREUIDECLARATIVE_PLUGINLOADER_H
#define SHAREUIDECLARATIVE_PLUGINLOADER_H

#include "share-ui-common-declarative_global.h"

#include <QObject>
#include <QList>


namespace ShareUI {
    class PluginLoader;
}

namespace ShareUIDeclarative {
    class PluginLoader;
    class MethodBase;
}


class SHAREUICOMMONDECLARATIVESHARED_EXPORT ShareUIDeclarative::PluginLoader: public QObject {
    Q_OBJECT

    Q_PROPERTY(int methodCount READ methodCount NOTIFY methodCountChanged)
    Q_PROPERTY(int pluginCount READ pluginCount NOTIFY pluginCountChanged)
    Q_PROPERTY(QList<QObject*> methods READ methods NOTIFY methodsChanged)

    class Private;

public:
    PluginLoader(ShareUI::PluginLoader *PluginLoader, QObject *parent = 0);

    /*!
      \brief Number of methods loaded currently
      \sa ShareUI::PluginLoader::methodCount()
      \return Number of methods loaded
     */
    int methodCount() const;

    /*!
      \brief Number of plugins loaded currently
      \sa ShareUI::PluginLoader::pluginCount()
      \return Number of plugins loaded
     */
    int pluginCount() const;

    /*!
      \brief Get current list of methods.
      \sa ShareUI::PluginLoader::methods()
      \return List of methods
     */
    QList <QObject *> methods ();

    /*!
      \brief Get method with index
      \param at Index number of plugin. 0 .. (amount() - 1)
      \note Returns QObject because of qml restrictions. However, will be seen
            as ShareUIDeclarative::MethodBase at qml side
      \sa ShareUI::PluginLoader::method(int at)
      \return Pointer to ShareUIDeclarative::MethodBase or null if at is out of range
     */
    Q_INVOKABLE QObject * method (int at);

    /*!
      \brief Get plugin name for method
      \param method Method searched
      \sa  ShareUI::PluginLoader::pluginNameForMethod(ShareUI::MethodBase* method)
      \return Plugin name for method
     */
    Q_INVOKABLE QString pluginNameForMethod (QObject * method) const;

signals:

    void methodCountChanged();
    void pluginCountChanged();
    void methodsChanged();

    void allPluginsLoaded();
    void newMethod();


private:
    Private *m_d;
};

#endif // SHAREUIDECLARATIVE_PLUGINLOADER_H
