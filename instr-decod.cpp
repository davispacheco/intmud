/* Este programa � software livre; voc� pode redistribuir e/ou
 * modificar nos termos da GNU General Public License V2
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details at www.gnu.org
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "instr.h"
#include "classe.h"
#include "misc.h"

using namespace Instr;

//------------------------------------------------------------------------------
// Acrescenta texto no in�cio de destino
// Retorna: endere�o do fim do texto
static char * copiaini(char * destino, const char * texto)
{
    int total = strlen(texto);
    char * fim = destino;
    while (*fim)
        fim++;
    if (total==0)
        return fim;
    for (char * copia = fim; copia>=destino; copia--)
        copia[total] = copia[0];
    while (*texto)
        *destino++ = *texto++;
    return fim + total;
}

//------------------------------------------------------------------------------
// Decodifica uma instru��o (inverso de Instr::Codif())
// Retorna: true = conseguiu decodificar com sucesso
//          false = erro, destino cont�m a mensagem de erro
bool Instr::Decod(char * destino, const char * origem, int tamanho)
{
    int  expr=0;   // �ndice da express�o num�rica, 0=n�o h�
    int  coment=0; // �ndice do coment�rio, 0=n�o h�
    char nome[40]; // Nome da instru��o
    *nome=0;

// Coment�rio em vari�veis
    if (origem[2] >= cVariaveis)
    {
        for (coment=5; origem[coment]; coment++);
        coment++;
    }

// Anota o nome da instru��o
    *destino=0;
    switch (origem[2])
    {
    case cHerda:         // 1 byte = n�mero de classes
        {
            const char * p = origem+4;
            for (int total=(unsigned char)origem[3]; total; total--)
                while (*p++);
            if (p-origem+10+(unsigned char)origem[3] > tamanho)
            {
                copiastr(destino, "Espa�o insuficiente", tamanho);
                return false;
            }
            destino = copiastr(destino, "herda ");
            p--;
            for (origem+=4; origem<p; origem++,destino++)
            {
                if (*origem==0)
                {
                    destino[0] = ',';
                    destino[1] = ' ';
                    destino++;
                }
                else
                    *destino = *origem;
            }
            *destino=0;
        }
        return true;
    case cExpr:  // Express�o num�rica pura
        expr=3;
        break;
    case cComent: // Coment�rio
        if ((int)strlen(origem+3) + 3 > tamanho)
        {
            copiastr(destino, "Espa�o insuficiente", tamanho);
            return false;
        }
        if (origem[3]==0)
            strcpy(destino, "#");
        else
            sprintf(destino, "# %s", origem+3);
        return true;

// Constrole de fluxo
    case cSe:        strcpy(nome, "se "); expr=5; break;
    case cSenao1:    strcpy(nome, "sen�o"); coment=5; break;
    case cSenao2:    strcpy(nome, "sen�o "); expr=5; break;
    case cFimSe:     strcpy(nome, "fimse"); coment=3; break;
    case cEnquanto:  strcpy(nome, "enquanto "); expr=5; break;
    case cEFim:      strcpy(nome, "efim"); coment=5; break;
    case cRet1:      strcpy(nome, "ret"); coment=3; break;
    case cRet2:      strcpy(nome, "ret "); expr=3; break;
    case cSair:      strcpy(nome, "sair"); coment=5; break;
    case cContinuar: strcpy(nome, "continuar"); coment=5; break;
    case cTerminar:  strcpy(nome, "terminar"); coment=3; break;

// Vari�veis
    case cVariaveis: break;
    case cTxt1:
        sprintf(nome, "txt%d", (unsigned char)origem[4]+1);
        break;
    case cTxt2:
        sprintf(nome, "txt%d", (unsigned char)origem[4]+257);
        break;
    case cIntb0:
    case cIntb1:
    case cIntb2:
    case cIntb3:
    case cIntb4:
    case cIntb5:
    case cIntb6:
    case cIntb7:     strcpy(nome, "int1"); break;
    case cInt8:      strcpy(nome, "int8"); break;
    case cUInt8:     strcpy(nome, "uint8"); break;
    case cInt16:     strcpy(nome, "int16"); break;
    case cUInt16:    strcpy(nome, "uint16"); break;
    case cInt32:     strcpy(nome, "int32"); break;
    case cUInt32:    strcpy(nome, "uint32"); break;
    case cIntInc:    strcpy(nome, "intinc"); break;
    case cIntDec:    strcpy(nome, "intdec"); break;
    case cReal:      strcpy(nome, "real"); break;
    case cRef:       strcpy(nome, "ref"); break;
    case cConstNulo:
    case cConstTxt:
    case cConstNum:
    case cConstExpr:
        strcpy(nome, "const");
        coment=0, expr=5;
        while (origem[expr++]);
        break;
    case cFunc:      strcpy(nome, "func"); break;
    case cVarFunc:   strcpy(nome, "varfunc"); break;

// Vari�veis extras
    case cListaObj:  strcpy(nome, "listaobj"); break;
    case cListaTxt:  strcpy(nome, "listatxt"); break;
    case cListaMsg:  strcpy(nome, "listamsg"); break;
    case cNomeObj:   strcpy(nome, "nomeobj"); break;
    case cLog:       strcpy(nome, "log"); break;
    case cVarTempo:  strcpy(nome, "vartempo"); break;
    case cSocket:    strcpy(nome, "socket"); break;
    case cServ:      strcpy(nome, "serv"); break;
    case cSalvar:    strcpy(nome, "salvar"); break;
    case cProg:      strcpy(nome, "prog"); break;
    case cIndice:    strcpy(nome, "indice"); break;
    default:
        copiastr(destino, "Instru��o n�o existe", tamanho);
        return false;
    }

// Copia nome da instru��o ou vari�vel
    if (origem[2]>cVariaveis)
    {
        if ((int)strlen(nome) + (int)strlen(origem+5) + 20 > tamanho)
        {
            copiastr(destino, "Espa�o insuficiente", tamanho);
            return false;
        }
        sprintf(destino, "%s%s%s %s%s",
                origem[3]&1 ? "comum " : "",
                origem[3]&2 ? "sav " : "",
                nome, origem+5, expr!=0 ? " = " : "");
    }
    else
    {
        if ((int)strlen(nome) + 1 > tamanho)
        {
            copiastr(destino, "Espa�o insuficiente", tamanho);
            return false;
        }
        strcpy(destino, nome);
    }
    while (*destino)
       destino++, tamanho--;

// Verifica se tem coment�rio
    if (coment)
    {
        int total = Num16(origem) - coment;
        assert(total>=0);
        if (total>0)
        {
            if (total + 5 > tamanho)
            {
                copiastr(destino, "Espa�o insuficiente", tamanho);
                return false;
            }
            destino[0] = ' ';
            destino[1] = '#';
            destino[2] = ' ';
            if (total>0)
                memcpy(destino+3, origem+coment, total);
        }
        destino[3+total]=0;
        return true;
    }

// Verifica se tem express�o num�rica
    if (expr==0)
        return true;

// Processamento de express�o num�rica
// Os textos (operandos) s�o precedidos de um byte de 1 a 0x1F, que indica
// a prioridade dos operadores envolvidos.
// Exemplo, um texto "1+2" � precedido de um byte 4.
// Assim, se houver uma multiplica��o, o programa sabe que deve colocar
// o texto "1+2" entre par�nteses.
// No retorno da fun��o, esses bytes de controle s�o retirados
    char * dest_ini = destino;
    const char * dest_fim = destino + tamanho;
    const char * origem_fim = origem + Num16(origem);
    origem += expr;

    while (true)
    {
        int indica=0;
                // Bit 0=1: Apagar a indica��o anterior de operando
                // Bit 1=1: Copiar texto de nome[]
                // Bit 2=1: Processar texto = nome da vari�vel
                // Bit 3=1: Operador unit�rio; nome[] cont�m o texto
                // Bit 4=1: Operador bin�rio; nome[] cont�m o texto
                // Se for operador: far� automaticamente origem++
                // indica=0 -> Comando desconhecido
        *nome=0;
        assert(origem < origem_fim);
        if (destino >= dest_fim-10)
            return false;

    // Para testes - mostra como est� o texto em destino
#if 0
        printf("destino = ");
        for (const char * x1=dest_ini; x1<destino; x1++)
            if (*(unsigned char*)x1>=' ')
                putchar(*x1);
            else
                printf(" [%d] ", *x1);
        putchar('\n'); fflush(stdout);
#endif

    // Verifica o comando
        switch (*origem)
        {
        case ex_fim:    // Fim
        case ex_coment: // Coment�rio
            assert(destino > dest_ini);
            *destino=0;
            for (destino=dest_ini+1; *(unsigned char*)destino>=' '; destino++)
                destino[-1] = destino[0];
            destino[-1]=0;
            assert(*destino==0);
            if (*origem==ex_coment)
            {
                if (dest_fim - destino < 4)
                    return false;
                destino = copiastr(destino, " # ");
                for (origem++; *origem; origem++)
                {
                    if (destino>=dest_fim-2 || *(unsigned char*)origem < ' ')
                        return false;
                    *destino++ = *origem;
                }
            }
            *destino=0;
            return true;

        // Nome de vari�vel ou fun��o (um texto)
        case ex_varabre:     // In�cio do texto + abre colchetes
            indica=2;
            strcpy(nome, "\x01" "[");
            break;
        case ex_ponto:       // Fim do nome da vari�vel
                             // Nesse caso � fim dos par�metros da fun��o
            indica=1+2; // 1 = Apaga a indica��o anterior de operando
                        // 2 = Copiar o nome em nome[]
            if (origem[1]==ex_varfim) // Seguido de ex_varfim: fim do nome
            {
                origem++;
                strcpy(nome, ")");
                break;
            }
            // Caso contr�rio: processegue com o nome
            indica |= 4;
            strcpy(nome, ").");
            break;
        case ex_fecha:       // Fecha colchetes
            indica=1+2+4; // 1 = Apaga a indica��o anterior de operando
                          // 2 = Copiar o nome em nome[]
                          // 4 = Prossegue com o nome
            strcpy(nome, "]");
            break;
        case ex_varini:      // In�cio do texto
            indica=2+4;   // 2 = Copiar o nome em nome[]
                          // 4 = Prossegue com o nome
            strcpy(nome, "\x01");
            break;

        // Valores fixos
        case ex_nulo:
            indica=2;
            strcpy(nome, "\x01" "nulo");
            break;
        case ex_txt: // Texto em ASCIIZ
            *destino++ = 1;
            indica=2; strcpy(nome, "\"");
            while (true)
            {
                if (destino+3 >= dest_fim)
                {
                    *destino=0;
                    return false;
                }
                if (*origem==0)
                    break;
                switch (*origem)
                {
                case ex_txt:
                    *destino++ = '\"';
                    break;
                case ex_barra_n:
                    destino[0] = '\\';
                    destino[1] = 'n';
                    destino+=2;
                    break;
                case ex_barra_b:
                    destino[0] = '\\';
                    destino[1] = 'b';
                    destino+=2;
                    break;
                case ex_barra_c:
                    destino[0] = '\\';
                    destino[1] = 'c';
                    destino+=2;
                    break;
                case ex_barra_d:
                    destino[0] = '\\';
                    destino[1] = 'd';
                    destino+=2;
                    break;
                case '\"':
                case '\\':
                    *destino++= '\"';
                default:
                    if (*(unsigned char*)origem >= ' ')
                        *destino++ = *origem;
                    else
                    {
                        *destino=0;
                        return false;
                    }
                }
                origem++;
            }
            break;
        case ex_num0:
        case ex_num1:
        case ex_num8p:
        case ex_num16p:
        case ex_num32p:
        case ex_num8n:
        case ex_num16n:
        case ex_num32n:
            {
                unsigned int valor = 0; // Valor num�rico sem sinal
                bool negativo = false; // Se � negativo
                int  virgula = 0;   // Casas ap�s a v�rgula
            // Acerta vari�veis valor e negativo
                switch (*origem)
                {
                case ex_num1:
                    valor=1;
                case ex_num0:
                    origem++;
                    break;
                case ex_num8n:
                    negativo=true;
                case ex_num8p:
                    valor=(unsigned char)origem[1];
                    origem+=2;
                    break;
                case ex_num16n:
                    negativo=true;
                case ex_num16p:
                    valor=Num16(origem+1);
                    origem+=3;
                    break;
                case ex_num32n:
                    negativo=true;
                case ex_num32p:
                    valor=Num32(origem+1);
                    origem+=5;
                    break;
                }
            // Acerta vari�vel virgula
                while (*origem>=ex_div1 && *origem<=ex_div6)
                    switch (*origem++)
                    {
                    case ex_div1: virgula++; break;
                    case ex_div2: virgula+=2; break;
                    case ex_div3: virgula+=3; break;
                    case ex_div4: virgula+=4; break;
                    case ex_div5: virgula+=5; break;
                    case ex_div6: virgula+=6; break;
                    }
            // Compensa "origem++", logo ap�s o switch
                origem--;
            // Zero � sempre zero
                if (valor==0)
                {
                    strcpy(nome, "\x01" "0");
                    indica=2;
                    break;
                }
            // Obt�m em nome a string correspondente ao n�mero
                char * d = nome;
                while (valor>0)
                    *d++=valor%10+'0', valor/=10;
            // Obt�m o n�mero de d�gitos
                int digitos = d-nome;
                if (digitos <= virgula)
                    digitos = virgula+1;
            // Verifica se tem espa�o suficiente
                if (dest_fim - destino < digitos+4)
                    return false;
            // Anota o n�mero
                *destino++ = 1;
                if (negativo)
                    *destino++ = '-';
                while (digitos>0)
                {
                    if (digitos==virgula)
                        *destino++ = '.';
                    digitos--;
                    *destino++ = (&nome[digitos]>=d ? '0' : nome[digitos]);
                }
                indica=0x80; // Indica que processou
                break;
            }

        // Operadores
        case exo_virgula:      strcpy(nome, ", ");   indica=16; break;
        case exo_neg:          strcpy(nome, "-");    indica=8;  break;
        case exo_exclamacao:   strcpy(nome, "!");    indica=8;  break;
        case exo_mul:          strcpy(nome, " * ");  indica=16; break;
        case exo_div:          strcpy(nome, " / ");  indica=16; break;
        case exo_porcent:      strcpy(nome, " % ");  indica=16; break;
        case exo_add:          strcpy(nome, " + ");  indica=16; break;
        case exo_sub:          strcpy(nome, " - ");  indica=16; break;
        case exo_menor:        strcpy(nome, " < ");  indica=16; break;
        case exo_menorigual:   strcpy(nome, " <= "); indica=16; break;
        case exo_maior:        strcpy(nome, " > ");  indica=16; break;
        case exo_maiorigual:   strcpy(nome, " >= "); indica=16; break;
        case exo_igual:        strcpy(nome, " = ");  indica=16; break;
        case exo_diferente:    strcpy(nome, " != "); indica=16; break;
        case exo_e:            strcpy(nome, " & ");  indica=16; break;
        case exo_ou:           strcpy(nome, " | ");  indica=16; break;
        case exo_igualmul:     strcpy(nome, " *= "); indica=16; break;
        case exo_igualdiv:     strcpy(nome, " /= "); indica=16; break;
        case exo_igualporcent: strcpy(nome, " %= "); indica=16; break;
        case exo_igualadd:     strcpy(nome, " += "); indica=16; break;
        case exo_igualsub:     strcpy(nome, " -= "); indica=16; break;
        case exo_ee:      indica=0x80; break;
        case exo_ouou:    indica=0x80; break;
        }
        origem++;

    // Se nenhuma a��o - erro nos dados do comando
        assert(indica!=0);
        //printf("indica=%d\n", indica); fflush(stdout);

    // Executa a��es conforme vari�vel indica
        if (indica&1) // Apagar a indica��o anterior de operando
        {
            destino--;
            char * p = destino;
            while (*(unsigned char*)p>=' ')
            {
                p--;
                assert(p>=dest_ini);
            }
            memcpy(p, p+1, destino-p);
        }
        if (indica&2) // Copiar texto de nome[]
        {
            //printf("copia: %s\n", nome); fflush(stdout);
            if (destino + strlen(nome) + 1 >= dest_fim)
                return false;
            destino = copiastr(destino, nome);
        }
        if (indica&4) // Processar texto = nome da vari�vel
        {
            while (true)
            {
                if (destino + 3 >= dest_fim)
                    return false;
            // Caracter normal - faz parte do nome
                if (*(unsigned char*)origem>=' ')
                    *destino++ = *origem++;
            // Ponto - pode ser um ponto ou fim do nome
                else if (*origem==ex_ponto)
                {
                    origem++;
                    if (*origem==ex_varfim)
                    {
                        origem++;
                        break;
                    }
                    *destino++ = '.';
                }
            // Arg - in�cio dos argumentos da fun��o
                else if (*origem==ex_arg)
                {
                    origem++;
                    *destino++ = '(';
                    break;
                }
            // Abre colchetes - segue express�o num�rica
                else if (*origem==ex_abre)
                {
                    origem++;
                    *destino++ = '[';
                    break;
                }
                else
                    assert(0);
            }
        }
        if (indica&8) // Operador unit�rio
        {
            //printf("unit�rio: %s\n", nome); fflush(stdout);
            int op = Instr::Prioridade(origem[-1]);
            assert(op!=0);
        // Recua at� operando anterior
            char * p = destino-1;
            for (; *(unsigned char*)p>=' '; p--)
                assert(p>dest_ini);
        // Decide se deve colocar entre par�nteses
            if (op < *p)
            {
                strcat(nome, "(");
                *destino++=')';
            }
            *p++ = op;
        // Anota o texto
            if (destino + strlen(nome) + 1 > dest_fim)
                return false;
            *destino=0;
            destino = copiaini(p, nome);
        }
        if (indica&16) // Operador bin�rio
        {
            //printf("bin�rio: %s\n", nome); fflush(stdout);
            const char * txtprimeiro = "";
            int op = Instr::Prioridade(origem[-1]);
            assert(op!=0);
        // Recua p2 at� operando anterior
            char * p2 = destino-1;
            for (; *(unsigned char*)p2>=' '; p2--)
                assert(p2>dest_ini);
        // Recua p1 mais um operador
            char * p1 = p2-1;
            for (; *(unsigned char*)p1>=' '; p1--)
                assert(p1>dest_ini);
        // Decide se deve colocar p1 entre par�nteses
            if (op < *p1)
            {
                copiaini(nome, ")");
                txtprimeiro = "(";
            }
        // Decide se deve colocar p2 entre par�nteses
            if (op <= *p2)
            {
                strcat(nome, "(");
                *destino++=')';
            }
        // Anota nome
            if (*nome==0)
                strcpy(nome, " ");
            if (destino + strlen(nome) + 1 > dest_fim)
                return false;
            *destino=0;
            destino = copiaini(p2+1, nome+1);
            *p2 = *nome;
        // Acerta in�cio de p1
            *p1 = op;
            if (*txtprimeiro)
            {
                if (destino + strlen(txtprimeiro) + 1 > dest_fim)
                    return false;
                *destino=0;
                destino = copiaini(p1+1, txtprimeiro);
            }
        }
    }
    assert(0);
    return false;
}