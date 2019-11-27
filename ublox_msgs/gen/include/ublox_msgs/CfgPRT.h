#pragma once

#include <cstdint>

namespace ublox_msgs {
    struct CfgPRT {
        // CFG-PRT (0x06 0x00);
        // Port Configuration for DDC, UART, USB, SPI
        //;
        // Several configurations can be concatenated to one input message. In this case 
        // the payload length can be a multiple of the normal length (see the other;
        // versions of CFG-PRT). Output messages from the module contain only one
        // configuration unit.;
        //
        
        static constexpr uint8_t CLASS_ID = 6;
        static constexpr uint8_t MESSAGE_ID = 0;
        
        uint8_t portID;              // Port Identifier Number
        static constexpr uint8_t PORT_ID_DDC = 0;
        static constexpr uint8_t PORT_ID_UART1 = 1;
        static constexpr uint8_t PORT_ID_UART2 = 2;
        static constexpr uint8_t PORT_ID_USB = 3;
        static constexpr uint8_t PORT_ID_SPI = 4;
        
        uint8_t reserved0;           // Reserved
        
        uint16_t txReady;            // TX ready PIN configuration (since Firmware 7.01)
                                  // reserved (Always set to zero) up to Firmware 7.01;
                                  
        static constexpr uint16_t TX_READY_EN = 1;                    // Enable TX ready feature for this 
                                                  // port;
        static constexpr uint16_t TX_READY_POLARITY_HIGH_ACTIVE = 0;  // Polarity High-active
        static constexpr uint16_t TX_READY_POLARITY_LOW_ACTIVE = 2;   // Polarity Low-active
        static constexpr uint16_t TX_READY_PIN_SHIFT = 2;             // PIO to be used (must not be in use
                                                  // already by another function);
        static constexpr uint16_t TX_READY_PIN_MASK = 124;            //
        static constexpr uint16_t TX_READY_THRES_SHIFT = 7;           // Threshold
        static constexpr uint16_t TX_READY_THRES_MASK = 65408;        // The given threshold is multiplied by
                                                  // 8 bytes.;
                                                  // The TX ready PIN goes active 
                                                  // after >= thres*8 bytes are pending;
                                                  // for the port and going inactive
                                                  // after the last pending bytes have;
                                                  // been written to hardware (0-4 bytes
                                                  // before end of stream).;
        
        uint32_t mode;               // A bit mask describing the DDC, UART or SPI mode 
                                  // Reserved for USB;
        // DDC Mode Constants
        static constexpr uint32_t MODE_DDC_SLAVE_ADDR_SHIFT = 1;      
        static constexpr uint32_t MODE_DDC_SLAVE_ADDR_MASK = 254;     // Slave address
                                                  // Range: 0x07 < slaveAddr < 0x78.; 
        // UART Mode Constants
        static constexpr uint32_t MODE_RESERVED1 = 16;                // Default 1 for compatibility with A4
        static constexpr uint32_t MODE_CHAR_LEN_MASK = 192;           // Character Length
        static constexpr uint32_t MODE_CHAR_LEN_5BIT = 0;               // 5bit (not supported)
        static constexpr uint32_t MODE_CHAR_LEN_6BIT = 64;              // 6bit (not supported)
        static constexpr uint32_t MODE_CHAR_LEN_7BIT = 128;             // 7bit (supported only with parity)
        static constexpr uint32_t MODE_CHAR_LEN_8BIT = 192;             // 8bit
        static constexpr uint32_t MODE_PARITY_MASK = 3584;            //
        static constexpr uint32_t MODE_PARITY_EVEN = 0;                 // Even Parity
        static constexpr uint32_t MODE_PARITY_ODD = 512;                // Odd Parity
        static constexpr uint32_t MODE_PARITY_NO = 2048;                // No Parity (even/odd ignored)
        static constexpr uint32_t MODE_STOP_BITS_MASK = 12288;        // Number of Stop Bits
        static constexpr uint32_t MODE_STOP_BITS_1 = 0;                 // 1 Stop Bit
        static constexpr uint32_t MODE_STOP_BITS_15 = 4096;             // 1.5 Stop Bit
        static constexpr uint32_t MODE_STOP_BITS_2 = 8192;              // 2 Stop Bit
        static constexpr uint32_t MODE_STOP_BITS_05 = 12288;            // 0.5 Stop Bit
        // SPI Mode Constants;
        static constexpr uint32_t MODE_SPI_SPI_MODE_CPOL = 4;         // SPI Mode CPOL (0/1)
        static constexpr uint32_t MODE_SPI_SPI_MODE_CPHA = 2;         // SPI Mode CPH (0/1)
                                                  // (both CPOL/CPHA) can be = 1;
        static constexpr uint32_t MODE_SPI_FLOW_CONTROL = 64;         // (u-blox 6 only)
                                                  // 0 Flow control disabled;
                                                  // 1 Flow control enabled (9-bit mode)
        static constexpr uint32_t MODE_SPI_FF_COUNT_SHIFT = 8;
        static constexpr uint32_t MODE_SPI_FF_COUNT_MASK = 16128;     // Number of bytes containing 0xFF to
                                                  // receive before switching off; 
                                                  // reception. 
                                                  // Range: 0(mechanism off)-63;
        
        uint32_t baudRate;           // UART Baudrate in bits/second [bits/s]
                                  // Reserved for USB, SPI, DDC;
                                  // Possible values: 4800, 9600, 19200, 38400, 57600, 
                                  //                  115200, 230400, 460800;
        
        uint16_t inProtoMask;        // A mask describing which input protocols are active.
                                  // Each bit of this mask is used for a protocol.;
                                  // Through that, multiple protocols can be defined
                                  // on a single port.;
        
        uint16_t outProtoMask;       // A mask describing which output protocols are active.
                                  // Each bit of this mask is used for a protocol.;
                                  // Through that, multiple protocols can be defined
                                  // on a single port.;
        
        static constexpr uint16_t PROTO_UBX = 1;
        static constexpr uint16_t PROTO_NMEA = 2;
        static constexpr uint16_t PROTO_RTCM = 4;     // only for inProtoMask
        static constexpr uint16_t PROTO_RTCM3 = 32;   // (not supported in protocol versions less than 20)
        
        uint16_t flags;              // Flags for UART & SPI, Reserved for USB
        static constexpr uint16_t FLAGS_EXTENDED_TX_TIMEOUT = 2;  // if set, the port will timeout if 
                                              // allocated TX memory >=4 kB and no; 
                                              // activity for 1.5s. If not set the port 
                                              // will timoout if no activity for 1.5s; 
                                              // regardless on the amount of allocated 
                                              // TX memory.;
        
        uint16_t reserved1;          // Always set to zero

    };
}
