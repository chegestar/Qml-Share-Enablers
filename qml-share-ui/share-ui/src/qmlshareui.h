/* This file is part of qml-share-ui
 *
 * Copyright © 2010 Nokia Corporation and/or its subsidiary(-ies).
 * All rights reserved.
 * Contact: Jukka Tiihonen <jukka.t.tiihonen@nokia.com>
 *
 * This software, including documentation, is protected by copyright controlled
 * by Nokia Corporation. All rights are reserved. Copying, including
 * reproducing, storing, adapting or translating, any or all of this material
 * requires the prior written consent of Nokia Corporation. This material also
 * contains confidential information which may not be disclosed to others
 * without the prior written consent of Nokia.
 */

#ifndef _QML_SHARE_UI_IMPLEMENTATION_H_
#define _QML_SHARE_UI_IMPLEMENTATION_H_

#include <QObject>
#include <ShareWidgets/UiImplementationBase>

// Forward declarations
//class MApplicationWindow;

class QMainWindow;

/*!
  \class QMLShareUi
  \brief QML way UI implementation for Share UI interfaces
 */
class QMLShareUi : public ShareWidgets::UiImplementationBase {
Q_OBJECT

public:

    QMLShareUi (QObject * parent = 0);
    virtual ~QMLShareUi();

    //!\reimp
    virtual QApplication * application (int & argc, char ** argv);
    
    virtual bool showUI (ShareUI::PluginLoader * loader,
        const ShareUI::ItemContainer * container);
    //!\reimp_end

public Q_SLOTS:
    /*!
        \brief Slot to close a window
    */
    void closeWindow();

private:
    QApplication *m_application;
    QMainWindow *m_mainWindow;

};

#endif
