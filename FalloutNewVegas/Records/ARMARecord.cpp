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
        MODL->Textures.MODS = srcRecord->MODL->Textures.MODS;
        MODL->MODD = srcRecord->MODL->MODD;
        }
    if(srcRecord->MOD2.IsLoaded())
        {
        MOD2.Load();
        MOD2->MOD2 = srcRecord->MOD2->MOD2;
        MOD2->MO2T = srcRecord->MOD2->MO2T;
        MOD2->MO2S = srcRecord->MOD2->MO2S;
        }
    ICON = srcRecord->ICON;
    MICO = srcRecord->MICO;
    if(srcRecord->MOD3.IsLoaded())
        {
        MOD3.Load();
        MOD3->MOD3 = srcRecord->MOD3->MOD3;
        MOD3->MO3T = srcRecord->MOD3->MO3T;
        MOD3->MO3S = srcRecord->MOD3->MO3S;
        MOD3->MOSD = srcRecord->MOD3->MOSD;
        }
    if(srcRecord->MOD4.IsLoaded())
        {
        MOD4.Load();
        MOD4->MOD4 = srcRecord->MOD4->MOD4;
        MOD4->MO4T = srcRecord->MOD4->MO4T;
        MOD4->MO4S = srcRecord->MOD4->MO4S;
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

    if(MODL.IsLoaded())
        {
        for(UINT32 x = 0; x < MODL->Textures.MODS.size(); x++)
            op.Accept(MODL->Textures.MODS[x]->texture);
        }
    if(MOD2.IsLoaded() && MOD2->MO2S.IsLoaded())
        op.Accept(MOD2->MO2S->value);
    if(MOD3.IsLoaded() && MOD3->MO3S.IsLoaded())
        op.Accept(MOD3->MO3S->value);
    if(MOD4.IsLoaded() && MOD4->MO4S.IsLoaded())
        op.Accept(MOD4->MO4S->value);

    return op.Stop();
    }

bool ARMARecord::IsHead()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsHead) != 0;
    }

void ARMARecord::IsHead(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsHead) : (Dummy->flags & ~fIsHead);
    }

bool ARMARecord::IsHair()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsHair) != 0;
    }

void ARMARecord::IsHair(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsHair) : (Dummy->flags & ~fIsHair);
    }

bool ARMARecord::IsUpperBody()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUpperBody) != 0;
    }

void ARMARecord::IsUpperBody(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsUpperBody) : (Dummy->flags & ~fIsUpperBody);
    }

bool ARMARecord::IsLeftHand()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsLeftHand) != 0;
    }

void ARMARecord::IsLeftHand(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsLeftHand) : (Dummy->flags & ~fIsLeftHand);
    }

bool ARMARecord::IsRightHand()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsRightHand) != 0;
    }

void ARMARecord::IsRightHand(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsRightHand) : (Dummy->flags & ~fIsRightHand);
    }

bool ARMARecord::IsWeapon()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsWeapon) != 0;
    }

void ARMARecord::IsWeapon(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsWeapon) : (Dummy->flags & ~fIsWeapon);
    }

bool ARMARecord::IsPipBoy()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsPipBoy) != 0;
    }

void ARMARecord::IsPipBoy(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsPipBoy) : (Dummy->flags & ~fIsPipBoy);
    }

bool ARMARecord::IsBackpack()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsBackpack) != 0;
    }

void ARMARecord::IsBackpack(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsBackpack) : (Dummy->flags & ~fIsBackpack);
    }

bool ARMARecord::IsNecklace()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNecklace) != 0;
    }

void ARMARecord::IsNecklace(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsNecklace) : (Dummy->flags & ~fIsNecklace);
    }

bool ARMARecord::IsHeadband()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsHeadband) != 0;
    }

void ARMARecord::IsHeadband(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsHeadband) : (Dummy->flags & ~fIsHeadband);
    }

bool ARMARecord::IsHat()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsHat) != 0;
    }

void ARMARecord::IsHat(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsHat) : (Dummy->flags & ~fIsHat);
    }

bool ARMARecord::IsEyeGlasses()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsEyeGlasses) != 0;
    }

void ARMARecord::IsEyeGlasses(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsEyeGlasses) : (Dummy->flags & ~fIsEyeGlasses);
    }

bool ARMARecord::IsNoseRing()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNoseRing) != 0;
    }

void ARMARecord::IsNoseRing(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsNoseRing) : (Dummy->flags & ~fIsNoseRing);
    }

bool ARMARecord::IsEarrings()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsEarrings) != 0;
    }

void ARMARecord::IsEarrings(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsEarrings) : (Dummy->flags & ~fIsEarrings);
    }

bool ARMARecord::IsMask()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsMask) != 0;
    }

void ARMARecord::IsMask(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsMask) : (Dummy->flags & ~fIsMask);
    }

bool ARMARecord::IsChoker()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsChoker) != 0;
    }

void ARMARecord::IsChoker(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsChoker) : (Dummy->flags & ~fIsChoker);
    }

bool ARMARecord::IsMouthObject()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsMouthObject) != 0;
    }

void ARMARecord::IsMouthObject(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsMouthObject) : (Dummy->flags & ~fIsMouthObject);
    }

bool ARMARecord::IsBodyAddon1()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsBodyAddon1) != 0;
    }

void ARMARecord::IsBodyAddon1(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsBodyAddon1) : (Dummy->flags & ~fIsBodyAddon1);
    }

bool ARMARecord::IsBodyAddon2()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsBodyAddon2) != 0;
    }

void ARMARecord::IsBodyAddon2(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsBodyAddon2) : (Dummy->flags & ~fIsBodyAddon2);
    }

bool ARMARecord::IsBodyAddon3()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsBodyAddon3) != 0;
    }

void ARMARecord::IsBodyAddon3(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsBodyAddon3) : (Dummy->flags & ~fIsBodyAddon3);
    }

bool ARMARecord::IsFlagMask(UINT32 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void ARMARecord::SetFlagMask(UINT32 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool ARMARecord::IsUnknown1()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUnknown1) != 0;
    }

void ARMARecord::IsUnknown1(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsUnknown1) : (Dummy->flags & ~fIsUnknown1);
    }

bool ARMARecord::IsUnknown2()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUnknown2) != 0;
    }

void ARMARecord::IsUnknown2(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsUnknown2) : (Dummy->flags & ~fIsUnknown2);
    }

bool ARMARecord::IsHasBackpack()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsHasBackpack) != 0;
    }

void ARMARecord::IsHasBackpack(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsHasBackpack) : (Dummy->flags & ~fIsHasBackpack);
    }

bool ARMARecord::IsMedium()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsMedium) != 0;
    }

void ARMARecord::IsMedium(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsMedium) : (Dummy->flags & ~fIsMedium);
    }

bool ARMARecord::IsUnknown3()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUnknown3) != 0;
    }

void ARMARecord::IsUnknown3(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsUnknown3) : (Dummy->flags & ~fIsUnknown3);
    }

bool ARMARecord::IsPowerArmor()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsPowerArmor) != 0;
    }

void ARMARecord::IsPowerArmor(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsPowerArmor) : (Dummy->flags & ~fIsPowerArmor);
    }

bool ARMARecord::IsNonPlayable()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNonPlayable) != 0;
    }

void ARMARecord::IsNonPlayable(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsNonPlayable) : (Dummy->flags & ~fIsNonPlayable);
    }

bool ARMARecord::IsHeavy()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsHeavy) != 0;
    }

void ARMARecord::IsHeavy(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsHeavy) : (Dummy->flags & ~fIsHeavy);
    }

bool ARMARecord::IsExtraFlagMask(UINT8 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void ARMARecord::SetExtraFlagMask(UINT8 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool ARMARecord::IsNone()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eNone);
    }

void ARMARecord::IsNone(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eNone : eDummyDefault;
    }

bool ARMARecord::IsBigGuns()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eBigGuns);
    }

void ARMARecord::IsBigGuns(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eBigGuns : eDummyDefault;
    }

bool ARMARecord::IsEnergyWeapons()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eEnergyWeapons);
    }

void ARMARecord::IsEnergyWeapons(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eEnergyWeapons : eDummyDefault;
    }

bool ARMARecord::IsSmallGuns()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eSmallGuns);
    }

void ARMARecord::IsSmallGuns(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eSmallGuns : eDummyDefault;
    }

bool ARMARecord::IsMeleeWeapons()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eMeleeWeapons);
    }

void ARMARecord::IsMeleeWeapons(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eMeleeWeapons : eDummyDefault;
    }

bool ARMARecord::IsUnarmedWeapon()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eUnarmedWeapon);
    }

void ARMARecord::IsUnarmedWeapon(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eUnarmedWeapon : eDummyDefault;
    }

bool ARMARecord::IsThrownWeapons()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eThrownWeapons);
    }

void ARMARecord::IsThrownWeapons(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eThrownWeapons : eDummyDefault;
    }

bool ARMARecord::IsMine()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eMine);
    }

void ARMARecord::IsMine(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eMine : eDummyDefault;
    }

bool ARMARecord::IsBodyWear()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eBodyWear);
    }

void ARMARecord::IsBodyWear(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eBodyWear : eDummyDefault;
    }

bool ARMARecord::IsHeadWear()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHeadWear);
    }

void ARMARecord::IsHeadWear(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eHeadWear : eDummyDefault;
    }

bool ARMARecord::IsHandWear()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHandWear);
    }

void ARMARecord::IsHandWear(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eHandWear : eDummyDefault;
    }

bool ARMARecord::IsChems()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eChems);
    }

void ARMARecord::IsChems(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eChems : eDummyDefault;
    }

bool ARMARecord::IsStimpack()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eStimpack);
    }

void ARMARecord::IsStimpack(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eStimpack : eDummyDefault;
    }

bool ARMARecord::IsFood()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eFood);
    }

void ARMARecord::IsFood(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eFood : eDummyDefault;
    }

bool ARMARecord::IsAlcohol()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAlcohol);
    }

void ARMARecord::IsAlcohol(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAlcohol : eDummyDefault;
    }

bool ARMARecord::IsEquipmentType(UINT32 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void ARMARecord::SetEquipmentType(UINT32 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool ARMARecord::IsModulatesVoice()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsModulatesVoice) != 0;
    }

void ARMARecord::IsModulatesVoice(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsModulatesVoice) : (Dummy->flags & ~fIsModulatesVoice);
    }

bool ARMARecord::IsDNAMFlagMask(UINT16 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void ARMARecord::SetDNAMFlagMask(UINT16 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 ARMARecord::GetType()
    {
    return REV32(ARMA);
    }

STRING ARMARecord::GetStrType()
    {
    return "ARMA";
    }

SINT32 ARMARecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
    {
    UINT32 subType = 0;
    UINT32 subSize = 0;
    while(buffer < end_buffer){
        subType = *(UINT32 *)buffer;
        buffer += 4;
        switch(subType)
            {
            case REV32(XXXX):
                buffer += 2;
                subSize = *(UINT32 *)buffer;
                buffer += 4;
                subType = *(UINT32 *)buffer;
                buffer += 6;
                break;
            default:
                subSize = *(UINT16 *)buffer;
                buffer += 2;
                break;
            }
        switch(subType)
            {
            case REV32(EDID):
                EDID.Read(buffer, subSize);
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
                MODL->MODL.Read(buffer, subSize);
                break;
            case REV32(MODT):
                MODL.Load();
                MODL->MODT.Read(buffer, subSize);
                break;
            case REV32(MODS):
                MODL.Load();
                MODL->MODS.Read(buffer, subSize);
                break;
            case REV32(MODD):
                MODL.Load();
                MODL->MODD.Read(buffer, subSize);
                break;
            case REV32(MOD2):
                MOD2.Load();
                MOD2->MOD2.Read(buffer, subSize);
                break;
            case REV32(MO2T):
                MOD2.Load();
                MOD2->MO2T.Read(buffer, subSize);
                break;
            case REV32(MO2S):
                MOD2.Load();
                MOD2->MO2S.Read(buffer, subSize);
                break;
            case REV32(ICON):
                ICON.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MICO):
                MICO.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MOD3):
                MOD3.Load();
                MOD3->MOD3.Read(buffer, subSize);
                break;
            case REV32(MO3T):
                MOD3.Load();
                MOD3->MO3T.Read(buffer, subSize);
                break;
            case REV32(MO3S):
                MOD3.Load();
                MOD3->MO3S.Read(buffer, subSize);
                break;
            case REV32(MOSD):
                MOD3.Load();
                MOD3->MOSD.Read(buffer, subSize);
                break;
            case REV32(MOD4):
                MOD4.Load();
                MOD4->MOD4.Read(buffer, subSize);
                break;
            case REV32(MO4T):
                MOD4.Load();
                MOD4->MO4T.Read(buffer, subSize);
                break;
            case REV32(MO4S):
                MOD4.Load();
                MOD4->MO4S.Read(buffer, subSize);
                break;
            case REV32(ICO2):
                ICO2.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MIC2):
                MIC2.Read(buffer, subSize);
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
                //printf("FileName = %s\n", FileName);
                printf("  ARMA: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 ARMARecord::Unload()
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

SINT32 ARMARecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(OBND);
    WRITE(FULL);
    WRITE(BMDT);

    if(MODL.IsLoaded())
        {
        if(MODL->MODL.IsLoaded())
            SaveHandler.writeSubRecord(REV32(MODL), MODL->MODL.value, MODL->MODL.GetSize());

        if(MODL->MODT.IsLoaded())
            SaveHandler.writeSubRecord(REV32(MODT), MODL->MODT.value, MODL->MODT.GetSize());

        if(MODL->MODS.IsLoaded())
            SaveHandler.writeSubRecord(REV32(MODS), MODL->MODS.value, MODL->MODS.GetSize());

        if(MODL->MODD.IsLoaded())
            SaveHandler.writeSubRecord(REV32(MODD), MODL->MODD.value, MODL->MODD.GetSize());

        }

    if(MOD2.IsLoaded())
        {
        if(MOD2->MOD2.IsLoaded())
            SaveHandler.writeSubRecord(REV32(MOD2), MOD2->MOD2.value, MOD2->MOD2.GetSize());

        if(MOD2->MO2T.IsLoaded())
            SaveHandler.writeSubRecord(REV32(MO2T), MOD2->MO2T.value, MOD2->MO2T.GetSize());

        if(MOD2->MO2S.IsLoaded())
            SaveHandler.writeSubRecord(REV32(MO2S), MOD2->MO2S.value, MOD2->MO2S.GetSize());

        }

    WRITE(ICON);
    WRITE(MICO);

    if(MOD3.IsLoaded())
        {
        if(MOD3->MOD3.IsLoaded())
            SaveHandler.writeSubRecord(REV32(MOD3), MOD3->MOD3.value, MOD3->MOD3.GetSize());

        if(MOD3->MO3T.IsLoaded())
            SaveHandler.writeSubRecord(REV32(MO3T), MOD3->MO3T.value, MOD3->MO3T.GetSize());

        if(MOD3->MO3S.IsLoaded())
            SaveHandler.writeSubRecord(REV32(MO3S), MOD3->MO3S.value, MOD3->MO3S.GetSize());

        if(MOD3->MOSD.IsLoaded())
            SaveHandler.writeSubRecord(REV32(MOSD), MOD3->MOSD.value, MOD3->MOSD.GetSize());

        }

    if(MOD4.IsLoaded())
        {
        if(MOD4->MOD4.IsLoaded())
            SaveHandler.writeSubRecord(REV32(MOD4), MOD4->MOD4.value, MOD4->MOD4.GetSize());

        if(MOD4->MO4T.IsLoaded())
            SaveHandler.writeSubRecord(REV32(MO4T), MOD4->MO4T.value, MOD4->MO4T.GetSize());

        if(MOD4->MO4S.IsLoaded())
            SaveHandler.writeSubRecord(REV32(MO4S), MOD4->MO4S.value, MOD4->MO4S.GetSize());

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

bool ARMARecord::equals(const Record *other) const
    {
    return *this == *(ARMARecord *)other;
    }
}