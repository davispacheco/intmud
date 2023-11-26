/* Este arquivo � software livre; voc� pode redistribuir e/ou
 * modificar nos termos da licen�a LGPL. Vide arquivo COPYING.
 *
 * This file is free software; you can redistribute it and/or
 * modify it under the terms of the LGPL license. See file COPYING.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include "var-arqlog.h"
#include "variavel.h"
#include "variavel-def.h"
#include "instr.h"
#include "instr-enum.h"
#include "misc.h"

int TVarArqLog::Tempo = 20;
TVarArqLog * TVarArqLog::Inicio = nullptr;

//----------------------------------------------------------------------------
const TVarInfo * TVarArqLog::Inicializa()
{
    static const TVarInfo var(
        FTamanho,
        FTamanhoVetor,
        TVarInfo::FTipoOutros,
        FRedim,
        FMoverEnd,
        TVarInfo::FMoverDef0,
        FGetBool,
        FGetInt,
        FGetDouble,
        FGetTxt,
        TVarInfo::FGetObjNulo,
        TVarInfo::FOperadorAtribVazio,
        TVarInfo::FFuncVetorFalse);
    return &var;
}

//------------------------------------------------------------------------------
void TVarArqLog::Criar()
{
    arq = -1;
}

//------------------------------------------------------------------------------
void TVarArqLog::Apagar()
{
    Fechar();
}

//------------------------------------------------------------------------------
void TVarArqLog::Mover(TVarArqLog * destino)
{
    if (arq == -1)
    {
        destino->arq = -1;
        return;
    }
    (Antes ? Antes->Depois : Inicio) = destino;
    if (Depois)
        Depois->Antes = destino;
    int total = sizeof(TVarArqLog) - sizeof(buflog) + pontlog;
    memmove(destino, this, total);
}

//------------------------------------------------------------------------------
int TVarArqLog::getValor()
{
    return (arq >= 0 ? 1 : 0);
}

//------------------------------------------------------------------------------
int TVarArqLog::TempoEspera(int tempodecorrido)
{
// Atualiza tempo
    Tempo -= tempodecorrido;
// Grava dados pendentes se tempo expirou
    if (Tempo <= 0)
    {
        for (TVarArqLog * obj = Inicio; obj; obj = obj->Depois)
            if (obj->pontlog)
            {
                safe_write(obj->arq, obj->buflog, obj->pontlog);
                obj->pontlog = 0;
            }
        Tempo = 20;
        return 600;
    }
// Obt�m quanto tempo para gravar dados pendentes
    for (TVarArqLog * obj = Inicio; obj; obj = obj->Depois)
        if (obj->pontlog)
            return Tempo;
    Tempo = 20;
    return 600;
}

//------------------------------------------------------------------------------
void TVarArqLog::Fechar()
{
    if (arq < 0)
        return;
    if (pontlog)
        safe_write(arq, buflog, pontlog);
    close(arq);
    arq=-1;
    (Antes ? Antes->Depois : Inicio) = Depois;
    if (Depois)
        Depois->Antes = nullptr;
}

//------------------------------------------------------------------------------
bool TVarArqLog::Func(TVariavel * v, const char * nome)
{
// Lista das fun��es de arqlog
// Deve obrigatoriamente estar em letras min�sculas e ordem alfab�tica
    static const struct {
        const char * Nome;
        bool (TVarArqLog::*Func)(TVariavel * v); } ExecFunc[] = {
        { "abrir",     &TVarArqLog::FuncAbrir },
        { "existe",    &TVarArqLog::FuncExiste },
        { "fechar",    &TVarArqLog::FuncFechar },
        { "msg",       &TVarArqLog::FuncMsg },
        { "valido",    &TVarArqLog::FuncValido }  };
// Procura a fun��o correspondente e executa
    int ini = 0;
    int fim = sizeof(ExecFunc) / sizeof(ExecFunc[0]) - 1;
    char mens[80];
    copiastrmin(mens, nome, sizeof(mens));
    while (ini <= fim)
    {
        int meio = (ini + fim) / 2;
        int resultado = strcmp(mens, ExecFunc[meio].Nome);
        if (resultado == 0) // Se encontrou...
            return (this->*ExecFunc[meio].Func)(v);
        if (resultado < 0) fim = meio - 1; else ini = meio + 1;
    }
    return false;
}

//----------------------------------------------------------------------------
bool TVarArqLog::FuncMsg(TVariavel * v)
{
    if (arq < 0)
        return false;
    for (TVariavel * v1 = v + 1; v1 <= Instr::VarAtual; v1++)
    {
        const char * txt = v1->getTxt();
        while (true)
        {
            while (*txt == Instr::ex_barra_n)
                txt++;
            if (*txt == 0)
                break;
            if (pontlog >= (int)sizeof(buflog) - 500)
            {
                safe_write(arq, buflog, pontlog);
                pontlog = 0;
            }
            for (int x = 0; x < 490 && *txt && *txt != Instr::ex_barra_n; x++)
                switch (*txt)
                {
                case Instr::ex_barra_b:
                    txt++;
                    break;
                case Instr::ex_barra_c:
                    if ((txt[1] >= '0' && txt[1] <= '9') ||
                            (txt[1] >= 'A' && txt[1] <= 'J') ||
                            (txt[1] >= 'a' && txt[1] <= 'j'))
                        txt += 2;
                    else
                        txt++;
                    break;
                case Instr::ex_barra_d:
                    if (txt[1] >= '0' && txt[1] <= '7')
                        txt += 2;
                    else
                        txt++;
                    break;
                default:
                    buflog[pontlog++] = *txt++;
                }
            buflog[pontlog++] = '\n';
        }
    }
    return false;
}

//----------------------------------------------------------------------------
bool TVarArqLog::FuncFechar(TVariavel * v)
{
    Fechar();
    return false;
}

//----------------------------------------------------------------------------
bool TVarArqLog::FuncValido(TVariavel * v)
{
    char arqnome[300] = ""; // Nome do arquivo; nulo se n�o for v�lido
    if (Instr::VarAtual >= v + 1)
    {
        copiastr(arqnome, v[1].getTxt(), sizeof(arqnome) - 4);
        if (!arqvalido(arqnome, false))
            *arqnome = 0;
    }
    return Instr::CriarVarInt(v, *arqnome != 0);
}

//----------------------------------------------------------------------------
bool TVarArqLog::FuncExiste(TVariavel * v)
{
    char arqnome[300] = ""; // Nome do arquivo; nulo se n�o for v�lido
    if (Instr::VarAtual >= v + 1)
    {
        copiastr(arqnome, v[1].getTxt(), sizeof(arqnome) - 4);
        if (!arqvalido(arqnome, false))
            *arqnome = 0;
    }
    if (*arqnome == 0)
        return Instr::CriarVarInt(v, 0);
    int tam = strlen(arqnome);
    if (tam >= 4) // Tamanho suficiente
        if (comparaZ(arqnome + tam - 4, ".log") == 0) // Extens�o correta
            tam -= 4;
    strcpy(arqnome + tam, ".log"); // Acerta a extens�o
    struct stat buf;
    if (*arqnome && stat(arqnome, &buf) < 0)
        *arqnome = 0;
    return Instr::CriarVarInt(v, *arqnome != 0);
}

//----------------------------------------------------------------------------
bool TVarArqLog::FuncAbrir(TVariavel * v)
{
    char arqnome[300] = ""; // Nome do arquivo; nulo se n�o for v�lido
    if (Instr::VarAtual >= v + 1)
    {
        copiastr(arqnome, v[1].getTxt(), sizeof(arqnome) - 4);
        if (!arqvalido(arqnome, false))
            *arqnome = 0;
    }
    if (*arqnome)
    {
    // Acerta o nome do arquivo
        int tam = strlen(arqnome);
        if (tam >= 4) // Tamanho suficiente
            if (comparaZ(arqnome + tam - 4, ".log") == 0) // Extens�o correta
                tam -= 4;
        strcpy(arqnome + tam, ".log"); // Acerta a extens�o
    // Abre arquivo
        int descr = open(arqnome, O_WRONLY|O_CREAT|O_APPEND, (mode_t)0666);
        if (descr < 0)
            *arqnome = 0;
        else
        {
        // Fecha arquivo
            Fechar();
        // Anota vari�veis
            arq = descr;
            pontlog = 0;
        // Insere na lista ligada
            Antes = nullptr;
            Depois = Inicio;
            Inicio = this;
            if (Depois)
                Depois->Antes = this;
        }
    }
    return Instr::CriarVarInt(v, *arqnome != 0);
}

//------------------------------------------------------------------------------
int TVarArqLog::FTamanho(const char * instr)
{
    return sizeof(TVarArqLog);
}

//------------------------------------------------------------------------------
int TVarArqLog::FTamanhoVetor(const char * instr)
{
    int total = (unsigned char)instr[Instr::endVetor];
    return (total ? total : 1) * sizeof(TVarArqLog);
}

//------------------------------------------------------------------------------
void TVarArqLog::FRedim(TVariavel * v, TClasse * c, TObjeto * o,
        unsigned int antes, unsigned int depois)
{
    TVarArqLog * ref = reinterpret_cast<TVarArqLog*>(v->endvar);
    for (; antes < depois; antes++)
        ref[antes].Criar();
    for (; depois < antes; depois++)
        ref[depois].Apagar();
}

//------------------------------------------------------------------------------
void TVarArqLog::FMoverEnd(TVariavel * v, void * destino, TClasse * c, TObjeto * o)
{
    VARIAVEL_MOVER_SIMPLES(TVarArqLog)
}

//------------------------------------------------------------------------------
bool TVarArqLog::FGetBool(TVariavel * v) VARIAVEL_FGETINT0(TVarArqLog)
int TVarArqLog::FGetInt(TVariavel * v) VARIAVEL_FGETINT0(TVarArqLog)
double TVarArqLog::FGetDouble(TVariavel * v) VARIAVEL_FGETINT0(TVarArqLog)
const char * TVarArqLog::FGetTxt(TVariavel * v) VARIAVEL_FGETTXT0(TVarArqLog)
