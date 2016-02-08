#include <Qtcore/QObject>
#include <QWidget>
#include <string>
#include "ximuapi/io/serial_port.h"

#define XimuWidgetIPluginFactory_IDD "ximu.XimuWidgetIPluginFactory/1.0"

class XimuWidgetIPluginFactory
{
public:
    virtual std::string pluginName() = 0;
    virtual std::string displayName() = 0;
    virtual QWidget* create() = 0;
    virtual ~XimuWidgetIPluginFactory(){}
};

Q_DECLARE_INTERFACE( XimuWidgetIPluginFactory, XimuWidgetIPluginFactory_IDD)
