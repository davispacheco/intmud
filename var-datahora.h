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
    void LerSav(const char * texto);
        ///< Atualiza datahora com o valor salvo em arqsav
    void SalvarSav(char * texto);
        ///< Prepara um texto com data e hora para arqsav

private:
    void Mover(TVarDataHora * destino);
        ///< Move para outro lugar
    int  getInt(int numfunc);
        ///< Ler o valor num�rico da vari�vel como int
    double getDouble(int numfunc);
        ///< Ler o valor num�rico da vari�vel como double

    int DiasMes();          ///< Calcula quantos dias tem no m�s
    int DataNum();          ///< Calcula o n�mero de dias desde 1/1/1
    void NumData(int dias); ///< Obt�m dia/m�s/ano a partir do n�mero de dias
    unsigned short Ano;     ///< Vari�vel ano
    unsigned char Mes;      ///< Vari�vel mes
    unsigned char Dia;      ///< Vari�vel dia
    unsigned char Hora;     ///< Vari�vel hora
    unsigned char Min;      ///< Vari�vel min
    unsigned char Seg;      ///< Vari�vel seg

    static bool FuncAgora(TVariavel * v); ///< Processa fun��o Agora
    static bool FuncAno(TVariavel * v); ///< Processa fun��o Ano
    static bool FuncAntes(TVariavel * v); ///< Processa fun��o Antes
    static bool FuncBissexto(TVariavel * v); ///< Processa fun��o Bissexto
    static bool FuncDepois(TVariavel * v); ///< Processa fun��o Depois
    static bool FuncDia(TVariavel * v); ///< Processa fun��o Dia
    static bool FuncDiaSem(TVariavel * v); ///< Processa fun��o DiaSem
    static bool FuncHora(TVariavel * v); ///< Processa fun��o Hora
    static bool FuncMes(TVariavel * v); ///< Processa fun��o Mes
    static bool FuncMin(TVariavel * v); ///< Processa fun��o Min
    static bool FuncNovaData(TVariavel * v); ///< Processa fun��o NovaData
    static bool FuncNovaHora(TVariavel * v); ///< Processa fun��o NovaHora
    static bool FuncNumDias(TVariavel * v); ///< Processa fun��o NumDias
    static bool FuncNumSeg(TVariavel * v); ///< Processa fun��o NumSeg
    static bool FuncNumTotal(TVariavel * v); ///< Processa fun��o NumTotal
    static bool FuncSeg(TVariavel * v); ///< Processa fun��o Seg


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
    static void FOperadorAtrib(TVariavel * v1, TVariavel * v2);
    static bool FOperadorIgual2(TVariavel * v1, TVariavel * v2);
    static unsigned char FOperadorCompara(TVariavel * v1, TVariavel * v2);
};

//----------------------------------------------------------------------------

#endif
