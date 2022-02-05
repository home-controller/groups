#include <Arduino.h>

void groupSet(byte i, byte relays9_16, byte relays1_8, byte opts ){
  byte g_index;
  if ( i >= No_groups){ return; }
  g_index = groups_eeprom_start + (i*group_size);
  EEPROM.update(g_index+0, relays1_8);
  EEPROM.update(g_index+1, relays9_16);
  EEPROM.update(g_index+2, opts);
  groupsSateA[i+1] = 0;
}

void setSwitchGroups(byte switchN, byte quick_i, byte normal_i, byte count2_i, byte count3_i, byte count4_i){
  byte i;
  if ( switchN >= No_switches_eeprom_res){ return; }
  i = switches_eeprom_start + (switches_size * switchN);
  EEPROM.update(i, quick_i);
  EEPROM.update(i+1, normal_i);
  EEPROM.update(i+2, count2_i);
  EEPROM.update(i+3, count3_i);
  EEPROM.update(i+4, count4_i);
}