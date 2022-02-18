from tkinter import *
import serial
import matplotlib.pyplot as plt
from serial.serialutil import Timeout
import serial.tools.list_ports
import os
import time

root = Tk()

root.title("Serial_Communication")

label = Label(text="NAZEV")
label.grid(row= 1, column=1)

path= os.getcwd()+"/source/"
pathplt= os.getcwd()+"/graphs/"

r= StringVar()
X= IntVar()
i= 5

port= str()
nazev= str()
e= Entry(width= 60)
e.insert ( 0,"Data")
e.grid(row= 2, column=1)

label1 = Label(text="POCET HODNOT")
label1.grid(row= 3, column=1)

e1= Entry(width= 30)
e1.insert ( 0,"1800")
e1.grid(row= 4, column=1)

btn2 = Button(root, text='Vyvest grafy' ,command=lambda: plot(), fg="blue")

btn3 = Button(root, text='poslat K' ,command=lambda: K(), fg="blue")
btn3.grid(row= 4, column=2)

def K():
    port= r.get()
    ser= serial.Serial(port, 115200, timeout= .1)
    time.sleep(2)
    ser.write('K'.encode())
    time.sleep(0.5)

    '''b = ser.readline()       # read a byte string
    stringos = b.decode()  # decode byte string into Unicode  
    label4 = Label(text=stringos)
    label4.grid(row= 5, column=2)'''
    ser.close()

def clicked():
    port= r.get()
    nazev= e.get()
    value= e1.get()
    ser= serial.Serial(port, 115200, timeout = .1)
    time.sleep(2)
    ser.write('K'.encode())
    time.sleep(0.5)
    
    f= open(path+ nazev + ".txt", "w+")
    count=0
    data =[]                       # empty list to store the data
    while count < int(value):
        b = ser.readline()         # read a byte string
        string_n = b.decode()  # decode byte string into Unicode  
        string = string_n.rstrip() # remove \n and \r
        flt = float(string)        # convert string to float
        data.append(flt)
        f.write(string + '\n')
        count = count + 1

    f.close
    ser.close()

    plt.plot(data)
    plt.xlabel('pocet hodnot')
    plt.ylabel('Laser')
    plt.title('LASER')
    plt.savefig(pathplt +nazev + ".png", dpi=300, bbox_inches='tight')
    
    if X.get() == 1:
        #label3 = Label(text="Spoustim Soubor .cpp")
        #label3.grid(row= i + 4, column=1)
        os.startfile("LaserLogic.exe")
    
    label1 = Label(text=nazev)
    label1.grid(row= i+2, column=1)

    btn2.grid(row= i+3, column=1)

def plot():
    files= ['AwaragedValues', 'AwaragedValues2', 'Gause', 'Gause2']

    for p in files:
        x= []
        for line in open(path + p + ".txt", 'r'):
            l = [float(s) for s in line.split()]
            x.append(l[0])
        plt.clf()
        plt.plot(x)
        plt.xlabel('pocet hodnot')
        plt.ylabel('Laser')
        plt.title(p)
        plt.savefig(pathplt + p + ".png", dpi=300, bbox_inches='tight')

ports = list(serial.tools.list_ports.comports())

for p in ports:
    Radiobutton(text=p, variable=r, value=str(p).split(" ")[0],).grid(row=i, column=1)
    i += 1

label2 = Label(text="PROVEST ANALZYU POMOCI CPP?")
label2.grid(row= i, column=1)

Radiobutton(text="spustit", variable=X, value=1,).grid(row=i+1, column=0)
Radiobutton(text="nespoustet", variable=X, value=0,).grid(row=i+1, column=2)



btn = Button(root, text='Start' ,command=lambda: clicked(), fg="green")
btn.grid(row= i+3, column=0)

btn1 = Button(root, text='Exit' ,command=root.quit, fg="red")
btn1.grid(row= i+3, column=2)

mainloop()