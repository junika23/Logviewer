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

#ifndef _LOGUTILS_H_
#define _LOGUTILS_H_

#include <QString>
#include <QVector>
#include <QVariant>
#include <QList>
#include "common/SensorData.h"


class LogUtils
{
public:

    static bool parse( const QString& path, QVector< SensorData >& data );

    template< template< class > class SourceContainer,
              template< class > class ResultContainer,
              class T,
              class Fn >
    static auto transform( const SourceContainer< T >& list,
                           Fn&& fn ) -> ResultContainer< decltype( fn( T( ) ) ) >
    {
        ResultContainer< decltype( fn( T( ) ) ) > result;
        result.reserve( list.size( ) );
        for ( const T& v : list )
        {
            result += fn( v );
        }

        return result;
    }

    template< class To, class From, class Enable = void >
    struct Converter
    {
        static To convert( const From& value )
        {
            return static_cast< To >( value );
        }
    };

    template< class From >
    struct Converter< QVariant, From >
    {
        static QVariant convert( const From& value )
        {
            return qVariantFromValue( value );
        }
    };

    template< class T, class U >
    struct Converter< QList< T >, QList< U > >
    {
        static QList< T > convert( const QList< U >& value )
        {
            return transform< QList, QList >( value, []( const U& v )
            {
                return Converter< T, U >::convert( v );
            });
        }
    };

    template< class To, class From >
    static To convert( const From& value )
    {
        return Converter< To, From >::convert( value );
    }

};

#endif // _LOGUTILS_H_
