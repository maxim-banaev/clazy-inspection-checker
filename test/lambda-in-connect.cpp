// lambda-in-connect from level0
// problems: 6 + 1(pop)
// https://github.com/KDE/clazy/blob/master/docs/checks/README-lambda-in-connect.md
// Warns when a lambda inside a connect captures local variables by reference. This usually results in a crash
// since the lambda might get called after the captured variable went out of scope.

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow"
#pragma clang diagnostic ignored "-Wunused-value"
#pragma ide diagnostic ignored "UnusedValue"
#pragma clang diagnostic ignored "-Wunused-lambda-capture"
#pragma ide diagnostic ignored "UnusedLocalVariable"
#pragma clang diagnostic ignored "-Wuninitialized"
#pragma ide diagnostic ignored "readability-static-accessed-through-instance"

#include <QtCore/QObject>

namespace lambda_in_connect {
    struct A {
        int v;
    };


    [[maybe_unused]] void test() {
        QObject *o;
        int a, b, c;
        auto f = [&a]() {};                                 // OK
        o->connect(o, &QObject::destroyed, [a]() {});       // OK
        o->connect(o, &QObject::destroyed, [&a]() {});      // Warning
        QObject::connect(o, &QObject::destroyed, [&a]() {});// Warning
        QObject::connect(o, &QObject::destroyed, [&]() { a; b; });// Warning
        QObject::connect(o, &QObject::destroyed, [=]() { a; b; });// OK

        A *a1;
        QObject::connect(o, &QObject::destroyed, [a1]() { a1->v; }); // OK
        QObject::connect(o, &QObject::destroyed, [&a1]() { a1->v; });// Warning
    }


    static int s;

    struct [[maybe_unused]] C {

        [[maybe_unused]] void foo() {
            QObject *o;
            int m;
            QObject::connect(o, &QObject::destroyed, [this]() {});  // OK
            QObject::connect(o, &QObject::destroyed, []() { s; });  // OK
            QObject::connect(o, &QObject::destroyed, [&m]() { m; });// Warn

            QObject o2;
            QObject::connect(&o2, &QObject::destroyed, [&m]() { m; });// OK, o is on the stack

            QObject *o3;
            QObject::connect(o3, &QObject::destroyed,
                             o3, [&o3] { o3; });// OK, the captured variable is on the 3rd parameter too.
                                                // It will get destroyed
        }

        [[maybe_unused]] int m;
    };
}
#pragma clang diagnostic pop