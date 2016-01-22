/*
  Copyright 2014 Auke-Dirk Pietersma
*/

#ifndef INCLUDE_XIMUAPI_IO_SERIAL_PORT_H_
#define INCLUDE_XIMUAPI_IO_SERIAL_PORT_H_


#include "ximuapi/serialization/reader_base.h"

#include <QMutex>
#include <QThread>
#include <QWaitCondition>

namespace ximu{

/*! \brief SerialPort implementation.
 *         Lightweight SerialPort wrapper around the QSerialPort
 *
 *  Whenever QT5 is installed, the SerialPort class will become available
 *  in API. The SerialPort implementation is nothing more than a thin wrapper
 *  around the QSerialPort
 */
class SerialPort : public QThread, public ReaderBase{
    Q_OBJECT
public:
    enum Message {OKE, COULD_NOT_OPEN, CLOSED, OPEN };
    SerialPort(QObject* parent = 0 );
    void open(const std::string& port, size_t baudrate);
    void close();

signals:
    void quaternion(const ximu::QuaternionData& q);
    void calibratedInertialAndMagneticData(const ximu::CalInertialAndMagneticData& d);
    void messages (Message msg);

protected:
    void run();

private:
    QMutex _mutex;
    QString _port;

    bool _active;
    size_t _baudtrate;
    size_t _timeout_msec;

    virtual void recievedQuaternionData(ximu::QuaternionData& q);
    virtual void recievedCalInertialAndMagneticData(ximu::CalInertialAndMagneticData& d);
};

} // namesapce ximu

Q_DECLARE_METATYPE(ximu::QuaternionData)
Q_DECLARE_METATYPE(ximu::QuaternionData*)
Q_DECLARE_METATYPE(ximu::CalInertialAndMagneticData)
Q_DECLARE_METATYPE(ximu::CalInertialAndMagneticData*)
Q_DECLARE_METATYPE(ximu::SerialPort::Message)

#endif //  INCLUDE_XIMUAPI_IO_SERIAL_PORT_H_
