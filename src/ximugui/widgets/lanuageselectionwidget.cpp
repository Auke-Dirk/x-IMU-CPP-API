#include "ximugui/widgets/lanuageselectionwidget.h"
#include "ui_lanuageselectionwidget.h"

#include <QDir>


 LanguageSelectionWidget::LanguageSelectionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LanguageSelectionWidget)
{
    ui->setupUi(this);

    QStringList qmFilter("*.qm");
    QDir directory("translations");
    QStringList files = directory.entryList(qmFilter);

    _names.insert("en-en.qm", "English");
    _names.insert("nl-nl.qm","Dutch");
    _names.insert("pl-pl.qm","Polish");


    for(auto& item : files)
    {
        auto trans = _names.find(item);
        if (trans != _names.end())
        {
            ui->comboBoxLanguages->addItem(trans.value());
            auto path = QDir::cleanPath(directory.absolutePath() + QDir::separator() + item);
            QTranslator* translator = new QTranslator(this);
            translator->load(path);
            _translators.insert(trans.value(),translator);
        }
    }

    connect(ui->comboBoxLanguages,&QComboBox::currentTextChanged,
            this,&LanguageSelectionWidget::onTranslationChanged);
}

LanguageSelectionWidget::~LanguageSelectionWidget()
{
    delete ui;
}

void LanguageSelectionWidget::changeEvent(QEvent *event)
{
    switch(event->type())
    {
        case QEvent::LanguageChange :
            ui->retranslateUi(this);
        break;
    }

    QWidget::changeEvent(event);
}

void LanguageSelectionWidget::showEvent( QShowEvent* event ) {
    setTranslator(ui->comboBoxLanguages->currentText());
    QWidget::showEvent( event );
}

void LanguageSelectionWidget::onTranslationChanged(const QString& str)
{
    setTranslator(str);
}

void LanguageSelectionWidget::setTranslator(const QString& str)
{
    auto translator = _translators.find(str);
    if (translator != _translators.end())
        QApplication::instance()->installTranslator(*translator);
}


