#pragma clang diagnostic push
#pragma ide diagnostic ignored "-Wclazy-unused-non-trivial-variable"
// string-allocations from level2
// problems: 5 + 1(pop)
// https://github.com/KDE/clazy/blob/master/docs/checks/README-qstring-allocations.md

// Finds places with unneeded memory allocations due to temporary QStrings.


#include <QString>

namespace {
    [[maybe_unused]] void check() {
        QString s1 = "foo";
        QString s2 = QLatin1String("foo");
        QString s3 = QLatin1String(""); // no alloc
        QString s4 = QString::fromLatin1("foo");
        QString s5 = QString::fromUtf8("foo");
        if (s5 == "foo") {}
    }
}
#pragma clang diagnostic pop