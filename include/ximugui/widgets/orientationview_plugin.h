#ifndef ORIENTATION_VIEW_PLUGIN_H_
#define ORIENTATION_VIEW_PLUGIN_H_

#include <QtPlugin>
#include "ximugui/widgets/ximuwidget_iplugin_factory.h"


class OrientationViewPlugin :
        public QObject,
        public XimuWidgetIPluginFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID XimuWidgetIPluginFactory_IDD)
    Q_INTERFACES(XimuWidgetIPluginFactory)


public:
    virtual std::string pluginName();
    virtual std::string displayName();
    QWidget* create();
    OrientationViewPlugin();
};

#endif


