
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


#include "ShareUIDeclarative/methodbase.h"
#include "ShareUIDeclarative/itemcontainer.h"

#include <ShareUI/MethodBase>

using ShareUIDeclarative::MethodBase;

class MethodBase::Private: public QObject
{
    Q_OBJECT

public:
    Private(QObject *parent = 0);

public:

    ShareUI::MethodBase *m_methodBase;

};


MethodBase::Private::Private(QObject *parent): QObject(parent)
{
}


MethodBase::MethodBase(ShareUI::MethodBase *methodBase, QObject *parent): QObject(parent)
{
    m_d = new Private(this);
    m_d->m_methodBase = methodBase;
}

QString MethodBase::title() const
{
    return m_d->m_methodBase->title();
}


QString MethodBase::subtitle() const
{
    return m_d->m_methodBase->subtitle();
}

QString MethodBase::icon() const
{
    return m_d->m_methodBase->icon();
}


QString MethodBase::id() const
{
    return m_d->m_methodBase->id();
}


int MethodBase::order() const
{
    return m_d->m_methodBase->order();
}

void MethodBase::selected(ShareUIDeclarative::ItemContainer *items)
{
    m_d->m_methodBase->selected(items->itemContainer());
}


ShareUI::MethodBase *MethodBase::methodBase()
{
    return m_d->m_methodBase;
}

#include "methodbase.moc"

