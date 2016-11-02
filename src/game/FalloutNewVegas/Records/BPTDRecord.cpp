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
#include "common/Common.h"
#include "BPTDRecord.h"

namespace FNV
{
BPTDRecord::BPTDBPND::BPTDBPND():
    damageMult(0.0f),
    flags(0),
    partType(0),
    healthPercent(0),
    actorValue(0),
    hitChance(0),
    explodableExplosionChance(0),
    explodableDebrisCount(0),
    explodableDebris(0),
    explodableExplosion(0),
    maxTrackAngle(0.0f),
    explodableDebrisScale(0.0f),
    severableDebrisCount(0),
    severableDebris(0),
    severableExplosion(0),
    severableDebrisScale(0.0f),
    transX(0.0f),
    transY(0.0f),
    transZ(0.0f),
    rotX(0.0f),
    rotY(0.0f),
    rotZ(0.0f),
    severableImpact(0),
    explodableImpact(0),
    severableDecalCount(0),
    explodableDecalCount(0),
    limbReplaceScale(0.0f)
    {
    memset(&unused1[0], 0x00, sizeof(unused1));
    }

BPTDRecord::BPTDBPND::~BPTDBPND()
    {
    //
    }

bool BPTDRecord::BPTDBPND::operator ==(const BPTDBPND &other) const
    {
    return (flags == other.flags &&
            partType == other.partType &&
            healthPercent == other.healthPercent &&
            actorValue == other.actorValue &&
            hitChance == other.hitChance &&
            explodableExplosionChance == other.explodableExplosionChance &&
            explodableDebrisCount == other.explodableDebrisCount &&
            explodableDebris == other.explodableDebris &&
            explodableExplosion == other.explodableExplosion &&
            severableDebrisCount == other.severableDebrisCount &&
            severableDebris == other.severableDebris &&
            severableExplosion == other.severableExplosion &&
            severableImpact == other.severableImpact &&
            explodableImpact == other.explodableImpact &&
            severableDecalCount == other.severableDecalCount &&
            explodableDecalCount == other.explodableDecalCount &&
            AlmostEqual(limbReplaceScale,other.limbReplaceScale,2) &&
            AlmostEqual(damageMult,other.damageMult,2) &&
            AlmostEqual(maxTrackAngle,other.maxTrackAngle,2) &&
            AlmostEqual(explodableDebrisScale,other.explodableDebrisScale,2) &&
            AlmostEqual(severableDebrisScale,other.severableDebrisScale,2) &&
            AlmostEqual(transX,other.transX,2) &&
            AlmostEqual(transY,other.transY,2) &&
            AlmostEqual(transZ,other.transZ,2) &&
            AlmostEqual(rotX,other.rotX,2) &&
            AlmostEqual(rotY,other.rotY,2) &&
            AlmostEqual(rotZ,other.rotZ,2));
    }

bool BPTDRecord::BPTDBPND::operator !=(const BPTDBPND &other) const
    {
    return !(*this == other);
    }

bool BPTDRecord::BPTDPart::IsSeverable()
    {
    return (BPND.value.flags & fIsSeverable) != 0;
    }

void BPTDRecord::BPTDPart::IsSeverable(bool value)
    {
    SETBIT(BPND.value.flags, fIsSeverable, value);
    }

bool BPTDRecord::BPTDPart::IsIKData()
    {
    return (BPND.value.flags & fIsIKData) != 0;
    }

void BPTDRecord::BPTDPart::IsIKData(bool value)
    {
    SETBIT(BPND.value.flags, fIsIKData, value);
    }

bool BPTDRecord::BPTDPart::IsIKDataBipedData()
    {
    return (BPND.value.flags & fIsIKDataBipedData) != 0;
    }

void BPTDRecord::BPTDPart::IsIKDataBipedData(bool value)
    {
    SETBIT(BPND.value.flags, fIsIKDataBipedData, value);
    }

bool BPTDRecord::BPTDPart::IsExplodable()
    {
    return (BPND.value.flags & fIsExplodable) != 0;
    }

void BPTDRecord::BPTDPart::IsExplodable(bool value)
    {
    SETBIT(BPND.value.flags, fIsExplodable, value);
    }

bool BPTDRecord::BPTDPart::IsIKDataIsHead()
    {
    return (BPND.value.flags & fIsIKDataIsHead) != 0;
    }

void BPTDRecord::BPTDPart::IsIKDataIsHead(bool value)
    {
    SETBIT(BPND.value.flags, fIsIKDataIsHead, value);
    }

bool BPTDRecord::BPTDPart::IsIKDataHeadTracking()
    {
    return (BPND.value.flags & fIsIKDataHeadTracking) != 0;
    }

void BPTDRecord::BPTDPart::IsIKDataHeadTracking(bool value)
    {
    SETBIT(BPND.value.flags, fIsIKDataHeadTracking, value);
    }

bool BPTDRecord::BPTDPart::IsAbsoluteHitChance()
    {
    return (BPND.value.flags & fIsAbsoluteHitChance) != 0;
    }

void BPTDRecord::BPTDPart::IsAbsoluteHitChance(bool value)
    {
    SETBIT(BPND.value.flags, fIsAbsoluteHitChance, value);
    }

bool BPTDRecord::BPTDPart::IsFlagMask(uint8_t Mask, bool Exact)
    {
    return Exact ? ((BPND.value.flags & Mask) == Mask) : ((BPND.value.flags & Mask) != 0);
    }

void BPTDRecord::BPTDPart::SetFlagMask(uint8_t Mask)
    {
    BPND.value.flags = Mask;
    }

bool BPTDRecord::BPTDPart::IsTorso()
    {
    return BPND.value.partType == eTorso;
    }

void BPTDRecord::BPTDPart::IsTorso(bool value)
    {
    BPND.value.partType = value ? eTorso : eHead1;
    }

bool BPTDRecord::BPTDPart::IsHead1()
    {
    return BPND.value.partType == eHead1;
    }

void BPTDRecord::BPTDPart::IsHead1(bool value)
    {
    BPND.value.partType = value ? eHead1 : eTorso;
    }

bool BPTDRecord::BPTDPart::IsHead2()
    {
    return BPND.value.partType == eHead2;
    }

void BPTDRecord::BPTDPart::IsHead2(bool value)
    {
    BPND.value.partType = value ? eHead2 : eTorso;
    }

bool BPTDRecord::BPTDPart::IsLeftArm1()
    {
    return BPND.value.partType == eLeftArm1;
    }

void BPTDRecord::BPTDPart::IsLeftArm1(bool value)
    {
    BPND.value.partType = value ? eLeftArm1 : eTorso;
    }

bool BPTDRecord::BPTDPart::IsLeftArm2()
    {
    return BPND.value.partType == eLeftArm2;
    }

void BPTDRecord::BPTDPart::IsLeftArm2(bool value)
    {
    BPND.value.partType = value ? eLeftArm2 : eTorso;
    }

bool BPTDRecord::BPTDPart::IsRightArm1()
    {
    return BPND.value.partType == eRightArm1;
    }

void BPTDRecord::BPTDPart::IsRightArm1(bool value)
    {
    BPND.value.partType = value ? eRightArm1 : eTorso;
    }

bool BPTDRecord::BPTDPart::IsRightArm2()
    {
    return BPND.value.partType == eRightArm2;
    }

void BPTDRecord::BPTDPart::IsRightArm2(bool value)
    {
    BPND.value.partType = value ? eRightArm2 : eTorso;
    }

bool BPTDRecord::BPTDPart::IsLeftLeg1()
    {
    return BPND.value.partType == eLeftLeg1;
    }

void BPTDRecord::BPTDPart::IsLeftLeg1(bool value)
    {
    BPND.value.partType = value ? eLeftLeg1 : eTorso;
    }

bool BPTDRecord::BPTDPart::IsLeftLeg2()
    {
    return BPND.value.partType == eLeftLeg2;
    }

void BPTDRecord::BPTDPart::IsLeftLeg2(bool value)
    {
    BPND.value.partType = value ? eLeftLeg2 : eTorso;
    }

bool BPTDRecord::BPTDPart::IsLeftLeg3()
    {
    return BPND.value.partType == eLeftLeg3;
    }

void BPTDRecord::BPTDPart::IsLeftLeg3(bool value)
    {
    BPND.value.partType = value ? eLeftLeg3 : eTorso;
    }

bool BPTDRecord::BPTDPart::IsRightLeg1()
    {
    return BPND.value.partType == eRightLeg1;
    }

void BPTDRecord::BPTDPart::IsRightLeg1(bool value)
    {
    BPND.value.partType = value ? eRightLeg1 : eTorso;
    }

bool BPTDRecord::BPTDPart::IsRightLeg2()
    {
    return BPND.value.partType == eRightLeg2;
    }

void BPTDRecord::BPTDPart::IsRightLeg2(bool value)
    {
    BPND.value.partType = value ? eRightLeg2 : eTorso;
    }

bool BPTDRecord::BPTDPart::IsRightLeg3()
    {
    return BPND.value.partType == eRightLeg3;
    }

void BPTDRecord::BPTDPart::IsRightLeg3(bool value)
    {
    BPND.value.partType = value ? eRightLeg3 : eTorso;
    }

bool BPTDRecord::BPTDPart::IsBrain()
    {
    return BPND.value.partType == eBrain;
    }

void BPTDRecord::BPTDPart::IsBrain(bool value)
    {
    BPND.value.partType = value ? eBrain : eTorso;
    }

bool BPTDRecord::BPTDPart::IsWeapon()
    {
    return BPND.value.partType == eWeapon;
    }

void BPTDRecord::BPTDPart::IsWeapon(bool value)
    {
    BPND.value.partType = value ? eWeapon : eTorso;
    }

bool BPTDRecord::BPTDPart::IsType(uint8_t Type)
    {
    return BPND.value.partType == Type;
    }

void BPTDRecord::BPTDPart::SetType(uint8_t Type)
    {
    BPND.value.partType = Type;
    }

void BPTDRecord::BPTDPart::Write(FileWriter &writer)
    {
    WRITEREQ(BPTN);
    WRITEREQ(BPNN);
    WRITEREQ(BPNT);
    WRITEREQ(BPNI);
    WRITE(BPND);
    WRITEREQ(NAM1);
    WRITEREQ(NAM4);
    WRITEREQ(NAM5);
    }

bool BPTDRecord::BPTDPart::operator ==(const BPTDPart &other) const
    {
    return (BPND == other.BPND &&
            BPTN.equalsi(other.BPTN) &&
            BPNN.equalsi(other.BPNN) &&
            BPNT.equalsi(other.BPNT) &&
            BPNI.equalsi(other.BPNI) &&
            NAM1.equalsi(other.NAM1) &&
            NAM4.equalsi(other.NAM4) &&
            NAM5 == other.NAM5);
    }

bool BPTDRecord::BPTDPart::operator !=(const BPTDPart &other) const
    {
    return !(*this == other);
    }

BPTDRecord::BPTDRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

BPTDRecord::BPTDRecord(BPTDRecord *srcRecord):
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
    MODL = srcRecord->MODL;
    Parts = srcRecord->Parts;
    RAGA = srcRecord->RAGA;
    return;
    }

BPTDRecord::~BPTDRecord()
    {
    //
    }

bool BPTDRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(MODL.IsLoaded())
        {
        for(uint32_t x = 0; x < MODL->Textures.MODS.size(); x++)
            op.Accept(MODL->Textures.MODS[x]->texture);
        }
    for(uint32_t ListIndex = 0; ListIndex < Parts.value.size(); ListIndex++)
        {
        op.Accept(Parts.value[ListIndex]->BPND.value.explodableDebris);
        op.Accept(Parts.value[ListIndex]->BPND.value.explodableExplosion);
        op.Accept(Parts.value[ListIndex]->BPND.value.severableDebris);
        op.Accept(Parts.value[ListIndex]->BPND.value.severableExplosion);
        op.Accept(Parts.value[ListIndex]->BPND.value.severableImpact);
        op.Accept(Parts.value[ListIndex]->BPND.value.explodableImpact);
        }
    op.Accept(RAGA.value);

    return op.Stop();
    }

uint32_t BPTDRecord::GetType()
    {
    return REV32(BPTD);
    }

char * BPTDRecord::GetStrType()
    {
    return "BPTD";
    }

int32_t BPTDRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(MODL):
                MODL.Load();
                MODL->MODL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MODB):
                MODL.Load();
                MODL->MODB.Read(buffer, subSize);
                break;
            case REV32(MODT):
                MODL.Load();
                MODL->MODT.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MODS):
                MODL.Load();
                MODL->Textures.Read(buffer, subSize);
                break;
            case REV32(MODD):
                MODL.Load();
                MODL->MODD.Read(buffer, subSize);
                break;
            case REV32(BPTN):
                Parts.value.push_back(new BPTDPart);
                Parts.value.back()->BPTN.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(BPNN):
                if(Parts.value.size() == 0)
                    Parts.value.push_back(new BPTDPart);
                Parts.value.back()->BPNN.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(BPNT):
                if(Parts.value.size() == 0)
                    Parts.value.push_back(new BPTDPart);
                Parts.value.back()->BPNT.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(BPNI):
                if(Parts.value.size() == 0)
                    Parts.value.push_back(new BPTDPart);
                Parts.value.back()->BPNI.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(BPND):
                if(Parts.value.size() == 0)
                    Parts.value.push_back(new BPTDPart);
                Parts.value.back()->BPND.Read(buffer, subSize);
                break;
            case REV32(NAM1):
                if(Parts.value.size() == 0)
                    Parts.value.push_back(new BPTDPart);
                Parts.value.back()->NAM1.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(NAM4):
                if(Parts.value.size() == 0)
                    Parts.value.push_back(new BPTDPart);
                Parts.value.back()->NAM4.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(NAM5):
                if(Parts.value.size() == 0)
                    Parts.value.push_back(new BPTDPart);
                Parts.value.back()->NAM5.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(RAGA):
                RAGA.Read(buffer, subSize);
                break;
            default:
                UnrecognizedSubRecord(formID, subType, subSize, buffer, end_buffer);
                break;
            }
        };
    return 0;
    }

int32_t BPTDRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);

    EDID.Unload();
    MODL.Unload();
    Parts.Unload();
    RAGA.Unload();
    return 1;
    }

int32_t BPTDRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    MODL.Write(writer);
    Parts.Write(writer);
    WRITE(RAGA);
    return -1;
    }

bool BPTDRecord::operator ==(const BPTDRecord &other) const
    {
    return (RAGA == other.RAGA &&
            EDID.equalsi(other.EDID) &&
            MODL == other.MODL &&
            Parts == other.Parts);
    }

bool BPTDRecord::operator !=(const BPTDRecord &other) const
    {
    return !(*this == other);
    }

bool BPTDRecord::equals(Record *other)
    {
    return *this == *(BPTDRecord *)other;
    }
}