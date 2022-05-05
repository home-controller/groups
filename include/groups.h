#ifndef _groups_h //User Interface for Home Auto
#define _groups_h

#include <Arduino.h>
#include <store.h>


class Groups {
private:
    /* data */
    blockMem_C blockObj3;// saved mem manager for 3byte/24bit groups.
    blockMem_C blockObj10;// saved mem manager for 10byte/80bit groups.
    byte numOfSmallGroups;
    byte numOfGroups;

public:
    void initStuff(storageBlock_C& o, byte id1, storageBlock_C& o2, byte id2);

    byte setGroup(byte i, char r[ ]);
    byte getGroup(byte i, char r[ ]);

    void printInfo();
    // Groups(/* args */);
    // ~Groups();
};

byte setBits(byte numBytes, byte bitx1, byte bitx2 = 0, byte bitx3 = 0, byte bitx4 = 0, byte bitx5 = 0, byte bitx6 = 0, byte bitx7 = 0)
// Groups::Groups(/* args */) { }

// Groups::~Groups() { }


#endif