/*
  Copyright 2014 Auke-Dirk Pietersma
*/

#include "ximuapi/io/serial_port.h"

#include <QtSerialPort/QSerialPort>

namespace ximu{

SerialPort::SerialPort(QObject* parent)
    : QThread(parent),_active(false)
{
    qRegisterMetaType<ximu::QuaternionData>();
    qRegisterMetaType<ximu::CalInertialAndMagneticData>();
    qRegisterMetaType<ximu::SerialPort::Message>("Message");
}

void SerialPort::open(const std::string& port, size_t baudrate){
    QMutexLocker locker(&_mutex);

    _port = QString::fromStdString(port);
    _baudtrate = baudrate;
    _timeout_msec = 50;

    if (!isRunning())
        start();
}

void SerialPort::close(){
    _active = false;
}


void SerialPort::run(){
    _mutex.lock();

    QSerialPort sp;
    sp.setPortName(_port);
    sp.setBaudRate(_baudtrate);

    _active = sp.open(QIODevice::ReadWrite);

    if (!_active){
        emit this->messages(Message::COULD_NOT_OPEN);                  
    }
    else
    {
        emit this->messages(Message::OPEN);
        while(_active){
            if (sp.waitForReadyRead(_timeout_msec)) {
                auto recieved = sp.readAll();

                // ximu::BaseReader
                fill(recieved.begin(), recieved.end());
                read();
            }
        }
        emit this->messages(Message::CLOSED);
    }
    _mutex.unlock();
}

void SerialPort::recievedQuaternionData(ximu::QuaternionData& q)
{
    emit this->quaternion(q);
}

void SerialPort::recievedCalInertialAndMagneticData
(ximu::CalInertialAndMagneticData& data)
{
    emit this->calibratedInertialAndMagneticData(data);
}

} // namesapce ximu
