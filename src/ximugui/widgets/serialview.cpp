#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QPluginLoader>
#include <QPlainTextEdit>
#include <QTextStream>
#include <QDir>
#include <QPushButton>
#include <sstream>
#include "ximugui/widgets/serialview.h"
#include "ui_serialview.h"
#include <QDialog>


#include <iostream>

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
            ui->comboBoxPortNames->addItem(port.systemLocation());

    // gui::button open/close
    connect(this->ui->pushButtonOnOff, &QPushButton::clicked,this, &SerialView::on_openClose_triggerd);

    // serialport::quaternion
    connect(&_sp,&ximu::SerialPort::quaternion,this,&SerialView::on_quaternion_recieved);

    connect(this->ui->textArea,&QPlainTextEdit::textChanged,this,&SerialView::on_text_changed);

    // serialport::interial magnetic
    connect(&_sp,&ximu::SerialPort::calibratedInertialAndMagneticData,
            this,&SerialView::on_calibrated_inert_mag_recieved);

    // serialport::messages
    connect(&_sp,&ximu::SerialPort::messages,this,&SerialView::on_message_recieved);

    // load all the plugins
    loadPlugins();
    displayPlugins();
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
            break;
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
            ui->pushButtonOnOff->setText(tr("close"));
        break;

        case ximu::SerialPort::Message::CLOSED:
            ui->comboBoxPortNames->setEnabled(true);
            ui->comboBoxBaudRates->setEnabled(true);
            ui->pushButtonOnOff->setText(tr("open"));
        break;

        case ximu::SerialPort::Message::COULD_NOT_OPEN:
             this->ui->textArea->appendPlainText(tr("[ERR] Could not open port"));
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

void SerialView::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
            ui->retranslateUi(this);
    QMainWindow::changeEvent(event);
}

void SerialView::loadPlugins()
{
    QStringList qmFilter{"*.dll","*.so", "*.dylib"};
    QDir plugins("plugins");
    if (plugins.exists())
    {
        for(auto& item : plugins.entryList(qmFilter))
        {
            auto path = QDir::cleanPath(plugins.absolutePath() + QDir::separator() + item);
            QPluginLoader loader(path);
            QObject* instance = loader.instance();

            if( instance ){
                XimuWidgetIPluginFactory *plugin = qobject_cast< XimuWidgetIPluginFactory* >( instance );
                if(plugin)
                {
                    std::unique_ptr<XimuWidgetIPluginFactory> uniquePlugin(plugin);
                    _plugins.push_back(std::move(uniquePlugin));
                }
            }else
            {
                QString err = loader.errorString();
                std::cout << loader.errorString().toStdString() << std::endl;
            }
        }
    }
}

void SerialView::displayPlugins()
{
    for(auto& item : _plugins)
    {
        QPushButton* button = new QPushButton(this);
        button->setText(QString::fromStdString(item->displayName()));
        ui->pluginLayout->addWidget(button,0);
        ui->pluginLayout->setAlignment(Qt::AlignTop);
        connect(button,&QPushButton::pressed,this,&SerialView::onPluginPressed);
    }
}

void SerialView::onPluginPressed()
{
    QPushButton* button = static_cast<QPushButton*>(sender());
    std::string name = button->text().toStdString();

    PLUGIN_ITERATOR it = std::find_if(std::begin(_plugins),std::end(_plugins),
                 [&](PLUGIN_TYPE& ptr){ return ptr->displayName() == name;}
              );
    if (it != std::end(_plugins))
    {
        QWidget* w = (*it)->create();
        w->show();
       _sp.connect(&_sp,SIGNAL(quaternion(const ximu::QuaternionData&)),
                   w,SLOT(onNewRotation(const ximu::QuaternionData&))
                   );
    }
}

