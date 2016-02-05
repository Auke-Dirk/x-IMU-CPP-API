#include "ximugui/widgets/orientationview_plugin.h"
#include "ximugui/widgets/orientationview.h"
#include <QDialog>
#include <QApplication>

OrientationViewPlugin::OrientationViewPlugin()
{}

std::string OrientationViewPlugin::pluginName()
{
    return "OrientationViewFactory";
}
