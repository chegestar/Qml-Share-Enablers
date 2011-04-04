
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


#include "ShareUIDeclarative/shareditem.h"
#include "ShareUIDeclarative/itemmodel.h"
#include "ShareUIDeclarative/itemcontainer.h"

#include <ShareUI/ItemContainer>

#include <QDebug>

using ShareUIDeclarative::ItemModel;

class ItemModel::Private : public QObject
{
    Q_OBJECT

public:
    Private(QObject *parent = 0);

public:
    ShareUI::ItemContainer* m_items;
};


ItemModel::Private::Private(QObject *parent) : QObject(parent)
{

}


ItemModel::ItemModel(ShareUI::ItemContainer* items, QObject *parent) : QAbstractListModel(parent)
{
    m_d = new Private(this);

    m_d->m_items = items;

    QHash<int, QByteArray> roles;
    roles[ItemRole] = "item";
    setRoleNames(roles);

}

QVariant ItemModel::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(index);

    if (index.row() < 0 || index.row() >= m_d->m_items->count()) {
        qWarning() << "ItemModel::data: invalid index row: " << index.row();
        return QVariant();
    }


    if ( role == ItemRole ) {
        ShareUIDeclarative::SharedItem* i = new ShareUIDeclarative::SharedItem(m_d->m_items->getItem(index.row()));
        QObject *qi = qobject_cast<QObject*>(i);
        return QVariant(qi);
    }


    return QVariant();
}

int ItemModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return 0;
}

#include "itemmodel.moc"
