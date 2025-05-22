import serial
import serial.tools.list_ports

def byte_to_hex(byte_str):       
        return ''.join( [ "%02X" % ord( x ) for x in byte_str ] ).strip()

def HexToByte(hexStr):
    bytes = []
    hexStr = ''.join( hexStr.split(" ") )

    for i in range(0, len(hexStr), 2):
        bytes.append( chr( int (hexStr[i:i+2], 16 ) ) )
    return ''.join( bytes )

class serialApp ():
    def __init__(self):
        self.serial_port = serial.Serial()
        self.baudrate = [9600,115200]
        self.portlist = []
        self.serial_port.timeout = 1

    def update_port(self): #updates de portas seriais
        self.portlist =[port.device for port in serial.tools.list_ports.comports()]
        print (self.portlist)

    def connect_serial(self):
        try:
            self.serial_port.open()
            print("CONECTADO",self.serial_port.port)
            return True
        except:
            print("Houve um erro")
            return False

    def close_serial(self):
        self.serial_port.close()
        print("DESCONECTADO", self.serial_port.port)
    
    def read_serial(self):
            data = self.serial_port.readline()
            return data

    def send_serial (self,data):
        if(self.serial_port.isOpen()):
            message = str(data) + "\r\n"
            self.serial_port.write(message.encode())
            
    def clear_serial(self):
        self.serial_port.reset_input_buffer()
        self.serial_port.reset_output_buffer()

    def get_count(self):
        self.clear_serial()
        self.send_serial("count")
        message = self.read_serial()
        message = self.read_serial()

        count = int(((message.decode()).replace("Count: ", "")).replace("\n", ""))
        return count

    def get_coletas(self):
        self.send_serial("storage extract")

        values = [[]]

        message = self.read_serial()
        message = self.read_serial()
        message = self.read_serial()
        message = self.read_serial()
        idx = 0
        while(message != b''):
            if(b'=' in message):
                idx += 1
                values.append([])
            else:
                value = float((message.decode()).replace(" C\n", ""))
                values[idx].append(value)

            message = self.read_serial()

        return values






## coletas
import numpy as np
import matplotlib.pyplot as plt

def coletas_show(matriz):
    """
    Mostra quantos coletas de dados existem e suas características
    """
    print(f"\nExistem {len(matriz)} coletas de dados disponíveis:")
    for i, conjunto in enumerate(matriz):
        minutos = (len(conjunto) - 1)*10
        print(f"{i+1}: {minutos/60:.2f} horas")

def coletas_plot(matriz, indice):
    """
    Plota a coleta de dados selecionado com marcação temporal
    """
    conjunto = matriz[indice]
    
    # Criar array de tempo (intervalos de 10 minutos)
    tempo = np.arange(len(conjunto)) * (10/60)
    
    plt.figure(figsize=(10, 6))
    plt.plot(tempo, conjunto, 'b', linewidth=2)
    plt.grid(True)
    plt.title(f'Coleta de Dados {indice+1}')
    plt.xlabel('Tempo (horas)')
    plt.ylabel('Temperatura (°C)')
    plt.ylim(0,40)
    plt.xlim(0, tempo[-1])
    plt.show()



## extract
from serial_app import serialApp
from coletas import *

ser = serialApp()

matriz_dados = [[]]


def main():
    #ser.update_port()
    ser.serial_port.port = '/dev/ttyUSB0'
    ser.serial_port.baudrate = 115200
    ser.connect_serial()

    matriz_dados = ser.get_coletas()

    coletas_show(matriz_dados)
    
    # User choice
    while True:
        try:
            escolha = int(input("\nEscolha um conjunto para visualizar (0 para sair): "))
            if escolha == 0:
                ser.close_serial()
                break
            elif 1 <= escolha <= len(matriz_dados):
                coletas_plot(matriz_dados, escolha-1)
            else:
                print("Escolha inválida!")
        except ValueError:
            print("Por favor, digite um número válido!")

if __name__ == "__main__":
    main()