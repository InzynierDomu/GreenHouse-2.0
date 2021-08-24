#ifndef SUPERVISOR
#define SUPERVISOR

enum class Device_state
{
    ok,
    error
};

class Supervisor
{
public:
    Supervisor();
    void set_error_led();
    void set_mqtt();
    void error();
    Device_state get_state() const;

private:
    void turn_on_error_led();
    void send_error_msg();
    void set_safe_state();

    Device_state m_state;
};

#endif //SUPERVISOR