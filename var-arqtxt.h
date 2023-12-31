#ifndef VAR_ARQTXT_H
#define VAR_ARQTXT_H

#include <stdio.h>

class TVariavel;
class TVarInfo;
class TClasse;
class TObjeto;

//----------------------------------------------------------------------------
class TVarArqTxt /// Vari�vel arqtxt
{
public:
    static const TVarInfo * Inicializa();
        ///< Inicializa vari�vel e retorna informa��es
    void Criar();           ///< Chamado ao criar objeto
    void Apagar();          ///< Apaga objeto
    int  getValor();        ///< Ler valor num�rico da vari�vel
private:
    static bool FuncLer(TVariavel * v);          ///< Processa fun��o Ler
    static bool FuncEscr(TVariavel * v);         ///< Processa fun��o Escr
    static bool FuncEof(TVariavel * v);          ///< Processa fun��o Eof
    static bool FuncPos(TVariavel * v);          ///< Processa fun��o Pos
    static bool FuncFechar(TVariavel * v);       ///< Processa fun��o Fechar
    static bool FuncFlush(TVariavel * v);        ///< Processa fun��o Flush
    static bool FuncValido(TVariavel * v);       ///< Processa fun��o Valido
    static bool FuncExiste(TVariavel * v);       ///< Processa fun��o Existe
    static bool FuncAbrir(TVariavel * v);        ///< Processa fun��o Abrir
    static bool FuncTruncar(TVariavel * v);      ///< Processa fun��o Truncar

    static int FTamanho(const char * instr);
    static int FTamanhoVetor(const char * instr);
    static void FRedim(TVariavel * v, TClasse * c, TObjeto * o,
            unsigned int antes, unsigned int depois);
    static void FMoverEnd(TVariavel * v, void * destino,
            TClasse * c, TObjeto * o);
    static bool FGetBool(TVariavel * v);
    static int FGetInt(TVariavel * v);
    static double FGetDouble(TVariavel * v);
    static const char * FGetTxt(TVariavel * v);

    void Fechar();      ///< Fecha arquivo
    FILE * arq;         ///< Para acessar o arquivo
    bool ModoBinario;   ///< Se est� acessando o arquivo em modo bin�rio
};

//----------------------------------------------------------------------------

#endif
