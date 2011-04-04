
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


#include "ShareUIDeclarative/itemcontainer.h"
#include "ShareUIDeclarative/shareditem.h"

#include <ShareUI/ItemContainer>

#include <QDebug>

using ShareUIDeclarative::ItemContainer;


class ItemContainer::Private: public QObject
{
    Q_OBJECT

public:
    Private(QObject *parent = 0);


public:
    const ShareUI::ItemContainer *m_itemContainer;

};


ItemContainer::Private::Private(QObject *parent): QObject(parent)
{
}


ItemContainer::ItemContainer(const ShareUI::ItemContainer *itemContainer, QObject *parent): QObject(parent)
{
    m_d = new Private(this);
    m_d->m_itemContainer = itemContainer;
}


bool ItemContainer::isEmpty() const
{
    return m_d->m_itemContainer->isEmpty();
}


int ItemContainer::count() const
{
    return m_d->m_itemContainer->count();
}


QObject* ItemContainer::getItem(int index)
{
    qDebug() << "ShareUIDeclarative::ItemContainer::getItem" << index;

    // TODO: fix memory leak
    ShareUIDeclarative::SharedItem *si = new ShareUIDeclarative::SharedItem(m_d->m_itemContainer->getItem(index), this);
    return qobject_cast<QObject*>(si);
}

bool ItemContainer::hasSpace() const
{
    return m_d->m_itemContainer->hasSpace();
}


bool ItemContainer::isReady() const
{
    return m_d->m_itemContainer->isReady();
}


quint64 ItemContainer::totalSize() const
{
    return m_d->m_itemContainer->totalSize();
}


int ItemContainer::waitingItemsCount() const
{
    return m_d->m_itemContainer->waitingItemsCount();
}


const ShareUI::ItemContainer* ItemContainer::itemContainer()
{
    return m_d->m_itemContainer;
}

#include "itemcontainer.moc"

