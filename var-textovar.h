#ifndef VAR_TEXTOVAR_H
#define VAR_TEXTOVAR_H

#include "instr.h"

class TVariavel;
class TVarInfo;
enum TVarTipo : unsigned char;
class TTextoVarSub;
class TBlocoVar;

//----------------------------------------------------------------------------
enum TextoVarTipo ///< Tipo de vari�vel
{
    TextoVarTipoTxt, ///< TBlocoVarTxt
    TextoVarTipoNum, ///< TBlocoVarNum
    TextoVarTipoDec, ///< TBlocoVarDec
    TextoVarTipoRef  ///< TBlocoVarRef
};

//----------------------------------------------------------------------------
class TTextoVar  /// Vari�veis TextoVar
{
public:
    static const TVarInfo * Inicializa();
        ///< Inicializa vari�vel e retorna informa��es
    void Apagar();          ///< Apaga objeto
    void Limpar();          ///< Apaga o texto do objeto
    void Mover(TTextoVar * destino);
        ///< Move objeto para outro lugar
    bool CriarTextoVarSub(const char * nome);
        ///< Cria uma vari�vel TTextoVarSub na pilha
    bool CriarTextoVarSub(TBlocoVar * bl);
        ///< Cria uma vari�vel TTextoVarSub na pilha
    TBlocoVar * Procura(const char * texto);
        ///< Procura um objeto TIndiceObj a partir do nome
        /**< @param texto Nome a pesquisar
         *   @return Endere�o do objeto, ou 0 se n�o foi encontrado */
    TBlocoVar * ProcIni(const char * nome);
        ///< Semelhante a Procura(), mas procura o primeiro texto
    TBlocoVar * ProcFim(const char * nome);
        ///< Semelhante a Procura(), mas procura o �ltimo texto
    TBlocoVar * ProcAntes(const char * nome);
        ///< Semelhante a Procura(), mas procura o texto anterior
    TBlocoVar * ProcDepois(const char * nome);
        ///< Semelhante a Procura(), mas procura o pr�ximo texto

private:
    static bool FuncValor(TVariavel * v);
    static bool FuncValorIni(TVariavel * v);
    static bool FuncValorFim(TVariavel * v);
    static bool FuncMudar(TVariavel * v);
    static bool FuncNomeVar(TVariavel * v);
    static bool FuncTipo(TVariavel * v);
    static bool FuncAntes(TVariavel * v);
    static bool FuncDepois(TVariavel * v);
    static bool FuncIni(TVariavel * v);
    static bool FuncFim(TVariavel * v);
    static bool FuncLimpar(TVariavel * v);
    static bool FuncTotal(TVariavel * v);

    static int FTamanho(const char * instr);
    static int FTamanhoVetor(const char * instr);
    static void FRedim(TVariavel * v, TClasse * c, TObjeto * o,
            unsigned int antes, unsigned int depois);
    static void FMoverEnd(TVariavel * v, void * destino,
            TClasse * c, TObjeto * o);
    static void FOperadorAtrib(TVariavel * v1, TVariavel * v2);
    static bool FOperadorIgual2(TVariavel * v1, TVariavel * v2);
    static unsigned char FOperadorCompara(TVariavel * v1, TVariavel * v2);
    static bool FFuncTexto(TVariavel * v,const char * nome);

public:
    TBlocoVar * RBroot;  ///< Objeto raiz da RBT
    TTextoVarSub * Inicio; ///< Primeiro objeto TTextoVarSub
    int Total;  ///< Quantidade de vari�veis

    static TTextoVar * TextoAtual;
                ///< Para obter o endere�o da vari�vel mesmo que seja movida
};

//----------------------------------------------------------------------------
class TTextoVarSub /// Para acessar uma vari�vel de TTextoVar
{
public:
    static const TVarInfo * Inicializa();
        ///< Inicializa vari�vel e retorna informa��es
    void Criar(TTextoVar * var, const char * nome, bool checatipo);
        ///< Adiciona objeto em um TTextoVar
        /**< @param var Vari�vel TextoVar
         *   @param nome Nome da vari�vel de TextoVar
         *   @param checatipo Se deve obter o tipo a partir do nome
         *           da vari�vel */
    void Apagar();
        ///< Retira objeto de um textovar
    void Mover(TTextoVarSub * destino);
        ///< Move bloco para outro lugar

// Lista ligada
    TTextoVar * TextoVar;       ///< A qual textovar pertence
                                /**< Se 0, a vari�vel n�o � v�lida */
    TTextoVarSub * Antes;       ///< Objeto anterior
    TTextoVarSub * Depois;      ///< Pr�ximo objeto
    char   NomeVar[VAR_NOME_TAM]; ///< Nome da vari�vel
    TextoVarTipo TipoVar;       ///< Tipo da vari�vel

// Fun��es get
    bool getBool();         ///< Obt�m o valor "bool" da vari�vel
    int getInt();           ///< Obt�m o valor "int" da vari�vel
    double getDouble();     ///< Obt�m o valor "double" da vari�vel
    const char * getTxt();  ///< Obt�m o texto da vari�vel
    TObjeto * getObj();     ///< Obt�m a refer�ncia da vari�vel

// Fun��es set
    void setInt(int valor); ///< Muda vari�vel a partir de int
    void setDouble(double valor); ///< Muda vari�vel a partir de double
    void setTxt(const char * txt); ///< Muda vari�vel a partir de texto
    void addTxt(const char * txt); ///< Adiciona texto na vari�vel
    void setObj(TObjeto * obj); ///< Muda vari�vel a partir de refer�ncia

private:
    static int FTamanho(const char * instr);
    static int FTamanhoVetor(const char * instr);
    static TVarTipo FTipo(TVariavel * v);
    static void FRedim(TVariavel * v, TClasse * c, TObjeto * o,
            unsigned int antes, unsigned int depois);
    static void FMoverEnd(TVariavel * v, void * destino,
            TClasse * c, TObjeto * o);
    static bool FGetBool(TVariavel * v);
    static int FGetInt(TVariavel * v);
    static double FGetDouble(TVariavel * v);
    static const char * FGetTxt(TVariavel * v);
    static TObjeto * FGetObj(TVariavel * v);
    static void FOperadorAtrib(TVariavel * v1, TVariavel * v2);
    static bool FOperadorAdd(TVariavel * v1, TVariavel * v2);
    static bool FOperadorIgual2(TVariavel * v1, TVariavel * v2);
    static unsigned char FOperadorCompara(TVariavel * v1, TVariavel * v2);
};

//----------------------------------------------------------------------------
class TBlocoVar /// Vari�vel de um objeto TTextoVar
{
public:
    TBlocoVar(TTextoVar * var, const char * nome, const char * texto=0);
        ///< Construtor
        /**< @param var Objeto TTextoVar que cont�m essa vari�vel
         *   @param nome Nome da vari�vel
         *   @param texto Texto que ser� colocado ap�s o nome da vari�vel */
    virtual ~TBlocoVar();
        ///< Destrutor
    void MoveTextoVar(TTextoVar * textovar);
        ///< Usado por TTextoVar::Mover, para mudar TBlocoVar::TextoVar
    virtual const char * Tipo() = 0;
        ///< Caracter ap�s o nome da vari�vel que indica o tipo
    virtual TextoVarTipo TipoVar() = 0;
        ///< Tipo de vari�vel

// Fun��es get
    virtual bool   getBool()=0;           ///< Retorna valor como bool
    virtual int    getInt()=0;            ///< Retorna valor como int
    virtual double getDouble()=0;         ///< Retorna valor como double
    virtual const char * getTxt()=0;      ///< Retorna valor como texto
    virtual TObjeto * getObj()=0;         ///< Obt�m a refer�ncia da vari�vel

// Fun��es set
    virtual void setInt(int valor)=0;   ///< Muda valor como int
    virtual void setDouble(double valor)=0; ///< Muda valor como double
    virtual void setTxt(const char * txt)=0; ///< Muda valor como texto
    virtual void addTxt(const char * txt)=0; ///< Adiciona texto
    virtual void setObj(TObjeto * obj)=0; ///< Muda vari�vel a partir de refer�ncia

// �rvore organizada por TBlocoVar::NomeVar
    void RBinsert(void);       ///< Insere objeto na RBT
    void RBremove(void);       ///< Remove objeto da RBT
    TBlocoVar * RBfirst(void); ///< Primeiro objeto da RBT
    TBlocoVar * RBlast(void);  ///< �ltimo objeto da RBT
    static TBlocoVar * RBnext(TBlocoVar *); ///< Pr�ximo objeto da RBT
    static TBlocoVar * RBprevious(TBlocoVar *); ///< Objeto anterior da RBT
    static int RBcomp(TBlocoVar * x, TBlocoVar * y); ///< Compara objetos
    void RBleft_rotate(void);
    void RBright_rotate(void);

    //static TBlocoVar * RBroot;  ///< Objeto raiz
    TBlocoVar *RBparent;    ///< Objeto objeto pai
    TBlocoVar *RBleft,*RBright; ///< Objetos filhos
    TTextoVar *TextoVar;    ///< Vari�vel TextoVar que cont�m o bloco (RBT)
    const char * NomeVar;   ///< Nome da vari�vel
    unsigned char RBcolour; ///< Bit 0=cor, bit 1: 0=RBT, 1=somente texto
    unsigned short Texto;   ///< NomeVar+Texto = texto ap�s o nome da vari�vel
};

//----------------------------------------------------------------------------
class TBlocoVarTxt : public TBlocoVar // Vari�vel de texto
{
public:
    TBlocoVarTxt(TTextoVar * var, const char * nome, const char * texto);
    virtual ~TBlocoVarTxt();
    const char * Tipo() { return " "; }
    TextoVarTipo TipoVar() { return TextoVarTipoTxt; }

// Fun��es get
    bool getBool();         ///< Obt�m o valor "bool" da vari�vel
    int getInt();           ///< Obt�m o valor "int" da vari�vel
    double getDouble();     ///< Obt�m o valor "double" da vari�vel
    const char * getTxt();  ///< Obt�m o texto da vari�vel
    TObjeto * getObj();     ///< Obt�m a refer�ncia da vari�vel

// Fun��es set
    void setInt(int valor); ///< Muda vari�vel a partir de int
    void setDouble(double valor); ///< Muda vari�vel a partir de double
    void setTxt(const char * txt); ///< Muda vari�vel a partir de texto
    void addTxt(const char * txt); ///< Adiciona texto na vari�vel
    void setObj(TObjeto * obj); ///< Muda vari�vel a partir de refer�ncia
};

//----------------------------------------------------------------------------
class TBlocoVarNum : public TBlocoVar // Vari�vel num�rica
{
public:
    TBlocoVarNum(TTextoVar * var, const char * nome, double valor);
    virtual ~TBlocoVarNum();
    const char * Tipo() { return "_"; }
    TextoVarTipo TipoVar() { return TextoVarTipoNum; }

// Fun��es get
    bool getBool();         ///< Obt�m o valor "bool" da vari�vel
    int getInt();           ///< Obt�m o valor "int" da vari�vel
    double getDouble();     ///< Obt�m o valor "double" da vari�vel
    const char * getTxt();  ///< Obt�m o texto da vari�vel
    TObjeto * getObj();     ///< Obt�m a refer�ncia da vari�vel

// Fun��es set
    void setInt(int valor); ///< Muda vari�vel a partir de int
    void setDouble(double valor); ///< Muda vari�vel a partir de double
    void setTxt(const char * txt); ///< Muda vari�vel a partir de texto
    void addTxt(const char * txt); ///< Adiciona texto na vari�vel
    void setObj(TObjeto * obj); ///< Muda vari�vel a partir de refer�ncia
private:
    double ValorDouble;
};

//----------------------------------------------------------------------------
class TBlocoVarDec : public TBlocoVar // Vari�vel intdec
{
public:
    static void PreparaIni();
    static void ProcEventos(int TempoDecorrido);
    TBlocoVarDec(TTextoVar * var, const char * nome, int valor);
    virtual ~TBlocoVarDec();
    const char * Tipo() { return "@"; }
    TextoVarTipo TipoVar() { return TextoVarTipoDec; }

// Fun��es get
    bool getBool();         ///< Obt�m o valor "bool" da vari�vel
    int getInt();           ///< Obt�m o valor "int" da vari�vel
    double getDouble();     ///< Obt�m o valor "double" da vari�vel
    const char * getTxt();  ///< Obt�m o texto da vari�vel
    TObjeto * getObj();     ///< Obt�m a refer�ncia da vari�vel

// Fun��es set
    void setInt(int valor); ///< Muda vari�vel a partir de int
    void setDouble(double valor); ///< Muda vari�vel a partir de double
    void setTxt(const char * txt); ///< Muda vari�vel a partir de texto
    void addTxt(const char * txt); ///< Adiciona texto na vari�vel
    void setObj(TObjeto * obj); ///< Muda vari�vel a partir de refer�ncia

private:
    void InsereLista(int valor);///< Adiciona na lista ligada
    void RemoveLista();           ///< Remove da lista ligada
    unsigned short IndiceMenos;   ///< �ndice em VetMenos
    unsigned short IndiceMais;    ///< �ndice em VetMais
    TBlocoVarDec * Antes;         ///< Objeto anterior na lista ligada
    TBlocoVarDec * Depois;        ///< Pr�ximo objeto na lista ligada

    static unsigned int TempoMenos;  ///< Contagem de tempo com VetMenos
    static unsigned int TempoMais;   ///< Contagem de tempo com VetMais
    static TBlocoVarDec ** VetMenos; ///< Primeira lista ligada
    static TBlocoVarDec ** VetMais;  ///< Segunda lista ligada
};

//----------------------------------------------------------------------------
class TBlocoVarRef : public TBlocoVar // Vari�vel ref
{
public:
    TBlocoVarRef(TTextoVar * var, const char * nome, TObjeto * obj);
    virtual ~TBlocoVarRef();
    const char * Tipo() { return "$"; }
    TextoVarTipo TipoVar() { return TextoVarTipoRef; }

// Fun��es get
    bool getBool();         ///< Obt�m o valor "bool" da vari�vel
    int getInt();           ///< Obt�m o valor "int" da vari�vel
    double getDouble();     ///< Obt�m o valor "double" da vari�vel
    const char * getTxt();  ///< Obt�m o texto da vari�vel
    TObjeto * getObj();     ///< Obt�m a refer�ncia da vari�vel

// Fun��es set
    void setInt(int valor); ///< Muda vari�vel a partir de int
    void setDouble(double valor); ///< Muda vari�vel a partir de double
    void setTxt(const char * txt); ///< Muda vari�vel a partir de texto
    void addTxt(const char * txt); ///< Adiciona texto na vari�vel
    void setObj(TObjeto * obj); ///< Muda vari�vel a partir de refer�ncia

    void InsereLista(TObjeto * obj); ///< Adiciona objeto na lista ligada
    void RemoveLista();        ///< Remove objeto da lista ligada
    TObjeto * Objeto;          ///< Objeto que est� na lista
    TBlocoVarRef * ObjAntes;   ///< Objeto anterior da lista
    TBlocoVarRef * ObjDepois;  ///< Pr�ximo objeto da lista
};

//----------------------------------------------------------------------------
#endif
