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
#include "REFRRecord.h"
#include "CELLRecord.h"

namespace FNV
{
REFRRecord::REFRRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

REFRRecord::REFRRecord(REFRRecord *srcRecord):
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
    NAME = srcRecord->NAME;
    XEZN = srcRecord->XEZN;
    XRGD = srcRecord->XRGD;
    XRGB = srcRecord->XRGB;
    Patrol = srcRecord->Patrol;
    XLCM = srcRecord->XLCM;
    Ownership = srcRecord->Ownership;
    XCNT = srcRecord->XCNT;
    XRDS = srcRecord->XRDS;
    XHLP = srcRecord->XHLP;
    XRAD = srcRecord->XRAD;
    XCHG = srcRecord->XCHG;
    XDCR = srcRecord->XDCR;
    XLKR = srcRecord->XLKR;
    XCLP = srcRecord->XCLP;
    RCLR = srcRecord->RCLR;
    ActivateParents = srcRecord->ActivateParents;
    XATO = srcRecord->XATO;
    XESP = srcRecord->XESP;
    XEMI = srcRecord->XEMI;
    XMBR = srcRecord->XMBR;
    XPRM = srcRecord->XPRM;
    XTRI = srcRecord->XTRI;
    XMBO = srcRecord->XMBO;
    XTEL = srcRecord->XTEL;
    MapData = srcRecord->MapData;
    AudioData = srcRecord->AudioData;
    XSRF = srcRecord->XSRF;
    XSRD = srcRecord->XSRD;
    XTRG = srcRecord->XTRG;
    XRDO = srcRecord->XRDO;
    XLOC = srcRecord->XLOC;
    Ammo = srcRecord->Ammo;
    XPWR = srcRecord->XPWR;
    XLTW = srcRecord->XLTW;
    XACT = srcRecord->XACT;
    XNDP = srcRecord->XNDP;
    XPOD = srcRecord->XPOD;
    XPTL = srcRecord->XPTL;
    XSED = srcRecord->XSED;
    Room = srcRecord->Room;
    XOCP = srcRecord->XOCP;
    XORD = srcRecord->XORD;
    XLOD = srcRecord->XLOD;
    XIBS = srcRecord->XIBS;
    XSCL = srcRecord->XSCL;
    DATA = srcRecord->DATA;

    if(srcRecord->IsOpenByDefault())//bool ONAM; //Open by Default, empty marker, written whenever fOpenByDefault is true
        IsOpenByDefault(true);
    return;
    }

REFRRecord::~REFRRecord()
    {
    //
    }

bool REFRRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    op.Accept(NAME.value);
    if(XEZN.IsLoaded())
        op.Accept(XEZN.value);
    if(Patrol.IsLoaded())
        {
        op.Accept(Patrol->INAM.value);
        for(uint32_t x = 0; x < Patrol->SCR_.value.size(); x++)
            if(Patrol->SCR_.value[x]->isSCRO)
                op.Accept(Patrol->SCR_.value[x]->reference);
        op.Accept(Patrol->TNAM.value);
        }
    if(Ownership.IsLoaded())
        op.Accept(Ownership->XOWN.value);
    for(uint32_t x = 0; x < XDCR.value.size(); x++)
        op.Accept(XDCR.value[x]->reference);
    if(XLKR.IsLoaded())
        op.Accept(XLKR.value);
    if(ActivateParents.IsLoaded())
        for(uint32_t x = 0; x < ActivateParents->XAPR.value.size(); x++)
            op.Accept(ActivateParents->XAPR.value[x]->reference);
    if(XESP.IsLoaded())
        op.Accept(XESP->parent);
    if(XEMI.IsLoaded())
        op.Accept(XEMI.value);
    if(XMBR.IsLoaded())
        op.Accept(XMBR.value);
    if(XTEL.IsLoaded())
        op.Accept(XTEL->destinationFid);
    if(MapData.IsLoaded())
        {
        if(MapData->WMI1.IsLoaded())
            op.Accept(MapData->WMI1.value);
        }
    if(AudioData.IsLoaded())
        {
        if(AudioData->CNAM.IsLoaded())
            op.Accept(AudioData->CNAM.value);
        }
    if(XTRG.IsLoaded())
        op.Accept(XTRG.value);
    if(XRDO.IsLoaded())
        op.Accept(XRDO->positionReference);
    if(XLOC.IsLoaded())
        op.Accept(XLOC->key);
    if(Ammo.IsLoaded())
        {
        if(Ammo->XAMT.IsLoaded())
            op.Accept(Ammo->XAMT.value);
        }
    for(uint32_t x = 0; x < XPWR.value.size(); x++)
        op.Accept(XPWR.value[x]->reference);
    for(uint32_t x = 0; x < XLTW.value.size(); x++)
        op.Accept(XLTW.value[x]);
    if(XNDP.IsLoaded())
        op.Accept(XNDP->navMesh);
    if(XPOD.IsLoaded())
        {
        op.Accept(XPOD->room1);
        op.Accept(XPOD->room2);
        }
    if(Room.IsLoaded())
        for(uint32_t x = 0; x < Room->XLRM.value.size(); x++)
            op.Accept(Room->XLRM.value[x]);
    if(XORD.IsLoaded())
        {
        op.Accept(XORD->right);
        op.Accept(XORD->left);
        op.Accept(XORD->bottom);
        op.Accept(XORD->top);
        }

    return op.Stop();
    }

bool REFRRecord::IsUseDefault()
    {
    return (XACT.value & fIsUseDefault) != 0;
    }

void REFRRecord::IsUseDefault(bool value)
    {
    SETBIT(XACT.value, fIsUseDefault, value);
    }

bool REFRRecord::IsActivate()
    {
    return (XACT.value & fIsActivate) != 0;
    }

void REFRRecord::IsActivate(bool value)
    {
    SETBIT(XACT.value, fIsActivate, value);
    }

bool REFRRecord::IsOpen()
    {
    return (XACT.value & fIsOpen) != 0;
    }

void REFRRecord::IsOpen(bool value)
    {
    SETBIT(XACT.value, fIsOpen, value);
    }

bool REFRRecord::IsOpenByDefault()
    {
    return (XACT.value & fIsOpenByDefault) != 0;
    }

void REFRRecord::IsOpenByDefault(bool value)
    {
    SETBIT(XACT.value, fIsOpenByDefault, value);
    }

bool REFRRecord::IsActionFlagMask(uint32_t Mask, bool Exact)
    {
    return Exact ? ((XACT.value & Mask) == Mask) : ((XACT.value & Mask) != 0);
    }

void REFRRecord::SetActionFlagMask(uint32_t Mask)
    {
    XACT.value = Mask;
    }

bool REFRRecord::IsOppositeParent()
    {
    if(!XESP.IsLoaded()) return false;
    return (XESP->flags & fIsOppositeParent) != 0;
    }

void REFRRecord::IsOppositeParent(bool value)
    {
    if(!XESP.IsLoaded()) return;
    SETBIT(XESP->flags, fIsOppositeParent, value);
    }

bool REFRRecord::IsPopIn()
    {
    if(!XESP.IsLoaded()) return false;
    return (XESP->flags & fIsPopIn) != 0;
    }

void REFRRecord::IsPopIn(bool value)
    {
    if(!XESP.IsLoaded()) return;
    SETBIT(XESP->flags, fIsPopIn, value);
    }

bool REFRRecord::IsParentFlagMask(uint8_t Mask, bool Exact)
    {
    if(!XESP.IsLoaded()) return false;
    return Exact ? ((XESP->flags & Mask) == Mask) : ((XESP->flags & Mask) != 0);
    }

void REFRRecord::SetParentFlagMask(uint8_t Mask)
    {
    XESP.Load();
    XESP->flags = Mask;
    }

bool REFRRecord::IsNoAlarm()
    {
    if(!XTEL.IsLoaded()) return false;
    return (XTEL->flags & fIsNoAlarm) != 0;
    }

void REFRRecord::IsNoAlarm(bool value)
    {
    if(!XTEL.IsLoaded()) return;
    SETBIT(XTEL->flags, fIsNoAlarm, value);
    }

bool REFRRecord::IsDestFlagMask(uint32_t Mask, bool Exact)
    {
    if(!XTEL.IsLoaded()) return false;
    return Exact ? ((XTEL->flags & Mask) == Mask) : ((XTEL->flags & Mask) != 0);
    }

void REFRRecord::SetDestFlagMask(uint32_t Mask)
    {
    XTEL.Load();
    XTEL->flags = Mask;
    }

bool REFRRecord::IsVisible()
    {
    if(!MapData.IsLoaded()) return false;
    return (MapData->FNAM.value & fIsVisible) != 0;
    }

void REFRRecord::IsVisible(bool value)
    {
    if(!MapData.IsLoaded()) return;
    SETBIT(MapData->FNAM.value, fIsVisible, value);
    }

bool REFRRecord::IsCanTravelTo()
    {
    if(!MapData.IsLoaded()) return false;
    return (MapData->FNAM.value & fIsCanTravelTo) != 0;
    }

void REFRRecord::IsCanTravelTo(bool value)
    {
    if(!MapData.IsLoaded()) return;
    SETBIT(MapData->FNAM.value, fIsCanTravelTo, value);
    }

bool REFRRecord::IsMapFlagMask(uint8_t Mask, bool Exact)
    {
    if(!MapData.IsLoaded()) return false;
    return Exact ? ((MapData->FNAM.value & Mask) == Mask) : ((MapData->FNAM.value & Mask) != 0);
    }

void REFRRecord::SetMapFlagMask(uint8_t Mask)
    {
    MapData.Load();
    MapData->FNAM.value = Mask;
    }

bool REFRRecord::IsLeveledLock()
    {
    if(!XLOC.IsLoaded()) return false;
    return (XLOC->flags & fIsLeveledLock) != 0;
    }

void REFRRecord::IsLeveledLock(bool value)
    {
    if(!XLOC.IsLoaded()) return;
    SETBIT(XLOC->flags, fIsLeveledLock, value);
    }

bool REFRRecord::IsLockFlagMask(uint8_t Mask, bool Exact)
    {
    if(!XLOC.IsLoaded()) return false;
    return Exact ? ((XLOC->flags & Mask) == Mask) : ((XLOC->flags & Mask) != 0);
    }

void REFRRecord::SetLockFlagMask(uint8_t Mask)
    {
    XLOC.Load();
    XLOC->flags = Mask;
    }

bool REFRRecord::IsNone()
    {
    if(!XPRM.IsLoaded()) return false;
    return XPRM->type == eNone;
    }

void REFRRecord::IsNone(bool value)
    {
    if(!XPRM.IsLoaded()) return;
    XPRM->type = value ? eNone : eBox;
    }

bool REFRRecord::IsBox()
    {
    if(!XPRM.IsLoaded()) return false;
    return XPRM->type == eBox;
    }

void REFRRecord::IsBox(bool value)
    {
    if(!XPRM.IsLoaded()) return;
    XPRM->type = value ? eBox : eNone;
    }

bool REFRRecord::IsSphere()
    {
    if(!XPRM.IsLoaded()) return false;
    return XPRM->type == eSphere;
    }

void REFRRecord::IsSphere(bool value)
    {
    if(!XPRM.IsLoaded()) return;
    XPRM->type = value ? eSphere : eNone;
    }

bool REFRRecord::IsPortalBox()
    {
    if(!XPRM.IsLoaded()) return false;
    return XPRM->type == ePortalBox;
    }

void REFRRecord::IsPortalBox(bool value)
    {
    if(!XPRM.IsLoaded()) return;
    XPRM->type = value ? ePortalBox : eNone;
    }

bool REFRRecord::IsPrimitiveType(uint32_t Type)
    {
    if(!XPRM.IsLoaded()) return false;
    return XPRM->type == Type;
    }

void REFRRecord::SetPrimitiveType(uint32_t Type)
    {
    XPRM.Load();
    XPRM->type = Type;
    }

bool REFRRecord::IsUnidentified()
    {
    return XTRI.value == eUnidentified;
    }

void REFRRecord::IsUnidentified(bool value)
    {
    XTRI.value = value ? eUnidentified : eStatic;
    }

bool REFRRecord::IsStatic()
    {
    return XTRI.value == eStatic;
    }

void REFRRecord::IsStatic(bool value)
    {
    XTRI.value = value ? eStatic : eUnidentified;
    }

bool REFRRecord::IsAnimStatic()
    {
    return XTRI.value == eAnimStatic;
    }

void REFRRecord::IsAnimStatic(bool value)
    {
    XTRI.value = value ? eAnimStatic : eUnidentified;
    }

bool REFRRecord::IsTransparent()
    {
    return XTRI.value == eTransparent;
    }

void REFRRecord::IsTransparent(bool value)
    {
    XTRI.value = value ? eTransparent : eUnidentified;
    }

bool REFRRecord::IsClutter()
    {
    return XTRI.value == eClutter;
    }

void REFRRecord::IsClutter(bool value)
    {
    XTRI.value = value ? eClutter : eUnidentified;
    }

bool REFRRecord::IsWeapon()
    {
    return XTRI.value == eWeapon;
    }

void REFRRecord::IsWeapon(bool value)
    {
    XTRI.value = value ? eWeapon : eUnidentified;
    }

bool REFRRecord::IsProjectile()
    {
    return XTRI.value == eProjectile;
    }

void REFRRecord::IsProjectile(bool value)
    {
    XTRI.value = value ? eProjectile : eUnidentified;
    }

bool REFRRecord::IsSpell()
    {
    return XTRI.value == eSpell;
    }

void REFRRecord::IsSpell(bool value)
    {
    XTRI.value = value ? eSpell : eUnidentified;
    }

bool REFRRecord::IsBiped()
    {
    return XTRI.value == eBiped;
    }

void REFRRecord::IsBiped(bool value)
    {
    XTRI.value = value ? eBiped : eUnidentified;
    }

bool REFRRecord::IsTrees()
    {
    return XTRI.value == eTrees;
    }

void REFRRecord::IsTrees(bool value)
    {
    XTRI.value = value ? eTrees : eUnidentified;
    }

bool REFRRecord::IsProps()
    {
    return XTRI.value == eProps;
    }

void REFRRecord::IsProps(bool value)
    {
    XTRI.value = value ? eProps : eUnidentified;
    }

bool REFRRecord::IsWater()
    {
    return XTRI.value == eWater;
    }

void REFRRecord::IsWater(bool value)
    {
    XTRI.value = value ? eWater : eUnidentified;
    }

bool REFRRecord::IsTrigger()
    {
    return XTRI.value == eTrigger;
    }

void REFRRecord::IsTrigger(bool value)
    {
    XTRI.value = value ? eTrigger : eUnidentified;
    }

bool REFRRecord::IsTerrain()
    {
    return XTRI.value == eTerrain;
    }

void REFRRecord::IsTerrain(bool value)
    {
    XTRI.value = value ? eTerrain : eUnidentified;
    }

bool REFRRecord::IsTrap()
    {
    return XTRI.value == eTrap;
    }

void REFRRecord::IsTrap(bool value)
    {
    XTRI.value = value ? eTrap : eUnidentified;
    }

bool REFRRecord::IsNonCollidable()
    {
    return XTRI.value == eNonCollidable;
    }

void REFRRecord::IsNonCollidable(bool value)
    {
    XTRI.value = value ? eNonCollidable : eUnidentified;
    }

bool REFRRecord::IsCloudTrap()
    {
    return XTRI.value == eCloudTrap;
    }

void REFRRecord::IsCloudTrap(bool value)
    {
    XTRI.value = value ? eCloudTrap : eUnidentified;
    }

bool REFRRecord::IsGround()
    {
    return XTRI.value == eGround;
    }

void REFRRecord::IsGround(bool value)
    {
    XTRI.value = value ? eGround : eUnidentified;
    }

bool REFRRecord::IsPortal()
    {
    return XTRI.value == ePortal;
    }

void REFRRecord::IsPortal(bool value)
    {
    XTRI.value = value ? ePortal : eUnidentified;
    }

bool REFRRecord::IsDebrisSmall()
    {
    return XTRI.value == eDebrisSmall;
    }

void REFRRecord::IsDebrisSmall(bool value)
    {
    XTRI.value = value ? eDebrisSmall : eUnidentified;
    }

bool REFRRecord::IsDebrisLarge()
    {
    return XTRI.value == eDebrisLarge;
    }

void REFRRecord::IsDebrisLarge(bool value)
    {
    XTRI.value = value ? eDebrisLarge : eUnidentified;
    }

bool REFRRecord::IsAcousticSpace()
    {
    return XTRI.value == eAcousticSpace;
    }

void REFRRecord::IsAcousticSpace(bool value)
    {
    XTRI.value = value ? eAcousticSpace : eUnidentified;
    }

bool REFRRecord::IsActorZone()
    {
    return XTRI.value == eActorZone;
    }

void REFRRecord::IsActorZone(bool value)
    {
    XTRI.value = value ? eActorZone : eUnidentified;
    }

bool REFRRecord::IsProjectileZone()
    {
    return XTRI.value == eProjectileZone;
    }

void REFRRecord::IsProjectileZone(bool value)
    {
    XTRI.value = value ? eProjectileZone : eUnidentified;
    }

bool REFRRecord::IsGasTrap()
    {
    return XTRI.value == eGasTrap;
    }

void REFRRecord::IsGasTrap(bool value)
    {
    XTRI.value = value ? eGasTrap : eUnidentified;
    }

bool REFRRecord::IsShellCasing()
    {
    return XTRI.value == eShellCasing;
    }

void REFRRecord::IsShellCasing(bool value)
    {
    XTRI.value = value ? eShellCasing : eUnidentified;
    }

bool REFRRecord::IsTransparentSmall()
    {
    return XTRI.value == eTransparentSmall;
    }

void REFRRecord::IsTransparentSmall(bool value)
    {
    XTRI.value = value ? eTransparentSmall : eUnidentified;
    }

bool REFRRecord::IsInvisibleWall()
    {
    return XTRI.value == eInvisibleWall;
    }

void REFRRecord::IsInvisibleWall(bool value)
    {
    XTRI.value = value ? eInvisibleWall : eUnidentified;
    }

bool REFRRecord::IsTransparentSmallAnim()
    {
    return XTRI.value == eTransparentSmallAnim;
    }

void REFRRecord::IsTransparentSmallAnim(bool value)
    {
    XTRI.value = value ? eTransparentSmallAnim : eUnidentified;
    }

bool REFRRecord::IsDeadBip()
    {
    return XTRI.value == eDeadBip;
    }

void REFRRecord::IsDeadBip(bool value)
    {
    XTRI.value = value ? eDeadBip : eUnidentified;
    }

bool REFRRecord::IsCharController()
    {
    return XTRI.value == eCharController;
    }

void REFRRecord::IsCharController(bool value)
    {
    XTRI.value = value ? eCharController : eUnidentified;
    }

bool REFRRecord::IsAvoidBox()
    {
    return XTRI.value == eAvoidBox;
    }

void REFRRecord::IsAvoidBox(bool value)
    {
    XTRI.value = value ? eAvoidBox : eUnidentified;
    }

bool REFRRecord::IsCollisionBox()
    {
    return XTRI.value == eCollisionBox;
    }

void REFRRecord::IsCollisionBox(bool value)
    {
    XTRI.value = value ? eCollisionBox : eUnidentified;
    }

bool REFRRecord::IsCameraSphere()
    {
    return XTRI.value == eCameraSphere;
    }

void REFRRecord::IsCameraSphere(bool value)
    {
    XTRI.value = value ? eCameraSphere : eUnidentified;
    }

bool REFRRecord::IsDoorDetection()
    {
    return XTRI.value == eDoorDetection;
    }

void REFRRecord::IsDoorDetection(bool value)
    {
    XTRI.value = value ? eDoorDetection : eUnidentified;
    }

bool REFRRecord::IsCameraPick()
    {
    return XTRI.value == eCameraPick;
    }

void REFRRecord::IsCameraPick(bool value)
    {
    XTRI.value = value ? eCameraPick : eUnidentified;
    }

bool REFRRecord::IsItemPick()
    {
    return XTRI.value == eItemPick;
    }

void REFRRecord::IsItemPick(bool value)
    {
    XTRI.value = value ? eItemPick : eUnidentified;
    }

bool REFRRecord::IsLineOfSight()
    {
    return XTRI.value == eLineOfSight;
    }

void REFRRecord::IsLineOfSight(bool value)
    {
    XTRI.value = value ? eLineOfSight : eUnidentified;
    }

bool REFRRecord::IsPathPick()
    {
    return XTRI.value == ePathPick;
    }

void REFRRecord::IsPathPick(bool value)
    {
    XTRI.value = value ? ePathPick : eUnidentified;
    }

bool REFRRecord::IsCustomPick1()
    {
    return XTRI.value == eCustomPick1;
    }

void REFRRecord::IsCustomPick1(bool value)
    {
    XTRI.value = value ? eCustomPick1 : eUnidentified;
    }

bool REFRRecord::IsCustomPick2()
    {
    return XTRI.value == eCustomPick2;
    }

void REFRRecord::IsCustomPick2(bool value)
    {
    XTRI.value = value ? eCustomPick2 : eUnidentified;
    }

bool REFRRecord::IsSpellExplosion()
    {
    return XTRI.value == eSpellExplosion;
    }

void REFRRecord::IsSpellExplosion(bool value)
    {
    XTRI.value = value ? eSpellExplosion : eUnidentified;
    }

bool REFRRecord::IsDroppingPick()
    {
    return XTRI.value == eDroppingPick;
    }

void REFRRecord::IsDroppingPick(bool value)
    {
    XTRI.value = value ? eDroppingPick : eUnidentified;
    }

bool REFRRecord::IsCollisionType(uint32_t Type)
    {
    return XTRI.value == Type;
    }

void REFRRecord::SetCollisionType(uint32_t Type)
    {
    XTRI.value = Type;
    }

bool REFRRecord::IsMarkerNone()
    {
    if(!MapData.IsLoaded()) return false;
    return MapData->TNAM.value.markerType == eMarkerNone;
    }

void REFRRecord::IsMarkerNone(bool value)
    {
    if(!MapData.IsLoaded()) return;
    MapData->TNAM.value.markerType = value ? eMarkerNone : eCity;
    }

bool REFRRecord::IsCity()
    {
    if(!MapData.IsLoaded()) return false;
    return MapData->TNAM.value.markerType == eCity;
    }

void REFRRecord::IsCity(bool value)
    {
    if(!MapData.IsLoaded()) return;
    MapData->TNAM.value.markerType = value ? eCity : eMarkerNone;
    }

bool REFRRecord::IsSettlement()
    {
    if(!MapData.IsLoaded()) return false;
    return MapData->TNAM.value.markerType == eSettlement;
    }

void REFRRecord::IsSettlement(bool value)
    {
    if(!MapData.IsLoaded()) return;
    MapData->TNAM.value.markerType = value ? eSettlement : eMarkerNone;
    }

bool REFRRecord::IsEncampment()
    {
    if(!MapData.IsLoaded()) return false;
    return MapData->TNAM.value.markerType == eEncampment;
    }

void REFRRecord::IsEncampment(bool value)
    {
    if(!MapData.IsLoaded()) return;
    MapData->TNAM.value.markerType = value ? eEncampment : eMarkerNone;
    }

bool REFRRecord::IsNaturalLandmark()
    {
    if(!MapData.IsLoaded()) return false;
    return MapData->TNAM.value.markerType == eNaturalLandmark;
    }

void REFRRecord::IsNaturalLandmark(bool value)
    {
    if(!MapData.IsLoaded()) return;
    MapData->TNAM.value.markerType = value ? eNaturalLandmark : eMarkerNone;
    }

bool REFRRecord::IsCave()
    {
    if(!MapData.IsLoaded()) return false;
    return MapData->TNAM.value.markerType == eCave;
    }

void REFRRecord::IsCave(bool value)
    {
    if(!MapData.IsLoaded()) return;
    MapData->TNAM.value.markerType = value ? eCave : eMarkerNone;
    }

bool REFRRecord::IsFactory()
    {
    if(!MapData.IsLoaded()) return false;
    return MapData->TNAM.value.markerType == eFactory;
    }

void REFRRecord::IsFactory(bool value)
    {
    if(!MapData.IsLoaded()) return;
    MapData->TNAM.value.markerType = value ? eFactory : eMarkerNone;
    }

bool REFRRecord::IsMonument()
    {
    if(!MapData.IsLoaded()) return false;
    return MapData->TNAM.value.markerType == eMonument;
    }

void REFRRecord::IsMonument(bool value)
    {
    if(!MapData.IsLoaded()) return;
    MapData->TNAM.value.markerType = value ? eMonument : eMarkerNone;
    }

bool REFRRecord::IsMilitary()
    {
    if(!MapData.IsLoaded()) return false;
    return MapData->TNAM.value.markerType == eMilitary;
    }

void REFRRecord::IsMilitary(bool value)
    {
    if(!MapData.IsLoaded()) return;
    MapData->TNAM.value.markerType = value ? eMilitary : eMarkerNone;
    }

bool REFRRecord::IsOffice()
    {
    if(!MapData.IsLoaded()) return false;
    return MapData->TNAM.value.markerType == eOffice;
    }

void REFRRecord::IsOffice(bool value)
    {
    if(!MapData.IsLoaded()) return;
    MapData->TNAM.value.markerType = value ? eOffice : eMarkerNone;
    }

bool REFRRecord::IsTownRuins()
    {
    if(!MapData.IsLoaded()) return false;
    return MapData->TNAM.value.markerType == eTownRuins;
    }

void REFRRecord::IsTownRuins(bool value)
    {
    if(!MapData.IsLoaded()) return;
    MapData->TNAM.value.markerType = value ? eTownRuins : eMarkerNone;
    }

bool REFRRecord::IsUrbanRuins()
    {
    if(!MapData.IsLoaded()) return false;
    return MapData->TNAM.value.markerType == eUrbanRuins;
    }

void REFRRecord::IsUrbanRuins(bool value)
    {
    if(!MapData.IsLoaded()) return;
    MapData->TNAM.value.markerType = value ? eUrbanRuins : eMarkerNone;
    }

bool REFRRecord::IsSewerRuins()
    {
    if(!MapData.IsLoaded()) return false;
    return MapData->TNAM.value.markerType == eSewerRuins;
    }

void REFRRecord::IsSewerRuins(bool value)
    {
    if(!MapData.IsLoaded()) return;
    MapData->TNAM.value.markerType = value ? eSewerRuins : eMarkerNone;
    }

bool REFRRecord::IsMetro()
    {
    if(!MapData.IsLoaded()) return false;
    return MapData->TNAM.value.markerType == eMetro;
    }

void REFRRecord::IsMetro(bool value)
    {
    if(!MapData.IsLoaded()) return;
    MapData->TNAM.value.markerType = value ? eMetro : eMarkerNone;
    }

bool REFRRecord::IsVault()
    {
    if(!MapData.IsLoaded()) return false;
    return MapData->TNAM.value.markerType == eVault;
    }

void REFRRecord::IsVault(bool value)
    {
    if(!MapData.IsLoaded()) return;
    MapData->TNAM.value.markerType = value ? eVault : eMarkerNone;
    }

bool REFRRecord::IsMapType(uint8_t Type)
    {
    if(!MapData.IsLoaded()) return false;
    return MapData->TNAM.value.markerType == Type;
    }

void REFRRecord::SetMapType(uint8_t Type)
    {
    MapData.Load();
    MapData->TNAM.value.markerType = Type;
    }

bool REFRRecord::IsRadius()
    {
    if(!XRDO.IsLoaded()) return false;
    return XRDO->rangeType == eRadius;
    }

void REFRRecord::IsRadius(bool value)
    {
    if(!XRDO.IsLoaded()) return;
    XRDO->rangeType = value ? eRadius : eEverywhere;
    }

bool REFRRecord::IsEverywhere()
    {
    if(!XRDO.IsLoaded()) return false;
    return XRDO->rangeType == eEverywhere;
    }

void REFRRecord::IsEverywhere(bool value)
    {
    if(!XRDO.IsLoaded()) return;
    XRDO->rangeType = value ? eEverywhere : eRadius;
    }

bool REFRRecord::IsWorldAndLinkedInteriors()
    {
    if(!XRDO.IsLoaded()) return false;
    return XRDO->rangeType == eWorldAndLinkedInteriors;
    }

void REFRRecord::IsWorldAndLinkedInteriors(bool value)
    {
    if(!XRDO.IsLoaded()) return;
    XRDO->rangeType = value ? eWorldAndLinkedInteriors : eRadius;
    }

bool REFRRecord::IsLinkedInteriors()
    {
    if(!XRDO.IsLoaded()) return false;
    return XRDO->rangeType == eLinkedInteriors;
    }

void REFRRecord::IsLinkedInteriors(bool value)
    {
    if(!XRDO.IsLoaded()) return;
    XRDO->rangeType = value ? eLinkedInteriors : eRadius;
    }

bool REFRRecord::IsCurrentCellOnly()
    {
    if(!XRDO.IsLoaded()) return false;
    return XRDO->rangeType == eCurrentCellOnly;
    }

void REFRRecord::IsCurrentCellOnly(bool value)
    {
    if(!XRDO.IsLoaded()) return;
    XRDO->rangeType = value ? eCurrentCellOnly : eRadius;
    }

bool REFRRecord::IsBroadcastType(uint32_t Type)
    {
    if(!XRDO.IsLoaded()) return false;
    return XRDO->rangeType == Type;
    }

void REFRRecord::SetBroadcastType(uint32_t Type)
    {
    XRDO.Load();
    XRDO->rangeType = Type;
    }

uint32_t REFRRecord::GetType()
    {
    return REV32(REFR);
    }

char * REFRRecord::GetStrType()
    {
    return "REFR";
    }

int32_t REFRRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
    {
    uint32_t subType = 0;
    uint32_t subSize = 0;
    uint32_t lastChunk = 0;
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
            case REV32(NAME):
                NAME.Read(buffer, subSize);
                break;
            case REV32(XEZN):
                XEZN.Read(buffer, subSize);
                break;
            case REV32(XRGD):
                XRGD.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(XRGB):
                XRGB.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(XPRD):
                Patrol.Load();
                Patrol->XPRD.Read(buffer, subSize);
                break;
            case REV32(XPPA):
                //XPPA, Patrol Script Marker (Empty)
                lastChunk = REV32(XPPA);
                break;
            case REV32(INAM):
                Patrol.Load();
                Patrol->INAM.Read(buffer, subSize);
                break;
            case REV32(SCHR):
                Patrol.Load();
                Patrol->SCHR.Read(buffer, subSize);
                break;
            case REV32(SCDA):
                Patrol.Load();
                Patrol->SCDA.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(SCTX):
                Patrol.Load();
                Patrol->SCTX.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(SLSD):
                Patrol.Load();
                Patrol->VARS.value.push_back(new GENVARS);
                Patrol->VARS.value.back()->SLSD.Read(buffer, subSize);
                break;
            case REV32(SCVR):
                Patrol.Load();
                if(Patrol->VARS.value.size() == 0)
                    Patrol->VARS.value.push_back(new GENVARS);
                Patrol->VARS.value.back()->SCVR.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(SCRO):
                Patrol.Load();
                Patrol->SCR_.Read(buffer, subSize);
                Patrol->SCR_.value.back()->isSCRO = true;
                break;
            case REV32(SCRV):
                Patrol.Load();
                Patrol->SCR_.Read(buffer, subSize);
                Patrol->SCR_.value.back()->isSCRO = false;
                break;
            case REV32(TNAM):
                switch(lastChunk)
                    {
                    case REV32(XPPA):
                        Patrol.Load();
                        Patrol->TNAM.Read(buffer, subSize);
                        break;
                    case REV32(XMRK):
                        MapData.Load();
                        MapData->TNAM.Read(buffer, subSize);
                        break;
                    default:
                        printer("  REFR: %08X - Unexpected TNAM chunk\n", formID);
                        printer("  Size = %i\n", subSize);
                        printer("  CurPos = %04x\n\n", buffer - 6);
                        buffer += subSize;
                        break;
                    }
                break;
            case REV32(XLCM):
                XLCM.Read(buffer, subSize);
                break;
            case REV32(XOWN):
                Ownership.Load();
                Ownership->XOWN.Read(buffer, subSize);
                break;
            case REV32(XRNK):
                Ownership.Load();
                Ownership->XRNK.Read(buffer, subSize);
                break;
            case REV32(XCNT):
                XCNT.Read(buffer, subSize);
                break;
            case REV32(XRDS):
                XRDS.Read(buffer, subSize);
                break;
            case REV32(XHLP):
                XHLP.Read(buffer, subSize);
                break;
            case REV32(XRAD):
                XRAD.Read(buffer, subSize);
                break;
            case REV32(XCHG):
                XCHG.Read(buffer, subSize);
                break;
            case REV32(XDCR):
                XDCR.Read(buffer, subSize);
                break;
            case REV32(XLKR):
                XLKR.Read(buffer, subSize);
                break;
            case REV32(XCLP):
                XCLP.Read(buffer, subSize);
                break;
            case REV32(RCLR):
                RCLR.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(XAPD):
                ActivateParents.Load();
                ActivateParents->XAPD.Read(buffer, subSize);
                break;
            case REV32(XAPR):
                ActivateParents.Load();
                ActivateParents->XAPR.Read(buffer, subSize);
                break;
            case REV32(XATO):
                XATO.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(XESP):
                XESP.Read(buffer, subSize);
                break;
            case REV32(XEMI):
                XEMI.Read(buffer, subSize);
                break;
            case REV32(XMBR):
                XMBR.Read(buffer, subSize);
                break;
            case REV32(XPRM):
                XPRM.Read(buffer, subSize);
                break;
            case REV32(XTRI):
                XTRI.Read(buffer, subSize);
                break;
            case REV32(XMBO):
                XMBO.Read(buffer, subSize);
                break;
            case REV32(XTEL):
                XTEL.Read(buffer, subSize);
                break;
            case REV32(FNAM):
                MapData.Load();
                MapData->FNAM.Read(buffer, subSize);
                break;
            case REV32(WMI1):
                MapData.Load();
                MapData->WMI1.Read(buffer, subSize);
                break;
            case REV32(XMRK):
                lastChunk = REV32(XMRK);
                break;
            case REV32(MMRK):
                lastChunk = REV32(MMRK);
                break;
            case REV32(FULL):
                switch(lastChunk)
                    {
                    case REV32(XMRK):
                        MapData.Load();
                        MapData->FULL.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case REV32(MMRK):
                        AudioData.Load();
                        AudioData->FULL.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    default:
                        printer("  REFR: %08X - Unexpected FULL chunk\n", formID);
                        printer("  Size = %i\n", subSize);
                        printer("  CurPos = %04x\n\n", buffer - 6);
                        buffer += subSize;
                        break;
                    }
                break;
            case REV32(CNAM):
                AudioData.Load();
                AudioData->CNAM.Read(buffer, subSize);
                break;
            case REV32(BNAM):
                AudioData.Load();
                AudioData->BNAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MNAM):
                AudioData.Load();
                AudioData->MNAM.Read(buffer, subSize);
                break;
            case REV32(NNAM):
                AudioData.Load();
                AudioData->NNAM.Read(buffer, subSize);
                break;
            case REV32(XSRF):
                XSRF.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(XSRD):
                XSRD.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(XTRG):
                XTRG.Read(buffer, subSize);
                break;
            case REV32(XRDO):
                XRDO.Read(buffer, subSize);
                break;
            case REV32(XLOC):
                XLOC.Read(buffer, subSize);
                break;
            case REV32(XAMT):
                Ammo.Load();
                Ammo->XAMT.Read(buffer, subSize);
                break;
            case REV32(XAMC):
                Ammo.Load();
                Ammo->XAMC.Read(buffer, subSize);
                break;
            case REV32(XPWR):
                XPWR.Read(buffer, subSize);
                break;
            case REV32(XLTW):
                XLTW.Read(buffer, subSize);
                break;
            case REV32(XACT):
                XACT.Read(buffer, subSize);
                break;
            case REV32(XNDP):
                XNDP.Read(buffer, subSize);
                break;
            case REV32(XPOD):
                XPOD.Read(buffer, subSize);
                break;
            case REV32(XPTL):
                XPTL.Read(buffer, subSize);
                break;
            case REV32(XSED):
                XSED.Read(buffer, subSize);
                break;
            case REV32(XRMR):
                Room.Load();
                Room->XRMR.Read(buffer, subSize);
                break;
            case REV32(XLRM):
                Room.Load();
                Room->XLRM.Read(buffer, subSize);
                break;
            case REV32(XOCP):
                XOCP.Read(buffer, subSize);
                break;
            case REV32(XORD):
                XORD.Read(buffer, subSize);
                break;
            case REV32(XLOD):
                XLOD.Read(buffer, subSize);
                break;
            case REV32(XIBS):
                //XIBS.Read(buffer, subSize);
                XIBS.value = 1;
                break;
            case REV32(XMBP):
                //XMBP.Read(buffer, subSize);
                XMBP.Load();
                break;
            case REV32(XSCL):
                XSCL.Read(buffer, subSize);
                break;
            case REV32(ONAM):
                IsOpenByDefault(true);
                buffer += subSize;
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  REFR: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t REFRRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);

    EDID.Unload();
    NAME.Unload();
    XEZN.Unload();
    XRGD.Unload();
    XRGB.Unload();
    Patrol.Unload();
    XLCM.Unload();
    Ownership.Unload();
    XCNT.Unload();
    XRDS.Unload();
    XHLP.Unload();
    XRAD.Unload();
    XCHG.Unload();
    XDCR.Unload();
    XLKR.Unload();
    XCLP.Unload();
    RCLR.Unload();
    ActivateParents.Unload();
    XATO.Unload();
    XESP.Unload();
    XEMI.Unload();
    XMBR.Unload();
    XPRM.Unload();
    XTRI.Unload();
    XMBO.Unload();
    XTEL.Unload();
    MapData.Unload();
    AudioData.Unload();
    XSRF.Unload();
    XSRD.Unload();
    XTRG.Unload();
    XRDO.Unload();
    XLOC.Unload();
    Ammo.Unload();
    XPWR.Unload();
    XLTW.Unload();
    XACT.Unload();
    XNDP.Unload();
    XPOD.Unload();
    XPTL.Unload();
    XSED.Unload();
    Room.Unload();
    XOCP.Unload();
    XORD.Unload();
    XLOD.Unload();
    XIBS.Unload();
    XMBP.Unload();
    XSCL.Unload();
    DATA.Unload();
    return 1;
    }

int32_t REFRRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(NAME);
    WRITE(XEZN);
    WRITE(XRGD);
    WRITE(XRGB);
    Patrol.Write(writer);
    WRITE(XLCM);
    Ownership.Write(writer);
    WRITE(XCNT);
    WRITE(XRDS);
    WRITE(XHLP);
    WRITE(XRAD);
    WRITE(XCHG);
    WRITE(XDCR);
    WRITE(XLKR);
    WRITE(XCLP);
    WRITE(RCLR);
    ActivateParents.Write(writer);
    WRITE(XATO);
    WRITE(XESP);
    WRITE(XEMI);
    WRITE(XMBR);
    WRITE(XPRM);
    WRITE(XTRI);
    WRITE(XMBO);
    WRITE(XTEL);
    MapData.Write(writer);
    AudioData.Write(writer);
    WRITE(XSRF);
    WRITE(XSRD);
    WRITE(XTRG);
    WRITE(XRDO);
    WRITE(XLOC);
    Ammo.Write(writer);
    WRITE(XPWR);
    WRITE(XLTW);
    WRITE(XACT);
    WRITE(XNDP);
    WRITE(XPOD);
    WRITE(XPTL);
    WRITE(XSED);
    Room.Write(writer);
    WRITE(XOCP);
    WRITE(XORD);
    WRITE(XLOD);
    if(IsOpenByDefault())
        WRITEEMPTY(ONAM);
    if(XIBS.IsLoaded())
        WRITEEMPTY(XIBS);
    if(XMBP.IsLoaded())
        WRITEEMPTY(XMBP);
    WRITE(XSCL);
    WRITE(DATA);
    return -1;
    }

bool REFRRecord::operator ==(const REFRRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            NAME == other.NAME &&
            XEZN == other.XEZN &&
            XRGD == other.XRGD &&
            XRGB == other.XRGB &&
            Patrol == other.Patrol &&
            XLCM == other.XLCM &&
            Ownership == other.Ownership &&
            XCNT == other.XCNT &&
            XRDS == other.XRDS &&
            XHLP == other.XHLP &&
            XRAD == other.XRAD &&
            XCHG == other.XCHG &&
            XDCR == other.XDCR &&
            XLKR == other.XLKR &&
            XCLP == other.XCLP &&
            RCLR == other.RCLR &&
            ActivateParents == other.ActivateParents &&
            XATO.equals(other.XATO) &&
            XESP == other.XESP &&
            XEMI == other.XEMI &&
            XMBR == other.XMBR &&
            XPRM == other.XPRM &&
            XTRI == other.XTRI &&
            XMBO == other.XMBO &&
            XTEL == other.XTEL &&
            MapData == other.MapData &&
            AudioData == other.AudioData &&
            XSRF == other.XSRF &&
            XSRD == other.XSRD &&
            XTRG == other.XTRG &&
            XRDO == other.XRDO &&
            XLOC == other.XLOC &&
            Ammo == other.Ammo &&
            XPWR == other.XPWR &&
            XLTW == other.XLTW &&
            XACT == other.XACT &&
            XNDP == other.XNDP &&
            XPOD == other.XPOD &&
            XPTL == other.XPTL &&
            XSED == other.XSED &&
            Room == other.Room &&
            XOCP == other.XOCP &&
            XORD == other.XORD &&
            XLOD == other.XLOD &&
            XIBS == other.XIBS &&
            XSCL == other.XSCL &&
            DATA == other.DATA);
    }

bool REFRRecord::operator !=(const REFRRecord &other) const
    {
    return !(*this == other);
    }

bool REFRRecord::equals(Record *other)
    {
    return *this == *(REFRRecord *)other;
    }

bool REFRRecord::deep_equals(Record *master, RecordOp &read_self, RecordOp &read_master, boost::unordered_set<Record *> &identical_records)
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