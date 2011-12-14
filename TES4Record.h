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

class TES4Record : public Record
    {
    private:
        struct TES4HEDR
            {
            FLOAT32 version;
            UINT32  numRecords, nextObject;

            TES4HEDR(FLOAT32 _version=0.8f, UINT32 _numRecords=0, UINT32 _nextObject=END_HARDCODED_IDS);
            ~TES4HEDR();

            bool operator ==(const TES4HEDR &other) const;
            bool operator !=(const TES4HEDR &other) const;
            };

    public:
        whichGameTypes whichGame;
        ReqSubRecord<TES4HEDR> HEDR; //Header
        RawRecord OFST; //Unknown
	RawRecord DELE; //Unknown
	RawRecord INTV; //Unknown (Skyrim)
	RawRecord PURG; //Unknown (Skyrim)
        StringRecord CNAM; //Author
        StringRecord SNAM; //Description
        std::vector<STRING> MAST; //Master Files

        //FNV Specific
        UnorderedPackedArray<FORMID> ONAM; //Overridden Forms
        RawRecord SCRN; //Screenshot
        //Part of FNVRecord
        UINT16 formVersion; //FNV
        UINT8  versionControl2[2]; //FNV

        TES4Record(unsigned char *_recData=NULL);
        TES4Record(TES4Record *srcRecord);
        ~TES4Record();

        bool   VisitFormIDs(FormIDOp &op);

        bool IsESM();
        void IsESM(bool value);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);
        UINT32 Write(FileWriter &writer, const bool &bMastersChanged, FormIDResolver &expander, FormIDResolver &collapser, std::vector<FormIDResolver *> &Expanders);

        bool operator ==(const TES4Record &other) const;
        bool operator !=(const TES4Record &other) const;
        bool equals(Record *other);
    };