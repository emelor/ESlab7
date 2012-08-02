//***********************************************************************
// This file contains a simple CAN driver.
// Created by Jad El-khoury 2006, based on source code provided by Arcticus Systems AB!
//***********************************************************************

#include <hal.h>
#include <can.h>
#include <can_target.h>
#include "canDriver.h"

canBaud_t const baud = {
  0,  //SAMP
  1,  //RJW;
  1,  //PSEG1
  1,  //PSEG2;
  4,  //PRESDIV;
  2   //PROPSEG
};  

void can_initialise(userRxMessageConfig_t *userRxMessageConfig, int numberOfUserRxMessages) { 
	int i;
	canMsg_t msg;

	canDeviceInit(CAN_NODE_A,canIntBusOff.priority,CAN_MAX_MSG_OBJ);
	canInit(CAN_NODE_A,&baud);
	canSetMask(CAN_NODE_A,0, 0x3ffffffff);

	//Rubus Hemdahl Messages
	msg.header.id.id32 = CAN_RUBUS_ID_RX;
	msg.header.nBytes = 8;
	canConfigMsgObj(CAN_NODE_A,CAN_RUBUS_CHANNEL_READ,&msg.header, _R_APPEND);
	canSetIntrObj (CAN_NODE_A,CAN_RUBUS_CHANNEL_READ, canIntHpRx.priority);
	canSetIntrObj (CAN_NODE_A,CAN_RUBUS_CHANNEL_WRITE, canIntHpTx.priority);

	//User-specific messages
	for (i = 0; i < numberOfUserRxMessages; i++) {
		msg.header.id.id32 = userRxMessageConfig[i].id32;
		msg.header.nBytes = userRxMessageConfig[i].nBytes;
		canConfigMsgObj(CAN_NODE_A,userRxMessageConfig[i].channel,&msg.header, 0);
	}

	canEnable(CAN_NODE_A);
} 

int can_readMessage (canUnit_t canReadChannel, canMsg_t *msg) { 
  if (canGetMsgObj(CAN_NODE_A,canReadChannel, msg) != R_OK) {
    return(R_ERROR);
  }
  return(R_OK);
}

int can_writeMessage (canUnit_t canWriteChannel, ULONG id32, UCHAR nBytes, canMsgData_t data) {
	UCHAR      i;
	canMsg_t   msg;

	msg.header.id.id32 = id32;
	msg.header.nBytes = nBytes;
	for (i = 0; i < nBytes; i++) {
		msg.data.d8[i] = data.d8[i];
	}
	return(canTransmitMsgObj(CAN_NODE_A,canWriteChannel, &msg, 0));
}

int can_writeMessageStatus (canUnit_t channel) {
	return(canTransmitMsgStatus (CAN_NODE_A, channel));
	
}
