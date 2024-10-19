#include <QtWidgets/QApplication>
#include <qgraphicsscene.h>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <qdebug.h>

#include "MainWindow.h"
#include "MyGraphicsScene.h"
#include "MyGraphicsView.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
