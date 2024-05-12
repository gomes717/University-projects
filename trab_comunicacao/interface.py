# Desenvolvido por:
#   Interface: 
#   Gustavo V. Gulmine 
#   RA: 2026953
# 
#   Comunicação por socket: 
#   Paulo S. A. Junior
#   RA: 2022664
#
#   Gráfico do sinal:
#   Guilherme G. Barboza
#   RA: 2022567

import sys
import socket
import pickle
from PyQt5 import QtWidgets as wdg
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg, NavigationToolbar2QT
import matplotlib.pyplot as plt
import numpy as np
from criptografia import *
from codificacaodelinha_string import *
from codificacaodelinha_list import *

class App:

    def __init__(self):
        #--------------------------------------------------------------------#
        #///// WINDOW CREATION \\\\\#

        self.application = wdg.QApplication(sys.argv)

        # Get screen dimensions
        self.sSize = self.application.primaryScreen().size()
        sWidth = self.sSize.width()
        sHeight = self.sSize.height()

        # Create window
        self.window = wdg.QWidget()
        self.window.setGeometry(sWidth/6, sHeight/6, sWidth/1.5, sHeight/1.5)
        self.window.setMinimumSize(self.sSize/2.5)
        self.window.setWindowTitle("Trabalho - Codificação de Linha")

        # Get window dimensions
        self.wSize = self.window.size()
        wWidth = self.wSize.width()
        wHeight = self.wSize.height()
        
        #--------------------------------------------------------------------#
        #///// WINDOW LAYOUT CREATION \\\\\#

        # Create and set layouts
        self.mainLayout = wdg.QVBoxLayout(self.window)
        self.inputLayout = wdg.QHBoxLayout()
        self.messageLayout = wdg.QVBoxLayout()
        self.connectionLayout = wdg.QVBoxLayout()

        #--------------------------------------------------------------------#
        #///// WINDOW ELEMENTS CREATION \\\\\#

        # Create and set window elements
        self.selector = wdg.QComboBox()
        self.selector.addItem("Emissor")
        self.selector.addItem("Receptor")

        self.ipLabel = wdg.QLabel()
        self.ipLabel.setText("IP")
        self.ipTextBox = wdg.QTextEdit()
        self.ipTextBox.setMaximumSize(wWidth/6, wHeight/12)

        self.portLabel = wdg.QLabel()
        self.portLabel.setText("Porta")
        self.portTextBox = wdg.QTextEdit()
        self.portTextBox.setMaximumSize(wWidth/6, wHeight/12)

        self.messageLabel = wdg.QLabel()
        self.messageLabel.setText("Mensagem")
        self.messageTextBox = wdg.QTextEdit()

        self.sendButton = wdg.QPushButton()
        self.sendButton.setText("Enviar")

        self.receiveButton = wdg.QPushButton()
        self.receiveButton.setText("Receber")
        self.receiveButton.hide()

        self.cryptoLabel = wdg.QLabel()
        self.cryptoLabel.setText("Mensagem Criptografada")
        self.cryptoTextBox = wdg.QTextEdit()
        self.cryptoTextBox.setReadOnly(1)

        self.binaryLabel = wdg.QLabel()
        self.binaryLabel.setText("Binário")
        self.binaryTextBox = wdg.QTextEdit()
        self.binaryTextBox.setReadOnly(1)

        self.lineCodeLabel = wdg.QLabel()
        self.lineCodeLabel.setText("Codificação de Linha - 2B1Q")
        self.lineCodeTextBox = wdg.QTextEdit()
        self.lineCodeTextBox.setReadOnly(1)

        self.graphLabel = wdg.QLabel()
        self.graphLabel.setText("Grafico - 2B1Q")
        self.figure = plt.figure()
        self.canvas = FigureCanvasQTAgg(self.figure)
        self.canvas.setMinimumSize(wWidth*0.8, wHeight/8)
        self.toolbar = NavigationToolbar2QT(self.canvas, None)

        # Set connections
        self.selector.currentIndexChanged.connect(self.senderReceiverSwitch)
        self.sendButton.clicked.connect(self.messageSent)
        self.receiveButton.clicked.connect(self.messageReceived)

        # Set layouts
        self.connectionLayout.addWidget(self.selector)
        self.connectionLayout.addWidget(self.ipLabel)
        self.connectionLayout.addWidget(self.ipTextBox)
        self.connectionLayout.addWidget(self.portLabel)
        self.connectionLayout.addWidget(self.portTextBox)
        self.connectionLayout.addWidget(self.sendButton)
        self.connectionLayout.addWidget(self.receiveButton)
        
        self.messageLayout.addWidget(self.messageLabel)
        self.messageLayout.addWidget(self.messageTextBox)
        
        self.inputLayout.addLayout(self.connectionLayout)
        self.inputLayout.addLayout(self.messageLayout)

        self.mainLayout.addLayout(self.inputLayout)
        self.mainLayout.addWidget(self.cryptoLabel)
        self.mainLayout.addWidget(self.cryptoTextBox)
        self.mainLayout.addWidget(self.binaryLabel)
        self.mainLayout.addWidget(self.binaryTextBox)
        self.mainLayout.addWidget(self.lineCodeLabel)
        self.mainLayout.addWidget(self.lineCodeTextBox)
        self.mainLayout.addWidget(self.graphLabel)
        self.mainLayout.addWidget(self.canvas)
        self.mainLayout.addWidget(self.toolbar)

    #====================================================================#
    #///// WINDOW ELEMENTS EVENT CHECK \\\\\#

    def plot(self, twoboneq):
        #limpa canvas anterior
        self.figure.clear()
        size = np.arange(len(twoboneq))
        ax = self.figure.add_subplot(111)
        #cria grafico em estilo de sinal
        ax.step(size, twoboneq, where='post', label='post')
        self.canvas.draw()

    def senderReceiverSwitch(self):
        if self.selector.currentIndex() == 0:
            self.sendButton.show()
            self.receiveButton.hide()
            self.ipTextBox.clear()
            self.portTextBox.clear()
            self.messageTextBox.setReadOnly(0)
            self.messageTextBox.clear()
            self.cryptoTextBox.clear()
            self.binaryTextBox.clear()
            self.lineCodeTextBox.clear()
            
        else:
            self.sendButton.hide()
            self.receiveButton.show()
            self.ipTextBox.clear()
            self.portTextBox.clear()
            self.messageTextBox.setReadOnly(1)
            self.messageTextBox.clear()
            self.cryptoTextBox.clear()
            self.binaryTextBox.clear()
            self.lineCodeTextBox.clear()


    def messageSent(self):
        msg = self.messageTextBox.toPlainText()
        msgC = SimpleCripto(msg)
        msgB = tobits(msgC)
        msgLC = cod_2b1q(msgB)

        self.plot(msgLC)
        self.cryptoTextBox.setText(msgC)
        self.binaryTextBox.setText(str(msgB))
        self.lineCodeTextBox.setText(str(msgLC))

	#conecta num socket e envia mensagem
        host = self.ipTextBox.toPlainText()
        port = int(self.portTextBox.toPlainText())
        with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
                s.connect((host, port))
                s.send(pickle.dumps(msgLC))

    def messageReceived(self):

	#conecta um socket no endereco (HOST:PORT) e escuta por mensagens
        host = self.ipTextBox.toPlainText()
        port = int(self.portTextBox.toPlainText())
        with socket.socket(socket.AF_INET, socket.SOCK_DGRAM, 0) as s:
                s.bind((host,port))
                data = pickle.loads(s.recv(1024000))
                if data:
                        msgLC = data
                        msgB = decode_2b1q(data)
                        msgC = frombits(msgB)
                        msg = SimpleDeCripto(msgC)

                        self.plot(msgLC)
                        self.cryptoTextBox.setText(msgC)
                        self.binaryTextBox.setText(str(msgB))
                        self.lineCodeTextBox.setText(str(msgLC))
                        self.messageTextBox.setText(msg)

#        msg = "teste"
#        self.messageTextBox.setText(msg)
#        self.cryptoTextBox.setText(msg)
#        self.binaryTextBox.setText(msg)
#        self.lineCodeTextBox.setText(msg)

    #====================================================================#
    #///// OTHER FUNCTIONS \\\\\#

    # Execute application
    def execute(self):

        self.window.show()
        self.application.exec_()

    #https://build-system.fman.io/pyqt5-tutorial
    #https://doc.qt.io/qt-5/widget-classes.html#basic-widget-classes
    #https://doc.qt.io/qt-5/qlayout-members.html
