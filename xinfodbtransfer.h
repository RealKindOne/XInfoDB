/* Copyright (c) 2022-2024 hors<horsicq@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef XINFODBTRANSFER_H
#define XINFODBTRANSFER_H

#include "xformats.h"
#include "xinfodb.h"

class XInfoDBTransfer : public QObject {
    Q_OBJECT
public:
    explicit XInfoDBTransfer(QObject *pParent = nullptr);

    enum COMMAND {
        COMMAND_UNKNOWN = 0,
        COMMAND_ANALYZEALL,
        COMMAND_ANALYZE,
        COMMAND_SYMBOLS,  // TODO reload
        COMMAND_DISASM,
        COMMAND_REMOVE,
        COMMAND_CLEAR,
        COMMAND_EXPORT,
        COMMAND_IMPORT,
        COMMAND_SCANFORIAT,
        COMMAND_GETIAT
    };

    struct OPTIONS {
        XBinary::FT fileType;
        QString sFileName;
        QIODevice *pDevice;
        XADDR nAddress;
        qint64 nSize;
        qint64 nCount;
#ifdef USE_XPROCESS
        X_ID nProcessID;
#endif
    };

    struct RESULT {
        XADDR nAddress;
        qint64 nSize;
    };

    void setData(XInfoDB *pXInfoDB, COMMAND transferType, const OPTIONS &options, XBinary::PDSTRUCT *pPdStruct);
    void setData(COMMAND transferType, const OPTIONS &options, RESULT *pResult, XBinary::PDSTRUCT *pPdStruct);
#ifdef USE_XPROCESS
#ifdef Q_OS_WIN
    void setData(COMMAND transferType, const OPTIONS &options, QList<XPE::IMPORT_RECORD> *pListImports, XBinary::PDSTRUCT *pPdStruct);
#endif
#endif
    //    bool loadFromFile(const QString &sFileName,XBinary::FT fileType);

public slots:
    bool process();

signals:
    void errorMessage(const QString &sText);
    void completed(qint64 nElapsed);

private:
    XInfoDB *g_pXInfoDB;
    COMMAND g_transferType;
    OPTIONS g_options;
    RESULT *g_pResult;
    XBinary::PDSTRUCT *g_pPdStruct;
#ifdef USE_XPROCESS
#ifdef Q_OS_WIN
    QList<XPE::IMPORT_RECORD> *g_pListImports;
#endif
#endif
};

#endif  // XINFODBTRANSFER_H
