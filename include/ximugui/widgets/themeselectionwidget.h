#ifndef THEME_SELECTION_WIDGET_H__
#define THEME_SELECTION_WIDGET_H__

#include <QWidget>

namespace Ui {
class ThemeSelectionWidget;
}

class ThemeSelectionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ThemeSelectionWidget(QWidget *parent = 0);
    ~ThemeSelectionWidget();

protected:
    void changeEvent (QEvent* event);

private:
    Ui::ThemeSelectionWidget *ui;
    static const QString s_STYLESHEET_PATH;

    void onThemeChanged(const QString& event);
    void selectTheme(const QString& uri);
};

#endif // LANGUAGE_SELECTION_WIDGET_H__
