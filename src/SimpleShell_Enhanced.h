/**
 * @author      : CaféHaine (kilian.guillaume@gmail.com)
 * @author	: NuclearPhoenix
 * @file        : SimpleShell
 * @created     : Sunday Mar 08, 2020 08:33:56 CET
 */

#ifndef SIMPLESHELL_ENHANCED_H
#define SIMPLESHELL_ENHANCED_H	

#include "Arduino.h"
#include "LinkedPointerList.h"

class ShellCommand {
	public:
		ShellCommand(void (*func)(String *args), const __FlashStringHelper *name, const __FlashStringHelper *desc = F("")) {
			this->func = func;
			this->name = name;
			this->desc = desc;
		}
		
		ShellCommand(void (*func)(String *args), const char *name, const char *desc = "") {
			this->func = func;
			this->name = F(name);
			this->desc = F(desc);
		}

		void (*func)(String *args);
		const __FlashStringHelper *name;
		const __FlashStringHelper *desc;
};

class CShell {
	public:
		CShell(HardwareSerial &Serialx = Serial);
		void begin(long baudrate);
		void handleEvent();
		void registerCommand(ShellCommand *com);

	private:
		void _help();
		void _clear_buffer();
		void _draw_prompt();
		void _run_command();

		HardwareSerial *_serial;
		String _buffer;
		LinkedPointerList<ShellCommand> _commands;
};

#endif // SIMPLESHELL_ENHANCED_H
