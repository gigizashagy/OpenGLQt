#include <QApplication>
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setStyle("fusion");
    MainWindow window;
    window.show();
    window.resize(800, 640);
    return app.exec();
}
