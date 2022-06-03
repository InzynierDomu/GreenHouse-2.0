/**
 * @file Peripherals.h
 * @brief GreenHouse 2.0 - Peripherals container structure
 * @author Szymon Markiewicz
 * @details http://www.inzynierdomu.pl/
 * @date 06-2022
 */

#pragma once

#include "Peripheral_input.h"
#include "Peripheral_output.h"

#include <optional>
#include <vector>

namespace Peripherals
{

struct Peripherals
{
  std::vector<Peripheral_output*> m_outputs;
  std::vector<Peripheral_input*> m_inputs;

  Peripheral_output* get_output(String topic)
  {
    if (!m_outputs.empty())
    {
      for (auto it = m_outputs.begin(); it != m_outputs.end(); it++)
      {
        if (topic.equals((*it)->get_topic()))
        {
          return *it;
        }
      }
    }
    return nullptr;
  }
};
} // namespace Peripherals