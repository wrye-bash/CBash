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
#include "ARMARecord.h"

namespace FNV
{
ARMARecord::ARMARecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

ARMARecord::ARMARecord(ARMARecord *srcRecord):
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
    OBND = srcRecord->OBND;
    FULL = srcRecord->FULL;
    BMDT = srcRecord->BMDT;
    if(srcRecord->MODL.IsLoaded())
        {
        MODL.Load();
        MODL->MODL = srcRecord->MODL->MODL;
        MODL->MODT = srcRecord->MODL->MODT;
        MODL->Textures = srcRecord->MODL->Textures;
        MODL->MODD = srcRecord->MODL->MODD;
        }
    if(srcRecord->MOD2.IsLoaded())
        {
        MOD2.Load();
        MOD2->MODL = srcRecord->MOD2->MODL; // MOD2
        MOD2->MODT = srcRecord->MOD2->MODT; // MO2T
        MOD2->Textures = srcRecord->MOD2->Textures; // MO2S
        }
    ICON = srcRecord->ICON;
    MICO = srcRecord->MICO;
    if(srcRecord->MOD3.IsLoaded())
        {
        MOD3.Load();
        MOD3->MODL = srcRecord->MOD3->MODL; // MOD3
        MOD3->MODT = srcRecord->MOD3->MODT; // MO3T
        MOD3->Textures = srcRecord->MOD3->Textures; // MO3S
        MOD3->MODD = srcRecord->MOD3->MODD; // MOSD
        }
    if(srcRecord->MOD4.IsLoaded())
        {
        MOD4.Load();
        MOD4->MODL = srcRecord->MOD4->MODL; // MOD4
        MOD4->MODT = srcRecord->MOD4->MODT; // MO4T
        MOD4->Textures = srcRecord->MOD4->Textures; // MO4S
        }
    ICO2 = srcRecord->ICO2;
    MIC2 = srcRecord->MIC2;
    ETYP = srcRecord->ETYP;
    DATA = srcRecord->DATA;
    DNAM = srcRecord->DNAM;
    return;
    }

ARMARecord::~ARMARecord()
    {
    //
    }

bool ARMARecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if (MODL.IsLoaded())
        MODL->Textures.VisitFormIDs(op);
    if (MOD2.IsLoaded() && MOD2->Textures.IsLoaded())
        MOD2->Textures.VisitFormIDs(op);
    if (MOD3.IsLoaded() && MOD3->Textures.IsLoaded())
        MOD3->Textures.VisitFormIDs(op);
    if (MOD4.IsLoaded() && MOD4->Textures.IsLoaded())
        MOD4->Textures.VisitFormIDs(op);

    return op.Stop();
    }

bool ARMARecord::IsHead()
    {
    if (!BMDT.IsLoaded()) return false;
    return (BMDT->bipedFlags & fIsHead) != 0;
    }

void ARMARecord::IsHead(bool value)
    {
    if (!BMDT.IsLoaded()) return;
    SETBIT(BMDT->bipedFlags, fIsHair, value);
    }

bool ARMARecord::IsHair()
    {
    if (!BMDT.IsLoaded()) return false;
    return (BMDT->bipedFlags & fIsHair) != 0;
    }

void ARMARecord::IsHair(bool value)
    {
    if (!BMDT.IsLoaded()) return;
    SETBIT(BMDT->bipedFlags, fIsHair, value);
    }

bool ARMARecord::IsUpperBody()
    {
    if (!BMDT.IsLoaded()) return false;
    return (BMDT->bipedFlags & fIsUpperBody) != 0;
    }

void ARMARecord::IsUpperBody(bool value)
    {
    if (!BMDT.IsLoaded()) return;
    SETBIT(BMDT->bipedFlags, fIsUpperBody, value);
    }

bool ARMARecord::IsLeftHand()
    {
    if (!BMDT.IsLoaded()) return false;
    return (BMDT->bipedFlags & fIsLeftHand) != 0;
    }

void ARMARecord::IsLeftHand(bool value)
    {
    if (!BMDT.IsLoaded()) return;
    SETBIT(BMDT->bipedFlags, fIsLeftHand, value);
    }

bool ARMARecord::IsRightHand()
    {
    if (!BMDT.IsLoaded()) return false;
    return (BMDT->bipedFlags & fIsRightHand) != 0;
    }

void ARMARecord::IsRightHand(bool value)
    {
    if (!BMDT.IsLoaded()) return;
    SETBIT(BMDT->bipedFlags, fIsRightHand, value);
    }

bool ARMARecord::IsWeapon()
    {
    if (!BMDT.IsLoaded()) return false;
    return (BMDT->bipedFlags & fIsWeapon) != 0;
    }

void ARMARecord::IsWeapon(bool value)
    {
    if (!BMDT.IsLoaded()) return;
    SETBIT(BMDT->bipedFlags, fIsWeapon, value);
    }

bool ARMARecord::IsPipBoy()
    {
    if (!BMDT.IsLoaded()) return false;
    return (BMDT->bipedFlags & fIsPipBoy) != 0;
    }

void ARMARecord::IsPipBoy(bool value)
    {
    if (!BMDT.IsLoaded()) return;
    SETBIT(BMDT->bipedFlags, fIsPipBoy, value);
    }

bool ARMARecord::IsBackpack()
    {
    if (!BMDT.IsLoaded()) return false;
    return (BMDT->bipedFlags & fIsBackpack) != 0;
    }

void ARMARecord::IsBackpack(bool value)
    {
    if (!BMDT.IsLoaded()) return;
    SETBIT(BMDT->bipedFlags, fIsBackpack, value);
    }

bool ARMARecord::IsNecklace()
    {
    if (!BMDT.IsLoaded()) return false;
    return (BMDT->bipedFlags & fIsNecklace) != 0;
    }

void ARMARecord::IsNecklace(bool value)
    {
    if (!BMDT.IsLoaded()) return;
    SETBIT(BMDT->bipedFlags, fIsNecklace, value);
    }

bool ARMARecord::IsHeadband()
    {
    if (!BMDT.IsLoaded()) return false;
    return (BMDT->bipedFlags & fIsHeadband) != 0;
    }

void ARMARecord::IsHeadband(bool value)
    {
    if (!BMDT.IsLoaded()) return;
    SETBIT(BMDT->bipedFlags, fIsHeadband, value);
    }

bool ARMARecord::IsHat()
    {
    if (!BMDT.IsLoaded()) return false;
    return (BMDT->bipedFlags & fIsHat) != 0;
    }

void ARMARecord::IsHat(bool value)
    {
    if (!BMDT.IsLoaded()) return;
    SETBIT(BMDT->bipedFlags, fIsHat, value);
    }

bool ARMARecord::IsEyeGlasses()
    {
    if (!BMDT.IsLoaded()) return false;
    return (BMDT->bipedFlags & fIsEyeGlasses) != 0;
    }

void ARMARecord::IsEyeGlasses(bool value)
    {
    if (!BMDT.IsLoaded()) return;
    SETBIT(BMDT->bipedFlags, fIsEyeGlasses, value);
    }

bool ARMARecord::IsNoseRing()
    {
    if (!BMDT.IsLoaded()) return false;
    return (BMDT->bipedFlags & fIsNoseRing) != 0;
    }

void ARMARecord::IsNoseRing(bool value)
    {
    if (!BMDT.IsLoaded()) return;
    SETBIT(BMDT->bipedFlags, fIsNoseRing, value);
    }

bool ARMARecord::IsEarrings()
    {
    if (!BMDT.IsLoaded()) return false;
    return (BMDT->bipedFlags & fIsEarrings) != 0;
    }

void ARMARecord::IsEarrings(bool value)
    {
    if (!BMDT.IsLoaded()) return;
    SETBIT(BMDT->bipedFlags, fIsEarrings, value);
    }

bool ARMARecord::IsMask()
    {
    if (!BMDT.IsLoaded()) return false;
    return (BMDT->bipedFlags & fIsMask) != 0;
    }

void ARMARecord::IsMask(bool value)
    {
    if (!BMDT.IsLoaded()) return;
    SETBIT(BMDT->bipedFlags, fIsMask, value);
    }

bool ARMARecord::IsChoker()
    {
    if (!BMDT.IsLoaded()) return false;
    return (BMDT->bipedFlags & fIsChoker) != 0;
    }

void ARMARecord::IsChoker(bool value)
    {
    if (!BMDT.IsLoaded()) return;
    SETBIT(BMDT->bipedFlags, fIsChoker, value);
    }

bool ARMARecord::IsMouthObject()
    {
    if (!BMDT.IsLoaded()) return false;
    return (BMDT->bipedFlags & fIsMouthObject) != 0;
    }

void ARMARecord::IsMouthObject(bool value)
    {
    if (!BMDT.IsLoaded()) return;
    SETBIT(BMDT->bipedFlags, fIsMouthObject, value);
    }

bool ARMARecord::IsBodyAddon1()
    {
    if (!BMDT.IsLoaded()) return false;
    return (BMDT->bipedFlags & fIsBodyAddon1) != 0;
    }

void ARMARecord::IsBodyAddon1(bool value)
    {
    if (!BMDT.IsLoaded()) return;
    SETBIT(BMDT->bipedFlags, fIsBodyAddon1, value);
    }

bool ARMARecord::IsBodyAddon2()
    {
    if (!BMDT.IsLoaded()) return false;
    return (BMDT->bipedFlags & fIsBodyAddon2) != 0;
    }

void ARMARecord::IsBodyAddon2(bool value)
    {
    if (!BMDT.IsLoaded()) return;
    SETBIT(BMDT->bipedFlags, fIsBodyAddon2, value);
    }

bool ARMARecord::IsBodyAddon3()
    {
    if (!BMDT.IsLoaded()) return false;
    return (BMDT->bipedFlags & fIsBodyAddon3) != 0;
    }

void ARMARecord::IsBodyAddon3(bool value)
    {
    if (!BMDT.IsLoaded()) return;
    SETBIT(BMDT->bipedFlags, fIsBodyAddon3, value);
    }

bool ARMARecord::IsFlagMask(uint32_t Mask, bool Exact)
    {
    if (!BMDT.IsLoaded()) return false;
    return Exact ? ((BMDT->bipedFlags & Mask) == Mask) : ((BMDT->bipedFlags & Mask) != 0);
    }

void ARMARecord::SetFlagMask(uint32_t Mask)
    {
    BMDT.Load();
    BMDT->bipedFlags = Mask;
    }

bool ARMARecord::IsUnknown1()
    {
    if (!BMDT.IsLoaded()) return false;
    return (BMDT->generalFlags & fIsUnknown1) != 0;
    }

void ARMARecord::IsUnknown1(bool value)
    {
    if (!BMDT.IsLoaded()) return;
    SETBIT(BMDT->generalFlags, fIsUnknown1, value);
    }

bool ARMARecord::IsUnknown2()
    {
    if (!BMDT.IsLoaded()) return false;
    return (BMDT->generalFlags & fIsUnknown2) != 0;
    }

void ARMARecord::IsUnknown2(bool value)
    {
    if (!BMDT.IsLoaded()) return;
    SETBIT(BMDT->generalFlags, fIsUnknown2, value);
    }

bool ARMARecord::IsHasBackpack()
    {
    if(!BMDT.IsLoaded()) return false;
    return (BMDT->generalFlags & fIsHasBackpack) != 0;
    }

void ARMARecord::IsHasBackpack(bool value)
    {
    if(!BMDT.IsLoaded()) return;
    SETBIT(BMDT->generalFlags, fIsHasBackpack, value);
    }

bool ARMARecord::IsMedium()
    {
    if (!BMDT.IsLoaded()) return false;
    return (BMDT->generalFlags & fIsMedium) != 0;
    }

void ARMARecord::IsMedium(bool value)
    {
    if (!BMDT.IsLoaded()) return;
    SETBIT(BMDT->generalFlags, fIsMedium, value);
    }

bool ARMARecord::IsUnknown3()
    {
    if (!BMDT.IsLoaded()) return false;
    return (BMDT->generalFlags & fIsUnknown3) != 0;
    }

void ARMARecord::IsUnknown3(bool value)
    {
    if (!BMDT.IsLoaded()) return;
    SETBIT(BMDT->generalFlags, fIsUnknown3, value);
    }

bool ARMARecord::IsPowerArmor()
    {
    if (!BMDT.IsLoaded()) return false;
    return (BMDT->generalFlags & fIsPowerArmor) != 0;
    }

void ARMARecord::IsPowerArmor(bool value)
    {
    if(!BMDT.IsLoaded()) return;
    SETBIT(BMDT->generalFlags, fIsPowerArmor, value);
    }

bool ARMARecord::IsNonPlayable()
    {
    if (!BMDT.IsLoaded()) return false;
    return (BMDT->generalFlags & fIsNonPlayable) != 0;
    }

void ARMARecord::IsNonPlayable(bool value)
    {
    if (!BMDT.IsLoaded()) return;
    SETBIT(BMDT->generalFlags, fIsNonPlayable, value);
    }

bool ARMARecord::IsHeavy()
    {
    if (!BMDT.IsLoaded()) return false;
    return (BMDT->generalFlags & fIsHeavy) != 0;
    }

void ARMARecord::IsHeavy(bool value)
    {
    if (!BMDT.IsLoaded()) return;
    SETBIT(BMDT->generalFlags, fIsHeavy, value);
    }

bool ARMARecord::IsExtraFlagMask(uint8_t Mask, bool Exact)
    {
    if (!BMDT.IsLoaded()) return false;
    return Exact ? ((BMDT->generalFlags & Mask) == Mask) : ((BMDT->generalFlags & Mask) != 0);
    }

void ARMARecord::SetExtraFlagMask(uint8_t Mask)
    {
    BMDT.Load();
    BMDT->generalFlags = Mask;
    }

bool ARMARecord::IsNone()
    {
    if (!ETYP.IsLoaded()) return false;
    return (ETYP.value == eNone);
    }

bool ARMARecord::IsBigGuns()
    {
    if (!ETYP.IsLoaded()) return false;
    return (ETYP.value == eBigGuns);
    }

bool ARMARecord::IsEnergyWeapons()
    {
    if (!ETYP.IsLoaded()) return false;
    return (ETYP.value == eEnergyWeapons);
    }

bool ARMARecord::IsSmallGuns()
    {
    if (!ETYP.IsLoaded()) return false;
    return (ETYP.value == eSmallGuns);
    }

bool ARMARecord::IsMeleeWeapons()
    {
    if (!ETYP.IsLoaded()) return false;
    return (ETYP.value == eMeleeWeapons);
    }

bool ARMARecord::IsUnarmedWeapon()
    {
    if (!ETYP.IsLoaded()) return false;
    return (ETYP.value == eUnarmedWeapon);
    }

bool ARMARecord::IsThrownWeapons()
    {
    if (!ETYP.IsLoaded()) return false;
    return (ETYP.value == eThrownWeapons);
    }

bool ARMARecord::IsMine()
    {
    if (!ETYP.IsLoaded()) return false;
    return (ETYP.value == eMine);
    }

bool ARMARecord::IsBodyWear()
    {
    if (!ETYP.IsLoaded()) return false;
    return (ETYP.value == eBodyWear);
    }

bool ARMARecord::IsHeadWear()
    {
    if (!ETYP.IsLoaded()) return false;
    return (ETYP.value == eHeadWear);
    }

bool ARMARecord::IsHandWear()
    {
    if (!ETYP.IsLoaded()) return false;
    return (ETYP.value == eHandWear);
    }

bool ARMARecord::IsChems()
    {
    if (!ETYP.IsLoaded()) return false;
    return (ETYP.value == eChems);
    }

bool ARMARecord::IsStimpack()
    {
    if (!ETYP.IsLoaded()) return false;
    return (ETYP.value == eStimpack);
    }

bool ARMARecord::IsEdible()
    {
    if (!ETYP.IsLoaded()) return false;
    return (ETYP.value == eEdible);
    }

bool ARMARecord::IsAlcohol()
    {
    if (!ETYP.IsLoaded()) return false;
    return (ETYP.value == eAlcohol);
    }

bool ARMARecord::IsEquipmentType(int32_t Type)
    {
    if (!ETYP.IsLoaded()) return false;
    return ETYP.value == Type;
    }

void ARMARecord::SetEquipmentType(int32_t Type)
    {
    ETYP.Load();
    ETYP.value = Type;
    }

bool ARMARecord::IsModulatesVoice()
    {
    if (!DNAM.IsLoaded()) return false;
    return (DNAM->flags & fIsModulatesVoice) != 0;
    }

void ARMARecord::IsModulatesVoice(bool value)
    {
    if (!DNAM.IsLoaded()) return;
    SETBIT(DNAM->flags, fIsModulatesVoice, value);
    }

bool ARMARecord::IsDNAMFlagMask(uint16_t Mask, bool Exact)
    {
    if (!DNAM.IsLoaded()) return false;
    return Exact ? ((DNAM->flags & Mask) == Mask) : ((DNAM->flags & Mask) != 0);
    }

void ARMARecord::SetDNAMFlagMask(uint16_t Mask)
    {
    DNAM.Load();
    DNAM->flags = Mask;
    }

uint32_t ARMARecord::GetType()
    {
    return REV32(ARMA);
    }

char * ARMARecord::GetStrType()
    {
    return "ARMA";
    }

int32_t ARMARecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(OBND):
                OBND.Read(buffer, subSize);
                break;
            case REV32(FULL):
                FULL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(BMDT):
                BMDT.Read(buffer, subSize);
                break;
            case REV32(MODL):
                MODL.Load();
                MODL->MODL.Read(buffer, subSize, CompressedOnDisk);
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
            case REV32(MOD2):
                MOD2.Load();
                MOD2->MODL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MO2T):
                MOD2.Load();
                MOD2->MODT.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MO2S):
                MOD2.Load();
                MOD2->Textures.Read(buffer, subSize);
                break;
            case REV32(ICON):
                ICON.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MICO):
                MICO.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MOD3):
                MOD3.Load();
                MOD3->MODL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MO3T):
                MOD3.Load();
                MOD3->MODT.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MO3S):
                MOD3.Load();
                MOD3->Textures.Read(buffer, subSize);
                break;
            case REV32(MOSD):
                MOD3.Load();
                MOD3->MODD.Read(buffer, subSize);
                break;
            case REV32(MOD4):
                MOD4.Load();
                MOD4->MODL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MO4T):
                MOD4.Load();
                MOD4->MODT.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MO4S):
                MOD4.Load();
                MOD4->Textures.Read(buffer, subSize);
                break;
            case REV32(ICO2):
                ICO2.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MIC2):
                MIC2.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(ETYP):
                ETYP.Read(buffer, subSize);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(DNAM):
                DNAM.Read(buffer, subSize);
                break;
            default:
                UnrecognizedSubRecord(formID, subType, subSize, buffer, end_buffer);
                break;
            }
        };
    return 0;
    }

int32_t ARMARecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    OBND.Unload();
    FULL.Unload();
    BMDT.Unload();
    MODL.Unload();
    MOD2.Unload();
    ICON.Unload();
    MICO.Unload();
    MOD3.Unload();
    MOD4.Unload();
    ICO2.Unload();
    MIC2.Unload();
    ETYP.Unload();
    DATA.Unload();
    DNAM.Unload();
    return 1;
    }

int32_t ARMARecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(OBND);
    WRITE(FULL);
    WRITE(BMDT);

    if(MODL.IsLoaded())
        {
        if (MODL->MODL.IsLoaded())
            MODL->MODL.Write(REV32(MODL), writer);
        if (MODL->MODT.IsLoaded())
            MODL->MODT.Write(REV32(MODT), writer);
        if (MODL->Textures.IsLoaded())
            MODL->Textures.Write(REV32(MOD2), writer);
        if (MODL->MODD.IsLoaded())
            MODL->MODD.Write(REV32(MODD), writer);
        }

    if(MOD2.IsLoaded())
        {
        if (MOD2->MODL.IsLoaded())
            MOD2->MODL.Write(REV32(MOD2), writer);
        if (MOD2->MODT.IsLoaded())
            MOD2->MODT.Write(REV32(MO2T), writer);
        if (MOD2->Textures.IsLoaded())
            MOD2->Textures.Write(REV32(MO2S), writer);
        }

    WRITE(ICON);
    WRITE(MICO);

    if(MOD3.IsLoaded())
        {
        if (MOD3->MODL.IsLoaded())
            MOD3->MODL.Write(REV32(MOD3), writer);
        if (MOD3->MODT.IsLoaded())
            MOD3->MODT.Write(REV32(MO3T), writer);
        if (MOD3->Textures.IsLoaded())
            MOD3->Textures.Write(REV32(MO3S), writer);
        if (MOD3->MODD.IsLoaded())
            MOD3->MODD.Write(REV32(MOSD), writer);
        }

    if(MOD4.IsLoaded())
        {
        if (MOD4->MODL.IsLoaded())
            MOD4->MODL.Write(REV32(MOD4), writer);
        if (MOD4->MODT.IsLoaded())
            MOD4->MODT.Write(REV32(MO4T), writer);
        if (MOD4->Textures.IsLoaded())
            MOD4->Textures.Write(REV32(MO4S), writer);
        }

    WRITE(ICO2);
    WRITE(MIC2);
    WRITE(ETYP);
    WRITE(DATA);
    WRITE(DNAM);

    return -1;
    }

bool ARMARecord::operator ==(const ARMARecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            OBND == other.OBND &&
            FULL.equals(other.FULL) &&
            BMDT == other.BMDT &&
            MODL == other.MODL &&
            MOD2 == other.MOD2 &&
            ICON.equalsi(other.ICON) &&
            MICO.equalsi(other.MICO) &&
            MOD3 == other.MOD3 &&
            MOD4 == other.MOD4 &&
            ICO2.equalsi(other.ICO2) &&
            MIC2.equalsi(other.MIC2) &&
            ETYP == other.ETYP &&
            DATA == other.DATA &&
            DNAM == other.DNAM);
    }

bool ARMARecord::operator !=(const ARMARecord &other) const
    {
    return !(*this == other);
    }

bool ARMARecord::equals(Record *other)
    {
    return *this == *(ARMARecord *)other;
    }
}