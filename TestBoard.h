#ifndef TESTBOARD_H
#define TESTBOARD_H

#include <QTest>

#include "board.h"

class TestBoard: public QObject
{
    Q_OBJECT

private slots:
    void initTestCase()
    {
        qDebug("Called before everything else.");
    }

    void operatorEqual()
    {
        Board t(2, 3, 4);
        Board other(2, 3, 4);
        QVERIFY(t == other);
    }

    void copyConstructor()
    {
        Board original(2, 3, 4);
        Board copy(2, 3, 4);
        QVERIFY(original == copy);
        QVERIFY(&original != &copy);
    }


};

#endif // TESTBOARD_H
