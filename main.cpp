#include <QApplication>
#include <QFileDialog>
#include "appengine.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    AppEngine::instance()->initialize(&app);

    return AppEngine::instance()->exec();
}
