/*
 * This file is part of Handset UX Share user interface
 *
 * Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies). All rights reserved.
 * Contact: Jukka Tiihonen <jukka.tiihonen@nokia.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to 
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense,     
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER  
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS  
 * IN THE SOFTWARE. 
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
