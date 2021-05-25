# Airline Management System 

## Introdução

O sistema de linhas aéreas é um dos mais complexos hoje no mundo e de fundamental importância para a economia mundial. Como consequência dessa complexidade, surgem problemáticas de forma exponencial e para acompanhar esse crescimento diversas soluções de software foram criadas. Tendo isso em vista, para esse projeto foi decidido apresentar uma solução para algumas das problemáticas relacionadas a esse área.

## Visão geral

A ideia do projeto é oferecer uma forma,acessível e consistente, de gerenciar os dados essenciais para a operação de linhas aéreas. Dentre essas informações estão, os estados de aeroportos em um determinado momento, como as condições climáticas e aeronáves atualmente localizadas nele. 

Algumas outras funcionalidades são:
- Informar qual o menor caminho dentro da rede de aeroportos para chegar em uma determinada localização. 
- Listar informações sobre os diferentes conceitos abstraídos na aplicação, filtrando por campos.

## Estruturas Iniciais

OBSERVAÇÃO: provável que sejam adicionadas mais no futuro, ou retiradas.

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
| connections           | lista ligada de _Airport_     | outros aeroportos que se pode ir a partir do atual        |

<br/>

## WetherCondition
---
<br/>
Struct para representar a condição do tempo.

Fields: 

| nome                  | tipo      | descrição                                        |
| -------------         | ----------| ---                                              |
| condition             | string    | condição do tempo                                |
| lastTimeChecked       | timestamp | ultima vez que foi checado as condicoes de tempo |

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

_obs: na verdade acabaria sendo uma lista adjacente já que cada aeroporto tem uma lista de outros aeroportos com que ele se conecta._

_Através dessa lista adjacente será possível desenvolver as funcionalidades que envolvem operações de busca em grafos_

Fields:

- Lista ligada que armazena o tipo _Airport_

<br/>

## Plane
---
 
<br/>
Fields:

| nome                  | tipo                          | descrição                         |
| -------------         | -----------                   | ---                               |
|   model               | enum _Models_                 | modelo da aeronave                |
|   airlineCompany      | _AirlineCompany_              | companhia aerea dona da aeronave  |
|   capacity            | int                           | numero maximo de passageiros      |

<br/>

## AirlineCompany
---
Fields: 

| nome                  | tipo                          | descrição              |
| -------------         | -----------                   | ---                    |
|   id                  | long int                      | identificador          |
|   name                | string                        | nome da companhia aerea|
|   country             | string                        | pais da companhia      |

<br/>

## Histórico de versões do documento

| Responsável           | Descrição                                     | Data         |
| -------------         | -----------                                   | ---          |
| Vinicius M Miranda    | Primeira versão do documento                  | 04/03/2021   |
| Vinicius M Miranda    | adicionando fields e structs que faltaram     | 19/03/2021   |
| Victor Eduardo I M    | ajustando campos de structs                   | 25/05/2021   |



