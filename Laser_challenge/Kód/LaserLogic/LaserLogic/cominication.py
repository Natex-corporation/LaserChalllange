import serial
import matplotlib.pyplot as plt
import serial.tools.list_ports

print("seznam portu:")
ports = list(serial.tools.list_ports.comports())
for p in ports:
    print(p)

port= str(input("Zadej port: "))
values= int(input("Zadej pozadovany pocet hodnot: "))

ser = serial.Serial(port, 115200)

print("connected to: " + ser.portstr)

nazev= str(input("Zadej nazev souboru dat: "))
f= open(nazev + ".txt", "w+")
count=0
data =[]                       # empty list to store the data
while count < values:
    b = ser.readline()         # read a byte string
    string_n = b.decode()  # decode byte string into Unicode  
    string = string_n.rstrip() # remove \n and \r
    flt = float(string)        # convert string to float
    data.append(flt)
    print(string_n)
    f.write(string + '\n')
    count = count + 1

f.close
ser.close()

plt.plot(data)
plt.xlabel('pocet hodnot')
plt.ylabel('Laser')
plt.title('LASER')
plt.savefig(nazev + ".png", dpi=300, bbox_inches='tight')
plt.show()

