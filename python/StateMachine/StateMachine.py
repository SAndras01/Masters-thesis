import tkinter as tk
from enum import Enum

class State(Enum):
    IDLE = 0
    MEASURE = 1
    SERIAL = 2

class Machine:
    def __init__(self):
        self.state = State.IDLE
    def update(self, event):
        if self.state == State.IDLE and event == "start":
            self.state = State.MEASURE
        elif self.state == State.MEASURE and event == "serial":
            self.state = State.SERIAL
        elif event == "stop":
            self.state = State.IDLE
        return self.state

sm = Machine()

def on_event(ev):
    lbl.config(text=str(sm.update(ev)))

root = tk.Tk()
lbl = tk.Label(root, text=str(sm.state), font=("Arial", 20))
lbl.pack(pady=10)
tk.Button(root, text="Start",  command=lambda: on_event("start")).pack()
tk.Button(root, text="Serial", command=lambda: on_event("serial")).pack()
tk.Button(root, text="Stop",   command=lambda: on_event("stop")).pack()
root.mainloop()
