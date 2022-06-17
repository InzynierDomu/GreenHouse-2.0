/**
 * @file Peripherals.h
 * @brief Peripherals container structure
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @date 2022-06
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
  std::vector<Peripheral_output*> m_outputs; ///< outputs peripherals
  std::vector<Peripheral_input*> m_inputs; ///< inputs peripherals

  /**
   * @brief Get the output object
   * @param topic: with what topic want to find output
   * @return Peripheral_output* output
   */
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