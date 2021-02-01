#pragma clang diagnostic push
#pragma ide diagnostic ignored "-Wclazy-qstring-allocations"
// auto-unexpected-qstringbuilder from level1
// problems: 3 + 2(expression result unused) + 1(pop)
// https://github.com/KDE/clazy/blob/master/docs/checks/README-auto-unexpected-qstringbuilder.md
// Finds places where auto is deduced to be QStringBuilder instead of QString, which introduces crashes.
// Also warns for lambdas returning QStringBuilder.

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"
#pragma ide diagnostic ignored "-Wclazy-unused-non-trivial-variable"

#define QT_USE_QSTRINGBUILDER
#include <QtCore/QString>

namespace auto_unexpected_qstringbuilder {
    [[maybe_unused]] void test() {
        const auto s1 = "tests/" + QString::fromLatin1("foo");   // Warning
        const auto s2 = "tests/" % QString::fromLatin1("foo");   // Warning
        const QString s3 = "tests/" + QString::fromLatin1("foo");// OK
        const QString s4 = "tests/" % QString::fromLatin1("foo");// OK

        [] {
            return "tests/" % QString::fromLatin1("foo");// Warn
        };

        [] {
            return QString();// OK
        };
    }
}
#pragma clang diagnostic pop
#pragma clang diagnostic pop