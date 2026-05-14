CFL CONDITION

bool CFL: cria uma função que recebe c, dt e dx e retorna true ou false.

c -> velocidade da onda no meio
dt -> passo de tempo
dx -> passo espacial

true -> simulação estável
false -> simulação instável

ef -> estability factor

condição de estabilidade: c * dt/dx <= 1 -> número de courant
c * dt -> distância que a onda percorre em um passo temporal
dividir dx -> quantos pontos da malha ela atravessa

if(ef <= 1) -> se o número de courant for <= 1; A solução é estável e retorna TRUE!

se c * dt/dx > 1 -> a simulação explode numericamente

FONTE RICKER:

f0 = frequência dominante
t = vetor de tempo

vetor s -> contém a fonte sísmica ao longo do tempo
int nt = t_size(); -> número total de amostras no tempo e cria o vetor da fonte de tamanho nt

t0 -> define o atraso temporal da wavelet -> desloca o pico principal -> sem isso a fonte começaria no tempo zero de forma não simétrica

for -> nesse caso ele percorre todos os instantes de tempo

OBS.: A fonte é responsavel por injetar energia no modelo.

FUNÇÃO PRINCIPAL (derivates)

-> Resolve numericamente a equação da onda (discretização)

derivates -> propaga a onda, calcula o campo em todos os tempos e retorna o ultimo estado da onda

int is = nx/2 -> fonte ricker no centro -> define a posição da fonte -> será injetada no meio da malha

LOOP TEMPORAL: for -> evolução temporal que calcula a onda no proximo instante em cada iteração

fill(u_next)... -> zera o campo futuro antes do calculo

LOOP ESPACIAL: for -> percorre todos os pontos da malha

injeção da fonte: adiciona energia na malha -> a fonte é somada no centro

if(n % 50 == 0) -> a cada 50 passos é salvo um snapshot

ofstream -> abre o arquivo binário

file.write... -> Grava os floats diretamente em binário

reinterpret_cast -> converte o ponteiro do vetor float para bytes

CAMADA ABSORVENTE

nabs = 50 -> espessura da camada

for -> loops das bordas -> distância normalizada

damp -> fator amortecimento

MAIN

L -> tamanho da simulação

T -> tempo total da simulação

nx -> calcula quantos pontos existem no modelo -> pontos espaciais





