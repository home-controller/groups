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
    
    byte getGroup(byte i, char r[]);
    
    void printInfo();
    // Groups(/* args */);
    // ~Groups();
};

// Groups::Groups(/* args */) { }

// Groups::~Groups() { }


#endif