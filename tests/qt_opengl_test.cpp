/*
  Copyright 2015 Auke-Dirk Pietersma
*/

#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>
#include <thread>
#include <iostream>

#include <QApplication>
#include "ximugui/widgets/orientationview.h"


int main(int argc, char *argv[])
{
    // Main Application
    QApplication a(argc, argv);
    OrientationView w;
    w.show();

    QQuaternion q1 = QQuaternion(1,0.01,0.01,0.01);
    QQuaternion q2 = QQuaternion(1,0,0,0);

    size_t calls = 400;

    std::thread closer( [&] {
        while(--calls  > 0)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            q2*= q1;
            q2.normalize();
            w.rotation(q2);
        }
          QMetaObject::invokeMethod(&w, "close", Qt::QueuedConnection);
    });


    auto retcode =  a.exec();

    closer.join();

    return retcode;
}
