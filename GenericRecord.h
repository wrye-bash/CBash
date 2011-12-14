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
// BaseRecord.h
#include "Common.h"
#include "GenericChunks.h"

class Record;
class ModFile;

class RecordOp
    {
    protected:
        UINT32 count;
        bool stop;

    public:
        bool result;

        RecordOp();
        virtual ~RecordOp();

        virtual bool Accept(Record *&curRecord);

        UINT32 GetCount();
        void ResetCount();
        bool Stop();
    };

struct RecordHeader
    {
    UINT32 type;
    UINT32 flags;
    FORMID formID;
    UINT32 flagsUnk;
    UINT16 formVersion; //FNV
    UINT8  versionControl2[2]; //FNV
    unsigned char *data;
    };

class RecordProcessor
    {
    public:
        ModFile *curModFile;
        boost::unordered_set<UINT32> &NewTypes;
        UINT8 ExpandedIndex;
        FormIDResolver expander;
        const ModFlags &Flags;
        boost::unordered_set<UINT32> &UsedFormIDs;
        SINT32 &EmptyGRUPs;
        std::vector<FORMID> &OrphanedRecords;

	boost::unordered_set<UINT32> filter_records;
	boost::unordered_set<UINT32> filter_wspaces;
	bool filter_inclusive; FORMID activewspace;

        bool IsSkipNewRecords;
        bool IsSkipAllRecords;
        bool IsKeepRecords;
        bool IsTrackNewTypes;
        bool IsAddMasters;

        RecordProcessor(ModFile *curModFile, FormIDHandlerClass &_FormIDHandler, const ModFlags &_Flags, boost::unordered_set<UINT32> &_UsedFormIDs);
        ~RecordProcessor();

        //template<bool IsKeyedByEditorID, typename U>
        //typename boost::enable_if_c<!IsKeyedByEditorID,bool>::type Accept(U &header)

	void SetFilter(bool inclusive, boost::unordered_set<UINT32> &RecordTypes, boost::unordered_set<FORMID> &WorldSpaces) {
	  filter_inclusive = inclusive;
	  filter_records = RecordTypes;
	  filter_wspaces = WorldSpaces;
	}

        bool Accept(RecordHeader &header)
            {

	    /* this assumes records are read serial (all records belonging
	     * to a specific worldspace are between this WRLD and the next WRLD)
	     */
	    if (header.type == REV32(WRLD))
		activewspace = header.formID;

	    /* only allow those in the set */
	    if (filter_inclusive) {
		if (filter_records.count(header.type) == 0)
		    return false;
		if (header.type != REV32(LTEX))
		if (filter_wspaces.count(activewspace) == 0)
		    return false;
	    }
	    /* only allow those not in the set */
	    else {
		if (filter_records.count(header.type) != 0)
		    return false;
		if (header.type != REV32(LTEX))
		if (filter_wspaces.count(activewspace) != 0)
		    return false;
	    }

            expander.Accept(header.formID);

            if((IsTrackNewTypes || IsSkipNewRecords) && ((header.formID >> 24) == ExpandedIndex))
                {
                if(IsTrackNewTypes)
                    NewTypes.insert(header.type);
                if(IsSkipNewRecords)
                    return false;
                }

            //Make sure the formID is unique within the mod
            if(UsedFormIDs.insert(header.formID).second == false)
                {
                if(IsAddMasters) //If not, can cause any new records to be given a duplicate ID
                    printer("RecordProcessor: Warning - Information lost. Record skipped with duplicate formID: %08X\n", header.formID);
                return false;
                }

            return IsKeepRecords;
            }

        //template<bool IsKeyedByEditorID, typename U>
        //typename boost::enable_if_c<IsKeyedByEditorID,bool>::type Accept(U &header)
        //    {
        //    expander.Accept(header.formID);

        //    //EditorID keyed records (GMST, MGEF) don't use their formID, so there is little point in ensuring its uniqueness
        //    //Make sure the formID is unique within the mod
        //    //if(UsedFormIDs.insert(header.formID).second == false)
        //    //    {
        //    //    if(!IsAddMasters) //Can cause any new records to be given a duplicate ID
        //    //        printer("RecordProcessor: Warning - Information lost. Record skipped with duplicate formID: %08X\n", header.formID);
        //    //    return false;
        //    //    }

        //    //EditorID keyed records (GMST, MGEF) aren't normally createable, so they aren't really "new"
        //    //The exception being that MGEF's can be created if JRoush's OBME plugin is used
        //    //There's no good way to check for them with this available info (needs access to the MGEF's EDID chunk)
        //    //if(IsSkipNewRecords && ((header.formID >> 24) == ExpandedIndex))
        //    //    return false;

        //    return IsKeepRecords;
        //    }
    };

class Record
    {
    protected:
        enum headerFlags
            {
            fIsESM                  = 0x00000001,
            //fIsTaken              = 0x00000002, //From OBSE, unconfirmed, requires fIsDeleted also be set
            fIsDeleted              = 0x00000020,
            fIsBorderRegion         = 0x00000040,
            fIsTurnOffFire          = 0x00000080,
            fIsCastsShadows         = 0x00000200,
            fIsQuestOrPersistent    = 0x00000400,
            fIsInitiallyDisabled    = 0x00000800,
            fIsIgnored              = 0x00001000,
            //fIsTemporary          = 0x00004000, //From OBSE, unconfirmed
            fIsVisibleWhenDistant   = 0x00008000,
            fIsDangerousOrOffLimits = 0x00020000,
            fIsCompressed           = 0x00040000,
            fIsCantWait             = 0x00080000
            };

        enum cBashRecordFlags
            {
            _fIsLoaded            = 0x00000001,
            _fIsChanged           = 0x00000002,
            _fIsParentMod         = 0x00000004,
            _fIsWinningDetermined = 0x00000008,
            _fIsWinning           = 0x00000010,
            _fIsExtendedWinning   = 0x00000020,
            //_fHasInvalidFormIDs = 0x00000040
            };
        void *Parent;

    public:
        unsigned char *recData;
        UINT32 CBash_Flags;

        UINT32 flags;
        FORMID formID;
        UINT32 flagsUnk; //Version Control Info 1, FNV
        //UINT16 formVersion; //FNV
        //UINT8 versionControl2[2]; //FNV

        Record(unsigned char *_recData=NULL);
        virtual ~Record();

        void * GetParent() const;
        bool   SetParent(void *_Parent, bool IsMod);

        bool      IsParentMod() const;
        Record *  GetParentRecord() const;
        ModFile * GetParentMod() const;

        bool   IsWinningDetermined() const;
        void   IsWinningDetermined(bool value);
        bool   IsWinning() const;
        void   IsWinning(bool value);
        bool   IsExtendedWinning() const;
        void   IsExtendedWinning(bool value);
        //bool   HasInvalidFormIDs() const;
        //void   HasInvalidFormIDs(bool value);

        virtual SINT32 Unload() abstract {};
        virtual UINT32 GetType() abstract {};
        virtual STRING GetStrType() abstract {};
        virtual SINT32 WriteRecord(FileWriter &writer) abstract {};
        virtual SINT32 ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false) abstract {};

        virtual UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        virtual void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        virtual bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        virtual void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        virtual bool   IsKeyedByEditorID();
        virtual STRING GetEditorIDKey();
        virtual bool   SetEditorIDKey(STRING EditorID);

        virtual bool VisitFormIDs(FormIDOp &op);

        virtual bool   Read();
        virtual UINT32 Write(FileWriter &writer, const bool &bMastersChanged, FormIDResolver &expander, FormIDResolver &collapser, std::vector<FormIDResolver *> &Expanders);
        bool           IsValid(FormIDResolver &expander);

        bool         master_equality(Record *master, RecordOp &read_self, RecordOp &read_master, boost::unordered_set<Record *> &identical_records);
        bool         shallow_equals(Record *other);
		virtual bool equals(Record *other) abstract {};
		virtual bool deep_equals(Record *master, RecordOp &read_self, RecordOp &read_master, boost::unordered_set<Record *> &identical_records);

        bool IsDeleted() const;
        void IsDeleted(bool value);
        bool IsBorderRegion();
        void IsBorderRegion(bool value);
        bool IsTurnOffFire();
        void IsTurnOffFire(bool value);
        bool IsCastsShadows();
        void IsCastsShadows(bool value);
        bool IsQuestOrPersistent();
        void IsQuestOrPersistent(bool value);
        bool IsQuest();
        void IsQuest(bool value);
        bool IsPersistent();
        void IsPersistent(bool value);
        bool IsInitiallyDisabled();
        void IsInitiallyDisabled(bool value);
        bool IsIgnored();
        void IsIgnored(bool value);
        bool IsVisibleWhenDistant();
        void IsVisibleWhenDistant(bool value);
        bool IsVWD();
        void IsVWD(bool value);
        bool IsTemporary();
        void IsTemporary(bool value);
        bool IsDangerousOrOffLimits();
        void IsDangerousOrOffLimits(bool value);
        bool IsDangerous();
        void IsDangerous(bool value);
        bool IsOffLimits();
        void IsOffLimits(bool value);
        bool IsCompressed();
        void IsCompressed(bool value);
        bool IsCantWait();
        void IsCantWait(bool value);
        bool IsHeaderFlagMask(UINT32 Mask, bool Exact=false);
        void SetHeaderFlagMask(UINT32 Mask);

        bool IsHeaderUnknownFlagMask(UINT32 Mask, bool Exact=false);
        void SetHeaderUnknownFlagMask(UINT32 Mask);

        bool IsLoaded();
        void IsLoaded(bool value);

        bool IsChanged();
        void IsChanged(bool value);
    };

class FNVRecord : public Record
    {
    protected:
      enum FNVHeaderFlags
      {
	fIsESM                              = 0x00000001,
	fIsTaken                            = 0x00000002, //From OBSE, unconfirmed, requires fIsDeleted also be set
	fUnknown1                           = 0x00000004,
	fUnknown2                           = 0x00000008,
	fUnknown3                           = 0x00000010,
	fIsDeleted                          = 0x00000020,
	fIsBorderRegion                     = 0x00000040, //Has Tree LOD / Constant / Hidden From Local Map (FNV)
	fIsTurnOffFire                      = 0x00000080,
	fIsInaccessible                     = 0x00000100, // (FNV)
	fIsCastsShadows                     = 0x00000200, //On Local Map / Motion Blur (FNV)
	fIsQuestOrPersistent                = 0x00000400,
	fIsInitiallyDisabled                = 0x00000800,
	fIsIgnored                          = 0x00001000,
	fIsNoVoiceFilter                    = 0x00002000, // (FNV)
	fIsTemporary                        = 0x00004000, //From OBSE, unconfirmed
	fIsVisibleWhenDistant               = 0x00008000,
	fIsRandomAnimStartOrHighPriorityLOD = 0x00010000, // (FNV)
	fIsDangerousOrOffLimits             = 0x00020000, // Radio Station (Talking Activator) (FNV)
	fIsCompressed                       = 0x00040000,
	fIsCantWait                         = 0x00080000, // Platform Specific Texture (FNV)
	fUnknown4                           = 0x00100000,
	fUnknown5                           = 0x00200000,
	fUnknown6                           = 0x00400000,
	fUnknown7                           = 0x00800000,
	fUnknown8                           = 0x01000000,
	fIsObstacleOrNoAIAcquire            = 0x02000000, // (FNV)
	fIsNavMeshFilter                    = 0x04000000, // (FNV)
	fIsNavMeshBoundBox                  = 0x08000000, // (FNV)
	fIsNonPipboyOrAutoReflected         = 0x10000000, // (FNV)
	fIsChildUsableOrAutoRefracted       = 0x20000000, // (FNV)
	fIsNavMeshGround                    = 0x40000000, // (FNV)
	fUnknown9                           = 0x80000000
      };

    public:
      UINT16 formVersion; //FNV
      UINT8  versionControl2[2]; //FNV

      FNVRecord(unsigned char *_recData=NULL);
      virtual ~FNVRecord();

      bool Read();
      UINT32 Write(FileWriter &writer, const bool &bMastersChanged, FormIDResolver &expander, FormIDResolver &collapser, std::vector<FormIDResolver *> &Expanders);
    };

class TES5Record : public Record
    {
    protected:
      enum TES5HeaderFlags
      {
	fIsESM                              = 0x00000001,
	fUnknown01                          = 0x00000002,
	fUnknown02                          = 0x00000004,
	fUnknown03                          = 0x00000008,
	fUnknown04                          = 0x00000010,
	fUnknown05                          = 0x00000020,
	fUnknown06                          = 0x00000040,
	fUnknown07                          = 0x00000080,
	fUnknown08                          = 0x00000100,
	fUnknown09                          = 0x00000200,
	fUnknown10                          = 0x00000400,
	fUnknown11                          = 0x00000800,
	fUnknown12                          = 0x00001000,
	fUnknown13                          = 0x00002000,
	fUnknown14                          = 0x00004000,
	fUnknown15                          = 0x00008000,
	fUnknown16                          = 0x00010000,
	fUnknown17                          = 0x00020000,
	fUnknown18                          = 0x00040000,
	fUnknown19                          = 0x00080000,
	fUnknown20                          = 0x00100000,
	fUnknown21                          = 0x00200000,
	fUnknown22                          = 0x00400000,
	fUnknown23                          = 0x00800000,
	fUnknown24                          = 0x01000000,
	fUnknown25                          = 0x02000000,
	fUnknown26                          = 0x04000000,
	fUnknown27                          = 0x08000000,
	fUnknown28                          = 0x10000000,
	fUnknown29                          = 0x20000000,
	fUnknown30                          = 0x40000000,
	fUnknown31                          = 0x80000000
      };

    public:
      UINT16 formVersion; //TES5
      UINT8  versionControl2[2]; //TES5

      TES5Record(unsigned char *_recData=NULL);
      virtual ~TES5Record();

      bool Read();
      UINT32 Write(FileWriter &writer, const bool &bMastersChanged, FormIDResolver &expander, FormIDResolver &collapser, std::vector<FormIDResolver *> &Expanders);
    };