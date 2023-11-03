#ifndef VAR_BASICO_H
#define VAR_BASICO_H

class TVariavel;
class TVarInfo;

//----------------------------------------------------------------------------
/// Vari�veis txt1 a txt256
const TVarInfo * VarBaseTxt1();

/// Vari�veis txt257 a txt512
const TVarInfo * VarBaseTxt2();

/// Vari�veis int1
const TVarInfo * VarBaseInt1();

/// Vari�veis int8
const TVarInfo * VarBaseInt8();

/// Vari�veis uint8
const TVarInfo * VarBaseUInt8();

/// Vari�veis int16
const TVarInfo * VarBaseInt16();

/// Vari�veis uint16
const TVarInfo * VarBaseUInt16();

/// Vari�veis int32
const TVarInfo * VarBaseInt32();

/// Vari�veis uint32
const TVarInfo * VarBaseUInt32();

/// Vari�veis real
const TVarInfo * VarBaseReal();

/// Vari�veis real2
const TVarInfo * VarBaseReal2();

/// Altera valor num�rico de vetor de int1
void SetVetorInt1(TVariavel * v, int valor);

//----------------------------------------------------------------------------

#endif
