/*
1. maximum table entries = page number * page offset = 2^16 = 65536
2. 2^10 = 1024 byte
3. 24800 / 1024 = 24.21875 -> 25 pages
*/

#include <stdio.h>
#include <stdlib.h>

#define BitsForPageNo 6
#define BitsForPageOffset 10

#define ProcessSize 24800

void init_page_table(int table[], int no_page);
char* to_binary(unsigned short addr);
unsigned short logical2physical(unsigned short logical_addr, int page_table[]);

int main(){
    int no_page = 0;
    int * page_table = NULL;

    //logical addresses to test case logical2physical() - can be changed
    unsigned short logical_addr[] = {0x21dd, 0x0829, 0x08f0, 0x0ad1, 0x071e,\
        0x0431, 0x0fb8, 0x0b18, 0x38ab, 0x07a0};
    
    int i = 0;
    //print maximum # of pages and page size
    no_page = ProcessSize / (1<<BitsForPageOffset) + 1;
    printf("noPages = %d\n", no_page);//
    page_table = (int*)malloc(no_page * sizeof(int));
    if(page_table == NULL){
        printf("Failed to allocate memroy!\n");
        exit(-1);
    }

    init_page_table(page_table, no_page);

    for(i=0; i<10; i++){
        unsigned short physical_addr = logical2physical(logical_addr[i], page_table);
        printf("0x%04x (%s) ", logical_addr[i], to_binary(logical_addr[i]));
        printf("--> 0x%04x (%s)\n", physical_addr, to_binary(physical_addr));
    }

    free(page_table);

    return 0;
}

void init_page_table(int table[], int no_page){
    int i = 0;

    for(i=0; i<no_page; i++){
        table[i] = 60 - i * 2;
    }
}

char* to_binary(unsigned short addr){
    static char bits[17];
    int i = 0;
    for(i=0; i<16; i++){
        bits[15-i] = '0'+(addr&1);
        addr>>=1;
    }

    bits[16] = 0;

    return bits;
}

unsigned short logical2physical(unsigned short logical_addr, int page_table[]){
    unsigned short page_number = logical_addr >> 10;
    unsigned short page_offset = logical_addr & 0x03ff;
    unsigned short frame_number = page_table[page_number];
    
    unsigned short physical_addr = frame_number|0;
    physical_addr <<= 10;
    physical_addr |= page_offset;

    return physical_addr;
}
