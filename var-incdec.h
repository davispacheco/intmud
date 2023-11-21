#ifndef VAR_INCDEC_H
#define VAR_INCDEC_H

class TVariavel;
class TVarInfo;

//----------------------------------------------------------------------------
/** Trata das vari�veis intinc e intdec */
class TVarIncDec /// Vari�veis intinc e intdec
{
public:
    int getInc(int numfunc); ///< Obt�m o valor de intinc
    int getDec(int numfunc); ///< Obt�m o valor de intdec
    void setInc(int numfunc, int valor); ///< Muda o valor de intinc
    void setDec(int numfunc, int valor); ///< Muda o valor de intdec
    bool FuncInc(TVariavel * v, const char * nome);
        ///< Fun��es de intinc
    bool FuncDec(TVariavel * v, const char * nome);
        ///< Fun��es de intdec
    static bool FuncVetorInc(TVariavel * v, const char * nome);
        ///< Fun��es de vetores de intinc
    static bool FuncVetorDec(TVariavel * v, const char * nome);
        ///< Fun��es de vetores de intdec

    static const TVarInfo * InicializaInc();
        ///< Retorna informa��es de intinc
    static const TVarInfo * InicializaDec();
        ///< Retorna informa��es de intdec
private:
    static int FTamanho(const char * instr);
    static int FTamanhoVetor(const char * instr);
    static void FRedimInc(TVariavel * v, TClasse * c, TObjeto * o,
            unsigned int antes, unsigned int depois);
    static void FRedimDec(TVariavel * v, TClasse * c, TObjeto * o,
            unsigned int antes, unsigned int depois);
    static void FMoverEnd(TVariavel * v, void * destino,
            TClasse * c, TObjeto * o);
    static bool FGetBoolInc(TVariavel * v);
    static bool FGetBoolDec(TVariavel * v);
    static int FGetIntInc(TVariavel * v);
    static int FGetIntDec(TVariavel * v);
    static double FGetDoubleInc(TVariavel * v);
    static double FGetDoubleDec(TVariavel * v);
    static const char * FGetTxtInc(TVariavel * v);
    static const char * FGetTxtDec(TVariavel * v);
    static void FOperadorAtribInc(TVariavel * v);
    static void FOperadorAtribDec(TVariavel * v);

    int valor; ///< Tempo, usando tanto em intinc quanto em intdec
};

//----------------------------------------------------------------------------

#endif
