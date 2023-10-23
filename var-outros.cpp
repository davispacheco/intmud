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
#include <errno.h>
#include <assert.h>
#include "variavel.h"
#include "var-outros.h"
#include "instr.h"

//----------------------------------------------------------------------------
static int VarOutrosVarNome_Tamanho(const char * instr)
{
    return VAR_NOME_TAM;
}
static int VarOutrosVarNome_TamanhoVetor(const char * instr)
{
    int total = (unsigned char)instr[Instr::endVetor];
    return (total ? total : 1) * VAR_NOME_TAM;
}

//----------------------------------------------------------------------------
static void VarOutrosVarNome_Redim(TVariavel * v, TClasse * c, TObjeto * o,
        unsigned int antes, unsigned int depois)
{
    char * ref = reinterpret_cast<char*>(v->endvar);
    if (antes < depois)
        ref[antes * VAR_NOME_TAM] = 0;
}

//----------------------------------------------------------------------------
static void VarOutrosVarNome_MoverEnd(TVariavel * v, void * destino,
        TClasse * c, TObjeto * o)
{
    memmove(destino, v->endvar, VarOutrosVarNome_TamanhoVetor(v->defvar));
}

//----------------------------------------------------------------------------
static void VarOutrosTxtFixo_MoverEnd(TVariavel * v, void * destino,
        TClasse * c, TObjeto * o)
{
    memmove(destino, v->endvar, strlen((char*)v->endvar) + 1);
}

//----------------------------------------------------------------------------
const TVarInfo * VarOutrosConstNulo()
{
    static const TVarInfo var(
        TVarInfo::FTamanho0,
        TVarInfo::FTamanho0,
        TVarInfo::FTipoObj,
        TVarInfo::FRedim0,
        TVarInfo::FMoverEnd0,
        TVarInfo::FMoverDef0,
        TVarInfo::FFuncVetorFalse);
    return &var;
}

const TVarInfo * VarOutrosConstTxt()
{
    static const TVarInfo var(
        TVarInfo::FTamanho0,
        TVarInfo::FTamanho0,
        TVarInfo::FTipoTxt,
        TVarInfo::FRedim0,
        TVarInfo::FMoverEnd0,
        TVarInfo::FMoverDef0,
        TVarInfo::FFuncVetorFalse);
    return &var;
}

const TVarInfo * VarOutrosConstNum()
{
    static const TVarInfo var(
        TVarInfo::FTamanho0,
        TVarInfo::FTamanho0,
        TVarInfo::FTipoDouble,
        TVarInfo::FRedim0,
        TVarInfo::FMoverEnd0,
        TVarInfo::FMoverDef0,
        TVarInfo::FFuncVetorFalse);
    return &var;
}

const TVarInfo * VarOutrosConstExpr()
{
    static const TVarInfo var(
        TVarInfo::FTamanho0,
        TVarInfo::FTamanho0,
        TVarInfo::FTipoOutros,
        TVarInfo::FRedim0,
        TVarInfo::FMoverEnd0,
        TVarInfo::FMoverDef0,
        TVarInfo::FFuncVetorFalse);
    return &var;
}

const TVarInfo * VarOutrosConstVar()
{
    static const TVarInfo var(
        TVarInfo::FTamanho0,
        TVarInfo::FTamanho0,
        TVarInfo::FTipoOutros,
        TVarInfo::FRedim0,
        TVarInfo::FMoverEnd0,
        TVarInfo::FMoverDef0,
        TVarInfo::FFuncVetorFalse);
    return &var;
}

const TVarInfo * VarOutrosFunc()
{
    static const TVarInfo var(
        TVarInfo::FTamanho0,
        TVarInfo::FTamanho0,
        TVarInfo::FTipoOutros,
        TVarInfo::FRedim0,
        TVarInfo::FMoverEnd0,
        TVarInfo::FMoverDef0,
        TVarInfo::FFuncVetorFalse);
    return &var;
}

const TVarInfo * VarOutrosVarFunc()
{
    static const TVarInfo var(
        TVarInfo::FTamanho0,
        TVarInfo::FTamanho0,
        TVarInfo::FTipoOutros,
        TVarInfo::FRedim0,
        TVarInfo::FMoverEnd0,
        TVarInfo::FMoverDef0,
        TVarInfo::FFuncVetorFalse);
    return &var;
}

const TVarInfo * VarOutrosTxtFixo()
{
    static const TVarInfo var(
        TVarInfo::FTamanho0,
        TVarInfo::FTamanho0,
        TVarInfo::FTipoTxt,
        TVarInfo::FRedim0,
        VarOutrosTxtFixo_MoverEnd,
        TVarInfo::FMoverDef0,
        TVarInfo::FFuncVetorFalse);
    return &var;
}

const TVarInfo * VarOutrosVarNome()
{
    static const TVarInfo var(
        VarOutrosVarNome_Tamanho,
        VarOutrosVarNome_TamanhoVetor,
        TVarInfo::FTipoTxt,
        VarOutrosVarNome_Redim,
        VarOutrosVarNome_MoverEnd,
        TVarInfo::FMoverDef0,
        TVarInfo::FFuncVetorFalse);
    return &var;
}

const TVarInfo * VarOutrosVarInicio()
{
    static const TVarInfo var(
        TVarInfo::FTamanho0,
        TVarInfo::FTamanho0,
        TVarInfo::FTipoOutros,
        TVarInfo::FRedim0,
        TVarInfo::FMoverEnd0,
        TVarInfo::FMoverDef0,
        TVarInfo::FFuncVetorFalse);
    return &var;
}

const TVarInfo * VarOutrosVarIniFunc()
{
    static const TVarInfo var(
        TVarInfo::FTamanho0,
        TVarInfo::FTamanho0,
        TVarInfo::FTipoInt,
        TVarInfo::FRedim0,
        TVarInfo::FMoverEnd0,
        TVarInfo::FMoverDef0,
        TVarInfo::FFuncVetorFalse);
    return &var;
}

const TVarInfo * VarOutrosVarClasse()
{
    static const TVarInfo var(
        TVarInfo::FTamanho0,
        TVarInfo::FTamanho0,
        TVarInfo::FTipoTxt,
        TVarInfo::FRedim0,
        TVarInfo::FMoverEnd0,
        TVarInfo::FMoverDef0,
        TVarInfo::FFuncVetorFalse);
    return &var;
}

const TVarInfo * VarOutrosVarObjeto()
{
    static const TVarInfo var(
        TVarInfo::FTamanho0,
        TVarInfo::FTamanho0,
        TVarInfo::FTipoObj,
        TVarInfo::FRedim0,
        TVarInfo::FMoverEnd0,
        TVarInfo::FMoverDef0,
        TVarInfo::FFuncVetorFalse);
    return &var;
}

const TVarInfo * VarOutrosVarInt()
{
    static const TVarInfo var(
        TVarInfo::FTamanho0,
        TVarInfo::FTamanho0,
        TVarInfo::FTipoInt,
        TVarInfo::FRedim0,
        TVarInfo::FMoverEnd0,
        TVarInfo::FMoverDef0,
        TVarInfo::FFuncVetorFalse);
    return &var;
}
