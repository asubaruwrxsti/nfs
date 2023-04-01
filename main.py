from ctypes import *
from ctypes.wintypes import *
import psutil
import time
import serial

arduino = serial.Serial('COM3', 9600, timeout=1)

OpenProcess = windll.kernel32.OpenProcess
ReadProcessMemory = windll.kernel32.ReadProcessMemory
CloseHandle = windll.kernel32.CloseHandle

def find_process_id(process_name):
    for process in psutil.process_iter():
        if process.name() == process_name:
            return process.pid
    return None

process_name = "NFS13.exe"
process_id = find_process_id(process_name)
process_handle = OpenProcess(0x10, False, process_id)

address = 0x27BF773C
refresh = 0.05

while find_process_id(process_name) is not None:
    distance_initial = c_float()
    ReadProcessMemory(process_handle, address, byref(distance_initial), sizeof(distance_initial), None)
    time.sleep(refresh)
    distance_final = c_float()
    ReadProcessMemory(process_handle, address, byref(distance_final), sizeof(distance_final), None)
    speed = ((distance_final.value - distance_initial.value) / refresh) * 3.6
    arduino.write(bytes(str(int(speed)), 'utf-8'))
    print(f"Speed: {int(speed)} km/h :: Arduino: {arduino.readline()}")





