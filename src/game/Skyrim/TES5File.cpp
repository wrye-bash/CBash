/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is CBash code.
 *
 * The Initial Developer of the Original Code is
 * Waruddar.
 * Portions created by the Initial Developer are Copyright (C) 2010
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */
// TES5File.cpp
#include "common/Common.h"
#include "common/GenericRecord.h"
#include "TES5File.h"
#include "SkyrimCommon.h"

TES5File::TES5File(Collection *_Parent, char * FileName, char * ModName, const uint32_t _flags):
    ModFile(_Parent, FileName, ModName, _flags)
    {
    //
    }

TES5File::~TES5File()
    {
    //
    }

void TES5File::SetFilter(bool inclusive, boost::unordered_set<uint32_t> &RecordTypes, boost::unordered_set<FORMID> &WorldSpaces) {
  filter_inclusive = inclusive;
  filter_records = RecordTypes;
  filter_wspaces = WorldSpaces;
}

int32_t TES5File::LoadTES4()
    {
    if(TES4.IsLoaded() || !Open())
        {
        if(!TES4.IsLoaded() && !Open())
            printer("TES5File::LoadTES4: Error - Unable to load the TES4 record for mod \"%s\". The mod is not open for reading.\n", ModName);
        return 0;
        }
    buffer_position = buffer_start + 4;

    uint32_t recSize = 0;
    recSize = *(uint32_t *)buffer_position;
    buffer_position += 4;

    TES4.flags = *(uint32_t *)buffer_position;
    buffer_position += 4;

    TES4.formID = *(FORMID *)buffer_position;
    buffer_position += 4;

    TES4.flagsUnk = *(uint32_t *)buffer_position;
    buffer_position += 4;

    TES4.formVersion = *(uint16_t *)buffer_position;
    buffer_position += 2;

    TES4.versionControl2[0] = *(uint8_t *)buffer_position;
    buffer_position++;

    TES4.versionControl2[1] = *(uint8_t *)buffer_position;
    buffer_position++;

    TES4.recData = buffer_position;
    TES4.Read();
    TES4.IsChanged(true); //prevents the record from ever being unloaded
    buffer_position += recSize;
    return 1;
    }

int32_t TES5File::Load(RecordOp &read_parser, RecordOp &indexer, std::vector<FormIDResolver *> &Expanders, std::vector<Record *> &DeletedRecords)
    {
    enum IgTopRecords {
        eIgGMST = REV32(GMST) | 0x00001000, //Record::fIsIgnored
        eIgTXST = REV32(TXST) | 0x00001000,
        eIgGLOB = REV32(GLOB) | 0x00001000,
        eIgCLAS = REV32(CLAS) | 0x00001000,
        eIgFACT = REV32(FACT) | 0x00001000,
        eIgHDPT = REV32(HDPT) | 0x00001000,
        eIgHAIR = REV32(HAIR) | 0x00001000,
        eIgEYES = REV32(EYES) | 0x00001000,
        eIgRACE = REV32(RACE) | 0x00001000,
        eIgSOUN = REV32(SOUN) | 0x00001000,
        eIgASPC = REV32(ASPC) | 0x00001000,
        eIgMGEF = REV32(MGEF) | 0x00001000,
        eIgSCPT = REV32(SCPT) | 0x00001000,
        eIgLTEX = REV32(LTEX) | 0x00001000,
        eIgENCH = REV32(ENCH) | 0x00001000,
        eIgSPEL = REV32(SPEL) | 0x00001000,
        eIgACTI = REV32(ACTI) | 0x00001000,
        eIgTACT = REV32(TACT) | 0x00001000,
        eIgARMO = REV32(ARMO) | 0x00001000,
        eIgBOOK = REV32(BOOK) | 0x00001000,
        eIgCONT = REV32(CONT) | 0x00001000,
        eIgDOOR = REV32(DOOR) | 0x00001000,
        eIgINGR = REV32(INGR) | 0x00001000,
        eIgLIGH = REV32(LIGH) | 0x00001000,
        eIgMISC = REV32(MISC) | 0x00001000,
        eIgAPPA = REV32(APPA) | 0x00001000,
        eIgSTAT = REV32(STAT) | 0x00001000,
        eIgSCOL = REV32(SCOL) | 0x00001000,
        eIgMSTT = REV32(MSTT) | 0x00001000,
        eIgPWAT = REV32(PWAT) | 0x00001000,
        eIgGRAS = REV32(GRAS) | 0x00001000,
        eIgTREE = REV32(TREE) | 0x00001000,
        eIgFLOR = REV32(FLOR) | 0x00001000,
        eIgFURN = REV32(FURN) | 0x00001000,
        eIgWEAP = REV32(WEAP) | 0x00001000,
        eIgAMMO = REV32(AMMO) | 0x00001000,
        eIgNPC_ = REV32(NPC_) | 0x00001000,
        eIgLVLN = REV32(LVLN) | 0x00001000,
        eIgKEYM = REV32(KEYM) | 0x00001000,
        eIgALCH = REV32(ALCH) | 0x00001000,
        eIgIDLM = REV32(IDLM) | 0x00001000,
        eIgCOBJ = REV32(COBJ) | 0x00001000,
        eIgPROJ = REV32(PROJ) | 0x00001000,
        eIgSLGM = REV32(SLGM) | 0x00001000,
        eIgLVLI = REV32(LVLI) | 0x00001000,
        eIgWTHR = REV32(WTHR) | 0x00001000,
        eIgCLMT = REV32(CLMT) | 0x00001000,
        eIgREGN = REV32(REGN) | 0x00001000,
        eIgNAVI = REV32(NAVI) | 0x00001000,
        eIgCELL = REV32(CELL) | 0x00001000,
        eIgWRLD = REV32(WRLD) | 0x00001000,
        eIgDIAL = REV32(DIAL) | 0x00001000,
        eIgQUST = REV32(QUST) | 0x00001000,
        eIgIDLE = REV32(IDLE) | 0x00001000,
        eIgPACK = REV32(PACK) | 0x00001000,
        eIgCSTY = REV32(CSTY) | 0x00001000,
        eIgLSCR = REV32(LSCR) | 0x00001000,
        eIgLVSP = REV32(LVSP) | 0x00001000,
        eIgANIO = REV32(ANIO) | 0x00001000,
        eIgWATR = REV32(WATR) | 0x00001000,
        eIgEFSH = REV32(EFSH) | 0x00001000,
        eIgEXPL = REV32(EXPL) | 0x00001000,
        eIgDEBR = REV32(DEBR) | 0x00001000,
        eIgIMGS = REV32(IMGS) | 0x00001000,
        eIgIMAD = REV32(IMAD) | 0x00001000,
        eIgFLST = REV32(FLST) | 0x00001000,
        eIgPERK = REV32(PERK) | 0x00001000,
        eIgBPTD = REV32(BPTD) | 0x00001000,
        eIgADDN = REV32(ADDN) | 0x00001000,
        eIgAVIF = REV32(AVIF) | 0x00001000,
        eIgCAMS = REV32(CAMS) | 0x00001000,
        eIgCPTH = REV32(CPTH) | 0x00001000,
        eIgVTYP = REV32(VTYP) | 0x00001000,
        eIgIPCT = REV32(IPCT) | 0x00001000,
        eIgIPDS = REV32(IPDS) | 0x00001000,
        eIgARMA = REV32(ARMA) | 0x00001000,
        eIgECZN = REV32(ECZN) | 0x00001000,
        eIgMESG = REV32(MESG) | 0x00001000,
        eIgRGDL = REV32(RGDL) | 0x00001000,
        eIgDOBJ = REV32(DOBJ) | 0x00001000,
        eIgLGTM = REV32(LGTM) | 0x00001000,
        eIgMUSC = REV32(MUSC) | 0x00001000,
        eIgKYWD = REV32(KYWD) | 0x00001000,
        eIgLCRT = REV32(LCRT) | 0x00001000,
        eIgAACT = REV32(AACT) | 0x00001000,
        eIgSCRL = REV32(SCRL) | 0x00001000,
        eIgCLDC = REV32(CLDC) | 0x00001000,
        eIgHAZD = REV32(HAZD) | 0x00001000,
        eIgSPGD = REV32(SPGD) | 0x00001000,
        eIgRFCT = REV32(RFCT) | 0x00001000,
        eIgMATT = REV32(MATT) | 0x00001000,
        eIgLCTN = REV32(LCTN) | 0x00001000,
        eIgFSTP = REV32(FSTP) | 0x00001000,
        eIgFSTS = REV32(FSTS) | 0x00001000,
        eIgSMBN = REV32(SMBN) | 0x00001000,
        eIgSMQN = REV32(SMQN) | 0x00001000,
        eIgSMEN = REV32(SMEN) | 0x00001000,
        eIgDLBR = REV32(DLBR) | 0x00001000,
        eIgMUST = REV32(MUST) | 0x00001000,
        eIgDLVW = REV32(DLVW) | 0x00001000,
        eIgWOOP = REV32(WOOP) | 0x00001000,
        eIgSHOU = REV32(SHOU) | 0x00001000,
        eIgEQUP = REV32(EQUP) | 0x00001000,
        eIgRELA = REV32(RELA) | 0x00001000,
        eIgSCEN = REV32(SCEN) | 0x00001000,
        eIgASTP = REV32(ASTP) | 0x00001000,
        eIgOTFT = REV32(OTFT) | 0x00001000,
        eIgARTO = REV32(ARTO) | 0x00001000,
        eIgMATO = REV32(MATO) | 0x00001000,
        eIgMOVT = REV32(MOVT) | 0x00001000,
        eIgSNDR = REV32(SNDR) | 0x00001000,
        eIgDUAL = REV32(DUAL) | 0x00001000,
        eIgSNCT = REV32(SNCT) | 0x00001000,
        eIgSOPM = REV32(SOPM) | 0x00001000,
        eIgCOLL = REV32(COLL) | 0x00001000,
        eIgCLFM = REV32(CLFM) | 0x00001000,
        eIgREVB = REV32(REVB) | 0x00001000,
    };

    if(Flags.IsNoLoad || Flags.IsCreateNew || !file_map.is_open() || Flags.LoadedGRUPs)
        {
        if(!(Flags.IsNoLoad || Flags.IsCreateNew))
            {
            if(!file_map.is_open())
                printer("TES5File::Load: Error - Unable to load mod \"%s\". The mod is not open.\n", ModName);
            else
                printer("TES5File::Load: Error - Unable to load mod \"%s\". The mod is already loaded.\n", ModName);
            }
        return 0;
        }

    // Load translation strings
    TES4.LoadStringLookups(FileName);

    Flags.LoadedGRUPs = true;
    unsigned char *group_buffer_end = NULL;
    uint32_t GRUPSize;
    uint32_t GRUPLabel;
    boost::unordered_set<uint32_t> UsedFormIDs;

    RecordOp skip_parser;
    RecordOp &parser = Flags.IsFullLoad ? read_parser : skip_parser;

    RecordProcessor processor(this, FormIDHandler, Flags, UsedFormIDs);
    processor.SetFilter(filter_inclusive, filter_records, filter_wspaces);

    while(buffer_position < buffer_end){
        buffer_position += 4; //Skip "GRUP"
        GRUPSize = *(uint32_t *)buffer_position;
        group_buffer_end = buffer_position + GRUPSize - 4;
        buffer_position += 4;
        GRUPLabel = *(uint32_t *)buffer_position;
        buffer_position += 8; //Skip type (tops will all == 0)

        //printer("%c%c%c%c\n", ((char *)&GRUPLabel)[0], ((char *)&GRUPLabel)[1], ((char *)&GRUPLabel)[2], ((char *)&GRUPLabel)[3]);
        switch(GRUPLabel)
        {
        case eIgAACT:
        case REV32(AACT):
            AACT.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgACTI:
        case REV32(ACTI):
            ACTI.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgADDN:
        case REV32(ADDN):
            ADDN.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgALCH:
        case REV32(ALCH):
            ALCH.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgAMMO:
        case REV32(AMMO):
            buffer_position = group_buffer_end;
            //AMMO.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgANIO:
        case REV32(ANIO):
            ANIO.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
      //case eIgAPPA:           // Same as REV32(APPA)
        case REV32(APPA):
            APPA.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
      //case eIgARMA:           // Same as REV32(ARMA)
        case REV32(ARMA):
            buffer_position = group_buffer_end;
            //ARMA.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
      //case eIgARMO:           // Same as REV32(ARMO)
        case REV32(ARMO):
            buffer_position = group_buffer_end;
            //ARMO.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
      //case eIgARTO:           // Same as REV32(ARTO)
        case REV32(ARTO):
            ARTO.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
      //case eIgASPC:           // Same as REV32(ASPC)
        case REV32(ASPC):
            ASPC.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
      //case eIgASTP:           // Same as REV32(ASTP)
        case REV32(ASTP):
            ASTP.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
      //case eIgAVIF:           // Same as REV32(AVIF)
        case REV32(AVIF):
            buffer_position = group_buffer_end;
            //AVIF.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgBOOK:
        case REV32(BOOK):
            buffer_position = group_buffer_end;
            //BOOK.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
      //case eIgBPTD:           // Same as REV32(BPTD)
        case REV32(BPTD):
            buffer_position = group_buffer_end;
            //BPTD.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgCAMS:
        case REV32(CAMS):
            buffer_position = group_buffer_end;
            //CAMS.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgCELL:
        case REV32(CELL):
            CELL.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgCLAS:
        case REV32(CLAS):
            buffer_position = group_buffer_end;
            //CLAS.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgCLDC:
        case REV32(CLDC):
            // Empty GRUP
            buffer_position = group_buffer_end;
            break;
        case eIgCLFM:
        case REV32(CLFM):
            buffer_position = group_buffer_end;
            //CLFM.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgCLMT:
        case REV32(CLMT):
            buffer_position = group_buffer_end;
            //CLMT.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgCOBJ:
        case REV32(COBJ):
            buffer_position = group_buffer_end;
            //COBJ.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgCOLL:
        case REV32(COLL):
            COLL.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgCONT:
        case REV32(CONT):
            buffer_position = group_buffer_end;
            //CONT.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
      //case eIgCPTH:           // Same as REV32(CPTH)
        case REV32(CPTH):
            buffer_position = group_buffer_end;
            //CPTH.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
      //case eIgCSTY:           // Same as REV32(CSTY)
        case REV32(CSTY):
            buffer_position = group_buffer_end;
            //CSTY.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgDEBR:
        case REV32(DEBR):
            buffer_position = group_buffer_end;
            //DEBR.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgDIAL:
        case REV32(DIAL):
            buffer_position = group_buffer_end;
            //DIAL.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgDLBR:
        case REV32(DLBR):
            buffer_position = group_buffer_end;
            //DLBR.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgDLVW:
        case REV32(DLVW):
            buffer_position = group_buffer_end;
            //DLVW.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgDOBJ:
        case REV32(DOBJ):
            buffer_position = group_buffer_end;
            //DOBJ.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgDOOR:
        case REV32(DOOR):
            buffer_position = group_buffer_end;
            //DOOR.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
      //case eIgDUAL:           // Same as REV32(DUAL)
        case REV32(DUAL):
            buffer_position = group_buffer_end;
            //DUAL.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgECZN:
        case REV32(ECZN):
            buffer_position = group_buffer_end;
            //ECZN.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgEFSH:
        case REV32(EFSH):
            buffer_position = group_buffer_end;
            //EFSH.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgENCH:
        case REV32(ENCH):
            buffer_position = group_buffer_end;
            //ENCH.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
      //case eIgEQUP:           // Same as REV32(EQUP)
        case REV32(EQUP):
            EQUP.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
      //case eIgEXPL:           // Same as REV32(EXPL)
        case REV32(EXPL):
            buffer_position = group_buffer_end;
            //EXPL.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
      //case eIgEYES:           // Same as REV32(EYES)
        case REV32(EYES):
            buffer_position = group_buffer_end;
            //EYES.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgFACT:
        case REV32(FACT):
            buffer_position = group_buffer_end;
            //FACT.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgFLOR:
        case REV32(FLOR):
            buffer_position = group_buffer_end;
            //FLOR.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgFLST:
        case REV32(FLST):
            buffer_position = group_buffer_end;
            //FLST.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
      //case eIgFSTP:           // Same as REV32(FSTP)
        case REV32(FSTP):
            buffer_position = group_buffer_end;
            //FSTP.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
      //case eIgFSTS:           // Same as REV32(FSTS)
        case REV32(FSTS):
            buffer_position = group_buffer_end;
            //FSTS.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
      //case eIgFURN:           // Same as REV32(FURN)
        case REV32(FURN):
            buffer_position = group_buffer_end;
            //FURN.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgGLOB:
        case REV32(GLOB):
            buffer_position = group_buffer_end;
            //GLOB.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgGMST:
        case REV32(GMST):
            buffer_position = group_buffer_end;
            //GMST.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
      //case eIgGRAS:           // Same as REV32(GRAS)
        case REV32(GRAS):
            buffer_position = group_buffer_end;
            //GRAS.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgHAIR:
        case REV32(HAIR):
            // Empty GRUP
            buffer_position = group_buffer_end;
            break;
        case eIgHAZD:
        case REV32(HAZD):
            buffer_position = group_buffer_end;
            //HAZD.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgHDPT:
        case REV32(HDPT):
            buffer_position = group_buffer_end;
            //HDPT.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgIDLE:
        case REV32(IDLE):
            buffer_position = group_buffer_end;
            //IDLE.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgIDLM:
        case REV32(IDLM):
            buffer_position = group_buffer_end;
            //IDLM.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgIMAD:
        case REV32(IMAD):
            buffer_position = group_buffer_end;
            //IMAD.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgIMGS:
        case REV32(IMGS):
            buffer_position = group_buffer_end;
            //IMGS.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgINGR:
        case REV32(INGR):
            buffer_position = group_buffer_end;
            //INGR.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
      //case eIgIPCT:           // Same as REV32(IPCT)
        case REV32(IPCT):
            buffer_position = group_buffer_end;
            //IPCT.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
      //case eIgIPDS:           // Same as REV32(IPDS)
        case REV32(IPDS):
            buffer_position = group_buffer_end;
            //IPDS.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgKEYM:
        case REV32(KEYM):
            buffer_position = group_buffer_end;
            //KEYM.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
      //case eIgKYWD:           // Same as REV32(KYWD)
        case REV32(KYWD):
            KYWD.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgLCRT:
        case REV32(LCRT):
            buffer_position = group_buffer_end;
            //LCRT.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgLCTN:
        case REV32(LCTN):
            buffer_position = group_buffer_end;
            //LCTN.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgLGTM:
        case REV32(LGTM):
            buffer_position = group_buffer_end;
            //LGTM.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgLIGH:
        case REV32(LIGH):
            buffer_position = group_buffer_end;
            //LIGH.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
      //case eIgLSCR:           // Same as REV32(LSCR)
        case REV32(LSCR):
            buffer_position = group_buffer_end;
            //LSCR.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
      //case eIgLTEX:           // Same as REV32(LTEX)
        case REV32(LTEX):
            LTEX.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
      //case eIgLVLI:           // Same as REV32(LVLI)
        case REV32(LVLI):
            LVLI.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
      //case eIgLVLN:           // Same as REV32(LVLN)
        case REV32(LVLN):
            LVLN.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
      //case eIgLVSP:           // Same as REV32(LVSP)
        case REV32(LVSP):
            LVSP.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgMATO:
        case REV32(MATO):
            buffer_position = group_buffer_end;
            //MATO.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgMATT:
        case REV32(MATT):   // EDID: MaterialInsect (new record-type)
            MATT.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgMESG:
        case REV32(MESG):
            buffer_position = group_buffer_end;
            //MESG.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgMGEF:
        case REV32(MGEF):
            buffer_position = group_buffer_end;
            //MGEF.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgMISC:
        case REV32(MISC):
            buffer_position = group_buffer_end;
            //MISC.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgMOVT:
        case REV32(MOVT):
            buffer_position = group_buffer_end;
            //MOVT.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
      //case eIgMSTT:           // Same as REV32(MSTT)
        case REV32(MSTT):
            buffer_position = group_buffer_end;
            //MSTT.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
      //case eIgMUSC:           // Same as REV32(MUSC)
        case REV32(MUSC):
            buffer_position = group_buffer_end;
            //MUSC.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
      //case eIgMUST:           // Same as REV32(MUST)
        case REV32(MUST):
            buffer_position = group_buffer_end;
            //MUST.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgNAVI:
        case REV32(NAVI):
            buffer_position = group_buffer_end;
            //NAVI.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
      //case eIgNPC_:           // Same as REV32(NPC_)
        case REV32(NPC_):
            buffer_position = group_buffer_end;
            //NPC.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
      //case eIgOTFT:           // Same as REV32(OTFT)
        case REV32(OTFT):
            OTFT.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgPACK:
        case REV32(PACK):
            buffer_position = group_buffer_end;
            //PACK.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgPERK:
        case REV32(PERK):
            buffer_position = group_buffer_end;
            //PERK.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
      //case eIgPROJ:           // Same as REV32(PROJ)
        case REV32(PROJ):
            buffer_position = group_buffer_end;
            //PROJ.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
      //case eIgPWAT:           // Same as REV32(PWAT)
        case REV32(PWAT):
            // Empyt GRUP
            buffer_position = group_buffer_end;
            break;
      //case eIgQUST:           // Same as REV32(QUST)
        case REV32(QUST):
            buffer_position = group_buffer_end;
            //QUST.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgRACE:
        case REV32(RACE):
            buffer_position = group_buffer_end;
            //RACE.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgREGN:
        case REV32(REGN):
            buffer_position = group_buffer_end;
            //REGN.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgRELA:
        case REV32(RELA):
            buffer_position = group_buffer_end;
            //RELA.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgREVB:
        case REV32(REVB):
            buffer_position = group_buffer_end;
            //REVG.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgRFCT:
        case REV32(RFCT):
            buffer_position = group_buffer_end;
            //RFCT.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgRGDL:
        case REV32(RGDL):
            // Empty GRUP
            buffer_position = group_buffer_end;
            break;
        case eIgSCEN:
        case REV32(SCEN):
            buffer_position = group_buffer_end;
            //SCNE.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgSCOL:
        case REV32(SCOL):
            // Empty GRUP
            buffer_position = group_buffer_end;
            break;
        case eIgSCPT:
        case REV32(SCPT):
            buffer_position = group_buffer_end;
            //SCPT.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgSCRL:
        case REV32(SCRL):
            buffer_position = group_buffer_end;
            //SCRL.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgSHOU:
        case REV32(SHOU):
            SHOU.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgSLGM:
        case REV32(SLGM):
            buffer_position = group_buffer_end;
            //SLGM.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgSMBN:
        case REV32(SMBN):
            buffer_position = group_buffer_end;
            //SMBN.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgSMEN:
        case REV32(SMEN):
            buffer_position = group_buffer_end;
            //SMEN.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgSMQN:
        case REV32(SMQN):
            buffer_position = group_buffer_end;
            //SMQN.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgSNCT:
        case REV32(SNCT):
            buffer_position = group_buffer_end;
            //SNCT.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgSNDR:
        case REV32(SNDR):
            buffer_position = group_buffer_end;
            //SNDR.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgSOPM:
        case REV32(SOPM):
            buffer_position = group_buffer_end;
            //SOPM.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgSOUN:
        case REV32(SOUN):
            buffer_position = group_buffer_end;
            //SOUN.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
      //case eIgSPEL:           // Same as REV32(SPEL)
        case REV32(SPEL):
            buffer_position = group_buffer_end;
            //SPEL.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
      //case eIgSPGD:           // Same as REV32(SPGD)
        case REV32(SPGD):
            buffer_position = group_buffer_end;
            //SPGD.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
      //case eIgSTAT:           // Same as REV32(STAT)
        case REV32(STAT):
            buffer_position = group_buffer_end;
            //STAT.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgTACT:
        case REV32(TACT):
            buffer_position = group_buffer_end;
            //TACT.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
      //case eIgTREE:           // Same as REV32(TREE)
        case REV32(TREE):
            buffer_position = group_buffer_end;
            //TREE.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
      //case eIgTXST:           // Same as REV32(TXST)
        case REV32(TXST):
            TXST.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
      //case eIgVTYP:           // Same as REV32(VTYP)
        case REV32(VTYP):
            VTYP.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgWATR:
        case REV32(WATR):
            buffer_position = group_buffer_end;
            //WATR.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgWEAP:
        case REV32(WEAP):
            buffer_position = group_buffer_end;
            //WEAP.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        case eIgWOOP:
        case REV32(WOOP):
            WOOP.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
      //case eIgWRLD:           // Same as REV32(WRLD)
        case REV32(WRLD):
            WRLD.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName, read_parser, CELL);
            break;
      //case eIgWTHR:           // Same as REV32(WTHR)
        case REV32(WTHR):
            buffer_position = group_buffer_end;
            //WTHR.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
            break;
        default:
            if(GRUPLabel == 0 && GRUPSize == 0)
            {
                printer("TES5File::Read: Warning - Unknown record group (%c%c%c%c) encountered in mod \"%s\". Bad file structure, zeros found past end of groups.\n", ((char *)&GRUPLabel)[0], ((char *)&GRUPLabel)[1], ((char *)&GRUPLabel)[2], ((char *)&GRUPLabel)[3], ModName);
                return 1;
            }
            //else
            //    printer("TES5File::Read: Error - Unknown record group (%c%c%c%c) encountered in mod \"%s\". ", ((char *)&GRUPLabel)[0], ((char *)&GRUPLabel)[1], ((char *)&GRUPLabel)[2], ((char *)&GRUPLabel)[3], ModName);

            if(GRUPSize == 0)
            {
                printer("Unable to continue loading.\n");
                return 1;
            }
            else
            {
                //printer("Attempting to skip and continue loading.\n");
                buffer_position = group_buffer_end;
            }
            break;
        }; // end swtich
    }; // end whle

    FormIDHandler.IsEmpty = UsedFormIDs.empty();
    //Testing snippet
    //if(Flags.IsFullLoad)
    //    {
    //    RecordChanger changer(FormIDHandler, Expanders);
    //    VisitAllRecords(changer);
    //    }
    return 1;
    }

uint32_t TES5File::GetNumRecords(const uint32_t &RecordType)
    {
    switch(RecordType)
    {
    case REV32(AACT):
        return (uint32_t)AACT.pool.used_object_capacity();
    /*
    case REV32(ACHR):
        return (uint32_t)CELL.achr_pool.used_object_capacity();
    */
    case REV32(ACTI):
        return (uint32_t)ACTI.pool.used_object_capacity();
    case REV32(ADDN):
        return (uint32_t)ADDN.pool.used_object_capacity();
    case REV32(ALCH):
        return (uint32_t)ALCH.pool.used_object_capacity();
    /*
    case REV32(AMMO):
        return (uint32_t)AMMO.pool.used_object_capacity();
    */
    case REV32(ANIO):
        return (uint32_t)ANIO.pool.used_object_capacity();
    case REV32(APPA):
        return (uint32_t)APPA.pool.used_object_capacity();
    /*
    case REV32(ARMA):
        return (uint32_t)ARMA.pool.used_object_capacity();
    case REV32(ARMO):
        return (uint32_t)ARMO.pool.used_object_capacity();
    */
    case REV32(ARTO):
        return (uint32_t)ARTO.pool.used_object_capacity();
    case REV32(ASPC):
        return (uint32_t)ASPC.pool.used_object_capacity();
    case REV32(ASTP):
        return (uint32_t)ASTP.pool.used_object_capacity();
    /*
    case REV32(AVIF):
        return (uint32_t)AVIF.pool.used_object_capacity();
    case REV32(BOOK):
        return (uint32_t)BOOK.pool.used_object_capacity();
    case REV32(BPTD):
        return (uint32_t)BPTD.pool.used_object_capacity();
    case REV32(CAMS):
        return (uint32_t)CAMS.pool.used_object_capacity();
    */
    case REV32(CELL):  // Top CELLs
        return (uint32_t)CELL.cell_pool.used_object_capacity();
    case REV32(WCEL):  // CELLs attached to WRLDs
        return (uint32_t)WRLD.cell_pool.used_object_capacity();
    case REV32(CLSS):  // All CELL records
        return (uint32_t)CELL.cell_pool.used_object_capacity() +
               (uint32_t)WRLD.cell_pool.used_object_capacity();
    /*
    case REV32(CLAS):
        return (uint32_t)CLAS.pool.used_object_capacity();
    case REV32(CLFM):
        return (uint32_t)CLFM.pool.used_object_capacity();
    case REV32(CLMT):
        return (uint32_t)CLMT.pool.used_object_capacity();
    case REV32(COBJ):
        return (uint32_t)COBJ.pool.used_object_capacity();
    */
    case REV32(COLL):
        return (uint32_t)COLL.pool.used_object_capacity();
    /*
    case REV32(CONT):
        return (uint32_t)CONT.pool.used_object_capacity();
    case REV32(CPTH):
        return (uint32_t)CPTH.pool.used_object_capacity();
    case REV32(CSTY):
        return (uint32_t)CSTY.pool.used_object_capacity();
    case REV32(DEBR):
        return (uint32_t)DEBR.pool.used_object_capacity();
    case REV32(DLVW):
        return (uint32_t)DLVW.pool.used_object_capacity();
    case REV32(DOBJ):
        return (uint32_t)DOBJ.pool.used_object_capacity();
    case REV32(DOOR):
        return (uint32_t)DOOR.pool.used_object_capacity();
    case REV32(DUAL):
        return (uint32_t)DUAL.pool.used_object_capacity();
    case REV32(ECZN):
        return (uint32_t)ECZN.pool.used_object_capacity();
    case REV32(EFSH):
        return (uint32_t)EFSH.pool.used_object_capacity();
    case REV32(ENCH):
        return (uint32_t)ENCH.pool.used_object_capacity();
    */
    case REV32(EQUP):
        return (uint32_t)EQUP.pool.used_object_capacity();
    /*
    case REV32(EXPL):
        return (uint32_t)EXPL.pool.used_object_capacity();
    case REV32(EYES):
        return (uint32_t)EYES.pool.used_object_capacity();
    case REV32(FACT):
        return (uint32_t)FACT.pool.used_object_capacity();
    case REV32(FLOR):
        return (uint32_t)FLOR.pool.used_object_capacity();
    case REV32(FLST):
        return (uint32_t)FLST.pool.used_object_capacity();
    case REV32(FSTP):
        return (uint32_t)FSTP.pool.used_object_capacity();
    case REV32(FSTS):
        return (uint32_t)FSTS.pool.used_object_capacity();
    case REV32(FURN):
        return (uint32_t)FURN.pool.used_object_capacity();
    case REV32(GLOB):
        return (uint32_t)GLOB.pool.used_object_capacity();
    case REV32(GMST):
        return (uint32_t)GMST.pool.used_object_capacity();
    case REV32(GRAS):
        return (uint32_t)GRAS.pool.used_object_capacity();
    case REV32(HAZD):
        return (uint32_t)HAZD.pool.used_object_capacity();
    case REV32(HDPT):
        return (uint32_t)HDPT.pool.used_object_capacity();
    case REV32(IDLE):
        return (uint32_t)IDLE.pool.used_object_capacity();
    case REV32(IDLM):
        return (uint32_t)IDLM.pool.used_object_capacity();
    case REV32(IMAD):
        return (uint32_t)IMAD.pool.used_object_capacity();
    case REV32(IMGS):
        return (uint32_t)IMGS.pool.used_object_capacity();
    case REV32(INFO):
        return (uint32_t)DIAL.info_pool.used_object_capacity();
    case REV32(INGR):
        return (uint32_t)INGR.pool.used_object_capacity();
    case REV32(IPCT):
        return (uint32_t)IPCT.pool.used_object_capacity();
    case REV32(IPDS):
        return (uint32_t)IPDS.pool.used_object_capacity();
    case REV32(KEYM):
        return (uint32_t)KEYM.pool.used_object_capacity();
    */
    case REV32(KYWD):
        return (uint32_t)KYWD.pool.used_object_capacity();
    case REV32(LAND):
        return (uint32_t)WRLD.land_pool.used_object_capacity();
    /*
    case REV32(LCTR):
        return (uint32_t)LCRT.pool.used_object_capacity();
    case REV32(LCTN):
        return (uint32_t)LCTN.pool.used_object_capacity();
    case REV32(LGTM):
        return (uint32_t)LGTM.pool.used_object_capacity();
    case REV32(LIGH):
        return (uint32_t)LIGH.pool.used_object_capacity();
    case REV32(LSCR):
        return (uint32_t)LSCR.pool.used_object_capacity();
    */
    case REV32(LTEX):
        return (uint32_t)LTEX.pool.used_object_capacity();
    case REV32(LVLI):
        return (uint32_t)LVLI.pool.used_object_capacity();
    case REV32(LVLN):
        return (uint32_t)LVLN.pool.used_object_capacity();
    case REV32(LVSP):
        return (uint32_t)LVSP.pool.used_object_capacity();
    /*
    case REV32(MATO):
        return (uint32_t)MATO.pool.used_object_capacity();
    */
    case REV32(MATT):
        return (uint32_t)MATT.pool.used_object_capacity();
    /*
    case REV32(MESG):
        return (uint32_t)MESG.pool.used_object_capacity();
    case REV32(MGEF):
        return (uint32_t)MGEF.pool.used_object_capacity();
    case REV32(MISC):
        return (uint32_t)MISC.pool.used_object_capacity();
    case REV32(MOVT):
        return (uint32_t)MOVT.pool.used_object_capacity();
    case REV32(MSTT):
        return (uint32_t)MSTT.pool.used_object_capacity();
    case REV32(MUSC):
        return (uint32_t)MUSC.pool.used_object_capacity();
    case REV32(MUST):
        return (uint32_t)MUST.pool.used_object_capacity();
    case REV32(NAVI):
        return (uint32_t)NAVI.pool.used_object_capacity();
    case REV32(NAVM):
        return (uint32_t)CELL.navm_pool.used_object_capacity();
    case REV32(NPC_):
        return (uint32_t)NPC_.pool.used_object_capacity();
    */
    case REV32(OTFT):
        return (uint32_t)OTFT.pool.used_object_capacity();
    /*
    case REV32(PACK):
        return (uint32_t)PACK.pool.used_object_capacity();
    case REV32(PERK):
        return (uint32_t)PERK.pool.used_object_capacity();
    case REV32(PGRE):
        return (uint32_t)CELL.pgre_pool.used_object_capacity();
    case REV32(PHZD):
        return (uint32_t)PHZD.pool.used_object_capacity();
    case REV32(PROJ):
        return (uint32_t)PROJ.pool.used_object_capacity();
    case REV32(QUST):
        return (uint32_t)QUST.pool.used_object_capacity();
    case REV32(RACE):
        return (uint32_t)RACE.pool.used_object_capacity();
    case REV32(REFR):
        return (uint32_t)CELL.refr_pool.used_object_capacity();
    case REV32(REGN):
        return (uint32_t)REGN.pool.used_object_capacity();
    case REV32(RELA):
        return (uint32_t)RELA.pool.used_object_capacity();
    case REV32(REVB):
        return (uint32_t)REVB.pool.used_object_capacity();
    case REV32(RFCT):
        return (uint32_t)RFCT.pool.used_object_capacity();
    case REV32(SCEN):
        return (uint32_t)SCEN.pool.used_object_capacity();
    case REV32(SCRL):
        return (uint32_t)SCRL.pool.used_object_capacity();
    */
    case REV32(SHOU):
        return (uint32_t)SHOU.pool.used_object_capacity();
    /*
    case REV32(SLGM):
        return (uint32_t)SLGM.pool.used_object_capacity();
    case REV32(SMBN):
        return (uint32_t)SMBN.pool.used_object_capacity();
    case REV32(SMEN):
        return (uint32_t)SMEN.pool.used_object_capacity();
    case REV32(SMQN):
        return (uint32_t)SMQN.pool.used_object_capacity();
    case REV32(SNCT):
        return (uint32_t)SNCT.pool.used_object_capacity();
    case REV32(SNDR):
        return (uint32_t)SNDR.pool.used_object_capacity();
    case REV32(SOPM):
        return (uint32_t)SOPM.pool.used_object_capacity();
    case REV32(SOUN):
        return (uint32_t)SOUN.pool.used_object_capacity();
    case REV32(SPEL):
        return (uint32_t)SPEL.pool.used_object_capacity();
    case REV32(SPGD):
        return (uint32_t)SPGD.pool.used_object_capacity();
    case REV32(STAT):
        return (uint32_t)STAT.pool.used_object_capacity();
    case REV32(TACT):
        return (uint32_t)TACT.pool.used_object_capacity();
    case REV32(TREE):
        return (uint32_t)TREE.pool.used_object_capacity();
    */
    case REV32(TXST):
            return (uint32_t)TXST.pool.used_object_capacity();
    case REV32(VTYP):
        return (uint32_t)VTYP.pool.used_object_capacity();
    /*
    case REV32(WATR):
        return (uint32_t)WATR.pool.used_object_capacity();
    case REV32(WEAP):
        return (uint32_t)WEAP.pool.used_object_capacity();
    */
    case REV32(WOOP):
        return (uint32_t)WOOP.pool.used_object_capacity();
    case REV32(WRLD):
        return (uint32_t)WRLD.wrld_pool.used_object_capacity();
    /*
    case REV32(WTHR):
        return (uint32_t)WTHR.pool.used_object_capacity();
    */
    default:
        printer("TES5File::GetNumRecords: Warning - Unable to count records (%c%c%c%c) in mod \"%s\". Unrecognized record type.\n", ((char *)&RecordType)[0], ((char *)&RecordType)[1], ((char *)&RecordType)[2], ((char *)&RecordType)[3], ModName);
        break;
    };

    return 0;
    }

Record * TES5File::CreateRecord(const uint32_t &RecordType, char * const &RecordEditorID, Record *&SourceRecord, Record *&ParentRecord, CreationFlags &options)
    {
    if(Flags.IsNoLoad)
        {
        printer("TES5File::CreateRecord: Error - Unable to create any records in mod \"%s\". The mod is flagged not to be loaded.\n", ModName);
        return NULL;
        }

    Record *newRecord = NULL;

    switch(RecordType)
    {
    case REV32(AACT):
        return AACT.pool.construct(SourceRecord, this, true);
    case REV32(ARTO):
        return ARTO.pool.construct(SourceRecord, this, true);
    case REV32(ASPC):
        return ASPC.pool.construct(SourceRecord, this, true);
    case REV32(ASTP):
        return ASTP.pool.construct(SourceRecord, this, true);
    case REV32(CELL):
        if (ParentRecord == NULL)
        {
            newRecord = CELL.cell_pool.construct(SourceRecord, this, true);
            ((Sk::CELLRecord *)newRecord)->IsInterior(true);
            return newRecord;
        }
        else
        {
            if (ParentRecord->GetType() != REV32(WRLD))
            {
                printer("TES5File::CreateRecord: Error - Unable to create CELL record in mod \"%s\". Parent record type (%s) is invalid, only WRLD records can be CELL parents.\n", ModName, ParentRecord->GetStrType());
                return NULL;
            }

            //If the SourceRecord is a world cell, then the copy will be a world cell
            if (SourceRecord != NULL && ((Sk::WRLDRecord *)((Sk::CELLRecord *)SourceRecord)->GetParentRecord())->CELL == SourceRecord)
            {
                //If a world cell already exists, return it instead of making a new one
                if (((Sk::WRLDRecord *)ParentRecord)->CELL != NULL)
                {
                    options.ExistingReturned = true;
                    return ((Sk::WRLDRecord *)ParentRecord)->CELL;
                }

                newRecord = ((Sk::WRLDRecord *)ParentRecord)->CELL = WRLD.cell_pool.construct(SourceRecord, ParentRecord, false);
            }
            else
            {
                newRecord = WRLD.cell_pool.construct(SourceRecord, ParentRecord, false);
                ((Sk::WRLDRecord *)ParentRecord)->CELLS.push_back(newRecord);
            }

            ((Sk::CELLRecord *)newRecord)->IsInterior(false);
            return newRecord;
        }
    case REV32(WCEL):
        if (ParentRecord == NULL || ParentRecord->GetType() != REV32(WRLD))
        {
            printer("TES5File::CreateRecord: Error - Unable to create world CELL record in mod \"%s\". Parent record type (%s) is invalid, only WRLD records can be world CELL parents.\n", ModName, ParentRecord->GetStrType());
            return NULL;
        }

        //If a world cell already exists, return it instead of making a new one
        if (((Sk::WRLDRecord *)ParentRecord)->CELL != NULL)
        {
            options.ExistingReturned = true;
            return ((Sk::WRLDRecord *)ParentRecord)->CELL;
        }

        ((Sk::WRLDRecord *)ParentRecord)->CELL = WRLD.cell_pool.construct(SourceRecord, ParentRecord, false);
        ((Sk::CELLRecord *)((Sk::WRLDRecord *)ParentRecord)->CELL)->IsInterior(false);
        return ((Sk::WRLDRecord *)ParentRecord)->CELL;
    case REV32(LAND):
        if (ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
        {
            printer("TES5File::CreateRecord: Error - Unable to create LAND record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be LAND parents.\n", ModName, ParentRecord->GetStrType());
            return NULL;
        }

        //If a cell land already exists, return it instead of making a new one
        if (((Sk::CELLRecord *)ParentRecord)->LAND != NULL)
        {
            options.ExistingReturned = true;
            return ((Sk::CELLRecord *)ParentRecord)->LAND;
        }

        ((Sk::CELLRecord *)ParentRecord)->LAND = WRLD.land_pool.construct(SourceRecord, ParentRecord, false);
        return ((Sk::CELLRecord *)ParentRecord)->LAND;
    case REV32(LTEX):
        return LTEX.pool.construct(SourceRecord, this, true);
    case REV32(LVLI):
        return LVLI.pool.construct(SourceRecord, this, true);
    case REV32(LVLN):
        return LVLN.pool.construct(SourceRecord, this, true);
    case REV32(LVSP):
        return LVSP.pool.construct(SourceRecord, this, true);
    case REV32(MATT):
        return MATT.pool.construct(SourceRecord, this, true);
    case REV32(TXST):
        return TXST.pool.construct(SourceRecord, this, true);
    case REV32(WOOP):
        return WOOP.pool.construct(SourceRecord, this, true);
    case REV32(WRLD):
        return WRLD.wrld_pool.construct(SourceRecord, this, true);

    /*
    case REV32(GMST):
        if(RecordEditorID == NULL && SourceRecord == NULL)
            {
            printer("TES5File::CreateRecord: Error - Unable to create GMST record in mod \"%s\". No valid editorID is available.\n", ModName);
            return NULL;
            }
        newRecord = GMST.pool.construct(SourceRecord, this, true);

        if(RecordEditorID != NULL)
            {
            ((Sk::GMSTRecord *)newRecord)->EDID.Copy(RecordEditorID);
            ((Sk::GMSTRecord *)newRecord)->DATA.format = ((Sk::GMSTRecord *)newRecord)->EDID.value[0];
            }
    break;
    case REV32(MICN):
        return MICN.pool.construct(SourceRecord, this, true);
    case REV32(GLOB):
        return GLOB.pool.construct(SourceRecord, this, true);
    case REV32(CLAS):
        return CLAS.pool.construct(SourceRecord, this, true);
    case REV32(FACT):
        return FACT.pool.construct(SourceRecord, this, true);
    case REV32(HDPT):
        return HDPT.pool.construct(SourceRecord, this, true);
    case REV32(HAIR):
        return HAIR.pool.construct(SourceRecord, this, true);
    case REV32(EYES):
        return EYES.pool.construct(SourceRecord, this, true);
    case REV32(RACE):
        return RACE.pool.construct(SourceRecord, this, true);
    case REV32(SOUN):
        return SOUN.pool.construct(SourceRecord, this, true);
    case REV32(MGEF):
        return MGEF.pool.construct(SourceRecord, this, true);
    case REV32(SCPT):
        return SCPT.pool.construct(SourceRecord, this, true);
    case REV32(ENCH):
        return ENCH.pool.construct(SourceRecord, this, true);
    case REV32(SPEL):
        return SPEL.pool.construct(SourceRecord, this, true);
    */
    case REV32(ACTI):
        return ACTI.pool.construct(SourceRecord, this, true);
    /*
    case REV32(TACT):
        return TACT.pool.construct(SourceRecord, this, true);
    case REV32(TERM):
        return TERM.pool.construct(SourceRecord, this, true);
    case REV32(ARMO):
        return ARMO.pool.construct(SourceRecord, this, true);
    case REV32(BOOK):
        return BOOK.pool.construct(SourceRecord, this, true);
    case REV32(CONT):
        return CONT.pool.construct(SourceRecord, this, true);
    case REV32(DOOR):
        return DOOR.pool.construct(SourceRecord, this, true);
    case REV32(INGR):
        return INGR.pool.construct(SourceRecord, this, true);
    case REV32(LIGH):
        return LIGH.pool.construct(SourceRecord, this, true);
    case REV32(MISC):
        return MISC.pool.construct(SourceRecord, this, true);
    case REV32(STAT):
        return STAT.pool.construct(SourceRecord, this, true);
    case REV32(SCOL):
        return SCOL.pool.construct(SourceRecord, this, true);
    case REV32(MSTT):
        return MSTT.pool.construct(SourceRecord, this, true);
    case REV32(PWAT):
        return PWAT.pool.construct(SourceRecord, this, true);
    case REV32(GRAS):
        return GRAS.pool.construct(SourceRecord, this, true);
    case REV32(TREE):
        return TREE.pool.construct(SourceRecord, this, true);
    case REV32(FURN):
        return FURN.pool.construct(SourceRecord, this, true);
    case REV32(WEAP):
        return WEAP.pool.construct(SourceRecord, this, true);
    case REV32(AMMO):
        return AMMO.pool.construct(SourceRecord, this, true);
    case REV32(NPC_):
        return NPC_.pool.construct(SourceRecord, this, true);
    case REV32(CREA):
        return CREA.pool.construct(SourceRecord, this, true);
    case REV32(LVLC):
        return LVLC.pool.construct(SourceRecord, this, true);
    case REV32(KEYM):
        return KEYM.pool.construct(SourceRecord, this, true);
    */
    case REV32(ALCH):
        return ALCH.pool.construct(SourceRecord, this, true);
    /*
    case REV32(IDLM):
        return IDLM.pool.construct(SourceRecord, this, true);
    case REV32(NOTE):
        return NOTE.pool.construct(SourceRecord, this, true);
    case REV32(COBJ):
        return COBJ.pool.construct(SourceRecord, this, true);
    case REV32(PROJ):
        return PROJ.pool.construct(SourceRecord, this, true);
    case REV32(WTHR):
        return WTHR.pool.construct(SourceRecord, this, true);
    case REV32(CLMT):
        return CLMT.pool.construct(SourceRecord, this, true);
    case REV32(REGN):
        return REGN.pool.construct(SourceRecord, this, true);
    case REV32(NAVI):
        return NAVI.pool.construct(SourceRecord, this, true);
    case REV32(DIAL):
        return DIAL.dial_pool.construct(SourceRecord, this, true);
    case REV32(INFO):
        if(ParentRecord == NULL || ParentRecord->GetType() != REV32(DIAL))
            {
            printer("TES5File::CreateRecord: Error - Unable to create INFO record in mod \"%s\". Parent record type (%s) is invalid, only DIAL records can be INFO parents.\n", ModName, ParentRecord->GetStrType());
            return NULL;
            }

        ((Sk::DIALRecord *)ParentRecord)->INFO.push_back(DIAL.info_pool.construct(SourceRecord, ParentRecord, false));
        return ((Sk::DIALRecord *)ParentRecord)->INFO.back();
    case REV32(ACHR):
        if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
            {
            printer("TES5File::CreateRecord: Error - Unable to create ACHR record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be ACHR parents.\n", ModName, ParentRecord->GetStrType());
            return NULL;
            }

        ((Sk::CELLRecord *)ParentRecord)->ACHR.push_back(CELL.achr_pool.construct(SourceRecord, ParentRecord, false));
        return ((Sk::CELLRecord *)ParentRecord)->ACHR.back();
    case REV32(ACRE):
        if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
            {
            printer("TES5File::CreateRecord: Error - Unable to create ACRE record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be ACRE parents.\n", ModName, ParentRecord->GetStrType());
            return NULL;
            }

        ((Sk::CELLRecord *)ParentRecord)->ACRE.push_back(CELL.acre_pool.construct(SourceRecord, ParentRecord, false));
        return ((Sk::CELLRecord *)ParentRecord)->ACRE.back();
    case REV32(REFR):
        if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
            {
            printer("TES5File::CreateRecord: Error - Unable to create REFR record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be REFR parents.\n", ModName, ParentRecord->GetStrType());
            return NULL;
            }

        ((Sk::CELLRecord *)ParentRecord)->REFR.push_back(CELL.refr_pool.construct(SourceRecord, ParentRecord, false));
        return ((Sk::CELLRecord *)ParentRecord)->REFR.back();
    case REV32(PGRE):
        if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
            {
            printer("TES5File::CreateRecord: Error - Unable to create PGRE record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be REFR parents.\n", ModName, ParentRecord->GetStrType());
            return NULL;
            }

        ((Sk::CELLRecord *)ParentRecord)->PGRE.push_back(CELL.pgre_pool.construct(SourceRecord, ParentRecord, false));
        return ((Sk::CELLRecord *)ParentRecord)->PGRE.back();
    case REV32(PMIS):
        if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
            {
            printer("TES5File::CreateRecord: Error - Unable to create PMIS record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be REFR parents.\n", ModName, ParentRecord->GetStrType());
            return NULL;
            }

        ((Sk::CELLRecord *)ParentRecord)->PMIS.push_back(CELL.pmis_pool.construct(SourceRecord, ParentRecord, false));
        return ((Sk::CELLRecord *)ParentRecord)->PMIS.back();
    case REV32(PBEA):
        if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
            {
            printer("TES5File::CreateRecord: Error - Unable to create PBEA record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be REFR parents.\n", ModName, ParentRecord->GetStrType());
            return NULL;
            }

        ((Sk::CELLRecord *)ParentRecord)->PBEA.push_back(CELL.pbea_pool.construct(SourceRecord, ParentRecord, false));
        return ((Sk::CELLRecord *)ParentRecord)->PBEA.back();
    case REV32(PFLA):
        if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
            {
            printer("TES5File::CreateRecord: Error - Unable to create PFLA record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be REFR parents.\n", ModName, ParentRecord->GetStrType());
            return NULL;
            }

        ((Sk::CELLRecord *)ParentRecord)->PFLA.push_back(CELL.pfla_pool.construct(SourceRecord, ParentRecord, false));
        return ((Sk::CELLRecord *)ParentRecord)->PFLA.back();
    case REV32(PCBE):
        if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
            {
            printer("TES5File::CreateRecord: Error - Unable to create PCBE record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be REFR parents.\n", ModName, ParentRecord->GetStrType());
            return NULL;
            }

        ((Sk::CELLRecord *)ParentRecord)->PCBE.push_back(CELL.pcbe_pool.construct(SourceRecord, ParentRecord, false));
        return ((Sk::CELLRecord *)ParentRecord)->PCBE.back();
    case REV32(NAVM):
        if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
            {
            printer("TES5File::CreateRecord: Error - Unable to create NAVM record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be REFR parents.\n", ModName, ParentRecord->GetStrType());
            return NULL;
            }

        ((Sk::CELLRecord *)ParentRecord)->NAVM.push_back(CELL.navm_pool.construct(SourceRecord, ParentRecord, false));
        return ((Sk::CELLRecord *)ParentRecord)->NAVM.back();
    case REV32(QUST):
        return QUST.pool.construct(SourceRecord, this, true);
    case REV32(IDLE):
        return IDLE.pool.construct(SourceRecord, this, true);
    case REV32(PACK):
        return PACK.pool.construct(SourceRecord, this, true);
    case REV32(CSTY):
        return CSTY.pool.construct(SourceRecord, this, true);
    case REV32(LSCR):
        return LSCR.pool.construct(SourceRecord, this, true);
    */
    case REV32(ANIO):
        return ANIO.pool.construct(SourceRecord, this, true);
    /*
    case REV32(WATR):
        return WATR.pool.construct(SourceRecord, this, true);
    case REV32(EFSH):
        return EFSH.pool.construct(SourceRecord, this, true);
    case REV32(EXPL):
        return EXPL.pool.construct(SourceRecord, this, true);
    case REV32(DEBR):
        return DEBR.pool.construct(SourceRecord, this, true);
    case REV32(IMGS):
        //return IMGS.pool.construct(SourceRecord, this, true);
    case REV32(IMAD):
        //return IMAD.pool.construct(SourceRecord, this, true);
    case REV32(FLST):
        //return FLST.pool.construct(SourceRecord, this, true);
    case REV32(PERK):
        //return PERK.pool.construct(SourceRecord, this, true);
    case REV32(BPTD):
        //return BPTD.pool.construct(SourceRecord, this, true);
    */
    case REV32(ADDN):
        return ADDN.pool.construct(SourceRecord, this, true);
    /*
    case REV32(AVIF):
        //return AVIF.pool.construct(SourceRecord, this, true);
    case REV32(RADS):
        //return RADS.pool.construct(SourceRecord, this, true);
    case REV32(CAMS):
        //return CAMS.pool.construct(SourceRecord, this, true);
    case REV32(CPTH):
        //return CPTH.pool.construct(SourceRecord, this, true);
    */
    case REV32(VTYP):
        return VTYP.pool.construct(SourceRecord, this, true);
    /*
    case REV32(IPCT):
        //return IPCT.pool.construct(SourceRecord, this, true);
    case REV32(IPDS):
        //return IPDS.pool.construct(SourceRecord, this, true);
    case REV32(ARMA):
        //return ARMA.pool.construct(SourceRecord, this, true);
    case REV32(ECZN):
        //return ECZN.pool.construct(SourceRecord, this, true);
    case REV32(MESG):
        //return MESG.pool.construct(SourceRecord, this, true);
    case REV32(RGDL):
        //return RGDL.pool.construct(SourceRecord, this, true);
    case REV32(DOBJ):
        //return DOBJ.pool.construct(SourceRecord, this, true);
    case REV32(LGTM):
        //return LGTM.pool.construct(SourceRecord, this, true);
    case REV32(MUSC):
        //return MUSC.pool.construct(SourceRecord, this, true);
    case REV32(IMOD):
        //return IMOD.pool.construct(SourceRecord, this, true);
    case REV32(REPU):
        //return REPU.pool.construct(SourceRecord, this, true);
    case REV32(RCPE):
        //return RCPE.pool.construct(SourceRecord, this, true);
    case REV32(RCCT):
        //return RCCT.pool.construct(SourceRecord, this, true);
    case REV32(CHIP):
        //return CHIP.pool.construct(SourceRecord, this, true);
    case REV32(CSNO):
        //return CSNO.pool.construct(SourceRecord, this, true);
    case REV32(LSCT):
        //return LSCT.pool.construct(SourceRecord, this, true);
    case REV32(MSET):
        //return MSET.pool.construct(SourceRecord, this, true);
    case REV32(ALOC):
        //return ALOC.pool.construct(SourceRecord, this, true);
    case REV32(CHAL):
        //return CHAL.pool.construct(SourceRecord, this, true);
    case REV32(AMEF):
        //return AMEF.pool.construct(SourceRecord, this, true);
    case REV32(CCRD):
        //return CCRD.pool.construct(SourceRecord, this, true);
    case REV32(CMNY):
        //return CMNY.pool.construct(SourceRecord, this, true);
    case REV32(CDCK):
        //return CDCK.pool.construct(SourceRecord, this, true);
    case REV32(DEHY):
        //return DEHY.pool.construct(SourceRecord, this, true);
    case REV32(HUNG):
        //return HUNG.pool.construct(SourceRecord, this, true);
    case REV32(SLPD):
        //return SLPD.pool.construct(SourceRecord, this, true);
    */
    default:
        printer("TES5File::CreateRecord: Error - Unable to create (%c%c%c%c) record in mod \"%s\". Unknown record type.\n", ((char *)&RecordType)[0], ((char *)&RecordType)[1], ((char *)&RecordType)[2], ((char *)&RecordType)[3], ModName);
        break;
    }

    return newRecord;
    }

int32_t TES5File::DeleteRecord(Record *&curRecord, RecordOp &deindexer)
    {
    switch(curRecord->GetType())
    {
    case REV32(AACT):
        deindexer.Accept(curRecord);
        AACT.pool.destroy(curRecord);
        return 1;
    /*
    case REV32(ACHR):
    {
        Sk::CELLRecord *cell_record = (Sk::CELLRecord *)curRecord->GetParentRecord();
        bool child_found = false;
        for (uint32_t ListIndex = 0; ListIndex < cell_record->ACHR.size(); ++ListIndex)
        {
            if (cell_record->ACHR[ListIndex] == curRecord)
            {
                cell_record->ACHR.erase(cell_record->ACHR.begin() + ListIndex);
                child_found = true;
                break;
            }
        }
        if (!child_found)
        {
            printer("TES5File::DeleteRecord: Error - Unable to delete record type (%s) with parent type (%s) in mod \"%s\". The parent record (%08X) does not contain the record to be deleted (%08X).\n", curRecord->GetStrType(), curRecord->GetParentRecord()->GetStrType(), ModName, curRecord->GetParentRecord()->formID, curRecord->formID);
            return 0;
        }

        deindexer.Accept(curRecord);
        CELL.achr_pool.destroy(curRecord);
    }
        return 1;
    */
    case REV32(ACTI):
        deindexer.Accept(curRecord);
        ACTI.pool.destroy(curRecord);
        return 1;
    case REV32(ADDN):
        deindexer.Accept(curRecord);
        ADDN.pool.destroy(curRecord);
        return 1;
    case REV32(ALCH):
        deindexer.Accept(curRecord);
        ALCH.pool.destroy(curRecord);
        return 1;
    /*
    case REV32(AMMO):
        deindexer.Accept(curRecord);
        AMMO.pool.destroy(curRecord);
        return 1;
    */
    case REV32(ANIO):
        deindexer.Accept(curRecord);
        ANIO.pool.destroy(curRecord);
        return 1;
    case REV32(APPA):
        deindexer.Accept(curRecord);
        APPA.pool.destroy(curRecord);
        return 1;
    /*
    case REV32(ARMA):
        deindexer.Accept(curRecord);
        ARMA.pool.destroy(curRecord);
        return 1;
    */
    /*
    case REV32(ARMO):
        deindexer.Accept(curRecord);
        ARMO.pool.destroy(curRecord);
        return 1;
    */
    case REV32(ARTO):
        deindexer.Accept(curRecord);
        ARTO.pool.destroy(curRecord);
        return 1;
    case REV32(ASPC):
        deindexer.Accept(curRecord);
        ASPC.pool.destroy(curRecord);
        return 1;
    case REV32(ASTP):
        deindexer.Accept(curRecord);
        ASTP.pool.destroy(curRecord);
        return 1;
    /*
    case REV32(AVIF):
        deindexer.Accept(curRecord);
        AVIF.pool.destroy(curRecord);
        return 1;
    case REV32(BOOK):
        deindexer.Accept(curRecord);
        BOOK.pool.destroy(curRecord);
        return 1;
    case REV32(BPTD):
        deindexer.Accept(curRecord);
        BPTD.pool.destroy(curRecord);
        return 1;
    case REV32(CAMS):
        deindexer.Accept(curRecord);
        CAMS.pool.destroy(curRecord);
        return 1;
    */
    case REV32(CELL):
    {
        Sk::WRLDRecord *wrld_record = (Sk::WRLDRecord *)curRecord->GetParentRecord();
        bool cell_found = false;
        if (wrld_record != NULL)
        {
            if (wrld_record->CELL == curRecord)
            {
                wrld_record->CELL = NULL;
                cell_found = true;
            }
            else
            {
                for (uint32_t ListIndex = 0; ListIndex < wrld_record->CELLS.size(); ++ListIndex)
                {
                    if (wrld_record->CELLS[ListIndex] == curRecord)
                    {
                        wrld_record->CELLS.erase(wrld_record->CELLS.begin() + ListIndex);
                        cell_found = true;
                        break;
                    }
                }
            }
            if (!cell_found)
            {
                printer("TES5File::DeleteRecord: Error - Unable to delete record type (%s) with parent type (%s) in mod \"%s\". The parent record (%08X) does not contain the record to be deleted (%08X).\n", curRecord->GetStrType(), curRecord->GetParentRecord()->GetStrType(), ModName, curRecord->GetParentRecord()->formID, curRecord->formID);
                return 0;
            }
        }
        Sk::CELLRecord *cell_record = (Sk::CELLRecord *)curRecord;

        /*
        for(uint32_t ListIndex = 0; ListIndex < cell_record->ACHR.size(); ++ListIndex)
        {
            deindexer.Accept(cell_record->ACHR[ListIndex]);
            CELL.achr_pool.destroy(cell_record->ACHR[ListIndex]);
        }

        for(uint32_t ListIndex = 0; ListIndex < cell_record->ACRE.size(); ++ListIndex)
        {
            deindexer.Accept(cell_record->ACRE[ListIndex]);
            CELL.acre_pool.destroy(cell_record->ACRE[ListIndex]);
        }

        for(uint32_t ListIndex = 0; ListIndex < cell_record->REFR.size(); ++ListIndex)
        {
            deindexer.Accept(cell_record->REFR[ListIndex]);
            CELL.refr_pool.destroy(cell_record->REFR[ListIndex]);
        }

        for(uint32_t ListIndex = 0; ListIndex < cell_record->PGRE.size(); ++ListIndex)
        {
            deindexer.Accept(cell_record->PGRE[ListIndex]);
            CELL.pgre_pool.destroy(cell_record->PGRE[ListIndex]);
        }

        for(uint32_t ListIndex = 0; ListIndex < cell_record->PMIS.size(); ++ListIndex)
        {
            deindexer.Accept(cell_record->PMIS[ListIndex]);
            CELL.pmis_pool.destroy(cell_record->PMIS[ListIndex]);
        }

        for(uint32_t ListIndex = 0; ListIndex < cell_record->PBEA.size(); ++ListIndex)
        {
            deindexer.Accept(cell_record->PBEA[ListIndex]);
            CELL.pbea_pool.destroy(cell_record->PBEA[ListIndex]);
        }

        for(uint32_t ListIndex = 0; ListIndex < cell_record->PFLA.size(); ++ListIndex)
        {
            deindexer.Accept(cell_record->PFLA[ListIndex]);
            CELL.pfla_pool.destroy(cell_record->PFLA[ListIndex]);
        }

        for(uint32_t ListIndex = 0; ListIndex < cell_record->PCBE.size(); ++ListIndex)
        {
            deindexer.Accept(cell_record->PCBE[ListIndex]);
            CELL.pcbe_pool.destroy(cell_record->PCBE[ListIndex]);
        }

        for(uint32_t ListIndex = 0; ListIndex < cell_record->NAVM.size(); ++ListIndex)
        {
            deindexer.Accept(cell_record->NAVM[ListIndex]);
            CELL.navm_pool.destroy(cell_record->NAVM[ListIndex]);
        }
        */

        deindexer.Accept(cell_record->LAND);
        WRLD.land_pool.destroy(cell_record->LAND);

        deindexer.Accept(curRecord);
        if (cell_found)
            WRLD.cell_pool.destroy(curRecord);
        else
            CELL.cell_pool.destroy(curRecord);

    }
        return 1;
    /*
    case REV32(CLAS):
        deindexer.Accept(curRecord);
        CLAS.pool.destroy(curRecord);
        return 1;
    case REV32(CLFM):
        deindexer.Accept(curRecord);
        CLFM.pool.destroy(curRecord);
        return 1;
    case REV32(CLMT):
        deindexer.Accept(curRecord);
        CLMT.pool.destroy(curRecord);
        return 1;
    case REV32(COBJ):
        deindexer.Accept(curRecord);
        COBJ.pool.destroy(curRecord);
        return 1;
    */
    case REV32(COLL):
        deindexer.Accept(curRecord);
        COLL.pool.destroy(curRecord);
        return 1;
    /*
    case REV32(CONT):
        deindexer.Accept(curRecord);
        CONT.pool.destroy(curRecord);
        return 1;
    case REV32(CPTH):
        deindexer.Accept(curRecord);
        CPTH.pool.destroy(curRecord);
        return 1;
    case REV32(CSTY):
        deindexer.Accept(curRecord);
        CSTY.pool.destroy(curRecord);
        return 1;
    case REV32(DEBR):
        deindexer.Accept(curRecord);
        DEBR.pool.destroy(curRecord);
        return 1;
    case REV32(DIAL):
    {
        Sk::DIALRecord *dial_record = (Sk::DIALRecord *)curRecord;
        for(uint32_t ListIndex = 0; ListIndex < dial_record->INFO.size(); ++ListIndex)
        {
            deindexer.Accept(dial_record->INFO[ListIndex]);
            DIAL.info_pool.destroy(dial_record->INFO[ListIndex]);
        }

        deindexer.Accept(curRecord);
        DIAL.dial_pool.destroy(curRecord);
    }
        return 1;
    case REV32(DLBR):
        deindexer.Accept(curRecord);
        DLBR.pool.destroy(curRecord);
        return 1;
    case REV32(DLVW):
        deindexer.Accept(curRecord);
        DLVW.pool.destroy(curRecord);
        return 1;
    case REV32(DOBJ):
        deindexer.Accept(curRecord);
        DOBJ.pool.destroy(curRecord);
        return 1;
    case REV32(DOOR):
        deindexer.Accept(curRecord);
        DOOR.pool.destroy(curRecord);
        return 1;
    case REV32(DUAL):
        deindexer.Accept(curRecord);
        DUAL.pool.destroy(curRecord);
        return 1;
    case REV32(ECZN):
        deindexer.Accept(curRecord);
        ECZN.pool.destroy(curRecord);
        return 1;
    case REV32(EFSH):
        deindexer.Accept(curRecord);
        EFSH.pool.destroy(curRecord);
        return 1;
    case REV32(ENCH):
        deindexer.Accept(curRecord);
        ENCH.pool.destroy(curRecord);
        return 1;
    */
    case REV32(EQUP):
        deindexer.Accept(curRecord);
        EQUP.pool.destroy(curRecord);
        return 1;
    /*
    case REV32(EXPL):
        deindexer.Accept(curRecord);
        EXPL.pool.destroy(curRecord);
        return 1;
    case REV32(EYES):
        deindexer.Accept(curRecord);
        EYES.pool.destroy(curRecord);
        return 1;
    case REV32(FACT):
        deindexer.Accept(curRecord);
        FACT.pool.destroy(curRecord);
        return 1;
    case REV32(FLOR):
        deindexer.Accept(curRecord);
        FLOR.pool.destroy(curRecord);
        return 1;
    case REV32(FLST):
        deindexer.Accept(curRecord);
        FLST.pool.destroy(curRecord);
        return 1;
    case REV32(FSTP):
        deindexer.Accept(curRecord);
        FSTP.pool.destroy(curRecord);
        return 1;
    case REV32(FSTS):
        deindexer.Accept(curRecord);
        FSTS.pool.destroy(curRecord);
        return 1;
    case REV32(FURN):
        deindexer.Accept(curRecord);
        FURN.pool.destroy(curRecord);
        return 1;
    case REV32(GLOB):
        deindexer.Accept(curRecord);
        GLOB.pool.destroy(curRecord);
        return 1;
    case REV32(GMST):
        deindexer.Accept(curRecord);
        GMST.pool.destroy(curRecord);
        return 1;
    case REV32(GRAS):
        deindexer.Accept(curRecord);
        GRAS.pool.destroy(curRecord);
        return 1;
    case REV32(HAZD):
        deindexer.Accept(curRecord);
        HAZD.pool.destroy(curRecord);
        return 1;
    case REV32(IDLE):
        deindexer.Accept(curRecord);
        IDLE.pool.destroy(curRecord);
        return 1;
    case REV32(IDLM):
        deindexer.Accept(curRecord);
        IDLM.pool.destroy(curRecord);
        return 1;
    case REV32(IMAD):
        deindexer.Accept(curRecord);
        IMAD.pool.destroy(curRecord);
        return 1;
    case REV32(IMGS):
        deindexer.Accept(curRecord);
        IMGS.pool.destroy(curRecord);
        return 1;
    case REV32(INFO):
    {
        Sk::DIALRecord *dial_record = (Sk::DIALRecord *)curRecord->GetParentRecord();
        bool info_found = false;
        for(uint32_t ListIndex = 0; ListIndex < dial_record->INFO.size(); ++ListIndex)
        {
            if(dial_record->INFO[ListIndex] == curRecord)
            {
                dial_record->INFO.erase(dial_record->INFO.begin() + ListIndex);
                info_found = true;
                break;
            }
        }
        if(!info_found)
        {
            printer("TES5File::DeleteRecord: Error - Unable to delete record type (%s) with parent type (%s) in mod \"%s\". The parent record (%08X) does not contain the record to be deleted (%08X).\n", curRecord->GetStrType(), curRecord->GetParentRecord()->GetStrType(), ModName, curRecord->GetParentRecord()->formID, curRecord->formID);
            return 0;
        }

        deindexer.Accept(curRecord);
        DIAL.info_pool.destroy(curRecord);
    }
        return 1;
    case REV32(INGR):
        deindexer.Accept(curRecord);
        INGR.pool.destroy(curRecord);
        return 1;
    case REV32(IPCT):
        deindexer.Accept(curRecord);
        IPCT.pool.destroy(curRecord);
        return 1;
    case REV32(IPDS):
        deindexer.Accept(curRecord);
        IPDS.pool.destroy(curRecord);
        return 1;
    case REV32(KEYM):
        deindexer.Accept(curRecord);
        KEYM.pool.destroy(curRecord);
        return 1;
    */
    case REV32(KYWD):
        deindexer.Accept(curRecord);
        KYWD.pool.destroy(curRecord);
        return 1;
    case REV32(LAND):
    {
        Sk::CELLRecord *cell_record = (Sk::CELLRecord *)curRecord->GetParentRecord();

        if (cell_record->LAND != curRecord)
        {
            printer("TES5File::DeleteRecord: Error - Unable to delete record type (%s) with parent type (%s) in mod \"%s\". The parent record (%08X) does not contain the record to be deleted (%08X).\n", curRecord->GetStrType(), curRecord->GetParentRecord()->GetStrType(), ModName, curRecord->GetParentRecord()->formID, curRecord->formID);
            return 0;
        }

        cell_record->LAND = NULL;
        deindexer.Accept(curRecord);
        WRLD.land_pool.destroy(curRecord);
    }
        return 1;
    /*
    case REV32(LCRT):
        deindexer.Accept(curRecord);
        LCRT.pool.destroy(curRecord);
        return 1;
    case REV32(LCTN):
        deindexer.Accept(curRecord);
        LCTN.pool.destroy(curRecord);
        return 1;
    case REV32(LGTM):
        deindexer.Accept(curRecord);
        LGTM.pool.destroy(curRecord);
        return 1;
    case REV32(LIGH):
        deindexer.Accept(curRecord);
        LIGH.pool.destroy(curRecord);
        return 1;
    case REV32(LSCR):
        deindexer.Accept(curRecord);
        LSCR.pool.destroy(curRecord);
        return 1;
    */
    case REV32(LTEX):
        deindexer.Accept(curRecord);
        LTEX.pool.destroy(curRecord);
        return 1;
    case REV32(LVLI):
        deindexer.Accept(curRecord);
        LVLI.pool.destroy(curRecord);
        return 1;
    case REV32(LVLN):
        deindexer.Accept(curRecord);
        LVLN.pool.destroy(curRecord);
        return 1;
    case REV32(LVSP):
        deindexer.Accept(curRecord);
        LVSP.pool.destroy(curRecord);
        return 1;
    /*
    case REV32(MATO):
        deindexer.Accept(curRecord);
        LIGH.pool.destroy(curRecord);
        return 1;

    */
    case REV32(MATT):
        deindexer.Accept(curRecord);
        MATT.pool.destroy(curRecord);
        return 1;
    /*
    case REV32(MESG):
        deindexer.Accept(curRecord);
        MESG.pool.destroy(curRecord);
        return 1;
    case REV32(MGEF):
        deindexer.Accept(curRecord);
        MGEF.pool.destroy(curRecord);
        return 1;
    case REV32(MISC):
        deindexer.Accept(curRecord);
        MISC.pool.destroy(curRecord);
        return 1;
    case REV32(MOVT):
        deindexer.Accept(curRecord);
        MOVT.pool.destroy(curRecord);
        return 1;
    case REV32(MSTT):
        deindexer.Accept(curRecord);
        MSTT.pool.destroy(curRecord);
        return 1;
    case REV32(MUSC):
        deindexer.Accept(curRecord);
        MUSC.pool.destroy(curRecord);
        return 1;
    case REV32(MUST):
        deindexer.Accept(curRecord);
        MUST.pool.destroy(curRecord);
        return 1;
    case REV32(NAVI):
        deindexer.Accept(curRecord);
        NAVI.pool.destroy(curRecord);
        return 1;
    case REV32(NAVM):
    {
        Sk::CELLRecord *cell_record = (Sk::CELLRecord *)curRecord->GetParentRecord();
        bool child_found = false;
        for(uint32_t ListIndex = 0; ListIndex < cell_record->NAVM.size(); ++ListIndex)
        {
            if(cell_record->NAVM[ListIndex] == curRecord)
            {
                cell_record->NAVM.erase(cell_record->NAVM.begin() + ListIndex);
                child_found = true;
                break;
            }
        }
        if(!child_found)
        {
            printer("TES5File::DeleteRecord: Error - Unable to delete record type (%s) with parent type (%s) in mod \"%s\". The parent record (%08X) does not contain the record to be deleted (%08X).\n", curRecord->GetStrType(), curRecord->GetParentRecord()->GetStrType(), ModName, curRecord->GetParentRecord()->formID, curRecord->formID);
            return 0;
        }

        deindexer.Accept(curRecord);
        CELL.navm_pool.destroy(curRecord);
    }
        return 1;
    case REV32(NPC_):
        deindexer.Accept(curRecord);
        NPC_.pool.destroy(curRecord);
        return 1;
    */
    case REV32(OTFT):
        deindexer.Accept(curRecord);
        OTFT.pool.destroy(curRecord);
        return 1;
    /*
    case REV32(PACK):
        deindexer.Accept(curRecord);
        PACK.pool.destroy(curRecord);
        return 1;
    case REV32(PERK):
        deindexer.Accept(curRecord);
        PERK.pool.destroy(curRecord);
        return 1;
    case REV32(PGRE):
    {
        Sk::CELLRecord *cell_record = (Sk::CELLRecord *)curRecord->GetParentRecord();
        bool child_found = false;
        for(uint32_t ListIndex = 0; ListIndex < cell_record->PGRE.size(); ++ListIndex)
        {
            if(cell_record->PGRE[ListIndex] == curRecord)
            {
                cell_record->PGRE.erase(cell_record->PGRE.begin() + ListIndex);
                child_found = true;
                break;
            }
        }
        if(!child_found)
        {
            printer("TES5File::DeleteRecord: Error - Unable to delete record type (%s) with parent type (%s) in mod \"%s\". The parent record (%08X) does not contain the record to be deleted (%08X).\n", curRecord->GetStrType(), curRecord->GetParentRecord()->GetStrType(), ModName, curRecord->GetParentRecord()->formID, curRecord->formID);
            return 0;
        }

        deindexer.Accept(curRecord);
        CELL.pgre_pool.destroy(curRecord);
    }
        return 1;
    case REV32(PHZD):
        deindexer.Accept(curRecord);
        PHZD.pool.destroy(curRecord);
        return 1;
    case REV32(PROJ):
        deindexer.Accept(curRecord);
        PROJ.pool.destroy(curRecord);
        return 1;
    case REV32(QUST):
        deindexer.Accept(curRecord);
        QUST.pool.destroy(curRecord);
        return 1;
    case REV32(RACE):
        deindexer.Accept(curRecord);
        RACE.pool.destroy(curRecord);
        return 1;
    case REV32(REFR):
    {
        Sk::CELLRecord *cell_record = (Sk::CELLRecord *)curRecord->GetParentRecord();
        bool child_found = false;
        for(uint32_t ListIndex = 0; ListIndex < cell_record->REFR.size(); ++ListIndex)
        {
            if(cell_record->REFR[ListIndex] == curRecord)
            {
                cell_record->REFR.erase(cell_record->REFR.begin() + ListIndex);
                child_found = true;
                break;
            }
        }
        if(!child_found)
        {
            printer("TES5File::DeleteRecord: Error - Unable to delete record type (%s) with parent type (%s) in mod \"%s\". The parent record (%08X) does not contain the record to be deleted (%08X).\n", curRecord->GetStrType(), curRecord->GetParentRecord()->GetStrType(), ModName, curRecord->GetParentRecord()->formID, curRecord->formID);
            return 0;
        }

        deindexer.Accept(curRecord);
        CELL.refr_pool.destroy(curRecord);
    }
        return 1;
    case REV32(REGN):
        deindexer.Accept(curRecord);
        REGN.pool.destroy(curRecord);
        return 1;
    case REV32(RELA):
        deindexer.Accept(curRecord);
        RELA.pool.destroy(curRecord);
        return 1;
    case REV32(REVB):
        deindexer.Accept(curRecord);
        REVB.pool.destroy(curRecord);
        return 1;
    case REV32(RFCT):
        deindexer.Accept(curRecord);
        RFCT.pool.destroy(curRecord);
        return 1;
    case REV32(SCEN):
        deindexer.Accept(curRecord);
        SCEN.pool.destroy(curRecord);
        return 1;
    case REV32(SCRL):
        deindexer.Accept(curRecord);
        SCRL.pool.destroy(curRecord);
        return 1;
    */
    case REV32(SHOU):
        deindexer.Accept(curRecord);
        SHOU.pool.destroy(curRecord);
        return 1;
    /*
    case REV32(SLGM):
        deindexer.Accept(curRecord);
        SLGM.pool.destroy(curRecord);
        return 1;
    case REV32(SMBN):
        deindexer.Accept(curRecord);
        SMBN.pool.destroy(curRecord);
        return 1;
    case REV32(SMEN):
        deindexer.Accept(curRecord);
        SMEN.pool.destroy(curRecord);
        return 1;
    case REV32(SMQN):
        deindexer.Accept(curRecord);
        SMQN.pool.destroy(curRecord);
        return 1;
    case REV32(SNCT):
        deindexer.Accept(curRecord);
        SNCT.pool.destroy(curRecord);
        return 1;
    case REV32(SNDR):
        deindexer.Accept(curRecord);
        SNDR.pool.destroy(curRecord);
        return 1;
    case REV32(SOPM):
        deindexer.Accept(curRecord);
        SOPM.pool.destroy(curRecord);
        return 1;
    case REV32(SOUN):
        deindexer.Accept(curRecord);
        SOUN.pool.destroy(curRecord);
        return 1;
    case REV32(SPEL):
        deindexer.Accept(curRecord);
        SPEL.pool.destroy(curRecord);
        return 1;
    case REV32(SPGD):
        deindexer.Accept(curRecord);
        SPGD.pool.destroy(curRecord);
        return 1;
    case REV32(STAT):
        deindexer.Accept(curRecord);
        STAT.pool.destroy(curRecord);
        return 1;
    case REV32(TACT):
        deindexer.Accept(curRecord);
        TACT.pool.destroy(curRecord);
        return 1;
    case REV32(TREE):
        deindexer.Accept(curRecord);
        TRRE.pool.destroy(curRecord);
        return 1;
    */
    case REV32(TXST):
            deindexer.Accept(curRecord);
            TXST.pool.destroy(curRecord);
            return 1;
    case REV32(VTYP):
        deindexer.Accept(curRecord);
        VTYP.pool.destroy(curRecord);
        return 1;
    /*
    case REV32(WATR):
        deindexer.Accept(curRecord);
        WATR.pool.destroy(curRecord);
        return 1;
    case REV32(WEAP):
        deindexer.Accept(curRecord);
        WEAP.pool.destroy(curRecord);
        return 1;
    */
    case REV32(WOOP):
        deindexer.Accept(curRecord);
        WOOP.pool.destroy(curRecord);
        return 1;
    case REV32(WRLD):
    {
        Sk::WRLDRecord *wrld_record = (Sk::WRLDRecord *)curRecord;

        Sk::CELLRecord *cell_record = (Sk::CELLRecord *)wrld_record->CELL;
        if(cell_record != NULL) //Add it to list of cells to be deleted
            wrld_record->CELLS.push_back(cell_record);

        for(uint32_t ListIndex = 0; ListIndex < wrld_record->CELLS.size(); ++ListIndex)
        {
            cell_record = (Sk::CELLRecord *)wrld_record->CELLS[ListIndex];

            /*
            // TODO: Code duplication, good spot for a new function
            for(uint32_t ListX2Index = 0; ListX2Index < cell_record->ACHR.size(); ++ListX2Index)
            {
                deindexer.Accept(cell_record->ACHR[ListX2Index]);
                CELL.achr_pool.destroy(cell_record->ACHR[ListX2Index]);
            }

            for(uint32_t ListX2Index = 0; ListX2Index < cell_record->ACRE.size(); ++ListX2Index)
            {
                deindexer.Accept(cell_record->ACRE[ListX2Index]);
                CELL.acre_pool.destroy(cell_record->ACRE[ListX2Index]);
            }

            for(uint32_t ListX2Index = 0; ListX2Index < cell_record->REFR.size(); ++ListX2Index)
            {
                deindexer.Accept(cell_record->REFR[ListX2Index]);
                CELL.refr_pool.destroy(cell_record->REFR[ListX2Index]);
            }

            for(uint32_t ListX2Index = 0; ListX2Index < cell_record->PGRE.size(); ++ListX2Index)
            {
                deindexer.Accept(cell_record->PGRE[ListX2Index]);
                CELL.pgre_pool.destroy(cell_record->PGRE[ListX2Index]);
            }

            for(uint32_t ListX2Index = 0; ListX2Index < cell_record->PMIS.size(); ++ListX2Index)
            {
                deindexer.Accept(cell_record->PMIS[ListX2Index]);
                CELL.pmis_pool.destroy(cell_record->PMIS[ListX2Index]);
            }

            for(uint32_t ListX2Index = 0; ListX2Index < cell_record->PBEA.size(); ++ListX2Index)
            {
                deindexer.Accept(cell_record->PBEA[ListX2Index]);
                CELL.pbea_pool.destroy(cell_record->PBEA[ListX2Index]);
            }

            for(uint32_t ListX2Index = 0; ListX2Index < cell_record->PFLA.size(); ++ListX2Index)
            {
                deindexer.Accept(cell_record->PFLA[ListX2Index]);
                CELL.pfla_pool.destroy(cell_record->PFLA[ListX2Index]);
            }

            for(uint32_t ListX2Index = 0; ListX2Index < cell_record->PCBE.size(); ++ListX2Index)
            {
                deindexer.Accept(cell_record->PCBE[ListX2Index]);
                CELL.pcbe_pool.destroy(cell_record->PCBE[ListX2Index]);
            }

            for(uint32_t ListX2Index = 0; ListX2Index < cell_record->NAVM.size(); ++ListX2Index)
            {
                deindexer.Accept(cell_record->NAVM[ListX2Index]);
                CELL.navm_pool.destroy(cell_record->NAVM[ListX2Index]);
            }
            */

            deindexer.Accept(cell_record->LAND);
            WRLD.land_pool.destroy(cell_record->LAND);

            deindexer.Accept((Record *&)cell_record);
            WRLD.cell_pool.destroy(cell_record);
        }

        deindexer.Accept(curRecord);
        WRLD.wrld_pool.destroy(curRecord);
    } // end WRLD
        return 1;
    /*
    case REV32(WTHR):
        deindexer.Accept(curRecord);
        WTHR.pool.destroy(curRecord);
        return 1;
    */
    default:
    {
        Record *Parent = curRecord->GetParentRecord();
        if(Parent != NULL)
        {
            Record *TopParent = Parent->GetParentRecord();
            if(TopParent != NULL)
                printer("TES4File::DeleteRecord: Error - Unable to delete record type (%s) with parent type (%s) in group (%s) in mod \"%s\". The parent record (%08X) does not contain the record to be deleted (%08X).\n", curRecord->GetStrType(), Parent->GetStrType(), TopParent->GetStrType(), ModName, Parent->formID, curRecord->formID);
            else
                printer("TES4File::DeleteRecord: Error - Unable to delete record type (%s) in group (%s) in mod \"%s\". The parent record (%08X) does not contain the record to be deleted (%08X).\n", curRecord->GetStrType(), Parent->GetStrType(), ModName, Parent->formID, curRecord->formID);
        }
        else
            printer("TES4File::DeleteRecord: Error - Unable to delete record type (%s) in group (%s) in mod \"%s\". The group does not contain the record to be deleted (%08X).\n", curRecord->GetStrType(), curRecord->GetStrType(), ModName, curRecord->formID);
    }
        return 0;
    }; // end switch

    return 0;
    }

int32_t TES5File::Save(char * const &SaveName, std::vector<FormIDResolver *> &Expanders, bool CloseMod, RecordOp &indexer)
    {
    if(!Flags.IsSaveable)
        {
        printer("TES5File::Save: Error - Unable to save mod \"%s\". It is flagged as being non-saveable.\n", ModName);
        return -1;
        }

    FileWriter writer(SaveName, BUFFERSIZE);
    if(writer.open() == -1)
        throw std::exception("TES5File::Save: Error - Unable to open temporary file for writing\n");

    uint32_t formCount = 0;
    FormIDResolver expander(FormIDHandler.ExpandTable, FormIDHandler.FileStart, FormIDHandler.FileEnd);
    FormIDResolver collapser(FormIDHandler.CollapseTable, FormIDHandler.FileStart, FormIDHandler.FileEnd);
    //RecordReader reader(FormIDHandler);
    const bool bMastersChanged = FormIDHandler.MastersChanged();

    TES4.Write(writer, bMastersChanged, expander, collapser, Expanders);

    //ADD DEFINITIONS HERE, but Write in the same Top GRUP order as Skyrim.esm
    // formCount += GMST.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += KYWD.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += LCRT.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += AACT.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += TXST.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += GLOB.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += CLAS.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += FACT.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += HDPT.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // HAIR - Skyrim.esm has an empty GRUP for these
    // formCount += EYES.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += RACE.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += SOUN.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += ASPC.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += MGEF.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // SCPT - Skyrim.esm has an empty GRUP for these
    formCount += LTEX.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += ENCH.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += SPEL.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += SCRL.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += ACTI.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += TACT.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += ARMO.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += BOOK.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += CONT.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += DOOR.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += INGR.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += LIGH.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += MISC.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += APPA.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += STAT.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // SCOL - Skyrim.esm has an empty GRUP for these
    // formCount += MSTT.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // PWAT - Skyrim.esm has an empty GRUP for these
    // formCount += GRAS.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += TREE.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // CLDC - Skyrim.esm has an empty GRUP for these
    // formCount += FLOR.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += FURN.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += WEAP.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += AMMO.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += NPC_.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += LVLN.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += KEYM.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += ALCH.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += IDLM.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += COBJ.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += PROJ.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += HAZD.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += SLGM.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += LVLI.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += WTHR.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += CLMT.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += SPGD.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += RFCT.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += REGN.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += NAVI.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += CELL.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += WRLD.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod, FormIDHandler, CELL, indexer);
    // formCount += DIAL.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += QUST.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += IDLE.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += PACK.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += CSTY.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += LSCR.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += LVSP.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += ANIO.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += WATR.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += EFSH.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += EXPL.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += DEBR.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += IMGS.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += IMAD.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += FLST.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += PERK.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += BPTD.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += ADDN.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += AVIF.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += CAMS.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += CPTH.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += VTYP.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += MATT.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += IPCT.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += IPDS.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += ARMA.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += ECZN.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += LCTN.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += MESG.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += RGDL.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += DOBJ.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += LGTM.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += MUSC.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += FSTP.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += FSTS.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += SMBN.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += SMQN.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += SMEN.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += DLBR.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += MUST.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += DLVW.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += WOOP.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += SHOU.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += EQUP.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += RELA.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += SCEN.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += ASTP.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += OTFT.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += ARTO.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += MATO.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += MOVT.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // HAZD - Skyrim.esm has a second GRUP here with no records
    // formCount += SNDR.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += DUAL.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += SNCT.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += SOPM.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += COLL.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += CLFM.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    // formCount += REVB.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);

    //update formCount. Cheaper to go back and write it at the end than to calculate it before any writing.
    writer.file_write(34, &formCount, 4);
    writer.close();

    return 0;
    }

void TES5File::VisitAllRecords(RecordOp &op)
    {
    if(Flags.IsNoLoad)
        {
        printer("TES5File::VisitAllRecords: Error - Unable to visit records in mod \"%s\". The mod is flagged not to be loaded.\n", ModName);
        return;
        }

    //This visits every record and subrecord
    {
        Record *temp = &TES4;
        op.Accept(temp);
    }

    //Child records need to be visited prior to the parent in order for identical to master cleaning to work nicely
    AACT.pool.VisitRecords(op);
    // ACHR - in CELL
    ACTI.pool.VisitRecords(op);
    ADDN.pool.VisitRecords(op);
    ALCH.pool.VisitRecords(op);
    // AMMO.pool.VisitRecords(op);
    ANIO.pool.VisitRecords(op);
    APPA.pool.VisitRecords(op);
    // ARMA.pool.VisitRecords(op);
    // ARMO.pool.VisitRecords(op);
    ARTO.pool.VisitRecords(op);
    ASPC.pool.VisitRecords(op);
    ASTP.pool.VisitRecords(op);
    // AVIF.pool.VisitRecords(op);
    // BOOK.pool.VisitRecords(op);
    // BPTD.pool.VisitRecords(op);
    // CAMS.pool.VisitRecords(op);
    // CELL
    {
        // CELL.achr_pool.VisitRecords(op);
        // CELL.navm_pool.VisitRecords(op);
        // CELL.pgre_pool.VisitRecords(op);
        // CELL.refr_pool.VisitRecords(op);
        CELL.cell_pool.VisitRecords(op);
    }
    // CLAS.pool.VisitRecords(op);
    // CLFM.pool.VisitRecords(op);
    // CLMT.pool.VisitRecords(op);
    // COBJ.pool.VisitRecords(op);
    COLL.pool.VisitRecords(op);
    // CONT.pool.VisitRecords(op);
    // CPTH.pool.VisitRecords(op);
    // CSTY.pool.VisitRecords(op);
    // DEBR.pool.VisitRecords(op);
    // DIAL
    {
        // DIAL.info_pool.VisitRecords(op);
        // DIAL.dial_pool.VisitRecords(op);
    }
    // DLBR.pool.VisitRecords(op);
    // DLVW.pool.VisitRecords(op);
    // DOBJ.pool.VisitRecords(op);
    // DOOR.pool.VisitRecords(op);
    // DUAL.pool.VisitRecords(op);
    // ECZN.pool.VisitRecords(op);
    // EFSH.pool.VisitRecords(op);
    // ENCH.pool.VisitRecords(op);
    EQUP.pool.VisitRecords(op);
    // EXPL.pool.VisitRecords(op);
    // EYES.pool.VisitRecords(op);
    // FACT.pool.VisitRecords(op);
    // FLOT.pool.VisitRecords(op);
    // FLST.pool.VisitRecords(op);
    // FSTP.pool.VisitRecords(op);
    // FSTS.pool.VisitRecords(op);
    // FURN.pool.VisitRecords(op);
    // GLOB.pool.VisitRecords(op);
    // GMST.pool.VisitRecords(op);
    // GRAS.pool.VisitRecords(op);
    // HAZD.pool.VisitRecords(op);
    // IDLE.pool.VisitRecords(op);
    // IDLM.pool.VisitRecords(op);
    // IMAD.pool.VisitRecords(op);
    // IMGS.pool.VisitRecords(op);
    // INFO - in DIAL
    // INGR.pool.VisitRecords(op);
    // IPCT.pool.VisitRecords(op);
    // IPDS.pool.VisitRecords(op);
    // KEYM.pool.VisitRecords(op);
    KYWD.pool.VisitRecords(op);
    // LAND - in WRLD
    // LCRT.pool.VisitRecords(op);
    // LCTN.pool.VisitRecords(op);
    // LGTM.pool.VisitRecords(op);
    // LIGH.pool.VisitRecords(op);
    // LSCR.pool.VisitRecords(op);
    LTEX.pool.VisitRecords(op);
    LVLI.pool.VisitRecords(op);
    LVLN.pool.VisitRecords(op);
    LVSP.pool.VisitRecords(op);
    // MATO.pool.VisitRecords(op);
    MATT.pool.VisitRecords(op);
    // MESG.pool.VisitRecords(op);
    // MGEF.pool.VisitRecords(op);
    // MISC.pool.VisitRecords(op);
    // MOVT.pool.VisitRecords(op);
    // MSTT.pool.VisitRecords(op);
    // MUSC.pool.VisitRecords(op);
    // MUST.pool.VisitRecords(op);
    // NAVI.pool.VisitRecords(op);
    // NAVM - in CELL
    // NPC_.pool.VisitRecords(op);
    OTFT.pool.VisitRecords(op);
    // PACK.pool.VisitRecords(op);
    // PERK.pool.VisitRecords(op);
    // PGRE - in CELL
    // PHZD.pool.VisitRecords(op); // in CELL?
    // PROJ.pool.VisitRecords(op);
    // QUST.pool.VisitRecords(op);
    // RACE.pool.VisitRecords(op);
    // REFR - in CELL
    // REGN.pool.VisitRecords(op);
    // RELA.pool.VisitRecords(op);
    // REVB.pool.VisitRecords(op);
    // RFCT.pool.VisitRecords(op);
    // SCEN.pool.VisitRecords(op);
    // SCRL.pool.VisitRecords(op);
    SHOU.pool.VisitRecords(op);
    // SLGM.pool.VisitRecords(op);
    // SMBN.pool.VisitRecords(op);
    // SMEN.pool.VisitRecords(op);
    // SMQN.pool.VisitRecords(op);
    // SNCT.pool.VisitRecords(op);
    // SNDR.pool.VisitRecords(op);
    // SOPM.pool.VisitRecords(op);
    // SOUN.pool.VisitRecords(op);
    // SPEL.pool.VisitRecords(op);
    // SPGD.pool.VisitRecords(op);
    // STAT.pool.VisitRecords(op);
    // TACT.pool.VisitRecords(op);
    // TREE.pool.VisitRecords(op);
    TXST.pool.VisitRecords(op);
    VTYP.pool.VisitRecords(op);
    // WATR.pool.VisitRecords(op);
    // WEAP.pool.VisitRecords(op);
    WOOP.pool.VisitRecords(op);
    // WRLD
    {
        WRLD.cell_pool.VisitRecords(op);
        WRLD.land_pool.VisitRecords(op);
        WRLD.wrld_pool.VisitRecords(op);
    }
    // WTHR.pool.VisitRecords(op);

    return;
    }

void TES5File::VisitRecords(const uint32_t &RecordType, RecordOp &op)
    {
    if(Flags.IsNoLoad)
    {
        printer("TES5File::VisitRecords: Error - Unable to visit records in mod \"%s\". The mod is flagged not to be loaded.\n", ModName);
        return;
    }

    switch(RecordType)
    {
    case REV32(TES4):
    {
        Record *temp = &TES4;
        op.Accept(temp);
    }
        break;

    case REV32(AACT):
        AACT.pool.VisitRecords(op);
        break;
    case REV32(ACHR):
        // CELL.achr_pool.VisitRecords(op);
        break;
    case REV32(ACTI):
        ACTI.pool.VisitRecords(op);
        break;
    case REV32(ADDN):
        ADDN.pool.VisitRecords(op);
        break;
    case REV32(ALCH):
        ALCH.pool.VisitRecords(op);
        break;
    case REV32(AMMO):
        // AMMO.pool.VisitRecords(op);
        break;
    case REV32(ANIO):
        ANIO.pool.VisitRecords(op);
        break;
    case REV32(APPA):
        APPA.pool.VisitRecords(op);
        break;
    case REV32(ARMA):
        // ARMA.pool.VisitRecords(op);
        break;
    case REV32(ARMO):
        // ARMO.pool.VisitRecords(op);
        break;
    case REV32(ARTO):
        ARTO.pool.VisitRecords(op);
        break;
    case REV32(ASPC):
        ASPC.pool.VisitRecords(op);
        break;
    case REV32(ASTP):
        ASTP.pool.VisitRecords(op);
        break;
    case REV32(AVIF):
        // AVIF.pool.VisitRecords(op);
        break;
    case REV32(BOOK):
        // BOOK.pool.VisitRecords(op);
        break;
    case REV32(BPTD):
        // BPTD.pool.VisitRecords(op);
        break;
    case REV32(CAMS):
        // CAMS.pool.VisitRecords(op);
        break;
    case REV32(CELL):
        CELL.cell_pool.VisitRecords(op);
        break;
    case REV32(CLSS):
        CELL.cell_pool.VisitRecords(op);
        WRLD.cell_pool.VisitRecords(op);
        break;
    case REV32(WCEL):
        WRLD.cell_pool.VisitRecords(op);
        break;
    case REV32(CLAS):
        // CLAS.pool.VisitRecords(op);
        break;
    case REV32(CLFM):
        // CLFM.pool.VisitRecords(op);
        break;
    case REV32(CLMT):
        // CLMT.pool.VisitRecords(op);
        break;
    case REV32(COBJ):
        // COBJ.pool.VisitRecords(op);
        break;
    case REV32(COLL):
        COLL.pool.VisitRecords(op);
        break;
    case REV32(CONT):
        // CONT.pool.VisitRecords(op);
        break;
    case REV32(CPTH):
        // CPTH.pool.VisitRecords(op);
        break;
    case REV32(CSTY):
        // CSTY.pool.VisitRecords(op);
        break;
    case REV32(DEBR):
        // DEBR.pool.VisitRecords(op);break;
    case REV32(DIAL):
        // DIAL.dial_pool.VisitRecords(op);
        break;
    case REV32(DLBR):
        // DLBR.pool.VisitRecords(op);
        break;
    case REV32(DLVW):
        // DLVW.pool.VisitRecords(op);
        break;
    case REV32(DOBJ):
        // DOBJ.pool.VisitRecords(op);
        break;
    case REV32(DOOR):
        // DOOR.pool.VisitRecords(op);
        break;
    case REV32(DUAL):
        // DUAL.pool.VisitRecords(op);
        break;
    case REV32(ECZN):
        // ECZN.pool.VisitRecords(op);
        break;
    case REV32(EFSH):
        // EFSH.pool.VisitRecords(op);
        break;
    case REV32(ENCH):
        // ENCH.pool.VisitRecords(op);
        break;
    case REV32(EQUP):
        EQUP.pool.VisitRecords(op);
        break;
    case REV32(EXPL):
        // EXPL.pool.VisitRecords(op);
        break;
    case REV32(EYES):
        // EYES.pool.VisitRecords(op);
        break;
    case REV32(FACT):
        // FACT.pool.VisitRecords(op);
        break;
    case REV32(FLOT):
        // FLOT.pool.VisitRecords(op);
        break;
    case REV32(FLST):
        // FLST.pool.VisitRecords(op);
        break;
    case REV32(FSTP):
        // FSTP.pool.VisitRecords(op);
        break;
    case REV32(FSTS):
        // FSTS.pool.VisitRecords(op);
        break;
    case REV32(FURN):
        // FURN.pool.VisitRecords(op);
        break;
    case REV32(GLOB):
        // GLOB.pool.VisitRecords(op);
        break;
    case REV32(GMST):
        // GMST.pool.VisitRecords(op);
        break;
    case REV32(GRAS):
        // GRAS.pool.VisitRecords(op);
        break;
    case REV32(HAZD):
        // HAZD.pool.VisitRecords(op);
        break;
    case REV32(IDLE):
        // IDLE.pool.VisitRecords(op);
        break;
    case REV32(IDLM):
        // IDLM.pool.VisitRecords(op);
        break;
    case REV32(IMAD):
        // IMAD.pool.VisitRecords(op);
        break;
    case REV32(IMGS):
        // IMGS.pool.VisitRecords(op);
        break;
    case REV32(INFO):
        // DIAL.info_pool.VisitRecords(op);
        break;
    case REV32(INGR):
        // INGR.pool.VisitRecords(op);
        break;
    case REV32(IPCT):
        // IPCT.pool.VisitRecords(op);
        break;
    case REV32(IPDS):
        // IPDS.pool.VisitRecords(op);
        break;
    case REV32(KEYM):
        // KEYM.pool.VisitRecords(op);
        break;
    case REV32(KYWD):
        KYWD.pool.VisitRecords(op);
        break;
    case REV32(LAND):
        WRLD.land_pool.VisitRecords(op);
        break;
    case REV32(LCRT):
        // LCRT.pool.VisitRecords(op);
        break;
    case REV32(LCTN):
        // LCTN.pool.VisitRecords(op);
        break;
    case REV32(LGTM):
        // LGTM.pool.VisitRecords(op);
        break;
    case REV32(LIGH):
        // LIGH.pool.VisitRecords(op);
        break;
    case REV32(LSCR):
        // LSCR.pool.VisitRecords(op);
        break;
    case REV32(LTEX):
        LTEX.pool.VisitRecords(op);
        break;
    case REV32(LVLI):
        LVLI.pool.VisitRecords(op);
        break;
    case REV32(LVLN):
        LVLN.pool.VisitRecords(op);
        break;
    case REV32(LVSP):
        LVSP.pool.VisitRecords(op);
        break;
    case REV32(MATO):
        // MATO.pool.VisitRecords(op);
        break;
    case REV32(MATT):
        MATT.pool.VisitRecords(op);
        break;
    case REV32(MESG):
        // MESG.pool.VisitRecords(op);
        break;
    case REV32(MGEF):
        // MGEF.pool.VisitRecords(op);
        break;
    case REV32(MISC):
        // MISC.pool.VisitRecords(op);
        break;
    case REV32(MOVT):
        // MOVT.pool.VisitRecords(op);
        break;
    case REV32(MSTT):
        // MSTT.pool.VisitRecords(op);
        break;
    case REV32(MUSC):
        // MUSC.pool.VisitRecords(op);
        break;
    case REV32(MUST):
        // MUST.pool.VisitRecords(op);
        break;
    case REV32(NAVI):
        // NAVI.pool.VisitRecords(op);
        break;
    case REV32(NAVM):
        // CELL.navm_pool.VisitRecords(op);
        break;
    case REV32(NPC_):
        // NPC_.pool.VisitRecords(op);
        break;
    case REV32(OTFT):
        OTFT.pool.VisitRecords(op);
        break;
    case REV32(PACK):
        // PACK.pool.VisitRecords(op);
        break;
    case REV32(PERK):
        // PERK.pool.VisitRecords(op);
        break;
    case REV32(PGRE):
        // CELL.pgre_pool.VisitRecords(op);
        break;
    case REV32(PHZD):
        // PHZD.pool.VisitRecords(op); // in CELL?
        break;
    case REV32(PROJ):
        // PROJ.pool.VisitRecords(op);
        break;
    case REV32(QUST):
        // QUST.pool.VisitRecords(op);
        break;
    case REV32(RACE):
        // RACE.pool.VisitRecords(op);
        break;
    case REV32(REFR):
        // CELL.refr_pool.VisitRecords(op);
        break;
    case REV32(REGN):
        // REGN.pool.VisitRecords(op);
        break;
    case REV32(RELA):
        // RELA.pool.VisitRecords(op);
        break;
    case REV32(REVB):
        // REVB.pool.VisitRecords(op);
        break;
    case REV32(RFCT):
        // RFCT.pool.VisitRecords(op);
        break;
    case REV32(SCEN):
        // SCEN.pool.VisitRecords(op);
        break;
    case REV32(SCRL):
        // SCRL.pool.VisitRecords(op);
        break;
    case REV32(SHOU):
        SHOU.pool.VisitRecords(op);
        break;
    case REV32(SLGM):
        // SLGM.pool.VisitRecords(op);
        break;
    case REV32(SMBN):
        // SMBN.pool.VisitRecords(op);
        break;
    case REV32(SMEN):
        // SMEN.pool.VisitRecords(op);
        break;
    case REV32(SMQN):
        // SMQN.pool.VisitRecords(op);
        break;
    case REV32(SNCT):
        // SNCT.pool.VisitRecords(op);
        break;
    case REV32(SNDR):
        // SNDR.pool.VisitRecords(op);
        break;
    case REV32(SOPM):
        // SOPM.pool.VisitRecords(op);
        break;
    case REV32(SOUN):
        // SOUN.pool.VisitRecords(op);
        break;
    case REV32(SPEL):
        // SPEL.pool.VisitRecords(op);
        break;
    case REV32(SPGD):
        // SPGD.pool.VisitRecords(op);
        break;
    case REV32(STAT):
        // STAT.pool.VisitRecords(op);
        break;
    case REV32(TACT):
        // TACT.pool.VisitRecords(op);
        break;
    case REV32(TREE):
        // TREE.pool.VisitRecords(op);
        break;
    case REV32(TXST):
        TXST.pool.VisitRecords(op);
        break;
    case REV32(VTYP):
        VTYP.pool.VisitRecords(op);
        break;
    case REV32(WATR):
        // WATR.pool.VisitRecords(op);
        break;
    case REV32(WEAP):
        // WEAP.pool.VisitRecords(op);
        break;
    case REV32(WOOP):
        WOOP.pool.VisitRecords(op);
        break;
    case REV32(WRLD):
        WRLD.wrld_pool.VisitRecords(op);
        break;
    case REV32(WTHR):
        // WTHR.pool.VisitRecords(op);
        break;
        default:
            printer("TES5File::VisitRecords: Error - Unable to visit record type (%c%c%c%c) in mod \"%s\". Unknown record type.\n", ((char *)&RecordType)[0], ((char *)&RecordType)[1], ((char *)&RecordType)[2], ((char *)&RecordType)[3], ModName);
            break;
    }; // end switch

    return;
    }
