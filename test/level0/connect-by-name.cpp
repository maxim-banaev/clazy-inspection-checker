// connect-by-name from level0
// problems: 1 + 1(pop)
// https://github.com/KDE/clazy/blob/master/docs/checks/README-connect-by-name.md

// Warns when "auto-connection slots" are used. They're also known as "connect by name", an old and unpopular feature
// which isn't recommended. Consult the official documentation for more information.

#pragma clang diagnostic push
#pragma ide diagnostic ignored "-Wclazy-missing-qobject-macro"
#include <QObject>

namespace connect_by_name {
    class [[maybe_unused]] MyObj;// OK

    class [[maybe_unused]] MyObj : public QObject {
    public Q_SLOTS:

        [[maybe_unused]] void on_foo_bar(){};// Warn

    public:
        [[maybe_unused]] void on_foo2_bar2(){};// OK

    signals:

        [[maybe_unused]] void on_foo3_bar3(){};// OK
    };
}// namespace connect_by_name
#pragma clang diagnostic pop