#pragma clang diagnostic push
#pragma ide diagnostic ignored "-Wclazy-qstring-allocations"
#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QPushButton button("Hello world!", nullptr);
    button.resize(200, 100);
    button.show();
    return QApplication::exec();
}
#pragma clang diagnostic pop