#include "Supervisor.h"

Supervisor::Supervisor()
: m_state(Device_state::ok)
{}

void Supervisor::set_error_led() {}

void Supervisor::set_mqtt() {}

void Supervisor::error()
{
  set_safe_state();
  turn_on_error_led();
  send_error_msg();
  m_state = Device_state::error;
}

Device_state Supervisor::get_state() const
{
  return m_state;
}

void Supervisor::turn_on_error_led() {}
void Supervisor::send_error_msg() {}
void Supervisor::set_safe_state() {}