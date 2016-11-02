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
#include "..\..\Common.h"
#include "RACERecord.h"

namespace FNV
{
void RACERecord::RACEPart::Write(uint32_t index, FileWriter &writer)
    {
    writer.record_write_subrecord(REV32(INDX), &index, 4);
    MODL.Write(writer);
    WRITE(ICON);
    WRITE(MICO);
    }

void RACERecord::RACEPart::WriteIconsFirst(uint32_t index, FileWriter &writer)
    {
    writer.record_write_subrecord(REV32(INDX), &index, 4);
    WRITE(ICON);
    WRITE(MICO);
    MODL.Write(writer);
    }

bool RACERecord::RACEPart::operator ==(const RACEPart &other) const
    {
    return (MODL == other.MODL &&
            ICON.equalsi(other.ICON) &&
            MICO.equalsi(other.MICO));
    }

bool RACERecord::RACEPart::operator !=(const RACEPart &other) const
    {
    return !(*this == other);
    }

RACERecord::RACERecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

RACERecord::RACERecord(RACERecord *srcRecord):
    FNVRecord()
    {
    if(srcRecord == NULL)
        return;

    flags = srcRecord->flags;
    formID = srcRecord->formID;
    flagsUnk = srcRecord->flagsUnk;
    formVersion = srcRecord->formVersion;
    versionControl2[0] = srcRecord->versionControl2[0];
    versionControl2[1] = srcRecord->versionControl2[1];

    recData = srcRecord->recData;
    if(!srcRecord->IsChanged())
        return;

    EDID = srcRecord->EDID;
    FULL = srcRecord->FULL;
    DESC = srcRecord->DESC;
    XNAM = srcRecord->XNAM;
    DATA = srcRecord->DATA;
    ONAM = srcRecord->ONAM;
    YNAM = srcRecord->YNAM;
    VTCK = srcRecord->VTCK;
    DNAM = srcRecord->DNAM;
    CNAM = srcRecord->CNAM;
    PNAM = srcRecord->PNAM;
    UNAM = srcRecord->UNAM;
    ATTR = srcRecord->ATTR;

    MHMOD0 = srcRecord->MHMOD0;
    MHMOD1 = srcRecord->MHMOD1;
    MHMOD2 = srcRecord->MHMOD2;
    MHMOD3 = srcRecord->MHMOD3;
    MHMOD4 = srcRecord->MHMOD4;
    MHMOD5 = srcRecord->MHMOD5;
    MHMOD6 = srcRecord->MHMOD6;
    MHMOD7 = srcRecord->MHMOD7;

    FHMOD0 = srcRecord->FHMOD0;
    FHMOD1 = srcRecord->FHMOD1;
    FHMOD2 = srcRecord->FHMOD2;
    FHMOD3 = srcRecord->FHMOD3;
    FHMOD4 = srcRecord->FHMOD4;
    FHMOD5 = srcRecord->FHMOD5;
    FHMOD6 = srcRecord->FHMOD6;
    FHMOD7 = srcRecord->FHMOD7;

    MBMOD0 = srcRecord->MBMOD0;
    MBMOD1 = srcRecord->MBMOD1;
    MBMOD2 = srcRecord->MBMOD2;
    MBMOD3 = srcRecord->MBMOD3;

    FBMOD0 = srcRecord->FBMOD0;
    FBMOD1 = srcRecord->FBMOD1;
    FBMOD2 = srcRecord->FBMOD2;
    FBMOD3 = srcRecord->FBMOD3;

    HNAM = srcRecord->HNAM;
    ENAM = srcRecord->ENAM;

    MaleFGGS = srcRecord->MaleFGGS;
    MaleFGGA = srcRecord->MaleFGGA;
    MaleFGTS = srcRecord->MaleFGTS;
    MaleSNAM = srcRecord->MaleSNAM;

    FemaleFGGS = srcRecord->FemaleFGGS;
    FemaleFGGA = srcRecord->FemaleFGGA;
    FemaleFGTS = srcRecord->FemaleFGTS;
    FemaleSNAM = srcRecord->FemaleSNAM;
    return;
    }

RACERecord::~RACERecord()
    {
    //
    }

bool RACERecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(uint32_t ListIndex = 0; ListIndex < XNAM.value.size(); ListIndex++)
        op.Accept(XNAM.value[ListIndex]->faction);
    if(ONAM.IsLoaded())
        op.Accept(ONAM.value);
    if(YNAM.IsLoaded())
        op.Accept(YNAM.value);
    if(VTCK.IsLoaded())
        {
        op.Accept(VTCK.value.maleVoice);
        op.Accept(VTCK.value.femaleVoice);
        }
    if(DNAM.IsLoaded())
        {
        op.Accept(DNAM.value.defaultHairMale);
        op.Accept(DNAM.value.defaultHairFemale);
        }

    if(MHMOD0.MODL.IsLoaded())
        {
        for(uint32_t ListIndex = 0; ListIndex < MHMOD0.MODL->Textures.MODS.size(); ListIndex++)
            op.Accept(MHMOD0.MODL->Textures.MODS[ListIndex]->texture);
        }

    if(MHMOD1.MODL.IsLoaded())
        {
        for(uint32_t ListIndex = 0; ListIndex < MHMOD1.MODL->Textures.MODS.size(); ListIndex++)
            op.Accept(MHMOD1.MODL->Textures.MODS[ListIndex]->texture);
        }

    if(MHMOD2.MODL.IsLoaded())
        {
        for(uint32_t ListIndex = 0; ListIndex < MHMOD2.MODL->Textures.MODS.size(); ListIndex++)
            op.Accept(MHMOD2.MODL->Textures.MODS[ListIndex]->texture);
        }

    if(MHMOD3.MODL.IsLoaded())
        {
        for(uint32_t ListIndex = 0; ListIndex < MHMOD3.MODL->Textures.MODS.size(); ListIndex++)
            op.Accept(MHMOD3.MODL->Textures.MODS[ListIndex]->texture);
        }

    if(MHMOD4.MODL.IsLoaded())
        {
        for(uint32_t ListIndex = 0; ListIndex < MHMOD4.MODL->Textures.MODS.size(); ListIndex++)
            op.Accept(MHMOD4.MODL->Textures.MODS[ListIndex]->texture);
        }

    if(MHMOD5.MODL.IsLoaded())
        {
        for(uint32_t ListIndex = 0; ListIndex < MHMOD5.MODL->Textures.MODS.size(); ListIndex++)
            op.Accept(MHMOD5.MODL->Textures.MODS[ListIndex]->texture);
        }

    if(MHMOD6.MODL.IsLoaded())
        {
        for(uint32_t ListIndex = 0; ListIndex < MHMOD6.MODL->Textures.MODS.size(); ListIndex++)
            op.Accept(MHMOD6.MODL->Textures.MODS[ListIndex]->texture);
        }

    if(MHMOD7.MODL.IsLoaded())
        {
        for(uint32_t ListIndex = 0; ListIndex < MHMOD7.MODL->Textures.MODS.size(); ListIndex++)
            op.Accept(MHMOD7.MODL->Textures.MODS[ListIndex]->texture);
        }

    if(FHMOD0.MODL.IsLoaded())
        {
        for(uint32_t ListIndex = 0; ListIndex < FHMOD0.MODL->Textures.MODS.size(); ListIndex++)
            op.Accept(FHMOD0.MODL->Textures.MODS[ListIndex]->texture);
        }

    if(FHMOD1.MODL.IsLoaded())
        {
        for(uint32_t ListIndex = 0; ListIndex < FHMOD1.MODL->Textures.MODS.size(); ListIndex++)
            op.Accept(FHMOD1.MODL->Textures.MODS[ListIndex]->texture);
        }

    if(FHMOD2.MODL.IsLoaded())
        {
        for(uint32_t ListIndex = 0; ListIndex < FHMOD2.MODL->Textures.MODS.size(); ListIndex++)
            op.Accept(FHMOD2.MODL->Textures.MODS[ListIndex]->texture);
        }

    if(FHMOD3.MODL.IsLoaded())
        {
        for(uint32_t ListIndex = 0; ListIndex < FHMOD3.MODL->Textures.MODS.size(); ListIndex++)
            op.Accept(FHMOD3.MODL->Textures.MODS[ListIndex]->texture);
        }

    if(FHMOD4.MODL.IsLoaded())
        {
        for(uint32_t ListIndex = 0; ListIndex < FHMOD4.MODL->Textures.MODS.size(); ListIndex++)
            op.Accept(FHMOD4.MODL->Textures.MODS[ListIndex]->texture);
        }

    if(FHMOD5.MODL.IsLoaded())
        {
        for(uint32_t ListIndex = 0; ListIndex < FHMOD5.MODL->Textures.MODS.size(); ListIndex++)
            op.Accept(FHMOD5.MODL->Textures.MODS[ListIndex]->texture);
        }

    if(FHMOD6.MODL.IsLoaded())
        {
        for(uint32_t ListIndex = 0; ListIndex < FHMOD6.MODL->Textures.MODS.size(); ListIndex++)
            op.Accept(FHMOD6.MODL->Textures.MODS[ListIndex]->texture);
        }

    if(FHMOD7.MODL.IsLoaded())
        {
        for(uint32_t ListIndex = 0; ListIndex < FHMOD7.MODL->Textures.MODS.size(); ListIndex++)
            op.Accept(FHMOD7.MODL->Textures.MODS[ListIndex]->texture);
        }

    if(MBMOD0.MODL.IsLoaded())
        {
        for(uint32_t ListIndex = 0; ListIndex < MBMOD0.MODL->Textures.MODS.size(); ListIndex++)
            op.Accept(MBMOD0.MODL->Textures.MODS[ListIndex]->texture);
        }

    if(MBMOD1.MODL.IsLoaded())
        {
        for(uint32_t ListIndex = 0; ListIndex < MBMOD1.MODL->Textures.MODS.size(); ListIndex++)
            op.Accept(MBMOD1.MODL->Textures.MODS[ListIndex]->texture);
        }

    if(MBMOD2.MODL.IsLoaded())
        {
        for(uint32_t ListIndex = 0; ListIndex < MBMOD2.MODL->Textures.MODS.size(); ListIndex++)
            op.Accept(MBMOD2.MODL->Textures.MODS[ListIndex]->texture);
        }

    if(MBMOD3.MODL.IsLoaded())
        {
        for(uint32_t ListIndex = 0; ListIndex < MBMOD3.MODL->Textures.MODS.size(); ListIndex++)
            op.Accept(MBMOD3.MODL->Textures.MODS[ListIndex]->texture);
        }

    if(FBMOD0.MODL.IsLoaded())
        {
        for(uint32_t ListIndex = 0; ListIndex < FBMOD0.MODL->Textures.MODS.size(); ListIndex++)
            op.Accept(FBMOD0.MODL->Textures.MODS[ListIndex]->texture);
        }

    if(FBMOD1.MODL.IsLoaded())
        {
        for(uint32_t ListIndex = 0; ListIndex < FBMOD1.MODL->Textures.MODS.size(); ListIndex++)
            op.Accept(FBMOD1.MODL->Textures.MODS[ListIndex]->texture);
        }

    if(FBMOD2.MODL.IsLoaded())
        {
        for(uint32_t ListIndex = 0; ListIndex < FBMOD2.MODL->Textures.MODS.size(); ListIndex++)
            op.Accept(FBMOD2.MODL->Textures.MODS[ListIndex]->texture);
        }

    if(FBMOD3.MODL.IsLoaded())
        {
        for(uint32_t ListIndex = 0; ListIndex < FBMOD3.MODL->Textures.MODS.size(); ListIndex++)
            op.Accept(FBMOD3.MODL->Textures.MODS[ListIndex]->texture);
        }

    for(uint32_t ListIndex = 0; ListIndex < HNAM.value.size(); ListIndex++)
        op.Accept(HNAM.value[ListIndex]);
    for(uint32_t ListIndex = 0; ListIndex < ENAM.value.size(); ListIndex++)
        op.Accept(ENAM.value[ListIndex]);

    return op.Stop();
    }

bool RACERecord::IsPlayable()
    {
    return (DATA.value.flags & fIsPlayable) != 0;
    }

void RACERecord::IsPlayable(bool value)
    {
    SETBIT(DATA.value.flags, fIsPlayable, value);
    }

bool RACERecord::IsChild()
    {
    return (DATA.value.flags & fIsChild) != 0;
    }

void RACERecord::IsChild(bool value)
    {
    SETBIT(DATA.value.flags, fIsChild, value);
    }

bool RACERecord::IsFlagMask(uint32_t Mask, bool Exact)
    {
    return Exact ? ((DATA.value.flags & Mask) == Mask) : ((DATA.value.flags & Mask) != 0);
    }

void RACERecord::SetFlagMask(uint32_t Mask)
    {
    DATA.value.flags = Mask;
    }

uint32_t RACERecord::GetType()
    {
    return REV32(RACE);
    }

char * RACERecord::GetStrType()
    {
    return "RACE";
    }

int32_t RACERecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
    {
    enum namFlags
        {
        fIsMale   = 0x10000000,
        fIsFemale = 0x20000000,
        fIsHead   = 0x40000000,
        fIsBody   = 0x80000000
        };

    enum headEnum
        {
        eHead = 0,
        eEars,
        eMouth,
        eLowerTeeth,
        eUpperTeeth,
        eTongue,
        eLeftEye,
        eRightEye
        };

    enum bodyEnum
        {
        eUpperBody = 0,
        eLeftHand,
        eRightHand,
        eUpperBodyTexture
        };

    uint32_t subType = 0;
    uint32_t subSize = 0;
    uint32_t part_id = 0;
    uint32_t temp_id = 0;
    while(buffer < end_buffer){
        subType = *(uint32_t *)buffer;
        buffer += 4;
        switch(subType)
            {
            case REV32(XXXX):
                buffer += 2;
                subSize = *(uint32_t *)buffer;
                buffer += 4;
                subType = *(uint32_t *)buffer;
                buffer += 6;
                break;
            default:
                subSize = *(uint16_t *)buffer;
                buffer += 2;
                break;
            }
        switch(subType)
            {
            case REV32(EDID):
                EDID.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(FULL):
                FULL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(DESC):
                DESC.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(XNAM):
                XNAM.Read(buffer, subSize);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(ONAM):
                ONAM.Read(buffer, subSize);
                break;
            case REV32(YNAM):
                YNAM.Read(buffer, subSize);
                break;
            case REV32(NAM2): //Unknown empty marker
                break;
            case REV32(VTCK):
                VTCK.Read(buffer, subSize);
                break;
            case REV32(DNAM):
                DNAM.Read(buffer, subSize);
                break;
            case REV32(CNAM):
                CNAM.Read(buffer, subSize);
                break;
            case REV32(PNAM):
                PNAM.Read(buffer, subSize);
                break;
            case REV32(UNAM):
                UNAM.Read(buffer, subSize);
                break;
            case REV32(ATTR):
                ATTR.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(NAM0):
                part_id = fIsHead;
                break;
            case REV32(NAM1):
                part_id = fIsBody;
                break;
            case REV32(MNAM):
                part_id = (part_id & ~fIsFemale) | fIsMale;
                break;
            case REV32(FNAM):
                part_id = (part_id & ~fIsMale) | fIsFemale;
                break;
            case REV32(INDX):
                temp_id = *(uint32_t *)buffer;
                buffer += 4;
                part_id = (part_id & 0xFF000000) | temp_id;
                break;
            case REV32(MODL):
                switch(part_id)
                    {
                    case fIsHead | fIsMale | eHead:
                        MHMOD0.MODL.Load();
                        MHMOD0.MODL->MODL.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsMale | eEars:
                        MHMOD1.MODL.Load();
                        MHMOD1.MODL->MODL.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsMale | eMouth:
                        MHMOD2.MODL.Load();
                        MHMOD2.MODL->MODL.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsMale | eLowerTeeth:
                        MHMOD3.MODL.Load();
                        MHMOD3.MODL->MODL.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsMale | eUpperTeeth:
                        MHMOD4.MODL.Load();
                        MHMOD4.MODL->MODL.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsMale | eTongue:
                        MHMOD5.MODL.Load();
                        MHMOD5.MODL->MODL.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsMale | eLeftEye:
                        MHMOD6.MODL.Load();
                        MHMOD6.MODL->MODL.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsMale | eRightEye:
                        MHMOD7.MODL.Load();
                        MHMOD7.MODL->MODL.Read(buffer, subSize, CompressedOnDisk);
                        break;

                    case fIsHead | fIsFemale | eHead:
                        FHMOD0.MODL.Load();
                        FHMOD0.MODL->MODL.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsFemale | eEars:
                        FHMOD1.MODL.Load();
                        FHMOD1.MODL->MODL.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsFemale | eMouth:
                        FHMOD2.MODL.Load();
                        FHMOD2.MODL->MODL.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsFemale | eLowerTeeth:
                        FHMOD3.MODL.Load();
                        FHMOD3.MODL->MODL.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsFemale | eUpperTeeth:
                        FHMOD4.MODL.Load();
                        FHMOD4.MODL->MODL.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsFemale | eTongue:
                        FHMOD5.MODL.Load();
                        FHMOD5.MODL->MODL.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsFemale | eLeftEye:
                        FHMOD6.MODL.Load();
                        FHMOD6.MODL->MODL.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsFemale | eRightEye:
                        FHMOD7.MODL.Load();
                        FHMOD7.MODL->MODL.Read(buffer, subSize, CompressedOnDisk);
                        break;

                    case fIsBody | fIsMale | eUpperBody:
                        MBMOD0.MODL.Load();
                        MBMOD0.MODL->MODL.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsBody | fIsMale | eLeftHand:
                        MBMOD1.MODL.Load();
                        MBMOD1.MODL->MODL.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsBody | fIsMale | eRightHand:
                        MBMOD2.MODL.Load();
                        MBMOD2.MODL->MODL.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsBody | fIsMale | eUpperBodyTexture:
                        MBMOD3.MODL.Load();
                        MBMOD3.MODL->MODL.Read(buffer, subSize, CompressedOnDisk);
                        break;

                    case fIsBody | fIsFemale | eUpperBody:
                        FBMOD0.MODL.Load();
                        FBMOD0.MODL->MODL.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsBody | fIsFemale | eLeftHand:
                        FBMOD1.MODL.Load();
                        FBMOD1.MODL->MODL.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsBody | fIsFemale | eRightHand:
                        FBMOD2.MODL.Load();
                        FBMOD2.MODL->MODL.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsBody | fIsFemale | eUpperBodyTexture:
                        FBMOD3.MODL.Load();
                        FBMOD3.MODL->MODL.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    default:
                        //ERROR
                        //printer("FileName = %s\n", FileName);
                        printer("  RACE: %08X - Unexpected MODL\n", formID);
                        CBASH_CHUNK_DEBUG
                        printer("  Size = %i\n", subSize);
                        printer("  CurPos = %04x\n\n", buffer - 6);
                        buffer = end_buffer;
                        break;
                    }
                break;
            case REV32(MODB):
                switch(part_id)
                    {
                    case fIsHead | fIsMale | eHead:
                        MHMOD0.MODL.Load();
                        MHMOD0.MODL->MODB.Read(buffer, subSize);
                        break;
                    case fIsHead | fIsMale | eEars:
                        MHMOD1.MODL.Load();
                        MHMOD1.MODL->MODB.Read(buffer, subSize);
                        break;
                    case fIsHead | fIsMale | eMouth:
                        MHMOD2.MODL.Load();
                        MHMOD2.MODL->MODB.Read(buffer, subSize);
                        break;
                    case fIsHead | fIsMale | eLowerTeeth:
                        MHMOD3.MODL.Load();
                        MHMOD3.MODL->MODB.Read(buffer, subSize);
                        break;
                    case fIsHead | fIsMale | eUpperTeeth:
                        MHMOD4.MODL.Load();
                        MHMOD4.MODL->MODB.Read(buffer, subSize);
                        break;
                    case fIsHead | fIsMale | eTongue:
                        MHMOD5.MODL.Load();
                        MHMOD5.MODL->MODB.Read(buffer, subSize);
                        break;
                    case fIsHead | fIsMale | eLeftEye:
                        MHMOD6.MODL.Load();
                        MHMOD6.MODL->MODB.Read(buffer, subSize);
                        break;
                    case fIsHead | fIsMale | eRightEye:
                        MHMOD7.MODL.Load();
                        MHMOD7.MODL->MODB.Read(buffer, subSize);
                        break;

                    case fIsHead | fIsFemale | eHead:
                        FHMOD0.MODL.Load();
                        FHMOD0.MODL->MODB.Read(buffer, subSize);
                        break;
                    case fIsHead | fIsFemale | eEars:
                        FHMOD1.MODL.Load();
                        FHMOD1.MODL->MODB.Read(buffer, subSize);
                        break;
                    case fIsHead | fIsFemale | eMouth:
                        FHMOD2.MODL.Load();
                        FHMOD2.MODL->MODB.Read(buffer, subSize);
                        break;
                    case fIsHead | fIsFemale | eLowerTeeth:
                        FHMOD3.MODL.Load();
                        FHMOD3.MODL->MODB.Read(buffer, subSize);
                        break;
                    case fIsHead | fIsFemale | eUpperTeeth:
                        FHMOD4.MODL.Load();
                        FHMOD4.MODL->MODB.Read(buffer, subSize);
                        break;
                    case fIsHead | fIsFemale | eTongue:
                        FHMOD5.MODL.Load();
                        FHMOD5.MODL->MODB.Read(buffer, subSize);
                        break;
                    case fIsHead | fIsFemale | eLeftEye:
                        FHMOD6.MODL.Load();
                        FHMOD6.MODL->MODB.Read(buffer, subSize);
                        break;
                    case fIsHead | fIsFemale | eRightEye:
                        FHMOD7.MODL.Load();
                        FHMOD7.MODL->MODB.Read(buffer, subSize);
                        break;

                    case fIsBody | fIsMale | eUpperBody:
                        MBMOD0.MODL.Load();
                        MBMOD0.MODL->MODB.Read(buffer, subSize);
                        break;
                    case fIsBody | fIsMale | eLeftHand:
                        MBMOD1.MODL.Load();
                        MBMOD1.MODL->MODB.Read(buffer, subSize);
                        break;
                    case fIsBody | fIsMale | eRightHand:
                        MBMOD2.MODL.Load();
                        MBMOD2.MODL->MODB.Read(buffer, subSize);
                        break;
                    case fIsBody | fIsMale | eUpperBodyTexture:
                        MBMOD3.MODL.Load();
                        MBMOD3.MODL->MODB.Read(buffer, subSize);
                        break;

                    case fIsBody | fIsFemale | eUpperBody:
                        FBMOD0.MODL.Load();
                        FBMOD0.MODL->MODB.Read(buffer, subSize);
                        break;
                    case fIsBody | fIsFemale | eLeftHand:
                        FBMOD1.MODL.Load();
                        FBMOD1.MODL->MODB.Read(buffer, subSize);
                        break;
                    case fIsBody | fIsFemale | eRightHand:
                        FBMOD2.MODL.Load();
                        FBMOD2.MODL->MODB.Read(buffer, subSize);
                        break;
                    case fIsBody | fIsFemale | eUpperBodyTexture:
                        FBMOD3.MODL.Load();
                        FBMOD3.MODL->MODB.Read(buffer, subSize);
                        break;
                    default:
                        //ERROR
                        //printer("FileName = %s\n", FileName);
                        printer("  RACE: %08X - Unexpected MODB\n", formID);
                        CBASH_CHUNK_DEBUG
                        printer("  Size = %i\n", subSize);
                        printer("  CurPos = %04x\n\n", buffer - 6);
                        buffer = end_buffer;
                        break;
                    }
                break;
            case REV32(MODT):
                switch(part_id)
                    {
                    case fIsHead | fIsMale | eHead:
                        MHMOD0.MODL.Load();
                        MHMOD0.MODL->MODT.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsMale | eEars:
                        MHMOD1.MODL.Load();
                        MHMOD1.MODL->MODT.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsMale | eMouth:
                        MHMOD2.MODL.Load();
                        MHMOD2.MODL->MODT.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsMale | eLowerTeeth:
                        MHMOD3.MODL.Load();
                        MHMOD3.MODL->MODT.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsMale | eUpperTeeth:
                        MHMOD4.MODL.Load();
                        MHMOD4.MODL->MODT.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsMale | eTongue:
                        MHMOD5.MODL.Load();
                        MHMOD5.MODL->MODT.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsMale | eLeftEye:
                        MHMOD6.MODL.Load();
                        MHMOD6.MODL->MODT.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsMale | eRightEye:
                        MHMOD7.MODL.Load();
                        MHMOD7.MODL->MODT.Read(buffer, subSize, CompressedOnDisk);
                        break;

                    case fIsHead | fIsFemale | eHead:
                        FHMOD0.MODL.Load();
                        FHMOD0.MODL->MODT.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsFemale | eEars:
                        FHMOD1.MODL.Load();
                        FHMOD1.MODL->MODT.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsFemale | eMouth:
                        FHMOD2.MODL.Load();
                        FHMOD2.MODL->MODT.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsFemale | eLowerTeeth:
                        FHMOD3.MODL.Load();
                        FHMOD3.MODL->MODT.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsFemale | eUpperTeeth:
                        FHMOD4.MODL.Load();
                        FHMOD4.MODL->MODT.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsFemale | eTongue:
                        FHMOD5.MODL.Load();
                        FHMOD5.MODL->MODT.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsFemale | eLeftEye:
                        FHMOD6.MODL.Load();
                        FHMOD6.MODL->MODT.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsFemale | eRightEye:
                        FHMOD7.MODL.Load();
                        FHMOD7.MODL->MODT.Read(buffer, subSize, CompressedOnDisk);
                        break;

                    case fIsBody | fIsMale | eUpperBody:
                        MBMOD0.MODL.Load();
                        MBMOD0.MODL->MODT.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsBody | fIsMale | eLeftHand:
                        MBMOD1.MODL.Load();
                        MBMOD1.MODL->MODT.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsBody | fIsMale | eRightHand:
                        MBMOD2.MODL.Load();
                        MBMOD2.MODL->MODT.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsBody | fIsMale | eUpperBodyTexture:
                        MBMOD3.MODL.Load();
                        MBMOD3.MODL->MODT.Read(buffer, subSize, CompressedOnDisk);
                        break;

                    case fIsBody | fIsFemale | eUpperBody:
                        FBMOD0.MODL.Load();
                        FBMOD0.MODL->MODT.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsBody | fIsFemale | eLeftHand:
                        FBMOD1.MODL.Load();
                        FBMOD1.MODL->MODT.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsBody | fIsFemale | eRightHand:
                        FBMOD2.MODL.Load();
                        FBMOD2.MODL->MODT.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsBody | fIsFemale | eUpperBodyTexture:
                        FBMOD3.MODL.Load();
                        FBMOD3.MODL->MODT.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    default:
                        //ERROR
                        //printer("FileName = %s\n", FileName);
                        printer("  RACE: %08X - Unexpected MODT\n", formID);
                        CBASH_CHUNK_DEBUG
                        printer("  Size = %i\n", subSize);
                        printer("  CurPos = %04x\n\n", buffer - 6);
                        buffer = end_buffer;
                        break;
                    }
                break;
            case REV32(MODS):
                switch(part_id)
                    {
                    case fIsHead | fIsMale | eHead:
                        MHMOD0.MODL.Load();
                        MHMOD0.MODL->Textures.Read(buffer, subSize);
                        break;
                    case fIsHead | fIsMale | eEars:
                        MHMOD1.MODL.Load();
                        MHMOD1.MODL->Textures.Read(buffer, subSize);
                        break;
                    case fIsHead | fIsMale | eMouth:
                        MHMOD2.MODL.Load();
                        MHMOD2.MODL->Textures.Read(buffer, subSize);
                        break;
                    case fIsHead | fIsMale | eLowerTeeth:
                        MHMOD3.MODL.Load();
                        MHMOD3.MODL->Textures.Read(buffer, subSize);
                        break;
                    case fIsHead | fIsMale | eUpperTeeth:
                        MHMOD4.MODL.Load();
                        MHMOD4.MODL->Textures.Read(buffer, subSize);
                        break;
                    case fIsHead | fIsMale | eTongue:
                        MHMOD5.MODL.Load();
                        MHMOD5.MODL->Textures.Read(buffer, subSize);
                        break;
                    case fIsHead | fIsMale | eLeftEye:
                        MHMOD6.MODL.Load();
                        MHMOD6.MODL->Textures.Read(buffer, subSize);
                        break;
                    case fIsHead | fIsMale | eRightEye:
                        MHMOD7.MODL.Load();
                        MHMOD7.MODL->Textures.Read(buffer, subSize);
                        break;

                    case fIsHead | fIsFemale | eHead:
                        FHMOD0.MODL.Load();
                        FHMOD0.MODL->Textures.Read(buffer, subSize);
                        break;
                    case fIsHead | fIsFemale | eEars:
                        FHMOD1.MODL.Load();
                        FHMOD1.MODL->Textures.Read(buffer, subSize);
                        break;
                    case fIsHead | fIsFemale | eMouth:
                        FHMOD2.MODL.Load();
                        FHMOD2.MODL->Textures.Read(buffer, subSize);
                        break;
                    case fIsHead | fIsFemale | eLowerTeeth:
                        FHMOD3.MODL.Load();
                        FHMOD3.MODL->Textures.Read(buffer, subSize);
                        break;
                    case fIsHead | fIsFemale | eUpperTeeth:
                        FHMOD4.MODL.Load();
                        FHMOD4.MODL->Textures.Read(buffer, subSize);
                        break;
                    case fIsHead | fIsFemale | eTongue:
                        FHMOD5.MODL.Load();
                        FHMOD5.MODL->Textures.Read(buffer, subSize);
                        break;
                    case fIsHead | fIsFemale | eLeftEye:
                        FHMOD6.MODL.Load();
                        FHMOD6.MODL->Textures.Read(buffer, subSize);
                        break;
                    case fIsHead | fIsFemale | eRightEye:
                        FHMOD7.MODL.Load();
                        FHMOD7.MODL->Textures.Read(buffer, subSize);
                        break;

                    case fIsBody | fIsMale | eUpperBody:
                        MBMOD0.MODL.Load();
                        MBMOD0.MODL->Textures.Read(buffer, subSize);
                        break;
                    case fIsBody | fIsMale | eLeftHand:
                        MBMOD1.MODL.Load();
                        MBMOD1.MODL->Textures.Read(buffer, subSize);
                        break;
                    case fIsBody | fIsMale | eRightHand:
                        MBMOD2.MODL.Load();
                        MBMOD2.MODL->Textures.Read(buffer, subSize);
                        break;
                    case fIsBody | fIsMale | eUpperBodyTexture:
                        MBMOD3.MODL.Load();
                        MBMOD3.MODL->Textures.Read(buffer, subSize);
                        break;

                    case fIsBody | fIsFemale | eUpperBody:
                        FBMOD0.MODL.Load();
                        FBMOD0.MODL->Textures.Read(buffer, subSize);
                        break;
                    case fIsBody | fIsFemale | eLeftHand:
                        FBMOD1.MODL.Load();
                        FBMOD1.MODL->Textures.Read(buffer, subSize);
                        break;
                    case fIsBody | fIsFemale | eRightHand:
                        FBMOD2.MODL.Load();
                        FBMOD2.MODL->Textures.Read(buffer, subSize);
                        break;
                    case fIsBody | fIsFemale | eUpperBodyTexture:
                        FBMOD3.MODL.Load();
                        FBMOD3.MODL->Textures.Read(buffer, subSize);
                        break;
                    default:
                        //ERROR
                        //printer("FileName = %s\n", FileName);
                        printer("  RACE: %08X - Unexpected MODS\n", formID);
                        CBASH_CHUNK_DEBUG
                        printer("  Size = %i\n", subSize);
                        printer("  CurPos = %04x\n\n", buffer - 6);
                        buffer = end_buffer;
                        break;
                    }
                break;
            case REV32(MODD):
                switch(part_id)
                    {
                    case fIsHead | fIsMale | eHead:
                        MHMOD0.MODL.Load();
                        MHMOD0.MODL->MODD.Read(buffer, subSize);
                        break;
                    case fIsHead | fIsMale | eEars:
                        MHMOD1.MODL.Load();
                        MHMOD1.MODL->MODD.Read(buffer, subSize);
                        break;
                    case fIsHead | fIsMale | eMouth:
                        MHMOD2.MODL.Load();
                        MHMOD2.MODL->MODD.Read(buffer, subSize);
                        break;
                    case fIsHead | fIsMale | eLowerTeeth:
                        MHMOD3.MODL.Load();
                        MHMOD3.MODL->MODD.Read(buffer, subSize);
                        break;
                    case fIsHead | fIsMale | eUpperTeeth:
                        MHMOD4.MODL.Load();
                        MHMOD4.MODL->MODD.Read(buffer, subSize);
                        break;
                    case fIsHead | fIsMale | eTongue:
                        MHMOD5.MODL.Load();
                        MHMOD5.MODL->MODD.Read(buffer, subSize);
                        break;
                    case fIsHead | fIsMale | eLeftEye:
                        MHMOD6.MODL.Load();
                        MHMOD6.MODL->MODD.Read(buffer, subSize);
                        break;
                    case fIsHead | fIsMale | eRightEye:
                        MHMOD7.MODL.Load();
                        MHMOD7.MODL->MODD.Read(buffer, subSize);
                        break;

                    case fIsHead | fIsFemale | eHead:
                        FHMOD0.MODL.Load();
                        FHMOD0.MODL->MODD.Read(buffer, subSize);
                        break;
                    case fIsHead | fIsFemale | eEars:
                        FHMOD1.MODL.Load();
                        FHMOD1.MODL->MODD.Read(buffer, subSize);
                        break;
                    case fIsHead | fIsFemale | eMouth:
                        FHMOD2.MODL.Load();
                        FHMOD2.MODL->MODD.Read(buffer, subSize);
                        break;
                    case fIsHead | fIsFemale | eLowerTeeth:
                        FHMOD3.MODL.Load();
                        FHMOD3.MODL->MODD.Read(buffer, subSize);
                        break;
                    case fIsHead | fIsFemale | eUpperTeeth:
                        FHMOD4.MODL.Load();
                        FHMOD4.MODL->MODD.Read(buffer, subSize);
                        break;
                    case fIsHead | fIsFemale | eTongue:
                        FHMOD5.MODL.Load();
                        FHMOD5.MODL->MODD.Read(buffer, subSize);
                        break;
                    case fIsHead | fIsFemale | eLeftEye:
                        FHMOD6.MODL.Load();
                        FHMOD6.MODL->MODD.Read(buffer, subSize);
                        break;
                    case fIsHead | fIsFemale | eRightEye:
                        FHMOD7.MODL.Load();
                        FHMOD7.MODL->MODD.Read(buffer, subSize);
                        break;

                    case fIsBody | fIsMale | eUpperBody:
                        MBMOD0.MODL.Load();
                        MBMOD0.MODL->MODD.Read(buffer, subSize);
                        break;
                    case fIsBody | fIsMale | eLeftHand:
                        MBMOD1.MODL.Load();
                        MBMOD1.MODL->MODD.Read(buffer, subSize);
                        break;
                    case fIsBody | fIsMale | eRightHand:
                        MBMOD2.MODL.Load();
                        MBMOD2.MODL->MODD.Read(buffer, subSize);
                        break;
                    case fIsBody | fIsMale | eUpperBodyTexture:
                        MBMOD3.MODL.Load();
                        MBMOD3.MODL->MODD.Read(buffer, subSize);
                        break;

                    case fIsBody | fIsFemale | eUpperBody:
                        FBMOD0.MODL.Load();
                        FBMOD0.MODL->MODD.Read(buffer, subSize);
                        break;
                    case fIsBody | fIsFemale | eLeftHand:
                        FBMOD1.MODL.Load();
                        FBMOD1.MODL->MODD.Read(buffer, subSize);
                        break;
                    case fIsBody | fIsFemale | eRightHand:
                        FBMOD2.MODL.Load();
                        FBMOD2.MODL->MODD.Read(buffer, subSize);
                        break;
                    case fIsBody | fIsFemale | eUpperBodyTexture:
                        FBMOD3.MODL.Load();
                        FBMOD3.MODL->MODD.Read(buffer, subSize);
                        break;
                    default:
                        //ERROR
                        //printer("FileName = %s\n", FileName);
                        printer("  RACE: %08X - Unexpected MODD\n", formID);
                        CBASH_CHUNK_DEBUG
                        printer("  Size = %i\n", subSize);
                        printer("  CurPos = %04x\n\n", buffer - 6);
                        buffer = end_buffer;
                        break;
                    }
                break;
            case REV32(ICON):
                switch(part_id)
                    {
                    case fIsHead | fIsMale | eHead:
                        MHMOD0.ICON.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsMale | eEars:
                        MHMOD1.ICON.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsMale | eMouth:
                        MHMOD2.ICON.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsMale | eLowerTeeth:
                        MHMOD3.ICON.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsMale | eUpperTeeth:
                        MHMOD4.ICON.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsMale | eTongue:
                        MHMOD5.ICON.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsMale | eLeftEye:
                        MHMOD6.ICON.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsMale | eRightEye:
                        MHMOD7.ICON.Read(buffer, subSize, CompressedOnDisk);
                        break;

                    case fIsHead | fIsFemale | eHead:
                        FHMOD0.ICON.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsFemale | eEars:
                        FHMOD1.ICON.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsFemale | eMouth:
                        FHMOD2.ICON.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsFemale | eLowerTeeth:
                        FHMOD3.ICON.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsFemale | eUpperTeeth:
                        FHMOD4.ICON.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsFemale | eTongue:
                        FHMOD5.ICON.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsFemale | eLeftEye:
                        FHMOD6.ICON.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsFemale | eRightEye:
                        FHMOD7.ICON.Read(buffer, subSize, CompressedOnDisk);
                        break;

                    case fIsBody | fIsMale | eUpperBody:
                        MBMOD0.ICON.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsBody | fIsMale | eLeftHand:
                        MBMOD1.ICON.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsBody | fIsMale | eRightHand:
                        MBMOD2.ICON.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsBody | fIsMale | eUpperBodyTexture:
                        MBMOD3.ICON.Read(buffer, subSize, CompressedOnDisk);
                        break;

                    case fIsBody | fIsFemale | eUpperBody:
                        FBMOD0.ICON.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsBody | fIsFemale | eLeftHand:
                        FBMOD1.ICON.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsBody | fIsFemale | eRightHand:
                        FBMOD2.ICON.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsBody | fIsFemale | eUpperBodyTexture:
                        FBMOD3.ICON.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    default:
                        //ERROR
                        //printer("FileName = %s\n", FileName);
                        printer("  RACE: %08X - Unexpected ICON\n", formID);
                        CBASH_CHUNK_DEBUG
                        printer("  Size = %i\n", subSize);
                        printer("  CurPos = %04x\n\n", buffer - 6);
                        buffer = end_buffer;
                        break;
                    }
                break;
            case REV32(MICO):
                switch(part_id)
                    {
                    case fIsHead | fIsMale | eHead:
                        MHMOD0.MICO.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsMale | eEars:
                        MHMOD1.MICO.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsMale | eMouth:
                        MHMOD2.MICO.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsMale | eLowerTeeth:
                        MHMOD3.MICO.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsMale | eUpperTeeth:
                        MHMOD4.MICO.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsMale | eTongue:
                        MHMOD5.MICO.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsMale | eLeftEye:
                        MHMOD6.MICO.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsMale | eRightEye:
                        MHMOD7.MICO.Read(buffer, subSize, CompressedOnDisk);
                        break;

                    case fIsHead | fIsFemale | eHead:
                        FHMOD0.MICO.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsFemale | eEars:
                        FHMOD1.MICO.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsFemale | eMouth:
                        FHMOD2.MICO.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsFemale | eLowerTeeth:
                        FHMOD3.MICO.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsFemale | eUpperTeeth:
                        FHMOD4.MICO.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsFemale | eTongue:
                        FHMOD5.MICO.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsFemale | eLeftEye:
                        FHMOD6.MICO.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsHead | fIsFemale | eRightEye:
                        FHMOD7.MICO.Read(buffer, subSize, CompressedOnDisk);
                        break;

                    case fIsBody | fIsMale | eUpperBody:
                        MBMOD0.MICO.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsBody | fIsMale | eLeftHand:
                        MBMOD1.MICO.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsBody | fIsMale | eRightHand:
                        MBMOD2.MICO.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsBody | fIsMale | eUpperBodyTexture:
                        MBMOD3.MICO.Read(buffer, subSize, CompressedOnDisk);
                        break;

                    case fIsBody | fIsFemale | eUpperBody:
                        FBMOD0.MICO.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsBody | fIsFemale | eLeftHand:
                        FBMOD1.MICO.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsBody | fIsFemale | eRightHand:
                        FBMOD2.MICO.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsBody | fIsFemale | eUpperBodyTexture:
                        FBMOD3.MICO.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    default:
                        //ERROR
                        //printer("FileName = %s\n", FileName);
                        printer("  RACE: %08X - Unexpected MICO\n", formID);
                        CBASH_CHUNK_DEBUG
                        printer("  Size = %i\n", subSize);
                        printer("  CurPos = %04x\n\n", buffer - 6);
                        buffer = end_buffer;
                        break;
                    }
                break;
            case REV32(HNAM):
                HNAM.Read(buffer, subSize);
                break;
            case REV32(ENAM):
                ENAM.Read(buffer, subSize);
                break;
            case REV32(FGGS):
                part_id &= ~(fIsBody | fIsHead);
                switch(part_id & 0xFF000000)
                    {
                    case fIsMale: //Male
                        MaleFGGS.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsFemale: //Female
                        FemaleFGGS.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    default:
                        //printer("FileName = %s\n", FileName);
                        printer("  RACE: %08X - Unexpected FGGS\n", formID);
                        CBASH_CHUNK_DEBUG
                        printer("  Size = %i\n", subSize);
                        printer("  CurPos = %04x\n\n", buffer - 6);
                        buffer = end_buffer;
                        break;
                    }
                break;
            case REV32(FGGA):
                part_id &= ~(fIsBody | fIsHead);
                switch(part_id & 0xFF000000)
                    {
                    case fIsMale: //Male
                        MaleFGGA.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsFemale: //Female
                        FemaleFGGA.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    default:
                        //printer("FileName = %s\n", FileName);
                        printer("  RACE: %08X - Unexpected FGGA\n", formID);
                        CBASH_CHUNK_DEBUG
                        printer("  Size = %i\n", subSize);
                        printer("  CurPos = %04x\n\n", buffer - 6);
                        buffer = end_buffer;
                        break;
                    }
                break;
            case REV32(FGTS):
                part_id &= ~(fIsBody | fIsHead);
                switch(part_id & 0xFF000000)
                    {
                    case fIsMale: //Male
                        MaleFGTS.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsFemale: //Female
                        FemaleFGTS.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    default:
                        //printer("FileName = %s\n", FileName);
                        printer("  RACE: %08X - Unexpected FGTS\n", formID);
                        CBASH_CHUNK_DEBUG
                        printer("  Size = %i\n", subSize);
                        printer("  CurPos = %04x\n\n", buffer - 6);
                        buffer = end_buffer;
                        break;
                    }
                break;
            case REV32(SNAM):
                part_id &= ~(fIsBody | fIsHead);
                switch(part_id & 0xFF000000)
                    {
                    case fIsMale: //Male
                        MaleSNAM.Read(buffer, subSize);
                        break;
                    case fIsFemale: //Female
                        FemaleSNAM.Read(buffer, subSize);
                        break;
                    default:
                        //printer("FileName = %s\n", FileName);
                        printer("  RACE: %08X - Unexpected SNAM\n", formID);
                        CBASH_CHUNK_DEBUG
                        printer("  Size = %i\n", subSize);
                        printer("  CurPos = %04x\n\n", buffer - 6);
                        buffer = end_buffer;
                        break;
                    }
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  RACE: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t RACERecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    DESC.Unload();
    XNAM.Unload();
    DATA.Unload();
    ONAM.Unload();
    YNAM.Unload();
    VTCK.Unload();
    DNAM.Unload();
    CNAM.Unload();
    PNAM.Unload();
    UNAM.Unload();
    ATTR.Unload();

    MHMOD0.MODL.Unload();
    MHMOD0.ICON.Unload();
    MHMOD0.MICO.Unload();
    MHMOD1.MODL.Unload();
    MHMOD1.ICON.Unload();
    MHMOD1.MICO.Unload();
    MHMOD2.MODL.Unload();
    MHMOD2.ICON.Unload();
    MHMOD2.MICO.Unload();
    MHMOD3.MODL.Unload();
    MHMOD3.ICON.Unload();
    MHMOD3.MICO.Unload();
    MHMOD4.MODL.Unload();
    MHMOD4.ICON.Unload();
    MHMOD4.MICO.Unload();
    MHMOD5.MODL.Unload();
    MHMOD5.ICON.Unload();
    MHMOD5.MICO.Unload();
    MHMOD6.MODL.Unload();
    MHMOD6.ICON.Unload();
    MHMOD6.MICO.Unload();
    MHMOD7.MODL.Unload();
    MHMOD7.ICON.Unload();
    MHMOD7.MICO.Unload();

    FHMOD0.MODL.Unload();
    FHMOD0.ICON.Unload();
    FHMOD0.MICO.Unload();
    FHMOD1.MODL.Unload();
    FHMOD1.ICON.Unload();
    FHMOD1.MICO.Unload();
    FHMOD2.MODL.Unload();
    FHMOD2.ICON.Unload();
    FHMOD2.MICO.Unload();
    FHMOD3.MODL.Unload();
    FHMOD3.ICON.Unload();
    FHMOD3.MICO.Unload();
    FHMOD4.MODL.Unload();
    FHMOD4.ICON.Unload();
    FHMOD4.MICO.Unload();
    FHMOD5.MODL.Unload();
    FHMOD5.ICON.Unload();
    FHMOD5.MICO.Unload();
    FHMOD6.MODL.Unload();
    FHMOD6.ICON.Unload();
    FHMOD6.MICO.Unload();
    FHMOD7.MODL.Unload();
    FHMOD7.ICON.Unload();
    FHMOD7.MICO.Unload();

    MBMOD0.MODL.Unload();
    MBMOD0.ICON.Unload();
    MBMOD0.MICO.Unload();
    MBMOD1.MODL.Unload();
    MBMOD1.ICON.Unload();
    MBMOD1.MICO.Unload();
    MBMOD2.MODL.Unload();
    MBMOD2.ICON.Unload();
    MBMOD2.MICO.Unload();
    MBMOD3.MODL.Unload();
    MBMOD3.ICON.Unload();
    MBMOD3.MICO.Unload();

    FBMOD0.MODL.Unload();
    FBMOD0.ICON.Unload();
    FBMOD0.MICO.Unload();
    FBMOD1.MODL.Unload();
    FBMOD1.ICON.Unload();
    FBMOD1.MICO.Unload();
    FBMOD2.MODL.Unload();
    FBMOD2.ICON.Unload();
    FBMOD2.MICO.Unload();
    FBMOD3.MODL.Unload();
    FBMOD3.ICON.Unload();
    FBMOD3.MICO.Unload();

    HNAM.Unload();
    ENAM.Unload();

    MaleFGGS.Unload();
    MaleFGGA.Unload();
    MaleFGTS.Unload();
    MaleSNAM.Unload();

    FemaleFGGS.Unload();
    FemaleFGGA.Unload();
    FemaleFGTS.Unload();
    FemaleSNAM.Unload();
    return 1;
    }

int32_t RACERecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    WRITE(DESC);
    XNAM.Write(REV32(XNAM), writer, true);
    WRITE(DATA);
    WRITE(ONAM);
    WRITE(YNAM);

    WRITEEMPTY(NAM2);
    WRITE(VTCK);
    WRITE(DNAM);
    WRITE(CNAM);
    WRITE(PNAM);
    WRITE(UNAM);
    WRITE(ATTR);

    WRITEEMPTY(NAM0);
    WRITEEMPTY(MNAM);
    uint32_t curINDX = 0;
    MHMOD0.Write(curINDX++, writer);
    MHMOD1.Write(curINDX++, writer);
    MHMOD2.Write(curINDX++, writer);
    MHMOD3.Write(curINDX++, writer);
    MHMOD4.Write(curINDX++, writer);
    MHMOD5.Write(curINDX++, writer);
    MHMOD6.Write(curINDX++, writer);
    MHMOD7.Write(curINDX, writer);

    WRITEEMPTY(FNAM);
    curINDX = 0;
    FHMOD0.Write(curINDX++, writer);
    FHMOD1.Write(curINDX++, writer);
    FHMOD2.Write(curINDX++, writer);
    FHMOD3.Write(curINDX++, writer);
    FHMOD4.Write(curINDX++, writer);
    FHMOD5.Write(curINDX++, writer);
    FHMOD6.Write(curINDX++, writer);
    FHMOD7.Write(curINDX, writer);

    WRITEEMPTY(NAM1);
    WRITEEMPTY(MNAM);
    curINDX = 0;
    MBMOD0.WriteIconsFirst(curINDX++, writer);
    MBMOD1.WriteIconsFirst(curINDX++, writer);
    MBMOD2.WriteIconsFirst(curINDX++, writer);
    MBMOD3.WriteIconsFirst(curINDX, writer);

    WRITEEMPTY(FNAM);
    curINDX = 0;
    FBMOD0.WriteIconsFirst(curINDX++, writer);
    FBMOD1.WriteIconsFirst(curINDX++, writer);
    FBMOD2.WriteIconsFirst(curINDX++, writer);
    FBMOD3.WriteIconsFirst(curINDX, writer);

    if(HNAM.value.size())
        WRITE(HNAM);
    else
        WRITEEMPTY(HNAM);

    if(ENAM.value.size())
        WRITE(ENAM);
    else
        WRITEEMPTY(ENAM);

    WRITEEMPTY(MNAM);
    WRITEAS(MaleFGGS,FGGS);
    WRITEAS(MaleFGGA,FGGA);
    WRITEAS(MaleFGTS,FGTS);
    WRITEAS(MaleSNAM,SNAM);

    WRITEEMPTY(FNAM);
    WRITEAS(FemaleFGGS,FGGS);
    WRITEAS(FemaleFGGA,FGGA);
    WRITEAS(FemaleFGTS,FGTS);
    WRITEAS(FemaleSNAM,SNAM);
    return -1;
    }

bool RACERecord::operator ==(const RACERecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            DESC.equals(other.DESC) &&
            DATA == other.DATA &&
            VTCK == other.VTCK &&
            DNAM == other.DNAM &&
            CNAM == other.CNAM &&
            ONAM == other.ONAM &&
            YNAM == other.YNAM &&
            PNAM == other.PNAM &&
            UNAM == other.UNAM &&
            ATTR == other.ATTR &&
            MHMOD0 == other.MHMOD0 &&
            MHMOD1 == other.MHMOD1 &&
            MHMOD2 == other.MHMOD2 &&
            MHMOD3 == other.MHMOD3 &&
            MHMOD4 == other.MHMOD4 &&
            MHMOD5 == other.MHMOD5 &&
            MHMOD6 == other.MHMOD6 &&
            MHMOD7 == other.MHMOD7 &&
            FHMOD0 == other.FHMOD0 &&
            FHMOD1 == other.FHMOD1 &&
            FHMOD2 == other.FHMOD2 &&
            FHMOD3 == other.FHMOD3 &&
            FHMOD4 == other.FHMOD4 &&
            FHMOD5 == other.FHMOD5 &&
            FHMOD6 == other.FHMOD6 &&
            FHMOD7 == other.FHMOD7 &&
            MBMOD0 == other.MBMOD0 &&
            MBMOD1 == other.MBMOD1 &&
            MBMOD2 == other.MBMOD2 &&
            MBMOD3 == other.MBMOD3 &&
            FBMOD0 == other.FBMOD0 &&
            FBMOD1 == other.FBMOD1 &&
            FBMOD2 == other.FBMOD2 &&
            FBMOD3 == other.FBMOD3 &&
            MaleFGGS == other.MaleFGGS &&
            MaleFGGA == other.MaleFGGA &&
            MaleFGTS == other.MaleFGTS &&
            MaleSNAM == other.MaleSNAM &&
            FemaleFGGS == other.FemaleFGGS &&
            FemaleFGGA == other.FemaleFGGA &&
            FemaleFGTS == other.FemaleFGTS &&
            FemaleSNAM == other.FemaleSNAM &&
            XNAM == other.XNAM &&
            HNAM == other.HNAM &&
            ENAM == other.ENAM);
    }

bool RACERecord::operator !=(const RACERecord &other) const
    {
    return !(*this == other);
    }

bool RACERecord::equals(Record *other)
    {
    return *this == *(RACERecord *)other;
    }
}