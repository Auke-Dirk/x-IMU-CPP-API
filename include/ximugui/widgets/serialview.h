#ifndef SERIAL_VIEW_H_
#define SERIAL_VIEW_H_

#include <QMainWindow>
#include <QVector>
#include <memory>
#include "ximuapi/io/serial_port.h"
#include "ximugui/widgets/ximuwidget_iplugin_factory.h"
#include <QThread>

namespace Ui {
class SerialView;
}

class SerialView : public QMainWindow
{
    Q_OBJECT

public:
    explicit SerialView(QWidget *parent = 0);
    ~SerialView();
    void loadPlugins();

private slots:
    void on_actionExit_triggered();
    void on_openClose_triggerd();
    void on_quaternion_recieved(const ximu::QuaternionData &);
    void on_calibrated_inert_mag_recieved(const ximu::CalInertialAndMagneticData &);
    void on_message_recieved(ximu::SerialPort::Message m);
    void on_text_changed();    

protected:
    void changeEvent(QEvent *event);

private:
    Ui::SerialView *ui;
    ximu::SerialPort _sp;    
    ximu::SerialPort::Message _state;    
    std::vector<std::unique_ptr<XimuWidgetIPluginFactory>> _plugins;

};

#endif // SERIAL_VIEW_H_
