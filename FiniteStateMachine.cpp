#include "FiniteStateMachine.h"
#include <cctype>

void Machine::FiniteStateMachine::Process(std::string& text)
{
	Machine machine(*this);
	machine.initiate();
	
	const size_t length = text.length();
	for (size_t i = 0; i != length; ++i)
	{
		const char current = text[i];
		
		if (std::isdigit(current))
		{
			machine.process_event(Events::Digit());
		}
		else if (std::isalpha(current))
		{
			machine.process_event(Events::Letter());
		}
		else if (current == '\'')
		{
			machine.process_event(Events::Quote());
		}
		else if (current == '*')
		{
			machine.process_event(Events::Multiplication());
		}
		else if (current == '\\')
		{
			machine.process_event(Events::Division());
		}
		else if (current == '.')
		{
			machine.process_event(Events::Dot());
		}
		else if (current == ',')
		{
			machine.process_event(Events::Comma());
		}
		else if (current == ';')
		{
			machine.process_event(Events::Semicolon());
		}
		else if (current == '>' || current == '<' || current == '=')
		{
			machine.process_event(Events::Comparsion());
		}
		else if (std::isspace(current))
		{
			machine.process_event(Events::Space());
		}
		else
		{
			machine.process_event(Events::Space());
			this->value = current;
			machine.process_event(Events::Other());
		}
		this->value += current;
	}
	machine.process_event(Events::Space());
	machine.terminate();
}
