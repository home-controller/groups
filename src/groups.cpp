#include <Arduino.h>
#include "groups.h"

byte Groups::getGroup(byte i, char r[ ]) {
  if (i <= numOfSmallGroups) {
    blockObj3.readSlot(i, r);
    return 3;
  } else if (i <= numOfGroups) {
    blockObj10.readSlot(i-numOfSmallGroups, r);
    return 10;
  }
  // else out of range.
  return 0;
}

void Groups::initStuff(storageBlock_C& o, byte id1, storageBlock_C& o2, byte id2) {
  blockObj3.setMemManager(o);
  blockObj3.setId(id1);
  blockObj10.setMemManager(o2);
  blockObj10.setId(id2);
  numOfSmallGroups = blockObj3.getSlots();
  numOfGroups = numOfSmallGroups + blockObj10.getSlots();
}

void Groups::printInfo() {

}