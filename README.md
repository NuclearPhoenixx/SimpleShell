# SimpleShell Enhanced

[![arduino-library-badge](https://www.ardu-badge.com/badge/SimpleShell%20Enhanced.svg?)](https://www.ardu-badge.com/SimpleShell%20Enhanced) ![latest version](https://img.shields.io/github/release/NuclearPhoenixx/SimpleShell.svg?) ![issues](https://img.shields.io/github/issues/NuclearPhoenixx/SimpleShell.svg?) ![open pr](https://img.shields.io/github/issues-pr-raw/NuclearPhoenixx/SimpleShell.svg?)

## What is SimpleShell?
SimpleShell is a quick way to create commands, and control your arduino using the serial interface.

This fork aims to improve upon the original SimpleShell and continue maintaining the codebase.

This library is also available in the Arduino IDE, see [Arduino Library List](https://www.arduinolibraries.info/libraries/simple-shell-enhanced).

```
Type 'help' for a list of commands.
> help
Usage:
	<command> [options]
Commands:
	helloworld	: Optional Description
>
```

Tab completion and descriptions will hopefully be supported someday.

Also TODO: use [ivanseidel/LinkedList](https://github.com/ivanseidel/LinkedList) instead of the minimalistic LinkedPointerList for sorting all the commands.

## How to use it?
See `examples/HelloWorld/HelloWorld.ino` for a simple example of a command.
