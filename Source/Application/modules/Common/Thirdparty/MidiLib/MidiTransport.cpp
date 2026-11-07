#include "MidiTransport.h"
using namespace Ignite;

void MidiTransport::begin()
{
}

bool MidiTransport::beginTransmission(MidiType type)
{
    _txtype = type;
    _len = 1;
    return true;
}

void MidiTransport::write(uint8_t value)
{
    txBuff[_len++] = value;
}

void MidiTransport::endTransmission()
{
    _cb(txBuff, _len, _txtype);
}

void MidiTransport::sendMessage(const uint8_t* msg, uint8_t len, MidiType type)
{
    _cb((uint8_t*)msg, len, type);
}

uint8_t MidiTransport::read()
{
    uint8_t val = 0;
    if (pRxWr != pRxRd) {
        val = RxFifo[pRxRd];
        RxFifo[pRxRd] = 0; // clear it after read
        pRxRd = (pRxRd + 1) % RX_FIFO_SIZE;
    }
    return val;
}

unsigned MidiTransport::available()
{
    return (pRxWr >= pRxRd) ? (pRxWr - pRxRd) : RX_FIFO_SIZE - (pRxRd - pRxWr);
}

void MidiTransport::byteRcvd(uint8_t byte)
{
    RxFifo[pRxWr] = byte;
    pRxWr = (pRxWr + 1) % RX_FIFO_SIZE;
}
