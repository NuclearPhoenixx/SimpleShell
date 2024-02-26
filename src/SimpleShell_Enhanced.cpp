#include "Arduino.h"
#include "LinkedPointerList.h"
#include "SimpleShell_Enhanced.h"

void CShell::_help() {
	_serial->println(F("Usage:"));
	_serial->println(F("\t<command> [options]"));
	_serial->println(F("Commands:"));
	for (uint8_t i=0; i<_commands.size(); i++) {
		_serial->print(F("\t"));
		_serial->print(_commands.get(i)->name);
		
		if (_commands.get(i)->desc != F("")) {
			_serial->print("\t: ");
			_serial->print(_commands.get(i)->desc);
		}
		_serial->println();
	}
}

CShell::CShell(HardwareSerial &Serialx) {
	_serial = &Serialx;
}

void CShell::begin(long baudrate) {
	_serial->begin(baudrate);
	_serial->println(F("Type 'help' for a list of commands."));
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
	_serial->print(F("> "));
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
	_serial->println(F("Command not found."));
	_serial->println(F("Type 'help' for a list of commands."));
	_draw_prompt();
}

void CShell::handleEvent() {
	// VT100 codes
	// http://matthieu.benoit.free.fr/68hc11/vt100.htm
	char input;
	while (_serial->available()) {
		input = _serial->read();
		switch (input) {
			// New page/Clear buffer
			case '\f':
				_serial->print(F("\e[0;0H\e[2J"));
				_draw_prompt();
				break;

				// Backspace
			case 0x7F: // Ctrl+Bs
			case '\b':
				if (_buffer.length() > 0) {
					_buffer = _buffer.substring(0, _buffer.length() - 1);
					_serial->print(F("\e[D \e[D"));
				}
				break;

				// Ctrl + C
			case 0x03:
				_serial->println(F("^C"));
				_draw_prompt();
				_clear_buffer();
				break;

				// Newline
			case '\n':
			case '\r':
				_serial->println();
				_run_command();
				_clear_buffer();
				break;

				// Tab
			case '\t':
				// TODO: Tab Completion?
				break;

				// Ascii char
			case 0x20 ... 0x7E:
				_serial->write(input);
				_buffer.concat(input);
				break;

			default:
				break;
		}
	}
}
