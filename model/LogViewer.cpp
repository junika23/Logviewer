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

#include "LogViewer.h"
#include "utils/LogUtils.h"

#include <algorithm>
#include <tuple>
#include <QDebug>


// -------------------------------------------------------------------------------------------------

LogViewer::LogViewer( QQuickItem* parent )
    : QQuickItem( parent )
    , m_loaded( false )
{
}

// -------------------------------------------------------------------------------------------------

const QString& LogViewer::logFilePath( ) const
{
    return m_logFilePath;
}

// -------------------------------------------------------------------------------------------------

void LogViewer::setLogFilePath( const QString& logFilePath )
{
    QUrl url( logFilePath );

    m_loaded = false;
    m_logFilePath = url.toLocalFile( );

    emit loadedChanged( m_loaded );
    emit logFilePathChanged( );
}

// -------------------------------------------------------------------------------------------------

bool LogViewer::loaded( ) const
{
    return m_loaded;
}

// -------------------------------------------------------------------------------------------------

int LogViewer::count( ) const
{
    return m_data.count( );
}

// -------------------------------------------------------------------------------------------------

QVariantList LogViewer::sensorDataList( ) const
{
    QList< SensorData > data = m_data.toList( );
    return LogUtils::convert< QVariantList >( data );
}

// -------------------------------------------------------------------------------------------------

void LogViewer::parse( )
{
    if ( m_logFilePath.isEmpty( ) )
    {
        return;
    }

    m_data.clear( );

    if ( !LogUtils::parse( m_logFilePath, m_data ) )
    {
        qWarning() << "Error while parsing: " << m_logFilePath;
    }

    m_loaded = true;
    emit loadedChanged( m_loaded );
}

// -------------------------------------------------------------------------------------------------

QDateTime LogViewer::minTimestampRange( int startIdx, int endIdx )
{
    if ( endIdx > startIdx )
    {
        auto min = std::min_element( m_data.begin( ) + startIdx,
                                     m_data.begin( ) + endIdx,
                                     [] ( const SensorData& data1, const SensorData& data2 ) {
            return data1.timestamp( ) < data2.timestamp( );
        });

        return min->timestamp( );
    }

    return QDateTime( );
}

// -------------------------------------------------------------------------------------------------

QDateTime LogViewer::maxTimestampRange( int startIdx, int endIdx )
{
    if ( endIdx > startIdx )
    {
        auto min = std::max_element( m_data.begin( ) + startIdx,
                                     m_data.begin( ) + endIdx,
                                     [] ( const SensorData& data1, const SensorData& data2 ) {
            return data1.timestamp( ) < data2.timestamp( );
        });

        return min->timestamp( );
    }

    return QDateTime( );
}

// -------------------------------------------------------------------------------------------------

int LogViewer::minTemperatureRange( int startIdx, int endIdx )
{
    if ( endIdx > startIdx )
    {
        auto min = std::min_element( m_data.begin( ) + startIdx,
                                     m_data.begin( ) + endIdx,
                                     [] ( const SensorData& data1, const SensorData& data2 ) {
            return data1.temperature( ) < data2.temperature( );
        });

        return min->temperature( );
    }

    return 0;
}

// -------------------------------------------------------------------------------------------------

int LogViewer::maxTemperatureRange( int startIdx, int endIdx )
{
    if ( endIdx > startIdx )
    {
        auto max = std::max_element( m_data.begin( ) + startIdx,
                                     m_data.begin( ) + endIdx,
                                     [] ( const SensorData& data1, const SensorData& data2 ) {
            return data1.temperature( ) < data2.temperature( );
        });

        return max->temperature( );
    }

    return 0;
}

// -------------------------------------------------------------------------------------------------

double LogViewer::minHeightRange( int startIdx, int endIdx )
{
    if ( endIdx > startIdx )
    {
        auto min = std::min_element( m_data.begin( ) + startIdx,
                                     m_data.begin( ) + endIdx,
                                     [] ( const SensorData& data1, const SensorData& data2 ) {
            return data1.height( ) < data2.height( );
        });

        return min->height( );
    }

    return 0;
}

// -------------------------------------------------------------------------------------------------

double LogViewer::maxHeightRange( int startIdx, int endIdx )
{
    if ( endIdx > startIdx )
    {
        auto max = std::max_element( m_data.begin( ) + startIdx,
                                     m_data.begin( ) + endIdx,
                                     [] ( const SensorData& data1, const SensorData& data2 ) {
            return data1.height( ) < data2.height( );
        });

        return max->height( );
    }

    return 0;
}

// -------------------------------------------------------------------------------------------------

QString LogViewer::msEpochToString( qint64 msEpoch )
{
    QDateTime dt;
    dt.setMSecsSinceEpoch( msEpoch );
    return dt.toString( "hh:mm:ss" );
}

// -------------------------------------------------------------------------------------------------

// End of file
