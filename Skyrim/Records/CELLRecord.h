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
#include "..\..\Common.h"
#include "..\..\GenericRecord.h"

namespace Sk
{
class CELLRecord : public TES5Record //Cell
    {
    private:
        struct CELLXCLC
            {
            SINT32  posX, posY;
            UINT32  flags; //Not always present in chunk

            CELLXCLC();
            ~CELLXCLC();

            bool operator ==(const CELLXCLC &other) const;
            bool operator !=(const CELLXCLC &other) const;
            };

        enum flagsFlags
            {
            fIsInterior         = 0x00000001,
            fHasWater           = 0x00000002,
            fInvertFastTravel   = 0x00000004,
            fForceHideLand      = 0x00000008, //Exterior Cells
            fIsOblivionInterior = 0x00000008, //Interior Cells
            fPublicPlace        = 0x00000020,
            fHandChanged        = 0x00000040,
            fBehaveLikeExterior = 0x00000080
            };

        enum lightFlags
            {
            fIsAmbientInherited             = 0x00000001,
            fIsDirectionalColorInherited    = 0x00000002,
            fIsFogColorInherited            = 0x00000004,
            fIsFogNearInherited             = 0x00000008,
            fIsFogFarInherited              = 0x00000010,
            fIsDirectionalRotationInherited = 0x00000020,
            fIsDirectionalFadeInherited     = 0x00000040,
            fIsFogClipInherited             = 0x00000080,
            fIsFogPowerInherited            = 0x00000100
            };

        enum xclcFlags
            {
            fIsQuad1ForceHidden = 0x00000001,
            fIsQuad2ForceHidden = 0x00000002,
            fIsQuad3ForceHidden = 0x00000004,
            fIsQuad4ForceHidden = 0x00000008
            };

    public:
        StringRecord EDID; //Editor ID
        StringRecord FULL; //Name
        ReqSimpleSubRecord<UINT8> DATA; //Flags
        OptSubRecord<CELLXCLC> XCLC; //Grid
//      OptSubRecord<TES5LIGHT> XCLL; //Lighting
        UnorderedSparseArray<GENIMPS *> IMPS; //Swapped Impact
        OptSubRecord<GENIMPF> IMPF; //Footstep Materials
        ReqSimpleSubRecord<FORMID> LTMP; //Light Template
        ReqSimpleSubRecord<UINT32> LNAM; //Light Inherit Flags
        SimpleFloatSubRecord<flt_max> XCLW; //waterHeight
        StringRecord XNAM; //Water Noise Texture
        UnorderedPackedArray<FORMID> XCLR; //Regions
        OptSimpleSubRecord<FORMID> XCIM; //Image Space
        RawRecord XCET; //Unknown
        OptSimpleSubRecord<FORMID> XEZN; //Encounter Zone
        OptSimpleSubRecord<FORMID> XCCM; //Climate
        OptSimpleSubRecord<FORMID> XCWT; //Water -> WATR
//      OptSubRecord<TES5XOWN> Ownership; //Owner
        OptSimpleSubRecord<FORMID> XCAS; //Acoustic Space
        RawRecord XCMT; //Unused
	OptSimpleSubRecord<FORMID> XCMO; //Music Type
	RawRecord TVDT; //Unknown (Skyrim)
	RawRecord MHDT; //Unknown (Skyrim)
	OptSimpleSubRecord<FORMID> XLCN; //Unknown (Skyrim) -> LCTN
	RawRecord XWCN; //Unknown (Skyrim)
	RawRecord XWCU; //Unknown (Skyrim)
	
/*
        std::vector<Record *> ACHR;
        std::vector<Record *> ACRE;
        std::vector<Record *> REFR;
        std::vector<Record *> PGRE;
        std::vector<Record *> PMIS;
        std::vector<Record *> PBEA;
        std::vector<Record *> PFLA;
        std::vector<Record *> PCBE;
        std::vector<Record *> NAVM;
*/
        Record *LAND;

        CELLRecord(unsigned char *_recData=NULL);
        CELLRecord(CELLRecord *srcRecord);
        ~CELLRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsInterior();
        void   IsInterior(bool value);
        bool   IsHasWater();
        void   IsHasWater(bool value);
        bool   IsInvertFastTravel();
        void   IsInvertFastTravel(bool value);
        bool   IsForceHideLand();
        void   IsForceHideLand(bool value);
        bool   IsOblivionInterior();
        void   IsOblivionInterior(bool value);
        bool   IsPublicPlace();
        void   IsPublicPlace(bool value);
        bool   IsHandChanged();
        void   IsHandChanged(bool value);
        bool   IsBehaveLikeExterior();
        void   IsBehaveLikeExterior(bool value);
        bool   IsFlagMask(UINT8 Mask, bool Exact=false);
        void   SetFlagMask(UINT8 Mask);

        bool   IsQuad1ForceHidden();
        void   IsQuad1ForceHidden(bool value);
        bool   IsQuad2ForceHidden();
        void   IsQuad2ForceHidden(bool value);
        bool   IsQuad3ForceHidden();
        void   IsQuad3ForceHidden(bool value);
        bool   IsQuad4ForceHidden();
        void   IsQuad4ForceHidden(bool value);
        bool   IsQuadFlagMask(UINT32 Mask, bool Exact=false);
        void   SetQuadFlagMask(UINT32 Mask);

        bool   IsLightAmbientInherited();
        void   IsLightAmbientInherited(bool value);
        bool   IsLightDirectionalColorInherited();
        void   IsLightDirectionalColorInherited(bool value);
        bool   IsLightFogColorInherited();
        void   IsLightFogColorInherited(bool value);
        bool   IsLightFogNearInherited();
        void   IsLightFogNearInherited(bool value);
        bool   IsLightFogFarInherited();
        void   IsLightFogFarInherited(bool value);
        bool   IsLightDirectionalRotationInherited();
        void   IsLightDirectionalRotationInherited(bool value);
        bool   IsLightDirectionalFadeInherited();
        void   IsLightDirectionalFadeInherited(bool value);
        bool   IsLightFogClipInherited();
        void   IsLightFogClipInherited(bool value);
        bool   IsLightFogPowerInherited();
        void   IsLightFogPowerInherited(bool value);
        bool   IsLightFlagMask(UINT32 Mask, bool Exact=false);
        void   SetLightFlagMask(UINT32 Mask);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const CELLRecord &other) const;
        bool operator !=(const CELLRecord &other) const;
        bool equals(Record *other);
        bool deep_equals(Record *master, RecordOp &read_self, RecordOp &read_master, boost::unordered_set<Record *> &identical_records);
    };
}