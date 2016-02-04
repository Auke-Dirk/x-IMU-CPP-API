#include <Qtcore/QObject>
#include <string>

#define XimuWidgetIPluginFactory_IDD "ximu.XimuWidgetIPluginFactory"

class XimuWidgetIPluginFactory
{
public:
    virtual std::string pluginName() = 0;
};

Q_DECLARE_INTERFACE( XimuWidgetIPluginFactory, XimuWidgetIPluginFactory_IDD)
