#include "Arduino.h"
#include "LinkedPointerList.h"
#include "SimpleShell_Enhanced.h"

void CShell::_help() {
	Serial.println(F("Usage:"));
	Serial.println(F("\t<command> [options]"));
	Serial.println(F("Commands:"));
	for (uint8_t i=0; i<_commands.size(); i++) {
		Serial.print(F("\t"));
		Serial.print(_commands.get(i)->name);
		
		if (_commands.get(i)->desc != F("")) {
			Serial.print("\t: ");
			Serial.print(_commands.get(i)->desc);
		}
		Serial.println();
	}
}

void CShell::begin(long baudrate) {
	Serial.begin(baudrate);
	Serial.println(F("Type 'help' for a list of commands."));
	_draw_prompt();
}

void CShell::registerCommand(ShellCommand *com) {
	_commands.add(com);
	// TODO: Sorting? Use LinkedList instead...
	// https://github.com/ivanseidel/LinkedList/blob/master/examples/Sort/Sort.ino
}

void CShell::_clear_buffer() {
	_buffer = String();
}

void CShell::_draw_prompt() {
	Serial.print(F("> "));
}

void CShell::_run_command() {
	_buffer.trim();
	if (_buffer.length() == 0) {
		_draw_prompt();
		return;
	}
	if (_buffer.startsWith(F("help"))) {
		_help();
		_draw_prompt();
		return;
	}
	for (uint8_t i=0; i<_commands.size(); i++) {
		ShellCommand *com = _commands.get(i);
		if (_buffer.startsWith(com->name)) {
			com->func(&_buffer);
			_draw_prompt();
			return;
		}
	}
	Serial.println(F("Command not found."));
	Serial.println(F("Type 'help' for a list of commands."));
	_draw_prompt();
}

void CShell::handleEvent() {
	// VT100 codes
	// http://matthieu.benoit.free.fr/68hc11/vt100.htm
	char input;
	while (Serial.available()) {
		input = Serial.read();
		switch (input) {
			// New page/Clear buffer
			case '\f':
				Serial.print(F("\e[0;0H\e[2J"));
				_draw_prompt();
				break;

				// Backspace
			case 0x7F: // Ctrl+Bs
			case '\b':
				if (_buffer.length() > 0) {
					_buffer = _buffer.substring(0, _buffer.length() - 1);
					Serial.print(F("\e[D \e[D"));
				}
				break;

				// Ctrl + C
			case 0x03:
				Serial.println(F("^C"));
				_draw_prompt();
				_clear_buffer();
				break;

				// Newline
			case '\n':
			case '\r':
				Serial.println();
				_run_command();
				_clear_buffer();
				break;

				// Tab
			case '\t':
				// TODO: Tab Completion?
				break;

				// Ascii char
			case 0x20 ... 0x7E:
				Serial.write(input);
				_buffer.concat(input);
				break;

			default:
				break;
		}
	}
}
