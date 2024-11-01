import os
import shutil
import customtkinter as ctk

def sort() -> None:
    try:
        #Obtener elementos presentes en la ruta que se desea ordenar
        path = input_path.get()
        elements = os.listdir(path)
        #Recorremos cada elemento
        for element in elements:
            #Separar por punto para despues obtener la extension del archivo
            element_sep = element.split(sep='.')
            #Comprobar que si hayan archivos en la ruta
            if not(len(element_sep) > 1):
                raise IsADirectoryError
            extension = element_sep[-1]
            #Ruta de la carpeta con la extensión del archivo de esa iteración
            dir_path = fr"{path}\{extension} files"

            #Si no existe, creamos la carpeta que contendra archivos con esa extensión
            if not os.path.exists(dir_path):
                os.mkdir(dir_path)

            #Movemos el archivo de la ruta actual a la ruta de la carpeta con su extensión correspondiente
            shutil.move(os.path.join(path, element), dir_path)
    
    #En caso de excepcion mostrar mensaje correspondiente al usuario
    except FileNotFoundError:
        status_label.configure(text="Error: Path not found", text_color="#a02108", font=font_tuple)
    except IsADirectoryError:
        status_label.configure(text="No files in the path", text_color="#a02108", font=font_tuple)
    except Exception as e:
        status_label.configure(text=f"An error occurred, try again", text_color="#a02108", font=font_tuple)
    #Si todo salio bien mostrar mensaje al usuario
    else: 
        status_label.configure(text=f"Dir sorted successfully", text_color="#06430c", font=font_tuple)

#Crear ventana grafica
root = ctk.CTk()
root.title('Sorter directories')
root.geometry("480x300")
root.resizable(0, 0)

#Modos preinstalados en cyk
ctk.set_appearance_mode("dark")
ctk.set_default_color_theme("dark-blue")

font_tuple = ('Courier', 13, 'bold')

#Frame principal en el que estara toda la interfaz
main = ctk.CTkFrame(master=root, width=460, height=280, border_color="darkblue", border_width=5, 
                    corner_radius=10).pack(padx=10, pady=10)

#Etiqueta con el titulo
label1 = ctk.CTkLabel(master=main, text="Sort your directories automatically", text_color="#ffffff", 
                      bg_color="darkblue", height=35, width=460, font=font_tuple).place(relx=0.02,rely=0.051)

#Etiqueta con subtitulo
label2 = ctk.CTkLabel(master=main, text="Path to sort:", text_color="#ffffff", 
                      height=35, width=40, font=font_tuple).place(relx=0.2,rely=0.3)

#Creamos variable con la entrada del usuario
input_path = ctk.StringVar()

#Caja para el input del usuario
entry_path = ctk.CTkEntry(master=main, height=40, width=280, border_width=5, border_color="darkblue", 
                          textvariable=input_path)
entry_path.place(relx=0.2,rely=0.4)

#Boton para ordenar 
button = ctk.CTkButton(master=main, text="Send", fg_color="darkblue" , text_color="#ffffff", font=font_tuple,
                       width=118, height=40, command=sort).place(relx=0.38, rely=0.55)

#Label vacia para el estado de la ejecucion
status_label = ctk.CTkLabel(master=main, text="")
status_label.place(relx=0.32, rely=0.75)

#Boton para cerrar el programa
exit_button = ctk.CTkButton(master=main, text="Exit", fg_color="darkblue" , text_color="#ffffff", font=font_tuple,
                       width=90, height=30, command=root.destroy).place(relx=0.79, rely=0.85)

root.mainloop()