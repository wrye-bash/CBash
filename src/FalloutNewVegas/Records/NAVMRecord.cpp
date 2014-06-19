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
#include "..\..\Common.h"
#include "NAVMRecord.h"
#include "CELLRecord.h"

namespace FNV
{
NAVMRecord::NAVMDATA::NAVMDATA():
    cell(0),
    numVertices(0),
    numTriangles(0),
    numConnections(0),
    numNVCA(0),
    numDoors(0)
    {
    //
    }

NAVMRecord::NAVMDATA::~NAVMDATA()
    {
    //
    }

bool NAVMRecord::NAVMDATA::operator ==(const NAVMDATA &other) const
    {
    return (cell == other.cell &&
            numVertices == other.numVertices &&
            numTriangles == other.numTriangles &&
            numConnections == other.numConnections &&
            numNVCA == other.numNVCA &&
            numDoors == other.numDoors);
    }

bool NAVMRecord::NAVMDATA::operator !=(const NAVMDATA &other) const
    {
    return !(*this == other);
    }

NAVMRecord::NAVMVertex::NAVMVertex():
    x(0.0f),
    y(0.0f),
    z(0.0f)
    {
    //
    }

NAVMRecord::NAVMVertex::~NAVMVertex()
    {
    //
    }

bool NAVMRecord::NAVMVertex::operator ==(const NAVMVertex &other) const
    {
    return (AlmostEqual(x,other.x,2) &&
            AlmostEqual(y,other.y,2) &&
            AlmostEqual(z,other.z,2));
    }

bool NAVMRecord::NAVMVertex::operator !=(const NAVMVertex &other) const
    {
    return !(*this == other);
    }

NAVMRecord::NAVMNVTR::NAVMNVTR():
    vertex1(0),
    vertex2(0),
    vertex3(0),
    edge1(0),
    edge2(0),
    edge3(0),
    flags(0)
    {
    //
    }

NAVMRecord::NAVMNVTR::~NAVMNVTR()
    {
    //
    }

bool NAVMRecord::NAVMNVTR::IsTriangle0External()
    {
    return (flags & fIsTriangle0External) != 0;
    }

void NAVMRecord::NAVMNVTR::IsTriangle0External(bool value)
    {
    SETBIT(flags, fIsTriangle0External, value);
    }

bool NAVMRecord::NAVMNVTR::IsTriangle1External()
    {
    return (flags & fIsTriangle1External) != 0;
    }

void NAVMRecord::NAVMNVTR::IsTriangle1External(bool value)
    {
    SETBIT(flags, fIsTriangle1External, value);
    }

bool NAVMRecord::NAVMNVTR::IsTriangle2External()
    {
    return (flags & fIsTriangle2External) != 0;
    }

void NAVMRecord::NAVMNVTR::IsTriangle2External(bool value)
    {
    SETBIT(flags, fIsTriangle2External, value);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown4()
    {
    return (flags & fIsUnknown4) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown4(bool value)
    {
    SETBIT(flags, fIsUnknown4, value);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown5()
    {
    return (flags & fIsUnknown5) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown5(bool value)
    {
    SETBIT(flags, fIsUnknown5, value);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown6()
    {
    return (flags & fIsUnknown6) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown6(bool value)
    {
    SETBIT(flags, fIsUnknown6, value);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown7()
    {
    return (flags & fIsUnknown7) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown7(bool value)
    {
    SETBIT(flags, fIsUnknown7, value);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown8()
    {
    return (flags & fIsUnknown8) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown8(bool value)
    {
    SETBIT(flags, fIsUnknown8, value);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown9()
    {
    return (flags & fIsUnknown9) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown9(bool value)
    {
    SETBIT(flags, fIsUnknown9, value);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown10()
    {
    return (flags & fIsUnknown10) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown10(bool value)
    {
    SETBIT(flags, fIsUnknown10, value);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown11()
    {
    return (flags & fIsUnknown11) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown11(bool value)
    {
    SETBIT(flags, fIsUnknown11, value);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown12()
    {
    return (flags & fIsUnknown12) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown12(bool value)
    {
    SETBIT(flags, fIsUnknown12, value);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown13()
    {
    return (flags & fIsUnknown13) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown13(bool value)
    {
    SETBIT(flags, fIsUnknown13, value);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown14()
    {
    return (flags & fIsUnknown14) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown14(bool value)
    {
    SETBIT(flags, fIsUnknown14, value);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown15()
    {
    return (flags & fIsUnknown15) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown15(bool value)
    {
    SETBIT(flags, fIsUnknown15, value);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown16()
    {
    return (flags & fIsUnknown16) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown16(bool value)
    {
    SETBIT(flags, fIsUnknown16, value);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown17()
    {
    return (flags & fIsUnknown17) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown17(bool value)
    {
    SETBIT(flags, fIsUnknown17, value);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown18()
    {
    return (flags & fIsUnknown18) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown18(bool value)
    {
    SETBIT(flags, fIsUnknown18, value);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown19()
    {
    return (flags & fIsUnknown19) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown19(bool value)
    {
    SETBIT(flags, fIsUnknown19, value);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown20()
    {
    return (flags & fIsUnknown20) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown20(bool value)
    {
    SETBIT(flags, fIsUnknown20, value);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown21()
    {
    return (flags & fIsUnknown21) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown21(bool value)
    {
    SETBIT(flags, fIsUnknown21, value);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown22()
    {
    return (flags & fIsUnknown22) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown22(bool value)
    {
    SETBIT(flags, fIsUnknown22, value);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown23()
    {
    return (flags & fIsUnknown23) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown23(bool value)
    {
    SETBIT(flags, fIsUnknown23, value);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown24()
    {
    return (flags & fIsUnknown24) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown24(bool value)
    {
    SETBIT(flags, fIsUnknown24, value);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown25()
    {
    return (flags & fIsUnknown25) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown25(bool value)
    {
    SETBIT(flags, fIsUnknown25, value);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown26()
    {
    return (flags & fIsUnknown26) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown26(bool value)
    {
    SETBIT(flags, fIsUnknown26, value);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown27()
    {
    return (flags & fIsUnknown27) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown27(bool value)
    {
    SETBIT(flags, fIsUnknown27, value);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown28()
    {
    return (flags & fIsUnknown28) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown28(bool value)
    {
    SETBIT(flags, fIsUnknown28, value);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown29()
    {
    return (flags & fIsUnknown29) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown29(bool value)
    {
    SETBIT(flags, fIsUnknown29, value);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown30()
    {
    return (flags & fIsUnknown30) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown30(bool value)
    {
    SETBIT(flags, fIsUnknown30, value);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown31()
    {
    return (flags & fIsUnknown31) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown31(bool value)
    {
    SETBIT(flags, fIsUnknown31, value);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown32()
    {
    return (flags & fIsUnknown32) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown32(bool value)
    {
    SETBIT(flags, fIsUnknown32, value);
    }

bool NAVMRecord::NAVMNVTR::IsFlagMask(uint32_t Mask, bool Exact)
    {
    return Exact ? ((flags & Mask) == Mask) : ((flags & Mask) != 0);
    }

void NAVMRecord::NAVMNVTR::SetFlagMask(uint32_t Mask)
    {
    flags = Mask;
    }

bool NAVMRecord::NAVMNVTR::operator ==(const NAVMNVTR &other) const
    {
    return (vertex1 == other.vertex1 &&
            vertex2 == other.vertex2 &&
            vertex3 == other.vertex3 &&
            edge1 == other.edge1 &&
            edge2 == other.edge2 &&
            edge3 == other.edge3 &&
            flags == other.flags);
    }

bool NAVMRecord::NAVMNVTR::operator !=(const NAVMNVTR &other) const
    {
    return !(*this == other);
    }

NAVMRecord::NAVMNVDP::NAVMNVDP():
    door(0),
    unknown1(0)
    {
    memset(&unused1[0], 0x00, sizeof(unused1));
    }

NAVMRecord::NAVMNVDP::~NAVMNVDP()
    {
    //
    }

bool NAVMRecord::NAVMNVDP::operator ==(const NAVMNVDP &other) const
    {
    return (door == other.door &&
            unknown1 == other.unknown1);
    }

bool NAVMRecord::NAVMNVDP::operator !=(const NAVMNVDP &other) const
    {
    return !(*this == other);
    }

NAVMRecord::NAVMNVEX::NAVMNVEX():
    mesh(0),
    triangle(0)
    {
    memset(&unknown1[0], 0x00, sizeof(unknown1));
    }

NAVMRecord::NAVMNVEX::~NAVMNVEX()
    {
    //
    }

bool NAVMRecord::NAVMNVEX::operator ==(const NAVMNVEX &other) const
    {
    return (unknown1[0] == other.unknown1[0] &&
            unknown1[1] == other.unknown1[1] &&
            unknown1[2] == other.unknown1[2] &&
            unknown1[3] == other.unknown1[3] &&
            mesh == other.mesh &&
            triangle == other.triangle);
    }

bool NAVMRecord::NAVMNVEX::operator !=(const NAVMNVEX &other) const
    {
    return !(*this == other);
    }

NAVMRecord::NAVMRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

NAVMRecord::NAVMRecord(NAVMRecord *srcRecord):
    FNVRecord()
    {
    if(srcRecord == NULL)
        return;

    flags = srcRecord->flags;
    formID = srcRecord->formID;
    flagsUnk = srcRecord->flagsUnk;
    formVersion = srcRecord->formVersion;
    versionControl2[0] = srcRecord->versionControl2[0];
    versionControl2[1] = srcRecord->versionControl2[1];

    recData = srcRecord->recData;
    if(!srcRecord->IsChanged())
        return;

    EDID = srcRecord->EDID;
    NVER = srcRecord->NVER;
    DATA = srcRecord->DATA;
    NVVX = srcRecord->NVVX;
    NVTR = srcRecord->NVTR;
    NVCA = srcRecord->NVCA;
    NVDP = srcRecord->NVDP;
    NVGD = srcRecord->NVGD;
    NVEX = srcRecord->NVEX;
    return;
    }

NAVMRecord::~NAVMRecord()
    {
    //
    }

bool NAVMRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    op.Accept(DATA.value.cell);
    for(uint32_t ListIndex = 0; ListIndex < NVDP.value.size(); ListIndex++)
        op.Accept(NVDP.value[ListIndex].door);
    for(uint32_t ListIndex = 0; ListIndex < NVEX.value.size(); ListIndex++)
        op.Accept(NVEX.value[ListIndex].mesh);

    return op.Stop();
    }

uint32_t NAVMRecord::GetType()
    {
    return REV32(NAVM);
    }

char * NAVMRecord::GetStrType()
    {
    return "NAVM";
    }

int32_t NAVMRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
    {
    uint32_t subType = 0;
    uint32_t subSize = 0;
    while(buffer < end_buffer){
        subType = *(uint32_t *)buffer;
        buffer += 4;
        switch(subType)
            {
            case REV32(XXXX):
                buffer += 2;
                subSize = *(uint32_t *)buffer;
                buffer += 4;
                subType = *(uint32_t *)buffer;
                buffer += 6;
                break;
            default:
                subSize = *(uint16_t *)buffer;
                buffer += 2;
                break;
            }
        switch(subType)
            {
            case REV32(EDID):
                EDID.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(NVER):
                NVER.Read(buffer, subSize);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(NVVX):
                NVVX.Read(buffer, subSize);
                break;
            case REV32(NVTR):
                NVTR.Read(buffer, subSize);
                break;
            case REV32(NVCA):
                NVCA.Read(buffer, subSize);
                break;
            case REV32(NVDP):
                NVDP.Read(buffer, subSize);
                break;
            case REV32(NVGD):
                NVGD.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(NVEX):
                NVEX.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  NAVM: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t NAVMRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);

    EDID.Unload();
    NVER.Unload();
    DATA.Unload();
    NVVX.Unload();
    NVTR.Unload();
    NVCA.Unload();
    NVDP.Unload();
    NVGD.Unload();
    NVEX.Unload();
    return 1;
    }

int32_t NAVMRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(NVER);
    WRITE(DATA);
    WRITE(NVVX);
    WRITE(NVTR);
    WRITE(NVCA);
    WRITE(NVDP);
    WRITE(NVGD);
    WRITE(NVEX);
    return -1;
    }

bool NAVMRecord::operator ==(const NAVMRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            NVER == other.NVER &&
            DATA == other.DATA &&
            NVVX == other.NVVX &&
            NVTR == other.NVTR &&
            NVCA == other.NVCA &&
            NVDP == other.NVDP &&
            NVGD == other.NVGD &&
            NVEX == other.NVEX);
    }

bool NAVMRecord::operator !=(const NAVMRecord &other) const
    {
    return !(*this == other);
    }

bool NAVMRecord::equals(Record *other)
    {
    return *this == *(NAVMRecord *)other;
    }

bool NAVMRecord::deep_equals(Record *master, RecordOp &read_self, RecordOp &read_master, boost::unordered_set<Record *> &identical_records)
    {
    //Precondition: equals has been run for these records and returned true
    CELLRecord *parent_cell = (CELLRecord *)GetParentRecord(), *master_cell = (CELLRecord *)master->GetParentRecord();
    Record *parent_wrld = parent_cell->GetParentRecord(), *master_wrld = master_cell->GetParentRecord();
    //Check to make sure the parent cell is attached at the same spot
    if(parent_cell->formID != master_cell->formID)
        return false;
    if(parent_wrld != NULL)
        {
        if(master_wrld != NULL)
            {
            if(parent_wrld->formID != master_wrld->formID)
                return false;
            }
        else
            return false;
        }
    else if(master_wrld != NULL)
        return false;
    if(parent_wrld)
        {
        read_self.Accept((Record *&)parent_cell);
        read_master.Accept((Record *&)master_cell);
        parent_cell->XCLC.Load();
        master_cell->XCLC.Load();
        if(parent_cell->XCLC->posX != master_cell->XCLC->posX)
            return false;
        if(parent_cell->XCLC->posY != master_cell->XCLC->posY)
            return false;
        }
    return true;
    }
}