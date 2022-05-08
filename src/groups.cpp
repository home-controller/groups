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

byte Groups::getGroup(byte i, char r[ ]) {
  if (i <= numOfSmallGroups) {
    blockObj3.readSlot(i, r);
    return 3;
  } else if (i <= numOfGroups) {
    blockObj10.readSlot(i - numOfSmallGroups, r);
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
byte Groups::setGroup(byte i, char r[ ]) {
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
    i -=numOfSmallGroups;
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

void Groups::initStuff(storageBlock_C& o, byte id1, storageBlock_C& o2, byte id2) {
  blockObj3.setMemManager(o);
  blockObj3.setId(id1);
  blockObj10.setMemManager(o2);
  blockObj10.setId(id2);
  numOfSmallGroups = blockObj3.getSlots();
  numOfGroups = numOfSmallGroups + blockObj10.getSlots();
}

void Groups::printInfo() {
  //byte i;
  io_printHeading("Printing setup");
  //io_print( "Storeage id" ); io_print_n( blockObj.getId() ); 
  io_print("Max groups"); io_println_n(numOfSmallGroups + numOfSmallGroups);// io_print( ", Lights" ); io_println_n( numLights );

  // //io_print("Size of room record extened(room_TE) : ");  io_println_n(roomsRecSizeE);
  // for ( i = 0; i < maxLights; i++ ) {
  //   printLightInfo( i );
  // }

}