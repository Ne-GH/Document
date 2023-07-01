#include <QApplication>
#include <QPushButton>

#include "MainWindow.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow window;
    window.show();

//    QPushButton button("Hello world!", nullptr);
//    button.resize(200, 100);
//    button.show();
    return QApplication::exec();
}
