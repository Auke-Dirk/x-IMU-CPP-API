#ifndef SERIAL_VIEW_H_
#define SERIAL_VIEW_H_

#include <QMainWindow>
#include "ximuapi/io/serial_port.h"

namespace Ui {
class SerialView;
}

class SerialView : public QMainWindow
{
    Q_OBJECT

public:
    explicit SerialView(QWidget *parent = 0);
    ~SerialView();

private slots:
    void on_actionExit_triggered();
    void on_openClose_triggerd();
    void on_quaternion_recieved(const ximu::QuaternionData &);
    void on_calibrated_inert_mag_recieved(const ximu::CalInertialAndMagneticData &);
    void on_message_recieved(ximu::SerialPort::Message m);
    void on_text_changed();


private:
    Ui::SerialView *ui;
    ximu::SerialPort _sp;
    ximu::SerialPort::Message _state;

    static const QString OPEN_LBL;
    static const QString CLOSE_LBL;
    static const QString OPEN_FAILED_MSG;
};

#endif // SERIAL_VIEW_H_
