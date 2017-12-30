//
//  CommandProcessor.h
//  design_pattern
//
//  Created by dao on 12/26/17.
//  Copyright © 2017 dao. All rights reserved.
//

#ifndef CommandProcessor_h
#define CommandProcessor_h
#include <memory>
#include <stack>
#include <vector>
#include <iostream>

namespace command_processor
{

    class Command
    {
    public:
        virtual ~Command() = default;
        virtual void execute() = 0;
    };
    
    class Revertable
    {
    public:
        virtual ~Revertable() = default;
        virtual void undo() = 0;
    };
    
    class UndoableCommand : public Command, public Revertable
    { };
    
    using CommandPtr = std::shared_ptr<UndoableCommand>;
    
    struct Point
    {
        int x,y;
    };
    
    class DrawingProcessor
    {
    public:
        void drawCircle(const Point& centerPoint, const double radius)
        { // Instructions to draw a circle on the screen...
            std::cout << "Draw cirle\n";
        };
        void eraseCircle(const Point& centerPoint, const double radius)
        { // Instructions to erase a circle from the screen...
             std::cout << "Erase cirle\n";
        };
        // ...
        
        void drawRectangle(const Point& centerPoint, const double width, const double height)
        { // Instructions to draw a circle on the screen...
             std::cout << "Draw rectangle\n";
        };
        void eraseRectangle(const Point& centerPoint, const double width, const double height)
        { // Instructions to erase a circle from the screen...
             std::cout << "Erase rectangle\n";
        };
        
        
    };
    

    class CommandProcessor
    {
    public:
        void execute(const CommandPtr& command)
        {
            command->execute();
            commandHistory.push(command);
        }
        void undoLastCommand()
        {
            if (commandHistory.empty()) {
                return; }
            commandHistory.top()->undo();
            commandHistory.pop();
        }
    private:
        std::stack<std::shared_ptr<Revertable>> commandHistory;
    };
    
    class UndoCommand : public UndoableCommand
    {
    public:
        explicit UndoCommand(CommandProcessor& receiver) noexcept : receiver { receiver }
        { }
        virtual void execute() override
        {
            receiver.undoLastCommand();
        }
        virtual void undo() override {
            // Intentionally left blank, because an undo should not be undone.
        }
    private:
        CommandProcessor& receiver;
    };
    
    class CompositeCommand : public UndoableCommand
    {
    public:
        void addCommand(CommandPtr& command)
        {
            commands.push_back(command);
        }
        
        virtual void execute() override
        {
            for (const auto& command : commands) {
                command->execute();
            }
        }
        virtual void undo() override
        {
            for (const auto& command : commands) {
                command->undo();
            }
        }
    private:
        std::vector<CommandPtr> commands;
    };
    
    class DrawCircleCommand : public UndoableCommand
    {
    public:
        DrawCircleCommand(DrawingProcessor& receiver, const Point& centerPoint, const double radius) noexcept :
        receiver { receiver }, centerPoint { centerPoint }, radius { radius }
        { }
        virtual void execute() override
        {
            receiver.drawCircle(centerPoint, radius);
        }
        
        virtual void undo() override
        {
            receiver.eraseCircle(centerPoint, radius);
        }
    private:
        DrawingProcessor& receiver;
        const Point centerPoint;
        const double radius;
    };
    
    class DrawRectangleCommand: public UndoableCommand
    {
    public:
        DrawRectangleCommand(DrawingProcessor& receiver, const Point& centerPoint, const double width, const double height) noexcept :
        receiver { receiver }, centerPoint { centerPoint }, width(width), height(height)
        { }
        virtual void execute() override
        {
            receiver.drawRectangle(centerPoint, width, height);
        }
        
        virtual void undo() override
        {
            receiver.eraseRectangle(centerPoint, width, height);
        }
    private:
        DrawingProcessor& receiver;
        const Point centerPoint;
        const double width, height;
    };
    
    int runDP()
    {
        CommandProcessor commandProcessor { };
        DrawingProcessor drawingProcessor { };
        
        auto macroRecorder = std::make_shared<CompositeCommand>();
        Point circleCenterPoint { 20, 20 };
        CommandPtr drawCircleCommand = std::make_shared<DrawCircleCommand>(drawingProcessor,
                                                                           circleCenterPoint, 10);
        commandProcessor.execute(drawCircleCommand);
        macroRecorder->addCommand(drawCircleCommand);
        
        Point rectangleCenterPoint { 30, 10 };
        CommandPtr drawRectangleCommand = std::make_shared<DrawRectangleCommand>(drawingProcessor,
                                                                                 rectangleCenterPoint, 5, 8);
        commandProcessor.execute(drawRectangleCommand);
        macroRecorder->addCommand(drawRectangleCommand);
        commandProcessor.execute(macroRecorder);
        
        CommandPtr undoCommand = std::make_shared<UndoCommand>(commandProcessor);
        commandProcessor.execute(undoCommand);
        return 1;
    }
}

#endif /* CommandProcessor_h */
