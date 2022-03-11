#include "fsm.h"
#include <iostream>
#include <stdint.h>

enum class MyStates : uint32_t
{
    On = 0,
    Off,
    Smashed,
    NumStates
};

enum class MyEvents : uint32_t
{
    Toggle = 0,
    Smash
};

int main(int argc, char** argv)
{
    std::cout << "Hello, world" << std::endl;

    FSM<MyStates, MyEvents> Fsm((size_t)MyStates::NumStates, MyStates::On);
    Fsm.AddTransition(MyStates::On,
                      MyStates::Off,
                      MyEvents::Toggle,
                      []()
                      {
                          std::cout << "TurnOff!" << std::endl;
                      });
    Fsm.AddTransition(MyStates::Off,
                      MyStates::On,
                      MyEvents::Toggle,
                      []()
                      {
                          std::cout << "TurnOn!" << std::endl;
                      });
    Fsm.AddWildcardTransition(1 << (uint32_t)MyStates::On | 1 << (uint32_t)MyStates::Off,
                              MyStates::Smashed,
                              MyEvents::Smash,
                              []()
                              {
                                  std::cout << "Smash!" << std::endl;
                              });

    Fsm.Input(MyEvents::Toggle);
    Fsm.Input(MyEvents::Toggle);
    Fsm.Input(MyEvents::Smash);
    Fsm.Input(MyEvents::Toggle);
    Fsm.Input(MyEvents::Toggle);
    Fsm.Input(MyEvents::Smash);

    return 0;
}
