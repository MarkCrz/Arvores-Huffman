#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include "Bibliotecas\ArvoreHuffman.h"
#include "Bibliotecas\ManipulacaoTexto.h"

using namespace std;

int main () {
    TArvoreHuffman huffman;
    TArvoreHuffman huffmanDecode;
    string binario;
    double tamanhoHuffman = 0;
    double tamanhoASCII = 0;
    

    try {
        InicializaArvore(huffman);
        InicializaArvore(huffmanDecode);

        SeparaChar(huffman);
        FormarArvoreHuff(huffman);
        DescobreBinario(huffman.raiz, binario);

        cout << endl << "================CODIFICACAO================" << endl;
        cout << endl << "---------------Arvore de Huffman---------------";
        ImprimePreFixa(huffman.raiz);

        cout << endl << endl << "---------------Tabela de Codigo---------------";
        ImprimeTabela(huffman.raiz);

        cout << endl << endl << "---------------Codigo Binario---------------" << endl;
        CriaCodigoHuffmanEConta (huffman.raiz, tamanhoHuffman);

        cout << endl << "---------------Tamanhos dos texto---------------" << endl;
        tamanhoASCII = TamanhoTextoASCII();
        cout << "ASCII Bits: " << tamanhoASCII << endl;
        cout << "Huffman Bits: " << tamanhoHuffman << endl;
        cout << "A codificacao de Huffman e equivalente a cerca de " << (tamanhoHuffman/tamanhoASCII) * 100 << "% do tamanho em ASCII" << endl;
        cout << "A codificacao de ASCII e equivalente a cerca de " << (tamanhoASCII/tamanhoHuffman) * 100 << "% do tamanho em Huffman" << endl;

        EscreveCodificacaoTXT(huffman);

        cout << endl << "---------------Texto Descodificado---------------" << endl;
        Decodificacao(huffman);

        cout << endl << "================DECODIFICACAO================" << endl;
        FormaArvoreBinaria(huffmanDecode);

        cout << endl << "---------------Arvore de Huffman---------------";
        ImprimePreFixa(huffmanDecode.raiz);

        cout << endl << endl << "---------------Texto Descodificado---------------" << endl;
        DecodificacaoArvoreBinaria(huffmanDecode);

        cout << endl << "---------------Tabela de Codigo---------------";
        ImprimeTabela(huffmanDecode.raiz);

    } 
    catch(const char* err) {
        cout << "ERRO: " << err << endl;
    }
    
    return 0;
}