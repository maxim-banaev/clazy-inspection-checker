// qstring-ref from level0
// problems: 5 + 1(pop)
// https://github.com/KDE/clazy/blob/master/docs/checks/README-qstring-ref.md
// Finds places where QString::fooRef() should be used instead of QString::foo(), to avoid temporary heap allocations.

#include <QtCore/QString>
#include <QtCore/QRegExp>
#include <QtCore/QStringList>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-result"
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"
namespace qstring_ref {
    [[maybe_unused]] void test()
    {
        bool ok = false;
        QString s;

        s.mid(1, 1).toInt(&ok); // Warning
        s.mid(1, 1); // OK
        s.toInt(&ok); // OK
        s.midRef(1, 1).toInt(&ok); // OK
        s.mid(s.lastIndexOf(QLatin1Char('#')) + 1).toUpper(); // OK
        s.mid(s.lastIndexOf(QLatin1Char('#')) + 1).trimmed(); // Warning
        const QRegExp r;
        QRegExp r2;
        s.mid(1, 1).indexOf(r); // OK
        s.mid(1, 1).indexOf(r2); // OK
        QString s2;
        s.append(s2.mid(1,1)); // Warning
        s.count(s2.left(1)); // Warning
        QStringList list;
        list.append(s2.mid(1,1)); // OK
        s += s2.mid(1,1); // Warning
        int start,end;
        [[maybe_unused]] int m = s.mid(start + 1, end - start - 1).toUInt(&ok); // Warning
    }

    QString i18n(const QString &) { return {}; }

    [[maybe_unused]] void test2()
    {
        QString s;
        s.append(i18n(s.mid(1, 1))); // OK
    }
}

#pragma clang diagnostic pop