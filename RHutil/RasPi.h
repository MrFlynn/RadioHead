// RasPi.h
//
// Routines for implementing RadioHead on Raspberry Pi
// using BCM2835 library for GPIO
// Contributed by Mike Poublon and used with permission

#ifndef RASPI_h
#define RASPI_h

#define RISING 2

extern "C" {
    #include <wiringPi.h> // Add ISR capability.
}

#include <bcm2835.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

typedef unsigned char byte;

#ifndef NULL
  #define NULL 0
#endif

#ifndef OUTPUT
  #define OUTPUT BCM2835_GPIO_FSEL_OUTP
#endif

class SPIClass
{
  public:
    static byte transfer(byte _data);
    // SPI Configuration methods
    static void begin(); // Default
    static void begin(uint16_t, uint8_t, uint8_t);
    static void end();
    static void setBitOrder(uint8_t);
    static void setDataMode(uint8_t);
    static void setClockDivider(uint16_t);
    static void usingInterrupt(uint8_t);
};

extern SPIClass SPI;

class SerialSimulator
{
  public:
    #define DEC 10
    #define HEX 16
    #define OCT 8
    #define BIN 2

    // TODO: move these from being inlined
    static void begin(int baud);
    static size_t println(const char* s);
    static size_t print(const char* s);
    static size_t print(unsigned int n, int base = DEC);
    static size_t print(char ch);
    static size_t println(char ch);
    static size_t print(unsigned char ch, int base = DEC);
    static size_t println(unsigned char ch, int base = DEC);
};

extern SerialSimulator Serial;

void RasPiSetup();

void attachInterrupt(int pin, void (*function)(void), int mode);

long random(long min, long max);

#endif
