import serial
import random

serial_port = 'COM5'
baud_rate = 9600

ser = serial.Serial(serial_port, baud_rate, timeout=60)


def send_Frame(data):
    frame = [0,255,1,0,2]
    checkSum = 0
    frame.append(len(data))
    for i in range(3,11):
        frame.append(i)
        if i-3 < len(data):
            frame.append(ord(data[i-3]))
            checkSum+=ord(data[i-3])
        else :
            frame.append(0)
    frame.append(11)
    frame.append(checkSum)
    frame.append(12)
    frame.append(255)
    return frame


try:
    while True:
        msg = input("Enter the Message : ")
        frame = send_Frame(msg)
        print(frame)
        ser.write(frame)
        received_data = ser.read(26)
        if received_data:
            formatted_received_data = ' '.join('{:02x}'.format(byte) if index not in (7, 9) else chr(byte) for index, byte in enumerate(received_data))
            print("stm reply: ", formatted_received_data)

except KeyboardInterrupt:
    print("Exiting...")
    ser.close()
