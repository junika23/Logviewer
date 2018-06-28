// -------------------------------------------------------------------------------------------------
//
// Copyright (C) Juniarto Saputra (juniarto.wongso@gmail.com). All rights reserved.
//
// This software, including documentation, is protected by copyright controlled by
// the contributor(s). All rights are reserved. Copying, including reproducing, storing,
// adapting or translating, any or all of this material requires the prior written
// consent of the contributor(s).
//
// -------------------------------------------------------------------------------------------------

#include "model/LogViewer.h"

#include <QtWidgets/QApplication>
#include <QQmlApplicationEngine>


#define QML_LOGVIEWER_PLUGIN "LogViewer", 1, 0

// -------------------------------------------------------------------------------------------------

void registerQmlTypes( )
{
    qmlRegisterType< LogViewer >( QML_LOGVIEWER_PLUGIN, "LogViewer" );
}

// -------------------------------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    registerQmlTypes( );

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

// -------------------------------------------------------------------------------------------------

// End of file
