
// http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml
// http://www.possibility.com/Cpp/CppCodingStandard.html
// http://geosoft.no/development/cppstyle.html


#include <QApplication>
#include <signal.h>
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include "mainwindow.h"
#include "soccer.h"
using namespace std;

void SignalHandler(int)
{
    // save current state here
    // and then ...
    qDebug() << "Segmentation Fault !!!";
    exit(1);
}

int main(int argc, char *argv[])
{
    //signal(SIGSEGV, SignalHandler);
    //signal(SIGALRM, SignalHandler);

    QCoreApplication::setOrganizationName("KN2C");
    QCoreApplication::setOrganizationDomain("www.kn2c.ir");
    QCoreApplication::setApplicationName("KN2C SSL");

    QApplication a(argc, argv);
    cout << endl;
    cout << "KN2C Small Size League Robocup Team" << endl;
    cout << "K.N.Toosi University of Technology" << endl;
    cout << "Computer & Electrical Eng. Faculty" << endl;
    cout << "Version 7.0.0" << endl;
    cout << endl;

    Soccer soccer;

    MainWindow w;

    bool gui = false;
    if(argc > 1)
        if(strcmp(argv[1], "nogui") == 0)
            gui = false;
    if(gui) w.show();

    return a.exec();
}

