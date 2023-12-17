#ifndef VAR_TEXTOOBJ_H
#define VAR_TEXTOOBJ_H

//----------------------------------------------------------------------------
class TVariavel;
class TVarInfo;
class TClasse;
class TObjeto;
class TTextoObjSub;
class TBlocoObj;

class TTextoObj  /// Vari�veis TextoObj
{
public:
    static const TVarInfo * Inicializa();
        ///< Inicializa vari�vel e retorna informa��es
    void Apagar();          ///< Apaga objeto
    void Limpar();          ///< Apaga o texto do objeto
    void Mover(TTextoObj * destino, TObjeto * o);
        ///< Move objeto para outro lugar
    TBlocoObj * Procura(const char * texto);
        ///< Procura um objeto TIndiceObj a partir do nome
        /**< @param texto Nome a pesquisar
         *   @return Endere�o do objeto, ou 0 se n�o foi encontrado */
    TBlocoObj * ProcIni(const char * nome);
        ///< Semelhante a Procura(), mas procura o primeiro texto
    TBlocoObj * ProcFim(const char * nome);
        ///< Semelhante a Procura(), mas procura o �ltimo texto
    TBlocoObj * ProcAntes(const char * nome);
        ///< Semelhante a Procura(), mas procura o texto anterior
    TBlocoObj * ProcDepois(const char * nome);
        ///< Semelhante a Procura(), mas procura o pr�ximo texto
    void Mudar(const char * nomevar, TObjeto * obj);
        ///< Adiciona/muda/apaga vari�vel
    bool Func(TVariavel * v, const char * nome);
        ///< Fun��o da vari�vel

private:
    bool FuncValor(TVariavel * v);
    bool FuncValorIni(TVariavel * v);
    bool FuncValorFim(TVariavel * v);
    bool FuncNomeVar(TVariavel * v);
    bool FuncMudar(TVariavel * v);
    bool FuncAntes(TVariavel * v);
    bool FuncDepois(TVariavel * v);
    bool FuncIni(TVariavel * v);
    bool FuncFim(TVariavel * v);
    bool FuncLimpar(TVariavel * v);
    bool FuncApagar(TVariavel * v);
    bool FuncTotal(TVariavel * v);

    static int FTamanho(const char * instr);
    static int FTamanhoVetor(const char * instr);
    static void FRedim(TVariavel * v, TClasse * c, TObjeto * o,
            unsigned int antes, unsigned int depois);
    static void FMoverEnd(TVariavel * v, void * destino,
            TClasse * c, TObjeto * o);
    static void FOperadorAtrib(TVariavel * v1, TVariavel * v2);
    static bool FOperadorIgual2(TVariavel * v1, TVariavel * v2);
    static unsigned char FOperadorCompara(TVariavel * v1, TVariavel * v2);

public:
    TBlocoObj * RBroot;  ///< Objeto raiz da RBT
    TTextoObjSub * Inicio; ///< Primeiro objeto TTextoObjSub
    TObjeto * Objeto;       ///< Objeto em que o textoobj lista foi definido
    int Total;  ///< Quantidade de vari�veis
};

//----------------------------------------------------------------------------
class TTextoObjSub /// Para acessar uma vari�vel de textoobj
{
public:
    static const TVarInfo * Inicializa();
        ///< Inicializa vari�vel e retorna informa��es
    void Criar(TTextoObj * var); ///< Adiciona objeto em um textoobj
    void Apagar();      ///< Retira objeto de um textoobj
    void Mover(TTextoObjSub * destino);
        ///< Move bloco para outro lugar

    int getValor();             ///< Retorna valor como int
    TObjeto * getObj();         ///< Retorna valor como TObjeto
    void setObj(TObjeto * obj); ///< Muda o valor
    TTextoObj * TextoObj;       ///< A qual textoobj pertence
    TTextoObjSub * Antes;       ///< Objeto anterior
    TTextoObjSub * Depois;      ///< Pr�ximo objeto
    char NomeVar[64];           ///< Nome da vari�vel

private:
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
    static TObjeto * FGetObj(TVariavel * v);
    static void FOperadorAtrib(TVariavel * v1, TVariavel * v2);
    static bool FOperadorIgual2(TVariavel * v1, TVariavel * v2);
    static unsigned char FOperadorCompara(TVariavel * v1, TVariavel * v2);
};

//----------------------------------------------------------------------------
class TBlocoObj /// Bloco de texto de um objeto TTextoObj
{
public:
    void InsereLista(TObjeto * obj); ///< Adiciona objeto na lista ligada
    void RemoveLista();        ///< Remove objeto da lista ligada
    void Apagar();              ///< Apaga objeto
    void Mover(TBlocoObj * destino);
        ///< Move bloco para outro lugar
        /**< @param destino Endere�o destino
         *   @note Usado por TGrupoVar */
    void MoveTextoObj(TTextoObj * textoobj);
        ///< Usado por TTextoObj::Mover, para mudar TBlocoObj::TextoObj
    void FuncApagarSub();
        ///< Usado por TTextoObj::FuncApagar, para marcar para exclus�o

// �rvore organizada por TBlocoObj::Texto
    void RBinsert(void);        ///< Insere objeto na RBT
    void RBremove(void);        ///< Remove objeto da RBT
    TBlocoObj * RBfirst(void);  ///< Primeiro objeto da RBT
    TBlocoObj * RBlast(void);   ///< �ltimo objeto da RBT
    static TBlocoObj * RBnext(TBlocoObj *); ///< Pr�ximo objeto da RBT
    static TBlocoObj * RBprevious(TBlocoObj *); ///< Objeto anterior da RBT
    static int RBcomp(TBlocoObj * x, TBlocoObj * y); ///< Compara objetos
    void RBleft_rotate(void);
    void RBright_rotate(void);

    TObjeto * Objeto;       ///< Objeto que est� na lista
    TBlocoObj * ObjAntes;   ///< Objeto anterior da lista
    TBlocoObj * ObjDepois;  ///< Pr�ximo objeto da lista

    //static TBlocoObj * RBroot;  ///< Objeto raiz
    TBlocoObj *RBparent;    ///< Objeto objeto pai
    TBlocoObj *RBleft,*RBright; ///< Objetos filhos
    TTextoObj *TextoObj;    ///< Vari�vel TextoObj que cont�m o bloco (RBT)
    unsigned char RBcolour; ///< Bit 0=cor, bit 1: 0=RBT, 1=somente texto

    char NomeVar[1];        ///< Nome da vari�vel, em ASCIIZ
};

//----------------------------------------------------------------------------
#endif
