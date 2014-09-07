#include "TinyWireS.h"

namespace Codes
{

typedef uint32_t Code;

namespace Power
{
Code Toggle = 0xA55A38C7;
Code On = 0xA55A58A7;
Code Off = 0xA55AD827;
}

namespace Volume
{
Code Up = 0xA55A50AF;
Code Down = 0xA55AD02F;
}

namespace Mute
{
Code Toggle = 0xA55A48B7;
Code On = 0xA55A8A75;
Code Off = 0xA55A4AB5;
}

}

namespace IR
{
class Sender
{
  uint8_t pins;

public:
  Sender(uint8_t pins):
    pins(pins)
  {
  }

  void blink(unsigned long us)
  {
    for (size_t i = 0; i < (us / 26); i++)
    {
      PORTB |= pins;
      delayMicroseconds(9);
      PORTB &= ~pins;
      delayMicroseconds(9);
    }
  }

  void header()
  {
    blink(9000);
    delayMicroseconds(4500);
  }

  void one()
  {
    blink(562);
    delayMicroseconds(1686);
  }

  void zero()
  {
    blink(562);
    delayMicroseconds(562);
  }

  void send(Codes::Code code, unsigned int times = 2)
  {
    for (unsigned int i = 0; i < times; ++i)
    {
      actuallySend(code);
      delayMicroseconds(2250);
    }
  }

  void actuallySend(Codes::Code code)
  {
    header();

    for (unsigned int i = 0; i < 32; ++i, code <<= 1)
    {
      if (code & 0x80000000)
      {
        one();
      }
      else
      {
        zero();
      }
    }

    blink(562);
  }
};
}

IR::Sender sender(2);

void setup()
{
  PORTB = 0;
  TinyWireS.begin(0x10);
  
  DDRB |= 2;
}

void loop()
{
    while (TinyWireS.available()){
      TinyWireS.receive();
  PORTB ^= 2;
    }
}
void unused() {
  while (TinyWireS.available())
  {
    static bool specialCommand = false;

    static uint8_t buffer[4] = {0 ,0,0,0 };
    static size_t bytesReceived = 0;

    uint8_t op = TinyWireS.receive();

    if (specialCommand)
    {
      buffer[3 - (bytesReceived++)] = op;

      if (bytesReceived == 4)
      {
        specialCommand = false;
        memset(buffer, 0, sizeof(buffer));
        bytesReceived = 0;
        sender.send(*reinterpret_cast<uint32_t*>(buffer));
      }
    }

    switch (op)
    {
    case 'p':
      sender.send(Codes::Power::Toggle);
      break;

    case 'o':
      sender.send(Codes::Power::On);
      break;

    case 'f':
      sender.send(Codes::Power::Off);
      break;

    case '+':
      sender.send(Codes::Volume::Up);
      break;

    case '-':
      sender.send(Codes::Volume::Down);
      break;

    case 'm':
      sender.send(Codes::Mute::Toggle);
      break;

    case 'u':
      sender.send(Codes::Mute::On);
      break;

    case 't':
      sender.send(Codes::Mute::Off);
      break;

    case 'x':
      memset(buffer, 0, sizeof(buffer));
      bytesReceived = 0;
      specialCommand = true;
    }
  }
}
  
