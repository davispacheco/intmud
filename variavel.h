#ifndef VARIAVEL_H
#define VARIAVEL_H

#include "instr-enum.h"
class TClasse;
class TObjeto;
class TVarRef;
class TVarIncDec;
class TVarIntTempo;
class TVarIntExec;
class TListaObj;
class TListaItem;
class TTextoTxt;
class TTextoPos;
class TTextoVar;
class TTextoObj;
class TVarArqDir;
class TVarArqProg;
class TVarArqExec;
class TVarArqLog;
class TVarArqTxt;
class TVarArqMem;
class TVarNomeObj;
class TVarTelaTxt;
class TVarSocket;
class TVarServ;
class TVarProg;
class TVarDebug;
class TIndiceObj;
class TIndiceItem;
class TVarDataHora;
class TTextoVarSub;
class TTextoObjSub;
class TVariavel;

//----------------------------------------------------------------------------
/// Tipo de vari�vel
enum TVarTipo : unsigned char
{
    varOutros,  ///< Desconhecido
    varInt,     ///< Vari�vel int
    varDouble,  ///< Vari�vel double
    varTxt,     ///< Texto (const char*)
    varObj      ///< Refer�ncia (TObjeto*) e "NULO" (se TObjeto* = 0)
};

//----------------------------------------------------------------------------
/// Informa��es e fun��es de cada vari�vel
class TVarInfo
{
private:
    int (*FTamanho)(const char * instr);
    int (*FTamanhoVetor)(const char * instr);
    TVarTipo (*FTipo)(TVariavel * v);
    void (*FRedim)(TVariavel * v, TClasse * c, TObjeto * o,
            unsigned int antes, unsigned int depois);
    void (*FMoverEnd)(TVariavel * v, void * destino, TClasse * c, TObjeto * o);
    void (*FMoverDef)(TVariavel * v);
    bool (*FGetBool)(TVariavel * v);
    int (*FGetInt)(TVariavel * v);
    double (*FGetDouble)(TVariavel * v);
    const char * (*FGetTxt)(TVariavel * v);
    TObjeto * (*FGetObj)(TVariavel * v);
    void (*FOperadorAtrib)(TVariavel * v);
    bool (*FFuncVetor)(TVariavel * v, const char * nome);

    static char * EndBufferTxt;
    static unsigned short NumBufferTxt;

public:
    /// Construtor usado ao criar TVariavel::VarInfo
    TVarInfo();
    /// Construtor usado nas vari�veis da linguagem
    TVarInfo(int (*fTamanho)(const char * instr),
            int (*fTamanhoVetor)(const char * instr),
            TVarTipo (*fTipo)(TVariavel * v),
            void (*fRedim)(TVariavel * v, TClasse * c, TObjeto * o,
                    unsigned int antes, unsigned int depois),
            void (*fMoverEnd)(TVariavel * v, void * destino,
                    TClasse * c, TObjeto * o),
            void (*fMoverDef)(TVariavel * v),
            bool (*fGetBool)(TVariavel * v),
            int (*fGetInt)(TVariavel * v),
            double (*fGetDouble)(TVariavel * v),
            const char * (*fGetTxt)(TVariavel * v),
            TObjeto * (*fGetObj)(TVariavel * v),
            void (*fOperadorAtrib)(TVariavel * v),
            bool (*fFuncVetor)(TVariavel * v, const char * nome));
    /// Retorna um buffer de 0x100 bytes para ser usado para retornar texto
    static inline char * BufferTxt()
    {
        NumBufferTxt = (NumBufferTxt + 0x100) & 0x300;
        return EndBufferTxt + NumBufferTxt;
    }

    static int FTamanho0(const char * instr);
    static TVarTipo FTipoOutros(TVariavel * v);
    static TVarTipo FTipoInt(TVariavel * v);
    static TVarTipo FTipoDouble(TVariavel * v);
    static TVarTipo FTipoTxt(TVariavel * v);
    static TVarTipo FTipoObj(TVariavel * v);
    static void FRedim0(TVariavel * v, TClasse * c, TObjeto * o,
            unsigned int antes, unsigned int depois);
    static void FMoverEnd0(TVariavel * v, void * destino,
            TClasse * c, TObjeto * o);
    static void FMoverDef0(TVariavel * v);
    static bool FGetBoolFalse(TVariavel * v);
    static int FGetInt0(TVariavel * v);
    static double FGetDouble0(TVariavel * v);
    static const char * FGetTxtVazio(TVariavel * v);
    static TObjeto * FGetObjNulo(TVariavel * v);
    static void FOperadorAtribVazio(TVariavel * v);
    static bool FFuncVetorFalse(TVariavel * v, const char * nome);

    friend TVariavel;
};

//----------------------------------------------------------------------------
/** Cont�m as informa��es necess�rias para acessar uma vari�vel
 *  - Usado ao acessar vari�veis
 *  - Usado tamb�m ao executar fun��es (a pilha de vari�veis)
 */
class TVariavel /// Acesso �s vari�veis
{
public:
    static void Inicializa(); ///< Inicializa as vari�veis; chamado em main.cpp
    TVariavel();        ///< Construtor
    void Limpar();      ///< Limpa todos os campos do objeto

// Dados da vari�vel

    ///< Obt�m o tamanho de uma vari�vel na mem�ria
    /**< @param instr Instru��o codificada por Instr::Codif
     *   @return Tamanho da vari�vel (0=n�o ocupa lugar na mem�ria)
     *   @note  Se for vetor, retorna o tamanho do vetor na mem�ria */
    static inline int Tamanho(const char * instr)
    {
        unsigned char cmd = (unsigned char)instr[2];
        if (cmd < Instr::cTotalComandos)
            return VarInfo[cmd].FTamanho(instr);
        return 0;
    }

    /// Obt�m o tamanho do vetor de vari�veis conforme TVariavel::defvar
    inline int TamanhoVetor()
    {
        unsigned char cmd = (unsigned char)defvar[2];
        if (cmd < Instr::cTotalComandos)
            return VarInfo[cmd].FTamanhoVetor(defvar);
        return 0;
    }

    /// Obt�m o tipo mais apropriado para express�es num�ricas
    /** Usa  TVariavel::defvar  e  TVariavel::endvar
     *  @return Tipo de vari�vel */
    inline TVarTipo Tipo()
    {
        if (indice == 0xFF) // Vetor
            return varOutros;
        unsigned char cmd = (unsigned char)defvar[2];
        if (cmd < Instr::cTotalComandos)
            return VarInfo[cmd].FTipo(this);
        return varOutros;
    }

// Construtor/destrutor/mover

    /// Criar vari�vel: acerta dados da vari�vel na mem�ria
    /** Usa  TVariavel::defvar  e  TVariavel::endvar
     *  @note Criar uma vari�vel significa:
     *    - Alocar mem�ria para a vari�vel
     *    - Chamar TVariavel::Criar()  */
    inline void Criar(TClasse * c, TObjeto * o)
    {
        Redim(c, o, 0, defvar[Instr::endVetor] ?
                (unsigned char)defvar[Instr::endVetor] : 1);
    }

    /// Apagar vari�vel: remove dados da vari�vel na mem�ria
    /** Usa  TVariavel::defvar  e  TVariavel::endvar
     *  @note N�o libera mem�ria alocada (n�o executa delete) */
    inline void Apagar()
    {
        Redim(0, 0, defvar[Instr::endVetor] ?
                (unsigned char)defvar[Instr::endVetor] : 1, 0);
    }

    /// Redimensiona vetor na mem�ria
    /** @param c Classe ao qual a vari�vel pertence, 0 se nenhuma classe
     *  @param o Objeto ao qual a vari�vel pertence, 0 se nenhum objeto
     *  @param antes Tamanho atual do vetor (quantidade de vari�veis)
     *  @param depois Novo tamanho do vetor (quantidade de vari�veis)
     *  @note Para diminuir o tamanho do vetor, c e o podem ser 0
     *  @note N�o libera mem�ria alocada (n�o executa delete) */
    inline void Redim(TClasse * c, TObjeto * o,
            unsigned int antes, unsigned int depois)
    {
        if (antes == depois)
            return;
        // Mostra o que vai fazer
#if 0
        if (depois > antes)
            printf("Vari�vel criada  (%d a %d) end=%p", antes, depois-1, endvar);
        else
            printf("Vari�vel apagada (%d a %d) end=%p", depois, antes-1, endvar);
        char mens[BUF_MENS];
        if (Instr::Decod(mens, defvar, sizeof(mens)))
            printf(" def=%p %s\n", defvar, mens);
        else
            printf(" ERRO: %s\n", mens);
        fflush(stdout);
#endif
        unsigned char cmd = (unsigned char)defvar[2];
        if (cmd < Instr::cTotalComandos)
            VarInfo[cmd].FRedim(this, c, o, antes, depois);
        else
            TVarInfo::FRedim0(this, c, o, antes, depois);
    }

    /// Move a vari�vel para outra regi�o da mem�ria, mas n�o acerta defvar
    /** Usa:
     *    - TVariavel::defvar = defini��o da vari�vel
     *    - TVariavel::endvar = endere�o atual  */
    inline void MoverEnd(void * destino, TClasse * c, TObjeto * o)
    {
        if (destino == endvar)
            return;
#if 0
        printf("Vari�vel movida de %p para %p", endvar, destino);
        char mens1[BUF_MENS];
        if (Instr::Decod(mens1, defvar, sizeof(mens1)))
            printf(" def=%p %s\n", defvar, mens1);
        else
            printf(" ERRO: %s\n", mens1);
        fflush(stdout);
#endif
        unsigned char cmd = (unsigned char)defvar[2];
        if (cmd < Instr::cTotalComandos)
            VarInfo[cmd].FMoverEnd(this, destino, c, o);
        endvar = destino;
    }

    /// Acerta vari�vel porque defvar mudou
    /** Usa:
     *    - TVariavel::defvar = defini��o da vari�vel
     *    - TVariavel::endvar = endere�o atual   */
    inline void MoverDef()
    {
        unsigned char cmd = (unsigned char)defvar[2];
#if 0
        printf("Vari�vel mudou def end=%p", endvar);
        char mens1[BUF_MENS];
        if (Instr::Decod(mens1, defvar, sizeof(mens1)))
            printf(" def=%p %s\n", defvar, mens1);
        else
            printf(" ERRO: %s\n", mens1);
        fflush(stdout);
#endif
        if (cmd < Instr::cTotalComandos)
            VarInfo[cmd].FMoverDef(this);
    }

// Fun��es get
    /// Obt�m o valor "bool" da vari�vel
    inline bool getBool()
    {
        unsigned char cmd = (unsigned char)defvar[2];
        if (cmd < Instr::cTotalComandos && indice != 0xff)
            return VarInfo[cmd].FGetBool(this);
        return false;
    }

    /// Obt�m o valor "int" da vari�vel
    inline int getInt()
    {
        unsigned char cmd = (unsigned char)defvar[2];
        if (cmd < Instr::cTotalComandos && indice != 0xff)
            return VarInfo[cmd].FGetInt(this);
        return 0;
    }

    /// Obt�m o valor "double" da vari�vel
    inline double getDouble()
    {
        unsigned char cmd = (unsigned char)defvar[2];
        if (cmd < Instr::cTotalComandos && indice != 0xff)
            return VarInfo[cmd].FGetDouble(this);
        return 0;
    }

    /// Obt�m o texto da vari�vel
    inline const char * getTxt()
    {
        unsigned char cmd = (unsigned char)defvar[2];
        if (cmd < Instr::cTotalComandos && indice != 0xff)
            return VarInfo[cmd].FGetTxt(this);
        return "";
    }

    /// Obt�m a refer�ncia da vari�vel
    inline TObjeto * getObj()
    {
        unsigned char cmd = (unsigned char)defvar[2];
        if (cmd < Instr::cTotalComandos && indice != 0xff)
            return VarInfo[cmd].FGetObj(this);
        return nullptr;
    }

// Fun��es set
    void setInt(int valor); ///< Muda vari�vel a partir de int
    void setDouble(double valor); ///< Muda vari�vel a partir de double
    void setTxt(const char * txt); ///< Muda vari�vel a partir de texto
    void addTxt(const char * txt); ///< Adiciona texto na vari�vel
    void setObj(TObjeto * obj); ///< Muda vari�vel a partir de refer�ncia

// Operadores
    /// Atribui o valor da pr�xima vari�vel (this[1]) a esta (*this)
    inline void OperadorAtrib()
    {
        unsigned char cmd = (unsigned char)defvar[2];
        if (cmd < Instr::cTotalComandos && indice != 0xff &&
                this[1].indice != 0xff)
            VarInfo[cmd].FOperadorAtrib(this);
    }

    int Compara(TVariavel * v);
        ///< Compara com outra vari�vel do mesmo tipo
        /**< @return -1 se menor, 0 se igual, 1 se maior */
    bool Func(const char * nome);
        ///< Executa fun��o da vari�vel
        /**< Deve verificar argumentos, ap�s a vari�vel
         *   @param nome Nome da fun��o
         *   @retval true se processou
         *   @retval false se fun��o inexistente */

// Vari�veis
    const char * defvar;
        ///< Instru��o que define a vari�vel
        /**< @sa Instr::Comando */
    const char * nomevar;
        ///< Mesmo que defvar, mas s� s�o usados nome da vari�vel e indenta��o
        /**< @note Usado para obter a vari�vel a partir do nome, nas fun��es,
         *         e para apagar vari�veis locais */
    union {
        void * endvar;  ///< Endere�o da vari�vel na mem�ria
                        /** - � nullptr se n�o for aplic�vel
                         *  - Em vetores, endere�o da primeira vari�vel */
        const void * endfixo;
                    ///< Valor "const" de endvar
                    /**< Usar endfixo quando a vari�vel n�o poder� ser mudada */
        char * endchar; ///< Usado principalmente com Instr::cVarNome
        int  valor_int;  ///< endvar como int
        double valor_double; ///< endvar como double (8 bytes)

        char * end_char; ///< endvar como char*
        TVarRef * end_varref;        ///< Instr::cRef
        signed   short * end_short;  ///< Instr::cInt16
        unsigned short * end_ushort; ///< Instr::cUInt16
        signed   int * end_int;      ///< Instr::cInt32
        unsigned int * end_uint;     ///< Instr::cUInt32
        TVarIncDec   * end_incdec;   ///< Instr::cIntInc e Instr::cIntDec
        float        * end_float;    ///< Instr::cReal
        double       * end_double;   ///< Instr::cReal2
        TVarArqDir   * end_arqdir;   ///< Instr::cArqDir
        TVarArqLog   * end_arqlog;   ///< Instr::cArqLog
        TVarArqProg  * end_arqprog;  ///< Instr::cArqProg
        TVarArqExec  * end_arqexec;  ///< Instr::cArqExec
        TVarArqTxt   * end_arqtxt;   ///< Instr::cArqTxt
        TVarArqMem   * end_arqmem;   ///< Instr::cArqMem
        TVarIntTempo * end_inttempo; ///< Instr::cIntTempo
        TVarIntExec  * end_intexec;  ///< Instr::cIntExec
        TListaObj    * end_listaobj; ///< Instr::cListaObj
        TListaItem   * end_listaitem;///< Instr::cListaItem
        TTextoTxt    * end_textotxt; ///< Instr::cTextoTxt
        TTextoPos    * end_textopos; ///< Instr::cTextoPos
        TTextoVar    * end_textovar; ///< Instr::cTextoVar
        TTextoObj    * end_textoobj; ///< Instr::cTextoObj
        TVarTelaTxt  * end_telatxt;  ///< Instr::cTelaTxt
        TVarSocket   * end_socket;   ///< Instr::cSocket
        TVarServ     * end_serv;     ///< Instr::cServ
        TVarNomeObj  * end_nomeobj;  ///< Instr::cNomeObj
        TVarProg     * end_prog;     ///< Instr::cProg
        TVarDebug    * end_debug;    ///< Instr::cDebug
        TIndiceObj   * end_indiceobj; ///< Instr::cIndiceObj
        TIndiceItem  * end_indiceitem; ///< Instr::cIndiceItem
        TVarDataHora * end_datahora; ///< Instr::cDataHora
        TTextoVarSub * end_textovarsub; ///< Instr::cTextoVarSub
        TTextoObjSub * end_textoobjsub; ///< Instr::cTextoObjSub
    };
    int  tamanho;   ///< Quantos bytes est� usando na mem�ria
                    /**< 0 significa que n�o est� usando ou a vari�vel est�
                         sendo usada em outro lugar
                             @note N�o � usado em TVariavel */
    unsigned char indice;
        ///< �ndice no vetor ou 0 se n�o for vetor ou 0xFF se for o vetor
    unsigned char numbit;  ///< N�mero do primeiro bit de 0 a 7, se int1
    unsigned short numfunc; ///< Para uso da vari�vel; inicialmente � zero

private:
    static TVarInfo * VarInfo;
};

//----------------------------------------------------------------------------

#endif
