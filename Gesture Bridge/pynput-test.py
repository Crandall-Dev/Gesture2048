from pynput.keyboard import Controller
import time

keyboard = Controller()

time.sleep(2)
keyboard.type("hello world")
