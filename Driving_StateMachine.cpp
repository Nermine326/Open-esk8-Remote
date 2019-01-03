

#include "Driving_StateMachine.h"

volatile mainStateMachine mainState;
volatile driveStateMachine driveState;

volatile bool messageType;      
volatile bool TX_DS_WasSetAlready_WaitFor_RX_DR = false;     
