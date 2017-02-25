/* -*- mode: c++ -*-
 * Kaleidoscope-Focus -- Bidirectional communication plugin
 * Copyright (C) 2017  Gergely Nagy
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <Kaleidoscope-Focus.h>
#include <avr/pgmspace.h>

namespace KaleidoscopePlugins {
  char Focus::command[32];
  Focus::Command *Focus::rootCommand;

  Focus::Focus (void) {
  }

  void
  Focus::begin (void) {
    Kaleidoscope.useLoopHook (loopHook);
  }

  void
  Focus::addCommand (Command *command) {
    if (!rootCommand) {
      rootCommand = command;
    } else {
      Command *currentCommand = rootCommand;

      while (currentCommand->next) {
        currentCommand = currentCommand->next;
      }
      currentCommand->next = command;
    }
  }

  const Focus::Command *
  Focus::getRootCommand (void) {
    return rootCommand;
  }

  void
  Focus::loopHook (bool postClear) {
    if (postClear)
      return;

    if (Serial.available () == 0)
      return;

    uint8_t i = 0;
    do {
      command[i++] = Serial.read ();
    } while (command[i - 1] != ' ' && command[i - 1] != '\n' && i < 32);
    command[i - 1] = '\0';

    for (Command *cc = rootCommand; cc; cc = cc->next) {
      if ((*cc->handler) (command)) {
        break;
      }
    }

    Serial.println (F("."));
  }
};

KaleidoscopePlugins::Focus Focus;

namespace FocusCommands {
  bool help (const char *command) {
    if (strcmp_P (command, PSTR("help")) != 0)
      return false;

    const KaleidoscopePlugins::Focus::Command *rootCommand = Focus.getRootCommand ();

    Serial.println (F("Available commands:\n"
                      "===================\n"));

    for (const KaleidoscopePlugins::Focus::Command *node = rootCommand; node; node = node->next) {
      Serial.println (node->docs);
      Serial.println ();
    }

    return true;
  }

  bool version (const char *command) {
    if (strcmp_P (command, PSTR ("version")) != 0)
      return false;

    Serial.print (F("Kaleidoscope/"));
    Serial.print (F(VERSION));
    Serial.print (F(", for "));
    Serial.print (F(USB_MANUFACTURER));
    Serial.print (F(" "));
    Serial.print (F(USB_PRODUCT));
    Serial.print (F(", compiled on "));
    Serial.print (F(__DATE__));
    Serial.print (F(" at "));
    Serial.print (F(__TIME__));
    Serial.print (F(" (Arduino "));
    Serial.print (ARDUINO);
    Serial.println (F(")"));

    return true;
  }

}
