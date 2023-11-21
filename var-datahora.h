#ifndef VAR_DATAHORA_H
#define VAR_DATAHORA_H

class TVariavel;
class TVarInfo;
enum TVarTipo : unsigned char;
class TClasse;
class TObjeto;

//----------------------------------------------------------------------------
class TVarDataHora /// Data e hora
{
public:
    static const TVarInfo * Inicializa();
        ///< Inicializa vari�vel e retorna informa��es
    void Mover(TVarDataHora * destino);
            ///< Move para outro lugar
    int  Compara(TVarDataHora * v);
            ///< Operador de compara��o
    bool Func(TVariavel * v, const char * nome);
            ///< Fun��o da vari�vel
    int  getInt(int numfunc);
            ///< Ler o valor num�rico da vari�vel como int
    double getDouble(int numfunc);
            ///< Ler o valor num�rico da vari�vel como double
    void setInt(int numfunc, int valor);
            ///< Mudar o valor num�rico da vari�vel como int
    void setDouble(int numfunc, double valor);
            ///< Mudar o valor num�rico da vari�vel como double
    void LerSav(const char * texto);
            ///< Atualiza datahora com o valor salvo em arqsav
    void SalvarSav(char * texto);
            ///< Prepara um texto com data e hora para arqsav

    int DiasMes();          ///< Calcula quantos dias tem no m�s
    int DataNum();          ///< Calcula o n�mero de dias desde 1/1/1
    void NumData(int dias); ///< Obt�m dia/m�s/ano a partir do n�mero de dias
    unsigned short Ano;     ///< Vari�vel ano
    unsigned char Mes;      ///< Vari�vel mes
    unsigned char Dia;      ///< Vari�vel dia
    unsigned char Hora;     ///< Vari�vel hora
    unsigned char Min;      ///< Vari�vel min
    unsigned char Seg;      ///< Vari�vel seg

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
    static void FOperadorAtrib(TVariavel * v);
};

//----------------------------------------------------------------------------

#endif
