// empty-qstringliteral from level0
// problems: 5 + 1(pop)
// https://github.com/KDE/clazy/blob/master/docs/checks/README-empty-qstringliteral.md

// Suggests to use QLatin1String("") instead of QStringLiteral() and QStringLiteral(""). QStringLiteral should only be
// used where it would reduce memory allocations.

#include <QString>

namespace empty_qstringliteral {
    [[maybe_unused]] void check() {
        auto s1 = QStringLiteral("foo");
        auto s2 = QStringLiteral("");
        auto s3 = QStringLiteral();

        if ("foo" == QStringLiteral()) {}
    }
}

