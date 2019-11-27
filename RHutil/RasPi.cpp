// RasPi.cpp
//
// Routines for implementing RadioHead on Raspberry Pi
// using BCM2835 library for GPIO
//
// Contributed by Mike Poublon and used with permission


#include <RadioHead.h>

#if (RH_PLATFORM == RH_PLATFORM_RASPI)
#include <sys/time.h>
#include <time.h>
#include "RasPi.h"

//Initialize the values for sanity
timeval RHStartTime;

void SPIClass::begin()
{
  //Set SPI Defaults
  uint16_t divider = BCM2835_SPI_CLOCK_DIVIDER_256;
  uint8_t bitorder = BCM2835_SPI_BIT_ORDER_MSBFIRST;
  uint8_t datamode = BCM2835_SPI_MODE0;

  begin(divider, bitorder, datamode);
}

void SPIClass::begin(uint16_t divider, uint8_t bitOrder, uint8_t dataMode)
{
  setClockDivider(divider);
  setBitOrder(bitOrder);
  setDataMode(dataMode);

  //Set CS pins polarity to low
  bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, 0);

  bcm2835_spi_begin();

  //Initialize a timestamp for millis calculation
  gettimeofday(&RHStartTime, NULL);
}

void SPIClass::end()
{
  //End the SPI
  bcm2835_spi_end();
}

void SPIClass::setBitOrder(uint8_t bitOrder)
{
  //Set the SPI bit Order
  bcm2835_spi_setBitOrder(bitOrder);
}

void SPIClass::setDataMode(uint8_t mode)
{
  //Set SPI data mode
  bcm2835_spi_setDataMode(mode);
}

void SPIClass::setClockDivider(uint16_t rate)
{
  //Set SPI clock divider
  bcm2835_spi_setClockDivider(rate);
}

byte SPIClass::transfer(byte _data)
{
  //Set which CS pin to use for next transfers
  bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
  //Transfer 1 byte
  byte data;
  data = bcm2835_spi_transfer((uint8_t)_data);
  return data;
}

void SPIClass::usingInterrupt(uint8_t pin) {
    return;
}

void attachInterrupt(int pin, int mode, void (*function)(void)) {
    wiringPiISR(pin, mode, function);
}

long random(long min, long max)
{
  long diff = max - min;
  long ret = diff * rand() + min;
  return ret;
}

void SerialSimulator::begin(int baud)
{
  //No implementation neccesary - Serial emulation on Linux = standard console
  //
  //Initialize a timestamp for millis calculation - we do this here as well in case SPI
  //isn't used for some reason
  gettimeofday(&RHStartTime, NULL);
}

size_t SerialSimulator::println(const char* s)
{
  print(s);
  printf("\n");
}

size_t SerialSimulator::print(const char* s)
{
  printf(s);
}

size_t SerialSimulator::print(unsigned int n, int base)
{
  if (base == DEC)
    printf("%d", n);
  else if (base == HEX)
    printf("%02x", n);
  else if (base == OCT)
    printf("%o", n);
  // TODO: BIN
}

size_t SerialSimulator::print(char ch)
{
  printf("%c", ch);
}

size_t SerialSimulator::println(char ch)
{
  printf("%c\n", ch);
}

size_t SerialSimulator::print(unsigned char ch, int base)
{
  return print((unsigned int)ch, base);
}

size_t SerialSimulator::println(unsigned char ch, int base)
{
  print((unsigned int)ch, base);
  printf("\n");
}

#endif
