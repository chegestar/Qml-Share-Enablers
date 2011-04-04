
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


#ifndef SHAREUIDECLARATIVE_ITEMMODEL_H
#define SHAREUIDECLARATIVE_ITEMMODEL_H

#include "share-ui-common-declarative_global.h"

#include <QAbstractListModel>


namespace ShareUI {
    class ItemContainer;
}

namespace ShareUIDeclarative {
    class ItemModel;
}

class SHAREUICOMMONDECLARATIVESHARED_EXPORT ShareUIDeclarative::ItemModel : public QAbstractListModel
{

    class Private;

public:

    enum roles {
        ItemRole = Qt::UserRole + 1
    };

    ItemModel(ShareUI::ItemContainer* items, QObject *parent = 0);
    virtual ~ItemModel() {}

    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual int rowCount(const QModelIndex &parent) const;

private:

    Private *m_d;
};


#endif //SHAREUIDECLARATIVE_ITEMMODEL_H
