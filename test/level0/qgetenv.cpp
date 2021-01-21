// qgetenv from level0
// problems: 3 + 1(pop)
// https://github.com/KDE/clazy/blob/master/docs/checks/README-qgetenv.md
// Warns on innefficient usages of qgetenv() which usually allocate memory.
// Suggests usage of qEnvironmentVariableIsSet(), qEnvironmentVariableIsEmpty() and qEnvironmentVariableIntValue().

#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedValue"
#pragma ide diagnostic ignored "UnusedLocalVariable"
#pragma ide diagnostic ignored "-Wclazy-unused-non-trivial-variable"

#include <qbytearray.h>
#include <qglobal.h>

namespace q_getenv {
    [[maybe_unused]] int test() {
        qgetenv("Foo").isEmpty();
        bool b = qgetenv("Foo").isNull();
        QByteArray ba = qgetenv("Foo");
        int a = qgetenv("Foo").toInt(&b);
        return 0;
    }
}
#pragma clang diagnostic pop