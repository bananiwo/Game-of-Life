#ifndef TESTTILE_H
#define TESTTILE_H

#include <QTest>

#include "Tile.h"

class TestTile: public QObject
{
    Q_OBJECT
    Tile *tile;
private slots:
    void initTestCase()
    {
        qDebug("Called before everything else.");
    }

    void initTestCase_data()
    {
       tile = new Tile(2, 3, 4);
    }

    void getRow()
    {
        QVERIFY(tile->getRow() == 2);
    }

    void getCol()
    {
        QVERIFY(tile->getCol() == 3);
    }

    // void isPressed()
    // {
    //     QVERIFY(tile->m_active == false);
    // }

    // void changeState()
    // {
    //     tile->changeActive();
    //     QVERIFY(tile->m_active == true);
    // }

    void operatorEqual()
    {
        Tile t(2, 3, 4);
        Tile other(2, 3, 4);
        QVERIFY(t == other);
    }

    void operatorNotEqual()
    {
        Tile t(2, 3, 4);
        Tile other(3, 3, 4);
        QVERIFY(t != other);
        Tile other1(2, 4, 4);
        QVERIFY(t != other1);
        Tile other2(2, 3, 5);
        QVERIFY(t != other2);
    }

    void copyConstructor()
    {
        Tile original(1, 2, 3);
        Tile copy = original;
        QVERIFY(original == copy);
        QVERIFY(&original != &copy);
    }

    void copyConstructorPointer()
    {
        Tile *original = new Tile(1, 2, 3);
        Tile *copy = new Tile(*original);
        QVERIFY(original != copy);
        QVERIFY(*original == *copy);
        delete original;
        delete copy;
    }


    void cleanupTestCase()
    {
        delete tile;
    }
};

#endif
