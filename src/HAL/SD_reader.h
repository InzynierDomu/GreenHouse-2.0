#ifndef SDREADER_SCREEN
#define SDREADER_SCREEN

#include <SPI.h>
#include "SD.h"
#include "Pin_config.h"

class Logger;

namespace HAL{

class SD_reader
{
public:
  SD_reader();

private:
  Logger* m_logger;
};

} // namespace HAL

#endif // SDREADER_SCREEN
