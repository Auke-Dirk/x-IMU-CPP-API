#include <QtCore>
#include <QApplication>
#include <QCoreApplication>
#include <ximuapi/io/serial_port.h>
#include <iostream>

class DisplaySink : public QObject
{
public slots:
    void recievedQuaternionData(const ximu::QuaternionData& q)
    {
        std::cout << "w:" << q.w() << " x: " << q.x() << " y: " << q.y() << " z: " << q.z()  << "\r" << std::flush;
    }
};

int main(int argc, char *argv[])
{
    std::cout.precision(5);

    QApplication a(argc, argv);

    if (a.arguments().size() != 2)
    {
        std::cout << "comport missing:  example XIMU_CONSOLE /dev/ttyUSB0" << std::endl;
        return 0;
    }

    ximu::SerialPort sp;
    sp.open(std::string(a.arguments().at(1).toStdString()),115200);
    DisplaySink dp;
    DisplaySink::connect(&sp,&ximu::SerialPort::quaternion,&dp,&DisplaySink::recievedQuaternionData);

    int ret = a.exec();
    return ret;
}
