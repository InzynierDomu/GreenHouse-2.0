#include "Checksum.h"

namespace Utils
{

void Checksum::add_char(char data) 
{
    m_crc.update<char>(data);
}

uint32_t Checksum::calculate_crc() 
{
    return m_crc.finalize();    
}

} // namespace Utils