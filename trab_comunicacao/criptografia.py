# Desenvolvido por:
# Guilherme G. Barboza
# RA: 2022567

def SimpleCripto(msg):
    msgcripto = [chr(ord(msg[-i]) + 2) for i in range(len(msg))]
    return ''.join(msgcripto)

def SimpleDeCripto(msg):
    msgdecripto = [chr(ord(msg[-i]) - 2) for i in range(len(msg))]
    return ''.join(msgdecripto)

def tobits(s):
    result = []
    for c in s:
        bits = bin(ord(c))[2:]
        bits = '00000000'[len(bits):] + bits
        result.extend([int(b) for b in bits])
    return result

def frombits(bits):
    chars = []
    for b in range(int(len(bits) / 8)):
        byte = bits[b*8:(b+1)*8]
        chars.append(chr(int(''.join([str(bit) for bit in byte]), 2)))
    return ''.join(chars)