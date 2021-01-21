// container-anti-pattern from level0
// problems: 7 + 1(pop)
// https://github.com/KDE/clazy/blob/master/docs/checks/README-container-anti-pattern.md
// Finds when temporary containers are being created needlessly. These cases are usually easy to fix by using iterators,
// avoiding memory allocations.

#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedLocalVariable"
#pragma ide diagnostic ignored "UnusedValue"
#pragma ide diagnostic ignored "-Wclazy-unused-non-trivial-variable"

#include <QHash>
#include <QList>
#include <QMap>
#include <QSet>
#include <QVector>

namespace container_anti_pattern{
    [[maybe_unused]] void test()
    {
        QSet<int> set;
        QMap<int,int> map;
        QHash<int,int> hash;
        QList<int> list;
        QVector<int> vec;

        vec.toList().count(); // Warning
        map.values()[0]; // Warning
        int a = hash.keys().at(0); // Warning
        a = map.keys().at(0); // Warning
        list.toVector().size(); // Warning
    }

    [[maybe_unused]] void testRangeLoop()
    {
        QHash<int,int> hash;
        for (auto i : hash.values()) {} // Warning
        for (auto i : hash.keys()) {} // Warning
        for (auto i : hash) {} // OK
        foreach (auto i, hash.keys()) {} // Warning
        foreach (auto i, hash.values()) {} // Warning
        foreach (auto i, hash) {} // OK
    }
}
#pragma clang diagnostic pop