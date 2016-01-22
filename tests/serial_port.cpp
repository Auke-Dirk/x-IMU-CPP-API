/*
  Copyright 2015 Auke-Dirk Pietersma
*/

#include <thread>
#include <QApplication>
#include <ximugui/widgets/serialview.h>

/*
 * Trying to open and close a QT Widget,
 * can QT be compiled and run.
 */
int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(serialview);

    QApplication a(argc, argv);
    SerialView w;
    w.show();

   return a.exec();
}
