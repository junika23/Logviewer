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

#include "LogUtils.h"

#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>

const QString TIMESTAMP = "timestamp";
const QString TEMPERATURE = "temperature";
const QString HEIGHT = "height";

// -------------------------------------------------------------------------------------------------

bool LogUtils::parse( const QString& path, QVector< SensorData >& data )
{
    bool success = false;
    QFileInfo fileInfo( path );

    if ( !fileInfo.exists( ) )
    {
        return success;
    }

    QFile file( path );
    if ( file.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        QJsonParseError jsonError;
        QJsonDocument doc = QJsonDocument::fromJson( file.readAll( ), &jsonError );
        if ( doc.isNull( ) )
        {
            qWarning() << "Error while parsing: " << path <<
                          " with error: " << jsonError.errorString( ) <<
                          " and offset: " << jsonError.offset;
        }
        else if ( doc.isEmpty( ) )
        {
            qWarning() << "File: " << path << " is empty";
        }
        if ( doc.isArray( ) )
        {
            QJsonArray jsonArray = doc.array( );

            for ( QJsonArray::iterator it = jsonArray.begin();
                  it != jsonArray.end(); ++it )
            {
                SensorData sensorData;
                QJsonObject obj = it->toObject( );
                if ( obj.contains( TIMESTAMP ) && obj[ TIMESTAMP ].isString( ) )
                {
                    sensorData.setTimestamp(
                                QDateTime::fromString( obj[ TIMESTAMP ].toString( ),
                                                       Qt::ISODate ) );
                }
                if ( obj.contains( TEMPERATURE ) && obj[ TEMPERATURE ].isString( ) )
                {
                    const QString tmp = obj[ TEMPERATURE ].toString( );
                    sensorData.setTemperature( tmp.toInt( ) );
                }
                if ( obj.contains( HEIGHT ) && obj[ HEIGHT ].isDouble( ) )
                {
                    sensorData.setHeight( obj[ HEIGHT ].toDouble( ) );
                }

                if ( !sensorData.isValid( ) )
                {
                    qWarning() << "Sensor data is invalid";
                }

                data.push_back( sensorData );
            }

            success = true;
        }

        file.close( );
    }

    return success;
}

// -------------------------------------------------------------------------------------------------


// -------------------------------------------------------------------------------------------------


// End of file
