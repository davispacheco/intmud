#ifndef VAR_ARQMEM_H
#define VAR_ARQMEM_H

class TVariavel;
class TVarInfo;
class TClasse;
class TObjeto;

//----------------------------------------------------------------------------
class TVarArqMem
{
private:
    /// Cabe�alho de um bloco
    class TBloco
    {
    public:
        TBloco * Antes; ///< Objeto anterior ou NULL se n�o houver
        TBloco * Depois; ///< Pr�ximo objeto ou NULL se n�o houver
        int Posicao; ///< Posi��o no arquivo do primeiro byte desse bloco
        int Tamanho; ///< Quantidade de bytes desse bloco
    };
    TBloco * Inicio; ///< Primeiro bloco
    TBloco * Fim; ///< �ltimo bloco
    TBloco * PosBloco; ///< Bloco da posi��o atual
    int PosByte; ///< Byte do bloco da posi��o atual
    int ArqByte; ///< Quantos bytes usados no �ltimo bloco

    bool CriarBloco();
        ///< Uso interno: cria um bloco no final do arquivo
        /**< @return true se conseguiu criar, false se arquivo muito grande */
    void ApagarBloco();
        ///< Uso interno: apaga o �ltimo bloco do arquivo
    void Debug();
        ///< Verifica se vari�veis de TArqMem est�o corretas

    static bool FuncAdd(TVariavel * v);          ///< Processa fun��o Add
    static bool FuncAddBin(TVariavel * v);       ///< Processa fun��o AddBin
    static bool FuncEof(TVariavel * v);          ///< Processa fun��o Eof
    static bool FuncEscr(TVariavel * v);         ///< Processa fun��o Escr
    static bool FuncEscrBin(TVariavel * v);      ///< Processa fun��o EscrBin
    static bool FuncLer(TVariavel * v);          ///< Processa fun��o Ler
    static bool FuncLerBin(TVariavel * v);       ///< Processa fun��o LerBin
    static bool FuncLerBinEsp(TVariavel * v);    ///< Processa fun��o LerBinEsp
    bool FuncLerBinComum(TVariavel * v, bool espaco);
            ///< Usado por FuncLerBin e FuncLerBinEsp
    static bool FuncLimpar(TVariavel * v);       ///< Processa fun��o Limpar
    static bool FuncPos(TVariavel * v);          ///< Processa fun��o Pos
    static bool FuncTamanho(TVariavel * v);      ///< Processa fun��o Tamanho
    static bool FuncTruncar(TVariavel * v);      ///< Processa fun��o Truncar

    static int FTamanho(const char * instr);
    static int FTamanhoVetor(const char * instr);
    static void FRedim(TVariavel * v, TClasse * c, TObjeto * o,
            unsigned int antes, unsigned int depois);
    static void FMoverEnd(TVariavel * v, void * destino,
            TClasse * c, TObjeto * o);

public:
    static const TVarInfo * Inicializa();
        ///< Inicializa vari�vel e retorna informa��es
    TVarArqMem() { Criar(); }  ///< Construtor
    ~TVarArqMem() { Apagar(); } ///< Destrutor
    void Criar();           ///< Chamado ao criar objeto
    void Apagar();          ///< Apaga objeto

    int Ler(char * buffer, int tamanho);
        ///< L� a partir da posi��o atual, retorna quantos bytes lidos
    int Escrever(char * buffer, int tamanho);
        ///< Escreve a partir da posi��o atual, retorna quantos bytes escritos
    int Tamanho();
        ///< Retorna o tamanho do arquivo
    int Posicao();
        ///< Retorna a posi��o no arquivo
    void Posicao(int novapos);
        ///< Muda a posi��o no arquivo
    void TruncarZero();
        ///< Apaga tudo que tem no arquivo
    void TruncarPosicao();
        ///< Trunca o arquivo na posi��o atual (apaga tudo que vem depois)

    class TArqLer
    {
    public:
        TArqLer(TVarArqMem * arqmem, bool inicio);
            ///< Inicia a leitura, acerta as vari�veis buffer e tamanho
        void Proximo();
            ///< Passa para o pr�ximo bloco, acerta as vari�veis buffer e tamanho
        void MudaPosicao(const char * posicao);
            ///< Muda posi��o no arquivo
        const char * buffer;
            ///< Buffer com os dados para serem lidos
        int tamanho;
            ///< N�mero de caracteres em buffer ou 0 se n�o houver
    private:
        TBloco * bloco; ///< Bloco atual
        TVarArqMem * arqmem; ///< Objeto ArqMem
    };
};

#endif
