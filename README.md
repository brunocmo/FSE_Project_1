# Trabalho 1 - 2022/1

Trabalho 1 da disciplina de Fundamentos de Sistemas Embarcados (2022/1)

[Link repositório](https://gitlab.com/fse_fga/trabalhos-2022_1/trabalho-1-2022-1)

***

## Aluno
|Matrícula | Aluno |
| -- | -- |
| 18/0117548  |  [Bruno Carmo Nunes](https://github.com/brunocmo) |

## Requisitos

É necessário o *git*, *make*, e *gpp* instalados.

Tem o uso das bibliotecas instalados na Raspberry Pi: *wiringPi.h*.

***
## Instalação 

Caso esteja rodando o servidor na rasp43, não é necessário modificar os arquivos,
rodarRasp43.sh e rodarRasp44.sh. Porém, caso necessite rodar a aplicação em diferentes
endereços de IP, modificar os endereços contidos nesses arquivos, selecionando então o
endereço de IP do servidor atual. 

Para compilar o programa use o comando abaxio para todas as raspberrys:

`make`

Para executar o programa são seguido três passos (nessa ordem):

- Executando primeiramente o servidor:

`make server`

- Executar na primeira raspberry o script:

`./rodarRasp43.sh`


- Executar na segunda raspberry o script:

`./rodarRasp44.sh`


Para limpar os arquivos .o e prog(executável):

`make clean`

***
## Uso

Ao iniciar o programa é possível ver duas opções, onde todas são usado valores numéricos:

* A primeira você vai no modo terminal para visualizar os valores de tráfego dos semáforos, onde são atualizados a cada 2 segundos. Podendo então voltar ao menu, se 
apertar a tecla CTRL-C.

* A segunda você pode escolher as funções do semáforo, onde são o modo noturno,
modo emergência, e o modo normal. Após selecionados, o programa volta para o menu
principal.

## Experimentos

1. Visualização do 4 cruzamentos

    * Figura mostrando no CLI :

        ![Potenciometro1](/doc/FSETRABALHO1.png)

    * Figura mostrando o semáforo :

        ![Potenciometro12](/doc/FSETRABALHO1_2.png)

***
