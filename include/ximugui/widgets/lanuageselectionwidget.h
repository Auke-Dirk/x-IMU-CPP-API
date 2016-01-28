#ifndef LANGUAGE_SELECTION_WIDGET_H__
#define LANGUAGE_SELECTION_WIDGET_H__

#include <QWidget>
#include <QString>
#include <QMap>
#include <QVector>
#include <QTranslator>

namespace Ui {
class LanguageSelectionWidget;
}

class LanguageSelectionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LanguageSelectionWidget(QWidget *parent = 0);
    ~LanguageSelectionWidget();

    void onTranslationChanged (const QString& str);
    void setTranslator (const QString& str);
protected:
    void changeEvent (QEvent* event);
    void showEvent (QShowEvent* event );

private:
    Ui::LanguageSelectionWidget *ui;
    QMap<QString,QString> _names;
    QMap<QString,QTranslator*> _translators;
};

#endif // LANGUAGE_SELECTION_WIDGET_H__
