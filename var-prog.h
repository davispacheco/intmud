#ifndef VAR_PROG_H
#define VAR_PROG_H

#include "classe.h"
class TVariavel;
class TVarInfo;
class TClasse;
class TObjeto;
class TArqMapa;

//----------------------------------------------------------------------------
enum TProgConsulta ///< O que consultar, TVarProg::consulta
{
    prNada,     ///< N�o est� consultando nada
    prArquivo,  ///< iniarq() para arquivos
    prArqCl,    ///< iniarq() para classes de um arquivo
    prClasse,   ///< iniclasse()
    prFunc,     ///< inifunc()
    prFuncTudo, ///< inifunctudo()
    prFuncCl,   ///< inifunccl()
    prHerda,    ///< iniherda()
    prHerdaTudo,///< iniherdatudo()
    prHerdaInv, ///< iniherdainv()
    prLinhaCl,  ///< inilinha() - linhas de uma classe
    prLinhaFunc,///< inilinha() - linhas de uma fun��o
    prLinhaVar  ///< inilinha() - uma vari�vel (uma �nica linha)
};

//----------------------------------------------------------------------------
/** Trata das vari�veis do tipo Prog */
class TVarProg /// Vari�veis Prog
{
public:
    static const TVarInfo * Inicializa();
        ///< Inicializa vari�vel e retorna informa��es
    static void LimparVar(); ///< Apaga refer�ncias do programa nas vari�veis prog
private:
    void Criar();           ///< Cria objeto
    void Apagar();          ///< Apaga objeto
    void Mover(TVarProg * destino); ///< Move objeto para outro lugar
    int  getValor();    ///< Ler valor num�rico da vari�vel

    static bool FuncExiste(TVariavel * v);       ///< Processa fun��o Existe
    static bool FuncArquivo(TVariavel * v);      ///< Processa fun��o Arquivo
    static bool FuncArqNome(TVariavel * v);      ///< Processa fun��o ArqNome
    static bool FuncVarComum(TVariavel * v);     ///< Processa fun��o VarComum
    static bool FuncVarSav(TVariavel * v);       ///< Processa fun��o VarSav
    static bool FuncVarNum(TVariavel * v);       ///< Processa fun��o VarNum
    static bool FuncVarTexto(TVariavel * v);     ///< Processa fun��o VarTexto
    static bool FuncVarTipo(TVariavel * v);      ///< Processa fun��o VarTipo
    static bool FuncVarLugar(TVariavel * v);     ///< Processa fun��o VarLugar
    static bool FuncVarVetor(TVariavel * v);     ///< Processa fun��o VarVetor
    static bool FuncConst(TVariavel * v);        ///< Processa fun��o Const
    static bool FuncClasse(TVariavel * v);       ///< Processa fun��o Classe

    static bool FuncIniArq(TVariavel * v);       ///< Processa fun��o IniArq
    static bool FuncIniClasse(TVariavel * v);    ///< Processa fun��o IniClasse
    static bool FuncIniFunc(TVariavel * v);      ///< Processa fun��o IniFunc
    static bool FuncIniFuncTudo(TVariavel * v);  ///< Processa fun��o IniFuncTudo
    static bool FuncIniFuncCl(TVariavel * v);    ///< Processa fun��o IniFuncCl
    static bool FuncIniHerda(TVariavel * v);     ///< Processa fun��o IniHerda
    static bool FuncIniHerdaTudo(TVariavel * v); ///< Processa fun��o IniHerdatudo
    static bool FuncIniHerdaInv(TVariavel * v);  ///< Processa fun��o IniHerdainv
    static bool FuncIniLinha(TVariavel * v);     ///< Processa fun��o IniLinha

    static bool FuncLin(TVariavel * v);          ///< Processa fun��o Lin
    static bool FuncNivel(TVariavel * v);        ///< Processa fun��o Nivel
    static bool FuncDepois(TVariavel * v);       ///< Processa fun��o Depois
    static bool FuncTexto(TVariavel * v);        ///< Processa fun��o Texto

    static bool FuncApagar(TVariavel * v);       ///< Processa fun��o Apagar
    static bool FuncCriar(TVariavel * v);        ///< Processa fun��o Criar
    static bool FuncApagarLin(TVariavel * v);    ///< Processa fun��o ApagarLin
    static bool FuncCriarLin(TVariavel * v);     ///< Processa fun��o CriarLin
    static bool FuncFAntes(TVariavel * v);       ///< Processa fun��o FAntes
    static bool FuncFDepois(TVariavel * v);      ///< Processa fun��o FDepois
    static bool FuncMudar(TVariavel * v, int lugar); ///< Chamado por FuncF*
    static bool FuncRenomear(TVariavel * v);     ///< Processa fun��o Renomear
    static bool FuncSalvar(TVariavel * v);       ///< Processa fun��o Salvar
    static bool FuncSalvarTudo(TVariavel * v);   ///< Processa fun��o SalvarTudo

    static bool FuncClIni(TVariavel * v);        ///< Processa fun��o ClIni
    static bool FuncClFim(TVariavel * v);        ///< Processa fun��o ClFim
    static bool FuncClAntes(TVariavel * v);      ///< Processa fun��o ClAntes
    static bool FuncClDepois(TVariavel * v);     ///< Processa fun��o ClDepois

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

    void MudaConsulta(TProgConsulta valor);
        ///< Muda o valor da vari�vel consulta
    TProgConsulta consulta;     ///< O que consultar
    TClasse * Classe;           ///< A classe que est� sendo consultada
    union {
        TArqMapa * ArqAtual;    ///< Valor atual da busca como arquivo
        TClasse ** PontAtual;   ///< Valor atual da busca
        TClasse * ClasseAtual;  ///< Valor atual da busca como classe
        const char * TextoAtual; ///< Valor atual da busca como texto
        int       ValorAtual;   ///< Valor atual da busca como int
    };
    union {
        TClasse ** PontFim;     ///< Valor final da busca
        TClasse * ClasseFim;    ///< Valor final da busca como classe
        const char * TextoFim;  ///< Valor final da busca como texto
        int       ValorFim;     ///< Valor final da busca como int
        TClasse * ClasseHerda[HERDA_TAM]; ///< Usado em IniHerda2
    };

    static TVarProg * Inicio;   ///< Primeiro objeto (com consulta!=0)
    TVarProg * Antes;           ///< Objeto anterior (se consulta!=0)
    TVarProg * Depois;          ///< Pr�ximo objeto (se consulta!=0)
};

//----------------------------------------------------------------------------

#endif
