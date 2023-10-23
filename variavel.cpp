/* Este arquivo � software livre; voc� pode redistribuir e/ou
 * modificar nos termos das licen�as GPL ou LGPL. Vide arquivos
 * COPYING e COPYING2.
 *
 * This file is free software; you can redistribute it and/or
 * modify it under the terms of the GPL or the LGP licenses.
 * See files COPYING e COPYING2.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <assert.h>
#include "variavel.h"
#include "instr.h"
#include "instr-enum.h"
#include "classe.h"
#include "objeto.h"
#include "var-listaobj.h"
#include "var-texto.h"
#include "var-textovar.h"
#include "var-textoobj.h"
#include "var-arqdir.h"
#include "var-arqlog.h"
#include "var-arqprog.h"
#include "var-arqexec.h"
#include "var-arqsav.h"
#include "var-arqtxt.h"
#include "var-arqmem.h"
#include "var-nomeobj.h"
#include "var-telatxt.h"
#include "var-socket.h"
#include "var-serv.h"
#include "var-prog.h"
#include "var-debug.h"
#include "var-indiceobj.h"
#include "var-datahora.h"
#include "var-basico.h"
#include "var-outros.h"
#include "var-ref.h"
#include "var-incdec.h"
#include "var-inttempo.h"
#include "var-intexec.h"
#include "misc.h"

TVarInfo * TVariavel::VarInfo = nullptr;

//----------------------------------------------------------------------------
TVarInfo::TVarInfo()
{
    FTamanho = FTamanho0;
    FTamanhoVetor = FTamanho0;
    FTipo = FTipoOutros;
    FRedim = FRedim0;
    FMoverEnd = FMoverEnd0;
    FMoverDef = FMoverDef0;
    FFuncVetor = FFuncVetorFalse;
}

//----------------------------------------------------------------------------
TVarInfo::TVarInfo(int (*fTamanho)(const char * instr),
        int (*fTamanhoVetor)(const char * instr),
        TVarTipo (*fTipo)(TVariavel * v),
        void (*fRedim)(TVariavel * v, TClasse * c, TObjeto * o,
                unsigned int antes, unsigned int depois),
        void (*fMoverEnd)(TVariavel * v, void * destino,
                TClasse * c, TObjeto * o),
        void (*fMoverDef)(TVariavel * v),
        bool (*fFuncVetor)(TVariavel * v, const char * nome))
{
    FTamanho = fTamanho;
    FTamanhoVetor = fTamanhoVetor;
    FTipo = fTipo;
    FRedim = fRedim;
    FMoverEnd = fMoverEnd;
    FMoverDef = fMoverDef;
    FFuncVetor = fFuncVetor;
}

//----------------------------------------------------------------------------
int TVarInfo::FTamanho0(const char * instr)
{
    return 0;
}

//----------------------------------------------------------------------------
TVarTipo TVarInfo::FTipoOutros(TVariavel * v)
{
    return varOutros;
}

//----------------------------------------------------------------------------
TVarTipo TVarInfo::FTipoInt(TVariavel * v)
{
    return varInt;
}

//----------------------------------------------------------------------------
TVarTipo TVarInfo::FTipoDouble(TVariavel * v)
{
    return varDouble;
}

//----------------------------------------------------------------------------
TVarTipo TVarInfo::FTipoTxt(TVariavel * v)
{
    return varTxt;
}

//----------------------------------------------------------------------------
TVarTipo TVarInfo::FTipoObj(TVariavel * v)
{
    return varObj;
}

//----------------------------------------------------------------------------
void TVarInfo::FRedim0(TVariavel * v, TClasse * c, TObjeto * o,
            unsigned int antes, unsigned int depois)
{
    v->endvar = nullptr;
}

//----------------------------------------------------------------------------
void TVarInfo::FMoverEnd0(TVariavel * v, void * destino, TClasse * c, TObjeto * o)
{
}

//----------------------------------------------------------------------------
void TVarInfo::FMoverDef0(TVariavel * v)
{
}

//----------------------------------------------------------------------------
bool TVarInfo::FFuncVetorFalse(TVariavel * v, const char * nome)
{
    return false;
}

//----------------------------------------------------------------------------
void TVariavel::Inicializa()
{
    if (VarInfo)
        return;
    VarInfo = new TVarInfo[Instr::cTotalComandos];

    //TBlocoVarDec::PreparaIni();
    TExec::Inicializa();

// Vari�veis
    VarInfo[Instr::cTxt1] =     *VarBaseTxt1();
    VarInfo[Instr::cTxt2] =     *VarBaseTxt2();
    VarInfo[Instr::cInt1] =     *VarBaseInt1();
    VarInfo[Instr::cInt8] =     *VarBaseInt8();
    VarInfo[Instr::cUInt8] =    *VarBaseUInt8();
    VarInfo[Instr::cInt16] =    *VarBaseInt16();
    VarInfo[Instr::cUInt16] =   *VarBaseUInt16();
    VarInfo[Instr::cInt32] =    *VarBaseInt32();
    VarInfo[Instr::cUInt32] =   *VarBaseUInt32();
    VarInfo[Instr::cReal] =     *VarBaseReal();
    VarInfo[Instr::cReal2] =    *VarBaseReal2();
    VarInfo[Instr::cConstNulo] =*VarOutrosConstNulo();
    VarInfo[Instr::cConstTxt] = *VarOutrosConstTxt();
    VarInfo[Instr::cConstNum] = *VarOutrosConstNum();
    VarInfo[Instr::cConstExpr]= *VarOutrosConstExpr();
    VarInfo[Instr::cConstVar] = *VarOutrosConstVar();
    VarInfo[Instr::cFunc] =     *VarOutrosFunc();
    VarInfo[Instr::cVarFunc] =  *VarOutrosVarFunc();
    VarInfo[Instr::cIntInc] =   *TVarIncDec::InicializaInc();
    VarInfo[Instr::cIntDec] =   *TVarIncDec::InicializaDec();
    VarInfo[Instr::cRef] =      *TVarRef::Inicializa();

// Vari�veis extras
    VarInfo[Instr::cListaObj] = *TListaObj::Inicializa();
    VarInfo[Instr::cListaItem] =*TListaItem::Inicializa();
    VarInfo[Instr::cTextoTxt] = *TTextoTxt::Inicializa();
    VarInfo[Instr::cTextoPos] = *TTextoPos::Inicializa();
    VarInfo[Instr::cTextoVar] = *TTextoVar::Inicializa();
    VarInfo[Instr::cTextoObj] = *TTextoObj::Inicializa();
    VarInfo[Instr::cNomeObj] =  *TVarNomeObj::Inicializa();
    VarInfo[Instr::cArqDir] =   *TVarArqDir::Inicializa();
    VarInfo[Instr::cArqLog] =   *TVarArqLog::Inicializa();
    VarInfo[Instr::cArqProg] =  *TVarArqProg::Inicializa();
    VarInfo[Instr::cArqExec] =  *TVarArqExec::Inicializa();
    VarInfo[Instr::cArqSav] =   *TVarSav::Inicializa();
    VarInfo[Instr::cArqTxt] =   *TVarArqTxt::Inicializa();
    VarInfo[Instr::cArqMem] =   *TVarArqMem::Inicializa();
    VarInfo[Instr::cIntTempo] = *TVarIntTempo::Inicializa();
    VarInfo[Instr::cIntExec] =  *TVarIntExec::Inicializa();
    VarInfo[Instr::cTelaTxt] =  *TVarTelaTxt::Inicializa();
    VarInfo[Instr::cSocket] =   *TVarSocket::Inicializa();
    VarInfo[Instr::cServ] =     *TVarServ::Inicializa();
    VarInfo[Instr::cProg] =     *TVarProg::Inicializa();
    VarInfo[Instr::cDebug] =    *TVarDebug::Inicializa();
    VarInfo[Instr::cIndiceObj] = *TIndiceObj::Inicializa();
    VarInfo[Instr::cIndiceItem] = *TIndiceItem::Inicializa();
    VarInfo[Instr::cDataHora] = *TVarDataHora::Inicializa();

    VarInfo[Instr::cTxtFixo] =   *VarOutrosTxtFixo();
    VarInfo[Instr::cVarNome] =   *VarOutrosVarNome();
    VarInfo[Instr::cVarInicio] = *VarOutrosVarInicio();
    VarInfo[Instr::cVarIniFunc] =*VarOutrosVarIniFunc();
    VarInfo[Instr::cVarClasse] = *VarOutrosVarClasse();
    VarInfo[Instr::cVarObjeto] = *VarOutrosVarObjeto();
    VarInfo[Instr::cVarInt] =    *VarOutrosVarInt();
    VarInfo[Instr::cTextoVarSub] =*TTextoVarSub::Inicializa();
    VarInfo[Instr::cTextoObjSub] =*TTextoObjSub::Inicializa();
}

//----------------------------------------------------------------------------
TVariavel::TVariavel()
{
    defvar = nullptr;
    nomevar = nullptr;
    endvar = nullptr;
    tamanho = 0;
    indice = 0;
    numbit = 0;
    numfunc = 0;
}

//----------------------------------------------------------------------------
void TVariavel::Limpar()
{
    defvar = nullptr;
    nomevar = nullptr;
    endvar = nullptr;
    tamanho = 0;
    indice = 0;
    numbit = 0;
    numfunc = 0;
}

//------------------------------------------------------------------------------
bool TVariavel::getBool()
{
    if (indice==0xFF) // Vetor
        return false;
    switch (defvar[2])
    {
// Vari�veis
    case Instr::cTxt1:
    case Instr::cTxt2:
        if (indice==0)
            return (end_char[0] != 0);
        return (end_char[indice * Tamanho(defvar)] != 0);
    case Instr::cTxtFixo:
        return (*end_char != 0);
    case Instr::cInt8:
    case Instr::cUInt8:
        return (end_char[indice] != 0);
    case Instr::cInt1:
        if (numfunc)
            return GetVetorInt1(this);
        if (indice)
        {
            int ind2 = indice + numbit;
            return end_char[ind2/8] & (1 << (ind2 & 7));
        }
        return (end_char[0] & (1 << numbit));
    case Instr::cInt16:
    case Instr::cUInt16:
        return end_short[indice];
    case Instr::cInt32:
    case Instr::cUInt32:
        return end_int[indice];
    case Instr::cIntInc:
        return end_incdec[indice].getInc(numfunc);
    case Instr::cIntDec:
        return end_incdec[indice].getDec(numfunc);
    case Instr::cReal:
        return (end_float[indice] != 0);
    case Instr::cReal2:
        return (end_double[indice] != 0);
    case Instr::cConstNulo:
        return 0;
    case Instr::cConstTxt:
        return defvar[(unsigned char)defvar[Instr::endIndice] + 1] != 0;
    case Instr::cConstNum:
        {
            const char * origem = defvar + defvar[Instr::endIndice];
            switch (*origem)
            {
            case Instr::ex_num1:
                return true;
            case Instr::ex_num0:
                return false;
            case Instr::ex_num8n:
            case Instr::ex_num8p:
            case Instr::ex_num8hexn:
            case Instr::ex_num8hexp:
                return origem[1]!=0;
            case Instr::ex_num16n:
            case Instr::ex_num16p:
            case Instr::ex_num16hexn:
            case Instr::ex_num16hexp:
                return origem[1]!=0 || origem[2]!=0;
            case Instr::ex_num32n:
            case Instr::ex_num32p:
            case Instr::ex_num32hexn:
            case Instr::ex_num32hexp:
                return origem[1]!=0 || origem[2]!=0 ||
                       origem[3]!=0 || origem[4]!=0;
            default:
                assert(0);
            }
        }
    case Instr::cConstExpr:
    case Instr::cConstVar:
    case Instr::cFunc:
    case Instr::cVarFunc:
        return 0;

// Vari�veis extras
    case Instr::cListaObj:
        return end_listaobj[indice].getValor();
    case Instr::cListaItem:
        return end_listaitem[indice].getValor();
    case Instr::cTextoTxt:
        return end_textotxt[indice].getValor();
    case Instr::cTextoPos:
        return end_textopos[indice].getValor(numfunc);
    case Instr::cTextoVar:
    case Instr::cTextoObj:
        return 0;
    case Instr::cNomeObj:
        return end_nomeobj[indice].getValor();
    case Instr::cArqDir:
        return 0;
    case Instr::cArqLog:
        return end_arqlog[indice].getValor();
    case Instr::cArqProg:
    case Instr::cArqExec:
    case Instr::cArqSav:
        return 0;
    case Instr::cArqTxt:
        return end_arqtxt[indice].getValor();
    case Instr::cArqMem:
        return 0;
    case Instr::cIntTempo:
        return end_inttempo[indice].getValor(numfunc);
    case Instr::cIntExec:
        return end_intexec[indice].getValor();
    case Instr::cTelaTxt:
        return end_telatxt[indice].getValor(numfunc);
    case Instr::cSocket:
        return end_socket[indice].getValor(numfunc);
    case Instr::cServ:
        return end_serv[indice].getValor();
    case Instr::cProg:
        return end_prog[indice].getValor();
    case Instr::cDebug:
        return TVarDebug::getInt(numfunc);
    case Instr::cIndiceObj:
        return end_indiceobj[indice].getNome()[0] != 0;
    case Instr::cIndiceItem:
        return end_indiceitem[indice].getValor();
    case Instr::cDataHora:
        return end_datahora[indice].getInt(numfunc);
    case Instr::cRef:
        return end_varref[indice].Pont != 0;
    case Instr::cVarObjeto:
        return (endvar!=0);
    case Instr::cVarIniFunc:
    case Instr::cVarInt:
        return (valor_int!=0);
    case Instr::cTextoVarSub:
        return end_textovarsub[indice].getBool();
    case Instr::cTextoObjSub:
        return end_textoobjsub[indice].getInt();
    }
    return 0;
}

//------------------------------------------------------------------------------
int TVariavel::getInt()
{
    if (indice==0xFF) // Vetor
        return 0;
    switch (defvar[2])
    {
// Vari�veis
    case Instr::cTxt1:
    case Instr::cTxt2:
        if (indice)
            return TxtToInt(&end_char[indice * Tamanho(defvar)]);
    case Instr::cTxtFixo:
        return TxtToInt(end_char);
    case Instr::cInt1:
        return (numfunc ? GetVetorInt1(this) : getBool());
    case Instr::cInt8:
        return (signed char)end_char[indice];
    case Instr::cUInt8:
        return (unsigned char)end_char[indice];
    case Instr::cInt16:
        return end_short[indice];
    case Instr::cUInt16:
        return end_ushort[indice];
    case Instr::cInt32:
        return end_int[indice];
    case Instr::cUInt32:
        return (end_uint[indice] > 0x7FFFFFFF ?
                0x7FFFFFFF : end_uint[indice]);
    case Instr::cIntInc:
        return end_incdec[indice].getInc(numfunc);
    case Instr::cIntDec:
        return end_incdec[indice].getDec(numfunc);
    case Instr::cReal:
        return DoubleToInt(end_float[indice]);
    case Instr::cReal2:
        return DoubleToInt(end_double[indice]);
    case Instr::cConstNulo:
        return 0;
    case Instr::cConstTxt:
        return TxtToInt(defvar + defvar[Instr::endIndice] + 1);
    case Instr::cConstNum:
        {
            unsigned int valor = 0;
            bool negativo = false;
            const char * origem = defvar + defvar[Instr::endIndice];
            switch (*origem)
            {
            case Instr::ex_num1:
                valor=1;
            case Instr::ex_num0:
                origem++;
                break;
            case Instr::ex_num8n:
            case Instr::ex_num8hexn:
                negativo=true;
            case Instr::ex_num8p:
            case Instr::ex_num8hexp:
                valor=(unsigned char)origem[1];
                origem+=2;
                break;
            case Instr::ex_num16n:
            case Instr::ex_num16hexn:
                negativo=true;
            case Instr::ex_num16p:
            case Instr::ex_num16hexp:
                valor=Num16(origem+1);
                origem+=3;
                break;
            case Instr::ex_num32n:
            case Instr::ex_num32hexn:
                negativo=true;
            case Instr::ex_num32p:
            case Instr::ex_num32hexp:
                valor=Num32(origem+1);
                origem+=5;
                break;
            default:
                assert(0);
            }
            while (*origem>=Instr::ex_div1 && *origem<=Instr::ex_div6)
                switch (*origem++)
                {
                case Instr::ex_div1: valor/=10; break;
                case Instr::ex_div2: valor/=100; break;
                case Instr::ex_div3: valor/=1000; break;
                case Instr::ex_div4: valor/=10000; break;
                case Instr::ex_div5: valor/=100000; break;
                case Instr::ex_div6: valor/=1000000; break;
                }
            if (negativo)
                return (valor<0x80000000LL ? -valor : -0x80000000);
            return (valor<0x7FFFFFFFLL ? valor : 0x7FFFFFFF);
        }
    case Instr::cConstExpr:
    case Instr::cConstVar:
    case Instr::cFunc:
    case Instr::cVarFunc:
        return 0;
    case Instr::cVarIniFunc:
    case Instr::cVarInt:
        return valor_int;

// Vari�veis extras
    case Instr::cListaObj:
        return end_listaobj[indice].getValor();
    case Instr::cListaItem:
        return end_listaitem[indice].getValor();
    case Instr::cTextoTxt:
        return end_textotxt[indice].getValor();
    case Instr::cTextoPos:
        return end_textopos[indice].getValor(numfunc);
    case Instr::cTextoVar:
    case Instr::cTextoObj:
        return 0;
    case Instr::cNomeObj:
        return end_nomeobj[indice].getValor();
    case Instr::cArqDir:
        return 0;
    case Instr::cArqLog:
        return end_arqlog[indice].getValor();
    case Instr::cArqProg:
    case Instr::cArqExec:
    case Instr::cArqSav:
        return 0;
    case Instr::cArqTxt:
        return end_arqtxt[indice].getValor();
    case Instr::cArqMem:
        return 0;
    case Instr::cIntTempo:
        return end_inttempo[indice].getValor(numfunc);
    case Instr::cIntExec:
        return end_intexec[indice].getValor();
    case Instr::cTelaTxt:
        return end_telatxt[indice].getValor(numfunc);
    case Instr::cSocket:
        return end_socket[indice].getValor(numfunc);
    case Instr::cServ:
        return end_serv[indice].getValor();
    case Instr::cProg:
        return end_prog[indice].getValor();
    case Instr::cDebug:
        return TVarDebug::getInt(numfunc);
    case Instr::cIndiceObj:
        return TxtToInt(end_indiceobj[indice].getNome());
    case Instr::cIndiceItem:
        return end_indiceitem[indice].getValor();
    case Instr::cDataHora:
        return end_datahora[indice].getInt(numfunc);

    case Instr::cRef:
        return end_varref[indice].Pont != 0;
    case Instr::cVarObjeto:
        return (endvar!=0);
    case Instr::cTextoVarSub:
        return end_textovarsub[indice].getInt();
    case Instr::cTextoObjSub:
        return end_textoobjsub[indice].getInt();
    }
    return 0;
}

//------------------------------------------------------------------------------
double TVariavel::getDouble()
{
    if (indice==0xFF) // Vetor
        return 0;
    switch (defvar[2])
    {
// Vari�veis
    case Instr::cTxt1:
    case Instr::cTxt2:
        if (indice)
            return TxtToDouble(&end_char[indice * Tamanho(defvar)]);
    case Instr::cTxtFixo:
        return TxtToDouble(end_char);
    case Instr::cInt1:
        return (numfunc ? GetVetorInt1(this) : getBool());
    case Instr::cInt8:
        return (signed char)end_char[indice];
    case Instr::cUInt8:
        return (unsigned char)end_char[indice];
    case Instr::cInt16:
        return end_short[indice];
    case Instr::cUInt16:
        return end_ushort[indice];
    case Instr::cInt32:
        return end_int[indice];
    case Instr::cUInt32:
        return end_uint[indice];
    case Instr::cIntInc:
        return end_incdec[indice].getInc(numfunc);
    case Instr::cIntDec:
        return end_incdec[indice].getDec(numfunc);
    case Instr::cReal:
        return end_float[indice];
    case Instr::cReal2:
        return end_double[indice];
    case Instr::cConstNulo:
        return 0;
    case Instr::cConstTxt:
        return TxtToDouble(defvar + defvar[Instr::endIndice] + 1);
    case Instr::cConstNum:
        {
            double valor = 0;
            bool negativo = false;
            const char * origem = defvar + defvar[Instr::endIndice];
            switch (*origem)
            {
            case Instr::ex_num1:
                valor=1;
            case Instr::ex_num0:
                origem++;
                break;
            case Instr::ex_num8n:
            case Instr::ex_num8hexn:
                negativo=true;
            case Instr::ex_num8p:
            case Instr::ex_num8hexp:
                valor=(unsigned char)origem[1];
                origem+=2;
                break;
            case Instr::ex_num16n:
            case Instr::ex_num16hexn:
                negativo=true;
            case Instr::ex_num16p:
            case Instr::ex_num16hexp:
                valor=Num16(origem+1);
                origem+=3;
                break;
            case Instr::ex_num32n:
            case Instr::ex_num32hexn:
                negativo=true;
            case Instr::ex_num32p:
            case Instr::ex_num32hexp:
                valor=Num32(origem+1);
                origem+=5;
                break;
            default:
                assert(0);
            }
            while (*origem>=Instr::ex_div1 && *origem<=Instr::ex_div6)
                switch (*origem++)
                {
                case Instr::ex_div1: valor/=10; break;
                case Instr::ex_div2: valor/=100; break;
                case Instr::ex_div3: valor/=1000; break;
                case Instr::ex_div4: valor/=10000; break;
                case Instr::ex_div5: valor/=100000; break;
                case Instr::ex_div6: valor/=1000000; break;
                }
            return (negativo ? -valor : valor);
        }
    case Instr::cConstExpr:
    case Instr::cConstVar:
    case Instr::cFunc:
    case Instr::cVarFunc:
        return 0;
    case Instr::cVarIniFunc:
    case Instr::cVarInt:
        return valor_int;

// Vari�veis extras
    case Instr::cListaObj:
        return end_listaobj[indice].getValor();
    case Instr::cListaItem:
        return end_listaitem[indice].getValor();
    case Instr::cTextoTxt:
        return end_textotxt[indice].getValor();
    case Instr::cTextoPos:
        return end_textopos[indice].getValor(numfunc);
    case Instr::cTextoVar:
    case Instr::cTextoObj:
        return 0;
    case Instr::cNomeObj:
        return end_nomeobj[indice].getValor();
    case Instr::cArqDir:
        return 0;
    case Instr::cArqLog:
        return end_arqlog[indice].getValor();
    case Instr::cArqProg:
    case Instr::cArqExec:
    case Instr::cArqSav:
        return 0;
    case Instr::cArqTxt:
        return end_arqtxt[indice].getValor();
    case Instr::cArqMem:
        return 0;
    case Instr::cIntTempo:
        return end_inttempo[indice].getValor(numfunc);
    case Instr::cIntExec:
        return end_intexec[indice].getValor();
    case Instr::cTelaTxt:
        return end_telatxt[indice].getValor(numfunc);
    case Instr::cSocket:
        return end_socket[indice].getValor(numfunc);
    case Instr::cServ:
        return end_serv[indice].getValor();
    case Instr::cProg:
        return end_prog[indice].getValor();
    case Instr::cDebug:
        return TVarDebug::getDouble(numfunc);
    case Instr::cIndiceObj:
        return TxtToDouble(end_indiceobj[indice].getNome());
    case Instr::cIndiceItem:
        return end_indiceitem[indice].getValor();
    case Instr::cDataHora:
        return end_datahora[indice].getDouble(numfunc);

    case Instr::cRef:
        return end_varref[indice].Pont != 0;
    case Instr::cVarObjeto:
        return (endvar!=0);
    case Instr::cTextoVarSub:
        return end_textovarsub[indice].getDouble();
    case Instr::cTextoObjSub:
        return end_textoobjsub[indice].getInt();
    }
    return 0;
}

//------------------------------------------------------------------------------
const char * TVariavel::getTxt()
{
    static char txtnum[80];
    if (indice==0xFF) // Vetor
        return "";
    switch (defvar[2])
    {
// Vari�veis
    case Instr::cTxt1:
    case Instr::cTxt2:
        if (indice)
            return &end_char[indice * Tamanho(defvar)];
    case Instr::cTxtFixo:
    case Instr::cVarNome:
        return end_char;
    case Instr::cInt1:
        if (numfunc==0)
            return (getBool() ? "1" : "0");
    case Instr::cInt8:
    case Instr::cUInt8:
    case Instr::cInt16:
    case Instr::cUInt16:
    case Instr::cInt32:
    case Instr::cIntInc:
    case Instr::cIntDec:
    case Instr::cIntTempo:
    case Instr::cIntExec:
    case Instr::cArqLog:
    case Instr::cArqTxt:
    case Instr::cListaObj:
    case Instr::cListaItem:
    case Instr::cTextoTxt:
    case Instr::cTextoPos:
    case Instr::cNomeObj:
    case Instr::cDebug:
    case Instr::cIndiceItem:
        sprintf(txtnum, "%d", getInt());
        return txtnum;
    case Instr::cUInt32:
        sprintf(txtnum, "%u", end_uint[indice]);
        return txtnum;
    case Instr::cReal:
    case Instr::cReal2:
        DoubleToTxt(txtnum, getDouble());
        return txtnum;
    case Instr::cArqMem:
    case Instr::cConstNulo:
        return "";
    case Instr::cConstTxt:
        return defvar + defvar[Instr::endIndice] + 1;
    case Instr::cConstNum:
        {
            unsigned int valor = 0; // Valor num�rico sem sinal
            bool negativo = false; // Se � negativo
            int  virgula = 0;   // Casas ap�s a v�rgula
            const char * origem = defvar + defvar[Instr::endIndice];
        // Acerta vari�veis valor e negativo
            switch (*origem)
            {
            case Instr::ex_num1:
                valor=1;
            case Instr::ex_num0:
                origem++;
                break;
            case Instr::ex_num8n:
            case Instr::ex_num8hexn:
                negativo=true;
            case Instr::ex_num8p:
            case Instr::ex_num8hexp:
                valor=(unsigned char)origem[1];
                origem+=2;
                break;
            case Instr::ex_num16n:
            case Instr::ex_num16hexn:
                negativo=true;
            case Instr::ex_num16p:
            case Instr::ex_num16hexp:
                valor=Num16(origem+1);
                origem+=3;
                break;
            case Instr::ex_num32n:
            case Instr::ex_num32hexn:
                negativo=true;
            case Instr::ex_num32p:
            case Instr::ex_num32hexp:
                valor=Num32(origem+1);
                origem+=5;
                break;
            }
        // Acerta vari�vel virgula
            while (*origem>=Instr::ex_div1 && *origem<=Instr::ex_div6)
                switch (*origem++)
                {
                case Instr::ex_div1: virgula++; break;
                case Instr::ex_div2: virgula+=2; break;
                case Instr::ex_div3: virgula+=3; break;
                case Instr::ex_div4: virgula+=4; break;
                case Instr::ex_div5: virgula+=5; break;
                case Instr::ex_div6: virgula+=6; break;
                }
            if (virgula>60)
                virgula=60;
        // Zero � sempre zero
            if (valor==0)
                return "0";
        // Obt�m em nome a string correspondente ao n�mero
            char mens[80];
            char * d=mens, *destino=txtnum;
            while (valor>0)
                *d++=valor%10+'0', valor/=10;
        // Obt�m o n�mero de d�gitos
            int digitos = d-mens;
            if (digitos <= virgula)
                digitos = virgula+1;
        // Anota o n�mero
            if (negativo)
                *destino++ = '-';
            while (digitos>0)
            {
                if (digitos==virgula)
                    *destino++ = '.';
                digitos--;
                *destino++ = (&mens[digitos]>=d ? '0' : mens[digitos]);
            }
            *destino=0;
            return txtnum;
        }
    case Instr::cConstExpr:
    case Instr::cConstVar:
    case Instr::cFunc:
    case Instr::cVarFunc:
        return "";

// Vari�veis extras
    case Instr::cTelaTxt:
        return end_telatxt[indice].getTxt(numfunc);
    case Instr::cSocket:
        if (TVarSocket::FTipo(this) != varInt)
            return "";
        sprintf(txtnum, "%d", getInt());
        return txtnum;
    case Instr::cTextoVar:
    case Instr::cTextoObj:
    case Instr::cArqDir:
    case Instr::cArqProg:
    case Instr::cArqExec:
    case Instr::cArqSav:
    case Instr::cServ:
    case Instr::cProg:
        return "";
    case Instr::cIndiceObj:
        return end_indiceobj[indice].getNome();
    case Instr::cDataHora:
        if (TVarDataHora::FTipo(this) == varDouble)
            sprintf(txtnum, "%.0f", end_datahora[indice].getDouble(numfunc));
        else
            sprintf(txtnum, "%d", end_datahora[indice].getInt(numfunc));
        return txtnum;

    case Instr::cRef:
        if (end_varref[indice].Pont == 0)
            break;
        return end_varref[indice].Pont->Classe->Nome;
    case Instr::cVarClasse:
        if (endvar==0)
            break;
        return ((TClasse*)endvar)->Nome;
    case Instr::cVarObjeto:
        if (endvar==0)
            break;
        return ((TObjeto*)endvar)->Classe->Nome;
    case Instr::cVarIniFunc:
    case Instr::cVarInt:
        sprintf(txtnum, "%d", valor_int);
        return txtnum;
    case Instr::cTextoVarSub:
        return end_textovarsub[indice].getTxt();
    case Instr::cTextoObjSub:
        {
            TObjeto * obj = end_textoobjsub[indice].getObj();
            if (obj == 0)
                break;
            return obj->Classe->Nome;
        }
    }
    return "";
}

//------------------------------------------------------------------------------
TObjeto * TVariavel::getObj()
{
    if (indice==0xFF && defvar[Instr::endVetor]) // Vetor
        return 0;
    switch (defvar[2])
    {
    case Instr::cRef:
        return end_varref[indice].Pont;
    case Instr::cVarObjeto:
        return (TObjeto*)endvar;
    case Instr::cListaItem:
        {
            TListaX * l = end_listaitem[indice].ListaX;
            return (l==0 ? 0 : l->Objeto);
        }
    case Instr::cTextoObjSub:
        return end_textoobjsub[indice].getObj();
    case Instr::cTextoVarSub:
        return end_textovarsub[indice].getObj();
    }
    return 0;
}

//------------------------------------------------------------------------------
void TVariavel::setInt(int valor)
{
    if (indice==0xFF) // Vetor
        return;
    switch (defvar[2])
    {
// Vari�veis
    case Instr::cTxt1:
    case Instr::cTxt2:
        {
            int tam = Tamanho(defvar);
            if (indice)
                mprintf(&end_char[tam*indice], tam, "%d", valor);
            else
                mprintf(end_char, tam, "%d", valor);
            break;
        }
    case Instr::cInt1:
        if (numfunc)
            SetVetorInt1(this, valor);
        else if (indice)
        {
            int ind2 = indice + numbit;
            if (valor)
                end_char[ind2/8] |= (1 << (ind2 & 7));
            else
                end_char[ind2/8] &= ~(1 << (ind2 & 7));
        }
        else if (valor)
            end_char[0] |= (1 << numbit);
        else
            end_char[0] &= ~(1 << numbit);
        break;
    case Instr::cInt8:
        if (valor<-0x80)
            valor=-0x80;
        else if (valor>0x7F)
            valor=0x7F;
        end_char[indice]=valor;
        break;
    case Instr::cUInt8:
        if (valor<0)
            valor=0;
        else if (valor>0xFF)
            valor=0xFF;
        end_char[indice]=valor;
        break;
    case Instr::cInt16:
        if (valor<-0x8000)
            end_short[indice] = -0x8000;
        else if (valor>0x7FFF)
            end_short[indice] = 0x7FFF;
        else
            end_short[indice] = valor;
        break;
    case Instr::cUInt16:
        if (valor<0)
            end_ushort[indice] = 0;
        else if (valor>0xFFFF)
            end_ushort[indice] = 0xFFFF;
        else
            end_ushort[indice] = valor;
        break;
    case Instr::cUInt32:
        if (valor<0)
            valor=0;
    case Instr::cInt32:
        end_int[indice] = valor;
        break;
    case Instr::cIntInc:
        end_incdec[indice].setInc(numfunc, valor);
        break;
    case Instr::cIntDec:
        end_incdec[indice].setDec(numfunc, valor);
        break;
    case Instr::cReal:
        end_float[indice] = valor;
        break;
    case Instr::cReal2:
        end_double[indice] = valor;
        break;
    case Instr::cConstNulo:
    case Instr::cConstTxt:
    case Instr::cConstNum:
    case Instr::cConstExpr:
    case Instr::cConstVar:
    case Instr::cFunc:
    case Instr::cVarFunc:
        break;
    case Instr::cVarIniFunc:
    case Instr::cVarInt:
        valor_int = valor;
        break;

// Vari�veis extras
    case Instr::cListaObj:
        break;
    case Instr::cListaItem:
        end_listaitem[indice].MudarRef(0);
        break;
    case Instr::cTextoPos:
        end_textopos[indice].setValor(numfunc, valor);
        break;
    case Instr::cTextoTxt:
    case Instr::cTextoVar:
    case Instr::cTextoObj:
    case Instr::cNomeObj:
    case Instr::cArqDir:
    case Instr::cArqProg:
    case Instr::cArqExec:
    case Instr::cArqLog:
    case Instr::cArqSav:
    case Instr::cArqTxt:
    case Instr::cArqMem:
        break;
    case Instr::cIntTempo:
        end_inttempo[indice].setValor(numfunc, valor);
        break;
    case Instr::cIntExec:
        end_intexec[indice].setValor(valor);
        break;
    case Instr::cTelaTxt:
        end_telatxt[indice].setValor(numfunc, valor);
        break;
    case Instr::cSocket:
        end_socket[indice].setValor(numfunc, valor);
        break;
    case Instr::cServ:
        end_serv[indice].Fechar();
        break;
    case Instr::cProg:
    case Instr::cIndiceItem:
        break;
    case Instr::cDebug:
        TVarDebug::setValor(numfunc, valor);
        break;
    case Instr::cIndiceObj:
        {
            char mens[20];
            mprintf(mens, sizeof(mens), "%d", valor);
            end_indiceobj[indice].setNome(mens);
            break;
        }
    case Instr::cDataHora:
        end_datahora[indice].setInt(numfunc, valor);
        break;
    case Instr::cRef:
        end_varref[indice].MudarPont(0);
        break;
    case Instr::cVarObjeto:
        endvar = 0;
        break;
    case Instr::cTextoVarSub:
        end_textovarsub[indice].setInt(valor);
        break;
    case Instr::cTextoObjSub:
        end_textoobjsub[indice].setObj(0);
        break;
    }
}

//------------------------------------------------------------------------------
void TVariavel::setDouble(double valor)
{
    if (indice==0xFF) // Vetor
        return;
    switch (defvar[2])
    {
// Vari�veis
    case Instr::cInt1:
    case Instr::cInt8:
    case Instr::cUInt8:
    case Instr::cInt16:
    case Instr::cUInt16:
    case Instr::cInt32:
    case Instr::cIntInc:
    case Instr::cIntDec:
    case Instr::cIntTempo:
    case Instr::cIntExec:
    case Instr::cIndiceObj:
        setInt(DoubleToInt(valor));
        break;
    case Instr::cUInt32:
        if (valor > 0xFFFFFFFFLL)
            end_uint[indice] = 0xFFFFFFFFLL;
        else if (valor < 0)
            end_uint[indice] = 0;
        else
            end_uint[indice] = (unsigned int)valor;
        break;
    case Instr::cReal:
        end_float[indice] = valor;
        break;
    case Instr::cReal2:
        end_double[indice] = valor;
        break;
    case Instr::cConstNulo:
    case Instr::cConstTxt:
    case Instr::cConstNum:
    case Instr::cConstExpr:
    case Instr::cConstVar:
    case Instr::cFunc:
    case Instr::cVarFunc:
        break;
    case Instr::cVarIniFunc:
    case Instr::cVarInt:
        valor_int = DoubleToInt(valor);
        break;

// Vari�veis extras
    case Instr::cListaObj:
        break;
    case Instr::cListaItem:
        end_listaitem[indice].MudarRef(0);
        break;
    case Instr::cTextoPos:
        end_textopos[indice].setValor(numfunc, DoubleToInt(valor));
        break;
    case Instr::cTextoTxt:
    case Instr::cTextoVar:
    case Instr::cTextoObj:
    case Instr::cNomeObj:
    case Instr::cArqDir:
    case Instr::cArqLog:
    case Instr::cArqProg:
    case Instr::cArqExec:
    case Instr::cArqSav:
    case Instr::cArqTxt:
    case Instr::cArqMem:
        break;
    case Instr::cTelaTxt:
        end_telatxt[indice].setValor(numfunc, DoubleToInt(valor));
        break;
    case Instr::cSocket:
        end_socket[indice].setValor(numfunc, DoubleToInt(valor));
        break;
    case Instr::cServ:
        end_serv[indice].Fechar();
        break;
    case Instr::cProg:
    case Instr::cIndiceItem:
        break;
    case Instr::cDebug:
        TVarDebug::setValor(numfunc, DoubleToInt(valor));
        break;
    case Instr::cDataHora:
        end_datahora[indice].setDouble(numfunc, valor);
        break;
    case Instr::cRef:
        end_varref[indice].MudarPont(0);
        break;
    case Instr::cVarObjeto:
        endvar = 0;
        break;
    case Instr::cTextoObjSub:
        end_textoobjsub[indice].setObj(0);
        break;
    case Instr::cTextoVarSub:
        end_textovarsub[indice].setDouble(valor);
        break;
    case Instr::cTxt1:
    case Instr::cTxt2:
        {
            char mens[100];
            if (valor >= DOUBLE_MAX || valor <= -DOUBLE_MAX)
                sprintf(mens, "%E", valor);
            else
            {
                sprintf(mens, "%.9f", valor);
                char * p = mens;
                while (*p)
                    p++;
                while (p>mens && p[-1]=='0')
                    p--;
                if (p>mens && p[-1]=='.')
                    p--;
                *p=0;
            }
            setTxt(mens);
            break;
        }
    }
}

//------------------------------------------------------------------------------
void TVariavel::setTxt(const char * txt)
{
    if (indice==0xFF) // Vetor
        return;
    switch (defvar[2])
    {
// Vari�veis
    case Instr::cTxt1:
    case Instr::cTxt2:
    case Instr::cVarNome:
        {
            int tam = Tamanho(defvar);
            if (indice)
                copiastr(&end_char[tam*indice], txt, tam);
            else
                copiastr(end_char, txt, tam);
            break;
        }
    case Instr::cInt1:
    case Instr::cInt8:
    case Instr::cUInt8:
    case Instr::cInt16:
    case Instr::cUInt16:
    case Instr::cInt32:
    case Instr::cIntInc:
    case Instr::cIntDec:
    case Instr::cIntTempo:
    case Instr::cIntExec:
    case Instr::cVarIniFunc:
    case Instr::cVarInt:
    case Instr::cSocket:
    case Instr::cDebug:
    case Instr::cDataHora:
        setInt(TxtToInt(txt));
        break;
    case Instr::cUInt32:
        {
            unsigned long num;
            errno=0, num=strtoul(txt, 0, 10);
            if (errno)
                num=0;
            end_uint[indice] = num;
            break;
        }
    case Instr::cReal:
        end_float[indice] = TxtToDouble(txt);
        break;
    case Instr::cReal2:
        end_double[indice] = TxtToDouble(txt);
        break;
    case Instr::cConstNulo:
    case Instr::cConstTxt:
    case Instr::cConstNum:
    case Instr::cConstExpr:
    case Instr::cConstVar:
    case Instr::cFunc:
    case Instr::cVarFunc:
        break;

// Vari�veis extras
    case Instr::cListaObj:
        break;
    case Instr::cListaItem:
        end_listaitem[indice].MudarRef(0);
        break;
    case Instr::cTextoPos:
        end_textopos[indice].setTxt(numfunc, txt);
        break;
    case Instr::cTextoTxt:
    case Instr::cTextoVar:
    case Instr::cTextoObj:
    case Instr::cNomeObj:
    case Instr::cArqDir:
    case Instr::cArqLog:
    case Instr::cArqProg:
    case Instr::cArqExec:
    case Instr::cArqSav:
    case Instr::cArqTxt:
    case Instr::cArqMem:
        break;
    case Instr::cTelaTxt:
        end_telatxt[indice].setTxt(numfunc, txt);
        break;
    case Instr::cServ:
        end_serv[indice].Fechar();
        break;
    case Instr::cProg:
    case Instr::cIndiceItem:
        break;
    case Instr::cIndiceObj:
        end_indiceobj[indice].setNome(txt);
        break;
    case Instr::cRef:
        end_varref[indice].MudarPont(0);
        break;
    case Instr::cVarObjeto:
        endvar = 0;
        break;
    case Instr::cTextoVarSub:
        end_textovarsub[indice].setTxt(txt);
        break;
    case Instr::cTextoObjSub:
        end_textoobjsub[indice].setObj(0);
        break;
    }
}

//------------------------------------------------------------------------------
void TVariavel::addTxt(const char * txt)
{
    if (indice==0xFF) // Vetor
        return;
    switch (defvar[2])
    {
    case Instr::cTxt1:
    case Instr::cTxt2:
    case Instr::cVarNome:
        {
            int tam = Tamanho(defvar);
            char * dest = end_char + indice * tam;
            const char * fim = dest + tam - 1;
            while (*dest)
                dest++;
            while (*txt && dest<fim)
                *dest++ = *txt++;
            *dest=0;
            break;
        }
    case Instr::cTelaTxt:
        end_telatxt[indice].addTxt(numfunc, txt);
        break;
    case Instr::cIndiceObj:
        {
            char mens[1024];
            mprintf(mens, sizeof(mens), "%s%s",
                    end_indiceobj[indice].getNome(), txt);
            end_indiceobj[indice].setNome(mens);
            break;
        }
    case Instr::cTextoVarSub:
        end_textovarsub[indice].addTxt(txt);
        break;
    }
}

//------------------------------------------------------------------------------
void TVariavel::setObj(TObjeto * obj)
{
    if (indice==0xFF) // Vetor
        return;
    switch (defvar[2])
    {
    case Instr::cRef:
        end_varref[indice].MudarPont(obj);
        break;
    case Instr::cVarObjeto:
        endvar = obj;
        break;
    case Instr::cTextoObjSub:
        end_textoobjsub[indice].setObj(obj);
        break;
    case Instr::cTextoVarSub:
        end_textovarsub[indice].setObj(obj);
        break;
    }
}

//------------------------------------------------------------------------------
int TVariavel::Compara(TVariavel * v)
{
    void * var1 = endvar;
    void * var2 = v->endvar;
    if (indice!=0xFF && v->indice!=0xFF)
        switch (defvar[2])
        {
        case Instr::cListaItem:
            var1 = end_listaitem[indice].ListaX;
            var2 = v->end_listaitem[v->indice].ListaX;
            break;
        case Instr::cTextoPos:
            return end_textopos[indice].Compara(v->end_textopos + v->indice);
        case Instr::cTextoVar:
            return end_textovar[indice].Compara(v->end_textovar + v->indice);
        case Instr::cSocket:
            var1 = end_socket->Socket + indice;
            var2 = v->end_socket->Socket + v->indice;
            break;
        case Instr::cIndiceItem:
            var1 = end_indiceitem[indice].getIndiceObj();
            var2 =v->end_indiceitem[v->indice].getIndiceObj();
            break;
        case Instr::cDataHora:
            return end_datahora[indice].Compara(v->end_datahora + v->indice);
        }
    return (var1 == var2 ? 0 : var1 < var2 ? -1 : 1);
}

//------------------------------------------------------------------------------
void TVariavel::Igual(TVariavel * v)
{
    if (indice==0xFF || v->indice==0xFF) // Vetor
        return;
    switch (defvar[2])
    {
    case Instr::cListaItem:
        end_listaitem[indice].MudarRef(v->end_listaitem[v->indice].ListaX);
        break;
    case Instr::cTextoPos:
        end_textopos[indice].Igual(v->end_textopos + v->indice);
        break;
    case Instr::cTextoVar:
        end_textovar[indice].Igual(v->end_textovar + v->indice);
        break;
    case Instr::cSocket:
        end_socket[indice].Igual(v->end_socket + v->indice);
        break;
    case Instr::cIndiceItem:
        end_indiceitem[indice].Igual(v->end_indiceitem + v->indice);
        break;
    case Instr::cDataHora:
        end_datahora[indice].Igual(v->end_datahora + v->indice);
    }
}

//------------------------------------------------------------------------------
bool TVariavel::Func(const char * nome)
{
    if (indice == 0xFF) // Vetor
    {
        int valor = 0;
        for (; *nome >= '0' && *nome <= '9'; nome++)
        {
            valor = valor * 10 + *nome - '0';
            if (valor >= 0xFF)
                return false;
        }
        if (*nome == 0 && valor < (unsigned char)defvar[Instr::endVetor])
        {
            indice = valor;
            Instr::ApagarVar(this+1);
            return true;
        }

        unsigned char cmd = (unsigned char)defvar[2];
        if (cmd < Instr::cTotalComandos)
            return VarInfo[cmd].FFuncVetor(this, nome);
        return false;
    }
    switch (defvar[2])
    {
    case Instr::cIntInc:
        return end_incdec->FuncInc(this, nome);
    case Instr::cIntDec:
        return end_incdec->FuncDec(this, nome);
    case Instr::cIntTempo:
        return end_inttempo->Func(this, nome);
    case Instr::cListaObj:
        return end_listaobj[indice].Func(this, nome);
    case Instr::cListaItem:
        return end_listaitem[indice].Func(this, nome);
    case Instr::cTextoTxt:
        return end_textotxt[indice].Func(this, nome);
    case Instr::cTextoPos:
        return end_textopos[indice].Func(this, nome);
    case Instr::cTextoVar:
        return end_textovar[indice].Func(this, nome);
    case Instr::cTextoObj:
        return end_textoobj[indice].Func(this, nome);
    case Instr::cNomeObj:
        return end_nomeobj[indice].Func(this, nome);
    case Instr::cArqDir:
        return end_arqdir[indice].Func(this, nome);
    case Instr::cArqLog:
        return end_arqlog[indice].Func(this, nome);
    case Instr::cArqProg:
        return end_arqprog[indice].Func(this, nome);
    case Instr::cArqExec:
        return end_arqexec[indice].Func(this, nome);
    case Instr::cArqSav:
        return TVarSav::Func(this, nome);
    case Instr::cArqTxt:
        return end_arqtxt[indice].Func(this, nome);
    case Instr::cArqMem:
        return end_arqmem[indice].Func(this, nome);
    case Instr::cTelaTxt:
        return end_telatxt[indice].Func(this, nome);
    case Instr::cSocket:
        return end_socket[indice].Func(this, nome);
    case Instr::cServ:
        return end_serv[indice].Func(this, nome);
    case Instr::cProg:
        return end_prog[indice].Func(this, nome);
    case Instr::cDebug:
        return TVarDebug::Func(this, nome);
    case Instr::cIndiceItem:
        return end_indiceitem[indice].Func(this, nome);
    case Instr::cDataHora:
        return end_datahora[indice].Func(this, nome);
    }
    return false;
}
