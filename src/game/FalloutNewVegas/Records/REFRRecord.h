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
#include "common/Common.h"
#include "common/GenericRecord.h"
#include "../FNVRecord.h"

namespace FNV
{
class REFRRecord : public FNVRecord //Placed Object
    {
    private:
        enum xprmTypes
            {
            eNone = 0,
            eBox,
            eSphere,
            ePortalBox
            };

        enum xtriTypes
            {
            eUnidentified = 0,
            eStatic,
            eAnimStatic,
            eTransparent,
            eClutter,
            eWeapon,
            eProjectile,
            eSpell,
            eBiped,
            eTrees,
            eProps,
            eWater,
            eTrigger,
            eTerrain,
            eTrap,
            eNonCollidable,
            eCloudTrap,
            eGround,
            ePortal,
            eDebrisSmall,
            eDebrisLarge,
            eAcousticSpace,
            eActorZone,
            eProjectileZone,
            eGasTrap,
            eShellCasing,
            eTransparentSmall,
            eInvisibleWall,
            eTransparentSmallAnim,
            eDeadBip,
            eCharController,
            eAvoidBox,
            eCollisionBox,
            eCameraSphere,
            eDoorDetection,
            eCameraPick,
            eItemPick,
            eLineOfSight,
            ePathPick,
            eCustomPick1,
            eCustomPick2,
            eSpellExplosion,
            eDroppingPick
            };

        enum xtelFlags
            {
            fIsNoAlarm = 0x00000001
            };

        enum fnamFlags
            {
            fIsVisible     = 0x00000001,
            fIsCanTravelTo = 0x00000002
            };

        enum markerTypeTypes
            {
            eMarkerNone = 0,
            eCity,
            eSettlement,
            eEncampment,
            eNaturalLandmark,
            eCave,
            eFactory,
            eMonument,
            eMilitary,
            eOffice,
            eTownRuins,
            eUrbanRuins,
            eSewerRuins,
            eMetro,
            eVault
            };

        enum xrdoTypes
            {
            eRadius = 0,
            eEverywhere,
            eWorldAndLinkedInteriors,
            eLinkedInteriors,
            eCurrentCellOnly
            };

        enum xactFlags
            {
            fIsUseDefault    = 0x00000001,
            fIsActivate      = 0x00000002,
            fIsOpen          = 0x00000004,
            fIsOpenByDefault = 0x00000008
            };

        enum xespFlags
            {
            fIsOppositeParent = 0x00000001,
            fIsPopIn          = 0x00000002
            };

        enum xlocFlags
            {
            fIsLeveledLock = 0x00000004
            };

    public:
        StringRecord EDID; //Editor ID
        ReqSimpleSubRecord<FORMID> NAME; //Base
        OptSimpleSubRecord<FORMID> XEZN; //Encounter Zone
        RawRecord XRGD; //Ragdoll Data
        RawRecord XRGB; //Ragdoll Biped Data
        OptSubRecord<GENPATROL> Patrol; //Patrol Data
        OptSimpleSubRecord<int32_t> XLCM; //Level Modifier
        OptSubRecord<FNVXOWN> Ownership; //Owner
        OptSimpleSubRecord<int32_t> XCNT; //Count
        OptSimpleFloatSubRecord<flt_0> XRDS; //Radius
        OptSimpleFloatSubRecord<flt_0> XHLP; //Health
        OptSimpleFloatSubRecord<flt_0> XRAD; //Radiation
        OptSimpleFloatSubRecord<flt_0> XCHG; //Charge
        UnorderedSparseArray<GENXDCR *> XDCR; //Linked Decals
        OptSimpleSubRecord<FORMID> XLKR; //Linked Reference
        OptSubRecord<GENXCLP> XCLP; //Linked Reference Color
        RawRecord RCLR; //Unused Linked Reference Color (Old Format?)
        OptSubRecord<GENACTPARENT> ActivateParents; //Activate Parents
        StringRecord XATO; //Activation Prompt
        OptSubRecord<GENXESP> XESP; //Enable Parent
        OptSimpleSubRecord<FORMID> XEMI; //Emittance
        OptSimpleSubRecord<FORMID> XMBR; //MultiBound Reference

        OptSubRecord<GENXPRM> XPRM; //Primitive
        OptSimpleSubRecord<uint32_t> XTRI; //Collision Layer
        SemiOptSimpleSubRecord<uint8_t> XMBP; //MultiBound Primitive Marker (Empty) ?
        OptSubRecord<GENXMBO> XMBO; //BoundHalfExtents
        OptSubRecord<GENXTEL> XTEL; //Teleport Destination
        OptSubRecord<GENMAPDATA> MapData; //Map Data
        OptSubRecord<GENAUDIODATA> AudioData; //Audio Data
        RawRecord XSRF; //Unknown
        RawRecord XSRD; //Unknown
        OptSimpleSubRecord<FORMID> XTRG; //Target
        OptSubRecord<GENXRDO> XRDO; //Radio Data
        SemiOptSubRecord<FNVXLOC> XLOC; //Lock Data
        OptSubRecord<GENAMMO> Ammo; //Ammo
        UnorderedSparseArray<GENXPWR *> XPWR; //Reflected/Refracted By
        UnorderedSparseArray<FORMID> XLTW; //Lit Water
        OptSimpleSubRecord<uint32_t> XACT; //Action Flag
        //OptSubRecord<GENONAM> ONAM; //Open by Default (Empty)
        OptSubRecord<GENXNDP> XNDP; //Navigation Door Link
        OptSubRecord<GENXPOD> XPOD; //Portal Data
        OptSubRecord<GENPOSITION> XPTL; //Portal Data
        SemiOptSimpleSubRecord<uint8_t> XSED; //SpeedTree Seed
        OptSubRecord<GENROOM> Room; //Room Data
        OptSubRecord<GENPOSITION> XOCP; //Occlusion Plane Data
        OptSubRecord<GENXORD> XORD; //Linked Occlusion Planes (4 only?)
        OptSubRecord<GENXLOD> XLOD; //Distant LOD Data

        OptSimpleSubRecord<uint8_t> XIBS; //Ignored By Sandbox (Empty, boolean, if != 0, write empty)
        OptSimpleFloatSubRecord<flt_1> XSCL; //Scale
        ReqSubRecord<GENPOSDATA> DATA; //Position/Rotation

        REFRRecord(unsigned char *_recData=NULL);
        REFRRecord(REFRRecord *srcRecord);
        ~REFRRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsUseDefault();
        void   IsUseDefault(bool value);
        bool   IsActivate();
        void   IsActivate(bool value);
        bool   IsOpen();
        void   IsOpen(bool value);
        bool   IsOpenByDefault();
        void   IsOpenByDefault(bool value);
        bool   IsActionFlagMask(uint32_t Mask, bool Exact=false);
        void   SetActionFlagMask(uint32_t Mask);

        bool   IsOppositeParent();
        void   IsOppositeParent(bool value);
        bool   IsPopIn();
        void   IsPopIn(bool value);
        bool   IsParentFlagMask(uint8_t Mask, bool Exact=false);
        void   SetParentFlagMask(uint8_t Mask);

        bool   IsNoAlarm();
        void   IsNoAlarm(bool value);
        bool   IsDestFlagMask(uint32_t Mask, bool Exact=false);
        void   SetDestFlagMask(uint32_t Mask);

        bool   IsVisible();
        void   IsVisible(bool value);
        bool   IsCanTravelTo();
        void   IsCanTravelTo(bool value);
        bool   IsMapFlagMask(uint8_t Mask, bool Exact=false);
        void   SetMapFlagMask(uint8_t Mask);

        bool   IsLeveledLock();
        void   IsLeveledLock(bool value);
        bool   IsLockFlagMask(uint8_t Mask, bool Exact=false);
        void   SetLockFlagMask(uint8_t Mask);

        bool   IsNone();
        void   IsNone(bool value);
        bool   IsBox();
        void   IsBox(bool value);
        bool   IsSphere();
        void   IsSphere(bool value);
        bool   IsPortalBox();
        void   IsPortalBox(bool value);
        bool   IsPrimitiveType(uint32_t Type);
        void   SetPrimitiveType(uint32_t Type);

        bool   IsUnidentified();
        void   IsUnidentified(bool value);
        bool   IsStatic();
        void   IsStatic(bool value);
        bool   IsAnimStatic();
        void   IsAnimStatic(bool value);
        bool   IsTransparent();
        void   IsTransparent(bool value);
        bool   IsClutter();
        void   IsClutter(bool value);
        bool   IsWeapon();
        void   IsWeapon(bool value);
        bool   IsProjectile();
        void   IsProjectile(bool value);
        bool   IsSpell();
        void   IsSpell(bool value);
        bool   IsBiped();
        void   IsBiped(bool value);
        bool   IsTrees();
        void   IsTrees(bool value);
        bool   IsProps();
        void   IsProps(bool value);
        bool   IsWater();
        void   IsWater(bool value);
        bool   IsTrigger();
        void   IsTrigger(bool value);
        bool   IsTerrain();
        void   IsTerrain(bool value);
        bool   IsTrap();
        void   IsTrap(bool value);
        bool   IsNonCollidable();
        void   IsNonCollidable(bool value);
        bool   IsCloudTrap();
        void   IsCloudTrap(bool value);
        bool   IsGround();
        void   IsGround(bool value);
        bool   IsPortal();
        void   IsPortal(bool value);
        bool   IsDebrisSmall();
        void   IsDebrisSmall(bool value);
        bool   IsDebrisLarge();
        void   IsDebrisLarge(bool value);
        bool   IsAcousticSpace();
        void   IsAcousticSpace(bool value);
        bool   IsActorZone();
        void   IsActorZone(bool value);
        bool   IsProjectileZone();
        void   IsProjectileZone(bool value);
        bool   IsGasTrap();
        void   IsGasTrap(bool value);
        bool   IsShellCasing();
        void   IsShellCasing(bool value);
        bool   IsTransparentSmall();
        void   IsTransparentSmall(bool value);
        bool   IsInvisibleWall();
        void   IsInvisibleWall(bool value);
        bool   IsTransparentSmallAnim();
        void   IsTransparentSmallAnim(bool value);
        bool   IsDeadBip();
        void   IsDeadBip(bool value);
        bool   IsCharController();
        void   IsCharController(bool value);
        bool   IsAvoidBox();
        void   IsAvoidBox(bool value);
        bool   IsCollisionBox();
        void   IsCollisionBox(bool value);
        bool   IsCameraSphere();
        void   IsCameraSphere(bool value);
        bool   IsDoorDetection();
        void   IsDoorDetection(bool value);
        bool   IsCameraPick();
        void   IsCameraPick(bool value);
        bool   IsItemPick();
        void   IsItemPick(bool value);
        bool   IsLineOfSight();
        void   IsLineOfSight(bool value);
        bool   IsPathPick();
        void   IsPathPick(bool value);
        bool   IsCustomPick1();
        void   IsCustomPick1(bool value);
        bool   IsCustomPick2();
        void   IsCustomPick2(bool value);
        bool   IsSpellExplosion();
        void   IsSpellExplosion(bool value);
        bool   IsDroppingPick();
        void   IsDroppingPick(bool value);
        bool   IsCollisionType(uint32_t Type);
        void   SetCollisionType(uint32_t Type);

        bool   IsMarkerNone();
        void   IsMarkerNone(bool value);
        bool   IsCity();
        void   IsCity(bool value);
        bool   IsSettlement();
        void   IsSettlement(bool value);
        bool   IsEncampment();
        void   IsEncampment(bool value);
        bool   IsNaturalLandmark();
        void   IsNaturalLandmark(bool value);
        bool   IsCave();
        void   IsCave(bool value);
        bool   IsFactory();
        void   IsFactory(bool value);
        bool   IsMonument();
        void   IsMonument(bool value);
        bool   IsMilitary();
        void   IsMilitary(bool value);
        bool   IsOffice();
        void   IsOffice(bool value);
        bool   IsTownRuins();
        void   IsTownRuins(bool value);
        bool   IsUrbanRuins();
        void   IsUrbanRuins(bool value);
        bool   IsSewerRuins();
        void   IsSewerRuins(bool value);
        bool   IsMetro();
        void   IsMetro(bool value);
        bool   IsVault();
        void   IsVault(bool value);
        bool   IsMapType(uint8_t Type);
        void   SetMapType(uint8_t Type);

        bool   IsRadius();
        void   IsRadius(bool value);
        bool   IsEverywhere();
        void   IsEverywhere(bool value);
        bool   IsWorldAndLinkedInteriors();
        void   IsWorldAndLinkedInteriors(bool value);
        bool   IsLinkedInteriors();
        void   IsLinkedInteriors(bool value);
        bool   IsCurrentCellOnly();
        void   IsCurrentCellOnly(bool value);
        bool   IsBroadcastType(uint32_t Type);
        void   SetBroadcastType(uint32_t Type);

        uint32_t GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, uint32_t WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, uint32_t ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        uint32_t GetType();
        char * GetStrType();

        int32_t ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        int32_t Unload();
        int32_t WriteRecord(FileWriter &writer);

        bool operator ==(const REFRRecord &other) const;
        bool operator !=(const REFRRecord &other) const;
        bool equals(Record *other);
        bool deep_equals(Record *master, RecordOp &read_self, RecordOp &read_master, boost::unordered_set<Record *> &identical_records);
    };
}