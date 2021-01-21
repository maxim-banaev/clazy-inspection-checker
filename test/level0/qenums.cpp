// qenums from level0
// problems: 1
// https://github.com/KDE/clazy/blob/master/docs/checks/README-qenums.md
// Warns when you're using Q_ENUMS. Use Q_ENUM instead.


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