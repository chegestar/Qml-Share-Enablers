
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


#ifndef SHAREUIDECLARATIVE_ITEMCONTAINER_H
#define SHAREUIDECLARATIVE_ITEMCONTAINER_H

#include "share-ui-common-declarative_global.h"

#include <QObject>
#include <QList>


namespace ShareUI {
    class ItemContainer;
}

namespace ShareUIDeclarative {
    class ItemContainer;
    class SharedItem;
}


class SHAREUICOMMONDECLARATIVESHARED_EXPORT ShareUIDeclarative::ItemContainer: public QObject {
    Q_OBJECT

    Q_PROPERTY(bool   isEmpty   READ isEmpty   NOTIFY isEmptyChanged)
    Q_PROPERTY(int    count     READ count     NOTIFY countChanged)
    Q_PROPERTY(int    hasSpace  READ hasSpace  NOTIFY hasSpaceChanged)
    Q_PROPERTY(int    isReady   READ isReady   NOTIFY isReadyChanged)
    Q_PROPERTY(qint64 totalSize READ totalSize NOTIFY totalSizeChanged)

    Q_PROPERTY(int  waitingItemsCount READ waitingItemsCount NOTIFY waitingItemsCountChanged)

    // TODO: a list model for items
    //Q_PROPERTY(ShareUIDeclarative::ItemModel* items READ items NOTIFY itemsChanged)

    class Private;

public:
    ItemContainer(const ShareUI::ItemContainer *itemContainer, QObject *parent = 0);


    /*!
      \brief If container is empty
      \return <code>true</code> if container is empty
     */
    bool isEmpty() const;

    /*!
      \brief Number or items in container
      \return Number of items in container
     */
    int count() const;

    /*!
      \brief Get item at given index
      \note  Returns a QObject* because of qml limitations, will be seen as
             ShareUIDeclarative::SharedItem* at qml side, though.
      \param index: Index of required item
      \return ShareUIDeclarative::SharedItem* at given index
     */
    Q_INVOKABLE QObject* getItem (int index);

    /*!
      \brief Function to check if there is still free space for new items in
             the container
      \return <code>true</code> if container is not full
     */
    bool hasSpace() const;

    /*!
      \brief To check if all items are ready to be shared. Signal itemsReady
             is emitted only after this function is called and it has
             returned <code>false</code>.
      \return <code>true</code> if items are ready
     */
    bool isReady() const;

    /*!
      \brief Get total size of all items in container
      \return Total size of items in bytes when all items are ready. If
              asked before that will always return 0.
     */
    quint64 totalSize() const;

    /*!
      \brief Get count of items not fully processed yet
      \return Count of items not fully processed
     */
    int waitingItemsCount () const;

    /*!
      \brief Get pointer to the ShareUI::ItemContainer wrapped inside this
             ShareUIDeclarative::ItemContainer
      \return ItemContainer inside this wrapper
     */
    const ShareUI::ItemContainer *itemContainer();

signals:
    /*!
      \brief Signal emitted when container items are changed. This happens
             if items are added or removed from the container.
     */
    void changed ();

    /*!
      \brief Signal emitted when all items are ready
     */
    void itemsReady();


    // declarare as signals, but i'm not sure whether these can be guarantee to
    // be emited at proper times...
    void isEmptyChanged();
    void countChanged();
    void hasSpaceChanged();
    void isReadyChanged();
    void totalSizeChanged();
    void waitingItemsCountChanged();


private:
    Private *m_d;
};

#endif // SHAREUIDECLARATIVE_ITEMCONTAINER_H
