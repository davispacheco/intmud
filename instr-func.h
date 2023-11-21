#ifndef INSTR_FUNC_H
#define INSTR_FUNC_H

class TVariavel;

/// Fun��es predefinidas da linguagem
/** Fun��es predefinidas da linguagem */
namespace InstrFunc {

bool FuncArg0(TVariavel * v); ///< Fun��o arg0
bool FuncArg1(TVariavel * v); ///< Fun��o arg1
bool FuncArg2(TVariavel * v); ///< Fun��o arg2
bool FuncArg3(TVariavel * v); ///< Fun��o arg3
bool FuncArg4(TVariavel * v); ///< Fun��o arg4
bool FuncArg5(TVariavel * v); ///< Fun��o arg5
bool FuncArg6(TVariavel * v); ///< Fun��o arg6
bool FuncArg7(TVariavel * v); ///< Fun��o arg7
bool FuncArg8(TVariavel * v); ///< Fun��o arg8
bool FuncArg9(TVariavel * v); ///< Fun��o arg9
bool FuncArgs(TVariavel * v); ///< N�mero de argumentos (args)
bool FuncCriar(TVariavel * v); ///< Criar objeto (fun��o criar)
bool FuncApagar(TVariavel * v); ///< Apagar objeto (fun��o apagar)
bool FuncMatPi(TVariavel * v); ///< Fun��o matpi
bool FuncEste(TVariavel * v); ///< Objeto "este"
bool FuncIntPos(TVariavel * v); ///< Fun��o intpos
bool FuncIntAbs(TVariavel * v); ///< Fun��o intabs
bool FuncInt(TVariavel * v); ///< Fun��o int
bool FuncIntDiv(TVariavel * v); ///< Fun��o intdiv
bool FuncMatSin(TVariavel * v); ///< Fun��o matsin
bool FuncMatCos(TVariavel * v); ///< Fun��o matcos
bool FuncMatTan(TVariavel * v); ///< Fun��o mattan
bool FuncMatAsin(TVariavel * v); ///< Fun��o matasin
bool FuncMatAcos(TVariavel * v); ///< Fun��o matacos
bool FuncMatAtan(TVariavel * v); ///< Fun��o matatan
bool FuncMatExp(TVariavel * v); ///< Fun��o matexp
bool FuncMatLog(TVariavel * v); ///< Fun��o matlog
bool FuncMatRaiz(TVariavel * v); ///< Fun��o matraiz
bool FuncMatCima(TVariavel * v); ///< Fun��o matcima
bool FuncMatBaixo(TVariavel * v); ///< Fun��o matbaixo
bool FuncMatRad(TVariavel * v); ///< Fun��o matrad
bool FuncMatDeg(TVariavel * v); ///< Fun��o matdeg
bool FuncMatPow(TVariavel * v); ///< Fun��o mathpow
bool FuncIntBit(TVariavel * v); ///< Fun��o intbit
bool FuncIntBitH(TVariavel * v); ///< Fun��o intbith
bool FuncTxtBit(TVariavel * v); ///< Fun��o txtbit
bool FuncTxtBitH(TVariavel * v); ///< Fun��o txtbith
bool FuncTxtHex(TVariavel * v); ///< Fun��o txthex
bool FuncIntMax(TVariavel * v); ///< Fun��o intmax
bool FuncIntMin(TVariavel * v); ///< Fun��o intmin
bool FuncRand(TVariavel * v); ///< Fun��o rand
bool FuncRef(TVariavel * v); ///< Refer�ncia (ref)
bool FuncTxtTipoVar(TVariavel * v); ///< Fun��o txttipovar
bool FuncTxtNum(TVariavel * v); ///< Fun��o txtnum
bool FuncIntSub(TVariavel * v); ///< Fun��o intsub
bool FuncIntSubLin(TVariavel * v); ///< Fun��o intsublin
bool FuncTxt(TVariavel * v); ///< Fun��o txt
bool FuncTxtSub(TVariavel * v); ///< Fun��o txtsub
bool FuncTxtSubLin(TVariavel * v); ///< Fun��o txtsublin
bool FuncTxtFim(TVariavel * v); ///< Fun��o txtfim
bool FuncTxt1(TVariavel * v); ///< Fun��o txt1
bool FuncTxt2(TVariavel * v); ///< Fun��o txt2
bool FuncTxtCor(TVariavel * v); ///< Fun��o txtcor
bool FuncTxtMai(TVariavel * v); ///< Fun��o txtmai
bool FuncTxtMaiIni(TVariavel * v); ///< Fun��o txtmaiini
bool FuncTxtMin(TVariavel * v); ///< Fun��o txtmin
bool FuncTxtMaiMin(TVariavel * v); ///< Fun��o txtmaimin
bool FuncTxtFiltro(TVariavel * v); ///< Fun��o txtfiltro
bool FuncTxtSha1Bin(TVariavel * v); ///< Fun��o txtsha1bin
bool FuncTxtSha1(TVariavel * v); ///< Fun��o txtsha1
bool FuncTxtMd5(TVariavel * v); ///< Fun��o txtms5
bool FuncTxtNome(TVariavel * v); ///< Fun��o txtnome
bool FuncTxtInvis(TVariavel * v); ///< Fun��o txtinvis
bool FuncTxtCod(TVariavel * v); ///< Fun��o txtcod
bool FuncTxtDec(TVariavel * v); ///< Fun��o txtdec
bool FuncTxtVis(TVariavel * v); ///< Fun��o txtvis
bool FuncTxtUrlCod(TVariavel * v); ///< Fun��o txturlcod
bool FuncTxtUrlDec(TVariavel * v); ///< Fun��o txturldec
bool FuncTxtE(TVariavel * v); ///< Fun��o txte
bool FuncTxtS(TVariavel * v); ///< Fun��o txts
bool FuncTxtRev(TVariavel * v); ///< Fun��o txtrev
bool FuncTxtMudaMai(TVariavel * v); ///< Fun��o txtmudamai
bool FuncTxtCopiaMai(TVariavel * v); ///< Fun��o txtcopiamai
bool FuncEsp(TVariavel * v); ///< Fun��o txtesp
bool FuncTxtRepete(TVariavel * v); ///< Fun��o txtrepete
bool FuncIntNome(TVariavel * v); ///< Fun��o intnome
bool FuncIntSenha(TVariavel * v); ///< Fun��o intsenha
bool FuncTxtRemove(TVariavel * v); ///< Fun��o txtremove
bool FuncTxtConv(TVariavel * v); ///< Fun��o txtconv
bool FuncTxtChr(TVariavel * v); ///< Fun��o txtchr
bool FuncIntChr(TVariavel * v); ///< Fun��o intchr
bool FuncIntDist(TVariavel * v); ///< Fun��o intdist
bool FuncIntDistMai(TVariavel * v); ///< Fun��o intdistmai
bool FuncIntDistDif(TVariavel * v); ///< Fun��o intdistdif
bool FuncTxtProc(TVariavel * v); ///< Fun��o txtproc
bool FuncTxtProcMai(TVariavel * v); ///< Fun��o txtprocmai
bool FuncTxtProcDif(TVariavel * v); ///< Fun��o txtprocdif
bool FuncTxtProcLin(TVariavel * v); ///< Fun��o txtproclin
bool FuncTxtProcLinMai(TVariavel * v); ///< Fun��o txtproclinmai
bool FuncTxtProcLinDif(TVariavel * v); ///< Fun��o txtproclindif
bool FuncTxtTroca(TVariavel * v); ///< Fun��o txttroca
bool FuncTxtTrocaMai(TVariavel * v); ///< Fun��o txttrocaMai
bool FuncTxtTrocaDif(TVariavel * v); ///< Fun��o txttrocaDif
bool FuncTxtSepara(TVariavel * v); ///< Fun��o txtsepara
bool FuncObjAntes(TVariavel * v); ///< Fun��o objantes
bool FuncObjDepois(TVariavel * v); ///< Fun��o objdepois
bool FuncTotal(TVariavel * v); ///< Fun��o inttotal
bool FuncVarTroca(TVariavel * v); ///< Fun��o vartroca
bool FuncVarTrocaCod(TVariavel * v); ///< Fun��o vartrocacod

}

#endif
