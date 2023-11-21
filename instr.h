#ifndef INSTR_H
#define INSTR_H

class TClasse;
class TObjeto;
class TVariavel;

#define OTIMIZAR_VAR // Otimiza��o de fun��es predefinidas e vari�veis locais
#define VAR_NOME_TAM 80 // Tamanho m�ximo dos nomes das vari�veis + 1
#define BUF_MENS 16384 // Tamanho do buffer de texto usado nas fun��es
#define BUF_CODIF 8192 // Tamanho do buffer com uma instru��o codificada

/// Codificar, decodificar e executar instru��es
/** Codificar, decodificar e executar instru��es */
namespace Instr {

//----------------------------------------------------------------------------
// Fun��es
bool Codif(char * destino, const char * origem, int tamanho);
bool Decod(char * destino, const char * origem, int tamanho);
bool Mostra(char * destino, const char * origem, int tamanho);

int  Prioridade(int operador);
bool ChecaHerda(const char * instr, const char * nomeclasse);
const char * ProximaInstr(const char * instr, const char * texto, int tamanho);

bool CriarVarInt(int valor);
bool CriarVarInt(TVariavel * v, int valor);
bool CriarVarDouble(double valor);
bool CriarVarDouble(TVariavel * v, double valor);
bool CriarVarTexto(const char * mens, int tammens = -1);
bool CriarVarTxtFixo(const char * texto);
bool CriarVarTxtFixo(TVariavel * v, const char * texto);
bool CriarVarObj(TObjeto * obj);
bool CriarVar(const char * defvar);
void ApagarVar(TVariavel * v);
void ApagarRet(TVariavel * v);
void VarFuncPrepara(TVariavel * varini);
bool VarFuncFim();
bool ComparaInstr(const char * instr1, const char * instr2);
const char * ProcuraExpr(const char * expr, int valor);
const char * NomeInstr(const char * instr);
const char * NomeComando(int valor);
const char * NomeExpr(int valor);

bool ExecIni(TClasse * classe, const char * func);
bool ExecIni(TObjeto * este, const char * func);
void ExecArg(const char * txt);
void ExecArg(int valor);
void ExecArgCriar(const char * def);
bool ExecX();
void ExecFim();

//----------------------------------------------------------------------------
// Vari�veis predefinidas
/// TVariavel::defvar para Instr::cNulo
extern const char InstrNulo[];
/// TVariavel::defvar para Instr::cSocket
extern const char InstrSocket[];
/// TVariavel::defvar para Instr::cTxtFixo
extern const char InstrTxtFixo[];
/// TVariavel::defvar para Instr::cVarNome
extern const char InstrVarNome[];
/// TVariavel::defvar para Instr::cVarInicio
extern const char InstrVarInicio[];
/// TVariavel::defvar para Instr::cVarIniFunc
extern const char InstrVarIniFunc[];
/// TVariavel::defvar para Instr::cVarClasse
extern const char InstrVarClasse[];
/// TVariavel::defvar para Instr::cVarObjeto
extern const char InstrVarObjeto[];
/// TVariavel::defvar para Instr::cVarInt
extern const char InstrVarInt[];
/// TVariavel::defvar para Instr::cVarDouble
extern const char InstrVarDouble[];
/// TVariavel::defvar para Instr::cListaItem
extern const char InstrVarListaItem[];
/// TVariavel::defvar para Instr::cTextoPos
extern const char InstrVarTextoPos[];
/// TVariavel::defvar para Instr::cTextoVarSub
extern const char InstrVarTextoVarSub[];
/// TVariavel::defvar para Instr::cTextoObjSub
extern const char InstrVarTextoObjSub[];
/// TVariavel::func para Instr::cDebug
extern const char InstrDebugFunc[];
/// TVariavel::defvar para operadores ++ e --
extern const char InstrAddSub[];
/// Quantas instru��es pode executar antes que o controle retorne ao programa
extern int VarExec;
/// Valor inicial de Instr::VarExec quando Instr::ExecIni � executado
extern int VarExecIni;

//----------------------------------------------------------------------------
/** Verifica se instru��es de uma classe (codificadas por Instr::Codif)
    est�o na ordem correta */
class ChecaLinha /// Verifica ordem das instru��es de uma classe
{
public:
    ChecaLinha();
    void Inicio();
            /**< Indica que est� no in�cio da lista de instru��es */
    const char * Instr(const char * instr);
            /**< Checa pr�xima instru��o da lista
                @param instr Instru��o codificada
                @return 0 se instru��o est� no lugar correto,
                        outro valor=mensagem de erro */
    const char * Fim();
            ///< Chamado ap�s checar todas as instru��es
            /**< Verifica se h� algum bloco pendente */
    static int ChecaErro;
            ///< Checagem de erros em blocos de instru��es
            /**< - 0=n�o verifica se cada bloco est� terminando corretamente
             *   - 1=verifica blocos exceto fimse no final das fun��es
             *   - 2=verifica blocos inclusive fimse no final das fun��es */
private:
    char esperando;
            /**< O que est� esperando:
                - 0=in�cio do arquivo; pode receber "herda"
                - 1=fun��o ou vari�vel (pertencente � classe)
                - 2=instru��es de uma fun��o
                - 3=ap�s defini��o de fun��o + defini��o de constante */
    unsigned char buf[1024];
            ///< Blocos; cada byte:
            /**< - 0=bloco se/senao/fimse
             *   - 1=bloco enquanto/efim ou epara/efim
             *   - 2=bloco casovar/casose/casofim */
    unsigned int pbuf;
            ///< Quantos bytes de buf[] est�o sendo usados
};

//----------------------------------------------------------------------------
/** Pilha de fun��es - usado ao executar fun��es */
class ExecFunc /// Pilha de fun��es
{
public:
    TObjeto * este;     ///< Objeto ao qual a fun��o pertence
    const char * nome;  ///< Nome da fun��o; codificado como instru��o
    const char * linha; ///< Instru��o codificada sendo executada
                        ///< Mesmo formato de TClasse::Comandos
    const char * expr;  ///< Aonde parou na express�o num�rica
                        ///< =0 se n�o estiver processando express�o num�rica
    TVariavel * inivar; ///< Primeiro argumento da fun��o
    TVariavel * fimvar; ///< Primeira vari�vel ap�s vari�veis locais da fun��o
    char  numarg;       ///< N�mero de argumentos arg0 a arg9
    char  tipo;         ///< Como � o retorno da fun��o:
            /**< - 0 = fun��o normal
             *   - 1 = ler varfunc
             *   - 2 = mudar varfunc
             *   - 3 = instru��o criar()
             *   - 4 = instru��o debug.cmd (transforma retorno em texto) */
    unsigned char indent;///< Para apagar vari�veis que sa�ram do escopo
    char * funcdebug;   ///< Fun��o executada a cada instru��o, 0 se nenhuma
    TObjeto * objdebug; ///< Objeto relacionado a funcdebug
};

//----------------------------------------------------------------------------
/** Processa fun��es predefinidas
    @note A lista de fun��es est� definida em instr-exec.cpp
*/
class TListaFunc /// Fun��es internas
{
public:
        /// Nome da fun��o predefinida
    const char * Nome;

        /// Fun��o que processa a fun��o predefinida
        /** Ao executar a fun��o, a pilha de vari�veis est� assim:
        - cVarNome
        - cVarInicio  (v aponta para essa vari�vel)
        - Argumentos da fun��o interna (VarAtual aponta para a �ltima)
        .
        Se retornar true, deve:
        - Apagar vari�veis de v em diante
        - Criar uma vari�vel com o resultado
        .
        @param v Endere�o da vari�vel cVarInicio
        @retval true Se processou normalmente
        @retval false Se erro; o resultado ser� o tipo NULO */
    bool (*Func)(TVariavel * v);
};

/// Lista de fun��es predefinidas
/// Deve obrigatoriamente estar em ordem alfab�tica
extern const TListaFunc ListaFunc[];

/// Obt�m o �ndice de uma fun��o em ListaFunc a partir do nome
/** @param nome Nome da fun��o
 *  @return -1 se n�o encontrou; caso contr�rio � o �ndice em ListaFunc */
int InfoFunc(const char * nome);

//----------------------------------------------------------------------------
    /// Pilha de dados (64K)
extern char * const DadosPilha;
extern char * const DadosFim;
    /// Pilha de dados - in�cio da �rea de dados dispon�vel
extern char * DadosTopo;

    /// Pilha de vari�veis
extern TVariavel * const VarPilha;
extern TVariavel * const VarFim;
    /// Pilha de vari�veis - �ltima vari�vel da pilha
extern TVariavel * VarAtual;

    /// Pilha de fun��es
extern ExecFunc * const FuncPilha;
extern ExecFunc * const FuncFim;
    /// Pilha de fun��es - �ltima fun��o da pilha
extern ExecFunc * FuncAtual;

//----------------------------------------------------------------------------
}

#endif
