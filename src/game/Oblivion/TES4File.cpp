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
// TES4File.cpp
#include "../Common.h"
#include "../GenericRecord.h"
#include "TES4File.h"

TES4File::TES4File(Collection *_Parent, char * FileName, char * ModName, const uint32_t _flags):
    ModFile(_Parent, FileName, ModName, _flags)
    {
    //
    }

TES4File::~TES4File()
    {
    //
    }

void TES4File::SetFilter(bool inclusive, boost::unordered_set<uint32_t> &RecordTypes, boost::unordered_set<FORMID> &WorldSpaces) {
  filter_inclusive = inclusive;
  filter_records = RecordTypes;
  filter_wspaces = WorldSpaces;
}

int32_t TES4File::LoadTES4()
    {
    if(TES4.IsLoaded() || !Open())
        {
        if(!TES4.IsLoaded() && !Open())
            printer("TES4File::LoadTES4: Error - Unable to load the TES4 record for mod \"%s\". The mod is not open for reading.\n", ModName);
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

    TES4.recData = buffer_position;
    TES4.Read();
    TES4.IsChanged(true); //prevents the record from ever being unloaded
    buffer_position += recSize;
    return 1;
    }

int32_t TES4File::Load(RecordOp &read_parser, RecordOp &indexer, std::vector<FormIDResolver *> &Expanders, std::vector<Record *> &DeletedRecords)
    {
    enum IgTopRecords {
        eIgGMST = REV32(GMST) | 0x00001000, //Record::fIsIgnored
        eIgGLOB = REV32(GLOB) | 0x00001000,
        eIgCLAS = REV32(CLAS) | 0x00001000,
        eIgFACT = REV32(FACT) | 0x00001000,
        eIgHAIR = REV32(HAIR) | 0x00001000,
        eIgEYES = REV32(EYES) | 0x00001000,
        eIgRACE = REV32(RACE) | 0x00001000,
        eIgSOUN = REV32(SOUN) | 0x00001000,
        eIgSKIL = REV32(SKIL) | 0x00001000,
        eIgMGEF = REV32(MGEF) | 0x00001000,
        eIgSCPT = REV32(SCPT) | 0x00001000,
        eIgLTEX = REV32(LTEX) | 0x00001000,
        eIgENCH = REV32(ENCH) | 0x00001000,
        eIgSPEL = REV32(SPEL) | 0x00001000,
        eIgBSGN = REV32(BSGN) | 0x00001000,
        eIgACTI = REV32(ACTI) | 0x00001000,
        eIgAPPA = REV32(APPA) | 0x00001000,
        eIgARMO = REV32(ARMO) | 0x00001000,
        eIgBOOK = REV32(BOOK) | 0x00001000,
        eIgCLOT = REV32(CLOT) | 0x00001000,
        eIgCONT = REV32(CONT) | 0x00001000,
        eIgDOOR = REV32(DOOR) | 0x00001000,
        eIgINGR = REV32(INGR) | 0x00001000,
        eIgLIGH = REV32(LIGH) | 0x00001000,
        eIgMISC = REV32(MISC) | 0x00001000,
        eIgSTAT = REV32(STAT) | 0x00001000,
        eIgGRAS = REV32(GRAS) | 0x00001000,
        eIgTREE = REV32(TREE) | 0x00001000,
        eIgFLOR = REV32(FLOR) | 0x00001000,
        eIgFURN = REV32(FURN) | 0x00001000,
        eIgWEAP = REV32(WEAP) | 0x00001000,
        eIgAMMO = REV32(AMMO) | 0x00001000,
        eIgNPC_ = REV32(NPC_) | 0x00001000,
        eIgCREA = REV32(CREA) | 0x00001000,
        eIgLVLC = REV32(LVLC) | 0x00001000,
        eIgSLGM = REV32(SLGM) | 0x00001000,
        eIgKEYM = REV32(KEYM) | 0x00001000,
        eIgALCH = REV32(ALCH) | 0x00001000,
        eIgSBSP = REV32(SBSP) | 0x00001000,
        eIgSGST = REV32(SGST) | 0x00001000,
        eIgLVLI = REV32(LVLI) | 0x00001000,
        eIgWTHR = REV32(WTHR) | 0x00001000,
        eIgCLMT = REV32(CLMT) | 0x00001000,
        eIgREGN = REV32(REGN) | 0x00001000,
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
        eIgEFSH = REV32(EFSH) | 0x00001000
        };
    if(Flags.IsNoLoad || Flags.IsCreateNew || !file_map.is_open() || Flags.LoadedGRUPs)
        {
        if(!(Flags.IsNoLoad || Flags.IsCreateNew))
            {
            if(!file_map.is_open())
                printer("TES4File::Load: Error - Unable to load mod \"%s\". The mod is not open.\n", ModName);
            else
                printer("TES4File::Load: Error - Unable to load mod \"%s\". The mod is already loaded.\n", ModName);
            }
        return 0;
        }

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
            //ADD DEFINITIONS HERE
            case eIgGMST:
            case REV32(GMST):
                GMST.Read(buffer_start, buffer_position, group_buffer_end, indexer, read_parser, DeletedRecords, processor, FileName);
                break;
            case eIgGLOB:
            case REV32(GLOB):
                GLOB.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgCLAS:
            case REV32(CLAS):
                CLAS.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgFACT:
            case REV32(FACT):
                FACT.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgHAIR:
            case REV32(HAIR):
                HAIR.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgEYES: //Same as normal
            case REV32(EYES):
                EYES.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgRACE:
            case REV32(RACE):
                RACE.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgSOUN:
            case REV32(SOUN):
                SOUN.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgSKIL:
            case REV32(SKIL):
                SKIL.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgMGEF:
            case REV32(MGEF):
                MGEF.Read(buffer_start, buffer_position, group_buffer_end, indexer, read_parser, DeletedRecords, processor, FileName);
                break;
            case eIgSCPT:
            case REV32(SCPT):
                SCPT.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgLTEX: //Same as normal
            case REV32(LTEX):
                LTEX.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgENCH:
            case REV32(ENCH):
                ENCH.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgSPEL: //Same as normal
            case REV32(SPEL):
                SPEL.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgBSGN: //Same as normal
            case REV32(BSGN):
                BSGN.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgACTI:
            case REV32(ACTI):
                ACTI.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgAPPA: //Same as normal
            case REV32(APPA):
                APPA.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgARMO: //Same as normal
            case REV32(ARMO):
                ARMO.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgBOOK:
            case REV32(BOOK):
                BOOK.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgCLOT:
            case REV32(CLOT):
                CLOT.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgCONT:
            case REV32(CONT):
                CONT.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgDOOR:
            case REV32(DOOR):
                DOOR.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgINGR:
            case REV32(INGR):
                INGR.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgLIGH:
            case REV32(LIGH):
                LIGH.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgMISC:
            case REV32(MISC):
                MISC.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgSTAT: //Same as normal
            case REV32(STAT):
                STAT.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgGRAS: //Same as normal
            case REV32(GRAS):
                GRAS.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgTREE: //Same as normal
            case REV32(TREE):
                TREE.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgFLOR:
            case REV32(FLOR):
                FLOR.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgFURN: //Same as normal
            case REV32(FURN):
                FURN.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgWEAP:
            case REV32(WEAP):
                WEAP.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgAMMO:
            case REV32(AMMO):
                AMMO.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgNPC_: //Same as normal
            case REV32(NPC_):
                NPC_.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgCREA: //Same as normal
            case REV32(CREA):
                CREA.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgLVLC: //Same as normal
            case REV32(LVLC):
                LVLC.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgSLGM:
            case REV32(SLGM):
                SLGM.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgKEYM:
            case REV32(KEYM):
                KEYM.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgALCH:
            case REV32(ALCH):
                ALCH.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgSBSP:
            case REV32(SBSP):
                SBSP.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgSGST:
            case REV32(SGST):
                SGST.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgLVLI: //Same as normal
            case REV32(LVLI):
                LVLI.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgWTHR: //Same as normal
            case REV32(WTHR):
                WTHR.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgCLMT:
            case REV32(CLMT):
                CLMT.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgREGN:
            case REV32(REGN):
                REGN.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgCELL:
            case REV32(CELL):
                CELL.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgWRLD: //Same as normal
            case REV32(WRLD):
                WRLD.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName, read_parser, CELL);
                break;
            case eIgDIAL:
            case REV32(DIAL):
                DIAL.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgQUST: //Same as normal
            case REV32(QUST):
                QUST.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgIDLE:
            case REV32(IDLE):
                IDLE.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgPACK:
            case REV32(PACK):
                PACK.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgCSTY: //Same as normal
            case REV32(CSTY):
                CSTY.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgLSCR: //Same as normal
            case REV32(LSCR):
                LSCR.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgLVSP: //Same as normal
            case REV32(LVSP):
                LVSP.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgANIO:
            case REV32(ANIO):
                ANIO.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgWATR:
            case REV32(WATR):
                WATR.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgEFSH:
            case REV32(EFSH):
                EFSH.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            default:
                if(GRUPLabel == 0 && GRUPSize == 0)
                    {
                    printer("TES4File::Read: Warning - Mod \"%s\" contains an unknown record group (%c%c%c%c). Bad file structure, zeros found past end of groups.\n", ModName, ((char *)&GRUPLabel)[0], ((char *)&GRUPLabel)[1], ((char *)&GRUPLabel)[2], ((char *)&GRUPLabel)[3]);
                    return 1;
                    }
                else
                    printer("TES4File::Read: Error - Mod \"%s\" contains an unknown record group (%c%c%c%c).", ModName, ((char *)&GRUPLabel)[0], ((char *)&GRUPLabel)[1], ((char *)&GRUPLabel)[2], ((char *)&GRUPLabel)[3]);

                if(GRUPSize == 0)
                    {
                    printer("Unable to continue loading.\n");
                    return 1;
                    }
                else
                    {
                    printer("Attempting to skip and continue loading.\n");
                    buffer_position = group_buffer_end;
                    }
                break;
            }
        };
    FormIDHandler.IsEmpty = UsedFormIDs.empty();
    return 1;
    }

uint32_t TES4File::GetNumRecords(const uint32_t &RecordType)
    {
    switch(RecordType)
        {
        case REV32(GMST):
            return (uint32_t)GMST.pool.used_object_capacity();
        case REV32(GLOB):
            return (uint32_t)GLOB.pool.used_object_capacity();
        case REV32(CLAS):
            return (uint32_t)CLAS.pool.used_object_capacity();
        case REV32(FACT):
            return (uint32_t)FACT.pool.used_object_capacity();
        case REV32(HAIR):
            return (uint32_t)HAIR.pool.used_object_capacity();
        case REV32(EYES):
            return (uint32_t)EYES.pool.used_object_capacity();
        case REV32(RACE):
            return (uint32_t)RACE.pool.used_object_capacity();
        case REV32(SOUN):
            return (uint32_t)SOUN.pool.used_object_capacity();
        case REV32(SKIL):
            return (uint32_t)SKIL.pool.used_object_capacity();
        case REV32(MGEF):
            return (uint32_t)MGEF.pool.used_object_capacity();
        case REV32(SCPT):
            return (uint32_t)SCPT.pool.used_object_capacity();
        case REV32(LTEX):
            return (uint32_t)LTEX.pool.used_object_capacity();
        case REV32(ENCH):
            return (uint32_t)ENCH.pool.used_object_capacity();
        case REV32(SPEL):
            return (uint32_t)SPEL.pool.used_object_capacity();
        case REV32(BSGN):
            return (uint32_t)BSGN.pool.used_object_capacity();
        case REV32(ACTI):
            return (uint32_t)ACTI.pool.used_object_capacity();
        case REV32(APPA):
            return (uint32_t)APPA.pool.used_object_capacity();
        case REV32(ARMO):
            return (uint32_t)ARMO.pool.used_object_capacity();
        case REV32(BOOK):
            return (uint32_t)BOOK.pool.used_object_capacity();
        case REV32(CLOT):
            return (uint32_t)CLOT.pool.used_object_capacity();
        case REV32(CONT):
            return (uint32_t)CONT.pool.used_object_capacity();
        case REV32(DOOR):
            return (uint32_t)DOOR.pool.used_object_capacity();
        case REV32(INGR):
            return (uint32_t)INGR.pool.used_object_capacity();
        case REV32(LIGH):
            return (uint32_t)LIGH.pool.used_object_capacity();
        case REV32(MISC):
            return (uint32_t)MISC.pool.used_object_capacity();
        case REV32(STAT):
            return (uint32_t)STAT.pool.used_object_capacity();
        case REV32(GRAS):
            return (uint32_t)GRAS.pool.used_object_capacity();
        case REV32(TREE):
            return (uint32_t)TREE.pool.used_object_capacity();
        case REV32(FLOR):
            return (uint32_t)FLOR.pool.used_object_capacity();
        case REV32(FURN):
            return (uint32_t)FURN.pool.used_object_capacity();
        case REV32(WEAP):
            return (uint32_t)WEAP.pool.used_object_capacity();
        case REV32(AMMO):
            return (uint32_t)AMMO.pool.used_object_capacity();
        case REV32(NPC_):
            return (uint32_t)NPC_.pool.used_object_capacity();
        case REV32(CREA):
            return (uint32_t)CREA.pool.used_object_capacity();
        case REV32(LVLC):
            return (uint32_t)LVLC.pool.used_object_capacity();
        case REV32(SLGM):
            return (uint32_t)SLGM.pool.used_object_capacity();
        case REV32(KEYM):
            return (uint32_t)KEYM.pool.used_object_capacity();
        case REV32(ALCH):
            return (uint32_t)ALCH.pool.used_object_capacity();
        case REV32(SBSP):
            return (uint32_t)SBSP.pool.used_object_capacity();
        case REV32(SGST):
            return (uint32_t)SGST.pool.used_object_capacity();
        case REV32(LVLI):
            return (uint32_t)LVLI.pool.used_object_capacity();
        case REV32(WTHR):
            return (uint32_t)WTHR.pool.used_object_capacity();
        case REV32(CLMT):
            return (uint32_t)CLMT.pool.used_object_capacity();
        case REV32(REGN):
            return (uint32_t)REGN.pool.used_object_capacity();
        case REV32(CELL):
            return (uint32_t)CELL.cell_pool.used_object_capacity();
        case REV32(WRLD):
            return (uint32_t)WRLD.wrld_pool.used_object_capacity();
        case REV32(DIAL):
            return (uint32_t)DIAL.dial_pool.used_object_capacity();
        ///////////////////////////////////////////////
        //These return the absolute total number of these SubRecords
        //Use the GetFieldAttribute API instead if you want the number
        // of SubRecords associated with a specific parent record
        case REV32(PGRD):
            return (uint32_t)CELL.pgrd_pool.used_object_capacity();
        case REV32(LAND):
            return (uint32_t)WRLD.land_pool.used_object_capacity();
        case REV32(ACHR):
            return (uint32_t)CELL.achr_pool.used_object_capacity();
        case REV32(ACRE):
            return (uint32_t)CELL.acre_pool.used_object_capacity();
        case REV32(REFR):
            return (uint32_t)CELL.refr_pool.used_object_capacity();
        case REV32(ROAD):
            return (uint32_t)WRLD.road_pool.used_object_capacity();
        case REV32(INFO):
            return (uint32_t)DIAL.info_pool.used_object_capacity();
        case REV32(WCEL):
            return (uint32_t)WRLD.cell_pool.used_object_capacity();
        case REV32(CLLS):
            return (uint32_t)CELL.cell_pool.used_object_capacity() + (uint32_t)WRLD.cell_pool.used_object_capacity();
        ///////////////////////////////////////////////
        case REV32(QUST):
            return (uint32_t)QUST.pool.used_object_capacity();
        case REV32(IDLE):
            return (uint32_t)IDLE.pool.used_object_capacity();
        case REV32(PACK):
            return (uint32_t)PACK.pool.used_object_capacity();
        case REV32(CSTY):
            return (uint32_t)CSTY.pool.used_object_capacity();
        case REV32(LSCR):
            return (uint32_t)LSCR.pool.used_object_capacity();
        case REV32(LVSP):
            return (uint32_t)LVSP.pool.used_object_capacity();
        case REV32(ANIO):
            return (uint32_t)ANIO.pool.used_object_capacity();
        case REV32(WATR):
            return (uint32_t)WATR.pool.used_object_capacity();
        case REV32(EFSH):
            return (uint32_t)EFSH.pool.used_object_capacity();
        default:
            printer("TES4File::GetNumRecords: Warning - Unable to count records (%c%c%c%c) in mod \"%s\". Unrecognized record type.\n", ((char *)&RecordType)[0], ((char *)&RecordType)[1], ((char *)&RecordType)[2], ((char *)&RecordType)[3], ModName);
            break;
        }
    return 0;
    }

Record * TES4File::CreateRecord(const uint32_t &RecordType, char * const &RecordEditorID, Record *&SourceRecord, Record *&ParentRecord, CreationFlags &options)
    {
    //if(Flags.IsNoLoad)
    //    {
    //    printer("TES4File::CreateRecord: Error - Unable to create any records in mod \"%s\". The mod is flagged not to be loaded.\n", ModName);
    //    return NULL;
    //    }

    Record *newRecord = NULL;

    switch(RecordType)
        {
        case REV32(GMST):
            if(RecordEditorID == NULL && SourceRecord == NULL)
                {
                printer("TES4File::CreateRecord: Error - Unable to create GMST record in mod \"%s\". No valid editorID is available.\n", ModName);
                return NULL;
                }
            newRecord = GMST.pool.construct(SourceRecord, this, true);

            if(RecordEditorID != NULL)
                {
                ((Ob::GMSTRecord *)newRecord)->EDID.Copy(RecordEditorID);
                ((Ob::GMSTRecord *)newRecord)->DATA.format = ((Ob::GMSTRecord *)newRecord)->EDID.value[0];
                }
            return newRecord;
        case REV32(GLOB):
            return GLOB.pool.construct(SourceRecord, this, true);
        case REV32(CLAS):
            return CLAS.pool.construct(SourceRecord, this, true);
        case REV32(FACT):
            return FACT.pool.construct(SourceRecord, this, true);
        case REV32(HAIR):
            return HAIR.pool.construct(SourceRecord, this, true);
        case REV32(EYES):
            return EYES.pool.construct(SourceRecord, this, true);
        case REV32(RACE):
            return RACE.pool.construct(SourceRecord, this, true);
        case REV32(SOUN):
            return SOUN.pool.construct(SourceRecord, this, true);
        case REV32(SKIL):
            return SKIL.pool.construct(SourceRecord, this, true);
        case REV32(MGEF):
            if(RecordEditorID == NULL && SourceRecord == NULL)
                {
                printer("TES4File::CreateRecord: Error - Unable to create MGEF record in mod \"%s\". No valid editorID is available.\n", ModName);
                return NULL;
                }

            newRecord = MGEF.pool.construct(SourceRecord, this, true);

            if(RecordEditorID != NULL)
                ((Ob::MGEFRecord *)newRecord)->EDID.Copy(RecordEditorID);
            return newRecord;
        case REV32(SCPT):
            return SCPT.pool.construct(SourceRecord, this, true);
        case REV32(LTEX):
            return LTEX.pool.construct(SourceRecord, this, true);
        case REV32(ENCH):
            return ENCH.pool.construct(SourceRecord, this, true);
        case REV32(SPEL):
            return SPEL.pool.construct(SourceRecord, this, true);
        case REV32(BSGN):
            return BSGN.pool.construct(SourceRecord, this, true);
        case REV32(ACTI):
            return ACTI.pool.construct(SourceRecord, this, true);
        case REV32(APPA):
            return APPA.pool.construct(SourceRecord, this, true);
        case REV32(ARMO):
            return ARMO.pool.construct(SourceRecord, this, true);
        case REV32(BOOK):
            return BOOK.pool.construct(SourceRecord, this, true);
        case REV32(CLOT):
            return CLOT.pool.construct(SourceRecord, this, true);
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
        case REV32(GRAS):
            return GRAS.pool.construct(SourceRecord, this, true);
        case REV32(TREE):
            return TREE.pool.construct(SourceRecord, this, true);
        case REV32(FLOR):
            return FLOR.pool.construct(SourceRecord, this, true);
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
        case REV32(SLGM):
            return SLGM.pool.construct(SourceRecord, this, true);
        case REV32(KEYM):
            return KEYM.pool.construct(SourceRecord, this, true);
        case REV32(ALCH):
            return ALCH.pool.construct(SourceRecord, this, true);
        case REV32(SBSP):
            return SBSP.pool.construct(SourceRecord, this, true);
        case REV32(SGST):
            return SGST.pool.construct(SourceRecord, this, true);
        case REV32(LVLI):
            return LVLI.pool.construct(SourceRecord, this, true);
        case REV32(WTHR):
            return WTHR.pool.construct(SourceRecord, this, true);
        case REV32(CLMT):
            return CLMT.pool.construct(SourceRecord, this, true);
        case REV32(REGN):
            return REGN.pool.construct(SourceRecord, this, true);
        case REV32(WCEL):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(WRLD))
                {
                printer("TES4File::CreateRecord: Error - Unable to create world CELL record in mod \"%s\". Parent record type (%s) is invalid, only WRLD records can be world CELL parents.\n", ModName, ParentRecord->GetStrType());
                return NULL;
                }

            //If a world cell already exists, return it instead of making a new one
            if(((Ob::WRLDRecord *)ParentRecord)->CELL != NULL)
                {
                options.ExistingReturned = true;
                return ((Ob::WRLDRecord *)ParentRecord)->CELL;
                }

            ((Ob::WRLDRecord *)ParentRecord)->CELL = WRLD.cell_pool.construct(SourceRecord, ParentRecord, false);
            ((Ob::CELLRecord *)((Ob::WRLDRecord *)ParentRecord)->CELL)->IsInterior(false);
            return ((Ob::WRLDRecord *)ParentRecord)->CELL;
        case REV32(CELL):
            if(ParentRecord == NULL)
                {
                newRecord = CELL.cell_pool.construct(SourceRecord, this, true);
                ((Ob::CELLRecord *)newRecord)->IsInterior(true);
                return newRecord;
                }
            else
                {
                if(ParentRecord->GetType() != REV32(WRLD))
                    {
                    printer("TES4File::CreateRecord: Error - Unable to create CELL record in mod \"%s\". Parent record type (%s) is invalid, only WRLD records can be CELL parents.\n", ModName, ParentRecord->GetStrType());
                    return NULL;
                    }

                //If the SourceRecord is a world cell, then the copy will be a world cell

                if(SourceRecord != NULL && ((Ob::WRLDRecord *)((Ob::CELLRecord *)SourceRecord)->GetParentRecord())->CELL == SourceRecord)
                    {
                    //If a world cell already exists, return it instead of making a new one
                    if(((Ob::WRLDRecord *)ParentRecord)->CELL != NULL)
                        {
                        options.ExistingReturned = true;
                        return ((Ob::WRLDRecord *)ParentRecord)->CELL;
                        }
                    newRecord = ((Ob::WRLDRecord *)ParentRecord)->CELL = WRLD.cell_pool.construct(SourceRecord, ParentRecord, false);
                    }
                else
                    {
                    newRecord = WRLD.cell_pool.construct(SourceRecord, ParentRecord, false);
                    ((Ob::WRLDRecord *)ParentRecord)->CELLS.push_back(newRecord);
                    }

                ((Ob::CELLRecord *)newRecord)->IsInterior(false);
                return newRecord;
                }
        case REV32(WRLD):
            return WRLD.wrld_pool.construct(SourceRecord, this, true);
        case REV32(DIAL):
            return DIAL.dial_pool.construct(SourceRecord, this, true);
        case REV32(INFO):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(DIAL))
                {
                printer("TES4File::CreateRecord: Error - Unable to create INFO record in mod \"%s\". Parent record type (%s) is invalid, only DIAL records can be INFO parents.\n", ModName, ParentRecord->GetStrType());
                return NULL;
                }

            ((Ob::DIALRecord *)ParentRecord)->INFO.push_back(DIAL.info_pool.construct(SourceRecord, ParentRecord, false));
            return ((Ob::DIALRecord *)ParentRecord)->INFO.back();
        case REV32(PGRD):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
                {
                printer("TES4File::CreateRecord: Error - Unable to create PGRD record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be PGRD parents.\n", ModName, ParentRecord->GetStrType());
                return NULL;
                }

            //If a cell pathgrid already exists, return it instead of making a new one
            if(((Ob::CELLRecord *)ParentRecord)->PGRD != NULL)
                {
                options.ExistingReturned = true;
                return ((Ob::CELLRecord *)ParentRecord)->PGRD;
                }

            ((Ob::CELLRecord *)ParentRecord)->PGRD = CELL.pgrd_pool.construct(SourceRecord, ParentRecord, false);
            return ((Ob::CELLRecord *)ParentRecord)->PGRD;
        case REV32(LAND):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
                {
                printer("TES4File::CreateRecord: Error - Unable to create LAND record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be LAND parents.\n", ModName, ParentRecord->GetStrType());
                return NULL;
                }

            //If a cell land already exists, return it instead of making a new one
            if(((Ob::CELLRecord *)ParentRecord)->LAND != NULL)
                {
                options.ExistingReturned = true;
                return ((Ob::CELLRecord *)ParentRecord)->LAND;
                }

            ((Ob::CELLRecord *)ParentRecord)->LAND = WRLD.land_pool.construct(SourceRecord, ParentRecord, false);
            return ((Ob::CELLRecord *)ParentRecord)->LAND;
        case REV32(ACHR):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
                {
                printer("TES4File::CreateRecord: Error - Unable to create ACHR record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be ACHR parents.\n", ModName, ParentRecord->GetStrType());
                return NULL;
                }

            ((Ob::CELLRecord *)ParentRecord)->ACHR.push_back(CELL.achr_pool.construct(SourceRecord, ParentRecord, false));
            return ((Ob::CELLRecord *)ParentRecord)->ACHR.back();
        case REV32(ACRE):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
                {
                printer("TES4File::CreateRecord: Error - Unable to create ACRE record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be ACRE parents.\n", ModName, ParentRecord->GetStrType());
                return NULL;
                }

            ((Ob::CELLRecord *)ParentRecord)->ACRE.push_back(CELL.acre_pool.construct(SourceRecord, ParentRecord, false));
            return ((Ob::CELLRecord *)ParentRecord)->ACRE.back();
        case REV32(REFR):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
                {
                printer("TES4File::CreateRecord: Error - Unable to create REFR record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be REFR parents.\n", ModName, ParentRecord->GetStrType());
                return NULL;
                }

            ((Ob::CELLRecord *)ParentRecord)->REFR.push_back(CELL.refr_pool.construct(SourceRecord, ParentRecord, false));
            return ((Ob::CELLRecord *)ParentRecord)->REFR.back();
        case REV32(ROAD):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(WRLD))
                {
                printer("TES4File::CreateRecord: Error - Unable to create ROAD record in mod \"%s\". Parent record type (%s) is invalid, only WRLD records can be ROAD parents.\n", ModName, ParentRecord->GetStrType());
                return NULL;
                }

            //If a world road already exists, return it instead of making a new one
            if(((Ob::WRLDRecord *)ParentRecord)->ROAD != NULL)
                {
                options.ExistingReturned = true;
                return ((Ob::WRLDRecord *)ParentRecord)->ROAD;
                }

            ((Ob::WRLDRecord *)ParentRecord)->ROAD = WRLD.road_pool.construct(SourceRecord, ParentRecord, false);
            return ((Ob::WRLDRecord *)ParentRecord)->ROAD;
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
        case REV32(LVSP):
            return LVSP.pool.construct(SourceRecord, this, true);
        case REV32(ANIO):
            return ANIO.pool.construct(SourceRecord, this, true);
        case REV32(WATR):
            return WATR.pool.construct(SourceRecord, this, true);
        case REV32(EFSH):
            return EFSH.pool.construct(SourceRecord, this, true);
        default:
            printer("TES4File::CreateRecord: Error - Unable to create (%c%c%c%c) record in mod \"%s\". Unknown record type.\n", ((char *)&RecordType)[0], ((char *)&RecordType)[1], ((char *)&RecordType)[2], ((char *)&RecordType)[3], ModName);
            break;
        }
    return NULL;
    }

int32_t TES4File::DeleteRecord(Record *&curRecord, RecordOp &deindexer)
    {
    switch(curRecord->GetType())
        {
        case REV32(GMST):
            deindexer.Accept(curRecord);
            GMST.pool.destroy(curRecord);
            return 1;
        case REV32(GLOB):
            deindexer.Accept(curRecord);
            GLOB.pool.destroy(curRecord);
            return 1;
        case REV32(CLAS):
            deindexer.Accept(curRecord);
            CLAS.pool.destroy(curRecord);
            return 1;
        case REV32(FACT):
            deindexer.Accept(curRecord);
            FACT.pool.destroy(curRecord);
            return 1;
        case REV32(HAIR):
            deindexer.Accept(curRecord);
            HAIR.pool.destroy(curRecord);
            return 1;
        case REV32(EYES):
            deindexer.Accept(curRecord);
            EYES.pool.destroy(curRecord);
            return 1;
        case REV32(RACE):
            deindexer.Accept(curRecord);
            RACE.pool.destroy(curRecord);
            return 1;
        case REV32(SOUN):
            deindexer.Accept(curRecord);
            SOUN.pool.destroy(curRecord);
            return 1;
        case REV32(SKIL):
            deindexer.Accept(curRecord);
            SKIL.pool.destroy(curRecord);
            return 1;
        case REV32(MGEF):
            deindexer.Accept(curRecord);
            MGEF.pool.destroy(curRecord);
            return 1;
        case REV32(SCPT):
            deindexer.Accept(curRecord);
            SCPT.pool.destroy(curRecord);
            return 1;
        case REV32(LTEX):
            deindexer.Accept(curRecord);
            LTEX.pool.destroy(curRecord);
            return 1;
        case REV32(ENCH):
            deindexer.Accept(curRecord);
            ENCH.pool.destroy(curRecord);
            return 1;
        case REV32(SPEL):
            deindexer.Accept(curRecord);
            SPEL.pool.destroy(curRecord);
            return 1;
        case REV32(BSGN):
            deindexer.Accept(curRecord);
            BSGN.pool.destroy(curRecord);
            return 1;
        case REV32(ACTI):
            deindexer.Accept(curRecord);
            ACTI.pool.destroy(curRecord);
            return 1;
        case REV32(APPA):
            deindexer.Accept(curRecord);
            APPA.pool.destroy(curRecord);
            return 1;
        case REV32(ARMO):
            deindexer.Accept(curRecord);
            ARMO.pool.destroy(curRecord);
            return 1;
        case REV32(BOOK):
            deindexer.Accept(curRecord);
            BOOK.pool.destroy(curRecord);
            return 1;
        case REV32(CLOT):
            deindexer.Accept(curRecord);
            CLOT.pool.destroy(curRecord);
            return 1;
        case REV32(CONT):
            deindexer.Accept(curRecord);
            CONT.pool.destroy(curRecord);
            return 1;
        case REV32(DOOR):
            deindexer.Accept(curRecord);
            DOOR.pool.destroy(curRecord);
            return 1;
        case REV32(INGR):
            deindexer.Accept(curRecord);
            INGR.pool.destroy(curRecord);
            return 1;
        case REV32(LIGH):
            deindexer.Accept(curRecord);
            LIGH.pool.destroy(curRecord);
            return 1;
        case REV32(MISC):
            deindexer.Accept(curRecord);
            MISC.pool.destroy(curRecord);
            return 1;
        case REV32(STAT):
            deindexer.Accept(curRecord);
            STAT.pool.destroy(curRecord);
            return 1;
        case REV32(GRAS):
            deindexer.Accept(curRecord);
            GRAS.pool.destroy(curRecord);
            return 1;
        case REV32(TREE):
            deindexer.Accept(curRecord);
            TREE.pool.destroy(curRecord);
            return 1;
        case REV32(FLOR):
            deindexer.Accept(curRecord);
            FLOR.pool.destroy(curRecord);
            return 1;
        case REV32(FURN):
            deindexer.Accept(curRecord);
            FURN.pool.destroy(curRecord);
            return 1;
        case REV32(WEAP):
            deindexer.Accept(curRecord);
            WEAP.pool.destroy(curRecord);
            return 1;
        case REV32(AMMO):
            deindexer.Accept(curRecord);
            AMMO.pool.destroy(curRecord);
            return 1;
        case REV32(NPC_):
            deindexer.Accept(curRecord);
            NPC_.pool.destroy(curRecord);
            return 1;
        case REV32(CREA):
            deindexer.Accept(curRecord);
            CREA.pool.destroy(curRecord);
            return 1;
        case REV32(LVLC):
            deindexer.Accept(curRecord);
            LVLC.pool.destroy(curRecord);
            return 1;
        case REV32(SLGM):
            deindexer.Accept(curRecord);
            SLGM.pool.destroy(curRecord);
            return 1;
        case REV32(KEYM):
            deindexer.Accept(curRecord);
            KEYM.pool.destroy(curRecord);
            return 1;
        case REV32(ALCH):
            deindexer.Accept(curRecord);
            ALCH.pool.destroy(curRecord);
            return 1;
        case REV32(SBSP):
            deindexer.Accept(curRecord);
            SBSP.pool.destroy(curRecord);
            return 1;
        case REV32(SGST):
            deindexer.Accept(curRecord);
            SGST.pool.destroy(curRecord);
            return 1;
        case REV32(LVLI):
            deindexer.Accept(curRecord);
            LVLI.pool.destroy(curRecord);
            return 1;
        case REV32(WTHR):
            deindexer.Accept(curRecord);
            WTHR.pool.destroy(curRecord);
            return 1;
        case REV32(CLMT):
            deindexer.Accept(curRecord);
            CLMT.pool.destroy(curRecord);
            return 1;
        case REV32(REGN):
            deindexer.Accept(curRecord);
            REGN.pool.destroy(curRecord);
            return 1;
        case REV32(CELL):
            {
            Ob::WRLDRecord *wrld_record = (Ob::WRLDRecord *)curRecord->GetParentRecord();
            bool cell_found = false;
            if(wrld_record != NULL)
                {
                if(wrld_record->CELL == curRecord)
                    {
                    wrld_record->CELL = NULL;
                    cell_found = true;
                    }
                else
                    {
                    for(uint32_t ListIndex = 0; ListIndex < wrld_record->CELLS.size(); ++ListIndex)
                        {
                        if(wrld_record->CELLS[ListIndex] == curRecord)
                            {
                            wrld_record->CELLS.erase(wrld_record->CELLS.begin() + ListIndex);
                            cell_found = true;
                            break;
                            }
                        }
                    }
                if(!cell_found)
                    {
                    printer("TES4File::DeleteRecord: Error - Unable to delete record type (%s) with parent type (%s) in mod \"%s\". The parent record (%08X) does not contain the record to be deleted (%08X).\n", curRecord->GetStrType(), curRecord->GetParentRecord()->GetStrType(), ModName, curRecord->GetParentRecord()->formID, curRecord->formID);
                    return 0;
                    }
                }

            Ob::CELLRecord *cell_record = (Ob::CELLRecord *)curRecord;
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

            deindexer.Accept(cell_record->PGRD);
            CELL.pgrd_pool.destroy(cell_record->PGRD);

            deindexer.Accept(cell_record->LAND);
            WRLD.land_pool.destroy(cell_record->LAND);

            deindexer.Accept(curRecord);
            if(cell_found)
                WRLD.cell_pool.destroy(curRecord);
            else
                CELL.cell_pool.destroy(curRecord);
            }
            return 1;
        case REV32(WRLD):
            {
            Ob::WRLDRecord *wrld_record = (Ob::WRLDRecord *)curRecord;

            deindexer.Accept(wrld_record->ROAD);
            WRLD.road_pool.destroy(wrld_record->ROAD);

            Ob::CELLRecord *cell_record = (Ob::CELLRecord *)wrld_record->CELL;
            if(cell_record != NULL) //Add it to list of cells to be deleted
                wrld_record->CELLS.push_back(cell_record);

            for(uint32_t ListIndex = 0; ListIndex < wrld_record->CELLS.size(); ++ListIndex)
                {
                cell_record = (Ob::CELLRecord *)wrld_record->CELLS[ListIndex];
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

                deindexer.Accept(cell_record->PGRD);
                CELL.pgrd_pool.destroy(cell_record->PGRD);

                deindexer.Accept(cell_record->LAND);
                WRLD.land_pool.destroy(cell_record->LAND);

                deindexer.Accept((Record *&)cell_record);
                WRLD.cell_pool.destroy(cell_record);
                }

            deindexer.Accept(curRecord);
            WRLD.wrld_pool.destroy(curRecord);
            }
            return 1;
        case REV32(ACHR):
            {
            Ob::CELLRecord *cell_record = (Ob::CELLRecord *)curRecord->GetParentRecord();
            bool achr_found = false;
            for(uint32_t ListIndex = 0; ListIndex < cell_record->ACHR.size(); ++ListIndex)
                {
                if(cell_record->ACHR[ListIndex] == curRecord)
                    {
                    cell_record->ACHR.erase(cell_record->ACHR.begin() + ListIndex);
                    achr_found = true;
                    break;
                    }
                }
            if(!achr_found)
                {
                printer("TES4File::DeleteRecord: Error - Unable to delete record type (%s) with parent type (%s) in mod \"%s\". The parent record (%08X) does not contain the record to be deleted (%08X).\n", curRecord->GetStrType(), curRecord->GetParentRecord()->GetStrType(), ModName, curRecord->GetParentRecord()->formID, curRecord->formID);
                return 0;
                }

            deindexer.Accept(curRecord);
            CELL.achr_pool.destroy(curRecord);
            }
            return 1;
        case REV32(ACRE):
            {
            Ob::CELLRecord *cell_record = (Ob::CELLRecord *)curRecord->GetParentRecord();
            bool acre_found = false;
            for(uint32_t ListIndex = 0; ListIndex < cell_record->ACRE.size(); ++ListIndex)
                {
                if(cell_record->ACRE[ListIndex] == curRecord)
                    {
                    cell_record->ACRE.erase(cell_record->ACRE.begin() + ListIndex);
                    acre_found = true;
                    break;
                    }
                }
            if(!acre_found)
                {
                printer("TES4File::DeleteRecord: Error - Unable to delete record type (%s) with parent type (%s) in mod \"%s\". The parent record (%08X) does not contain the record to be deleted (%08X).\n", curRecord->GetStrType(), curRecord->GetParentRecord()->GetStrType(), ModName, curRecord->GetParentRecord()->formID, curRecord->formID);
                return 0;
                }

            deindexer.Accept(curRecord);
            CELL.acre_pool.destroy(curRecord);
            }
            return 1;
        case REV32(REFR):
            {
            Ob::CELLRecord *cell_record = (Ob::CELLRecord *)curRecord->GetParentRecord();
            bool refr_found = false;
            for(uint32_t ListIndex = 0; ListIndex < cell_record->REFR.size(); ++ListIndex)
                {
                if(cell_record->REFR[ListIndex] == curRecord)
                    {
                    cell_record->REFR.erase(cell_record->REFR.begin() + ListIndex);
                    refr_found = true;
                    break;
                    }
                }
            if(!refr_found)
                {
                printer("TES4File::DeleteRecord: Error - Unable to delete record type (%s) with parent type (%s) in mod \"%s\". The parent record (%08X) does not contain the record to be deleted (%08X).\n", curRecord->GetStrType(), curRecord->GetParentRecord()->GetStrType(), ModName, curRecord->GetParentRecord()->formID, curRecord->formID);
                return 0;
                }

            deindexer.Accept(curRecord);
            CELL.refr_pool.destroy(curRecord);
            }
            return 1;
        case REV32(PGRD):
            {
            Ob::CELLRecord *cell_record = (Ob::CELLRecord *)curRecord->GetParentRecord();

            if(cell_record->PGRD != curRecord)
                {
                printer("TES4File::DeleteRecord: Error - Unable to delete record type (%s) with parent type (%s) in mod \"%s\". The parent record (%08X) does not contain the record to be deleted (%08X).\n", curRecord->GetStrType(), curRecord->GetParentRecord()->GetStrType(), ModName, curRecord->GetParentRecord()->formID, curRecord->formID);
                return 0;
                }

            cell_record->PGRD = NULL;
            deindexer.Accept(curRecord);
            CELL.pgrd_pool.destroy(curRecord);
            }
            return 1;
        case REV32(LAND):
            {
            Ob::CELLRecord *cell_record = (Ob::CELLRecord *)curRecord->GetParentRecord();

            if(cell_record->LAND != curRecord)
                {
                printer("TES4File::DeleteRecord: Error - Unable to delete record type (%s) with parent type (%s) in mod \"%s\". The parent record (%08X) does not contain the record to be deleted (%08X).\n", curRecord->GetStrType(), curRecord->GetParentRecord()->GetStrType(), ModName, curRecord->GetParentRecord()->formID, curRecord->formID);
                return 0;
                }

            cell_record->LAND = NULL;
            deindexer.Accept(curRecord);
            WRLD.land_pool.destroy(curRecord);
            }
            return 1;
        case REV32(ROAD):
            {
            Ob::WRLDRecord *wrld_record = (Ob::WRLDRecord *)curRecord->GetParentRecord();

            if(wrld_record->ROAD != curRecord)
                {
                printer("TES4File::DeleteRecord: Error - Unable to delete record type (%s) with parent type (%s) in mod \"%s\". The parent record (%08X) does not contain the record to be deleted (%08X).\n", curRecord->GetStrType(), curRecord->GetParentRecord()->GetStrType(), ModName, curRecord->GetParentRecord()->formID, curRecord->formID);
                return 0;
                }

            wrld_record->ROAD = NULL;
            deindexer.Accept(curRecord);
            WRLD.road_pool.destroy(curRecord);
            }
            return 1;
        case REV32(DIAL):
            {
            Ob::DIALRecord *dial_record = (Ob::DIALRecord *)curRecord;
            for(uint32_t ListIndex = 0; ListIndex < dial_record->INFO.size(); ++ListIndex)
                {
                deindexer.Accept(dial_record->INFO[ListIndex]);
                DIAL.info_pool.destroy(dial_record->INFO[ListIndex]);
                }

            deindexer.Accept(curRecord);
            DIAL.dial_pool.destroy(curRecord);
            }
            return 1;
        case REV32(INFO):
            {
            Ob::DIALRecord *dial_record = (Ob::DIALRecord *)curRecord->GetParentRecord();
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
                printer("TES4File::DeleteRecord: Error - Unable to delete record type (%s) with parent type (%s) in mod \"%s\". The parent record (%08X) does not contain the record to be deleted (%08X).\n", curRecord->GetStrType(), curRecord->GetParentRecord()->GetStrType(), ModName, curRecord->GetParentRecord()->formID, curRecord->formID);
                return 0;
                }

            deindexer.Accept(curRecord);
            DIAL.info_pool.destroy(curRecord);
            }
            return 1;
        case REV32(QUST):
            deindexer.Accept(curRecord);
            QUST.pool.destroy(curRecord);
            return 1;
        case REV32(IDLE):
            deindexer.Accept(curRecord);
            IDLE.pool.destroy(curRecord);
            return 1;
        case REV32(PACK):
            deindexer.Accept(curRecord);
            PACK.pool.destroy(curRecord);
            return 1;
        case REV32(CSTY):
            deindexer.Accept(curRecord);
            CSTY.pool.destroy(curRecord);
            return 1;
        case REV32(LSCR):
            deindexer.Accept(curRecord);
            LSCR.pool.destroy(curRecord);
            return 1;
        case REV32(LVSP):
            deindexer.Accept(curRecord);
            LVSP.pool.destroy(curRecord);
            return 1;
        case REV32(ANIO):
            deindexer.Accept(curRecord);
            ANIO.pool.destroy(curRecord);
            return 1;
        case REV32(WATR):
            deindexer.Accept(curRecord);
            WATR.pool.destroy(curRecord);
            return 1;
        case REV32(EFSH):
            deindexer.Accept(curRecord);
            EFSH.pool.destroy(curRecord);
            return 1;
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
        }
    return 0;
    }

int32_t TES4File::Save(char * const &SaveName, std::vector<FormIDResolver *> &Expanders, bool CloseMod, RecordOp &indexer)
    {
    if(!Flags.IsSaveable)
        {
        printer("TES4File::Save: Error - Unable to save mod \"%s\". It is flagged as being non-saveable.\n", ModName);
        return -1;
        }

    FileWriter writer(SaveName, BUFFERSIZE);
    if(writer.open() == -1)
        throw std::exception("TES4File::Save: Error - Unable to open temporary file for writing\n");

    uint32_t formCount = 0;
    FormIDResolver expander(FormIDHandler.ExpandTable, FormIDHandler.FileStart, FormIDHandler.FileEnd);
    FormIDResolver collapser(FormIDHandler.CollapseTable, FormIDHandler.FileStart, FormIDHandler.FileEnd);
    //RecordReader reader(FormIDHandler);
    const bool bMastersChanged = FormIDHandler.MastersChanged();

    TES4.Write(writer, bMastersChanged, expander, collapser, Expanders);

    //ADD DEFINITIONS HERE
    formCount += GMST.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += GLOB.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += CLAS.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += FACT.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += HAIR.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += EYES.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += RACE.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += SOUN.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += SKIL.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += MGEF.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += SCPT.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += LTEX.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += ENCH.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += SPEL.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += BSGN.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += ACTI.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += APPA.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += ARMO.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += BOOK.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += CLOT.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += CONT.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += DOOR.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += INGR.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += LIGH.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += MISC.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += STAT.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += GRAS.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += TREE.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += FLOR.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += FURN.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += WEAP.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += AMMO.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += NPC_.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += CREA.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += LVLC.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += SLGM.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += KEYM.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += ALCH.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += SBSP.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += SGST.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += LVLI.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += WTHR.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += CLMT.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += REGN.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += CELL.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += WRLD.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod, FormIDHandler, CELL, indexer);
    formCount += DIAL.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += QUST.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += IDLE.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += PACK.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += CSTY.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += LSCR.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += LVSP.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += ANIO.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += WATR.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += EFSH.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);

    //update formCount. Cheaper to go back and write it at the end than to calculate it before any writing.
    writer.file_write(30, &formCount, 4);
    writer.close();

    return 0;
    }

void TES4File::VisitAllRecords(RecordOp &op)
    {
    //if(Flags.IsNoLoad)
    //    {
    //    printer("TES4File::VisitAllRecords: Error - Unable to visit records in mod \"%s\". The mod is flagged not to be loaded.\n", ModName);
    //    return;
    //    }

    //This visits every record and subrecord
    {
    Record *temp = &TES4;
    op.Accept(temp);
    }
    GMST.pool.VisitRecords(op);
    GLOB.pool.VisitRecords(op);
    CLAS.pool.VisitRecords(op);
    FACT.pool.VisitRecords(op);
    HAIR.pool.VisitRecords(op);
    EYES.pool.VisitRecords(op);
    RACE.pool.VisitRecords(op);
    SOUN.pool.VisitRecords(op);
    SKIL.pool.VisitRecords(op);
    MGEF.pool.VisitRecords(op);
    SCPT.pool.VisitRecords(op);
    LTEX.pool.VisitRecords(op);
    ENCH.pool.VisitRecords(op);
    SPEL.pool.VisitRecords(op);
    BSGN.pool.VisitRecords(op);
    ACTI.pool.VisitRecords(op);
    APPA.pool.VisitRecords(op);
    ARMO.pool.VisitRecords(op);
    BOOK.pool.VisitRecords(op);
    CLOT.pool.VisitRecords(op);
    CONT.pool.VisitRecords(op);
    DOOR.pool.VisitRecords(op);
    INGR.pool.VisitRecords(op);
    LIGH.pool.VisitRecords(op);
    MISC.pool.VisitRecords(op);
    STAT.pool.VisitRecords(op);
    GRAS.pool.VisitRecords(op);
    TREE.pool.VisitRecords(op);
    FLOR.pool.VisitRecords(op);
    FURN.pool.VisitRecords(op);
    WEAP.pool.VisitRecords(op);
    AMMO.pool.VisitRecords(op);
    NPC_.pool.VisitRecords(op);
    CREA.pool.VisitRecords(op);
    LVLC.pool.VisitRecords(op);
    SLGM.pool.VisitRecords(op);
    KEYM.pool.VisitRecords(op);
    ALCH.pool.VisitRecords(op);
    SBSP.pool.VisitRecords(op);
    SGST.pool.VisitRecords(op);
    LVLI.pool.VisitRecords(op);
    WTHR.pool.VisitRecords(op);
    CLMT.pool.VisitRecords(op);
    REGN.pool.VisitRecords(op);
    //Child records need to be visited prior to the parent in order for identical to master cleaning to work nicely
    CELL.achr_pool.VisitRecords(op);
    CELL.acre_pool.VisitRecords(op);
    CELL.refr_pool.VisitRecords(op);
    CELL.pgrd_pool.VisitRecords(op);
    WRLD.land_pool.VisitRecords(op);
    WRLD.road_pool.VisitRecords(op);
    DIAL.info_pool.VisitRecords(op);

    WRLD.cell_pool.VisitRecords(op);
    CELL.cell_pool.VisitRecords(op);
    DIAL.dial_pool.VisitRecords(op);
    WRLD.wrld_pool.VisitRecords(op);

    QUST.pool.VisitRecords(op);
    IDLE.pool.VisitRecords(op);
    PACK.pool.VisitRecords(op);
    CSTY.pool.VisitRecords(op);
    LSCR.pool.VisitRecords(op);
    LVSP.pool.VisitRecords(op);
    ANIO.pool.VisitRecords(op);
    WATR.pool.VisitRecords(op);
    EFSH.pool.VisitRecords(op);
    return;
    }

void TES4File::VisitRecords(const uint32_t &RecordType, RecordOp &op)
    {
    //if(Flags.IsNoLoad)
    //    {
    //    printer("TES4File::VisitRecords: Error - Unable to visit records in mod \"%s\". The mod is flagged not to be loaded.\n", ModName);
    //    return;
    //    }

    switch(RecordType)
        {
        case REV32(TES4):
            {
            Record *temp = &TES4;
            op.Accept(temp);
            }
            break;
        case REV32(GMST):
            GMST.pool.VisitRecords(op);
            break;
        case REV32(GLOB):
            GLOB.pool.VisitRecords(op);
            break;
        case REV32(CLAS):
            CLAS.pool.VisitRecords(op);
            break;
        case REV32(FACT):
            FACT.pool.VisitRecords(op);
            break;
        case REV32(HAIR):
            HAIR.pool.VisitRecords(op);
            break;
        case REV32(EYES):
            EYES.pool.VisitRecords(op);
            break;
        case REV32(RACE):
            RACE.pool.VisitRecords(op);
            break;
        case REV32(SOUN):
            SOUN.pool.VisitRecords(op);
            break;
        case REV32(SKIL):
            SKIL.pool.VisitRecords(op);
            break;
        case REV32(MGEF):
            MGEF.pool.VisitRecords(op);
            break;
        case REV32(SCPT):
            SCPT.pool.VisitRecords(op);
            break;
        case REV32(LTEX):
            LTEX.pool.VisitRecords(op);
            break;
        case REV32(ENCH):
            ENCH.pool.VisitRecords(op);
            break;
        case REV32(SPEL):
            SPEL.pool.VisitRecords(op);
            break;
        case REV32(BSGN):
            BSGN.pool.VisitRecords(op);
            break;
        case REV32(ACTI):
            ACTI.pool.VisitRecords(op);
            break;
        case REV32(APPA):
            APPA.pool.VisitRecords(op);
            break;
        case REV32(ARMO):
            ARMO.pool.VisitRecords(op);
            break;
        case REV32(BOOK):
            BOOK.pool.VisitRecords(op);
            break;
        case REV32(CLOT):
            CLOT.pool.VisitRecords(op);
            break;
        case REV32(CONT):
            CONT.pool.VisitRecords(op);
            break;
        case REV32(DOOR):
            DOOR.pool.VisitRecords(op);
            break;
        case REV32(INGR):
            INGR.pool.VisitRecords(op);
            break;
        case REV32(LIGH):
            LIGH.pool.VisitRecords(op);
            break;
        case REV32(MISC):
            MISC.pool.VisitRecords(op);
            break;
        case REV32(STAT):
            STAT.pool.VisitRecords(op);
            break;
        case REV32(GRAS):
            GRAS.pool.VisitRecords(op);
            break;
        case REV32(TREE):
            TREE.pool.VisitRecords(op);
            break;
        case REV32(FLOR):
            FLOR.pool.VisitRecords(op);
            break;
        case REV32(FURN):
            FURN.pool.VisitRecords(op);
            break;
        case REV32(WEAP):
            WEAP.pool.VisitRecords(op);
            break;
        case REV32(AMMO):
            AMMO.pool.VisitRecords(op);
            break;
        case REV32(NPC_):
            NPC_.pool.VisitRecords(op);
            break;
        case REV32(CREA):
            CREA.pool.VisitRecords(op);
            break;
        case REV32(LVLC):
            LVLC.pool.VisitRecords(op);
            break;
        case REV32(SLGM):
            SLGM.pool.VisitRecords(op);
            break;
        case REV32(KEYM):
            KEYM.pool.VisitRecords(op);
            break;
        case REV32(ALCH):
            ALCH.pool.VisitRecords(op);
            break;
        case REV32(SBSP):
            SBSP.pool.VisitRecords(op);
            break;
        case REV32(SGST):
            SGST.pool.VisitRecords(op);
            break;
        case REV32(LVLI):
            LVLI.pool.VisitRecords(op);
            break;
        case REV32(WTHR):
            WTHR.pool.VisitRecords(op);
            break;
        case REV32(CLMT):
            CLMT.pool.VisitRecords(op);
            break;
        case REV32(REGN):
            REGN.pool.VisitRecords(op);
            break;
        case REV32(CELL):
            CELL.cell_pool.VisitRecords(op);
            break;
        case REV32(ACHR):
            CELL.achr_pool.VisitRecords(op);
            break;
        case REV32(ACRE):
            CELL.acre_pool.VisitRecords(op);
            break;
        case REV32(REFR):
            CELL.refr_pool.VisitRecords(op);
            break;
        case REV32(PGRD):
            CELL.pgrd_pool.VisitRecords(op);
            break;
        case REV32(WRLD):
            WRLD.wrld_pool.VisitRecords(op);
            break;
        case REV32(LAND):
            WRLD.land_pool.VisitRecords(op);
            break;
        case REV32(ROAD):
            WRLD.road_pool.VisitRecords(op);
            break;
        case REV32(WCEL):
            WRLD.cell_pool.VisitRecords(op);
            break;
        case REV32(CLLS):
            CELL.cell_pool.VisitRecords(op);
            WRLD.cell_pool.VisitRecords(op);
            break;
        case REV32(DIAL):
            DIAL.dial_pool.VisitRecords(op);
            break;
        case REV32(INFO):
            DIAL.info_pool.VisitRecords(op);
            break;
        case REV32(QUST):
            QUST.pool.VisitRecords(op);
            break;
        case REV32(IDLE):
            IDLE.pool.VisitRecords(op);
            break;
        case REV32(PACK):
            PACK.pool.VisitRecords(op);
            break;
        case REV32(CSTY):
            CSTY.pool.VisitRecords(op);
            break;
        case REV32(LSCR):
            LSCR.pool.VisitRecords(op);
            break;
        case REV32(LVSP):
            LVSP.pool.VisitRecords(op);
            break;
        case REV32(ANIO):
            ANIO.pool.VisitRecords(op);
            break;
        case REV32(WATR):
            WATR.pool.VisitRecords(op);
            break;
        case REV32(EFSH):
            EFSH.pool.VisitRecords(op);
            break;
        default:
            printer("TES4File::VisitRecords: Error - Unable to visit record type (%c%c%c%c) in mod \"%s\". Unknown record type.\n", ((char *)&RecordType)[0], ((char *)&RecordType)[1], ((char *)&RecordType)[2], ((char *)&RecordType)[3], ModName);
            break;
        }
    return;
    }