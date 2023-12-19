#include "tasky.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Tasky w;
    w.show();
    return a.exec();
}
