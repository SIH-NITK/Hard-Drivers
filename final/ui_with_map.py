# Imports tkinter and ttk module 
from tkinter import *
from tkinter.ttk import *
import serial
from serial import Serial
from time import localtime,strftime
from tkinter import messagebox
import threading
import matplotlib.pyplot as plt

# toplevel window 
root = Tk() 




# method to make widget invisible or remove from toplevel 
def forget(widget):  
    widget.grid_forget() 
  
# method to make widget visible 
def retrieve(widget): 
    widget.grid(row = 0, column = 0, ipady = 10, pady = 10, padx = 5) 

def begin_button():
    b1 = Button(root, text = "Soldier1")
    b1.grid(row = 0, column = 0, ipady = 10, pady = 10, padx = 5)
    b2 = Button(root, text = "Soldier2") 
    b2.grid(row = 0, column = 1, ipady = 10, pady = 10, padx = 5)
    b3 = Button(root, text = "Soldier3") 
    b3.grid(row = 0, column = 2, ipady = 10, pady = 10, padx = 5)
    b4 = Button(root, text = "Soldier4") 
    b4.grid(row = 0, column = 3, ipady = 10, pady = 10, padx = 5)
    t1 = threading.Thread(target=fun_nitk)
    t1.start()

def map(x,y):
    img = plt.imread("map")

    fig, ax = plt.subplots()
    ax.imshow(img, extent=[13.0000, 13.0157, 74.7888, 74.7984])
    ax.plot(x, y, '*', linewidth=5, color='red')
    plt.show()

def fun_nitk():
    serial_port = '/dev/ttyUSB0';
    baud_rate = 115200; #In arduino, Serial.begin(baud_rate)

    op_path1="op_s1.txt"
    op_path2="op_s2.txt"
    op_path3="op_s3.txt"
    op_path4="op_s4.txt"

    output_file1 = open(op_path1, "w+");
    output_file2 = open(op_path2, "w+");
    output_file3 = open(op_path3, "w+");
    output_file4 = open(op_path4, "w+");

    b1 = Button(root, text = "Soldier1")
    b1.grid(row = 0, column = 0, ipady = 10, pady = 10, padx = 5)
    b2 = Button(root, text = "Soldier2") 
    b2.grid(row = 0, column = 1, ipady = 10, pady = 10, padx = 5)
    b3 = Button(root, text = "Soldier3") 
    b3.grid(row = 0, column = 2, ipady = 10, pady = 10, padx = 5)
    b4 = Button(root, text = "Soldier4") 
    b4.grid(row = 0, column = 3, ipady = 10, pady = 10, padx = 5)



    ser = serial.Serial(serial_port, baud_rate)
    img = plt.imread("map")
    #while (plen>33):
    while(1):    
        line = ser.readline();
        info = line.decode("utf-8")
        header=info[0:9]
        if(header=="logClient"):
            print("Abhi rocks")
            index=info.find('*')
            print("AAron=",index)
            plen=len(info)
            info=info[index+1:plen-3]
            print(info)
            plen =len(info)
            if(plen>=33):
                print("NITK")
                ID=info[0:4]
                longitude=info[4:13]
                latitude=info[13:22]
                kan1=float(longitude)
                kan2=float(latitude)

                temp=info[22:26]
                heartbeat=info[26:29]
                battery=info[29:31]+"."+info[31:33]
                sos=info[32]
                curtime=strftime("%H:%M:%S",localtime())
                
            
                if(sos=="1"):
                    messagebox.showerror("SOS", "Soldier "+ID+" is in danger")
                abhi="Information of\nsoldier "+ID+"\nAt time="+curtime+"\nlongitude= "+longitude+"\nlatitude= "+latitude+"\nTemp="+temp+"\nHeartbeat= "+heartbeat+"\nBattery= "+battery+"%\n"
                print(abhi)
                if(ID=="0001"):
                    output_file1.write(abhi+"\n")
                    forget(b1)
                    b1 = Button(root, text = abhi,command=lambda:map(kan1,kan2)) 
                    b1.grid(row = 0, column = 0, ipady = 10, pady = 10, padx = 5)
                    
                if(ID=="0002"):
                    forget(b2)
                    b2 = Button(root, text = abhi,command=lambda:map(kan1,kan2)) 
                    b2.grid(row = 0, column = 1, ipady = 10, pady = 10, padx = 5)
                    output_file2.write(abhi+"\n")

                if(ID=="0003"):
                    forget(b3)
                    b3 = Button(root, text = abhi,command=lambda:map(kan1,kan2)) 
                    b3.grid(row = 0, column = 2, ipady = 10, pady = 10, padx = 5)
                    output_file3.write(abhi+"\n")
                
                if(ID=="0004"):
                    forget(b4)
                    b4 = Button(root, text = abhi,command=lambda:map(kan1,kan2)) 
                    b4.grid(row = 0, column = 3, ipady = 10, pady = 10, padx = 5)
                    output_file4.write(abhi+"\n")

                #info=info[34:]
t1 = threading.Thread(target=fun_nitk)
t1.start()
#begin_button()
mainloop()

  
# infinite loop, interrupted by keyboard or mouse 
 
