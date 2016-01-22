#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QPlainTextEdit>
#include <QTextStream>
#include <sstream>
#include "ximugui/widgets/serialview.h"
#include "ui_serialview.h"

const QString SerialView::OPEN_LBL = "open";
const QString SerialView::CLOSE_LBL = "close";
const QString SerialView::OPEN_FAILED_MSG = "[ERR] Could not open port";

SerialView::SerialView(QWidget *parent) :
    QMainWindow(parent),
    _state(ximu::SerialPort::Message::OKE),
    ui(new Ui::SerialView)
{    
    ui->setupUi(this);

    ui->comboBoxBaudRates->addItem("1200", QVariant(1200));
    ui->comboBoxBaudRates->addItem("2400", QVariant(2400));
    ui->comboBoxBaudRates->addItem("4800", QVariant(4800));
    ui->comboBoxBaudRates->addItem("9600", QVariant(9600));
    ui->comboBoxBaudRates->addItem("19200", QVariant(19200));
    ui->comboBoxBaudRates->addItem("38400", QVariant(38400));
    ui->comboBoxBaudRates->addItem("57600", QVariant(57600));
    ui->comboBoxBaudRates->addItem("115200", QVariant(115200));

    for (auto& port : QSerialPortInfo::availablePorts())
        ui->comboBoxPortNames->addItem(port.portName());

    // gui::button open/close
    connect(this->ui->pushButtonOnOff, &QPushButton::clicked,this, &SerialView::on_openClose_triggerd);

    // serialport::quaternion
    connect(&_sp,&ximu::SerialPort::quaternion,this,&SerialView::on_quaternion_recieved);

    connect(this->ui->textArea,&QPlainTextEdit::textChanged,this,&SerialView::on_text_changed);

    //serialport::interial magnetic
    connect(&_sp,&ximu::SerialPort::calibratedInertialAndMagneticData,
            this,&SerialView::on_calibrated_inert_mag_recieved);

    // serialport::messages
    connect(&_sp,&ximu::SerialPort::messages,this,&SerialView::on_message_recieved);

    ui->pushButtonOnOff->setText(OPEN_LBL);
}

SerialView::~SerialView()
{
    delete ui;
}

void SerialView::on_actionExit_triggered()
{
    this->close();
}

void SerialView::on_text_changed(){
    if (ui->textArea->document()->lineCount() > 100)
        ui->textArea->clear();
}

void SerialView::on_openClose_triggerd()
{
    switch (_state)
    {
        case ximu::SerialPort::Message::OKE:
        case ximu::SerialPort::Message::CLOSED:
        case ximu::SerialPort::Message::COULD_NOT_OPEN:
        {
            _sp.open(
                ui->comboBoxPortNames->currentText().toStdString(),
                ui->comboBoxBaudRates->currentData().toInt()
            );
        }
        case ximu::SerialPort::OPEN:
        {
            _sp.close();
        }
    }
}

void SerialView::on_message_recieved(ximu::SerialPort::Message m)
{
    _state = m;
    switch (_state)
    {
        case ximu::SerialPort::Message::OPEN:
            ui->comboBoxPortNames->setEnabled(false);
            ui->comboBoxBaudRates->setEnabled(false);
            ui->pushButtonOnOff->setText(CLOSE_LBL);
        break;

        case ximu::SerialPort::Message::CLOSED:
            ui->comboBoxPortNames->setEnabled(true);
            ui->comboBoxBaudRates->setEnabled(true);
            ui->pushButtonOnOff->setText(OPEN_LBL);
        break;

        case ximu::SerialPort::Message::COULD_NOT_OPEN:
             this->ui->textArea->appendPlainText(OPEN_FAILED_MSG);
    }
}

void SerialView::on_quaternion_recieved(const ximu::QuaternionData& q)
{
    std::stringstream ss;
    ss << "Quaternion (" << q.w() << "," << q.x() << "," << q.y() << "," << q.z() << ")";
    this->ui->textArea->appendPlainText(QString::fromStdString(ss.str()));
}

void SerialView::on_calibrated_inert_mag_recieved(const ximu::CalInertialAndMagneticData& d)
{
    std::stringstream ss;
    ss << "AcceleroMeter (" << d.accelerometer().x() << "," << d.accelerometer().y()
       << "," << d.accelerometer().z() << ")" << std::endl;

    ss << "Gyroscope (" << d.gyroscope().x() << "," << d.gyroscope().y()
       << "," << d.gyroscope().z() << ")" << std::endl;

    ss << "Magneto (" << d.magnetometer().x() << "," << d.magnetometer().y()
       << "," << d.magnetometer().z() << ")";

    this->ui->textArea->appendPlainText(QString::fromStdString(ss.str()));
}
