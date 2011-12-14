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

namespace Ob
{
class REGNRecord : public Record //Region
    {
    private:
        struct REGNRPLD //Point
            {
            FLOAT32 posX, posY;

            REGNRPLD();
            ~REGNRPLD();

            bool operator ==(const REGNRPLD &other) const;
            bool operator !=(const REGNRPLD &other) const;
            };

        struct REGNArea
            {
            ReqSimpleSubRecord<UINT32> RPLI; //Edge Fall-off
            UnorderedPackedArray<REGNRPLD> RPLD; //Region Point List Data

            void Write(FileWriter &writer);

            bool operator ==(const REGNArea &other) const;
            bool operator !=(const REGNArea &other) const;
            };

        struct REGNRDWT //Weather Type
            {
            FORMID  weather;
            UINT32  chance;

            REGNRDWT();
            ~REGNRDWT();

            bool operator ==(const REGNRDWT &other) const;
            bool operator !=(const REGNRDWT &other) const;
            };

        struct REGNRDSD //Sound
            {
            FORMID  sound;
            UINT32  flags, chance;

            enum RDSDFlags
                {
                fIsPleasant = 0x00000001,
                fIsCloudy   = 0x00000002,
                fIsRainy    = 0x00000004,
                fIsSnowy    = 0x00000008
                };

            REGNRDSD();
            ~REGNRDSD();

            bool IsPleasant();
            void IsPleasant(bool value);
            bool IsCloudy();
            void IsCloudy(bool value);
            bool IsRainy();
            void IsRainy(bool value);
            bool IsSnowy();
            void IsSnowy(bool value);
            bool IsFlagMask(UINT32 Mask, bool Exact=false);
            void SetFlagMask(UINT32 Mask);

            bool operator ==(const REGNRDSD &other) const;
            bool operator !=(const REGNRDSD &other) const;
            };

        struct REGNRDGS //Grass
            {
            FORMID  grass;
            UINT8   unk1[4];

            REGNRDGS();
            ~REGNRDGS();

            bool operator ==(const REGNRDGS &other) const;
            bool operator !=(const REGNRDGS &other) const;
            };

        struct REGNRDOT //Object
            {
            FORMID  objectId;
            UINT16  parentIndex;
            UINT8   unused1[2];
            FLOAT32 density;
            UINT8   clustering, minSlope, maxSlope, flags;
            UINT16  radiusWRTParent, radius;
            UINT8   unk1[4];
            FLOAT32 maxHeight, sink, sinkVar, sizeVar;
            UINT16  angleVarX, angleVarY, angleVarZ;
            UINT8   unused2[2], unk2[4];

            enum RDOTFlags
                {
                fIsConformToSlope = 0x00000001,
                fIsPaintVertices  = 0x00000002,
                fIsSizeVariance   = 0x00000004,
                fIsXVariance      = 0x00000008,
                fIsYVariance      = 0x00000010,
                fIsZVariance      = 0x00000020,
                fIsTree           = 0x00000040,
                fIsHugeRock       = 0x00000080
                };

            REGNRDOT();
            ~REGNRDOT();

            bool IsConformToSlope();
            void IsConformToSlope(bool value);
            bool IsPaintVertices();
            void IsPaintVertices(bool value);
            bool IsSizeVariance();
            void IsSizeVariance(bool value);
            bool IsXVariance();
            void IsXVariance(bool value);
            bool IsYVariance();
            void IsYVariance(bool value);
            bool IsZVariance();
            void IsZVariance(bool value);
            bool IsTree();
            void IsTree(bool value);
            bool IsHugeRock();
            void IsHugeRock(bool value);
            bool IsFlagMask(UINT8 Mask, bool Exact=false);
            void SetFlagMask(UINT8 Mask);

            bool operator ==(const REGNRDOT &other) const;
            bool operator !=(const REGNRDOT &other) const;
            };

        struct REGNRDAT //Data Header
            {
            UINT32  entryType;
            UINT8   flags, priority, unused1[2];

            REGNRDAT();
            ~REGNRDAT();

            bool operator ==(const REGNRDAT &other) const;
            bool operator !=(const REGNRDAT &other) const;
            };

        struct REGNEntry //Region Data Entry
            {
            ReqSubRecord<REGNRDAT> RDAT; //Data Header
            UnorderedPackedArray<REGNRDOT> RDOT; //Objects
            StringRecord RDMP; //Map Name
            StringRecord ICON; //Unknown
            UnorderedPackedArray<REGNRDGS> RDGS; //Grasses
            SemiOptSimpleSubRecord<UINT32> RDMD; //Music Type
            UnorderedPackedArray<REGNRDSD> RDSD; //Sounds
            UnorderedPackedArray<REGNRDWT> RDWT; //Weather Types

            enum RDATFlags
                {
                fIsOverride = 0x00000001
                };

            enum eRDATType
                {
                eObject  = 2,
                eWeather = 3,
                eMap     = 4,
                eUnkIcon = 5,
                eGrass   = 6,
                eSound   = 7
                };

            enum eRDMDType
                {
                eDefault = 0,
                ePublic,
                eDungeon
                };

            bool IsOverride();
            void IsOverride(bool value);
            bool IsFlagMask(UINT8 Mask, bool Exact=false);
            void SetFlagMask(UINT8 Mask);

            bool IsObject();
            void IsObject(bool value);
            bool IsWeather();
            void IsWeather(bool value);
            bool IsMap();
            void IsMap(bool value);
            bool IsIcon();
            void IsIcon(bool value);
            bool IsGrass();
            void IsGrass(bool value);
            bool IsSound();
            void IsSound(bool value);
            bool IsType(UINT32 Type);
            void SetType(UINT32 Type);

            bool IsDefaultMusic();
            void IsDefaultMusic(bool value);
            bool IsPublicMusic();
            void IsPublicMusic(bool value);
            bool IsDungeonMusic();
            void IsDungeonMusic(bool value);
            bool IsMusicType(UINT32 Type);
            void SetMusicType(UINT32 Type);

            void Write(FileWriter &writer);

            bool operator ==(const REGNEntry &other) const;
            bool operator !=(const REGNEntry &other) const;
            };

    public:
        StringRecord EDID; //Editor ID
        StringRecord ICON; //Large Icon Filename
        ReqSubRecord<GENCLR> RCLR; //Map Color
        OptSimpleSubRecord<FORMID> WNAM; //Worldspace
        UnorderedSparseArray<REGNArea *> Areas; //Areas
        UnorderedSparseArray<REGNEntry *> Entries; //Region Data Entries

        REGNRecord(unsigned char *_recData=NULL);
        REGNRecord(REGNRecord *srcRecord);
        ~REGNRecord();

        bool   VisitFormIDs(FormIDOp &op);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const REGNRecord &other) const;
        bool operator !=(const REGNRecord &other) const;
        bool equals(Record *other);
    };
}