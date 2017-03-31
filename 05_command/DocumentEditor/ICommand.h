#pragma once

class ICommand
{
public:
	virtual ~ICommand() = default;
	virtual void Execute() = 0;
	virtual void Unexecute() = 0;
};

typedef std::unique_ptr<ICommand> ICommandPtr;