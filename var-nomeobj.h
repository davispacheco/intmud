#ifndef VAR_NOMEOBJ_H
#define VAR_NOMEOBJ_H

class TVariavel;
class TVarInfo;
class TClasse;
class TObjeto;

//----------------------------------------------------------------------------
/** Trata das vari�veis do tipo NomeObj */
class TVarNomeObj /// Vari�veis NomeObj
{
public:
    static const TVarInfo * Inicializa();
        ///< Inicializa vari�vel e retorna informa��es
    bool Func(TVariavel * v, const char * nome); ///< Fun��o da vari�vel
    int  getValor();    ///< Ler valor num�rico da vari�vel
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

    char NomeObj[64];   ///< Nome do item que est� procurando
    int  Achou;         ///< Quantos itens achou na �ltima busca
    int  Inicio;        ///< N�mero de itens antes
    int  Total;         ///< N�mero m�ximo de itens
};

//----------------------------------------------------------------------------

#endif
