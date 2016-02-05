/*
  Copyright 2014 Auke-Dirk Pietersma
*/

#include "ximuapi/io/serial_port.h"
#include <QtSerialPort/QSerialPort>
#include <iostream>

namespace ximu{

SerialPort::SerialPort(QObject* parent):
    _active(false)
{
    qRegisterMetaType<ximu::QuaternionData>();
    qRegisterMetaType<ximu::CalInertialAndMagneticData>();
    qRegisterMetaType<ximu::SerialPort::Message>("Message");    
    connect(&_sp,&QSerialPort::readyRead,this,&SerialPort::onReadyRead);
}

void SerialPort::onReadyRead()
{
    auto recieved = _sp.readAll();
    auto ptr = reinterpret_cast<unsigned char*>(recieved.data());
    fill(ptr, recieved.size());
    read();
}

void SerialPort::open(const std::string& port, size_t baudrate){
    QMutexLocker locker(&_mutex);

    _port = QString::fromStdString(port);
    _baudtrate = baudrate;
    _timeout_msec = 50;

    _sp.setPortName(_port);
    _sp.setBaudRate(_baudtrate);
    _active = _sp.open(QIODevice::ReadWrite);
    _sp.setBaudRate(_baudtrate);
    _sp.setFlowControl(QSerialPort::HardwareControl);

    emit this->messages(_active ? Message::OPEN : Message::COULD_NOT_OPEN);
}

void SerialPort::close(){    
    _sp.close();
    emit this->messages(Message::CLOSED);
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
