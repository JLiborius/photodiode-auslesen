import serial
import time
import serial.tools.list_ports

try:
    ports = list(serial.tools.list_ports.comports())
    print("Detected ports:")
    for p in ports:
        print(p.device, p.description)
    
    port = input("Choose Port: ")
    baudrate = 115200
    filename = input("Name of the csv file:")
    output_file = filename + '.csv'

   
    ser = serial.Serial(port, baudrate, timeout=1)
   

    time.sleep(2)

    with open(output_file, 'w') as f:
        f.write("time_ms,voltage\n")
        print("Logging data... Press Ctrl+C to stop.")
        try:
            while True:
                line = ser.readline().decode(errors='replace').strip()
                if line:
                    if line[0].isdigit():
                        print(line)
                        f.write(line + '\n')
        except KeyboardInterrupt:
            print("Finished logging.")
            ser.close()
except Exception as e:
    print("An error occurred:", e)
finally:
    input("Press Enter to exit...")