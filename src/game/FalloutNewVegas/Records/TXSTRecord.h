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
class TXSTRecord : public FNVRecord //Texture Set
    {
    private:
        enum flagsFlags
            {
            fIsNoSpecularMap = 0x00000001
            };

        enum DODTFlags
            {
            fIsParallax      = 0x00000001,
            fIsAlphaBlending = 0x00000002,
            fIsAlphaTesting  = 0x00000004
            };

    public:
        StringRecord EDID; //Editor ID
        ReqSubRecord<GENOBND> OBND; //Object Bounds
        //Textures (RGB/A)
        StringRecord TX00; //Base Image / Transparency
        StringRecord TX01; //Normal Map / Specular
        StringRecord TX02; //Environment Map Mask / ?
        StringRecord TX03; //Glow Map / Unused
        StringRecord TX04; //Parallax Map / Unused
        StringRecord TX05; //Environment Map / Unused
        OptSubRecord<GENDODT> DODT; //Decal Data
        SemiOptSimpleSubRecord<uint16_t> DNAM; //Flags

        TXSTRecord(unsigned char *_recData=NULL);
        TXSTRecord(TXSTRecord *srcRecord);
        ~TXSTRecord();

        bool   IsNoSpecularMap();
        void   IsNoSpecularMap(bool value);
        bool   IsFlagMask(uint16_t Mask, bool Exact=false);
        void   SetFlagMask(uint16_t Mask);

        bool   IsObjectParallax();
        void   IsObjectParallax(bool value);
        bool   IsObjectAlphaBlending();
        void   IsObjectAlphaBlending(bool value);
        bool   IsObjectAlphaTesting();
        void   IsObjectAlphaTesting(bool value);
        bool   IsObjectFlagMask(uint8_t Mask, bool Exact=false);
        void   SetObjectFlagMask(uint8_t Mask);

        uint32_t GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, uint32_t WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, uint32_t ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        uint32_t GetType();
        char * GetStrType();

        int32_t ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        int32_t Unload();
        int32_t WriteRecord(FileWriter &writer);

        bool operator ==(const TXSTRecord &other) const;
        bool operator !=(const TXSTRecord &other) const;
        bool equals(Record *other);
    };
}