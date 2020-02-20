#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "modbus.h"

#define R "\e[1;31m"
#define G "\e[1;32m"
#define Y "\e[1;33m"
#define B "\e[1;34m"
#define P "\e[1;35m"
#define C "\e[1;36m"
#define E "\e[0m"

#define MAX_BIT 32767
#define MAX_REGISTER_VALUE 65535

void modbus_read_print_bits(modbus_t *ctx);
void modbus_read_print_registers(modbus_t *ctx);
void modbus_print_registers(modbus_t *ctx, int start_addr, int size);
void modbus_print_bits(modbus_t *ctx, int start_addr, int size);
void modbus_write_bits_wrapper(modbus_t *ctx);
void modbus_write_register_wrapper(modbus_t *ctx);
void error_handling();

int main(int c, char ** v)
{
    if (c != 2)
    {
        fputs("Usage : ./modTCPClient <Modbus_Server_IP>\n", stderr);
        return EXIT_FAILURE;
    }
    int select;
    int addr;
    modbus_t *ctx;

    ctx = modbus_new_tcp(v[1], 502);
    if (modbus_connect(ctx) == -1)
    {
        fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
        modbus_free(ctx);
        return EXIT_FAILURE;
    }

    do
    {
        fputs(
            B"Which function do you want?\n"E
            C"[1]"E" : Read Coils\n"
            C"[2]"E" : Write multiple Coils\n"
            C"[3]"E" : Read Holding Registers\n"
            C"[4]"E" : Write multiple (Holding) Registers\n"
            C"[5]"E" : Quit\n"
            Y"Select a function "E"> "
            , stdout
        );
        scanf("%d", &select);

        switch (select)
        {
        case 1:
            modbus_read_print_bits(ctx);
            break;
        case 2:
            modbus_write_bits_wrapper(ctx);
            break;
        case 3:
            modbus_read_print_registers(ctx);
            break;
        case 4:
            modbus_write_register_wrapper(ctx);
            break;
        case 5:
            puts("Exit program");
            break;
        default:
            puts(R "Invaild option!!"E);
            break;
        }
    } while(select!=5);

    modbus_close(ctx);
    modbus_free(ctx);
}

void modbus_print_bits(modbus_t *ctx, int start_addr, int size)
{
    int rc;
    int i;
    uint8_t tab_reg[MAX_BIT];
    rc = modbus_read_bits(ctx, start_addr, size, tab_reg);
    if (rc == -1)
        error_handling();
    puts(B"lqqqqqqqqqqqqqqqqqk"E);
    for (i=0; i < rc; i++, start_addr++)
        printf(B"x"E" coil[" R "%5d"E"] = "C"%d "E B"x\n", start_addr, tab_reg[i]);
    puts(B"mqqqqqqqqqqqqqqqqqj"E);
}

void modbus_print_registers(modbus_t *ctx, int start_addr, int size)
{
    int rc;
    int i;
    uint16_t tab_reg[MAX_BIT];
    rc = modbus_read_registers(ctx, start_addr, size, tab_reg);
    if (rc == -1)
        error_handling();
    puts(B"lqqqqqqqqqqqqqqqqqqqqk"E);
    for (i=0; i < rc; i++, start_addr++)
        printf(B"x"E" reg[" R "%5d"E"] = "C"%-5d "E B"x\n", start_addr, tab_reg[i]);
    puts(B"mqqqqqqqqqqqqqqqqqqqqj"E);
}

void modbus_read_print_bits(modbus_t *ctx)
{
    int start_addr;
    int size;

    printf(G"Enter the start address (0 ~ %d)"E"> ", MAX_BIT);
    scanf("%d", &start_addr);
    if (start_addr < 0 || start_addr > MAX_BIT)
    {
        fputs("Invalid range\n", stderr);
        return;
    }

    printf(G"Enter the number of coils to be read (1 ~ %d)"E"> ", MAX_BIT - start_addr + 1);
    scanf("%d", &size);
    if (size < 1 || size > MAX_BIT - start_addr + 1)
    {
        fputs("Invalid size\n", stderr);
        return;
    }

    modbus_print_bits(ctx, start_addr, size);
}

void modbus_read_print_registers(modbus_t *ctx)
{
    int start_addr;
    int size;

    printf(G"Enter the start address (0 ~ %d)"E"> ", MAX_BIT);
    scanf("%d", &start_addr);
    if (start_addr < 0 || start_addr > MAX_BIT)
    {
        fputs("Invalid range\n", stderr);
        return;
    }

    printf(G"Enter the number of registers to be read (1 ~ %d)"E"> ", MAX_BIT - start_addr + 1);
    scanf("%d", &size);
    if (size < 1 || size > MAX_BIT - start_addr + 1)
    {
        fputs("Invalid size\n", stderr);
        return;
    }

    modbus_print_registers(ctx, start_addr, size);
}

void modbus_write_bits_wrapper(modbus_t *ctx)
{
    int start_addr;
    int data;
    int nb;
    int i;
    uint8_t tab_reg[MAX_BIT];

    printf(G"Enter the address to write data into Coil (0 ~ %d)"E" > ", MAX_BIT);
    scanf("%d", &start_addr);
    if (start_addr < 0 || start_addr > MAX_BIT)
    {
        fputs(R "Invalid range\n"E, stderr);
        return;
    }

    printf(G"Enter count of data to write (1 ~ %d)"E" > ", MAX_BIT - start_addr + 1);
    scanf("%d", &nb);
    if (nb < 1 || nb > MAX_BIT - start_addr + 1)
    {
        fputs(R "Invalid count\n"E, stderr);
        return;
    }

    for(i=0; i<nb; i++)
    {
        printf(G"Enter the status(0 or 1)"E" of coil["R "%d"E"] > ", start_addr + i);
        scanf("%d", &tab_reg[i]);
        if(tab_reg[i] != 0 && tab_reg[i] != 1)
        {
            fputs(R "Invalid status\n"E, stderr);
            i--;
            continue;
        }
    }

    modbus_write_bits(ctx, start_addr, nb, tab_reg);
    modbus_print_bits(ctx, start_addr, nb);
}

void modbus_write_register_wrapper(modbus_t *ctx)
{
    int start_addr;
    int data;
    int nb;
    int i;
    int tmp;
    uint16_t tab_reg[MAX_BIT];

    printf(G"Enter the address to write data into Register (0 ~ %d)"E" > ", MAX_BIT);
    scanf("%d", &start_addr);
    if (start_addr < 0 || start_addr > MAX_BIT)
    {
        fputs(R "Invalid range\n"E, stderr);
        return;
    }

    printf(G"Enter count of data to write (1 ~ %d)"E" > ", MAX_BIT - start_addr + 1);
    scanf("%d", &nb);
    if (nb < 1 || nb > MAX_BIT - start_addr + 1)
    {
        fputs(R "Invalid count\n"E, stderr);
        return;
    }

    for(i=0; i<nb; i++)
    {
        printf(G"Enter the value(0 ~ %d)"E " of reg["R "%d"E"] > ", MAX_REGISTER_VALUE, start_addr + i);
        scanf("%d", &tmp);
        if (tmp < 0 || tmp > MAX_REGISTER_VALUE)
        {
            fputs(R "Invalid range\n"E, stderr);
            i--;
            continue;
        }
        tab_reg[i] = (uint16_t) tmp;
    }

    modbus_write_registers(ctx, start_addr, nb, tab_reg);
    modbus_print_registers(ctx, start_addr, nb);
}

void error_handling()
{
    fprintf(stderr, "%s\n", modbus_strerror(errno));
    exit(1);
}