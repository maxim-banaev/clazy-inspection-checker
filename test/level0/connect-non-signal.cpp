// connect-non-signal from level0
// problems: 3 + 1(pop)
// https://github.com/KDE/clazy/blob/master/docs/checks/README-connect-non-signal.md
// Warns when connecting a non-signal to something.

#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-convert-member-functions-to-static"
#pragma ide diagnostic ignored "readability-static-accessed-through-instance"
#pragma ide diagnostic ignored "-Wclazy-ctor-missing-parent-argument"
#pragma ide diagnostic ignored "-Wclazy-overridden-signal"
#pragma ide diagnostic ignored "-Wclazy-old-style-connect"
#pragma ide diagnostic ignored "-Wclazy-virtual-signal"

#include <QObject>

namespace connect_non_signal {
    class MyObj : public QObject {
        Q_OBJECT
    public:
        void foo(){};

        [[maybe_unused]] int bar() { return 1; }

    signals:

        void mySig(){};

        virtual void myVirtualSig(){};

    public Q_SLOTS:

        void mySlot(){};
    };

    [[maybe_unused]] void test() {
        auto *o = new MyObj();
        o->connect(o, &MyObj::mySig, o, &MyObj::mySlot);// OK
        o->connect(o, &MyObj::foo, o, &MyObj::mySlot);  // Warning
        o->connect(o, SIGNAL(foo()), o, SLOT(mySlot()));// OK, only PMF is checked
    }

    class MyObj2 : public QObject {
        Q_OBJECT
    public:
        void foo(){};

    signals:
        void mySig() {};
    };

    [[maybe_unused]] void test2() {
        auto *o2 = new MyObj2();
        o2->connect(o2, &MyObj2::mySig, o2, &MyObj2::foo);     // OK
        QObject::connect(o2, &MyObj2::mySig, o2, &MyObj2::foo);// OK
        QObject::connect(o2, &MyObj2::foo, o2, &MyObj2::foo);  // Warning
    }

    class MyDerivedObj : public MyObj {
        Q_OBJECT
    public:
        void myVirtualSig() override{};
    };

    [[maybe_unused]] void test3() {
        auto *o = new MyDerivedObj();
        QObject::connect(o, &MyDerivedObj::myVirtualSig, o, &MyObj::foo);// Warn, overridden but not a signal now
        QObject::connect(o, &MyObj::myVirtualSig, o, &MyObj::foo);       // OK
    }
}// namespace connect_non_signal
#pragma clang diagnostic pop