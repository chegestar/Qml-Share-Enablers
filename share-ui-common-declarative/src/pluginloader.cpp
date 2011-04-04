
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


#include "ShareUIDeclarative/pluginloader.h"
#include "ShareUIDeclarative/methodbase.h"

#include <ShareUI/PluginLoader>
#include <ShareUI/MethodBase>

#include <QDebug>

using ShareUIDeclarative::PluginLoader;


class PluginLoader::Private: public QObject
{
    Q_OBJECT

public:
    Private(QObject *parent = 0);


public:

    ShareUI::PluginLoader *m_pluginLoader;

public slots:

    void newMethod(ShareUI::MethodBase *method);

};


PluginLoader::Private::Private(QObject *parent): QObject(parent)
{
}


void PluginLoader::Private::newMethod(ShareUI::MethodBase *method)
{
    qDebug() << "PluginLoader::Private::newMethod" << method->title();
}


PluginLoader::PluginLoader(ShareUI::PluginLoader *pluginLoader, QObject *parent): QObject(parent)
{
    m_d = new Private(this);
    m_d->m_pluginLoader = pluginLoader;

    /*!
      \brief Signal emitted when method is activated after loading
      \param method Method activated
     */
    //void newMethod (ShareUI::MethodBase * method);
    connect(m_d->m_pluginLoader, SIGNAL(newMethod(ShareUI::MethodBase*)),
            this, SIGNAL(methodCountChanged()));

    connect(m_d->m_pluginLoader, SIGNAL(newMethod(ShareUI::MethodBase*)),
            m_d->m_pluginLoader, SIGNAL(newMethod(ShareUI::MethodBase*)));

    /*!
      \brief Signal to listen method visibility changes. Better to use this
             than direct signal from ShareUI::MethodBase.
      \param method Method which visibility state has changed
      \param visible If true method should be presented to user. If false
                     then it must be hidden from the user.
     */
    //void methodVisible (ShareUI::MethodBase * method, bool visible);

    /*!
      \brief Signal emitted when all plugins have been loaded
    */
    //void allPluginsLoaded ();

    connect(m_d->m_pluginLoader, SIGNAL(allPluginsLoaded()),
            this, SIGNAL(allPluginsLoaded()));


}


int PluginLoader::methodCount() const
{
    return m_d->m_pluginLoader->methodCount();
}

int PluginLoader::pluginCount() const
{
    return m_d->m_pluginLoader->pluginCount();
}


QList<QObject*> PluginLoader::methods()
{
    QList<ShareUI::MethodBase *> shareui_methods = m_d->m_pluginLoader->methods();

    QList<QObject *> declarative_methods;

    foreach(ShareUI::MethodBase * m, shareui_methods ) {
        ShareUIDeclarative::MethodBase *dm = new ShareUIDeclarative::MethodBase(m, this);
        declarative_methods << qobject_cast<QObject*>(dm);
    }

    return declarative_methods;
}


QObject *PluginLoader::method(int at)
{
    ShareUI::MethodBase *mb = m_d->m_pluginLoader->method(at);
    ShareUIDeclarative::MethodBase *dmb = new ShareUIDeclarative::MethodBase(mb, this);
    return qobject_cast<QObject*>(dmb);
}


QString PluginLoader::pluginNameForMethod(QObject *method) const
{
    ShareUIDeclarative::MethodBase* m = qobject_cast<ShareUIDeclarative::MethodBase*>(method);
    return m_d->m_pluginLoader->pluginNameForMethod(m->methodBase());
}

#include "pluginloader.moc"

