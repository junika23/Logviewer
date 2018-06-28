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

#ifndef _SENSORDATA_H_
#define _SENSORDATA_H_

#include <QObject>
#include <QDateTime>


class SensorData
{
    Q_GADGET
    Q_PROPERTY(QDateTime timestamp READ timestamp)
    Q_PROPERTY(int temperature READ temperature)
    Q_PROPERTY(double height READ height)

public:

    SensorData( );

    SensorData( const SensorData& other );

    ~SensorData( );

    QDateTime timestamp( ) const;

    void setTimestamp( const QDateTime& timestamp );

    int temperature( ) const;

    void setTemperature( int temperature );

    double height( ) const;

    void setHeight( double height );

    bool isValid( ) const;

private:

    QDateTime m_timestamp;
    int m_temperature;
    double m_height;
};

Q_DECLARE_METATYPE( SensorData )

#endif // _SENSORDATA_H_
