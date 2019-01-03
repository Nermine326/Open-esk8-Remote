

#ifndef __DRIVING_STATEMACHINE_H__
#define __DRIVING_STATEMACHINE_H__

enum mainStateMachine {pairingRemote, initRemote, driveRemote, lostRemote, idleRemote, offRemote};
enum driveStateMachine {flushTX, clearPendingIRQ, sendMessage, checkStatus, receiveMessage};

extern volatile mainStateMachine mainState;
extern volatile driveStateMachine driveState;

extern volatile bool messageType;     
extern volatile bool TX_DS_WasSetAlready_WaitFor_RX_DR;
#endif 