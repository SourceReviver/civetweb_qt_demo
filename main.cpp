#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

#include "ImageGenerator.h"
#include "Server.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    auto mainwindow = new QWidget();
    auto hbox = new QHBoxLayout(mainwindow);

    auto start = new QPushButton("start", mainwindow);
    auto stop = new QPushButton("stop", mainwindow);

    hbox->addWidget(start);
    hbox->addWidget(stop);

    mainwindow->setLayout(hbox);
    mainwindow->show();

    auto serverController = new Server();

    QObject::connect(start, &QPushButton::clicked,
                     serverController, &Server::startServer);
    QObject::connect(stop, &QPushButton::clicked,
                     serverController, &Server::requestStop);

    return QApplication::exec();
}
