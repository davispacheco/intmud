#ifndef VAR_ARQLOG_H
#define VAR_ARQLOG_H

class TVariavel;
class TVarInfo;
class TClasse;
class TObjeto;

//----------------------------------------------------------------------------
class TVarArqLog /// Vari�vel arqlog
{
public:
    static const TVarInfo * Inicializa();
        ///< Inicializa vari�vel e retorna informa��es
    void Criar();           ///< Chamado ao criar objeto
    void Apagar();          ///< Apaga objeto
    void Mover(TVarArqLog * destino); ///< Move para outro lugar
    int  getValor();        ///< Ler valor num�rico da vari�vel
    static int TempoEspera(int tempodecorrido);
    bool Func(TVariavel * v, const char * nome); ///< Fun��o da vari�vel
private:
    bool FuncMsg(TVariavel * v);    ///< Processa fun��o Msg
    bool FuncFechar(TVariavel * v); ///< Processa fun��o Fechar
    bool FuncValido(TVariavel * v); ///< Processa fun��o Valido
    bool FuncExiste(TVariavel * v); ///< Processa fun��o Existe
    bool FuncAbrir(TVariavel * v);  ///< Processa fun��o Abrir

    static int FTamanho(const char * instr);
    static int FTamanhoVetor(const char * instr);
    static void FRedim(TVariavel * v, TClasse * c, TObjeto * o,
            unsigned int antes, unsigned int depois);
    static void FMoverEnd(TVariavel * v, void * destino,
            TClasse * c, TObjeto * o);

    void Fechar();      ///< Fecha arquivo
    static int Tempo;   ///< Quanto tempo para atualizar arquivos
    static TVarArqLog * Inicio; ///< Primeiro objeto com arq>=0
    TVarArqLog * Antes; ///< Objeto anterior com arq>=0
    TVarArqLog * Depois;///< Pr�ximo objeto com arq>=0
    int  arq;           ///< Para acessar o arquivo
    int  pontlog;       ///< Ponteiro para anotar texto em buflog
    char buflog[2048];  ///< Texto a ser gravado
                        /**< @note Deve ser a �ltima vari�vel da classe */
};

//----------------------------------------------------------------------------

#endif
