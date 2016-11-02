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
class RACERecord : public FNVRecord //Race
    {
    private:
        struct RACEPart //Part
            {
            OptSubRecord<FNVMODEL> MODL; //Model
            StringRecord ICON; //Large Icon Filename
            StringRecord MICO; //Small Icon Filename

            void Write(uint32_t index, FileWriter &writer);
            void WriteIconsFirst(uint32_t index, FileWriter &writer);

            bool operator ==(const RACEPart &other) const;
            bool operator !=(const RACEPart &other) const;
            };

        enum flagsFlags
            {
            fIsPlayable = 0x00000001,
            fIsChild    = 0x00000004
            };

    public:
        StringRecord EDID; //Editor ID
        StringRecord FULL; //Name
        StringRecord DESC; //Description
        OrderedSparseArray<FNVXNAM *> XNAM; //Relations, not sure if record order matters
        ReqSubRecord<RACEDATA> DATA; //Data
        OptSimpleSubRecord<FORMID> ONAM; //Older
        OptSimpleSubRecord<FORMID> YNAM; //Younger
        //OptSubRecord<GENNAM2> NAM2; //Unknown Marker (Empty)
        SubRecord<RACEVNAM> VTCK; //Voices
        SubRecord<RACEDNAM> DNAM; //Default Hair Styles
        SubRecord<RACECNAM> CNAM; //Default Hair Colors
        OptSimpleFloatSubRecord<flt_0> PNAM; //FaceGen - Main clamp
        OptSimpleFloatSubRecord<flt_0> UNAM; //FaceGen - Face clamp
        RawRecord ATTR; //Unknown

        //OptSubRecord<GENNAM> NAM0; //Head Data Marker (Empty)
        //OptSubRecord<GENMNAM> MNAM; //Male Data Marker (Empty)
        //Male Head Parts
        RACEPart MHMOD0; //Head
        RACEPart MHMOD1; //Ears
        RACEPart MHMOD2; //Mouth
        RACEPart MHMOD3; //Teeth Lower
        RACEPart MHMOD4; //Teeth Upper
        RACEPart MHMOD5; //Tongue
        RACEPart MHMOD6; //Left Eye
        RACEPart MHMOD7; //Right Eye

        //OptSubRecord<GENFNAM> FNAM; //Female Data Marker (Empty)
        //Female Head Parts
        RACEPart FHMOD0; //Head
        RACEPart FHMOD1; //Ears
        RACEPart FHMOD2; //Mouth
        RACEPart FHMOD3; //Teeth Lower
        RACEPart FHMOD4; //Teeth Upper
        RACEPart FHMOD5; //Tongue
        RACEPart FHMOD6; //Left Eye
        RACEPart FHMOD7; //Right Eye

        //OptSubRecord<GENNAM1> NAM1; //Body Data Marker (Empty)
        //OptSubRecord<GENMNAM> MNAM; //Male Data Marker (Empty)
        //Male Body Parts
        RACEPart MBMOD0; //Upper Body
        RACEPart MBMOD1; //Left Hand
        RACEPart MBMOD2; //Right Hand
        RACEPart MBMOD3; //Upper Body Texture

        //OptSubRecord<GENFNAM> FNAM; //Female Data Marker (Empty)
        //Female Body Parts
        RACEPart FBMOD0; //Upper Body
        RACEPart FBMOD1; //Left Hand
        RACEPart FBMOD2; //Right Hand
        RACEPart FBMOD3; //Upper Body Texture

        UnorderedPackedArray<FORMID> HNAM; //Hairs
        UnorderedPackedArray<FORMID> ENAM; //Eyes

        //OptSubRecord<GENMNAM> MNAM; //Male Data Marker (Empty)
        RawRecord MaleFGGS; //FaceGen Geometry-Symmetric
        RawRecord MaleFGGA; //FaceGen Geometry-Asymmetric
        RawRecord MaleFGTS; //FaceGen Texture-Symmetric
        ReqSubRecord<RACESNAM> MaleSNAM; //Unknown
        //OptSubRecord<GENFNAM> FNAM; //Female Data Marker (Empty)
        RawRecord FemaleFGGS; //FaceGen Geometry-Symmetric
        RawRecord FemaleFGGA; //FaceGen Geometry-Asymmetric
        RawRecord FemaleFGTS; //FaceGen Texture-Symmetric
        ReqSubRecord<RACESNAM> FemaleSNAM; //Unknown

        RACERecord(unsigned char *_recData=NULL);
        RACERecord(RACERecord *srcRecord);
        ~RACERecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsPlayable();
        void   IsPlayable(bool value);
        bool   IsChild();
        void   IsChild(bool value);
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

        bool operator ==(const RACERecord &other) const;
        bool operator !=(const RACERecord &other) const;
        bool equals(Record *other);
    };
}