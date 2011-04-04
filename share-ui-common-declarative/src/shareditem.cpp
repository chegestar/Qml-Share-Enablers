
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

#include <ShareUI/Item>
#include <ShareUI/FileItem>
#include <QDebug>
#include <thumbnailer/Thumbnailer>
#include <QIcon>

using ShareUIDeclarative::SharedItem;

class SharedItem::Private: public QObject
{
    Q_OBJECT

public:
    Private(QObject *parent = 0);
    ~Private();

    // given a file path or uri, tries to guess mimeType based on the file
    // suffix
    QString parameterToMime(const QString& param);

public slots:
    void thumbnail(QUrl uri, QUrl thumbnailUri, QPixmap pixmap, QString flavor);
    void error (QString error, QUrl uri);

signals:
    void thumbnail(QString uri);
    void thumbnailChanged();

public:
    ShareUI::SharedItem m_sharedItem;
    Thumbnails::Thumbnailer* m_thumbnailer;

    // flavor, uri pairs
    QHash<QString, QString> m_thumbnails;
};


SharedItem::Private::Private(QObject *parent):
    QObject(parent), m_sharedItem(0), m_thumbnailer(new Thumbnails::Thumbnailer())
{
}

SharedItem::Private::~Private() {
    delete m_thumbnailer;
    m_thumbnailer = 0;
}

void SharedItem::Private::thumbnail(
    QUrl uri,
    QUrl thumbnailUri,
    QPixmap pixmap,
    QString flavor)
{
    Q_UNUSED(pixmap)
    Q_UNUSED(uri)

    qDebug() << "SharedItem::Private::thumbnail, flavor:" << flavor
             << "thumbnailUri:" << thumbnailUri;

    // store the thumbnail uri
    m_thumbnails[flavor] = thumbnailUri.toString();

    // let the world know we do have a new thumbnail
    emit thumbnail(thumbnailUri.toString());

    // a special case is when the thumbnail flavor is default because this is
    // used on thumbnail property
    if (Thumbnails::Thumbnailer::defaultFlavor == flavor) {
        qDebug() << "SharedItem::Private::thumbnail: emiting thumbnailChanged";
        emit thumbnailChanged();
    }
}

// TODO: can or should we really do anything else?
void SharedItem::Private::error(QString error, QUrl uri)
{
    qWarning() << "SharedItem::Private::error" << error << uri;
}

// shamelessly stolen from thumbnailer-simple example of libthumbnailer...
QString SharedItem::Private::parameterToMime(const QString& param) {
    static QHash<QString, QString> mimes;
    if(mimes.count() <= 0) {
        mimes.insert(".jpeg", "image/jpeg");
        mimes.insert(".jpg",  "image/jpeg");
        mimes.insert(".gif",  "image/gif");
        mimes.insert(".png",  "image/png");
        mimes.insert(".bmp",  "image/bmp");
        mimes.insert(".tif",  "image/tiff");
        mimes.insert(".tiff", "image/tiff");

        mimes.insert(".avi",  "video/x-msvideo");
        mimes.insert(".mpg",  "video/mpeg");
        mimes.insert(".mpeg", "video/mpeg");
        mimes.insert(".mpga", "video/mpeg");
        mimes.insert(".mpe",  "video/mpeg");
        mimes.insert(".mpa",  "video/mpeg");
        mimes.insert(".mp2",  "video/mpeg");
        mimes.insert(".mp4",  "video/mp4");
        mimes.insert(".3gp",  "video/3gpp");
    }

    foreach(QString mime, mimes.keys()) {
        if(param.endsWith(mime, Qt::CaseInsensitive)) {
            return mimes[mime];
        }
    }

    return QString();
}


SharedItem::SharedItem(const ShareUI::SharedItem sharedItem, QObject *parent):
    QObject(parent), m_d(new Private(this))
{
    m_d->m_sharedItem = sharedItem;

    connect(m_d->m_thumbnailer, SIGNAL(thumbnail(QUrl,QUrl,QPixmap,QString)),
            m_d, SLOT(thumbnail(QUrl,QUrl,QPixmap,QString)));

    connect(m_d->m_thumbnailer, SIGNAL(error(QString,QUrl,QUrl,QPixmap)),
            m_d, SLOT(error(QString,QUrl)));


    // forward signals from private
    connect(m_d, SIGNAL(thumbnail(QString)), this, SIGNAL(thumbnail(QString)));
    connect(m_d, SIGNAL(thumbnailChanged()), this, SIGNAL(thumbnailChanged()));

    // if item emits ready(), it should have before returned false for isReady
    // and now it has changed.
    connect(m_d->m_sharedItem.data(),
            SIGNAL(ready()),
            this,
            SIGNAL(isReadyChanged()));
}


QString SharedItem::title()
{
    return m_d->m_sharedItem.data()->title();
}


QString SharedItem::description()
{
    return m_d->m_sharedItem.data()->description();
}


QString SharedItem::icon()
{    
    return m_d->m_sharedItem.data()->icon();
}


QString SharedItem::thumbnail()
{
    qDebug() << "SharedItem::thumbnail";
    // if we have default thumbie, return it straight away,
    // this avoids thumbnail()->thumbnailChanged()->thumbnail()... loops
    if (m_d->m_thumbnails.keys().contains(Thumbnails::Thumbnailer::defaultFlavor)) {
        qDebug() << "SharedItem::thumbnail: shortcut return"
                 << m_d->m_thumbnails[Thumbnails::Thumbnailer::defaultFlavor];
        return m_d->m_thumbnails[Thumbnails::Thumbnailer::defaultFlavor];
    }

    // request default flavor thumbnail and return empty string, later on
    // thumbnail signal will provide the real path
    requestThumbnail();
    return QString ("");
}


QString SharedItem::mimeType()
{
    return m_d->m_sharedItem.data()->mimeType();
}


QString SharedItem::toString()
{
    return m_d->m_sharedItem.data()->toString();
}


bool SharedItem::isReady()
{
    return m_d->m_sharedItem.data()->isReady();
}


quint64 SharedItem::size()
{
    return m_d->m_sharedItem.data()->size();
}


QString SharedItem::constructInfo()
{
    return m_d->m_sharedItem.data()->constructInfo();
}


void SharedItem::requestThumbnail(QString flavor)
{
    qDebug() << "SharedItem::requestThumbnail" << flavor;

    // requesting thumbnails is meaningful only for fileitems
    ShareUI::FileItem* fileItem = ShareUI::FileItem::toFileItem(m_d->m_sharedItem);

    if (fileItem == 0) {
        qWarning() << "SharedItem::requestThumbnail: "
                   << m_d->m_sharedItem.data()
                   << "is not FileItem";
        return;
    }

    QUrl uri = fileItem->URI();

    // try to use mime type from fileItem and rollback to SharedItem::Private,
    // note that it too may be empty but at least we tried :)
    QString mimeType = fileItem->mimeType();
    if (mimeType.isEmpty()) {
        mimeType = m_d->parameterToMime(uri.toString());
    }

    // make sure given flavor is supported, otherwise use the default flavor
    QStringList supported = Thumbnails::Thumbnailer::getFlavors();

    if (flavor.trimmed() != Thumbnails::Thumbnailer::defaultFlavor &&
        supported.indexOf(flavor.trimmed()) == -1)
    {
        qWarning() << "SharedItem::requestThumbnail: flavor" << flavor
                   << "is not in supported flavors:" << supported;

        flavor = Thumbnails::Thumbnailer::defaultFlavor;
        qDebug()   << "SharedItem::requestThumbnail: using default flavor"
                   << flavor;
    }

    QList<QUrl> uris;
    uris << uri;
    QStringList mimeTypes;
    mimeTypes << mimeType;

    bool madeRequest = m_d->m_thumbnailer->request(uris, mimeTypes, false, flavor.trimmed());

    // if request wasn't made, then the thumbnail is already requested.
    // in this case we might already know the thumbnail uri for the requested
    // flavor.
    if (!madeRequest) {
        qDebug() << "SharedItem::requestThumbnail: thumbnails were ready before request";

        if ( m_d->m_thumbnails.keys().contains(flavor.trimmed())) {
            emit thumbnail(m_d->m_thumbnails[flavor.trimmed()]);
        }

    }
}

#include "shareditem.moc"

