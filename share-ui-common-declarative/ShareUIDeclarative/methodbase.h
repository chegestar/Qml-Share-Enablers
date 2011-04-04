
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


#ifndef SHAREUIDECLARATIVE_METHODBASE_H
#define SHAREUIDECLARATIVE_METHODBASE_H

#include "share-ui-common-declarative_global.h"

#include <QObject>
#include <QSharedPointer>


namespace ShareUI {
    class MethodBase;
};

namespace ShareUIDeclarative {
    class MethodBase;
    class ItemContainer;
}


class SHAREUICOMMONDECLARATIVESHARED_EXPORT ShareUIDeclarative::MethodBase: public QObject {
    Q_OBJECT

    Q_PROPERTY(QString title    READ title    CONSTANT)
    Q_PROPERTY(QString subtitle READ subtitle CONSTANT)
    Q_PROPERTY(QString icon     READ icon     CONSTANT)
    Q_PROPERTY(QString id       READ id       CONSTANT)
    Q_PROPERTY(int     order    READ order    CONSTANT)

    class Private;

public:
    MethodBase(ShareUI::MethodBase *methodBase, QObject *parent = 0);


    /*!
      \brief Title for the method. For example "Facebook" or "Email".
             Function has to be implemented by method and it must return
             valid title to be shown with method.
      \return Method title.
     */
    QString title () const;

    /*!
      \brief Subtitle for the method. For example "username".
             Subtitles might be ignored in future UIs for some methods.
      \return Method subtitle. In default implementation empty string.
     */
    QString subtitle () const;

    /*!
      \brief Icon for the method
      \return Method icon. Can be name of icon or filepath to icon.
              In default implementation empty string that is same as no
              icon.
     */
    QString icon () const;

    /*!
      \brief ID for method. This is useful for applications using Method
             plugins directly. For example id of email method is
             "com.meego.email".
      \return ID string if defined by implementing class. By default empty
              string.
     */
    QString id () const;

    /*!
      \brief Ordering value for item. This is only used with TYPE_PROMOTED
             methods. For other types it is not used. Just keep the default
             implementation.
      \return Order value for method. Methods with higher order values are
              before methods with lower order values. Default value is
              0.
     */
    int order () const;

    ShareUI::MethodBase *methodBase();

public slots:

    /*!
      \brief Method has been selected
      \sa    ShareUI::MethodBase::selected(ShareUI::ItemContainer* items)
    */
    void selected(ShareUIDeclarative::ItemContainer* items);


private:
    Private *m_d;
};

#endif // SHAREUIDECLARATIVE_SHAREDITEM
