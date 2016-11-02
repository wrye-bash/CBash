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
class ASPCRecord : public FNVRecord //Acoustic Space
    {
    private:
        enum eEnvTypes
            {
            eNone = 0,
            eDefault,
            eGeneric,
            ePaddedCell,
            eRoom,
            eBathroom,
            eLivingroom,
            eStoneRoom,
            eAuditorium,
            eConcerthall,
            eCave,
            eArena,
            eHangar,
            eCarpetedHallway,
            eHallway,
            eStoneCorridor,
            eAlley,
            eForest,
            eCity,
            eMountains,
            eQuarry,
            ePlain,
            eParkinglot,
            eSewerpipe,
            eUnderwater,
            eSmallRoom,
            eMediumRoom,
            eLargeRoom,
            eMediumHall,
            eLargeHall,
            ePlate
            };

        enum eSpaceTypes
            {
            eIsExterior = 0,
            eIsInterior
            };
    public:
        StringRecord EDID; //Editor ID
        ReqSubRecord<GENOBND> OBND; //Object Bounds
        ReqSimpleSubRecord<FORMID> DawnSNAM; //Dawn / Default Loop
        ReqSimpleSubRecord<FORMID> AfternoonSNAM; //Afternoon
        ReqSimpleSubRecord<FORMID> DuskSNAM; //Dusk
        ReqSimpleSubRecord<FORMID> NightSNAM; //Night
        ReqSimpleSubRecord<FORMID> WallaSNAM; //Walla
        ReqSimpleSubRecord<uint32_t> WNAM; //Walla Trigger Count
        OptSimpleSubRecord<FORMID> RDAT; //Use Sound from Region (Interiors Only)
        ReqSimpleSubRecord<uint32_t> ANAM; //Environment Type
        ReqSimpleSubRecord<uint32_t> INAM; //Is Interior

        ASPCRecord(unsigned char *_recData=NULL);
        ASPCRecord(ASPCRecord *srcRecord);
        ~ASPCRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsEnvironmentNone();
        void   IsEnvironmentNone(bool value);
        bool   IsEnvironmentDefault();
        void   IsEnvironmentDefault(bool value);
        bool   IsEnvironmentGeneric();
        void   IsEnvironmentGeneric(bool value);
        bool   IsEnvironmentPaddedCell();
        void   IsEnvironmentPaddedCell(bool value);
        bool   IsEnvironmentRoom();
        void   IsEnvironmentRoom(bool value);
        bool   IsEnvironmentBathroom();
        void   IsEnvironmentBathroom(bool value);
        bool   IsEnvironmentLivingroom();
        void   IsEnvironmentLivingroom(bool value);
        bool   IsEnvironmentStoneRoom();
        void   IsEnvironmentStoneRoom(bool value);
        bool   IsEnvironmentAuditorium();
        void   IsEnvironmentAuditorium(bool value);
        bool   IsEnvironmentConcerthall();
        void   IsEnvironmentConcerthall(bool value);
        bool   IsEnvironmentCave();
        void   IsEnvironmentCave(bool value);
        bool   IsEnvironmentArena();
        void   IsEnvironmentArena(bool value);
        bool   IsEnvironmentHangar();
        void   IsEnvironmentHangar(bool value);
        bool   IsEnvironmentCarpetedHallway();
        void   IsEnvironmentCarpetedHallway(bool value);
        bool   IsEnvironmentHallway();
        void   IsEnvironmentHallway(bool value);
        bool   IsEnvironmentStoneCorridor();
        void   IsEnvironmentStoneCorridor(bool value);
        bool   IsEnvironmentAlley();
        void   IsEnvironmentAlley(bool value);
        bool   IsEnvironmentForest();
        void   IsEnvironmentForest(bool value);
        bool   IsEnvironmentCity();
        void   IsEnvironmentCity(bool value);
        bool   IsEnvironmentMountains();
        void   IsEnvironmentMountains(bool value);
        bool   IsEnvironmentQuarry();
        void   IsEnvironmentQuarry(bool value);
        bool   IsEnvironmentPlain();
        void   IsEnvironmentPlain(bool value);
        bool   IsEnvironmentParkinglot();
        void   IsEnvironmentParkinglot(bool value);
        bool   IsEnvironmentSewerpipe();
        void   IsEnvironmentSewerpipe(bool value);
        bool   IsEnvironmentUnderwater();
        void   IsEnvironmentUnderwater(bool value);
        bool   IsEnvironmentSmallRoom();
        void   IsEnvironmentSmallRoom(bool value);
        bool   IsEnvironmentMediumRoom();
        void   IsEnvironmentMediumRoom(bool value);
        bool   IsEnvironmentLargeRoom();
        void   IsEnvironmentLargeRoom(bool value);
        bool   IsEnvironmentMediumHall();
        void   IsEnvironmentMediumHall(bool value);
        bool   IsEnvironmentLargeHall();
        void   IsEnvironmentLargeHall(bool value);
        bool   IsEnvironmentPlate();
        void   IsEnvironmentPlate(bool value);
        bool   IsEnvironmentType(uint32_t Type);
        void   SetEnvironmentType(uint32_t Type);

        bool   IsSpaceExterior();
        void   IsSpaceExterior(bool value);
        bool   IsSpaceInterior();
        void   IsSpaceInterior(bool value);
        bool   IsSpaceType(uint32_t Type);
        void   SetSpaceType(uint32_t Type);

        uint32_t GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, uint32_t WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, uint32_t ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        uint32_t GetType();
        char * GetStrType();

        int32_t ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        int32_t Unload();
        int32_t WriteRecord(FileWriter &writer);

        bool operator ==(const ASPCRecord &other) const;
        bool operator !=(const ASPCRecord &other) const;
        bool equals(Record *other);
    };
}