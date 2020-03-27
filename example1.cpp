#include <iostream>
#include <string>

#include "sofia.h"
#include "s_automata.h"

SOFIA_NS_USE

class Light
{
public:
    void on()
    {
        std::cout << "Switch On" << std::endl;
    }

    void off()
    {
        std::cout << "Switch Off" << std::endl;
    }
};

int main()
{
    Light light;
    Automata<std::string, int, Light> automata;

    automata.addTransition("On", "Off", 0, &Light::off);
    automata.addTransition("Off", "On", 1, &Light::on);

    automata.init("Off");

    std::cout << "Light is " << automata.getCurrentState() << std::endl;

    automata.handleEvent(1, light);
    automata.handleEvent(0, light);
    automata.handleEvent(0, light);

    automata.handleEvent(1, light);
    automata.handleEvent(1, light);

    std::cout << "Light is " << automata.getCurrentState() << std::endl;

    return 42;
}
