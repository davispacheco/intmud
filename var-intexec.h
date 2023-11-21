#ifndef VAR_INTEXEC_H
#define VAR_INTEXEC_H

class TVariavel;
class TVarInfo;
class TObjeto;

//----------------------------------------------------------------------------
/** Executa eventos */
class TVarIntExec /// Vari�veis intexec
{
public:
    static const TVarInfo * Inicializa();
        ///< Inicializa vari�vel e retorna informa��es
    static void ProcEventos(); ///< Processa eventos pendentes
    int  getValor(); ///< Ler valor da vari�vel
    void setValor(int valor); ///< Mudar valor da vari�vel
    void Mover(TVarIntExec * destino); ///< Move para outro lugar
    void EndObjeto(TClasse * c, TObjeto * o);

    const char * defvar;///< Como foi definida a vari�vel
    union {
        TClasse * endclasse;///< Em que classe est� definido
        TObjeto * endobjeto;///< Em que objeto est� definido
    };
    bool b_objeto;          ///< O que usar: true=endobjeto, false=endclasse
    unsigned char indice;   ///< �ndice no vetor

private:
    static int FTamanho(const char * instr);
    static int FTamanhoVetor(const char * instr);
    static void FRedim(TVariavel * v, TClasse * c, TObjeto * o,
            unsigned int antes, unsigned int depois);
    static void FMoverEnd(TVariavel * v, void * destino,
            TClasse * c, TObjeto * o);
    static void FMoverDef(TVariavel * v);
    static bool FGetBool(TVariavel * v);
    static int FGetInt(TVariavel * v);
    static double FGetDouble(TVariavel * v);
    static const char * FGetTxt(TVariavel * v);
    static void FOperadorAtrib(TVariavel * v);

    TVarIntExec * Antes;        ///< Objeto anterior na lista ligada
    TVarIntExec * Depois;        ///< Pr�ximo objeto na lista ligada
    static TVarIntExec * Inicio; ///< Primeiro item da lista ligada
    static TVarIntExec * Fim; ///< �ltimo item da lista ligada
};

//----------------------------------------------------------------------------

#endif
