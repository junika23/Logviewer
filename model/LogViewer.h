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

#ifndef _LOGVIEWER_H_
#define _LOGVIEWER_H_

#include <QQuickItem>
#include <QVector>
#include <QVariantList>

#include "common/SensorData.h"


class LogViewer : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QString logFilePath READ logFilePath WRITE setLogFilePath NOTIFY logFilePathChanged)
    Q_PROPERTY(bool loaded READ loaded NOTIFY loadedChanged)
    Q_PROPERTY(int count READ count)
    Q_PROPERTY(QVariantList sensorDataList READ sensorDataList)

public:

    explicit LogViewer( QQuickItem* parent = 0 );
    Q_INVOKABLE void parse( );
    Q_INVOKABLE QDateTime minTimestampRange( int startIdx, int endIdx );
    Q_INVOKABLE QDateTime maxTimestampRange( int startIdx, int endIdx );
    Q_INVOKABLE int minTemperatureRange( int startIdx, int endIdx );
    Q_INVOKABLE int maxTemperatureRange( int startIdx, int endIdx );
    Q_INVOKABLE double minHeightRange( int startIdx, int endIdx );
    Q_INVOKABLE double maxHeightRange( int startIdx, int endIdx );
    Q_INVOKABLE QString msEpochToString( qint64 msEpoch );

protected:

    const QString& logFilePath( ) const;
    void setLogFilePath( const QString& logFilePath );
    bool loaded( ) const;
    int count( ) const;
    QVariantList sensorDataList( ) const;

signals:

    void logFilePathChanged( );
    void loadedChanged( bool loaded );

private:

    QString m_logFilePath;
    bool m_loaded;
    QVector< SensorData > m_data;
};

#endif // _LOGVIEWER_H_
