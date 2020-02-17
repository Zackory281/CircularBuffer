//
//  CBuffer.h
//  CPP
//
//  Created by Zackori Cui on 2/9/20.
//  Copyright © 2020 Zackori Cui. All rights reserved.
//

#ifndef CBuffer_h
#define CBuffer_h

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    size_t size;
    size_t index;
    size_t length;
    char* buffer;
} CircularBuffer;

void InitCircularBufferFromMem(CircularBuffer* ptr, char* buffer, uint16_t size);
CircularBuffer* InitCircularBuffer(uint16_t size);
extern inline void DeinitCircularBuffer(CircularBuffer* ptr);
uint8_t CBuffer_addElements(CircularBuffer* ptr, char* data, size_t length);
uint8_t CBuffer_add(CircularBuffer* ptr, char data);
uint8_t CBuffer_get(CircularBuffer* ptr, char* dst, size_t index);
uint8_t CBuffer_popElementsFront(CircularBuffer* ptr, char* dst, size_t length);
uint8_t CBuffer_removeElementsFront(CircularBuffer* ptr, size_t length);
uint8_t CBuffer_removeElementFront(CircularBuffer* ptr);
size_t CBuffer_getLength(CircularBuffer* ptr);
size_t CBuffer_getSize(CircularBuffer* ptr);
uint8_t CBuffer_isEmpty(CircularBuffer* ptr);
uint8_t CBuffer_isFull(CircularBuffer* ptr);

#endif /* CBuffer_h */
