#include <Arduino.h>
#include "groups.h"
#include <ui_io.h>

byte setBits(byte numBytes, byte bitx1, byte bitx2, byte bitx3, byte bitx4, byte bitx5, byte bitx6, byte bitx7) {
  byte i;
  i = 0;
  if (bitx1 > 0) {
    bitSet(i, bitx1 - 1);// the first bit is 0, so sub 1. Therefore bitx1 = 1 will set the least-significant (rightmost) bit.
    if (bitx2 > 0) {
      bitSet(i, bitx2 - 1);
      if (bitx3 > 0) {
        bitSet(i, bitx3 - 1);
        if (bitx4 > 0) {
          bitSet(i, bitx4 - 1);
          if (bitx5 > 0) {
            bitSet(i, bitx5 - 1);
            if (bitx6 > 0) {
              bitSet(i, bitx6 - 1);
              if (bitx7 > 0) {
                bitSet(i, bitx7 - 1);
              }
            }
          }
        }
      }
    }
  }
  return i;
}

byte Groups::getGroup(byte i, byte r[ ]) {
  if (i <= numOfSmallGroups) {
    blockObj3.readSlot(i, r + 1);
    r[0] = blockObj3.slotSize();
    return 3;
  } else if (i <= numOfGroups) {
    blockObj10.readSlot(i - numOfSmallGroups, r + 1);
    r[0] = 10;
    return 10;
  }
  // else out of range.
  return 0;
}

/**
 * @brief Store a group to storage i.e. EEPROM
 * @details This will store the group to storage. To position determins the size in bytes of the storage.
 *
 *
 * @param i The index in storage to store the group in.
 * @param r The array of bytes passed in. first element at 0 should be the size of the array.
 * @return byte
 */
byte Groups::setGroup(byte i, byte r[ ]) {
  byte l, x;
  if (i <= numOfSmallGroups) {
    l = blockObj3.blockSize();
    if (r[0] == l) {
      blockObj3.writeSlot(i, r + 1);
    } else {
      if (l > r[0]) l = r[0];
      for (x = 0; x < l; x++) {
        blockObj3.writeByte(i, x, r[x + 1]);
      }
    }
    return 3;
  } else if (i <= numOfGroups) {
    l = blockObj10.blockSize();
    i -= numOfSmallGroups;
    if (r[0] == l) {
      blockObj10.writeSlot(i, r + 1);
    } else {
      if (l > r[0]) l = r[0];
      for (x = 0; x < l; x++) {
        blockObj10.writeByte(i, x, r[x + 1]);
      }
    }

    blockObj10.writeSlot(i, r);
    return 10;
  }
  // else out of range.
  return 0;
}

/**
 * @brief Init groups.
 *
 * @param o object keeping track of block of different types of storage slots.
 * @param id1 The block of storage used to store all the 3 byte long slots.
 * @param o2 likely the same storage as o but it could be different if different chips were used etc.
 * @param id2 id of the block of storage used to store slots
 */
void Groups::initStuff(storageBlock_C& o, byte id1, storageBlock_C& o2, byte id2) {
  blockObj3.setMemManager(o);
  blockObj3.setId(id1);
  blockObj10.setMemManager(o2);
  blockObj10.setId(id2);
  numOfSmallGroups = blockObj3.getSlots();
  numOfGroups = numOfSmallGroups + blockObj10.getSlots();
}

void Groups::printInfo() {
  byte i, x;
  byte tA[10];
  io_printHeading("Stored groups");
  //io_print( "Storeage id" ); io_print_n( blockObj.getId() ); 
  io_print("Num of small groups:"); io_println_n(numOfSmallGroups);// io_print( ", Lights" ); io_println_n( numLights );
  for (i = 1; i <= numOfSmallGroups; i++) {
    getGroup(i, tA);
    io_print_n(i);
    io_print(": len: "); io_print_n(tA[0]);
    io_print(", ");
    for (x = 1; x <= tA[0]; x++) {
      Serial.print(tA[x]); Serial.print(":");
      io_print_nb_f(tA[x], ( x < tA[0] ));
    }
    io_ln;

  }

}