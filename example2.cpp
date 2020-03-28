#include <iostream>
#include <string>

#include "sofia.h"
#include "s_automata.h"

SOFIA_NS_USE

class Motor
{
    int speed_;

public:
    Motor() : speed_(0)
    {
    }

    const int getSpeed() const
    {
        return speed_;
    }

    void start()
    {
        std::cout << "Motor started" << std::endl;
        speed_ = 10;
    }

    void inc()
    {
        std::cout << "Motor speed increased" << std::endl;
        speed_ += 10;
    }

    void dec()
    {
        std::cout << "Motor speed decreased" << std::endl;
        speed_ -= 10;
    }

    void stop()
    {
        std::cout << "Motor emergency stopped" << std::endl;
        speed_ = 0;
    }
};

enum States
{
    S_OFF,
    S_SPEED_1,
    S_SPEED_2,
};

enum Event
{
    E_STOP,
    E_SPEED_INC,
    E_SPEED_DEC,
};

int main()
{
    Motor motor;
    Automata<States, Event, Motor> motor_automata;

    motor_automata.addTransition(S_OFF, S_SPEED_1, E_SPEED_INC, &Motor::start);
    motor_automata.addTransition(S_SPEED_1, S_SPEED_2, E_SPEED_INC, &Motor::inc);
    motor_automata.addTransition(S_SPEED_2, S_SPEED_1, E_SPEED_DEC, &Motor::dec);
    motor_automata.addTransition(S_SPEED_1, S_OFF, E_STOP, &Motor::stop);
    motor_automata.addTransition(S_SPEED_2, S_OFF, E_STOP, &Motor::stop);
    motor_automata.addTransition(S_SPEED_1, S_OFF, E_SPEED_DEC, &Motor::dec);

    motor_automata.init(S_OFF);

    std::cout << "Motor state is " << motor_automata.getCurrentState() << std::endl;
    std::cout << "Motor speed is " << motor.getSpeed() << std::endl;

    motor_automata.handleEvent(E_SPEED_INC, motor);
    std::cout << "Motor state is " << motor_automata.getCurrentState() << std::endl;
    std::cout << "Motor speed is " << motor.getSpeed() << std::endl;

    motor_automata.handleEvent(E_SPEED_INC, motor);
    std::cout << "Motor state is " << motor_automata.getCurrentState() << std::endl;
    std::cout << "Motor speed is " << motor.getSpeed() << std::endl;

    motor_automata.handleEvent(E_SPEED_INC, motor);
    std::cout << "Motor state is " << motor_automata.getCurrentState() << std::endl;
    std::cout << "Motor speed is " << motor.getSpeed() << std::endl;

    motor_automata.handleEvent(E_STOP, motor);
    std::cout << "Motor state is " << motor_automata.getCurrentState() << std::endl;
    std::cout << "Motor speed is " << motor.getSpeed() << std::endl;

    return 42;
}
