#include "ximugui/widgets/themeselectionwidget.h"
#include "ui_themeselectionwidget.h"

#include <QDir>


const QString ThemeSelectionWidget::s_STYLESHEET_PATH = ":/theme/stylesheets/";

 ThemeSelectionWidget::ThemeSelectionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ThemeSelectionWidget)
{
    ui->setupUi(this); 

    foreach( const QString &qss, QDir(s_STYLESHEET_PATH).entryList() )
    {
        auto label = qss;
        label.replace(QString(".qss"),QString(""));
        ui->comboBox->addItem(label,s_STYLESHEET_PATH + qss);
    }

    connect(ui->comboBox,&QComboBox::currentTextChanged,
            this,&ThemeSelectionWidget::onThemeChanged);

    onThemeChanged("finds some default");
}

ThemeSelectionWidget::~ThemeSelectionWidget()
{
    delete ui;
}

void ThemeSelectionWidget::changeEvent(QEvent *event)
{
    switch(event->type())
    {
        case QEvent::LanguageChange :
            ui->retranslateUi(this);
        break;
    }

    QWidget::changeEvent(event);
}

void ThemeSelectionWidget::selectTheme(const QString& uri)
{
    QFile file(uri);
    if (file.exists())
    {
        file.open(QFile::ReadOnly);
        QString StyleSheet = QLatin1String(file.readAll());
        qApp->setStyleSheet(StyleSheet);
    }
}

void ThemeSelectionWidget::onThemeChanged(const QString& event)
{
    auto index = ui->comboBox->currentIndex();
    QVariant variant = ui->comboBox->itemData(index);
    QString str  = variant.value<QString>();
    selectTheme(str);
}

