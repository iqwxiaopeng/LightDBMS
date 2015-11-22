#include "FiniteStateMachine.h"
#include <cctype>
#include <iostream>

void Machine::FiniteStateMachine::Process(std::string& text)
{
	Machine machine(*this);
	machine.initiate();
	char lastOne = '#';
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
			if (i == 0)
			{
				if (current == 's' || current == 'S') machine.process_event(Events::LetterS());
				else machine.process_event(Events::Letter());
			}
			else
			{
				if (lastOne == ' ')
				{
					if (current == 'a' || current == 'A')
						machine.process_event(Events::LetterA());
					else if (current == 'f' || current == 'F')
						machine.process_event(Events::LetterF());
					else if (current == 'l' || current == 'L')
						machine.process_event(Events::LetterL());
					else if (current == 'n' || current == 'N')
						machine.process_event(Events::LetterN());
					else if (current == 'o' || current == 'O')
						machine.process_event(Events::LetterO());
					else if (current == 'w' || current == 'W')
						machine.process_event(Events::LetterW());
					else machine.process_event(Events::Letter());
				}
				else if (lastOne == 'e' || lastOne == 'E')
				{
					if (current == 'c' || current == 'C')
						machine.process_event(Events::LetterC());
					else if (current == 'l' || current == 'L')
						machine.process_event(Events::LetterL());
					else if (current == 'r' || current == 'R')
						machine.process_event(Events::LetterR());
					else if (current == 'l' || current == 'L')
						machine.process_event(Events::LetterL());
					else if (current == 'n' || current == 'N')
						machine.process_event(Events::LetterN());
					else if (current == 'o' || current == 'O')
						machine.process_event(Events::LetterO());
					else if (current == 'w' || current == 'W')
						machine.process_event(Events::LetterW());
					else machine.process_event(Events::Letter());
				}
				else if ((lastOne == 'n' || lastOne == 'N') && (current == 'd' || current == 'D'))
					machine.process_event(Events::LetterD());
				else if (current == 'e' || current == 'E')
				{
					if (lastOne == 's' || lastOne == 'S' || lastOne == 'l' || lastOne == 'L' || lastOne == 'h' ||
						lastOne == 'H' || lastOne == 'k' || lastOne == 'K' || lastOne == 'r' || lastOne == 'R')
						machine.process_event(Events::LetterE());
					else machine.process_event(Events::Letter());
				}
				else if (lastOne == 'o' || lastOne == 'O')
				{
					if (current == 'm' || current == 'M')
						machine.process_event(Events::LetterM());
					else if (current == 'r' || current == 'R')
						machine.process_event(Events::LetterR());
					else if (current == 't' || current == 'T')
						machine.process_event(Events::LetterT());
					else machine.process_event(Events::Letter());
				}
				else if (lastOne == 'i' || lastOne == 'I')
				{
					if (current == 'k' || current == 'K')
						machine.process_event(Events::LetterK());
					else if (current == 'n' || current == 'N')
						machine.process_event(Events::LetterN());
					else machine.process_event(Events::Letter());
				}
				else if ((lastOne == 'w' || lastOne == 'W') && (current == 'h' || current == 'H'))
					machine.process_event(Events::LetterH());
				else if ((lastOne == 'l' || lastOne == 'L') && (current == 'i' || current == 'I'))
					machine.process_event(Events::LetterI());
				else if ((lastOne == 'a' || lastOne == 'A') && (current == 'n' || current == 'N'))
					machine.process_event(Events::LetterN());
				else if ((lastOne == 'r' || lastOne == 'R') && (current == 'o' || current == 'O'))
					machine.process_event(Events::LetterO());
				else if ((lastOne == 'f' || lastOne == 'F') && (current == 'r' || current == 'R'))
					machine.process_event(Events::LetterR());
				else if ((lastOne == 'c' || lastOne == 'C') && (current == 't' || current == 'T'))
					machine.process_event(Events::LetterT());
				else machine.process_event(Events::Letter());
			}
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
		else if (current == '>')
		{
			machine.process_event(Events::More());
		}
		else if (current == '<')
		{
			machine.process_event(Events::Less());
		}
		else if (current == '=')
		{
			machine.process_event(Events::Equal());
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
		lastOne = current;
	}
	machine.process_event(Events::Space());
	machine.terminate();

	for (Machine::state_iterator it = machine.state_begin(); it != machine.state_end(); ++it)
	{
		std::cout << typeid(*it).name() << "\n";
	}
}
