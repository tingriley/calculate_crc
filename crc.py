from tkinter import *
from tkinter import filedialog
import binascii
import os

def CRC32_from_file(filename):
    buf = open(filename,'rb').read()
    buf = (binascii.crc32(buf) & 0xFFFFFFFF)
    return "%08X" % buf

window = Tk()
frame = Frame(window).pack()

window.title("Header und CRC")

window.geometry('480x300')

v1 = StringVar()
v1.set("FILE");

v2 = StringVar()
v2.set("CRC");

v3 = StringVar()
v3.set("Größe");


v4 = StringVar()
v5 = StringVar()
v6 = StringVar()

label1= Label(frame,textvariable = v1,fg="black", font=("Times", 12, "bold")).place(x = 20, y = 15)
label2= Label(frame,textvariable = v2,fg="black", font=("Times", 12, "bold")).place(x = 20, y = 50)
label3= Label(frame,textvariable = v3,fg="black", font=("Times", 12, "bold")).place(x = 20, y = 85)
label4= Label(frame,textvariable = v4,fg="black").place(x = 100, y = 15)
label5= Label(frame,textvariable = v5,fg="black").place(x = 100, y = 50)
label6= Label(frame,textvariable = v6,fg="black").place(x = 100, y = 85)

def clicked():
    file = filedialog.askopenfilename(filetypes = (("hex files","*.hex"),("all files","*.*")))
    v4.set(file);
    v5.set(str(CRC32_from_file(file)));
    v6.set(os.path.getsize(file));

button = Button(frame, text ="File auswählen", command = clicked).place(x = 20, y = 120)


window.mainloop()