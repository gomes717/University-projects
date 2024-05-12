# Desenvolvido por:
# Paulo S. A. Junior
# RA: 2022664

def testeCodificacaoLinha():
    print("codificacao por list ok")

#codificacao dibit a dibit
def cod_dibits_2b1q(cur_bits, cur_volt):
    #Se o primeiro bit eh 1, valor negativo.
    #Se o segundo bit eh 1, amplitude de 3.
    if cur_volt < 0:
        #ultimo volt valendo -3
        if cur_volt == -3:
            if cur_bits[0] == 1:
                if cur_bits[1] == 0:
                    cur_volt = 1
                else:
                    cur_volt = 3
            elif cur_bits[1] == 0:
                cur_volt = -1
        #ultimo volt valendo -1
        else:
            #inverte o sinal
            if cur_bits[0] == 1:
                if cur_bits[1] == 0:
                    cur_volt = 1
                else:
                    cur_volt = 3
            #nao inverte o sinal
            elif cur_bits[1] == 1:
                cur_volt = -3

    else:
        #ultimo volt valendo 3
        if cur_volt == 3:
            #inverte o sinal
            if cur_bits[0] == 1:
                if cur_bits[1] == 0:
                    cur_volt = -1
                else:
                    cur_volt = -3
            #nao inverte o sinal
            elif cur_bits[1] == 0:
                cur_volt = 1
        #ultimo volt valendo 1
        else:
            #inverte o sinal
            if cur_bits[0] == 1:
                if cur_bits[1] == 0:
                    cur_volt = -1
                else:
                    cur_volt = -3
            #nao inverte o sinal
            elif cur_bits[1] == 1:
                cur_volt = 3

    return cur_volt

#codificacao de um pacote de bits
def cod_2b1q(bits):
    #Pega de dois em dois bits e traduz em tensao
    length = len(bits)
    if length%2 :
        print("Numero impar de bits, descartando o ultimo")
        length -= 1
    voltages = [None]*int(length/2)
    i = 0
    while i < length :
        cur_bits = bits[i:i+2]
        if i == 0:
            voltages[0] = cod_dibits_2b1q(cur_bits, 1)
        else:
            voltages[int(i/2)] = cod_dibits_2b1q(cur_bits, voltages[int(i/2 - 1)])
        i += 2
    
    #Retorna uma lista de tensoes
    return voltages

#decodificacao dibit a dibit
def dibit_decode_2b1q(volt, cur_volt):
    if cur_volt > 0:
        if volt == 1:
            dibit = [0,0]
        elif volt == 3:
            dibit = [0,1]
        elif volt == -1:
            dibit = [1,0]
        elif volt == -3:
            dibit = [1,1]
    else:
        if volt == -1:
            dibit = [0,0]
        elif volt == -3:
            dibit = [0,1]
        elif volt == 1:
            dibit = [1,0]
        elif volt == 3:
            dibit = [1,1]
    return dibit




#decodificacao de um pacote de bits
def decode_2b1q(volt):
    length = len(volt)
    bits = [None] * (length*2) 
    dibit = dibit_decode_2b1q(volt[0], 1)
    bits[0] = dibit[0]
    bits[1] = dibit[1]
    i = 2
    while i < length*2:
        dibit = dibit_decode_2b1q(volt[int(i/2)], volt[int(i/2) - 1])
        bits[i] = dibit[0]
        bits[i+1] = dibit[1]
        i += 2
    return bits