/*
 * File:    circularbuffer.h
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

#include "basic_datatypes.h"

#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

#ifdef __cplusplus
extern "C" {
#endif

    /** \struct circularBuffer_t
     * 
     * circular buffer 'object'
     * 
     * \warning buffer size must be a power of 2.
     */
    typedef struct {
        /** \var buffer
         * pointer to our buffer. 
         * \pre you have to allocate memory for proper use
         */
        uint8_t *buffer;
        /** \var size
         * size of our circular buffer
         */
        uint32_t size;
        /** \var messageStart
         * current read start position.
         * 
         * possible values are 0 to size-1
         */
        uint32_t messageStart;
        /** \var messageEnd
         * current read end position.
         * 
         * possible values are 0 to size-1
         */
        uint32_t messageEnd;
        /** \var datafieldStart
         * data start position, use this index!
         * 
         * possible values are 0 to size-1
         */
        uint32_t datafieldStart;
        /** \var datafieldEnd
         * delimiter of the datafield, it's not part of the data, it's a comma!
         * 
         * possible values are 0 to size-1
         */
        uint32_t datafieldEnd;
        /** \var write
         * current write position.
         * 
         * possible values are 0 to size-1
         */
        uint32_t write;
    } circularBuffer_t;

    /** \enum bufferError_t
     * enumeration of possible buffer errors.
     */
    typedef enum {
        NOERROR = 0,
        BUFFERFULL,
        BUFFEREMPTY,
        NOMESSAGE
    } bufferError_t;

    extern uint32_t circularBufferCalculateBufferSize(const uint32_t minimumBufferSize);
    extern uint32_t circularBufferIndexIncrease(circularBuffer_t *cBuffer, uint32_t index, uint32_t incr);
    extern uint32_t circularBufferMessageStartIncrease(circularBuffer_t *cBuffer, uint32_t incr);
    extern uint32_t circularBufferMessageEndIncrease(circularBuffer_t *cBuffer, uint32_t incr);
    extern void circularBufferMessageStartPlusPlus(circularBuffer_t *cBuffer);
    extern bufferError_t circularBufferWrite(circularBuffer_t *cBuffer, const uint8_t message[], const uint32_t messageLength);
    extern bufferError_t circularBufferGetMessageStart(circularBuffer_t *cBuffer);
    extern void circularBufferGetNextNMEADatafield(circularBuffer_t *cBuffer);
    extern void circularBufferSetMessageStartToEndOfMessage(circularBuffer_t *cBuffer);
    extern uint32_t circularBufferMessageLength(circularBuffer_t *cBuffer);
    extern uint32_t circularBufferNMEADatafieldLength(circularBuffer_t *cBuffer);
    extern uint32_t circularBufferDataLength(circularBuffer_t *cBuffer);

#ifdef __cplusplus
}
#endif

#endif /* CIRCULARBUFFER_H */
