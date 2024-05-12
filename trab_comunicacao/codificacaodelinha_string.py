# Desenvolvido por:
# Paulo S. A. Junior
# RA: 2022664

def string_testeCodificacaoLinha():
    print("codificacao por string ok")

#codificacao dibit a dibit
def string_cod_dibits_2b1q(cur_bits, cur_volt):
    #Se o primeiro bit eh 1, valor negativo.
    #Se o segundo bit eh 1, amplitude de 3.
    if cur_bits[1] == "1":
        cur_volt = 3
    else:
        cur_volt = 1
    if cur_bits[0] == "1":
        cur_volt *= -1
    return cur_volt

#codificacao de um pacote de bits
def string_cod_2b1q(bits):
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
            voltages[0] = string_cod_dibits_2b1q(cur_bits, 1)
        else:
            voltages[int(i/2)] = string_cod_dibits_2b1q(cur_bits, voltages[int(i/2 - 1)])
        i += 2
    
    #Retorna uma lista de tensoes
    return voltages

#decodificacao dibit a dibit
def string_dibit_decode_2b1q(volt, cur_volt):
    if cur_volt > 0:
        if volt == 1:
            dibit = "00"
        elif volt == 3:
            dibit = "01"
        elif volt == -1:
            dibit = "10"
        elif volt == -3:
            dibit = "11"
    else:
        if volt == -1:
            dibit = "00"
        elif volt == -3:
            dibit = "01"
        elif volt == 1:
            dibit = "10"
        elif volt == 3:
            dibit = "11"
    return dibit




#decodificacao de um pacote de bits
def string_decode_2b1q(volt):
    length = len(volt)
    bits = string_dibit_decode_2b1q(volt[0], 1)
    i = 1
    while i < length:
        bits += string_dibit_decode_2b1q(volt[i], volt[i - 1])
        i += 1
    return bits