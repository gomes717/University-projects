
import random
import math

#pesos
#########################################
peso_DU = 7      #distancia entre unidades
peso_QV = -4.5    #quantidade de vacinas entregues
peso_TN = 4.5    #tempo medio normalizado no horario
peso_QA = 2      #quantidade de acidentes na rota
peso_CO = 1      #caminho obstruido, como obras
#########################################

#entradas
#########################################
numero_unidades = 10
#qtd_vacina = [50, 100, 30]
#dst_central_unidade = [2, 5 ,6]
#dst_entre_unidades = [[0, 3, 6], [3, 0, 7], [6, 7, 0]]
#tempo_medio_central = [4,10,12]
#tempo_medio = [[0, 6, 12], [6,0,14], [12, 14, 0]]
#tempo = [[0,5,13], [5,0,15], [13,15,0]]
#qtd_acidente_central = [10, 7, 13]
#qtd_acidente = [[0, 5, 8], [5, 0, 3], [8,3,0]]
#caminho_obstruido_central = [0,0,0]
#caminho_obstruido = [[0, 0, 1], [0, 0, 0], [1,0,0]]
#########################################

qtd_vacina = []
dst_central_unidade = []
dst_entre_unidades = [[0]*numero_unidades for i in range(numero_unidades)]
tempo_medio_central = []
tempo_medio = [[0]*numero_unidades for i in range(numero_unidades)]
tempo = [[0]*numero_unidades for i in range(numero_unidades)]
qtd_acidente_central = []
qtd_acidente = [[0]*numero_unidades for i in range(numero_unidades)]
caminho_obstruido_central = []
caminho_obstruido = [[0]*numero_unidades for i in range(numero_unidades)]


tamanho_caminho_tempera = []
tamanho_subida_encosta = []
tempo_subida = []
tempo_tempera = []

for i in range(numero_unidades):
    qtd_vacina.append(random.randint(10, 100))
    dst_central_unidade.append(random.randint(1, 15))
    tempo_medio_central.append(dst_central_unidade[i]*random.randint(1, 4))
    qtd_acidente_central.append(random.randint(0, 20))
    caminho_obstruido_central.append(random.randint(0, 1))
    for j in range(numero_unidades):
        if i == j:
            continue
        dst_entre_unidades[i][j] = random.randint(1, 15)
        dst_entre_unidades[j][i] = dst_entre_unidades[i][j] + random.randint(0, 3)
        tempo_medio[i][j] = dst_entre_unidades[i][j]*random.randint(1, 4)
        tempo_medio[j][i] = dst_entre_unidades[j][i]*random.randint(1, 4)
        qtd_acidente[i][j] = random.randint(0, 20)
        qtd_acidente[j][i] = qtd_acidente[i][j]
        caminho_obstruido[i][j] = random.randint(0, 1)
        caminho_obstruido[j][i] = caminho_obstruido[i][j]
valor_max = 10
valor_min = 1

def map(input, max_input, min_input):
    if  max_input == min_input:
        return valor_min
    val = (input-min_input)*((valor_max - valor_min)/(max_input - min_input)) + valor_min
    return val


#Função que cria um grafo denso no formato de matrix
def criaGrafo():
    grafo = [[0]*numero_unidades for i in range(numero_unidades)]
    for i in range(numero_unidades):
        for j in range(numero_unidades):
            if i == j:
                continue
            grafo[i][j] +=  map(dst_entre_unidades[i][j], max(max(dst_entre_unidades)), min(min(dst_entre_unidades)))*peso_DU
            grafo[i][j] +=  map(tempo_medio[i][j], max(max(tempo_medio)), min(min(tempo_medio)))*peso_TN
            grafo[i][j] +=  map(qtd_acidente[i][j], max(max(qtd_acidente)),min(min(qtd_acidente)))*peso_QA
            grafo[i][j] +=  map(caminho_obstruido[i][j], max(max(caminho_obstruido)), min(min(caminho_obstruido)))*peso_CO
            grafo[i][j] +=  map(qtd_vacina[j], max(qtd_vacina), min(qtd_vacina))*peso_QV
    return grafo

grafo = criaGrafo()

def custoCaminho(caminho):
    custo = map(dst_central_unidade[caminho[0]], max(dst_central_unidade), min(dst_central_unidade))*peso_DU
    custo += map(dst_central_unidade[caminho[-1]], max(dst_central_unidade), min(dst_central_unidade))*peso_DU
    custo +=  map(tempo_medio_central[caminho[0]], max(tempo_medio_central), min(tempo_medio_central))*peso_TN
    custo +=  map(tempo_medio_central[caminho[-1]], max(tempo_medio_central), min(tempo_medio_central))*peso_TN
    custo +=  map(qtd_acidente_central[caminho[0]], max(qtd_acidente_central),min(qtd_acidente_central))*peso_QA
    custo +=  map(qtd_acidente_central[caminho[-1]], max(qtd_acidente_central),min(qtd_acidente_central))*peso_QA
    custo +=  map(caminho_obstruido_central[caminho[0]], max(caminho_obstruido_central), min(caminho_obstruido_central))*peso_CO
    custo +=  map(caminho_obstruido_central[caminho[-1]], max(caminho_obstruido_central), min(caminho_obstruido_central))*peso_CO
    for i in range(numero_unidades - 1):
        custo += grafo[caminho[i]][caminho[i + 1]]
    return custo


def geraVizinhos(estadoAtual):
    listaVizinhos = []
    vizinho = estadoAtual
    tamanhoCaminho = len(estadoAtual) - 1
    posTroca = 0
    while posTroca < tamanhoCaminho:
        vizinho = estadoAtual[:]
        aux = vizinho[posTroca]
        vizinho[posTroca] = vizinho[posTroca + 1]
        vizinho[posTroca + 1] = aux
        listaVizinhos.append(vizinho)
        posTroca += 1
    return listaVizinhos

## t: instante (iteração) atual
## n: iteração final
def funcaoT(t, n):
    temperatura = 0 + (100 - 0)*((n-t)/n)**2
    return temperatura
    
## estadoInicial: Estado de configuralçai inicial
## qtdIteracoes: Quantidade de comparações
def temperaSimulada(estadoInicial, qtdeIteracoes):
    temperatura = 100
    iteracaoAtual = 0
    estadoAtual = estadoInicial
    while temperatura > 0:
        temperatura = funcaoT(iteracaoAtual, qtdeIteracoes)
        if temperatura == 0:
            tempo_tempera.append(iteracaoAtual)
            return estadoAtual
        vizinhos = geraVizinhos(estadoAtual)
        proximoVizinho = vizinhos[random.randint(0,len(vizinhos) -1)]
        diferenca = custoCaminho(proximoVizinho) - custoCaminho(estadoAtual)
        if diferenca < 0:
            estadoAtual = proximoVizinho
        else:
            proba = math.e **(-diferenca/temperatura)
            rand = random.randint(0, 100)/100
            if rand < proba:
                estadoAtual = proximoVizinho
        iteracaoAtual += 1

## estadoInicial
def subidaEncosta(estadoInicial):
    estadoAtual = estadoInicial[::]
    c = 0
    while True:
        c +=1
        vizinhos = geraVizinhos(estadoAtual)
        proximoVizinho = encontraMelhorVizinho(vizinhos)
        if custoCaminho(proximoVizinho) >= custoCaminho(estadoAtual):
            tempo_subida.append(c)
            return estadoAtual
        estadoAtual = proximoVizinho

## vizinhos: Lista de vizinhos
## Retorna os vizinhos
def encontraMelhorVizinho(vizinhos):
    melhorVizinho = None
    custo = 1000000000000
    for i in vizinhos:
        valor = custoCaminho(i)
        if valor < custo:
            melhorVizinho = i
            custo = valor
    return melhorVizinho

for j in range(100):
    caminho = []
    while len(caminho) < numero_unidades:
        x = random.randint(0,numero_unidades -1)
        if not x in caminho:
            caminho.append(x)
    #print(caminho)
    res = subidaEncosta(caminho)
    tamanho_subida_encosta.append(custoCaminho(res))
    res = temperaSimulada(caminho, 1000)
    tamanho_caminho_tempera.append(custoCaminho(res))

#print(tempo_tempera, tamanho_caminho_tempera)
#print(tempo_subida, tamanho_subida_encosta)

import statistics

media_temperada_it = statistics.mean(tempo_tempera)
media_subida_it = statistics.mean(tempo_subida)
media_tempera_dst = statistics.mean(tamanho_caminho_tempera)
media_subida_dst = statistics.mean(tamanho_subida_encosta)

dp_temperada_it = statistics.stdev(tempo_tempera, xbar=None)
dp_subida_it = statistics.stdev(tempo_subida, xbar=None)
dp_tempera_dst = statistics.stdev(tamanho_caminho_tempera, xbar=None)
dp_subida_dst = statistics.stdev(tamanho_subida_encosta, xbar=None)

print(media_tempera_dst, media_subida_dst, media_temperada_it, media_subida_it)
print(dp_tempera_dst, dp_subida_dst, dp_temperada_it, dp_subida_it)