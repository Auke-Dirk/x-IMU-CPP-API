#include <thread>
#include <QApplication>
#include <QMainWindow>
#include <QLayout>

#include <ximugui/widgets/lanuageselectionwidget.h>

/*
 * Trying to open and close a QT Widget,
 * can QT be compiled and run.
 */
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    LanguageSelectionWidget* w;
    w = new LanguageSelectionWidget;
    QMainWindow window;

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(w);
    window.setCentralWidget(w);
    window.setLayout(layout);
    window.show();
    return  a.exec();

}
