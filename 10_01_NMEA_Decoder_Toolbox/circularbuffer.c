/*
 * File:    circularbuffer.c
 *
 * Created on 16. September 2017, 16:09
 *
 * Copyright (c) 2017 michael breuer <michael.breuer@ilsf.de>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <math.h>

#include "circularbuffer.h"

/** circularBufferCalculateBufferSize
 * 
 * calculate smallest power of 2 bigger than minimum buffer size.
 * 
 * @param[in] unsigned short int minimum required buffer size
 * @return unsigned short int calculated buffer size
 */
uint32_t circularBufferCalculateBufferSize(const uint32_t minimumBufferSize) {
    uint32_t bufferSize = 0;
    int j = 0;

    /* \warning buffer size may be power of 2, computing smallest possible value */
    while (bufferSize < minimumBufferSize) {
        j++;
        bufferSize = pow(2, j);
    }

    return (bufferSize);
}

/*
 * bufferIndexIncrease
 * 
 * return: new index. no changes to cBuffer by this function!
 */
uint32_t circularBufferIndexIncrease(circularBuffer_t *cBuffer, uint32_t index, uint32_t incr) {
    return ((index + incr) & (cBuffer->size - 1)); // must be atomic
}

/*
 * messageStartIncrease
 * 
 * return: new index. no changes to cBuffer by this function!
 */
uint32_t circularBufferMessageStartIncrease(circularBuffer_t *cBuffer, uint32_t incr) {
    return (circularBufferIndexIncrease(cBuffer, cBuffer->messageStart, incr));
}

/*
 * messageEndIncrease
 * 
 * return: new index. no changes to cBuffer by this function!
 */
uint32_t circularBufferMessageEndIncrease(circularBuffer_t *cBuffer, uint32_t incr) {
    return (circularBufferIndexIncrease(cBuffer, cBuffer->messageEnd, incr));
}

/*
 * messageStartPlusPlus increases +1
 * 
 * return: no return value. cBuffer will be changed.
 */
void circularBufferMessageStartPlusPlus(circularBuffer_t *cBuffer) {
    cBuffer->messageStart = circularBufferMessageStartIncrease(cBuffer, 1);
    return;
}

/**
 * write new data to circular buffer
 * 
 * @param cBuffer
 * @param message
 * @param messageLength
 * @return 
 */
bufferError_t circularBufferWrite(circularBuffer_t *cBuffer, const uint8_t message[], const uint32_t messageLength) {
    int i;
    for (i = 0; i < messageLength; i++) {
        cBuffer->buffer[cBuffer->write] = message[i]; // (uint8_t)
        cBuffer->write = circularBufferIndexIncrease(cBuffer, cBuffer->write, 1);
    }
    if (circularBufferDataLength(cBuffer) + messageLength > (cBuffer->size - 1)) {
        /* discard oldest data if not enough memory avalaible (already done at this point ;-) */
        cBuffer->messageStart = circularBufferIndexIncrease(cBuffer, cBuffer->messageStart, messageLength);
        return (BUFFERFULL);
    } else {
        return (NOERROR);
    }
}

/*
 * get next message start in circular buffer
 */
bufferError_t circularBufferGetMessageStart(circularBuffer_t *cBuffer) {
    while (cBuffer->buffer[cBuffer->messageStart] != '$' && cBuffer->buffer[cBuffer->messageStart] != '!' && circularBufferDataLength(cBuffer) > 1) {
        circularBufferMessageStartPlusPlus(cBuffer);
    }
    if (cBuffer->buffer[cBuffer->messageStart] == '$' || cBuffer->buffer[cBuffer->messageStart] == '!') {
        return (NOERROR);
    } else {
        return (NOMESSAGE);
    }
}

/*
 * get next datafield delimiter in nmea message - circular buffer
 */
void circularBufferGetNextNMEADatafield(circularBuffer_t *cBuffer) {
    cBuffer->datafieldStart = circularBufferIndexIncrease(cBuffer, cBuffer->datafieldEnd, 1);
    cBuffer->datafieldEnd = cBuffer->datafieldStart;
    while (cBuffer->buffer[cBuffer->datafieldEnd] != ',' && cBuffer->buffer[cBuffer->datafieldEnd] != '*' && cBuffer->buffer[cBuffer->datafieldEnd] != '\r') {
        cBuffer->datafieldEnd = circularBufferIndexIncrease(cBuffer, cBuffer->datafieldEnd, 1);
    }
    //cBuffer->datafieldEnd = circularBufferIndexIncrease(cBuffer, cBuffer->datafieldEnd, 1);
}

/*
 * set message start to end of current message
 */
void circularBufferSetMessageStartToEndOfMessage(circularBuffer_t *cBuffer) {
    cBuffer->messageStart = cBuffer->messageEnd;
    return;
}

/**
 * length of current (nmea) message in circular buffer. the used pointers in 
 * this function are messageStart (our general "read" pointer) and messageEnd 
 * (currently used only by nmea interface). This function requires the buffer 
 * size to be power of 2.
 * 
 * @param cBuffer ringbuffer
 * @return number of bytes between messageEnd and messageStart pointer
 */
uint32_t circularBufferMessageLength(circularBuffer_t *cBuffer) {
    return ((cBuffer->messageEnd - cBuffer->messageStart) & (cBuffer->size - 1)); // must be atomic
}

/**
 * length of current NMEA datafield in circular buffer
 * includes comma at endof data field!
 * req: buffer size is power of 2!
 * 
 * @param cBuffer
 * @return 
 */
uint32_t circularBufferNMEADatafieldLength(circularBuffer_t *cBuffer) {
    return ((cBuffer->datafieldEnd - cBuffer->datafieldStart) & (cBuffer->size - 1)); // must be atomic
}

/**
 * Returns the number of bytes in buffer.
 * 
 * Calculated using the read (messageStart) and write (write) pointer. This 
 * function requires the buffer size to be power of 2.
 * 
 * @param cBuffer
 * @return number of bytes stored in buffer
 */
uint32_t circularBufferDataLength(circularBuffer_t *cBuffer) {
    return ((cBuffer->write - cBuffer->messageStart) & (cBuffer->size - 1)); // must be atomic
}
