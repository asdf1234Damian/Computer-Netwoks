
from  tkinter  import *
import subprocess
root=Tk()
WIDTH=500
HEIGHT=350

class UI:
    def __init__(self):
        root.title("Practica 1")
        paddW = (root.winfo_screenwidth()-WIDTH)/2
        paddH = (root.winfo_screenheight()-HEIGHT)/2
        root.geometry('%sx%s+%s+%s' % (WIDTH, HEIGHT,int(paddW),int(paddH)))
        #IP input
        self.ip_lbl=Label(root,text="Ingrese una dirreccion IP valida")
        self.ip_lbl.pack(side=TOP, padx=10, pady=50)
        self.ip_In=Entry(root,width=300,justify="center")
        self.ip_In.pack(side=TOP, padx=0, pady=0)
        self.ip_In.insert(END,"000:000:000:000")
        #Run
        self.startBttn= Button(root, text="Analizar", command=self.analyse)
        self.startBttn.pack(side=TOP, padx=10, pady=10)
        #Class
        self.class_lbl=Label(root,text='Clase: -')
        self.class_lbl.pack(side=LEFT, padx=10, pady=10)
        #Type
        self.type_lbl=Label(root,text='Tipo: - ')
        self.type_lbl.pack(side=LEFT, padx=10, pady=10)
        #Network
        self.net_lbl=Label(root,text='Red:     ---:---:---:---')
        self.net_lbl.pack(side=TOP, padx=10, pady=5)
        #Broadcast
        self.brd_lbl=Label(root,text='Broadcast: ---:---:---:---')
        self.brd_lbl.pack(side=TOP, padx=10, pady=5)
        #Range
        self.rangeMin_lbl=Label(root,text='Rango min: ---:---:---:---')
        self.rangeMin_lbl.pack(side=TOP, padx=10, pady=5)
        #Range
        self.rangeMax_lbl=Label(root,text='Rango max: ---:---:---:---')
        self.rangeMax_lbl.pack(side=TOP, padx=10, pady=5)
        #Host
        self.host_lbl=Label(root,text='Host:   ---:---:---:---')
        self.host_lbl.pack(side=TOP, padx=10, pady=5)
        root.mainloop()

    def analyse(self):
        ip = self.ip_In.get().split(':')
        # Clase de la IP
        results = subprocess.check_output(["./ipInfo",ip[0],ip[1],ip[2],ip[3]]).decode('ascii').split(',')
        print(results)
        self.class_lbl.config(text='Clase: '+results[0])
        self.net_lbl.config(text='Red:     '+results[3])
        self.type_lbl.config(text='Tipo: '+results[2])
        self.host_lbl.config(text='Host:   '+results[1])
        self.brd_lbl.config(text='Broadcast: '+results[4])
        self.rangeMin_lbl.config(text='Rango min: '+results[5])
        self.rangeMax_lbl.config(text='Rango max: '+results[6])
mainUI = UI()
