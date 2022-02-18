from tkinter import *
import serial
import matplotlib.pyplot as plt
import time
import serial.tools.list_ports

root = Tk()

root.title("Serial_Communication")

label = Label(text="NAZEV")
label.grid(row= 1, column=1)

r= StringVar()
i= 5

port= str()
nazev= str()
e= Entry(width= 60)
e.grid(row= 2, column=1)

label1 = Label(text="POCET HODNOT")
label1.grid(row= 3, column=1)

e1= Entry(width= 30)
e1.grid(row= 4, column=1)


def clicked():
    port= r.get()
    nazev= e.get()
    value= e1.get()
    ser= serial.Serial(port, 115200)

    f= open(nazev + ".txt", "w+")
    count=0
    data =[]                       # empty list to store the data
    while count < int(value):
        b = ser.readline()         # read a byte string
        string_n = b.decode()  # decode byte string into Unicode  
        string = string_n.rstrip() # remove \n and \r
        flt = int(string)        # convert string to float
        data.append(flt)
        f.write(string + '\n')
        count = count + 1

    f.close
    ser.close()

    plt.plot(data)
    plt.xlabel('pocet hodnot')
    plt.ylabel('Laser')
    plt.title('LASER')
    plt.savefig(nazev + ".png", dpi=300, bbox_inches='tight')

    label1 = Label(text=nazev)
    label1.grid(row= i, column=1)

ports = list(serial.tools.list_ports.comports())

for p in ports:
    Radiobutton(text=str(p).split(" ")[0], variable=r, value=str(p).split(" ")[0],).grid(row=i, column=1)
    i += 1

btn = Button(root, text='Start' ,command=lambda: clicked(), fg="green")
btn.grid(row= i, column=0)

btn1 = Button(root, text='Exit' ,command=root.quit, fg="red")
btn1.grid(row= i, column=2)

mainloop()