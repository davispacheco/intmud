#ifndef INSTR_ENUM_H
#define INSTR_ENUM_H

/// Emumera��es de Instr
/** Emumera��es de Instr */
namespace Instr {

//----------------------------------------------------------------------------
enum EndVar
{
    endAlin = 3,
    endProp = 4,
    endIndice = 5,
    endVetor = 6,
    endExtra = 7,
    endNome = 8,
    endVar = 4
};

//----------------------------------------------------------------------------
/// Comandos
/**
    Cada linha de comando � codificada assim:
    - bytes 0,1 = tamanho em bytes; 0 significa fim da lista de comandos
    - byte 2 = comando (vide TComando)
    - byte 3 (Instr::endAlin) = alinhamento (n�vel de identa��o)
    - X bytes (Instr::endVar) = dados do comando (depende do comando)
    .

    A partir de cVariaveis vem as defini��es de vari�veis:
    - byte 4 (Instr::endProp) = propriedades:
      - bit 0=1 se comum
      - bit 1=1 se sav
      .
    - byte 5 (Instr::endIndice)
      - �ndice para os dados extras das vari�veis (express�o)
      - Ou 0 se n�o h� dados extras
      .
    - byte 6 (Instr::endVetor)
      - n�mero de elementos do vetor ou 0 se n�o for vetor
      .
    - byte 7 (Instr::endExtra)
      - tamanho do texto em cTxt1 e cTxt2
      .
    - X bytes (Instr::endNome) = nome da vari�vel em ASCIIZ
    - Y bytes = express�o num�rica, em cConstExp
      - texto em ASCIIZ, em cConstTxt
      - valor num�rico em cConstInt e cConstReal
      .
    .

    Tipos de comandos:
    - Comum: Instru��es comuns (n�o se encaixam em outra categoria)
    - Fluxo: Instru��es de controle de fluxo
    - Var:   Defini��es de vari�veis
    - Extra: Vari�veis extras
    .

    Nos comandos que n�o t�m express�es num�ricas (exceto Herda),
    se houver algum coment�rio, ele vir� ap�s os dados do comando.

    Exemplo,  "fimse # teste" � codificado assim:
              0x08, 0x00, cFimSe, 't', 'e', 's', 't', 'e'
 */
enum Comando
{
// Instru��es comuns
    cHerda,         /**< Comum: Instru��o herda
                        - 1 byte = n�mero de classes
                        - X bytes = nomes das classes em ASCIIZ
                        - S� pode estar no in�cio da lista de comandos */
    cExpr,          ///< Comum: Express�o num�rica pura
    cComent,        ///< Comum: Coment�rio
    cRefVar,        ///< Comum: refvar (refer�ncia a uma vari�vel)

// Instru��es de controle de fluxo
    cSe,            ///< Fluxo: ushort,express�o   se(express�o)
    cSenao1,        ///< Fluxo: ushort             sen�o
    cSenao2,        ///< Fluxo: ushort,express�o   sen�o(express�o)
    cFimSe,         ///< Fluxo:                    fimse
    cEnquanto,      ///< Fluxo: ushort,express�o   enquanto(express�o)
    cEPara,         ///< Fluxo: ushort[3],express�o
    cEFim,          ///< Fluxo: ushort             efim
    cCasoVar,       ///< Fluxo: ushort,express�o   casovar
    cCasoSe,        ///< Fluxo: ushort[2],texto    casose com texto
    cCasoSePadrao,  ///< Fluxo:                    casose sem texto
    cCasoFim,       ///< Fluxo:                    casofim
    cRet1,          ///< Fluxo: ret sem argumentos
    cRet2,          ///< Fluxo: ret com express�o num�rica
    cSair1,         ///< Fluxo: ushort             sair
    cSair2,         ///< Fluxo: ushort,express�o   sair
    cContinuar1,    ///< Fluxo: ushort             continuar
    cContinuar2,    ///< Fluxo: ushort,express�o   continuar
    cTerminar,      ///< Fluxo:                    terminar

// Defini��es de vari�veis
    cVariaveis,         ///< Var: Marca o in�cio das vari�veis
    cTxt1,              ///< Var: Texto de 1 a 256 caracteres
    cTxt2,              ///< Var: Texto de 257 a 512 caracteres
    cInt1,              ///< Var: 1 bit
    cInt8, cUInt8,      ///< Var: 8 bits com e sem sinal
    cInt16, cUInt16,    ///< Var: 16 bits com e sem sinal
    cInt32, cUInt32,    ///< Var: 32 bits com e sem sinal
    cReal,              ///< Var: real - "float"
    cReal2,             ///< Var: real2 - "double"
    cConstNulo,         ///< Var: Constante = nulo
    cConstTxt,          ///< Var: Constante = texto
    cConstNum,          ///< Var: Constante = n�mero
    cConstExpr,         ///< Var: Constante = express�o num�rica
    cConstVar,          ///< Var: Constante do tipo constvar
    cFunc,              ///< Var: Fun��o
    cVarFunc,           ///< Var: Fun��o
        /**< @note Para as vari�veis ap�s cVarFunc, deve-se
            obrigatoriamente usar TVariavel::Criar e TVariavel::Apagar,
            exceto quando TVariavel::Tamanho retorna 0 */
    cIntInc, cIntDec,   ///< Var: intinc e intdec
    cRef,               ///< Var: Refer�ncia para um objeto
                        /**< @sa TVarRef */

// Vari�veis extras
    cListaObj,          ///< Extra: ListaObj
    cListaItem,         ///< Extra: ListaItem
    cTextoTxt,          ///< Extra: TextoTxt
    cTextoPos,          ///< Extra: TextoPos
    cTextoVar,          ///< Extra: TextoVar
    cTextoObj,          ///< Extra: TextoObj
    cNomeObj,           ///< Extra: NomeObj
    cArqDir,            ///< Extra: ArqDir
    cArqLog,            ///< Extra: ArqLog
    cArqProg,           ///< Extra: ArqProg
    cArqExec,           ///< Extra: ArqExec
    cArqSav,            ///< Extra: Salvar
    cArqTxt,            ///< Extra: ArqTxt
    cArqMem,            ///< Extra: ArqMem
    cIntTempo,          ///< Extra: IntTempo
    cIntExec,           ///< Extra: IntExec
    cTelaTxt,           ///< Extra: TelaTxt
    cSocket,            ///< Extra: Socket
    cServ,              ///< Extra: Serv
    cProg,              ///< Extra: Prog
    cDebug,             ///< Extra: Debug
    cIndiceObj,         ///< Extra: IndiceObj
    cIndiceItem,        ///< Extra: IndiceItem
    cDataHora,          ///< Extra: DataHora

// Usado internamente
    cTxtFixo,           ///< Aponta para um texto fixo
    cVarNome,           ///< Para obter nome da vari�vel
    cVarInicio,         ///< Esperando texto logo ap�s ex_varini
    cVarIniFunc,        ///< Mesmo que cVarInicio, por�m para ex_varfunc
    cVarClasse,         ///< TVariavel::endvar = endere�o do objeto TClasse
    cVarObjeto,         ///< TVariavel::endvar = endere�o do objeto TObjeto
    cVarInt,            ///< int local; vide TVariavel::valor_int
    cVarDouble,         ///< double local; vide TVariavel::valor_double
    cTextoVarSub,       ///< Vari�vel de TextoVar
    cTextoObjSub,       ///< Vari�vel de TextoObj

    cTotalComandos      ///< N�mero de comandos - n�o usado
};

//----------------------------------------------------------------------------
/// Idenfificadores usados em express�es num�ricas
/**
    Texto: Usado em textos

    Vari�vel: Nome de vari�vel ou fun��o (um texto)
    - Cada conjunto de vari�veis/fun��es (no estilo x.y.x):
      -  ex_varini + vari�veis/fun��es + ex_varfim
      .
    - Cada vari�vel/fun��o (sem e com argumentos):
      -  nome da vari�vel/fun��o + ex_ponto
      -  nome da vari�vel/fun��o + ex_arg + express�es num�ricas + ex_ponto
      .
    - Colchetes em nomes de vari�veis/fun��es:
      -  ex_abre + express�es num�ricas + ex_fecha
      .
    - Substitui��es:
      -  ex_varabre = ex_varini + ex_abre
      -  ex_varfunc + n�mero da fun��o = ex_varini + nome da fun��o predefinida
      -  ex_varlocal + n�mero da vari�vel = ex_varini (para uma vari�vel local)
      -  ex_varlocal + 255 = ex_varini (para uma vari�vel da classe/objeto)
      -  Nota: vari�vel local � uma vari�vel definida na fun��o
      .
    .

    Operador: Operadores num�ricos

    Interno: Usado internamente em Instr::Codif
*/
enum Expressao
{
    ex_fim,         ///< Fim da vari�vel ou express�o num�rica
    ex_coment,      ///< Marca in�cio de coment�rio (encontrou #)

// Usado em textos
    ex_barra_n,     ///< Texto: \\n
    ex_barra_b,     ///< Texto: \\b
    ex_barra_c,     ///< Texto: \\c
    ex_barra_d,     ///< Texto: \\d

// Nome de vari�vel ou fun��o (um texto)
    ex_varini,      ///< Vari�vel: In�cio do texto
    ex_varfim,      ///< Vari�vel: Fim do texto
    ex_doispontos,  ///< Vari�vel: ":", que separa nome da classe da vari�vel
    ex_ponto,       ///< Vari�vel: Fim do nome da vari�vel
    ex_arg,         ///< Vari�vel: In�cio da lista de argumentos
    ex_varabre,     ///< Vari�vel: In�cio do texto + abre colchetes
    ex_abre,        ///< Vari�vel: Abre colchetes; segue express�o num�rica + ex_fecha
    ex_fecha,       ///< Vari�vel: Fecha colchetes
    ex_varfunc,     ///< Vari�vel: pr�ximo byte � o n�mero da fun��o predefinida
    ex_varlocal,    ///< Vari�vel: (+1 byte) vari�vel/fun��o exceto predefinida

// Valores fixos
    ex_nulo,        ///< Fixo: Valor NULO
    ex_txt,         ///< Fixo: Texto em ASCIIZ
    ex_num0,        ///< Fixo: n�mero 0
    ex_num1,        ///< Fixo: N�mero 1
    ex_num8p,       ///< Fixo: + 1 byte = n�mero 8 bits sem sinal
    ex_num16p,      ///< Fixo: + 2 bytes = n�mero 16 bits sem sinal
    ex_num32p,      ///< Fixo: + 4 bytes = n�mero 32 bits sem sinal
    ex_num8n,       ///< Fixo: + 1 byte = n�mero 8 bits negativo
    ex_num16n,      ///< Fixo: + 2 bytes = n�mero 16 bits negativo
    ex_num32n,      ///< Fixo: + 4 bytes = n�mero 32 bits negativo
    ex_num8hexp,    ///< Fixo: + 1 byte = n�mero hexadecimal 8 bits sem sinal
    ex_num16hexp,   ///< Fixo: + 2 bytes = n�mero hexadecimal 16 bits sem sinal
    ex_num32hexp,   ///< Fixo: + 4 bytes = n�mero hexadecimal 32 bits sem sinal
    ex_num8hexn,    ///< Fixo: + 1 byte = n�mero hexadecimal 8 bits negativo
    ex_num16hexn,   ///< Fixo: + 2 bytes = n�mero hexadecimal 16 bits negativo
    ex_num32hexn,   ///< Fixo: + 4 bytes = n�mero hexadecimal 32 bits negativo
    ex_div1,        ///< Fixo: Divide por 10
    ex_div2,        ///< Fixo: Divide por 100
    ex_div3,        ///< Fixo: Divide por 1000
    ex_div4,        ///< Fixo: Divide por 10000
    ex_div5,        ///< Fixo: Divide por 100000
    ex_div6,        ///< Fixo: Divide por 1000000

// Operadores num�ricos
    exo_ini,        ///< Operador: Marca o in�cio dos operadores
    exo_virgula,    ///< Operador: V�rgula
    exo_virg_expr,  ///< Operador: V�rgula, separando express�es
    exo_neg,        ///< Operador: -a
    exo_exclamacao, ///< Operador: !a
    exo_b_comp,     ///< Operador: ~a
    exo_add_antes,  ///< Operador: ++a
    exo_sub_antes,  ///< Operador: --a
    exo_add_depois, ///< Operador: a++
    exo_sub_depois, ///< Operador: a--
    exo_add_sub1,   ///< Usado em ++ e --
    exo_add_sub2,   ///< Usado em ++ e --
    exo_mul,        ///< Operador: a * b
    exo_div,        ///< Operador: a / b
    exo_porcent,    ///< Operador: a % b
    exo_add,        ///< Operador: a + b
    exo_sub,        ///< Operador: a - b
    exo_b_shl,      ///< Operador: a << b
    exo_b_shr,      ///< Operador: a >> b
    exo_b_e,        ///< Operador: a & b
    exo_b_ouou,     ///< Operador: a ^ b
    exo_b_ou,       ///< Operador: a | b
    exo_menor,      ///< Operador: a < b
    exo_menorigual, ///< Operador: a <= b
    exo_maior,      ///< Operador: a > b
    exo_maiorigual, ///< Operador: a >= b
    exo_igual,      ///< Operador: a == b
    exo_igual2,     ///< Operador: a === b
    exo_diferente,  ///< Operador: a != b
    exo_diferente2, ///< Operador: a !== b
    exo_e,          ///< Operador: a && b
    exo_ou,         ///< Operador: a || b
    exo_atrib,      ///< Operador: a = b
    exo_i_mul,      ///< Operador: a *= b   (segue exo_mul, exo_atrib)
    exo_i_div,      ///< Operador: a /= b   (segue exo_div, exo_atrib)
    exo_i_porcent,  ///< Operador: a %= b   (segue exo_porcent, exo_atrib)
    exo_i_add,      ///< Operador: a += b   (segue exo_add, exo_atrib)
    exo_i_sub,      ///< Operador: a -= b   (segue exo_sub, exo_atrib)
    exo_i_b_shl,    ///< Operador: a <<= b  (segue exo_b_shl, exo_atrib)
    exo_i_b_shr,    ///< Operador: a >>= b  (segue exo_b_shr, exo_atrib)
    exo_i_b_e,      ///< Operador: a &= b   (segue exo_b_e, exo_atrib)
    exo_i_b_ouou,   ///< Operador: a ^= b   (segue exo_b_ouou, exo_atrib)
    exo_i_b_ou,     ///< Operador: a |= b   (segue exo_b_ou, exo_atrib)
    exo_int2,       ///< Operador: Fim de ?
    exo_intint2,    ///< Operador: Fim de ??
    exo_dponto2,    ///< Operador: Fim de :
    exo_fim,        ///< Operador: Marca o fim dos operadores
    exo_int1,       ///< Operador: In�cio de ?
    exo_dponto1,    ///< Operador: In�cio de :
    exo_intint1,    ///< Operador: In�cio de ??
    exo_ee,         ///< Operador: In�cio do operador &&
    exo_ouou,       ///< Operador: In�cio do operador ||

// Usado ao codificar express�es
    ex_var1,        ///< Interno: Processando nome de vari�vel; aceita dois pontos
    ex_var2,        ///< Interno: Processando nome de vari�vel; n�o aceita dois pontos
    ex_var3,        ///< Interno: Processando nome de vari�vel; j� anotou ponto
    ex_colchetes,   ///< Interno: Processando colchetes em nome de vari�vel
    ex_parenteses   ///< Interno: Processando par�nteses
};

//----------------------------------------------------------------------------
}

#endif
