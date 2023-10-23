#ifndef VAR_ARQDIR_H
#define VAR_ARQDIR_H

#include <dirent.h>
#ifdef __WIN32__
#include <windows.h>
#endif

class TVariavel;
class TVarInfo;
class TClasse;
class TObjeto;

//----------------------------------------------------------------------------
class TVarArqDir /// Vari�vel arqdir
{
public:
    static const TVarInfo * Inicializa();
            ///< Inicializa vari�vel e retorna informa��es
    void Criar();
            ///< Chamado ao criar objeto
    void Apagar();
            ///< Chamado ao apagar objeto
    bool Func(TVariavel * v, const char * nome);
            ///< Fun��o da vari�vel
    void Proximo(); ///< Passa para a pr�xima entrada
#ifdef __WIN32__
    HANDLE wdir; ///< Diret�rio sendo verificado, ou 0 se nenhum
#else
    DIR * dir; ///< Diret�rio sendo verificado, ou 0 se nenhum
#endif
    char arqdir[258]; ///< Nome da entrada encontrada, se dir!=0
    char arqtipo;     ///< Letra que indica o tipo de arquivo, se dir!=0

private:
    bool FuncLin(TVariavel * v);
    bool FuncTexto(TVariavel * v);
    bool FuncDepois(TVariavel * v);
    bool FuncBarra(TVariavel * v);
    bool FuncAbrir(TVariavel * v);
    bool FuncFechar(TVariavel * v);
    bool FuncTipo(TVariavel * v);
    bool FuncTamanho(TVariavel * v);
    bool FuncMtempo(TVariavel * v);
    bool FuncAtempo(TVariavel * v);
    bool FuncApagarDir(TVariavel * v);
    bool FuncCriarDir(TVariavel * v);
    bool FuncApagar(TVariavel * v);
    bool FuncRenomear(TVariavel * v);

    static int FTamanho(const char * instr);
    static int FTamanhoVetor(const char * instr);
    static void FRedim(TVariavel * v, TClasse * c, TObjeto * o,
            unsigned int antes, unsigned int depois);
    static void FMoverEnd(TVariavel * v, void * destino,
            TClasse * c, TObjeto * o);
};

//----------------------------------------------------------------------------

#endif
