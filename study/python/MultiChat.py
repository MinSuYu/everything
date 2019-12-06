import sys
from tkinter import *
from tkinter.filedialog import asksaveasfilename
import threading
import socket
import time

conn_array = []
addr_array=[]
username_array = []
username="Self"
count=0
main_body_text=0
port = []
myname=""
th = []

class Server(threading.Thread):
    def __init__(self,port):
        threading.Thread.__init__(self)
        self.port=port

    def run(self):
        global conn_array
        global addr_array
        global username_array
        s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
        s.bind(('',self.port))
        s.listen(1)
        writeToScreen("Socket is good, waiting for connections on port : "+str(self.port),"System")
        while 1:
            if len(conn_array) <= 3:
                a=len(username_array)
                conn_init,addr_init=s.accept()
                conn_array.append(conn_init)
                addr_array.append(addr_init)
                thindex = threading.Thread(target=Runner,args=(conn_init,str(addr_init[0]),False))
                th.append(thindex)
                thindex.start()
                global statusConnect
                statusConnect.set("Disconnect")
                connecter.config(state=DISABLED)
                if a==len(username_array):
                    time.sleep(1)
                writeToScreen("accept Suceess",username_array[a])
            else:
                conn, addr = s.accept()
                netThrow(conn, "room is full!!")
                time.sleep(3)
                conn.close()

def QuickServer():
    Server(9990).start()

def resetting(master):
    connecter.config(state=NORMAL)
    master.destroy()
    
def server_options_window(master):
    """Launches server options window for getting port."""
    top = Toplevel(master)
    top.title("Connection options")
    top.grab_set()
    top.protocol("WM_DELETE_WINDOW", lambda: resetting(top))
    Label(top, text="Port:").grid(row=0)
    port = Entry(top)
    port.grid(row=0, column=1)
    port.focus_set()
    go = Button(top, text="Launch", command=lambda:
                server_options_go(port.get(), top))
    go.grid(row=1, column=1)

def server_options_go(port,window):
    if port_process(port):
        Server(int(port)).start()
    else:
        writeToScreen("you mistake input")
        connecter.config(state=NORMAL)
    window.destroy()

def saveHistory():
    """Saves history with Tkinter's asksaveasfilename dialog."""
    global main_body_text
    file_name = asksaveasfilename(
        title="Choose save location",
        filetypes=[('Plain text', '*.txt'), ('Any File', '*.*')])
    print(file_name)
    try:
        filehandle = open(file_name + ".txt", "w")
    except IOError:
        print("Can't save history.")
        return
    contents = main_body_text.get(1.0, END)
    for line in contents:
        filehandle.write(line)
    filehandle.close()

def list_info(master,mynick=""):
    top=Toplevel(master)
    top.title("talk list")
    top.protocol("WM_DELETE_WINDOW",lambda:top.destroy())
    top.grab_set()
    top.focus_set()
    listbox=Listbox(top)
    for i in range(0,len(username_array)):
        listbox.insert(END,username_array[i])
    listbox.pack()

class Client(threading.Thread):
    def __init__(self,host,port,name):
        threading.Thread.__init__(self)
        self.port=port
        self.host=host
        self.name=name
    def run(self):
        global conn_array
        global port
        
        conn_init=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
        conn_init.connect((self.host,self.port))
        port.append(self.port)
        writeToScreen("connect Suceess","Chatting server")
        netThrow(conn_init,"TnTiTcTk : "+self.name)
        conn_array.append(conn_init)
        threading.Thread(target=Runner,args=(conn_init,self.host,True)).start()
        global statusConnect
        statusConnect.set("Disconnect")
        connecter.config(state=NORMAL)

def client_options_go(dest,nickname,port,window):
    window.destroy()
    if ip_process(dest.split(".")) and port_process(port) and len(nickname)>0:
        Client(dest,int(port),nickname).start()
    else:
        writeToScreen("you mistake input")
        connecter.config(state=NORMAL)
    

def ip_process(ipArray):
    if len(ipArray) != 4:
        return False
    for ip in ipArray:
        if not ip.isnumeric():
            return False
        if int(ip)<0 or int(ip)>255:
            return False
    return True

def port_process(port):
    if not port.isnumeric():
        return False
    if int(port)<0 or 65555<int(port):
        return False
    return True

def QuickClient():
    #Client("192.168.10.73",9990).start()
    window = Toplevel(root)
    window.title("Connection options")
    window.grab_set()
    Label(window,text="Server IP : ").grid(row=0)
    destination = Entry(window)
    destination.grid(row=0,column=1)
    Label(window,text="Nick name : ").grid(row=1)
    nickname = Entry(window)
    nickname.grid(row=1,column=1)
    go = Button(window,text="Connect",command=lambda:
                client_options_go(destination.get(),nickname.get().strip(),"9990",window))
    go.grid(row=2,column=1)

def client_options_window(master):
    """Launches client options window for getting destination hostname
    and port.

    """
    top = Toplevel(master)
    top.title("Connection options")
    top.protocol("WM_DELETE_WINDOW", lambda: resetting(top))
    top.grab_set()
    Label(top, text="Server IP:").grid(row=0)
    location = Entry(top)
    location.grid(row=0, column=1)
    location.focus_set()
    Label(top, text="Port:").grid(row=1)
    port = Entry(top)
    port.grid(row=1, column=1)
    Label(top,text="Nick name : ").grid(row=2)
    nickname = Entry(top)
    nickname.grid(row=2,column=1)
    go = Button(top, text="Connect", command=lambda:
                client_options_go(location.get(),nickname.get().strip(), port.get(), top))
    go.grid(row=3, column=1)

def netThrow(conn,text):
    try:
        conn.send(text.encode("utf-8"))
    except socket.error:
        writeToScreen("throw fail","SYSTEM")

def netCatch(conn):
    try:
        message = conn.recv(512)
        return message.decode("utf-8")
    except socket.error:
        writeToScreen("catch fail","SYSTEM")

def contacts_window(master):
    top=Toplevel(master)
    top.title("Contacts")
    top.grab_set()
    scrollbar=Scrollbar(top,orient=VERTICAL)
    listbox=Listbox(top,yscrollcommand=scrollbar.set)
    scrollbar.config(command=listbox.yview)
    scrollbar.pack(side=RIGHT,fill=Y)
    buttons=Frame(top)
    cBut=Button(buttons,text="Connect",command=lambda:contacts_connect(listbox.get(ACTIVE).split(" ")))
    cBut.pack(side=LEFT)
    dBut=Button(buttons,text="Remove",command=lambda:contacts_remove(listbox.get(ACTIVE).split(" "),listbox))
    dBut.pack(side=LEFT)
    aBut=Button(buttons,text="Add",command=lambda:contacts_add(listbox,top))
    aBut.pack(side=LEFT)
    buttons.pack(side=BOTTOM)
    listbox.pack(side=LEFT,fill=BOTH,expand=1)

def contacts_connect(item):
    Client(item[1],int(item[2]),item[0]).start()

def contacts_remove(item,listbox):
    if listbox.size()!=0:
        listbox.delete(ACTIVE)

def contacts_add(listbox,master):
    top=Toplevel(master)
    top.title("Contact add")
    Label(top,text="Nickname:").grid(row=0)
    nickname=Entry(top)
    nickname.focus_set()
    nickname.grid(row=0,column=1)
    Label(top,text="IP:").grid(row=1)
    ip=Entry(top)
    ip.grid(row=1,column=1)
    Label(top,text="Port:").grid(row=2)
    port=Entry(top)
    port.grid(row=2,column=1)
    go=Button(top,text="Add",command=lambda:
              contacts_add_helper(nickname.get(),ip.get(),port.get(),
                                  top,listbox))
    go.grid(row=3,column=1)


def contacts_add_helper(nickname,ip,port,window,listbox):
    if ip_process(ip.split(".")) and port_process(port) and len(nickname)>0:
        listbox.insert(END,nickname+" "+ip+" "+port)
        window.destroy()
        return
def username_options_window(master):
    top=Toplevel(master)
    top.title("Nickname Change")
    top.grab_set()
    Label(top,text="Nickname:").grid(row=0)
    name=Entry(top)
    name.focus_set()
    name.grid(row=0,column=1)
    go=Button(top,text="Change",command=lambda:username_options_go(name.get(),top))
    go.grid(row=1,column=1)

def username_options_go(name,window):
    if len(conn_array)!=0:
        netThrow(conn_array[0],"TcThTaTn : "+name)
    else:
        writeToScreen("before you must connect","System")
    window.destroy()

def ProgramExit() :
    global conn_array

    fd = conn_array[0].getsockname()
    
    netThrow(conn_array[0], "TdTeTlTe : "+str(fd[1]))

    conn_array[0].close()
    conn_array.pop()
    root.destroy()
    
def Runner(conn,addr,clientType,name=""):
    global username_array
    global conn_array
    while 1:
        data = netCatch(conn)
        if type(data) == type(None) :
            time.sleep(10)
            break
        elif clientType==False:            
            if data[0:11]=="TnTiTcTk : ":
                if len(username_array)!=0:
                    for i in range(len(username_array)):
                        netThrow(conn_array[i],"TuTsTeTr : "+data[11:])
                    for i in range(len(username_array)):
                        netThrow(conn,"TuTsTeTr : "+username_array[i])
                try:
                    username_array.find(data[11:])
                except AttributeError:
                    username_array.append(data[11:])
                    continue
            elif data[0:11]=="TdTeTlTe : ":
                i = 0
                for ip, por in addr_array:
                    if str(por) == data[11:] :
                        port = por
                        break
                    i += 1
                conn_array[i].close()
                conn_array.pop(i)
                addr_array.pop(i)
                username_array.pop(i)
            elif data[0:11]=="TcThTaTn : ":
                writeToScreen(" nick : "+username_array[conn_array.index(conn)]+" change nickname nick : "+data[11:],"System")
                username_array[conn_array.index(conn)]=data[11:]
                for i in range(len(conn_array)):
                    if i!=conn_array.index(conn):
                        netThrow(conn_array[i],data)
            else:
                for i in range(0,len(conn_array)):
                    if conn!=conn_array[i]:
                        netThrow(conn_array[i],data+"+"+username_array[conn_array.index(conn)])
                    else:
                        writeToScreen(data,username_array[i])
        else:
            if data[0:11]=="TuTsTeTr : ":
                if myname!=data[11:]:
                    username_array.append(data[11:])
                continue
            if data[0:11]=="TcThTaTn : ":
                writeToScreen(" nick : "+username_array[conn_array.index(conn)]+" change nickname nick : "+data[11:],"System")
                username_array[conn_array.index(conn)]=data[11:]
                continue
            if data.rfind("+")==-1:
                writeToScreen(data,"Server")
            else:
                writeToScreen(data[0:data.rfind("+")],data[data.rfind("+")+1:])
                        
def processUserText(event):
    writeToScreen(text_input.get(),username)
    netThrow(conn_array[0],text_input.get())
    text_input.delete(0,END)

def writeToScreen(text,user=""):
    global main_body_text
    main_body_text.config(state=NORMAL)
    main_body_text.insert(END,'\n')
    if user:
        main_body_text.insert(END,"["+user+"]")
    main_body_text.insert(END,text)
    main_body_text.yview(END)
    main_body_text.config(state=DISABLED)

def connects(clientType):
    global conn_array
    connecter.config(state=DISABLED)
    if len(conn_array) == 0:
        if clientType == 0:
            client_options_window(root)
        if clientType == 1:
            server_options_window(root)
    else:
        ProgramExit()

def toOne():
    global clientType
    clientType = 0


def toTwo():
    global clientType
    clientType = 1

root=Tk()
root.title("MulitChat")

menubar=Menu(root)

file_menu = Menu(menubar,tearoff=0)
file_menu.add_command(label="Save Chat",command=lambda:saveHistory())
file_menu.add_command(label="Change Username",command=lambda:username_options_window(root))
file_menu.add_command(label="Exit",command=lambda:root.destroy())
menubar.add_cascade(label="File",menu=file_menu)

connection_menu = Menu(menubar,tearoff=0)
connection_menu.add_command(label="Quick Connect",command=QuickClient)
connection_menu.add_command(label="Connect on port",command=lambda:client_options_window(root))
connection_menu.add_command(label="Disconnect",command=ProgramExit)
menubar.add_cascade(label="Connect",menu=connection_menu)

server_menu = Menu(menubar,tearoff=0)
server_menu.add_command(label="Launch Server",command=QuickServer)
server_menu.add_command(label="Listen on port",command=lambda:server_options_window(root))
menubar.add_cascade(label="Server",menu=server_menu)

menubar.add_command(label="Contacts",command=lambda:contacts_window(root))

menubar.add_command(label="talk list",command=lambda:list_info(root,myname))

root.config(menu=menubar)

main_body = Frame(root,height=20,width=60)

main_body_text = Text(main_body)
body_text_scroll = Scrollbar(main_body)
main_body_text.focus_set()
body_text_scroll.pack(side=RIGHT,fill=Y)
main_body_text.pack(side=LEFT,fill=Y)
body_text_scroll.config(command=main_body_text.yview)
main_body_text.config(yscrollcommand=body_text_scroll.set)
main_body.pack()

main_body_text.insert(END,"Welcome to the chat program!")
main_body_text.config(state=DISABLED)

text_input = Entry(root,width=60)
text_input.bind("<Return>",processUserText)
text_input.pack()

statusConnect = StringVar()
statusConnect.set("Connect")
clientType = 1
Radiobutton(root,text="Client",variable=clientType,value=0,command=toOne).pack(anchor=E)
Radiobutton(root,text="Server",variable=clientType,value=1,command=toTwo).pack(anchor=E)
connecter = Button(root,textvariable=statusConnect,command=lambda: connects(clientType))
connecter.pack()

root.mainloop()
