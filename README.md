# groups


<<<<<<< HEAD
Pre beta work in progress, only public as easier for me. :hushed:
=======
Pre beta work in progress, only public as easier for me. :innocent:
>>>>>>> 52002ff5121c292f08d95a521f29d9215ad62101

At the moment this just has two block of storage from store.h(EEPROM, etc. memory blocks) the first split into 3 byte records and the second into 10 byte records.

Has functions to set or get an array with 3 or 10 bytes of data, 3 bytes if the index is in the first storage block or 10 if i is greater than the number of 3 bytes records.

I then use the record elsewhere. As a bitmap for the lights in a room or house, 3 bytes is 24bits so a room with up to 24 separately switched lights or up-to the first 24 lights in a house. Or the first byte could be a room and bitmap for 16 lights in the room. Or the 3 bytes can be 3 light Ids.

As for the 10 byte array, I use them for bigger groups, can be a bitmap for upto 80 lights or offset and bitmap etc. this is all handled elsewhere at the moment although I may move more here. 
