# Airline Management System 

## Introdução

O sistema de linhas aéreas é um dos mais complexos hoje no mundo e de fundamental importância para a economia mundial. Como consequência dessa complexidade, surgem problemáticas de forma exponencial e para acompanhar esse crescimento diversas soluções de software foram criadas. Tendo isso em vista, para esse projeto foi decidido apresentar uma solução para algumas das problemáticas relacionadas a esse área.

## Visão geral

A ideia do projeto é oferecer uma forma,acessível e consistente, de gerenciar os dados essenciais para a operação de linhas aéreas. Dentre essas informações estão, os estados de aeroportos em um determinado momento, como as condições climáticas e aeronáves atualmente localizadas nele. 

Algumas outras funcionalidades são:
- Informar qual o menor caminho dentro da rede de aeroportos para chegar em uma determinada localização. 
- Listar informações sobre os diferentes conceitos abstraídos na aplicação, filtrando por campos.

## Estruturas Iniciais

OBSERVAÇÃO: provável que sejam adicionadas mais no futuro.

## Airport
---
<br/>
Struct para representar um aeroporto.

Fields:

| nome                  | tipo                          | descrição                                                 |
| -------------         | -----------                   | ---                                                       |
| id                    | long int                      | numero de identificação do aeroporto                      |
| name                  | string                        | nome de completo  do aeroporto                            |
| code                  | string                        | código de identificação                                   |
| wether_condition      | WetherCondition               | condição do tempo no momento                              |
| location              | Location                      | localização geografica do aeroporto                       |
| planes                | Lista ligada de _Planes_      | aeronaves localizadas nesse aeroporto no exato momento    |

<br/>

## WetherCondition
---
<br/>
Struct para representar a condição do tempo.

Fields: 

| nome                  | tipo      | descrição         |
| -------------         | ----------| ---               |
| condition             | string    | condição do tempo |
| lastTimeChecked       | string    |                   |

NOTE:  


<br/>

## Location
---
<br/>
Fields: 

| nome                  | tipo                          | descrição                             |
| -------------         | -----------                   | ---                                   |
| city                  | string                        | cidade em que se localiza o aeroporto |
| country               | string                        | país em que se localiza o aeroporto   |

<br/>

## Airports 
---
<br/>
Lista ligada para representar conjunto do tipo aeroporto

Fields:

- Lista ligada que armazena o tipo _Airport_


<br/>

## Connection
---
<br/>
Struct para representar a conexão entre dois aeroportos.

Fields:

| nome                  | tipo                          | descrição                             |
| -------------         | -----------                   | ---                                   |
| city                  | string                        | cidade em que se localiza o aeroporto |
| country               | string                        | país em que se localiza o aeroporto   |


<br/>

## Plane
---
<br/>
Fields:

| Responsável           | Descrição                     |  Data             |
| -------------         | -----------                   | ---               |
| Vinicius M Miranda    | Primeira versão do documento  | 04/03/2021        |


<br/>

## AirlineCompany
---
Fields: 

| Responsável           | Descrição                     |  Data             |
| -------------         | -----------                   | ---               |
| Vinicius M Miranda    | Primeira versão do documento  | 04/03/2021        |

<br/>

## Histórico de versões do documento

| Responsável           | Descrição                     |  Data             |
| -------------         | -----------                   | ---               |
| Vinicius M Miranda    | Primeira versão do documento  | 04/03/2021        |



