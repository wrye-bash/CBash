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
// FNVFile.h
#include "common/Common.h"
#include "common/ModFile.h"
#include "common/GenericRecord.h"

#include "GRUPRecord.h"

#include "Records/GMSTRecord.h"
#include "Records/TXSTRecord.h"
#include "Records/MICNRecord.h"
#include "Records/GLOBRecord.h"
#include "Records/CLASRecord.h"
#include "Records/FACTRecord.h"
#include "Records/HDPTRecord.h"
#include "Records/HAIRRecord.h"
#include "Records/EYESRecord.h"
#include "Records/RACERecord.h"
#include "Records/SOUNRecord.h"
#include "Records/ASPCRecord.h"
#include "Records/MGEFRecord.h"
#include "Records/SCPTRecord.h"
#include "Records/LTEXRecord.h"
#include "Records/ENCHRecord.h"
#include "Records/SPELRecord.h"
#include "Records/ACTIRecord.h"
#include "Records/TACTRecord.h"
#include "Records/TERMRecord.h"
#include "Records/ARMORecord.h"
#include "Records/BOOKRecord.h"
#include "Records/CONTRecord.h"
#include "Records/DOORRecord.h"
#include "Records/INGRRecord.h"
#include "Records/LIGHRecord.h"
#include "Records/MISCRecord.h"
#include "Records/STATRecord.h"
#include "Records/SCOLRecord.h"
#include "Records/MSTTRecord.h"
#include "Records/PWATRecord.h"
#include "Records/GRASRecord.h"
#include "Records/TREERecord.h"
#include "Records/FURNRecord.h"
#include "Records/WEAPRecord.h"
#include "Records/AMMORecord.h"
#include "Records/NPC_Record.h"
#include "Records/CREARecord.h"
#include "Records/LVLCRecord.h"
#include "Records/LVLNRecord.h"
#include "Records/KEYMRecord.h"
#include "Records/ALCHRecord.h"
#include "Records/IDLMRecord.h"
#include "Records/NOTERecord.h"
#include "Records/COBJRecord.h"
#include "Records/PROJRecord.h"
#include "Records/LVLIRecord.h"
#include "Records/WTHRRecord.h"
#include "Records/CLMTRecord.h"
#include "Records/REGNRecord.h"
#include "Records/NAVIRecord.h"
#include "Records/CELLRecord.h"
#include "Records/WRLDRecord.h"
#include "Records/DIALRecord.h"
#include "Records/QUSTRecord.h"
#include "Records/IDLERecord.h"
#include "Records/PACKRecord.h"
#include "Records/CSTYRecord.h"
#include "Records/LSCRRecord.h"
#include "Records/ANIORecord.h"
#include "Records/WATRRecord.h"
#include "Records/EFSHRecord.h"
#include "Records/EXPLRecord.h"
#include "Records/DEBRRecord.h"
////#include "Records/IMGSRecord.h"
////#include "Records/IMADRecord.h"
////#include "Records/FLSTRecord.h"
////#include "Records/PERKRecord.h"
////#include "Records/BPTDRecord.h"
//#include "Records/ADDNRecord.h"
//#include "Records/AVIFRecord.h"
//#include "Records/RADSRecord.h"
//#include "Records/CAMSRecord.h"
//#include "Records/CPTHRecord.h"
//#include "Records/VTYPRecord.h"
//#include "Records/IPCTRecord.h"
//#include "Records/IPDSRecord.h"
//#include "Records/ARMARecord.h"
//#include "Records/ECZNRecord.h"
//#include "Records/MESGRecord.h"
//#include "Records/RGDLRecord.h"
//#include "Records/DOBJRecord.h"
//#include "Records/LGTMRecord.h"
//#include "Records/MUSCRecord.h"
//#include "Records/IMODRecord.h"
//#include "Records/REPURecord.h"
//#include "Records/RCPERecord.h"
//#include "Records/RCCTRecord.h"
//#include "Records/CHIPRecord.h"
//#include "Records/CSNORecord.h"
//#include "Records/LSCTRecord.h"
//#include "Records/MSETRecord.h"
//#include "Records/ALOCRecord.h"
//#include "Records/CHALRecord.h"
//#include "Records/AMEFRecord.h"
//#include "Records/CCRDRecord.h"
//#include "Records/CMNYRecord.h"
//#include "Records/CDCKRecord.h"
//#include "Records/DEHYRecord.h"
//#include "Records/HUNGRecord.h"
//#include "Records/SLPDRecord.h"

class FNVFile : public ModFile
    {
    public:
        FNVGRUPRecords<FNV::GMSTRecord, REV32(GMST), 5, true> GMST;
        FNVGRUPRecords<FNV::TXSTRecord, REV32(TXST), 5> TXST;
        FNVGRUPRecords<FNV::MICNRecord, REV32(MICN), 5> MICN;
        FNVGRUPRecords<FNV::GLOBRecord, REV32(GLOB), 5> GLOB;
        FNVGRUPRecords<FNV::CLASRecord, REV32(CLAS), 5> CLAS;
        FNVGRUPRecords<FNV::FACTRecord, REV32(FACT), 5> FACT;
        FNVGRUPRecords<FNV::HDPTRecord, REV32(HDPT), 5> HDPT;
        FNVGRUPRecords<FNV::HAIRRecord, REV32(HAIR), 5> HAIR;
        FNVGRUPRecords<FNV::EYESRecord, REV32(EYES), 5> EYES;
        FNVGRUPRecords<FNV::RACERecord, REV32(RACE), 5> RACE;
        FNVGRUPRecords<FNV::SOUNRecord, REV32(SOUN), 5> SOUN;
        FNVGRUPRecords<FNV::ASPCRecord, REV32(ASPC), 5> ASPC;
        FNVGRUPRecords<FNV::MGEFRecord, REV32(MGEF), 5> MGEF;
        FNVGRUPRecords<FNV::SCPTRecord, REV32(SCPT), 5> SCPT;
        FNVGRUPRecords<FNV::LTEXRecord, REV32(LTEX), 5> LTEX;
        FNVGRUPRecords<FNV::ENCHRecord, REV32(ENCH), 5> ENCH;
        FNVGRUPRecords<FNV::SPELRecord, REV32(SPEL), 5> SPEL;
        FNVGRUPRecords<FNV::ACTIRecord, REV32(ACTI), 5> ACTI;
        FNVGRUPRecords<FNV::TACTRecord, REV32(TACT), 5> TACT;
        FNVGRUPRecords<FNV::TERMRecord, REV32(TERM), 5> TERM;
        FNVGRUPRecords<FNV::ARMORecord, REV32(ARMO), 5> ARMO;
        FNVGRUPRecords<FNV::BOOKRecord, REV32(BOOK), 5> BOOK;
        FNVGRUPRecords<FNV::CONTRecord, REV32(CONT), 5> CONT;
        FNVGRUPRecords<FNV::DOORRecord, REV32(DOOR), 5> DOOR;
        FNVGRUPRecords<FNV::INGRRecord, REV32(INGR), 5> INGR;
        FNVGRUPRecords<FNV::LIGHRecord, REV32(LIGH), 5> LIGH;
        FNVGRUPRecords<FNV::MISCRecord, REV32(MISC), 5> MISC;
        FNVGRUPRecords<FNV::STATRecord, REV32(STAT), 5> STAT;
        FNVGRUPRecords<FNV::SCOLRecord, REV32(SCOL), 5> SCOL;
        FNVGRUPRecords<FNV::MSTTRecord, REV32(MSTT), 5> MSTT;
        FNVGRUPRecords<FNV::PWATRecord, REV32(PWAT), 5> PWAT;
        FNVGRUPRecords<FNV::GRASRecord, REV32(GRAS), 5> GRAS;
        FNVGRUPRecords<FNV::TREERecord, REV32(TREE), 5> TREE;
        FNVGRUPRecords<FNV::FURNRecord, REV32(FURN), 5> FURN;
        FNVGRUPRecords<FNV::WEAPRecord, REV32(WEAP), 5> WEAP;
        FNVGRUPRecords<FNV::AMMORecord, REV32(AMMO), 5> AMMO;
        FNVGRUPRecords<FNV::NPC_Record, REV32(NPC_), 5> NPC_;
        FNVGRUPRecords<FNV::CREARecord, REV32(CREA), 5> CREA;
        FNVGRUPRecords<FNV::LVLCRecord, REV32(LVLC), 5> LVLC;
        FNVGRUPRecords<FNV::LVLNRecord, REV32(LVLN), 5> LVLN;
        FNVGRUPRecords<FNV::KEYMRecord, REV32(KEYM), 5> KEYM;
        FNVGRUPRecords<FNV::ALCHRecord, REV32(ALCH), 5> ALCH;
        FNVGRUPRecords<FNV::IDLMRecord, REV32(IDLM), 5> IDLM;
        FNVGRUPRecords<FNV::NOTERecord, REV32(NOTE), 5> NOTE;
        FNVGRUPRecords<FNV::COBJRecord, REV32(COBJ), 5> COBJ;
        FNVGRUPRecords<FNV::PROJRecord, REV32(PROJ), 5> PROJ;
        FNVGRUPRecords<FNV::LVLIRecord, REV32(LVLI), 5> LVLI;
        FNVGRUPRecords<FNV::WTHRRecord, REV32(WTHR), 5> WTHR;
        FNVGRUPRecords<FNV::CLMTRecord, REV32(CLMT), 5> CLMT;
        FNVGRUPRecords<FNV::REGNRecord, REV32(REGN), 5> REGN;
        FNVGRUPRecords<FNV::NAVIRecord, REV32(NAVI), 5> NAVI;
        FNVGRUPRecords<FNV::CELLRecord, REV32(CELL), 5> CELL;
        FNVGRUPRecords<FNV::WRLDRecord, REV32(WRLD), 5> WRLD;
        FNVGRUPRecords<FNV::DIALRecord, REV32(DIAL), 5> DIAL;
        FNVGRUPRecords<FNV::QUSTRecord, REV32(QUST), 5> QUST;
        FNVGRUPRecords<FNV::IDLERecord, REV32(IDLE), 5> IDLE;
        FNVGRUPRecords<FNV::PACKRecord, REV32(PACK), 5> PACK;
        FNVGRUPRecords<FNV::CSTYRecord, REV32(CSTY), 5> CSTY;
        FNVGRUPRecords<FNV::LSCRRecord, REV32(LSCR), 5> LSCR;
        FNVGRUPRecords<FNV::ANIORecord, REV32(ANIO), 5> ANIO;
        FNVGRUPRecords<FNV::WATRRecord, REV32(WATR), 5> WATR;
        FNVGRUPRecords<FNV::EFSHRecord, REV32(EFSH), 5> EFSH;
        FNVGRUPRecords<FNV::EXPLRecord, REV32(EXPL), 5> EXPL;
        FNVGRUPRecords<FNV::DEBRRecord, REV32(DEBR), 5> DEBR;
        ////FNVGRUPRecords<FNV::IMGSRecord, REV32(IMGS), 5> IMGS;
        ////FNVGRUPRecords<FNV::IMADRecord, REV32(IMAD), 5> IMAD;
        ////FNVGRUPRecords<FNV::FLSTRecord, REV32(FLST), 5> FLST;
        ////FNVGRUPRecords<FNV::PERKRecord, REV32(PERK), 5> PERK;
        ////FNVGRUPRecords<FNV::BPTDRecord, REV32(BPTD), 5> BPTD;
        //FNVGRUPRecords<FNV::ADDNRecord, REV32(ADDN), 5> ADDN;
        //FNVGRUPRecords<FNV::AVIFRecord, REV32(AVIF), 5> AVIF;
        //FNVGRUPRecords<FNV::RADSRecord, REV32(RADS), 5> RADS;
        //FNVGRUPRecords<FNV::CAMSRecord, REV32(CAMS), 5> CAMS;
        //FNVGRUPRecords<FNV::CPTHRecord, REV32(CPTH), 5> CPTH;
        //FNVGRUPRecords<FNV::VTYPRecord, REV32(VTYP), 5> VTYP;
        //FNVGRUPRecords<FNV::IPCTRecord, REV32(IPCT), 5> IPCT;
        //FNVGRUPRecords<FNV::IPDSRecord, REV32(IPDS), 5> IPDS;
        //FNVGRUPRecords<FNV::ARMARecord, REV32(ARMA), 5> ARMA;
        //FNVGRUPRecords<FNV::ECZNRecord, REV32(ECZN), 5> ECZN;
        //FNVGRUPRecords<FNV::MESGRecord, REV32(MESG), 5> MESG;
        //FNVGRUPRecords<FNV::RGDLRecord, REV32(RGDL), 5> RGDL;
        //FNVGRUPRecords<FNV::DOBJRecord, REV32(DOBJ), 5> DOBJ;
        //FNVGRUPRecords<FNV::LGTMRecord, REV32(LGTM), 5> LGTM;
        //FNVGRUPRecords<FNV::MUSCRecord, REV32(MUSC), 5> MUSC;
        //FNVGRUPRecords<FNV::IMODRecord, REV32(IMOD), 5> IMOD;
        //FNVGRUPRecords<FNV::REPURecord, REV32(REPU), 5> REPU;
        //FNVGRUPRecords<FNV::RCPERecord, REV32(RCPE), 5> RCPE;
        //FNVGRUPRecords<FNV::RCCTRecord, REV32(RCCT), 5> RCCT;
        //FNVGRUPRecords<FNV::CHIPRecord, REV32(CHIP), 5> CHIP;
        //FNVGRUPRecords<FNV::CSNORecord, REV32(CSNO), 5> CSNO;
        //FNVGRUPRecords<FNV::LSCTRecord, REV32(LSCT), 5> LSCT;
        //FNVGRUPRecords<FNV::MSETRecord, REV32(MSET), 5> MSET;
        //FNVGRUPRecords<FNV::ALOCRecord, REV32(ALOC), 5> ALOC;
        //FNVGRUPRecords<FNV::CHALRecord, REV32(CHAL), 5> CHAL;
        //FNVGRUPRecords<FNV::AMEFRecord, REV32(AMEF), 5> AMEF;
        //FNVGRUPRecords<FNV::CCRDRecord, REV32(CCRD), 5> CCRD;
        //FNVGRUPRecords<FNV::CMNYRecord, REV32(CMNY), 5> CMNY;
        //FNVGRUPRecords<FNV::CDCKRecord, REV32(CDCK), 5> CDCK;
        //FNVGRUPRecords<FNV::DEHYRecord, REV32(DEHY), 5> DEHY;
        //FNVGRUPRecords<FNV::HUNGRecord, REV32(HUNG), 5> HUNG;
        //FNVGRUPRecords<FNV::SLPDRecord, REV32(SLPD), 5> SLPD;

        FNVFile(Collection *_Parent, char * FileName, char * ModName, const uint32_t _flags);
        ~FNVFile();

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