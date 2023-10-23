#ifndef VAR_ARQEXEC_H
#define VAR_ARQEXEC_H

#ifdef __WIN32__
 #include <windows.h>
 #include <winsock.h>
#else
 #include <sys/types.h>
 #include <netinet/in.h>
#endif
#include "exec.h"

#define EXEC_ENV 2048

//------------------------------------------------------------------------------
class TArqExec /// Op��es ARQEXEC do arquivo INT principal
{
public:
    TArqExec(const char * nome);
    ~TArqExec();

    static TArqExec * ExecIni() { return Inicio; }
        ///< Retorna o primeiro objeto TArqExec
    TArqExec * ExecProximo() { return Proximo; }
        ///< Retorna o pr�ximo objeto TArqExec ou 0 se n�o houver
    const char * ExecNome() { return Nome; }
        ///< Retorna o nome

private:
    char * Nome;            ///< Texto da op��o arqexec do arquivo int principal

    TArqExec *Anterior;     ///< Lista ligada; objeto anterior
    TArqExec *Proximo;      ///< Lista ligada; pr�ximo objeto
    static TArqExec *Inicio;///< Lista ligada; primeiro objeto
};

//------------------------------------------------------------------------------
class TClasse;
class TObjeto;
class TVariavel;
class TVarInfo;
class TVarArqExec;
class TObjExec : public TExec /// Um programa sendo executado por ArqExec
{
public:
    TObjExec(TVarArqExec * var);   ///< Construtor
    virtual ~TObjExec();        ///< Destrutor
    bool Enviar(const char * mensagem);
        ///< Envia mensagem
        /**< @return true se conseguiu enviar, false se buffer cheio */
    static void Fd_Set(fd_set * set_entrada, fd_set * set_saida);
    static void ProcEventos(fd_set * set_entrada, fd_set * set_saida);

private:
    TVarArqExec * VarArqExec;      ///< Objeto TVarArqExec associado a este objeto

// Para enviar mensagens
    void EnvPend();             ///< Envia dados pendentes
    char bufEnv[EXEC_ENV];      ///< Cont�m a mensagem que ser� enviada
    unsigned int pontEnv;       ///< N�mero de bytes pendentes em bufEnv
    static bool boolenvpend;    ///< Verdadeiro se tem algum dado pendente

// Para receber mensagens
    void Receber();
        ///< Recebe as mensagens pendentes
    char dadoRecebido;
        ///< Para controle da mensagem recebida
        /**< - 0 = comportamento padr�o
         *   - 0x0D, 0x0A = para detectar nova linha */

// Lista ligada
    static TObjExec * Inicio; ///< Primeiro objeto da lista ligada
    TObjExec * Antes;  ///< Objeto anterior da lista ligada
    TObjExec * Depois; ///< Pr�ximo objeto da lista ligada

    friend class TVarArqExec;
};

//------------------------------------------------------------------------------
class TVarArqExec /// Uma vari�vel ArqExec
{
public:
    static const TVarInfo * Inicializa();
        ///< Inicializa vari�vel e retorna informa��es
    void Mover(TVarArqExec * destino);  ///< Move TVarArqExec para outro lugar
    void EndObjeto(TClasse * c, TObjeto * o);
    bool Func(TVariavel * v, const char * nome); ///< Fun��o da vari�vel

    const char * defvar;    ///< Como foi definida a vari�vel
    union {
        TClasse * endclasse;///< Em que classe est� definido
        TObjeto * endobjeto;///< Em que objeto est� definido
    };
    bool b_objeto;          ///< O que usar: true=endobjeto, false=endclasse
    unsigned char indice;   ///< �ndice no vetor

private:
    void GeraEvento(const char * evento, const char * texto, int valor);
        ///< Executa uma fun��o
        /**< @param evento Nome do evento (ex. "msg")
         *   @param texto Texto do primeiro argumento, 0=nenhum texto
         *   @param valor Segundo argumento, <0 = nenhum valor
         *   @note O objeto pode ser apagado nessa fun��o */

    bool FuncMsg(TVariavel * v);    ///< Processa fun��o Msg
    bool FuncAbrir(TVariavel * v);  ///< Processa fun��o Abrir
    bool FuncFechar(TVariavel * v); ///< Processa fun��o Fechar
    bool FuncAberto(TVariavel * v); ///< Processa fun��o Aberto

    static int FTamanho(const char * instr);
    static int FTamanhoVetor(const char * instr);
    static void FRedim(TVariavel * v, TClasse * c, TObjeto * o,
            unsigned int antes, unsigned int depois);
    static void FMoverEnd(TVariavel * v, void * destino,
            TClasse * c, TObjeto * o);
    static void FMoverDef(TVariavel * v);

    TObjExec * ObjExec;     ///< Programa atual

    friend class TObjExec;
};

//------------------------------------------------------------------------------

#endif
