//
//  Command.h
//  design_pattern
//
//  Created by dao on 12/23/17.
//  Copyright © 2017 dao. All rights reserved.
//

#ifndef Command_h
#define Command_h
#include <iostream>
namespace command
{
    class Light {
    public:
        Light(){};
        ~Light(){};
        void switchOn()
        {
            std::cout << "\n Light is swithed on";
        }
        
        void switchOff()
        {
            std::cout << "\n Light is swithed off";
        }
        
    };
    
    class Command {
    public:
        Command(){};
        virtual ~Command(){};
        virtual void execute()=0;
    };
    
    class SwitchOnCommand: public Command {
        Light *light{NULL};
        
    public:
        SwitchOnCommand(Light *p)
        {
            light = p;
        }
         ~ SwitchOnCommand(){};
        void execute()
        {
            if(light)
                light->switchOn();
        }
    };
    
    class SwitchOffCommand: public Command {
        Light *light{NULL};
        
    public:
        SwitchOffCommand(Light *p)
        {
            light = p;
        }
        ~ SwitchOffCommand(){};
        void execute()
        {
            if(light)
                light->switchOff();
        }
    };
    
    class RemoteControl
    {
        Command * pCommand{NULL};
    public:
        void setCommand(Command *p)
        {
            pCommand = p;
        }
        
        void pressButton()
        {
            if(pCommand)
                pCommand->execute();
        }
    };
    
    
    int runDP()
    {
        Light  light;
        Command *pOnCommand = new SwitchOnCommand(&light);
        Command *pOffCommand = new SwitchOffCommand(&light);
        
        RemoteControl remote;
        remote.setCommand(pOnCommand);
        remote.pressButton();
        
        remote.setCommand(pOffCommand);
        remote.pressButton();
        
        
        return 1;
    }
    
}
#endif /* Command_h */
