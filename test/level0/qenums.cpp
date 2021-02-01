// qenums from level0
// problems: 1 + 1(pop)
// https://github.com/KDE/clazy/blob/master/docs/checks/README-qenums.md
// Warns when you're using Q_ENUMS. Use Q_ENUM instead.

#pragma clang diagnostic push
#pragma ide diagnostic ignored "-Wclazy-missing-qobject-macro"

#include <QObject>

namespace qenums {
    class B {
    public:
        enum BB {

        };
    };

    class [[maybe_unused]] A : public QObject {
    public:
        enum E {

        };
        Q_ENUMS(E)// Warning

        enum E2 {

        };
        Q_ENUM(E2)

        Q_ENUMS(B::BB)// OK
    };
}// namespace qenums
#pragma clang diagnostic pop