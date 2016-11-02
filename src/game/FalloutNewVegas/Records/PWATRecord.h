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

namespace FNV
{
class PWATRecord : public FNVRecord //Placeable Water
    {
    private:
        struct PWATDNAM
            {
            uint32_t  flags;
            FORMID  water;

            PWATDNAM();
            ~PWATDNAM();

            bool operator ==(const PWATDNAM &other) const;
            bool operator !=(const PWATDNAM &other) const;
            };

        enum flagsFlags
            {
            fIsReflects                 = 0x00000001,
            fIsReflectsActors           = 0x00000002,
            fIsReflectsLand             = 0x00000004,
            fIsReflectsLODLand          = 0x00000008,
            fIsReflectsLODBuildings     = 0x00000010,
            fIsReflectsTrees            = 0x00000020,
            fIsReflectsSky              = 0x00000040,
            fIsReflectsDynamicObjects   = 0x00000080,
            fIsReflectsDeadBodies       = 0x00000100,
            fIsRefracts                 = 0x00000200,
            fIsRefractsActors           = 0x00000400,
            fIsRefractsLand             = 0x00000800,
            fIsRefractsDynamicObjects   = 0x00010000,
            fIsRefractsDeadBodies       = 0x00020000,
            fIsSilhouetteReflections    = 0x00040000,
            fIsDepth                    = 0x10000000,
            fIsObjectTextureCoordinates = 0x20000000,
            fIsNoUnderwaterFog          = 0x80000000
            };

    public:
        StringRecord EDID; //Editor ID
        ReqSubRecord<GENOBND> OBND; //Object Bounds
        OptSubRecord<FNVMODEL> MODL; //Model
        ReqSubRecord<PWATDNAM> DNAM; //Data

        PWATRecord(unsigned char *_recData=NULL);
        PWATRecord(PWATRecord *srcRecord);
        ~PWATRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsReflects();
        void   IsReflects(bool value);
        bool   IsReflectsActors();
        void   IsReflectsActors(bool value);
        bool   IsReflectsLand();
        void   IsReflectsLand(bool value);
        bool   IsReflectsLODLand();
        void   IsReflectsLODLand(bool value);
        bool   IsReflectsLODBuildings();
        void   IsReflectsLODBuildings(bool value);
        bool   IsReflectsTrees();
        void   IsReflectsTrees(bool value);
        bool   IsReflectsSky();
        void   IsReflectsSky(bool value);
        bool   IsReflectsDynamicObjects();
        void   IsReflectsDynamicObjects(bool value);
        bool   IsReflectsDeadBodies();
        void   IsReflectsDeadBodies(bool value);
        bool   IsRefracts();
        void   IsRefracts(bool value);
        bool   IsRefractsActors();
        void   IsRefractsActors(bool value);
        bool   IsRefractsLand();
        void   IsRefractsLand(bool value);
        bool   IsRefractsDynamicObjects();
        void   IsRefractsDynamicObjects(bool value);
        bool   IsRefractsDeadBodies();
        void   IsRefractsDeadBodies(bool value);
        bool   IsSilhouetteReflections();
        void   IsSilhouetteReflections(bool value);
        bool   IsDepth();
        void   IsDepth(bool value);
        bool   IsObjectTextureCoordinates();
        void   IsObjectTextureCoordinates(bool value);
        bool   IsNoUnderwaterFog();
        void   IsNoUnderwaterFog(bool value);
        bool   IsFlagMask(uint32_t Mask, bool Exact=false);
        void   SetFlagMask(uint32_t Mask);

        uint32_t GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, uint32_t WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, uint32_t ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        uint32_t GetType();
        char * GetStrType();

        int32_t ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        int32_t Unload();
        int32_t WriteRecord(FileWriter &writer);

        bool operator ==(const PWATRecord &other) const;
        bool operator !=(const PWATRecord &other) const;
        bool equals(Record *other);
    };
}