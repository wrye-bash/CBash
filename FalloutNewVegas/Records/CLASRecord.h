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

namespace FNV
{
class CLASRecord : public FNVRecord //Class
    {
    private:
        struct CLASDATA
            {
            SINT32  tagSkills[4];
            UINT32  flags, services;
            SINT8   trainSkill;
            UINT8   trainLevel;
            SINT8   unused1[2];

            CLASDATA();
            ~CLASDATA();

            bool operator ==(const CLASDATA &other) const;
            bool operator !=(const CLASDATA &other) const;
            };

        struct CLASATTR
            {
            UINT8   strength, perception, endurance,
                    charisma, intelligence, agility, luck;

            CLASATTR();
            ~CLASATTR();

            bool operator ==(const CLASATTR &other) const;
            bool operator !=(const CLASATTR &other) const;
            };

        enum flagsFlags
            {
            fIsPlayable = 0x00000001,
            fIsGuard    = 0x00000002
            };

        enum servicesFlags
            {
            fIsServicesWeapons   = 0x00000001,
            fIsServicesArmor     = 0x00000002,
            fIsServicesClothing  = 0x00000004,
            fIsServicesBooks     = 0x00000008,
            fIsServicesFood      = 0x00000010,
            fIsServicesChems     = 0x00000020,
            fIsServicesStimpacks = 0x00000040,
            fIsServicesLights    = 0x00000080, // ?
            fIsServicesMiscItems = 0x00000400,
            fIsServicesPotions   = 0x00002000, // ?
            fIsServicesTraining  = 0x00004000,
            fIsServicesRecharge  = 0x00010000,
            fIsServicesRepair    = 0x00020000
            };
    public:
        StringRecord EDID; //Editor ID
        StringRecord FULL; //Name
        StringRecord DESC; //Description
        StringRecord ICON; //Large Icon Filename
        StringRecord MICO; //Small Icon Filename
        ReqSubRecord<CLASDATA> DATA; //Data
        ReqSubRecord<CLASATTR> ATTR; //Attributes

        CLASRecord(unsigned char *_recData=NULL);
        CLASRecord(CLASRecord *srcRecord);
        ~CLASRecord();

        bool   IsPlayable();
        void   IsPlayable(bool value);
        bool   IsGuard();
        void   IsGuard(bool value);
        bool   IsFlagMask(UINT32 Mask, bool Exact=false);
        void   SetFlagMask(UINT32 Mask);

        bool   IsServicesWeapons();
        void   IsServicesWeapons(bool value);
        bool   IsServicesArmor();
        void   IsServicesArmor(bool value);
        bool   IsServicesClothing();
        void   IsServicesClothing(bool value);
        bool   IsServicesBooks();
        void   IsServicesBooks(bool value);
        bool   IsServicesFood();
        void   IsServicesFood(bool value);
        bool   IsServicesChems();
        void   IsServicesChems(bool value);
        bool   IsServicesStimpacks();
        void   IsServicesStimpacks(bool value);
        bool   IsServicesLights();
        void   IsServicesLights(bool value);
        bool   IsServicesMiscItems();
        void   IsServicesMiscItems(bool value);
        bool   IsServicesPotions();
        void   IsServicesPotions(bool value);
        bool   IsServicesTraining();
        void   IsServicesTraining(bool value);
        bool   IsServicesRecharge();
        void   IsServicesRecharge(bool value);
        bool   IsServicesRepair();
        void   IsServicesRepair(bool value);
        bool   IsServicesFlagMask(UINT32 Mask, bool Exact=false);
        void   SetServicesFlagMask(UINT32 Mask);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const CLASRecord &other) const;
        bool operator !=(const CLASRecord &other) const;
        bool equals(Record *other);
    };
}