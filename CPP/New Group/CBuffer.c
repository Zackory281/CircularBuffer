//
//  CBuffer.c
//  CPP
//
//  Created by Zackori Cui on 2/9/20.
//  Copyright © 2020 Zackori Cui. All rights reserved.
//

#include "CBuffer.h"
#include <stdlib.h>

static inline size_t getStartIndexOffset(size_t index, size_t offset, size_t length, size_t size) {
    return (index + length + offset) % size;
}

static inline size_t getStartIndex(size_t index, size_t length, size_t size) {
    return getStartIndexOffset(index, 0, length, size);
}

static inline void increamentIndexBy(size_t* index, size_t amount, size_t size) {
    *index = (*index + amount) % size;
}

static inline void increamentIndex(size_t* index, size_t size) {
    increamentIndexBy(index, 1, size);
}

void InitCircularBufferFromMem(CircularBuffer* ptr, char* buffer, uint16_t size) {
    ptr->size = size;
    ptr->index = 0;
    ptr->length = 0;
    ptr->buffer = buffer;
}

CircularBuffer* InitCircularBuffer(uint16_t size) {
    CircularBuffer* ptr = malloc(sizeof(CircularBuffer));
    InitCircularBufferFromMem(ptr, malloc(size), size);
    return ptr;
}

extern inline void DeinitCircularBuffer(CircularBuffer* ptr) {
    free(ptr->buffer);
    free(ptr);
}

uint8_t CBuffer_addElements(CircularBuffer* ptr, char* data, size_t length) {
    size_t size = ptr->size, blength = ptr->length, afterLen = blength + length, startIndex;
    if (afterLen > ptr->size) {
        return 0;
    }
    startIndex = getStartIndex(ptr->index, blength, size);
    while (length--) {
        ptr->buffer[startIndex] = *data++;
        increamentIndex(&startIndex, size);
    }
    ptr->length = afterLen;
    return 1;
}

extern inline uint8_t CBuffer_add(CircularBuffer* ptr, char data) {
    return CBuffer_addElements(ptr, &data, 1);
}

uint8_t CBuffer_get(CircularBuffer* ptr, char* dst, size_t index) {
    if (ptr->length <= index) {
        return 0;
    }
    *dst = ptr->buffer[getStartIndexOffset(ptr->index, index, ptr->length, ptr->size)];
    return 1;
}

uint8_t CBuffer_popElementsFront(CircularBuffer* ptr, char* dst, size_t length) {
    size_t blength = ptr->length, afterLength = blength - length, currIndex, size;
    if (afterLength < 0) {
        return 0;
    }
    size = ptr->size;
    currIndex = getStartIndex(ptr->index, blength, size);
    while (length--) {
        *dst = ptr->buffer[currIndex];
        increamentIndex(&currIndex, size);
    }
    if (afterLength == 0) {
        ptr->index = 0;
        ptr->length = 0;
        return 1;
    }
    ptr->index = currIndex;
    ptr->length = afterLength;
    return 1;
}

uint8_t CBuffer_removeElementsFront(CircularBuffer* ptr, size_t length) {
    size_t blength = ptr->length, afterLength = blength - length;
    if (afterLength < 0) {
        return 0;
    }
    if (afterLength == 0) {
        ptr->index = 0;
        ptr->length = 0;
        return 1;
    }
    increamentIndexBy(&(ptr->index), length, ptr->size);
    ptr->length = afterLength;
    return 1;
}

extern inline uint8_t CBuffer_removeElementFront(CircularBuffer* ptr) {
    return CBuffer_removeElementsFront(ptr, 1);
}

extern inline size_t CBuffer_getLength(CircularBuffer* ptr) {
    return ptr->length;
}

extern inline size_t CBuffer_getSize(CircularBuffer* ptr) {
    return ptr->size;
}

extern inline uint8_t CBuffer_isEmpty(CircularBuffer* ptr) {
    return ptr->length == 0;
}

extern inline uint8_t CBuffer_isFull(CircularBuffer* ptr) {
    return ptr->length == ptr->size;
}
