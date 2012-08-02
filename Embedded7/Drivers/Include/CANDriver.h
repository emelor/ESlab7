#ifndef CANDRIVER_H
#define CANDRIVER_H

#include <can.h>

typedef struct {
	canUnit_t channel;
	ULONG id32;
	UCHAR nBytes;
} userRxMessageConfig_t;

//This function initialises the CAN device.
//1. It is necessary to first call this function before one can send/receive messages over CAN.
//   (This includes the Rubus VS logging functionality.)
//2. During the initialisation phase, this function also sets up the necessary channels to receive CAN messages.
//- The device is setup such that each channel is configured to receive messages of a single specific ID.
//- One cannot use the same channel for more than one message identifier.
//- Having defined a channel to receive messages with, one should avoid using that channel to write messages with.
//3. The configuration for receiving messages is specified through the parameter userRxMessageConfig, an array of type userRxMessageConfig_t.
//   The numberOfUserRxMessages parameter specifies the index range of the userRxMessageConfig array to be considered by the initialisation function.
//   The array can be of any larger length, but the initialisation function will only consider the elements indexed from 0 to numberOfUserRxMessages-1.
//- userRxMessageConfig[i] defines the configuration of channel userRxMessageConfig[i].channel, to receive message with 
//  the userRxMessageConfig[i].id32 identifier, and userRxMessageConfig[i].nBytes number of bytes.
//- userRxMessageConfig[i].channel ranges from 0 to 15. 
//  Note however that the channels CAN_RUBUS_CHANNEL_READ (0) & CAN_RUBUS_CHANNEL_WRITE (1) are occupid by Rubus functionality. (See file hal.h)
//- userRxMessageConfig[i].id32 is an extended (29-bits) identifier. 
//  Note however that the ids CAN_RUBUS_ID_RX (0x18000100) & CAN_RUBUS_ID_TX (0x18000101) are occupied by Rubus functionality. (See file hal.h)
void can_initialise(userRxMessageConfig_t *userRxMessageConfig, int numberOfUserRxMessages);

//Attempt to read a CAN message from channel canReadChannel. 
//1. If successfull, the function returns R_OK, and places the result in msg.
//   If no message is available, the function returns R_ERROR.
//Reminder: the channel from which to read ought to be initialised in function can_initialise for a specific identifier!
int can_readMessage (canUnit_t canReadChannel, canMsg_t *msg);

//Attempt to write a CAN message to channel canWriteChannel. 
//1. The message is to have an id of id32, number of bytes nBytes, and content of data.
//2. If successfull, the function returns R_OK, otherwise, an error code is returned.
//3. Note that nBytes is the message size in terms of bytes. 
//   this is irrespective of whether data is defined as an array of UCHAR[8], USHORT[4] or ULONG[2]
//4. Unlike reading messages, one can use the same channel during message writing for more than one identifier.
//   Care should be taken however to avoid writing using a channel already setup for reading.
//   This will cause the channel to not function as desired for the reading of messages.
int can_writeMessage (canUnit_t canWriteChannel, ULONG id32, UCHAR nBytes, canMsgData_t data);

//returns R_OK if the latest message on this channel was successfully transmitted.
int can_writeMessageStatus (canUnit_t channel);

#endif
