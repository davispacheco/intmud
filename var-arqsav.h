#ifndef VAR_ARQSAV_H
#define VAR_ARQSAV_H

class TVariavel;
class TVarInfo;
class TClasse;
class TObjeto;

//----------------------------------------------------------------------------
class TVarSav /// Vari�vel arqsav
{
public:
    static const TVarInfo * Inicializa();
        ///< Inicializa vari�vel e retorna informa��es
    static void ProcEventos(int tempoespera);
        ///< Processa eventos
    static int Tempo(const char * arqnome);
        ///< Obt�m a quantidade de minutos para expirar
        /**< @return quantidade de minutos ou 0=expirou, -1=nunca expira */

private:
    static bool ObterVar(TVariavel * var, TObjeto * obj, const char * nomevar);
        ///< Obt�m uma vari�vel "sav" a partir do nome e objeto
        /**< @param var Aonde colocar os dados da vari�vel
         *   @param obj Objeto que cont�m a vari�vel
         *   @param nomevar Nome da vari�vel
         *   @return verdadeiro se sucesso, falso se falha (var->defvar=0) */
    static int Ler(TVariavel * v, const char * arqnome);
        ///< L� um arquivo salvo; usado internamente
        /**< @param v Argumentos
         *   @param arqnome Nome do arquivo
         *   @return Quantidade de objetos lidos */
    static int Salvar(TVariavel * v, const char * arqnome, bool senhacod);
        ///< Salva um arquivo; usado internamente
        /**< @param v Argumentos
         *   @param arqnome Nome do arquivo
         *   @param senhacod Se a senha j� est� codificada
         *   @return 1 se conseguiu salvar, 0 se n�o conseguiu */
    static void Senha(char * senhacodif, const char * senha, char fator);
        ///< Codifica senha
    static bool InicVar;
        ///< Se j� inicializou vari�veis
    static int HoraReg;
        ///< Tempo que corresponde a dia, hora e minuto
    static int TempoSav;
        ///< Quanto tempo checou arquivos pendentes pela �ltima vez

    static bool FuncLimpar(TVariavel * v);     ///< Processa fun��o Limpar
    static bool FuncLimpou(TVariavel * v);     ///< Processa fun��o Limpou
    static bool FuncSenhaCod(TVariavel * v);   ///< Processa fun��o SenhaCod
    static bool FuncValido(TVariavel * v);     ///< Processa fun��o Valido
    static bool FuncExiste(TVariavel * v);     ///< Processa fun��o Existe
    static bool FuncSenha(TVariavel * v);      ///< Processa fun��o Senha
    static bool FuncDias(TVariavel * v);       ///< Processa fun��o Dias
    static bool FuncLer(TVariavel * v);        ///< Processa fun��o Ler
    static bool FuncSalvar(TVariavel * v);     ///< Processa fun��o Salvar
    static bool FuncSalvarCod(TVariavel * v);  ///< Processa fun��o SalvarCod
    static bool FuncApagar(TVariavel * v);     ///< Processa fun��o Apagar

    static bool FGetBool(TVariavel * v);
    static int FGetInt(TVariavel * v);
    static double FGetDouble(TVariavel * v);
    static const char * FGetTxt(TVariavel * v);
    static TObjeto * FGetObj(TVariavel * v);
};

//----------------------------------------------------------------------------
class TVarSavDir /// Diret�rios pendentes - para checar arquivos expirados
{
    TVarSavDir(const char * nomedir); ///< Construtor
public:
    ~TVarSavDir();  ///< Destrutor
    static void NovoDir(const char * nomedir);
        ///< Acrescenta um diret�rio na lista de busca
    static bool Checa();
        ///< Checa alguns arquivos pendentes
        /**< @return true se ainda tem arquivos pendentes
             @note Deve ser chamado de tempos em tempos, at� retornar false */
    static void ChecaTudo();
        ///< Checa todos os arquivos pendentes
    static bool ChecaPend();
        ///< Retorna true se tem algum arquivo pendente

private:
    void RBinsert(void);        ///< Insere objeto na RBT
    void RBremove(void);        ///< Remove objeto da RBT
    static TVarSavDir * RBfirst(void); ///< Primeiro objeto da RBT
    static TVarSavDir * RBlast(void);  ///< �ltimo objeto da RBT
    static TVarSavDir * RBnext(TVarSavDir *); ///< Pr�ximo objeto da RBT
    static TVarSavDir * RBprevious(TVarSavDir *); ///< Objeto anterior da RBT
    static int RBcomp(TVarSavDir * x, TVarSavDir * y); ///< Compara objetos
    static TVarSavDir * RBroot;  ///< Objeto raiz
    TVarSavDir *RBleft,*RBright,*RBparent; ///< Objetos filhos e objeto pai
    void RBleft_rotate(void);
    void RBright_rotate(void);
    unsigned char RBcolour;

    static TVarSavDir * Inicio; ///< endere�o do primeiro objeto
    static TVarSavDir * Fim; ///< endere�o do �ltimo objeto
    TVarSavDir * Proximo; ///< Endere�o do pr�ximo objeto

    char * Nome; ///< Nome do diret�rio que deve procurar
};

//----------------------------------------------------------------------------
class TVarSavArq /// Nomes dos arquivos apagados por arqsav por terem expirado
{
public:
    TVarSavArq(const char * nome); ///< Construtor
    ~TVarSavArq();              ///< Destrutor
    TVarSavArq * Antes;         ///< Objeto anterior
    TVarSavArq * Depois;        ///< Pr�ximo objeto
    static TVarSavArq * Inicio; ///< Primeiro objeto
    static TVarSavArq * Fim;    ///< �ltimo objeto
    char Nome[128];             ///< Nome do arquivo
};

//----------------------------------------------------------------------------

#endif
