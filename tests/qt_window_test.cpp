/*
  Copyright 2015 Auke-Dirk Pietersma
*/

#include <thread>
#include <QApplication>
#include <ximugui/widgets/simplewindow.h>

/*
 * Trying to open and close a QT Widget,
 * can QT be compiled and run.
 */
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    SimpleWindow w;

    // call close in 4 seconds
    std::thread closer( [&] {
        std::this_thread::sleep_for(std::chrono::seconds(4));
        QMetaObject::invokeMethod(&w, "close", Qt::QueuedConnection);
    });


    w.show();

    auto retcode =  a.exec();

    closer.join();

    return retcode;
}
