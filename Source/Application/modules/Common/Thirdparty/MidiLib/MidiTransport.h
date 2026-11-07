#pragma once
#include "midi_Defs.h"
#include <stdint.h>
namespace Ignite {

#define RX_FIFO_SIZE (512)
#define TX_FIFO_SIZE (64)

using MidiTransmitCallback = void (*)(uint8_t* data, uint8_t length, MidiType type);
class MidiTransport {

public:
    MidiTransport(MidiTransmitCallback cb)
        : _cb(cb)
        , RxFifo {}
        , txBuff {}
    {
    }
    void begin();
    bool beginTransmission(MidiType type);
    void write(uint8_t value);
    void endTransmission();
    void sendMessage(const uint8_t* msg, uint8_t len, MidiType type);
    uint8_t read();
    unsigned available();
    void byteRcvd(uint8_t byte);

private:
    MidiTransmitCallback _cb = nullptr;
    MidiType _txtype = MidiType::InvalidType;
    uint8_t _len = 0;
    uint32_t pRxRd = 0;
    uint32_t pRxWr = 0;
    uint8_t RxFifo[RX_FIFO_SIZE];
    uint8_t txBuff[TX_FIFO_SIZE];
};
}
