#ifndef ManipulacaoTexto_H
#define ManipulacaoTexto_H

#include <iostream>
#include <iomanip>
#include <fstream>

#include "ArvoreHuffman.h"

using namespace std;

//INICIO DE FUNÇÕES UTILIZADOS PARA DESCOBRIR O TAMANHO DO TEXTO EM ASCII-----------------------------------------------------------------------------------------------------------

//CONTA O TAMANHO DO TEXTO EM ASCII=================================================================================================================================================
int TamanhoTextoASCII() {
    char caractere;         //váriavel usada para armazenar temporarimente o caractere do texto.
    ifstream arquivoTexto;      //váriavel usada para armazenar o texto.
    int tamanho = 0;        //váriavel para armazenar o tamanho do texto ASCII

    arquivoTexto.open("Bibliotecas\\Texto.txt");    //Abre o arquivo desejado e armazena dentro da váriavel "arquivoTexto".

    while (arquivoTexto.get(caractere)) {   //Enquanto ainda tiver caractere dentro do texto a função get pega um por um e armazena dentro da váriavel caractere.
      tamanho += 8;     //formula para calcular o tamanho do ASCII, onde cada caractere possui 8 bits.
    }

    arquivoTexto.close();       //Libera a váriavel para ser inserida novamente.
    return tamanho;         //Retorna o tamanho do texto ASCII em bits.
}

//FIM DE FUNÇÕES UTILIZADOS PARA DESCOBRIR O TAMANHO DO TEXTO EM ASCII-----------------------------------------------------------------------------------------------------------

//INICIO DE FUNÇÕES UTILIZADAS PARA CRIAR A LISTA DE HUFFMAN----------------------------------------------------------------------------------------------------------------------------------------------------------

//VERIFICA SE POSSUI CARACTERE REPITIDO NO TEXTO, SOMANDO A FREQUENCIA=================================================================================================================================================
void VerificaIqualChar (TNoHuffman* novo) {
    char caractere;             //váriavel usada para armazenar temporarimente o caractere do texto.
    ifstream arquivoTexto;      //váriavel usada para armazenar o texto.

    arquivoTexto.open("Bibliotecas\\Texto.txt");        //Abre o arquivo desejado e armazena dentro da váriavel "arquivoTexto".

    while (arquivoTexto.get(caractere)) {           //Enquanto ainda tiver caractere dentro do texto a função get pega um por um e armazena dentro da váriavel caractere.
        if (novo->caractere == caractere) {         //Se o nó do caractere for igual a um caractere do texto
            novo->frequencia++;                 //Soma-se mais 1 na frequencia.
        }
    }

    arquivoTexto.close();       //Libera a váriavel para ser inserida novamente.
}

//SEPARA CADA CARACTERE DO TEXTO E INSERE NA LISTA=================================================================================================================================================
void SeparaChar (TArvoreHuffman &listaHuffman) {
    char caractere;                 //váriavel usada para armazenar temporarimente o caractere do texto.
    ifstream arquivoTexto;          //váriavel usada para armazenar o texto.

    arquivoTexto.open("Bibliotecas\\Texto.txt");    //Abre o arquivo desejado e armazena dentro da váriavel "arquivoTexto".

    while (arquivoTexto.get(caractere)) {   //Enquanto ainda tiver caractere dentro do texto a função get pega um por um e armazena dentro da váriavel caractere.
        if (caractere == '\n') {            //Se for encontrado uma quebra de linha dentro do texto, então aponta um erro para o usuário.
            throw "O arquivo txt nao pode ter quebra de linha!!";       //Erro apontado para o usuário.
        } else {
            TNoHuffman* no = CriaNoHuffman(caractere);      //Cria um nô com o caractere, e os ponteiros apontados para null.
            VerificaIqualChar(no);                          //Conta todos os caracteres iguais que possui dentro do texto.
            if (PertenceListaHuffman(listaHuffman, caractere) == false) {       //Verifica se o caractere já possui na lista.
                InserirListaHuff(listaHuffman, no);             //Se o caractere não possui na lista, então ele é inserido.
            }
        }
    }

    arquivoTexto.close();                   //Libera a váriavel para ser inserida novamente.
}

//FIM DE FUNÇÕES UTILIZADAS PARA CRIAR A LISTA DE HUFFMAN----------------------------------------------------------------------------------------------------------------------------------------------------------

//INICIO DE FUNÇÕES UTILIZADAS PARA GERAR O CODIGO BINÁRIO----------------------------------------------------------------------------------------------------------------------------------------------------------

//SEPARA CARACTERE PARA DESCOBRIR O CODIGO BINÁRIO DELE NA ÁRVORE=================================================================================================================================================
void CriaCodigoHuffmanEConta (TNoHuffman *no, double &tamanho) {
    char caractere;             //váriavel temporária para armazenar o caractere do texto. 
    ifstream arquivoTexto;      //váriavel usada para armazenar o texto.

    arquivoTexto.open("Bibliotecas\\Texto.txt");    //Abre o arquivo desejado e armazena dentro da váriavel "arquivoTexto".

    while (arquivoTexto.get(caractere)) {   //Enquanto ainda tiver caractere dentro do texto a função get pega um por um e armazena dentro da váriavel caractere.
        Escreve_ContaBinario(no, caractere, tamanho);      //função para achar o caractere na árvore e sua posição.
    }
    cout << endl;

    arquivoTexto.close();       //Libera a váriavel para ser inserida novamente.
}

//FIM DE FUNÇÕES UTILIZADAS PARA GERAR O CODIGO BINÁRIO----------------------------------------------------------------------------------------------------------------------------------------------------------


//INICIO DE FUNÇÕES UTILIZADAS PARA ESCREVER EM ARQUIVOS TXT----------------------------------------------------------------------------------------------------------------------------------------------------------

//ESCREVE A TABELA DA ÁRVORE EM ARQUIVO TXT, TANTO COM FREQUENCIA, COMO SEM=================================================================================================================================================
void EscreveTabelaTXT (TNoHuffman* no, ofstream &arquivoTexto, bool diferenciador) {
    if (no != NULL) {       //Se o nô não for nulo
        if (diferenciador == false) {
            switch (no->caractere) {        //Verifica se o caractere do nô é algum dos citados nos cases
                case ' ':                   //Caso o caractere seja espaço
                    arquivoTexto << "Caractere: SPACE" << " | Codigo: " << no->binario << " | Frequencia: " << no->frequencia << endl;      //Imprime "SPACE"
                    break;
                case '\n':                  //Caso o caractere seja quebra de linha
                    arquivoTexto << "Caractere: NEW LINE" << " | Codigo: " << no->binario << " | Frequencia: " << no->frequencia << endl;   //Imprime "NEW LINE"
                    break;
                case NULL:                  //Caso o caractere seja nulo
                    break;
                default:                    //Caso o caractere não seja nenhum dos citados acima
                    arquivoTexto << "Caractere: " << no->caractere << " | Codigo: " << no->binario << " | Frequencia: " << no->frequencia << endl;      //Imprime o caractere
                    break;
            }
        }
        if (diferenciador == true) {
            switch (no->caractere) {        //Verifica se o caractere do nô é algum dos citados nos cases
                case NULL:                  //Caso o caractere seja nulo
                    break;
                default:                    //Caso o caractere não seja null
                    arquivoTexto <<  no->caractere << ":" << no->binario << endl;      //Imprime o caractere
                    break;
            }
        }
        EscreveTabelaTXT(no->esquerda, arquivoTexto, diferenciador);      //Chama a função recursiva, passando por parametro todos os nôs que estão na esquerda
        EscreveTabelaTXT(no->direita, arquivoTexto, diferenciador);       //Chama a função recursiva, passando por parametro todos os nôs que estão na direita
    }
}

//FUNÇÃO RECURSIVA PARA PEGAR O BINÁRIO DE CADA CARACTERE=================================================================================================================================================
void RecursivaCodigoHuffmanTXT (TNoHuffman *no, char caractere, ofstream &arquivoTextoOut) {
    if (no != NULL) {               //se o nó for diferente de nulo
        if (no->caractere == caractere) {       //se o caractere for igual ao caractere do nó
            arquivoTextoOut << no->binario;     //escreve no arquivo txt o binário do nó.
        }

        RecursivaCodigoHuffmanTXT(no->esquerda, caractere, arquivoTextoOut);        //Chama a função recursiva, passando por parametro todos os nôs que estão na esquerda
        RecursivaCodigoHuffmanTXT(no->direita, caractere, arquivoTextoOut);         //Chama a função recursiva, passando por parametro todos os nôs que estão na direita
    }
}

//FUNÇÃO PARA ESCREVER O CODIGO HUFFMAN EM UM TXT=================================================================================================================================================
void EscreveCodigoHuffmanTXT (TNoHuffman *no, ofstream &arquivoTextoOut) {
    char caractere;             //váriavel usada para armazenar temporarimente o caractere do texto.
    ifstream arquivoTextoIn;    //váriavel usada para armazenar o txt.

    arquivoTextoIn.open("Bibliotecas\\Texto.txt");      //Abre o arquivo desejado e armazena dentro da váriavel "arquivoTexto".

    while (arquivoTextoIn.get(caractere)) {         //Enquanto ainda tiver caractere dentro do texto a função get pega um por um e armazena dentro da váriavel caractere.
        RecursivaCodigoHuffmanTXT(no, caractere, arquivoTextoOut);      //chama a função recursiva para percorrer toda a árvore e escrever o binário
    }
    cout << endl;

    arquivoTextoIn.close();     //Libera a váriavel para ser inserida novamente.
}


//FUNÇÃO PRINCIPAL QUE CHAMA TODAS AS OUTRAS, ESCREVE NOS TXTS OS DADOS=================================================================================================================================================
void EscreveCodificacaoTXT (TArvoreHuffman &arvore) {
    ofstream codigoHuffman;         //váriavel usada para escrever no txt.
    ofstream codificacaoFreq;       //váriavel usada para escrever no txt.
    ofstream tabelaDecode;          //váriavel usada para escrever no txt.

    codificacaoFreq.open("Bibliotecas\\Codificao da Tabela com Frequencia.txt");        //Abre o arquivo txt descrito no open() na váriavel
    codigoHuffman.open("Bibliotecas\\Codigo em Huffman (Codificacao).txt");             //Abre o arquivo txt descrito no open() na váriavel
    tabelaDecode.open("Bibliotecas\\Codificacao da Tabela sem Frequencia.txt");         //Abre o arquivo txt descrito no open() na váriavel

    codificacaoFreq << "TABELA DE SÍMBOLOS:" << endl;                   //escreve no txt aberto na váriavel codificacaoFreq a frase em aspas.
    EscreveTabelaTXT(arvore.raiz, codificacaoFreq, false);              //Chama função para escrever na váriavel codificacaoFreq.
    EscreveTabelaTXT(arvore.raiz, tabelaDecode, true);                  //Chama função para escrever na váriavel tabelaDecode.
    codificacaoFreq << endl << "CODIFICAÇÃO DE HUFFMAN:" << endl;       //escreve no txt aberto na váriavel codificacaoFreq a frase em aspas.
    EscreveCodigoHuffmanTXT(arvore.raiz, codificacaoFreq);              //Chama função para escrever na váriavel codificacaoFreq.
    EscreveCodigoHuffmanTXT(arvore.raiz, codigoHuffman);                //Chama função para escrever na váriavel codigoHuffman.

    codificacaoFreq.close();            //Libera a váriavel para ser inserida novamente.
    codigoHuffman.close();              //Libera a váriavel para ser inserida novamente.
    tabelaDecode.close();               //Libera a váriavel para ser inserida novamente.
}

//FIM DE FUNÇÕES UTILIZADAS PARA ESCREVER EM ARQUIVOS TXT----------------------------------------------------------------------------------------------------------------------------------------------------------

#endif //ManipulacaoTexto_H
