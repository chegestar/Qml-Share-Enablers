
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

#ifndef SHAREUIDECLARATIVE_SHAREDITEM_H
#define SHAREUIDECLARATIVE_SHAREDITEM_H

#include "share-ui-common-declarative_global.h"

#include <QObject>
#include <QSharedPointer>


namespace ShareUI {
    class Item;
    typedef QSharedPointer<Item> SharedItem;
};

namespace ShareUIDeclarative {
    class SharedItem;
}


class SHAREUICOMMONDECLARATIVESHARED_EXPORT ShareUIDeclarative::SharedItem: public QObject {
    Q_OBJECT

    Q_PROPERTY (QString title        READ title          CONSTANT)
    Q_PROPERTY (QString description   READ description   CONSTANT)
    Q_PROPERTY (QString icon          READ icon          CONSTANT)
    Q_PROPERTY (QString thumbnail     READ thumbnail     NOTIFY thumbnailChanged)
    Q_PROPERTY (QString mimeType      READ mimeType      CONSTANT)
    Q_PROPERTY (QString toString      READ toString      CONSTANT)
    Q_PROPERTY (bool    isReady       READ isReady       NOTIFY isReadyChanged)
    Q_PROPERTY (quint64 size          READ size          CONSTANT)
    Q_PROPERTY (QString constructInfo READ constructInfo CONSTANT)

    class Private;

public:

    SharedItem(const ShareUI::SharedItem sharedItem, QObject *parent = 0);

    /*!
      \brief  Title for item. Used in UI
      \sa     ShareUI::SharedItem::title()
      \return Title to be used with item
     */
    QString title();

    /*!
      \brief  Description of item. Used in UI
      \sa     ShareUI::SharedItem::description()
      \return Description to be used with item. Default implementation will
              return empty string.
     */
    QString description();

    /*!
      \brief Icon of item. Used in UI. This is called before loadThumbnail
             slot. So it should return default icon for given type. If
             item does not need thumbails then return value this gives
             will be used.
      \sa    ShareUI::SharedItem::icon()
      \return Icon name or path to it
     */
    QString icon ();

    /*!
      \brief Path to the thumbnail for the item. Will initially return empty
             string but will request a thumbnail with default flavor, which
             will later be emitted with thumbnailChanged signal. Later requests
             will get the default flavor thumbnail
      \return file uri to the thumbnail or empty if thumbnail is not yet available
    */
    QString thumbnail();

    /*!
      \brief Mime type of Item
      \sa     ShareUI::SharedItem::mimeType()
      \return Mime type of item or empty if item doesn't have mime type.
              Default implementation will return empty.
     */
    QString mimeType();

    /*!
      \brief String presentation of item. Used as default way to share item
             forward. By default returns empty string.
      \sa    ShareUI::ShareItem::toString()
      \return String presentation of item.
     */
    QString toString();

    /*!
      \brief Item class should tell if item is ready to be shared or not. User
             can't do selection until all items are ready. By default this will
             return always true but it should be implemented for the classes
             that can't be shared until readied.
      \sa     ShareUI::SharedItem::isReady
      \return <code>true</code> if ready to be shared
     */
    bool isReady();

    /*!
      \brief Get size of item in bytes
      \return Size of item in bytes. Default implementation will return 0.
     */
    quint64 size();

    /*!
      \brief Construction information for item
      \return String given to item when generated
     */
    QString constructInfo ();


public slots:
    /*!
      \brief Slot called when item should start thumbnail loading..
      \param flavor Thumbnail flavor: currently supported should be "common",
                    "grid", "half-screen", "screen" and "video-grid". Passing
                    an empty QString will request a thumbnail with default
                    flavor.
     */
    void requestThumbnail (QString flavor = QString());


signals:

    void isReadyChanged();
    void thumbnailChanged();

    void thumbnail(QString uri);


private:
    Private *m_d;
};


#endif // SHAREUIDECLARATIVE_SHAREDITEM
