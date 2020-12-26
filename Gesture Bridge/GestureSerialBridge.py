#!/usr/bin/env python3
#
#   GestureSerialBridge - Gesture JSON to keyboard keys
#
#   Author - Aaron S. Crandall <crandall@gonzaga.edu>
#   Copyright 2020
#

import serial
import sys
import json
from pynput.keyboard import Controller


class Keyboard(object):
    _instance = None
    _keyboard = None

    def type(self, msg):
        self._keyboard.type(msg)

    def __new__(cls):
        if cls._instance is None:
            cls._instance = super(Keyboard, cls).__new__(cls)
            cls._keyboard = Controller()
        return cls._instance


def parse_and_print(data):
    printStr = ""
    if "gesture" in data:
        if data["gesture"] == "GES_LEFT":
            printStr = "L"
        elif data["gesture"] == "GES_RIGHT":
            printStr = "R"
        elif data["gesture"] == "GES_UP":
            printStr = "U"
        elif data["gesture"] == "GES_DOWN":
            printStr = "D"
        elif data["gesture"] == "GES_WAVE":
            printStr = "W"
        elif data["gesture"] == "GES_ANTICLOCKWISE":
            printStr = "A"
        elif data["gesture"] == "GES_CLOCKWISE":
            printStr = "C"
        elif data["gesture"] == "GES_FORWARD":
            printStr = "F"
        elif data["gesture"] == "GES_BACKWARD":
            printStr = "B"
    elif "wave_count" in data:
        printStr = "#" + str(data["wave_count"])
    Keyboard().type(printStr + "\n")


def handle_input(indata):
    print(indata)
    indata = indata.strip()
    if(indata[0] == '{'):
        try:
            data = json.loads(indata)
            parse_and_print(data)
        except:
            print("Not json - ignoring")


if __name__ == "__main__":
    serialPort = sys.argv[1]

    try:
        ser = serial.Serial(serialPort, 115200)
        print("Serial Connected - ready for input.")
        while(True):
            line  = ser.readline()
            line = line.decode('utf-8')
            line = line.rstrip()
            handle_input(line)
    except KeyboardInterrupt:
        print("Interrupted - quitting")
    finally:
        ser.close()
