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
  Focus::HookNode *Focus::rootNode;

  Focus::Focus (void) {
  }

  void
  Focus::begin (void) {
    loop_hook_use (loopHook);
  }

  void
  Focus::addHook (HookNode *newNode) {
    if (!rootNode) {
      rootNode = newNode;
    } else {
      HookNode *node = rootNode;

      while (node->next) {
        node = node->next;
      }
      node->next = newNode;
    }
  }

  const Focus::HookNode *
  Focus::getRootNode (void) {
    return rootNode;
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

      if (Serial.peek () == '\n')
        break;
    } while (command[i - 1] != ' ' && i < 32);
    if (command[i - 1] == ' ')
      command[i - 1] = '\0';
    else
      command[i] = '\0';

    for (HookNode *node = rootNode; node; node = node->next) {
      if ((*node->handler) (command)) {
        break;
      }
    }

    Serial.println (F("."));

    while (Serial.peek () != '\n') {
      Serial.read ();
    }
    if (Serial.peek () == '\n')
      Serial.read ();
  }

  void
  Focus::printSpace (void) {
    Serial.print (F(" "));
  }

  void
  Focus::printNumber (uint8_t num) {
    if (num < 10)
      printSpace ();
    if (num < 100)
      printSpace ();
    Serial.print (num);
  }

  void
  Focus::printColor (cRGB color) {
    printNumber (color.r);
    printSpace ();
    printNumber (color.g);
    printSpace ();
    printNumber (color.b);
  }

  void
  Focus::printSeparator (void) {
    Serial.print (F(" | "));
  }

  void
  Focus::printBool (bool b) {
    Serial.print ((b) ? F("true") : F("false"));
  }
};

KaleidoscopePlugins::Focus Focus;

namespace FocusHooks {
  bool help (const char *command) {
    if (strcmp_P (command, PSTR("help")) != 0)
      return false;

    const KaleidoscopePlugins::Focus::HookNode *rootNode = Focus.getRootNode ();

    for (const KaleidoscopePlugins::Focus::HookNode *node = rootNode; node; node = node->next) {
      if (!node->docs)
        continue;

      Serial.println (node->docs);
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
    Focus.printSpace ();
    Serial.print (F(USB_PRODUCT));
    Serial.print (F(", compiled on "));
    Serial.print (F(__DATE__));
    Serial.print (F(" at "));
    Serial.println (F(__TIME__));

    return true;
  }

}
