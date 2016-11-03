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
#include "Common.h"
#include "GenericRecord.h"

//This record is a hybrid of all possible versions (TES4, FO3, FNV, TES5)

class StringLookups;

class TES4Record : public Record
    {
    private:
        struct TES4HEDR
            {
            float version;
            uint32_t  numRecords, nextObject;

            TES4HEDR(float _version=0.8f, uint32_t _numRecords=0, uint32_t _nextObject=END_HARDCODED_IDS);
            ~TES4HEDR();

            bool operator ==(const TES4HEDR &other) const;
            bool operator !=(const TES4HEDR &other) const;
            };

    public:
        // Common
        cb_game_type_t whichGame;
        ReqSubRecord<TES4HEDR> HEDR; //Header
        RawRecord OFST; //Unknown
        RawRecord DELE; //Unknown
        StringRecord CNAM; //Author
        StringRecord SNAM; //Description
        std::vector<char *> MAST; //Master Files

        // Fallout: New Vegas & Skyrim
        UnorderedPackedArray<FORMID> ONAM; //OverridednForms
        RawRecord SCRN; //Screenshot
        // Part of record header:
        uint16_t formVersion;
        uint8_t  versionControl2[2];

        // Skyrim
        RawRecord INTV; //Unknown
        RawRecord INCC; //Unknown
        StringLookups *LookupStrings;

        TES4Record(unsigned char *_recData=NULL);
        TES4Record(TES4Record *srcRecord);
        ~TES4Record();

        bool   VisitFormIDs(FormIDOp &op);

        bool IsESM() const;
        void IsESM(bool value);
        bool IsLookupStrings() const;
        void IsLookupStrings(bool value);

        void LoadStringLookups(char * FileName);

        uint32_t GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, uint32_t WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, uint32_t ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        uint32_t GetType();
        char * GetStrType();

        int32_t ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        int32_t Unload();
        int32_t WriteRecord(FileWriter &writer);
        uint32_t Write(FileWriter &writer, const bool &bMastersChanged, FormIDResolver &expander, FormIDResolver &collapser, std::vector<FormIDResolver *> &Expanders);

        bool operator ==(const TES4Record &other) const;
        bool operator !=(const TES4Record &other) const;
        bool equals(Record *other);
    };