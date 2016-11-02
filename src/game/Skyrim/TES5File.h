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
#pragma once
// TES5File.h
#include "../Common.h"
#include "../ModFile.h"
#include "../GenericRecord.h"
#include "../GRUPRecord.h"

// Only need to include Top Types
#include "Records/AACTRecord.h"
#include "Records/ACTIRecord.h"
#include "Records/ADDNRecord.h"
#include "Records/ALCHRecord.h"
// #include "Records/AMMORecord.h"
#include "Records/ANIORecord.h"
#include "Records/APPARecord.h"
// #include "Records/ARMARecord.h"
// #include "Records/ARMORecord.h"
#include "Records/ARTORecord.h"
#include "Records/ASPCRecord.h"
#include "Records/ASTPRecord.h"
// #include "Records/AVIFRecord.h"
// #include "Records/BOOKRecord.h"
// #include "Records/BPTDRecord.h"
// #include "Records/CAMSRecord.h"
#include "Records/CELLRecord.h"
// #include "Records/CLASRecord.h"
// #include "Records/CLDCRecord.h" // Empty GRUP
// #include "Records/CLFMRecord.h"
// #include "Records/CLMTRecord.h"
// #include "Records/COBJRecord.h"
#include "Records/COLLRecord.h"
// #include "Records/CONTRecord.h"
// #include "Records/CPTHRecord.h"
// #include "Records/CSTYRecord.h"
// #include "Records/DEBRRecord.h"
// #include "Records/DIALRecord.h"
// #include "Records/DLBRRecord.h"
// #include "Records/DLVWRecord.h"
// #include "Records/DOBJRecord.h"
// #include "Records/DOORRecord.h"
// #include "Records/DUALRecord.h"
// #include "Records/ECZNRecord.h"
// #include "Records/EFSHRecord.h"
// #include "Records/ENCHRecord.h"
#include "Records/EQUPRecord.h"
// #include "Records/EXPLRecord.h"
// #include "Records/EYESRecord.h"
// #include "Records/FACTRecord.h"
// #include "Records/FLORRecord.h"
// #include "Records/FLSTRecord.h"
// #include "Records/FSTPRecord.h"
// #include "Records/FSTSRecord.h"
// #include "Records/FURNRecord.h"
// #include "Records/GLOBRecord.h"
// #include "Records/GMSTRecord.h"
// #include "Records/GRASRecord.h"
// #include "Records/HAIRRecord.h" // Empty GRUP
// #include "Records/HAZDRecord.h"
// #include "Records/HDPTRecord.h"
// #include "Records/IDLERecord.h"
// #include "Records/IDLMRecord.h"
// #include "Records/IMADRecord.h"
// #include "Records/IMGSRecord.h"
// #include "Records/INGRRecord.h"
// #include "Records/IPCTRecord.h"
// #include "Records/IPDSRecord.h"
// #include "Records/KEYMRecord.h"
#include "Records/KYWDRecord.h"
// #include "Records/LCRTRecord.h"
// #include "Records/LCTNRecord.h"
// #include "Records/LGTMRecord.h"
// #include "Records/LIGHRecord.h"
// #include "Records/LSCRRecord.h"
#include "Records/LTEXRecord.h"
#include "Records/LVLIRecord.h"
#include "Records/LVLNRecord.h"
#include "Records/LVSPRecord.h"
// #include "Records/MATORecord.h"
#include "Records/MATTRecord.h"
// #include "Records/MESGRecord.h"
// #include "Records/MGEFRecord.h"
// #include "Records/MISCRecord.h"
// #include "Records/MOVTRecord.h"
// #include "Records/MSTTRecord.h"
// #include "Records/MUSCRecord.h"
// #include "Records/MUSTRecord.h"
// #include "Records/NAVIRecord.h"
// #include "Records/NPC_Record.h"
#include "Records/OTFTRecord.h"
// #include "Records/PACKRecord.h"
// #include "Records/PERKRecord.h"
// #include "Records/PROJRecord.h"
// #include "Records/PWATRecord.h" // Empty GRUP
// #include "Records/QUSTRecord.h"
// #include "Records/RACERecord.h"
// #include "Records/REGNRecord.h"
// #include "Records/RELARecord.h"
// #include "Records/REVBRecord.h"
// #include "Records/RFCTRecord.h"
// #include "Records/RGDLRecord.h" // Empty GRUP
// #include "Records/SCENRecord.h"
// #include "Records/SCOLRecord.h" // Empty GRUP
// #include "Records/SCPTRecord.h"
// #include "Records/SCRLRecord.h"
#include "Records/SHOURecord.h"
// #include "Records/SLGMRecord.h"
// #include "Records/SMBNRecord.h"
// #include "Records/SMENRecord.h"
// #include "Records/SMQNRecord.h"
// #include "Records/SNCTRecord.h"
// #include "Records/SNDRRecord.h"
// #include "Records/SOPMRecord.h"
// #include "Records/SOUNRecord.h"
// #include "Records/SPELRecord.h"
// #include "Records/SPGDRecord.h"
// #include "Records/STATRecord.h"
// #include "Records/TACTRecord.h"
// #include "Records/TREERecord.h"
#include "Records/TXSTRecord.h"
#include "Records/VTYPRecord.h"
// #include "Records/WATRRecord.h"
// #include "Records/WEAPRecord.h"
#include "Records/WOOPRecord.h"
#include "Records/WRLDRecord.h"
// #include "Records/WTHRRecord.h"


// Helper macros
#define GRUP(Type) \
    TES5GRUPRecords<Sk::Type##Record, REV32(Type), 5> Type
#define GRUP_EDID(Type) \
    TES5GRUPRecords<Sk::Type##Record, REV32(Type), 5, true> Type


class TES5File : public ModFile
    {
    public:
        GRUP(AACT);
        GRUP(ACTI);
        GRUP(ADDN);
        GRUP(ALCH);
        // GRUP(AMMO);
        GRUP(ANIO);
        GRUP(APPA);
        // GRUP(ARMA);
        // GRUP(ARMO);
        GRUP(ARTO);
        GRUP(ASPC);
        GRUP(ASTP);
        // GRUP(AVIF);
        // GRUP(BOOK);
        // GRUP(BPTD);
        // GRUP(CAMS);
        GRUP(CELL);
        // GRUP(CLAS);
        // GRUP(CLDC); // Empty GRUP
        // GRUP(CLFM);
        // GRUP(CLMT);
        // GRUP(COBJ);
        GRUP(COLL);
        // GRUP(CONT);
        // GRUP(CPTH);
        // GRUP(CSTY);
        // GRUP(DEBR);
        // GRUP(DIAL);
        // GRUP(DLBR);
        // GRUP(DLVW);
        // GRUP(DOBJ);
        // GRUP(DOOR);
        // GRUP(DUAL);
        // GRUP(ECZN);
        // GRUP(EFSH);
        // GRUP(ENCH);
        GRUP(EQUP);
        // GRUP(EXPL);
        // GRUP(EYES);
        // GRUP(FACT);
        // GRUP(FLOR);
        // GRUP(FLST);
        // GRUP(FSTP);
        // GRUP(FSTS);
        // GRUP(FURN);
        // GRUP(GLOB);
        // GRUP_EDID(GMST);
        // GRUP(GRAS);
        // GRUP(HAIR); // Empty GRUP
        // GRUP(HAZD);
        // GRUP(HDPT);
        // GRUP(IDLE);
        // GRUP(IDLM);
        // GRUP(IMAD);
        // GRUP(IMGS);
        // GRUP(INGR);
        // GRUP(IPCT);
        // GRUP(IPDS);
        // GRUP(KEYM);
        GRUP(KYWD);
        // GRUP(LCRT);
        // GRUP(LCTN);
        // GRUP(LGTM);
        // GRUP(LIGH);
        // GRUP(LSCR);
        GRUP(LTEX);
        GRUP(LVLI);
        GRUP(LVLN);
        GRUP(LVSP);
        // GRUP(MATO);
        GRUP(MATT);
        // GRUP(MESG);
        // GRUP(MGEF);
        // GRUP(MISC);
        // GRUP(MOVT);
        // GRUP(MSTT);
        // GRUP(MUSC);
        // GRUP(MUST);
        // GRUP(NAVI);
        // GRUP(NPC_);
        GRUP(OTFT);
        // GRUP(PACK);
        // GRUP(PERK);
        // GRUP(PROJ);
        // GRUP(PWAT); // Empty GRUP
        // GRUP(QUST);
        // GRUP(RACE);
        // GRUP(REGN);
        // GRUP(RELA);
        // GRUP(REVB);
        // GRUP(RFCT);
        // GRUP(RGDL); // Empty GRUP
        // GRUP(SCEN);
        // GRUP(SCOL); // Empty GRUP
        // GRUP(SCPT);
        // GRUP(SCRL);
        GRUP(SHOU);
        // GRUP(SLGM);
        // GRUP(SMBN);
        // GRUP(SMEN);
        // GRUP(SMQN);
        // GRUP(SNCT);
        // GRUP(SNDR);
        // GRUP(SOPM);
        // GRUP(SOUN);
        // GRUP(SPEL);
        // GRUP(SPGD);
        // GRUP(STAT);
        // GRUP(TACT);
        // GRUP(TREE);
        GRUP(TXST);
        GRUP(VTYP);
        // GRUP(WATR);
        // GRUP(WEAP);
        GRUP(WOOP);
        GRUP(WRLD);
        // GRUP(WTHR);

        TES5File(Collection *_Parent, char * FileName, char * ModName, const uint32_t _flags);
        ~TES5File();

        Record * GetTES4();
        int32_t   LoadTES4();
        int32_t   Load(RecordOp &read_parser, RecordOp &indexer, std::vector<FormIDResolver *> &Expanders, std::vector<Record *> &DeletedRecords);
        uint32_t   GetNumRecords(const uint32_t &RecordType);
        char *   GetMasterName(uint8_t &CollapsedIndex);
        Record * CreateRecord(const uint32_t &RecordType, char * const &RecordEditorID, Record *&SourceRecord, Record *&ParentRecord, CreationFlags &options);
        int32_t   DeleteRecord(Record *&curRecord, RecordOp &deindexer);
        int32_t   Save(char * const &SaveName, std::vector<FormIDResolver *> &Expanders, bool CloseMod, RecordOp &indexer);

        void     SetFilter(bool inclusive, boost::unordered_set<uint32_t> &RecordTypes, boost::unordered_set<FORMID> &WorldSpaces);

        void     VisitAllRecords(RecordOp &op);
        void     VisitRecords(const uint32_t &RecordType, RecordOp &op);
    };

// Clean up
#undef GRUP
#undef GRUP_EDID
