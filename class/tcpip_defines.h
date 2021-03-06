#ifndef __TCPIP_DEFINES_H

#define __TCPIP_DEFINES_H

// easyWEB-stack definitions
#define MYIP_1               192                 // our internet protocol (IP) address
#define MYIP_2               168
#define MYIP_3               38
#define MYIP_4               1

#define SUBMASK_1            255                 // subnet mask
#define SUBMASK_2            255
#define SUBMASK_3            255
#define SUBMASK_4            0

#define GWIP_1               192                 // standard gateway (used if remote
#define GWIP_2               168                 // IP is no part of our subnet)
#define GWIP_3               1
#define GWIP_4               1


#define MAC_5				0x12
#define MAC_4				0x34
#define MAC_3				0x56
#define MAC_2				0x78
#define MAC_1				0x9a
#define MAC_0				0xbc

#define RETRY_TIMEOUT        10                  // wait max. 8 x 262ms for an ACK (about 2 sec.)
#define FIN_TIMEOUT          2                   // max. time to wait for an ACK of a FIN
                                                 // before closing TCP state-machine (about 0.5 s)
#define MAX_RETRYS           4                   // nr. of resendings before reset conn.
                                                 // total nr. of transmissions = MAX_RETRYS + 1

#define MAX_TCP_TX_DATA_SIZE 2000                 // max. outgoing TCP data size (even!)
#define MAX_TCP_RX_DATA_SIZE 1460*8                 // max. incoming TCP data size (even!)
                                                 // (increasing the buffer-size dramatically
                                                 // increases the transfer-speed!)

#define MAX_ETH_TX_DATA_SIZE 1500                // 2nd buffer, used for ARP, ICMP, TCP (even!)
                                                 // enough to echo 32 byte via ICMP

#define DEFAULT_TTL          255                  // Time To Live sent with packets

// Ethernet network layer definitions
#define ETH_CTRL_FIELD		 4
#define ETH_DA_OFS           0                   // Destination MAC address (48 Bit)
#define ETH_SA_OFS           6                   // Source MAC address (48 Bit)
#define ETH_TYPE_OFS         12                  // Type field (16 Bit)
#define ETH_DATA_OFS         14                  // Frame Data
#define ETH_HEADER_SIZE      14

#define FRAME_ARP            0x0806              // frame types (stored in Type/Length field)
#define FRAME_IP             0x0800

// IPv4 layer definitions
#define IP_VER_IHL_TOS_OFS   ETH_DATA_OFS + 0    // Version, Header Length, Type of Service
#define IP_TOTAL_LENGTH_OFS  ETH_DATA_OFS + 2    // IP Frame's Total Length
#define IP_IDENT_OFS         ETH_DATA_OFS + 4    // Identifying Value
#define IP_FLAGS_FRAG_OFS    ETH_DATA_OFS + 6    // Flags and Fragment Offset
#define IP_TTL_PROT_OFS      ETH_DATA_OFS + 8    // Frame's Time to Live, Protocol
#define IP_HEAD_CHKSUM_OFS   ETH_DATA_OFS + 10   // IP Frame's Header Checksum
#define IP_SOURCE_OFS        ETH_DATA_OFS + 12   // Source Address (32 Bit)
#define IP_DESTINATION_OFS   ETH_DATA_OFS + 16   // Destination Address (32 Bit)
#define IP_DATA_OFS          ETH_DATA_OFS + 20   // Frame Data (if no options)
#define IP_HEADER_SIZE       20                  // w/o options

#define IP_VER_IHL           0x4500              // IPv4, Header Length = 5x32 bit
#define IP_TOS_D             0x0010              // TOS low delay
#define IP_TOS_T             0x0008              // TOS high throughput
#define IP_TOS_R             0x0004              // TOS high reliability

#define IP_FLAG_DONTFRAG     0x4000              // don't fragment IP frame
#define IP_FLAG_MOREFRAG     0x2000              // more fragments available
#define IP_FRAGOFS_MASK      0x1FFF              // indicates where this fragment belongs

#define PROT_ICMP            1                   // Internet Control Message Protocol
#define PROT_TCP             6                   // Transmission Control Protocol
#define PROT_UDP             17                  // User Datagram Protocol

// ARP definitions
#define ARP_HARDW_OFS        ETH_DATA_OFS + 0    // Hardware address type
#define ARP_PROT_OFS         ETH_DATA_OFS + 2    // Protocol
#define ARP_HLEN_PLEN_OFS    ETH_DATA_OFS + 4    // byte length of each hardw. / prot. address
#define ARP_OPCODE_OFS       ETH_DATA_OFS + 6    // Opcode
#define ARP_SENDER_HA_OFS    ETH_DATA_OFS + 8    // Hardw. address of sender of this packet
#define ARP_SENDER_IP_OFS    ETH_DATA_OFS + 14   // IP address of sender
#define ARP_TARGET_HA_OFS    ETH_DATA_OFS + 18   // Hardw. address of target of this packet
#define ARP_TARGET_IP_OFS    ETH_DATA_OFS + 24   // IP address of target
#define ARP_FRAME_SIZE       28

#define HARDW_ETH10          1                   // hardware-type 10Mbps Ethernet
#define IP_HLEN_PLEN         0x0604              // MAC = 6 byte long, IP = 4 byte long
#define OP_ARP_REQUEST       1                   // operations for ARP-frames
#define OP_ARP_ANSWER        2

// ICMP definitions
#define ICMP_TYPE_CODE_OFS   IP_DATA_OFS + 0     // type of message
#define ICMP_CHKSUM_OFS      IP_DATA_OFS + 2     // checksum of ICMP-message (16 bit)
#define ICMP_ID              IP_DATA_OFS + 4
#define ICMP_SEQ_NUM         IP_DATA_OFS + 6
#define ICMP_DATA_OFS        IP_DATA_OFS + 8
#define ICMP_HEADER_SIZE     8

#define ICMP_ECHO            8                   // message is an echo request
#define ICMP_ECHO_REPLY      0                   // message is an echo reply

// TCP layer definitions
#define TCP_SRCPORT_OFS      IP_DATA_OFS + 0     // Source Port (16 bit)
#define TCP_DESTPORT_OFS     IP_DATA_OFS + 2     // Destination Port (16 bit)
#define TCP_SEQNR_OFS        IP_DATA_OFS + 4     // Sequence Number (32 bit)
#define TCP_ACKNR_OFS        IP_DATA_OFS + 8     // Acknowledge Number (32 bit)
#define TCP_DATA_CODE_OFS    IP_DATA_OFS + 12    // Data Offset and Control Bits (16 bit)
#define TCP_WINDOW_OFS       IP_DATA_OFS + 14    // Window Size (16 bit)
#define TCP_CHKSUM_OFS       IP_DATA_OFS + 16    // Checksum Field (16 bit)
#define TCP_URGENT_OFS       IP_DATA_OFS + 18    // Urgent Pointer (16 bit)
#define TCP_DATA_OFS         IP_DATA_OFS + 20    // Frame Data (if no options)
#define TCP_HEADER_SIZE      20                  // size w/o options

#define DATA_OFS_MASK        0xF000              // number of 32 bit words in the TCP Header

#define TCP_CODE_FIN         0x0001
#define TCP_CODE_SYN         0x0002
#define TCP_CODE_RST         0x0004
#define TCP_CODE_PSH         0x0008
#define TCP_CODE_ACK         0x0010
#define TCP_CODE_URG         0x0020

#define TCP_OPT_MSS          0x0204              // Type 2, Option Length 4 (Max. Segment Size)
//#define TCP_OPT_MSS_SIZE     4
#define TCP_OPT_MSS_SIZE     4

// define some TCP standard-ports, useful for testing...
#define TCP_PORT_ECHO        7                   // echo
#define TCP_PORT_DISCARD     9                   // discard
#define TCP_PORT_DAYTIME     13                  // daytime
#define TCP_PORT_QOTD        17                  // quote of the day
#define TCP_PORT_CHARGEN     19                  // character generator
#define TCP_PORT_HTTP        80                  // word wide web HTTP
#define TCP_PORT_TELNET		 23

// macros
#define SWAPB(Word)          ((uint16_t)((Word) << 8) | ((Word) >> 8))
                                                 // convert little <-> big endian
#define SOCK_ACTIVE                    0x01      // state machine NOT closed
#define SOCK_CONNECTED                 0x02      // user may send & receive data
#define SOCK_DATA_AVAILABLE            0x04      // new data available
#define SOCK_TX_BUF_RELEASED           0x08      // user may fill buffer

#define SOCK_ERROR_MASK                0xF0      // bit-mask to check for errors
#define SOCK_ERR_OK                    0x00      // no error
#define SOCK_ERR_ARP_TIMEOUT           0x10      // timeout waiting for an ARP-REPLY
#define SOCK_ERR_TCP_TIMEOUT           0x20      // timeout waiting for an ACK
#define SOCK_ERR_CONN_RESET            0x30      // connection was reset by the other TCP
#define SOCK_ERR_REMOTE                0x40      // remote TCP caused fatal error
#define SOCK_ERR_ETHERNET              0x50      // network interface error (timeout)

// easyWEB-API buffer-pointers
#define TCP_TX_BUF      ((unsigned char *)TxFrame1 + ETH_HEADER_SIZE + IP_HEADER_SIZE + TCP_HEADER_SIZE)
#define TCP_RX_BUF      ((unsigned char *)RxTCPBuffer)
#define CLK_EN_ENET			0x00100000  //PLL_AXI => 20-???? ??????

// constants
#define SEND_FRAME1                    0x01
#define SEND_FRAME2                    0x02

//unsigned char TCPFlags;
#define TCP_ACTIVE_OPEN                0x01      // easyWEB shall initiate a connection
#define IP_ADDR_RESOLVED               0x02      // IP sucessfully resolved to MAC
#define TCP_TIMER_RUNNING              0x04
#define TIMER_TYPE_RETRY               0x08
#define TCP_CLOSE_REQUESTED            0x10

/* Initalizes the LAN-controller, reset flags, starts timer-ISR */
#define DATA_SIZE 8296
#define DATA_LEN (int)DATA_SIZE/6
#define DATA_LEN5 DATA_SIZE - DATA_LEN*5
#define MAX_TCP_DATA_SIZE 1460

#endif
