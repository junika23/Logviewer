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

#include "SensorData.h"

#include <climits>
#include <cfloat>


// -------------------------------------------------------------------------------------------------

SensorData::SensorData( )
    : m_temperature( INT_MIN )
    , m_height( DBL_MIN )
{
}

// -------------------------------------------------------------------------------------------------

SensorData::SensorData( const SensorData& other )
{
    m_timestamp = other.timestamp( );
    m_temperature = other.temperature( );
    m_height = other.height( );
}

// -------------------------------------------------------------------------------------------------

SensorData::~SensorData( )
{
    m_timestamp = QDateTime( );
    m_temperature = INT_MIN;
    m_height = DBL_MIN;
}

// -------------------------------------------------------------------------------------------------

QDateTime SensorData::timestamp( ) const
{
    return m_timestamp;
}

// -------------------------------------------------------------------------------------------------

void SensorData::setTimestamp( const QDateTime& timestamp )
{
    m_timestamp = timestamp;
}

// -------------------------------------------------------------------------------------------------

int SensorData::temperature( ) const
{
    return m_temperature;
}

// -------------------------------------------------------------------------------------------------

void SensorData::setTemperature( int temperature )
{
    m_temperature = temperature;
}

// -------------------------------------------------------------------------------------------------

double SensorData::height( ) const
{
    return m_height;
}

// -------------------------------------------------------------------------------------------------

void SensorData::setHeight( double height )
{
    m_height = height;
}

// -------------------------------------------------------------------------------------------------

bool SensorData::isValid( ) const
{
    return ( m_temperature != INT_MIN &&
            m_height != DBL_MIN &&
            m_timestamp.isValid( ) );
}

// End of file
