// connect-not-normalized from level0
// problems: 1(pop)
// https://github.com/KDE/clazy/blob/master/docs/checks/README-connect-not-normalized.md
// Warns when the contents of SIGNAL(), SLOT(), Q_ARG() and Q_RETURN_ARG() are not normalized.

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-pro-type-member-init"
#pragma ide diagnostic ignored "readability-static-accessed-through-instance"

#include <QtCore/QObject>
#include <QtCore/QVariant>

namespace connect_not_normalized {
    [[maybe_unused]] void test() {
        QObject o;

        QVariant v, returnedValue;
        QMetaObject::invokeMethod(&o, "mySlot",
                                  Q_RETURN_ARG(QVariant, returnedValue), // OK
                                  Q_ARG(const QVariant, v)); // Warn
        QMetaObject::invokeMethod(&o, "mySlot",
                                  Q_RETURN_ARG(QVariant, returnedValue), // OK
                                  Q_ARG(const QVariant, // Warn
        v)); // multi-line

        Q_ARG(QVariant, v); // OK
        Q_ARG(QVariant & , v); // Warn
        Q_ARG(QVariant & , v); // OK
        Q_ARG(const QVariant &, v); // Warn
    }

    [[maybe_unused]] void testConnect() {
        QObject o;
        o.connect(&o, SIGNAL(destroyed(int, int)), // Warn
                  &o, SLOT(void foo(const int))); // Warn
        o.connect(&o, SIGNAL(destroyed(int, int)), // OK
                  &o, SLOT(void foo(int))); // OK

        o.disconnect(&o, SLOT(void foo(const int))); // OK
    }


    class [[maybe_unused]] MyObj : public QObject {
    public:
        MyObj() {
            // volker mentioned this not working, but I can't reproduce
            connect(ui->host, SIGNAL(textChanged(QString)), // OK
                    SLOT(validateHostAddress(const QString&))); // OK
        }

        MyObj *ui;
        MyObj *host;
    };
}
#pragma clang diagnostic pop