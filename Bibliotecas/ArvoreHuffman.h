#ifndef ArvoreHuffman_H
#define ArvoreHuffman_H

#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

struct TNoHuffman {     //Struct do nô da árvore
    int frequencia;     //Contabiliza a quantidade do mesmo caractere
    char caractere;     //Armazena o caractere
    string binario;             //Armazena o binário do caractere
    TNoHuffman* esquerda;       //Aponta para o nô da esquerda
    TNoHuffman* direita;        //Aponta para o Nõ da direita
    TNoHuffman* proximo;        //Aponta para o próximo. (Utilizado apenas na lista de huffman)
};

struct TArvoreHuffman {     //Struct da árvore
    TNoHuffman* raiz;       //Armazena o nô raiz da árvore
};

//INICIALIZA A ARVORE=================================================================================================================================================
void InicializaArvore (TArvoreHuffman &arvore) {
    arvore.raiz = NULL;     //Inicializa a árvore, como nula (vázia)
}

//CRIA NÔS DA ARVORE=================================================================================================================================================
TNoHuffman* CriaNoHuffman (char caractere) { //Função para criar um nô "padrão", como parametro o caractere desejado
    TNoHuffman* novo = new TNoHuffman;      //Cria um novo nô e o instãncia
    novo->frequencia = 0;           //Coloca 0 na variável de frequencia
    novo->caractere = caractere;    //Adiciona o caractere passado por paramêtro
    novo->esquerda = NULL;          //Aponta para o nada (vázio)
    novo->direita = NULL;           //Aponta para o nada (vázio)
    novo->proximo = NULL;           //Aponta para o nada (vázio)

    return novo;    //Retorna o nô criado
}



//INICIO DE CODIGOS UTILIZADOS NA LISTA DE HUFFMAN---------------------------------------------------------------------------------------------------------------------

//INSERE NO INICIO DA LISTA DE HUFFMAN=================================================================================================================================================
void InserirInListaHuff (TArvoreHuffman &lista, TNoHuffman* novo) {     //Função para inserir no inicio da lista, os parametros são a lista e um nô
    if (lista.raiz == NULL) {       //Verifica se a lista está vázia
        lista.raiz = novo;      //Seta a raiz como o nô "novo"
    } else {        //Se não estiver vázia
        novo->proximo = lista.raiz;     //Aponta o proximo do nô para a "raiz" da lista
        lista.raiz = novo;      //Seta a "raiz" da lista como o nô novo
    }
}

//INSERE EM QUALQUER POSICAO DA LISTA DE HUFFMAN=================================================================================================================================================
void InserirListaHuff (TArvoreHuffman &lista, TNoHuffman* novo) {   //Função para inserir na lista, os parametros são a lista e um nó
    if (lista.raiz == NULL) {   //Verifica se a lista está vázia
        InserirInListaHuff(lista, novo);    //Chama a função de inserir no ínicio da lista
    } else {                                //Se não estiver vázia
        if (novo->frequencia < lista.raiz->frequencia) {   //Se a frequencia do nó novo, for menor ou igual a "raiz" da lista
            InserirInListaHuff(lista, novo);                //Chama a função de inserir no ínicio da lista
        } else {                                            //Se não for menor ou igual
            TNoHuffman* posicao = NULL;             //Cria um novo nó para descobrir a posição de inserção
            for (TNoHuffman* nav = lista.raiz; nav != NULL; nav = nav->proximo) {       //For para percorrer a lista inteira, utilizando um navegador
                if (novo->frequencia >= nav->frequencia) {          //Se a frequencia do nó novo, for maior ou igual ao do navegador
                    posicao = nav;                                  //O nô posição passa a armazenar a posição do navegador
                }
            }
            novo->proximo = posicao->proximo;           //Aponta o proximo do novo, para o proximo do posição
            posicao->proximo = novo;                    //Aponta o proximo do proximo para o novo

        }
    }
}

//REMOVE DO INICIO DA LISTA DE HUFFMAN=================================================================================================================================================
TNoHuffman* RemoverListaHuff (TArvoreHuffman &lista) {      //Função para remover do inicio da lista, parametro a lista
    if (lista.raiz == NULL) {           //Se a lista estiver vázia
        throw "Stack Underflow!!";      //A execução para e retorna o throw
    } else {                            //Se não estiver vázia
        TNoHuffman* remover = lista.raiz;       //Cria um nô gemeo do primeiro elemento da lista
        lista.raiz = lista.raiz->proximo;       //Seta o primeiro elemento da lista como o que era o segundo
        return remover;                         //Retorna o gemeo do antigo primeiro elemento da lista
    }
}

//VERIFICA SE UM CARACTERE EXISTE NA LISTA DE HUFFMAN=================================================================================================================================================
bool PertenceListaHuffman (TArvoreHuffman lista, char caractere) {          //Função para verificar se o caractere existe na lista
    for (TNoHuffman* nav = lista.raiz; nav != NULL; nav = nav->proximo) {   //For para percorrer a lista inteira, utilizando um navegador
        if (nav->caractere == caractere) {                                  //Se o caractere do navegador for igual ao caractere passado por paramêtro
            return true;                                                    //Retorna verdadeiro
        }
    }
    return false;           //Após percorrer a lista inteira sem retornar nada, retorna falso
}

//IMPRIME A LISTA DE HUFFMAN=================================================================================================================================================
void ImprimirListaHuff (TArvoreHuffman lista) {             //Imprime a lista
    cout << "=================== IMPRIMINDO LISTA HUFFMAN ===================" << endl;
    cout << "Comeca em: " << lista.raiz << endl;            //Imprime o endereço do primeiro elemento da lista.
    int i = 0;                                              //Utilizado para demonstrar a posição do "Array"
    for (TNoHuffman* nav = lista.raiz; nav != NULL; nav = nav->proximo) {       //For para percorrer a lista inteira, utilizando um navegador
        cout << "Item [" << i++ << "]: " << nav << endl                         //Imprime a posição do "Array"
             << "Frequencia: " << nav->frequencia << endl                       //Imprime a frequencia do elemento
             << "Caractere: " << nav->caractere << endl                         //Imprime o caractere do elemento
             << "Proximo: " << nav->proximo << endl << endl;                    //Imprime o endereço do proximo elemento
    }
}
//FIM DE CODIGOS UTILIZADOS NA LISTA DE HUFFMAN---------------------------------------------------------------------------------------------------------------------


//INÍCIO DE CÓDIGOS UTILIZADOS NA CODIFICAÇÃO DA ÁRVORE DE HUFFMAN---------------------------------------------------------------------------------------------------------------------

//FORMA A ÁRVORE DE HUFFMAN=================================================================================================================================================
void FormarArvoreHuff (TArvoreHuffman &arvore) {    //Função para organizar a lista e formar a árvore
    if (arvore.raiz == NULL) {              //Se a lista estiver vázia
        throw "A arvore esta vazia!!";      //A execução para e retorna o throw
    } else {                                //Se a lista não estiver vázia
        while (arvore.raiz->proximo != NULL) {          //Repete o código dentro dos colchetes, enquanto não estiver apenas um elemento na lista
            TNoHuffman* novo = CriaNoHuffman(NULL);     //Cria um nô com o caractere vázio
            novo->esquerda = RemoverListaHuff(arvore);      //Remove o primeiro elemento da lista e aponta o nô do novo da esquerda para ele
            novo->direita = RemoverListaHuff(arvore);       //Remove o primeiro elemento da lista e aponta o nô do novo da direita para ele
            novo->frequencia = novo->esquerda->frequencia + novo->direita->frequencia;      //Soma a frequencia da esquerda e direira na frequencia do novo
            InserirListaHuff(arvore, novo);                     //Insere o nô novo na lista
        }
    }
}

//DESCOBRE A SEQUENCIA DE BINARIOS DE CADA CARACTERE PRESENTE NA ARVORE=================================================================================================================================================
void DescobreBinario (TNoHuffman *no, string binario) { 
    if (no == NULL) {       //Se o nô for nulo, então ele finaliza a função recursiva.
        return;             //Finaliza a função.
    }

    if (!no->esquerda && !no->direita) {        //Se os nôs dos dois lados forem nulos
        no->binario = binario;                  //Transfere o binario da string para o caractere achado com aquele caminho.
    }

    DescobreBinario (no->esquerda, binario + "0");      //Entra em recursividade com todos os nôs da esquerda e acrecenta "0" na string binario
    DescobreBinario (no->direita, binario + "1");       //Entra em recursividade com todos os nôs da direita e acrecenta "1" na string binario
}

//ACHA O CARACTERE DO TEXTO E IMPRIME SUA SEQUENCIA BINÁRIA=================================================================================================================================================
void Escreve_ContaBinario (TNoHuffman *no, char caractere, double &tamanho) {
    if (no != NULL) {                       //se o nó não for nulo
        if (no->caractere == caractere) {   //Caso o caractere armazenado no nó seja igual ao caractere passado por parametro
            cout << no->binario;                //imprime a sequência de binário do nó
            tamanho += no->binario.length();    //Conta a quantidade de binários
        }

        Escreve_ContaBinario(no->esquerda, caractere, tamanho);     //Entra em recursividade com todos os nôs da esquerda.
        Escreve_ContaBinario(no->direita, caractere, tamanho);      //Entra em recursividade com todos os nôs da direita.
    }
}


//IMPRIME A ARVORE EM ORDEM PRE-FIXA=================================================================================================================================================
void ImprimePreFixa (TNoHuffman* no) {
    if (no != NULL) {       //Se o nô não for nulo
        switch (no->caractere) {        //Verifica se o caractere do nô é algum dos citados nos cases
            case ' ':                   //Caso o caractere seja espaço
                cout << "\nCaractere: SPACE" << " | Frequencia: " << no->frequencia;      //Imprime "SPACE"
                break;
            case '\n':                  //Caso o caractere seja quebra de linha
                cout << "\nCaractere: NEW LINE" << " | Frequencia: " << no->frequencia;   //Imprime "NEW LINE"
                break;
            case NULL:                  //Caso o caractere seja nulo
                cout << "\nNULL" << " | Frequencia: " << no->frequencia;       //Imprime "NULL"
                break;
            default:                    //Caso o caractere não seja nenhum dos citados acima
                cout << endl << "Caractere: " << no->caractere << " | Frequencia: " << no->frequencia;      //Imprime o caractere
                break;
        }
        ImprimePreFixa(no->esquerda);      //Chama a função recursiva, passando por parametro todos os nôs que estão na esquerda
        ImprimePreFixa(no->direita);       //Chama a função recursiva, passando por parametro todos os nôs que estão na direita
    }
}

//IMPRIME A TABELA COM O CARACTERE, CODIGO BINARIO E A FREQUENCIA=================================================================================================================================================
void ImprimeTabela (TNoHuffman* no) {
    if (no != NULL) {       //Se o nô não for nulo
        switch (no->caractere) {        //Verifica se o caractere do nô é algum dos citados nos cases
            case ' ':                   //Caso o caractere seja espaço
                cout << "\nCaractere: SPACE" << " | Codigo: " << no->binario << " | Frequencia: " << no->frequencia;      //Imprime "SPACE"
                break;
            case '\n':                  //Caso o caractere seja quebra de linha
                cout << "\nCaractere: NEW LINE" << " | Codigo: " << no->binario << " | Frequencia: " << no->frequencia;   //Imprime "NEW LINE"
                break;
            case NULL:                  //Caso o caractere seja nulo
                break;
            default:                    //Caso o caractere não seja nenhum dos citados acima
                cout << endl << "Caractere: " << no->caractere << " | Codigo: " << no->binario << " | Frequencia: " << no->frequencia;      //Imprime o caractere
                break;
        }
        ImprimeTabela(no->esquerda);      //Chama a função recursiva, passando por parametro todos os nôs que estão na esquerda
        ImprimeTabela(no->direita);       //Chama a função recursiva, passando por parametro todos os nôs que estão na direita
    }
}

//FIM DE CODIGOS UTILIZADOS NA CODIFICAÇÃO DA ÁRVORE DE HUFFMAN---------------------------------------------------------------------------------------------------------------------


//INÍCIO DE CÓDIGOS UTILIZADOS NA DECODIFICAÇÃO DA ÁRVORE DE HUFFMAN---------------------------------------------------------------------------------------------------------------------

//FUNÇÃO PARA DECODIFICAR UM CÓDIGO GERADO POR TEXTO=================================================================================================================================================
void Decodificacao (TArvoreHuffman &arvore) {
    ifstream arquivoTexto;              //váriavel usada para armazenar o texto.
    char caractere;                     //váriavel usada para armazenar temporarimente o caractere do texto.
    TNoHuffman* nav = arvore.raiz;      //navegador para navegar pela árvore

    arquivoTexto.open("Bibliotecas\\Codigo em Huffman (Codificacao).txt");      //Abre o arquivo desejado e armazena dentro da váriavel "arquivoTexto".

    while (arquivoTexto.get(caractere)) {           //Enquanto ainda tiver caractere dentro do texto a função get pega um por um e armazena dentro da váriavel caractere.
        if (!nav->esquerda && !nav->direita) {      //Se os nós da esquerda e direita forem nulos
            cout << nav->caractere;                 //Imprime o caractere do nó;
            nav = arvore.raiz;                      //retorna o navegador para o nó raiz.
        }
        
        if (caractere == '0') {                 //Caso o caractere for 0
            nav = nav->esquerda;                //Anda com o navegador para o ponteiro da esquerda
        } 
        if (caractere == '1') {                 //Caso o caractere for 1
            nav = nav->direita;                 //Anda com o navegador para o ponteiro da direita
        }
    }
    cout << nav->caractere;                     //Imprime o ultimo caractere do texto
    cout << endl;

    arquivoTexto.close();                        //Libera a váriavel para ser inserida novamente.
}

//FUNÇÃO PARA DECODIFICAR UM CÓDIGO GERADO POR TABELA=================================================================================================================================================
void DecodificacaoArvoreBinaria (TArvoreHuffman &arvore) {
    ifstream arquivoTexto;              //váriavel usada para armazenar o texto.
    char caractere;                     //váriavel usada para armazenar temporarimente o caractere do texto.
    TNoHuffman* nav = arvore.raiz;      //navegador para navegar pela árvore

    arquivoTexto.open("Bibliotecas\\Codigo em Huffman (Codificacao).txt");      //Abre o arquivo desejado e armazena dentro da váriavel "arquivoTexto".

    while (arquivoTexto.get(caractere)) {           //Enquanto ainda tiver caractere dentro do texto a função get pega um por um e armazena dentro da váriavel caractere.
        if (!nav->esquerda && !nav->direita) {      //Se os nós da esquerda e direita forem nulos
            cout << nav->caractere;                 //Imprime o caractere do nó;
            nav = arvore.raiz;                      //retorna o navegador para o nó raiz.
            nav->frequencia++;                      //Soma a frequência do nó mais 1.
        }
        
        if (caractere == '0') {                 //Caso o caractere for 0
            nav = nav->esquerda;                //Anda com o navegador para o ponteiro da esquerda
            nav->frequencia++;                      //Soma a frequência do nó mais 1.
        } 
        if (caractere == '1') {                 //Caso o caractere for 1
            nav = nav->direita;                 //Anda com o navegador para o ponteiro da direita
            nav->frequencia++;                      //Soma a frequência do nó mais 1.
        }
    }
    cout << nav->caractere;                     //Imprime o ultimo caractere do texto
    cout << endl;

    arquivoTexto.close();                        //Libera a váriavel para ser inserida novamente.
}

//FUNÇÃO PARA CRIAR UMA ÁRVORE COM A TABELA=================================================================================================================================================
void FormaArvoreBinaria (TArvoreHuffman &arvore) {
    ifstream arquivoTexto;          //váriavel usada para armazenar o texto.
    char caractere;                 //váriavel usada para armazenar temporarimente o caractere do texto.
    bool pegaChar = true;           //variavel de controle para pegar o caractere certo.
    string binario = "";            //string para armazenar o caminho em binário do caractere.
    char c;                         //váriavel usada para percorrer o texto.
    arvore.raiz = CriaNoHuffman(NULL);          //Cria um nó para a raiz da árvore
    TNoHuffman* nav = arvore.raiz;              //navegador para navegar pela árvore

    arquivoTexto.open("Bibliotecas\\Codificacao da Tabela sem Frequencia.txt");     //Abre o arquivo desejado e armazena dentro da váriavel "arquivoTexto".

    while (arquivoTexto.get(c)) {           //Enquanto ainda tiver caractere dentro do texto a função get pega um por um e armazena dentro da váriavel caractere.
        if (pegaChar == true) {             //se a váriavel de controle for verdadeira
            caractere = c;                  //armazena dentro da váriavel o caractere.
            pegaChar = false;               //seta a váriavel de controle como falsa
        }
        if (c == '0') {                                 //se o caractere for 0
            if (nav->esquerda == NULL) {                //se o nó da esquerda for nulo
                nav->esquerda = CriaNoHuffman(NULL);    //Instancia um nó a esquerda.
                nav = nav->esquerda;                    //Anda com o navegador para a esquerda.
            } else {                                    //se o nó da esquerda não for nulo 
                nav = nav->esquerda;                    //Anda com o navegador para a esquerda.
            }
            binario += c;                               //armazena o caractere dentro da váriavel
        }
        if (c == '1') {                                 //se o caractere for 1
            if (nav->direita == NULL) {                 //se o nó da direita for nulo
                nav->direita = CriaNoHuffman(NULL);     //Instancia um nó a direita.
                nav = nav->direita;                     //Anda com o navegador para a direita.
            } else {                                    //se o nó da direita não for nulo 
                nav = nav->direita;                     //Anda com o navegador para a direita.
            }
            binario += c;                               //armazena o caractere dentro da váriavel
        }
        if (c == '\n') {                                //se o caractere for uma quebra de linha
            nav->caractere = caractere;                 //armazena o caractere dentro nó
            nav->binario = binario;                     //armazena o caminho em binário dentro do nó
            binario = "";                               //Seta a váriavel como limpa
            nav = arvore.raiz;                          //retorna o navegador para o nó raiz.
            pegaChar = true;                            //Seta a váriavel de controle como true
        }
    }

    arquivoTexto.close();                               //Libera a váriavel para ser inserida novamente.
}


//FIM DE CÓDIGOS UTILIZADOS NA DECODIFICAÇÃO DA ÁRVORE DE HUFFMAN---------------------------------------------------------------------------------------------------------------------


#endif //ArvoreHuffman_H