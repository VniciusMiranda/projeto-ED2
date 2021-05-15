# Airline Management System 

### Introdução

O sistema de linhas aéreas é um dos mais complexos hoje no mundo e de fundamental importância para a economia mundial. Como consequência dessa complexidade, surgem problemáticas de forma exponencial e para acompanhar esse crescimento diversas soluções de software foram criadas. Tendo isso em vista, para esse projeto foi decidido apresentar uma solução simplista para algumas das problemáticas relacionadas a esse área.

### Visão geral

Este projeto objetiva oferecer a um usuário administrador de linhas aéreas uma forma de organizar e gerenciar dados sobre as operações de voos em aeroportos, podendo ser considerados alguns fatores como clima, rotas e posição.

### Descrição do projeto

A estrutura e organização do projeto será a seguinte:

* O projeto será composto de estruturas de dados como listas dinâmicas para guardar e ordenar os dados específicos para os aeroportos, aviões, etc.
* Para cada estrutura será implementado diversas funcionalidades como inserção, remoção, visualização e ordenação dos dados.
* A ordenação dos dados será feita de forma interna e externa utilizando variados tipos de métodos de ordenação dependendo de cada caso.
* Os dados serão guardados em arquivos e será implementado funcionalidades de um banco de dados.
* Será utilizado grafos para cálculo de rotas.
* Para dados sobre o clima, o usuário irá inserir no algoritmo ou poderá ser inserido dinamicamente através de uma API.
* A interface gráfica do programa será construída com ncurses.
* O projeto será organizado através do MakeFile. 

OBS: A implementação de grafos, UI e da API para o clima NÃO é prioridade e poderá ou não ser implementado.

#### Principais funcionalidades para o usuário

* Cadastrar Dados;
* Excluir Dados;
  - O usuário poderá inserir e remover dados sobre avião, aeroporto e outras objetos.
* Visualizar;
   - Dentro da opção visualizar o usuário poderá ordernar como desejar os dados mostrados.

### Depêndencias

- [curllib](https://curl.se/libcurl/c/)
- [ncurses](https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/)


### Como compilar e rodar

Obs: o projeto e apenas compativel com linux OS e o compilador usado foi GCC.

#### Instalar depêndencias

Para debian/ubuntu, rode no terminal:
```
sudo apt install curl libcurl4-openssl-dev libncurses5-dev libncursesw5-dev 
```

Dentro do  diretório *project* siga as seguintes instruções:

Crie os diretórios "executable" e "obj":

```
mkdir executable/ obj/
```

Compile o código usando make:
```
make
```

Agora rode o executável:
```
./executable/project-organizer
```

### Autores

* Victor Eduardo Iscava Moreira
* Vinicius Medeiros Miranda

Alunos de Engenharia de Computação, da Universidade Federal de Goiás.
