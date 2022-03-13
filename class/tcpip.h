#ifndef __TCPIP_H

#define __TCPIP_H

#include "tcpip_defines.h"

// typedefs
typedef enum {                                   // states of the TCP-state machine
  CLOSED,                                        // according to RFC793 //0
  LISTENING,                                     // 1
  SYN_SENT,                                      // 2
  SYN_RECD,                                      // 3
  ESTABLISHED,                                   // 4
  FIN_WAIT_1,                                    // 5
  FIN_WAIT_2,                                    // 6
  CLOSE_WAIT,                                    // 7
  CLOSING,                                       // 8
  LAST_ACK,                                      // 9
  TIME_WAIT                                      // 10
} TTCPStateMachine;

typedef enum {                                   // type of last frame sent. used
  ARP_REQUEST,                                   // for retransmissions
  TCP_SYN_FRAME,
  TCP_SYN_ACK_FRAME,
  TCP_FIN_FRAME,
  TCP_DATA_FRAME
} TLastFrameSent;

// prototypes
void DoNetworkStuff(MDR_ETHERNET_TypeDef * ETHERNETx);

// Handlers for incoming frames
void ProcessEthBroadcastFrame(uint32_t * ptr_InputBuffer, uint32_t FrameLen  );
void ProcessEthIAFrame(uint32_t * ptr_InputBuffer, uint32_t FrameLen  );
uint32_t ProcessICMPFrame ( void );
void ProcessTCPFrame(void);

// fill TX-buffers
void PrepareARP_REQUEST(void);
void PrepareARP_ANSWER(void);
void PrepareICMP_ECHO_REPLY(void);
void PrepareTCP_FRAME(uint16_t TCPCode);
void PrepareTCP_DATA_FRAME(void);

// general help functions
void SendFrame1(void);
void SendFrame2(void);
void TCPStartRetryTimer(void);
void TCPStartTimeWaitTimer(void);
void TCPRestartTimer(void);
void TCPStopTimer(void);
void TCPHandleRetransmission(void);
void TCPHandleTimeout(void);
uint16_t CalcChecksum(void *Start, uint16_t Count, uint16_t IsTCP);
void TCPClockHandler(void);
uint16_t standard_chksum_opt(void * dataptr, uint32_t len, unsigned char);
uint16_t CalcChecksum_TCP(void * Start, void * data, uint16_t Count, uint32_t CData,  uint8_t IsTCP);

// functions to work with big-endian numbers
uint16_t SwapBytes(uint16_t Data);
void WriteWBE(unsigned char *Add, uint16_t Data);
void WriteDWBE(uint8_t *Add, uint32_t Data);

TTCPStateMachine * TCPIP_init();
// easyWEB-API functions
void TCPLowLevelInit();                      // setup timer, LAN-controller, flags...
void TCPPassiveOpen(void);                       // listen for a connection
void TCPActiveOpen(void);                        // open connection
void TCPClose(void);                             // close connection
void TCPReleaseRxBuffer(void);                   // indicate to discard rec'd packet
void TCPTransmitTxBuffer(uint32_t SizeToSend, uint8_t* Data);	// initiate transfer after TxBuffer is filled

void ETH_InputPachetHandler(MDR_ETHERNET_TypeDef * ETHERNETx);

/* */
typedef struct {
    uint16_t DestAddr[3];
    uint16_t SrcAddr[3];
    uint16_t FrameType;
    uint16_t HardwareType;
    uint16_t ProtocolType;
    uint16_t HardSizeProtSize;
    uint16_t Opcode;
    uint16_t SenderMacAddr[3];
    uint16_t SenderIPAddr[2];
    uint16_t TargetMACAddr[3];
    uint16_t TargetIPAddr[2];
} sARPHead, *pARPHead;

/* */
typedef struct {
    uint16_t DestAddr[3];
    uint16_t SrcAddr[3];
    uint16_t FrameType;
    uint16_t HardwareType;
    uint16_t ProtocolType;
    uint16_t HardSizeProtSize;
    uint16_t Opcode;
    uint16_t SenderMacAddr[3];
    uint16_t SenderIPAddr[2];
    uint16_t TargetMACAddr[3];
    uint16_t TargetIPAddr[2];
} sEthernetARP_Answer, *pEthernetARP_Answer;

/* */
typedef struct {
    uint16_t DestAddr[3];
    uint16_t SrcAddr[3];
    uint16_t FrameType;
    uint16_t IPVerIHL;
    uint16_t FrameLength;
    uint16_t Identification;
    uint16_t Flags_Offset;
    uint16_t ProtocolType_TTL;
    uint16_t SRC_IP_Frame;
    uint16_t SenderIPAddr[2];
    uint16_t TargetIPAddr[2];
    uint16_t Type_and_Code;
    uint16_t CRS;
    uint16_t Identifier;
    uint16_t Sequence_number;
    uint16_t Data;

} sEthernetIP_Frame, *pEthernetIP_Frame;

/* */
typedef struct {
    uint16_t DestAddr[3];
    uint16_t SrcAddr[3];
    uint16_t FrameType;
    uint16_t IPVerIHL;
    uint16_t FrameLength;
    uint16_t Identification;
    uint16_t Flags_Offset;
    uint16_t ProtocolType_TTL;
    uint16_t SRC_IP_Frame;
    uint16_t SenderIPAddr[2];
    uint16_t TargetIPAddr[2];
    uint16_t SRC_port;
    uint16_t DEST_port;
    uint16_t Sequence_number_HI;
    uint16_t Sequence_number_LO;
    uint16_t Acknowlegement_HI;
    uint16_t Acknowlegement_LO;
    uint16_t Offset_data_and_Flags;
    uint16_t Window_size;
    uint32_t Options;
    uint32_t Data;

} sEthernetTCPIP_Frame, *pEthernetTCPIP_Frame;

#endif
