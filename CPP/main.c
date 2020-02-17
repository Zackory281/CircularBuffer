//
//  main.c
//  CPP
//
//  Created by Zackori Cui on 2/9/20.
//  Copyright © 2020 Zackori Cui. All rights reserved.
//

#include <stdio.h>
#include "CBuffer.h"

void assertTrue(char* str, uint8_t value);

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    CircularBuffer* cbptr = InitCircularBuffer(3);
    printf("Size: %zu\n", CBuffer_getSize(cbptr));
    printf("Length: %zu\n", CBuffer_getLength(cbptr));
    assertTrue("Adding a char", CBuffer_add(cbptr, 'i'));
    assertTrue("Adding a char", CBuffer_add(cbptr, 'l'));
    assertTrue("Adding a char", CBuffer_add(cbptr, 'k'));
    assertTrue("Adding a char", CBuffer_add(cbptr, 'L'));
    CBuffer_removeElementFront(cbptr);
    assertTrue("Adding a char", CBuffer_add(cbptr, 'K'));
    char c;
    printf("Is full %d\n", CBuffer_isFull(cbptr));
    CBuffer_get(cbptr, &c, 0);
    //printf("0th: %d", CBuffer_get(<#CircularBuffer *ptr#>, <#char *dst#>, <#size_t index#>))
    return 0;
}

void assertTrue(char* str, uint8_t value) {
    printf("%s, %s\n", str, value ? "Pass" : "Fail");
}
