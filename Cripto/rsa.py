
import codigo

def algoritmo_estendido_euclideano(a,b):
  x_antigo = y_novo = 1
  x_novo = y_antigo = 0
  Dividendo, Divisor = a, b
  while Divisor != 0:
    #Quociente, Resto = Dividendo//Divisor, Dividendo%Divisor
    Quociente, Resto = divmod(Dividendo, Divisor)
    x_antigo, x_novo = x_novo, x_antigo - x_novo*Quociente
    y_antigo, y_novo = y_novo, y_antigo - y_novo*Quociente
    Dividendo, Divisor = Divisor, Resto
  if Dividendo >= 0:
    return Dividendo, x_antigo, y_antigo
  return -Dividendo, -x_antigo, -y_antigo

def modinv(e, phi):
      
    mdc, x, y = algoritmo_estendido_euclideano(e, phi)
    return x % phi

def parte_ímpar(m):
  """Retorna k,q com q ímpar tal que m = 2**k * q"""
  k = 0
  q = m
  while q%2 == 0:
    k += 1
    q //= 2
  return k,q

def teste_Miller_Rabin(n,b):
  assert n%2 == 1, "n deve ser ímpar na entrada! (╯°□°)╯︵ ʞooqǝɔɐℲ "
  k, q = parte_ímpar(n-1)
  
  x = pow(b, q, n) # calcula a ***forma reduzida*** de b^q mod n
  # x está na faixa 0, 1, ..., n-1
  if x == 1 or x == n-1:
    return "teste inconclusivo"
  # else implícito
  contador = 0
  while True:
    x = pow(x,2,n)
    contador += 1
    if x == 1:
      return "composto"
    if contador == k:
      return "composto"
    if x == n-1:
      return "teste inconclusivo"

from random import randrange
def gerar_primos(n):
    sorteados = []
    while(True):
        vezes = 10
        sorteado = randrange(10**n + 1, 10**(n+2), 2)
        composto = False
        for _ in range(vezes):
            base_sorteada = randrange(2, sorteado-1)
            while(True):
                if base_sorteada in sorteados:
                    base_sorteada = randrange(2, sorteado-1)
                    continue 
                else: 
                    sorteados.append(base_sorteada)
                    break
            if teste_Miller_Rabin(sorteado, base_sorteada) == 'composto':
                composto = True
        if(composto == False):
            return sorteado     

def testa_primo(n):
    vezes = 10
    composto = False
    for _ in range(vezes):
        base_sorteada = randrange(2, n-1)
        if teste_Miller_Rabin(n, base_sorteada) == 'composto':
            composto = True
    if(composto == False):
        return True
    return False

def inverter(e,mod):
    while(True):
        if(mod%e == 0):
            e = e+1
            continue
        else:
            mdc,d, _ =  algoritmo_estendido_euclideano(e,mod)
            if(d<0):
                e = e+1
                continue
            if(e%2==0 or testa_primo(e)==False):
                e = e+1
                continue
        break
    return e,d

def gera_chave():
    p = gerar_primos(75)
    while(True):#Aquela probabilidade de cair um raio na minha cabeça, dificil mas nao impossível.
        q = gerar_primos(75)
        if(p != q):
            break
    phi = (p-1)*(q-1)
    e,d = inverter(3,phi)
    return p,q, p*q,phi,e,d

def encriptar(texto, n, e):
    lista = list(texto)
    for i in range(len(texto)):
        lista[i] = codigo.símbolos_para_códigos[texto[i]]
    texto = ''.join(map(str,lista))
    txt = ''
    blocos = []

    for i in range(len(texto)):
        if(int(txt + texto[i])<n):
            txt = txt + texto[i]
        else:
            blocos.append(txt)
            txt = texto[i]
    if(len(blocos)!=0):
        if(txt != blocos[-1]):
            blocos.append(txt)
    else:
        blocos.append(txt)
    blocos_lista = []
    for i in range(len(blocos)):
        blocos_lista.append(pow(int(blocos[i]), e,n))
    return blocos_lista

def descriptar(blocos,n,d):
    descriptado = []
    for i in range(len(blocos)):
        descriptado.append(pow(blocos[i], d,n))
    descriptado_str = ''.join(map(str, descriptado))
    txt = ''
    txt_final = ''
    for i in range(len(descriptado_str)):
        txt = str(txt + descriptado_str[i])
        if(int(i+1) % 3 ==0):
           txt_final = txt_final+ codigo.códigos_para_símbolos[int(txt)]
           txt=''


    return txt_final

def gera_chave_crt():
    p = gerar_primos(150)
    while(True):#Aquela probabilidade de cair um raio na minha cabeça, dificil mas nao impossível.
        q = gerar_primos(150)
        if(p != q):
            break
    phi = (p-1)*(q-1)
    e,d = inverter(3,phi)
    inverso_p = modinv(p,q)
    inverso_q = modinv(q,p)
    d_reduzido_p = pow(d,1,p-1)
    d_reduzido_q = pow(d,1,q-1)
    return p,q, p*q,phi,e,d,inverso_p,inverso_q,d_reduzido_p,d_reduzido_q

def descriptar_crt(blocos,p,q,d_reduzido_p,d_reduzido_q,inverso_p,inverso_q):
    descriptado = []
    for i in range(len(blocos)):
        dc1 = pow(blocos[i], d_reduzido_p, p)
        dc2 = pow(blocos[i], d_reduzido_q, q)
        d = dc1*q*inverso_q + dc2*p*inverso_p
        d = pow(d,1,p*q)
        descriptado.append(d)
    descriptado_str = ''.join(map(str, descriptado))
    txt = ''
    txt_final = ''
    for i in range(len(descriptado_str)):
        txt = str(txt + descriptado_str[i])
        if(int(i+1) % 3 ==0):
           txt_final = txt_final+ codigo.códigos_para_símbolos[int(txt)]
           txt=''


    return txt_final