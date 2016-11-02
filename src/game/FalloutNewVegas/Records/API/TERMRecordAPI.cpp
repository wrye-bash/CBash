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
#include "common/Common.h"
#include "..\TERMRecord.h"

namespace FNV
{
uint32_t TERMRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
    {
    switch(FieldID)
        {
        case 0: //recType
            return GetType();
        case 1: //flags1
            return CB_UINT32_FLAG_FIELD;
        case 2: //fid
            return CB_FORMID_FIELD;
        case 3: //versionControl1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 4: //eid
            return CB_ISTRING_FIELD;
        case 5: //formVersion
            return CB_UINT16_FIELD;
        case 6: //versionControl2
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 7: //boundX1
            return CB_SINT16_FIELD;
        case 8: //boundY1
            return CB_SINT16_FIELD;
        case 9: //boundZ1
            return CB_SINT16_FIELD;
        case 10: //boundX2
            return CB_SINT16_FIELD;
        case 11: //boundY2
            return CB_SINT16_FIELD;
        case 12: //boundZ2
            return CB_SINT16_FIELD;
        case 13: //full
            return CB_STRING_FIELD;
        case 14: //modPath
            return CB_ISTRING_FIELD;
        case 15: //modb
            return CB_FLOAT32_FIELD;
        case 16: //modt_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MODL.IsLoaded() ? MODL->MODT.GetSize() : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 17: //altTextures
            if(!MODL.IsLoaded())
                return CB_UNKNOWN_FIELD;

            if(ListFieldID == 0) //altTextures
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)MODL->Textures.MODS.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= MODL->Textures.MODS.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //name
                    return CB_STRING_FIELD;
                case 2: //texture
                    return CB_FORMID_FIELD;
                case 3: //index
                    return CB_SINT32_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 18: //modelFlags
            return CB_UINT8_FLAG_FIELD;
        case 19: //script
            return CB_FORMID_FIELD;
        case 20: //destructableHealth
            return CB_SINT32_FIELD;
        case 21: //destructableCount
            return CB_UINT8_FIELD;
        case 22: //destructableFlags
            return CB_UINT8_FLAG_FIELD;
        case 23: //destructableUnused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return Destructable.IsLoaded() ? 2 : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 24: //destructableStages
            if(!Destructable.IsLoaded())
                return CB_UNKNOWN_FIELD;

            if(ListFieldID == 0) //destructableStages
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)Destructable->Stages.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= Destructable->Stages.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //health
                    return CB_UINT8_FIELD;
                case 2: //index
                    return CB_UINT8_FIELD;
                case 3: //stage
                    return CB_UINT8_FIELD;
                case 4: //flags
                    return CB_UINT8_FLAG_FIELD;
                case 5: //dps
                    return CB_SINT32_FIELD;
                case 6: //explosion
                    return CB_FORMID_FIELD;
                case 7: //debris
                    return CB_FORMID_FIELD;
                case 8: //debrisCount
                    return CB_SINT32_FIELD;
                case 9: //modPath
                    return CB_ISTRING_FIELD;
                case 10: //modt_p
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return CB_UINT8_ARRAY_FIELD;
                        case 1: //fieldSize
                            return Destructable->Stages.value[ListIndex]->DMDT.GetSize();
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 25: //description
            return CB_STRING_FIELD;
        case 26: //loopSound
            return CB_FORMID_FIELD;
        case 27: //passNote
            return CB_FORMID_FIELD;
        case 28: //difficultyType
            return CB_UINT8_TYPE_FIELD;
        case 29: //flags
            return CB_UINT8_FLAG_FIELD;
        case 30: //serverType
            return CB_UINT8_TYPE_FIELD;
        case 31: //unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 32: //menus
            if(ListFieldID == 0) //menus
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)Menus.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= Menus.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //text
                    return CB_STRING_FIELD;
                case 2: //resultText
                    return CB_STRING_FIELD;
                case 3: //flags
                    return CB_UINT8_FLAG_FIELD;
                case 4: //displayNote
                    return CB_FORMID_FIELD;
                case 5: //subMenu
                    return CB_FORMID_FIELD;
                case 6: //unused1
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return CB_UINT8_ARRAY_FIELD;
                        case 1: //fieldSize
                            return 4;
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                case 7: //numRefs
                    return CB_UINT32_FIELD;
                case 8: //compiledSize
                    return CB_UINT32_FIELD;
                case 9: //lastIndex
                    return CB_UINT32_FIELD;
                case 10: //scriptType
                    return CB_UINT16_TYPE_FIELD;
                case 11: //scriptFlags
                    return CB_UINT16_FLAG_FIELD;
                case 12: //compiled_p
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return CB_UINT8_ARRAY_FIELD;
                        case 1: //fieldSize
                            return Menus.value[ListIndex]->SCDA.GetSize();
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                case 13: //scriptText
                    return CB_ISTRING_FIELD;
                case 14: //vars
                    if(ListX2FieldID == 0) //vars
                        {
                        switch(WhichAttribute)
                            {
                            case 0: //fieldType
                                return CB_LIST_FIELD;
                            case 1: //fieldSize
                                return (uint32_t)Menus.value[ListIndex]->VARS.value.size();
                            default:
                                return CB_UNKNOWN_FIELD;
                            }
                        }

                    if(ListX2Index >= Menus.value[ListIndex]->VARS.value.size())
                        return CB_UNKNOWN_FIELD;

                    switch(ListFieldID)
                        {
                        case 1: //index
                            return CB_UINT32_FIELD;
                        case 2: //unused1
                            switch(WhichAttribute)
                                {
                                case 0: //fieldType
                                    return CB_UINT8_ARRAY_FIELD;
                                case 1: //fieldSize
                                    return 12;
                                default:
                                    return CB_UNKNOWN_FIELD;
                                }
                            return CB_UNKNOWN_FIELD;
                        case 3: //flags
                            return CB_UINT8_FLAG_FIELD;
                        case 4: //unused2
                            switch(WhichAttribute)
                                {
                                case 0: //fieldType
                                    return CB_UINT8_ARRAY_FIELD;
                                case 1: //fieldSize
                                    return 7;
                                default:
                                    return CB_UNKNOWN_FIELD;
                                }
                            return CB_UNKNOWN_FIELD;
                        case 5: //name
                            return CB_ISTRING_FIELD;
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                    return CB_UNKNOWN_FIELD;
                case 15: //references
                    if(ListX2FieldID == 0) //references
                        {
                        switch(WhichAttribute)
                            {
                            case 0: //fieldType
                                return CB_FORMID_OR_UINT32_ARRAY_FIELD;
                            case 1: //fieldSize
                                return (uint32_t)Menus.value[ListIndex]->SCR_.value.size();
                            default:
                                return CB_UNKNOWN_FIELD;
                            }
                        return CB_UNKNOWN_FIELD;
                        }

                    if(ListX2Index >= Menus.value[ListIndex]->SCR_.value.size())
                        return CB_UNKNOWN_FIELD;

                    switch(ListX2FieldID)
                        {
                        case 1: //reference
                            switch(WhichAttribute)
                                {
                                case 0: //fieldType
                                    return CB_FORMID_OR_UINT32_FIELD;
                                case 2: //WhichType
                                    return (Menus.value[ListIndex]->SCR_.value[ListX2Index]->isSCRO ? CB_FORMID_FIELD : CB_UINT32_FIELD);
                                default:
                                    return CB_UNKNOWN_FIELD;
                                }
                            return CB_UNKNOWN_FIELD;
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                    return CB_UNKNOWN_FIELD;
                case 16: //conditions
                    if(ListX2FieldID == 0) //conditions
                        {
                        switch(WhichAttribute)
                            {
                            case 0: //fieldType
                                return CB_LIST_FIELD;
                            case 1: //fieldSize
                                return (uint32_t)Menus.value[ListIndex]->CTDA.value.size();
                            default:
                                return CB_UNKNOWN_FIELD;
                            }
                        }

                    if(ListX2Index >= Menus.value[ListIndex]->CTDA.value.size())
                        return CB_UNKNOWN_FIELD;

                    switch(ListX2FieldID)
                        {
                        case 1: //operType
                            return CB_UINT8_FLAG_TYPE_FIELD;
                        case 2: //unused1
                            switch(WhichAttribute)
                                {
                                case 0: //fieldType
                                    return CB_UINT8_ARRAY_FIELD;
                                case 1: //fieldSize
                                    return 3;
                                default:
                                    return CB_UNKNOWN_FIELD;
                                }
                        case 3: //compValue
                            switch(WhichAttribute)
                                {
                                case 0: //fieldType
                                    return CB_FORMID_OR_FLOAT32_FIELD;
                                case 2: //WhichType
                                    return Menus.value[ListIndex]->CTDA.value[ListX2Index]->IsUseGlobal() ? CB_FORMID_FIELD :  CB_FLOAT32_FIELD;
                                default:
                                    return CB_UNKNOWN_FIELD;
                                }
                        case 4: //ifunc
                            return CB_UINT32_TYPE_FIELD;
                        case 5: //param1
                            switch(WhichAttribute)
                                {
                                case 0: //fieldType
                                    return CB_UNKNOWN_OR_FORMID_OR_UINT32_FIELD;
                                case 2: //WhichType
                                    {
                                    Function_Arguments_Iterator curCTDAFunction = FNVFunction_Arguments.find(Menus.value[ListIndex]->CTDA.value[ListX2Index]->ifunc);
                                    if(curCTDAFunction != FNVFunction_Arguments.end())
                                        {
                                        const FunctionArguments &CTDAFunction = curCTDAFunction->second;
                                        switch(CTDAFunction.first)
                                            {
                                            case eFORMID:
                                                return CB_FORMID_FIELD;
                                            case eUINT32:
                                                return CB_UINT32_FIELD;
                                            default:
                                                return CB_UNKNOWN_FIELD;
                                            }
                                        }
                                    }
                                    return CB_UNKNOWN_FIELD;
                                default:
                                    return CB_UNKNOWN_FIELD;
                                }
                        case 6: //param2
                            switch(WhichAttribute)
                                {
                                case 0: //fieldType
                                    return CB_UNKNOWN_OR_FORMID_OR_UINT32_FIELD;
                                case 2: //WhichType
                                    {
                                    Function_Arguments_Iterator curCTDAFunction = FNVFunction_Arguments.find(Menus.value[ListIndex]->CTDA.value[ListX2Index]->ifunc);
                                    if(curCTDAFunction != FNVFunction_Arguments.end())
                                        {
                                        const FunctionArguments &CTDAFunction = curCTDAFunction->second;
                                        switch(CTDAFunction.second)
                                            {
                                            case eFORMID:
                                                return CB_FORMID_FIELD;
                                            case eUINT32:
                                                return CB_UINT32_FIELD;
                                            case eVATSPARAM:
                                                if(Menus.value[ListIndex]->CTDA.value[ListX2Index]->param1 < VATSFUNCTIONSIZE)
                                                    {
                                                    switch(VATSFunction_Argument[Menus.value[ListIndex]->CTDA.value[ListX2Index]->param1])
                                                        {
                                                        case eFORMID:
                                                            return CB_FORMID_FIELD;
                                                        case eUINT32:
                                                            return CB_UINT32_FIELD;
                                                        default:
                                                            return CB_UNKNOWN_FIELD;
                                                        }
                                                    }
                                            default:
                                                return CB_UNKNOWN_FIELD;
                                            }
                                        }
                                    }
                                    return CB_UNKNOWN_FIELD;
                                default:
                                    return CB_UNKNOWN_FIELD;
                                }
                        case 7: //runOnType
                            return CB_UINT32_TYPE_FIELD;
                        case 8: //reference
                            switch(WhichAttribute)
                                {
                                case 0: //fieldType
                                    return CB_UNKNOWN_OR_FORMID_OR_UINT32_FIELD;
                                case 2: //WhichType
                                    return Menus.value[ListIndex]->CTDA.value[ListX2Index]->IsResultOnReference() ? CB_FORMID_FIELD : CB_UINT32_FIELD;
                                default:
                                    return CB_UNKNOWN_FIELD;
                                }
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                default:
                    return CB_UNKNOWN_FIELD;
                }
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * TERMRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
    {
    switch(FieldID)
        {
        case 1: //flags1
            return &flags;
        case 2: //fid
            return &formID;
        case 3: //versionControl1
            *FieldValues = &flagsUnk;
            return NULL;
        case 4: //eid
            return EDID.value;
        case 5: //formVersion
            return &formVersion;
        case 6: //versionControl2
            *FieldValues = &versionControl2[0];
            return NULL;
        case 7: //boundX1
            return &OBND.value.x1;
        case 8: //boundY1
            return &OBND.value.y1;
        case 9: //boundZ1
            return &OBND.value.z1;
        case 10: //boundX2
            return &OBND.value.x2;
        case 11: //boundY2
            return &OBND.value.y2;
        case 12: //boundZ2
            return &OBND.value.z2;
        case 13: //full
            return FULL.value;
        case 14: //modPath
            return MODL.IsLoaded() ? MODL->MODL.value : NULL;
        case 15: //modb
            return MODL.IsLoaded() ? &MODL->MODB.value : NULL;
        case 16: //modt_p
            *FieldValues = MODL.IsLoaded() ? MODL->MODT.value : NULL;
            return NULL;
        case 17: //altTextures
            if(!MODL.IsLoaded())
                return NULL;

            if(ListIndex >= MODL->Textures.MODS.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //name
                    return MODL->Textures.MODS[ListIndex]->name;
                case 2: //texture
                    return &MODL->Textures.MODS[ListIndex]->texture;
                case 3: //index
                    return &MODL->Textures.MODS[ListIndex]->index;
                default:
                    return NULL;
                }
            return NULL;
        case 18: //modelFlags
            return MODL.IsLoaded() ? &MODL->MODD.value : NULL;
        case 19: //script
            return SCRI.IsLoaded() ? &SCRI.value : NULL;
        case 20: //destructableHealth
            return Destructable.IsLoaded() ? &Destructable->DEST.value.health : NULL;
        case 21: //destructableCount
            return Destructable.IsLoaded() ? &Destructable->DEST.value.count : NULL;
        case 22: //destructableFlags
            return Destructable.IsLoaded() ? &Destructable->DEST.value.flags : NULL;
        case 23: //destructableUnused1
            *FieldValues = Destructable.IsLoaded() ? &Destructable->DEST.value.unused1[0] : NULL;
            return NULL;
        case 24: //destructableStages
            if(!Destructable.IsLoaded())
                return NULL;

            if(ListIndex >= Destructable->Stages.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //health
                    return &Destructable->Stages.value[ListIndex]->DSTD.value.health;
                case 2: //index
                    return &Destructable->Stages.value[ListIndex]->DSTD.value.index;
                case 3: //stage
                    return &Destructable->Stages.value[ListIndex]->DSTD.value.stage;
                case 4: //flags
                    return &Destructable->Stages.value[ListIndex]->DSTD.value.flags;
                case 5: //dps
                    return &Destructable->Stages.value[ListIndex]->DSTD.value.dps;
                case 6: //explosion
                    return &Destructable->Stages.value[ListIndex]->DSTD.value.explosion;
                case 7: //debris
                    return &Destructable->Stages.value[ListIndex]->DSTD.value.debris;
                case 8: //debrisCount
                    return &Destructable->Stages.value[ListIndex]->DSTD.value.debrisCount;
                case 9: //modPath
                    return Destructable->Stages.value[ListIndex]->DMDL.value;
                case 10: //modt_p
                    *FieldValues = Destructable->Stages.value[ListIndex]->DMDT.value;
                    return NULL;
                default:
                    return NULL;
                }
            return NULL;
        case 25: //description
            return DESC.value;
        case 26: //loopSound
            return SNAM.IsLoaded() ? &SNAM.value : NULL;
        case 27: //passNote
            return PNAM.IsLoaded() ? &PNAM.value : NULL;
        case 28: //difficultyType
            return &DNAM.value.difficultyType;
        case 29: //flags
            return &DNAM.value.flags;
        case 30: //serverType
            return &DNAM.value.serverType;
        case 31: //unused1
            *FieldValues = &DNAM.value.unused1;
            return NULL;
        case 32: //menus
            if(ListIndex >= Menus.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //text
                    return Menus.value[ListIndex]->ITXT.value;
                case 2: //resultText
                    return Menus.value[ListIndex]->RNAM.value;
                case 3: //flags
                    return &Menus.value[ListIndex]->ANAM.value;
                case 4: //displayNote
                    return Menus.value[ListIndex]->INAM.IsLoaded() ? &Menus.value[ListIndex]->INAM.value : NULL;
                case 5: //subMenu
                    return Menus.value[ListIndex]->INAM.IsLoaded() ? &Menus.value[ListIndex]->TNAM.value : NULL;
                case 6: //unused1
                    *FieldValues = &Menus.value[ListIndex]->SCHR.value.unused1[0];
                    return NULL;
                case 7: //numRefs
                    return &Menus.value[ListIndex]->SCHR.value.numRefs;
                case 8: //compiledSize
                    return &Menus.value[ListIndex]->SCHR.value.compiledSize;
                case 9: //lastIndex
                    return &Menus.value[ListIndex]->SCHR.value.lastIndex;
                case 10: //scriptType
                    return &Menus.value[ListIndex]->SCHR.value.scriptType;
                case 11: //scriptFlags
                    return &Menus.value[ListIndex]->SCHR.value.flags;
                case 12: //compiled_p
                    *FieldValues = Menus.value[ListIndex]->SCDA.value;
                    return NULL;
                case 13: //scriptText
                    return Menus.value[ListIndex]->SCTX.value;
                case 14: //vars
                    if(ListX2Index >= Menus.value[ListIndex]->VARS.value.size())
                        return NULL;

                    switch(ListX2FieldID)
                        {
                        case 1: //index
                            return &Menus.value[ListIndex]->VARS.value[ListX2Index]->SLSD.value.index;
                        case 2: //unused1
                            *FieldValues = &Menus.value[ListIndex]->VARS.value[ListX2Index]->SLSD.value.unused1[0];
                            return NULL;
                        case 3: //flags
                            return &Menus.value[ListIndex]->VARS.value[ListX2Index]->SLSD.value.flags;
                        case 4: //unused2
                            *FieldValues = &Menus.value[ListIndex]->VARS.value[ListX2Index]->SLSD.value.unused2[0];
                            return NULL;
                        case 5: //name
                            return Menus.value[ListIndex]->VARS.value[ListX2Index]->SCVR.value;
                        default:
                            return NULL;
                        }
                    return NULL;
                case 15: //references
                    for(uint32_t x = 0; x < Menus.value[ListIndex]->SCR_.value.size(); ++x)
                        ((FORMIDARRAY)FieldValues)[x] = Menus.value[ListIndex]->SCR_.value[x]->reference;
                    return NULL;
                case 16: //conditions
                    if(ListX2Index >= Menus.value[ListIndex]->CTDA.value.size())
                        return NULL;

                    switch(ListX2FieldID)
                        {
                        case 1: //operType
                            return &Menus.value[ListIndex]->CTDA.value[ListX2Index]->operType;
                        case 2: //unused1
                            *FieldValues = &Menus.value[ListIndex]->CTDA.value[ListX2Index]->unused1[0];
                            return NULL;
                        case 3: //compValue
                            return &Menus.value[ListIndex]->CTDA.value[ListX2Index]->compValue;
                        case 4: //ifunc
                            return &Menus.value[ListIndex]->CTDA.value[ListX2Index]->ifunc;
                        case 5: //param1
                            return &Menus.value[ListIndex]->CTDA.value[ListX2Index]->param1;
                        case 6: //param2
                            return &Menus.value[ListIndex]->CTDA.value[ListX2Index]->param2;
                        case 7: //runOnType
                            return &Menus.value[ListIndex]->CTDA.value[ListX2Index]->runOnType;
                        case 8: //reference
                            return &Menus.value[ListIndex]->CTDA.value[ListX2Index]->reference;
                        default:
                            return NULL;
                        }
                    return NULL;
                default:
                    return NULL;
                }
            return NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool TERMRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
    {
    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(*(uint32_t *)FieldValue);
            break;
        case 3: //versionControl1
            if(ArraySize != 4)
                break;
            ((UINT8ARRAY)&flagsUnk)[0] = ((UINT8ARRAY)FieldValue)[0];
            ((UINT8ARRAY)&flagsUnk)[1] = ((UINT8ARRAY)FieldValue)[1];
            ((UINT8ARRAY)&flagsUnk)[2] = ((UINT8ARRAY)FieldValue)[2];
            ((UINT8ARRAY)&flagsUnk)[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 4: //eid
            EDID.Copy((char *)FieldValue);
            break;
        case 5: //formVersion
            formVersion = *(uint16_t *)FieldValue;
            break;
        case 6: //versionControl2
            if(ArraySize != 2)
                break;
            versionControl2[0] = ((UINT8ARRAY)FieldValue)[0];
            versionControl2[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 7: //boundX1
            OBND.value.x1 = *(int16_t *)FieldValue;
            break;
        case 8: //boundY1
            OBND.value.y1 = *(int16_t *)FieldValue;
            break;
        case 9: //boundZ1
            OBND.value.z1 = *(int16_t *)FieldValue;
            break;
        case 10: //boundX2
            OBND.value.x2 = *(int16_t *)FieldValue;
            break;
        case 11: //boundY2
            OBND.value.y2 = *(int16_t *)FieldValue;
            break;
        case 12: //boundZ2
            OBND.value.z2 = *(int16_t *)FieldValue;
            break;
        case 13: //full
            FULL.Copy((char *)FieldValue);
            break;
        case 14: //modPath
            MODL.Load();
            MODL->MODL.Copy((char *)FieldValue);
            break;
        case 15: //modb
            MODL.Load();
            MODL->MODB.value = *(float *)FieldValue;
            break;
        case 16: //modt_p
            MODL.Load();
            MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 17: //altTextures
            MODL.Load();
            if(ListFieldID == 0) //altTexturesSize
                {
                MODL->Textures.resize(ArraySize);
                return false;
                }

            if(ListIndex >= MODL->Textures.MODS.size())
                break;

            switch(ListFieldID)
                {
                case 1: //name
                    delete []MODL->Textures.MODS[ListIndex]->name;
                    MODL->Textures.MODS[ListIndex]->name = NULL;
                    if(FieldValue != NULL)
                        {
                        ArraySize = (uint32_t)strlen((char *)FieldValue) + 1;
                        MODL->Textures.MODS[ListIndex]->name = new char[ArraySize];
                        strcpy_s(MODL->Textures.MODS[ListIndex]->name, ArraySize, (char *)FieldValue);
                        }
                    break;
                case 2: //texture
                    MODL->Textures.MODS[ListIndex]->texture = *(FORMID *)FieldValue;
                    return true;
                case 3: //index
                    MODL->Textures.MODS[ListIndex]->index = *(int32_t *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 18: //modelFlags
            MODL.Load();
            MODL->SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 19: //script
            SCRI.value = *(FORMID *)FieldValue;
            return true;
        case 20: //destructableHealth
            Destructable.Load();
            Destructable->DEST.value.health = *(int32_t *)FieldValue;
            break;
        case 21: //destructableCount
            Destructable.Load();
            Destructable->DEST.value.count = *(uint8_t *)FieldValue;
            break;
        case 22: //destructableFlags
            Destructable.Load();
            Destructable->SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 23: //destructableUnused1
            if(ArraySize != 2)
                break;
            Destructable.Load();
            Destructable->DEST.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            Destructable->DEST.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 24: //destructableStages
            Destructable.Load();
            if(ListFieldID == 0) //destructableStagesSize
                {
                Destructable->Stages.resize(ArraySize);
                return false;
                }

            if(ListIndex >= Destructable->Stages.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //health
                    Destructable->Stages.value[ListIndex]->DSTD.value.health = *(uint8_t *)FieldValue;
                    break;
                case 2: //index
                    Destructable->Stages.value[ListIndex]->DSTD.value.index = *(uint8_t *)FieldValue;
                    break;
                case 3: //stage
                    Destructable->Stages.value[ListIndex]->DSTD.value.stage = *(uint8_t *)FieldValue;
                    break;
                case 4: //flags
                    Destructable->Stages.value[ListIndex]->SetFlagMask(*(uint8_t *)FieldValue);
                    break;
                case 5: //dps
                    Destructable->Stages.value[ListIndex]->DSTD.value.dps = *(int32_t *)FieldValue;
                    break;
                case 6: //explosion
                    Destructable->Stages.value[ListIndex]->DSTD.value.explosion = *(FORMID *)FieldValue;
                    return true;
                case 7: //debris
                    Destructable->Stages.value[ListIndex]->DSTD.value.debris = *(FORMID *)FieldValue;
                    return true;
                case 8: //debrisCount
                    Destructable->Stages.value[ListIndex]->DSTD.value.debrisCount = *(int32_t *)FieldValue;
                    break;
                case 9: //modPath
                    Destructable->Stages.value[ListIndex]->DMDL.Copy((char *)FieldValue);
                    break;
                case 10: //modt_p
                    Destructable->Stages.value[ListIndex]->DMDT.Copy((UINT8ARRAY)FieldValue, ArraySize);
                    break;
                default:
                    break;
                }
            break;
        case 25: //description
            DESC.Copy((char *)FieldValue);
            break;
        case 26: //loopSound
            SNAM.value = *(FORMID *)FieldValue;
            return true;
        case 27: //passNote
            PNAM.value = *(FORMID *)FieldValue;
            return true;
        case 28: //difficultyType
            DNAM.value.difficultyType = *(uint8_t *)FieldValue;
            break;
        case 29: //flags
            SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 30: //serverType
            SetServerType(*(uint8_t *)FieldValue);
            break;
        case 31: //unused1
            if(ArraySize != 1)
                break;
            DNAM.value.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 32: //menus
            if(ListFieldID == 0) //menus
                {
                Menus.resize(ArraySize);
                return false;
                }

            if(ListIndex >= Menus.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //text
                    Menus.value[ListIndex]->ITXT.Copy((char *)FieldValue);
                    break;
                case 2: //resultText
                    Menus.value[ListIndex]->RNAM.Copy((char *)FieldValue);
                    break;
                case 3: //flags
                    Menus.value[ListIndex]->SetFlagMask(*(uint8_t *)FieldValue);
                    break;
                case 4: //displayNote
                    Menus.value[ListIndex]->INAM.value = *(FORMID *)FieldValue;
                    return true;
                case 5: //subMenu
                    Menus.value[ListIndex]->TNAM.value = *(FORMID *)FieldValue;
                    return true;
                case 6: //unused1
                    if(ArraySize != 4)
                        break;
                    Menus.value[ListIndex]->SCHR.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
                    Menus.value[ListIndex]->SCHR.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
                    Menus.value[ListIndex]->SCHR.value.unused1[2] = ((UINT8ARRAY)FieldValue)[2];
                    Menus.value[ListIndex]->SCHR.value.unused1[3] = ((UINT8ARRAY)FieldValue)[3];
                    break;
                case 7: //numRefs
                    Menus.value[ListIndex]->SCHR.value.numRefs = *(uint32_t *)FieldValue;
                    break;
                case 8: //compiledSize
                    Menus.value[ListIndex]->SCHR.value.compiledSize = *(uint32_t *)FieldValue;
                    break;
                case 9: //lastIndex
                    Menus.value[ListIndex]->SCHR.value.lastIndex = *(uint32_t *)FieldValue;
                    break;
                case 10: //scriptType
                    Menus.value[ListIndex]->SetType(*(uint16_t *)FieldValue);
                    break;
                case 11: //scriptFlags
                    Menus.value[ListIndex]->SetScriptFlagMask(*(uint16_t *)FieldValue);
                    break;
                case 12: //compiled_p
                    Menus.value[ListIndex]->SCDA.Copy((UINT8ARRAY)FieldValue, ArraySize);
                    Menus.value[ListIndex]->SCHR.value.compiledSize = ArraySize;
                    break;
                case 13: //scriptText
                    Menus.value[ListIndex]->SCTX.Copy((char *)FieldValue);
                    break;
                case 14: //vars
                    if(ListX2FieldID == 0) //varsSize
                        {
                        Menus.value[ListIndex]->VARS.resize(ArraySize);
                        return false;
                        }

                    if(ListX2Index >= Menus.value[ListIndex]->VARS.value.size())
                        break;

                    switch(ListX2FieldID)
                        {
                        case 1: //index
                            Menus.value[ListIndex]->VARS.value[ListX2Index]->SLSD.value.index = *(uint32_t *)FieldValue;
                            break;
                        case 2: //unused1
                            if(ArraySize != 12)
                                break;
                            Menus.value[ListIndex]->VARS.value[ListX2Index]->SLSD.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
                            Menus.value[ListIndex]->VARS.value[ListX2Index]->SLSD.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
                            Menus.value[ListIndex]->VARS.value[ListX2Index]->SLSD.value.unused1[2] = ((UINT8ARRAY)FieldValue)[2];
                            Menus.value[ListIndex]->VARS.value[ListX2Index]->SLSD.value.unused1[3] = ((UINT8ARRAY)FieldValue)[3];
                            Menus.value[ListIndex]->VARS.value[ListX2Index]->SLSD.value.unused1[4] = ((UINT8ARRAY)FieldValue)[4];
                            Menus.value[ListIndex]->VARS.value[ListX2Index]->SLSD.value.unused1[5] = ((UINT8ARRAY)FieldValue)[5];
                            Menus.value[ListIndex]->VARS.value[ListX2Index]->SLSD.value.unused1[6] = ((UINT8ARRAY)FieldValue)[6];
                            Menus.value[ListIndex]->VARS.value[ListX2Index]->SLSD.value.unused1[7] = ((UINT8ARRAY)FieldValue)[7];
                            Menus.value[ListIndex]->VARS.value[ListX2Index]->SLSD.value.unused1[8] = ((UINT8ARRAY)FieldValue)[8];
                            Menus.value[ListIndex]->VARS.value[ListX2Index]->SLSD.value.unused1[9] = ((UINT8ARRAY)FieldValue)[9];
                            Menus.value[ListIndex]->VARS.value[ListX2Index]->SLSD.value.unused1[10] = ((UINT8ARRAY)FieldValue)[10];
                            Menus.value[ListIndex]->VARS.value[ListX2Index]->SLSD.value.unused1[11] = ((UINT8ARRAY)FieldValue)[11];
                            break;
                        case 3: //flags
                            Menus.value[ListIndex]->VARS.value[ListX2Index]->SetFlagMask(*(uint8_t *)FieldValue);
                            break;
                        case 4: //unused2
                            if(ArraySize != 7)
                                break;
                            Menus.value[ListIndex]->VARS.value[ListX2Index]->SLSD.value.unused2[0] = ((UINT8ARRAY)FieldValue)[0];
                            Menus.value[ListIndex]->VARS.value[ListX2Index]->SLSD.value.unused2[1] = ((UINT8ARRAY)FieldValue)[1];
                            Menus.value[ListIndex]->VARS.value[ListX2Index]->SLSD.value.unused2[2] = ((UINT8ARRAY)FieldValue)[2];
                            Menus.value[ListIndex]->VARS.value[ListX2Index]->SLSD.value.unused2[3] = ((UINT8ARRAY)FieldValue)[3];
                            Menus.value[ListIndex]->VARS.value[ListX2Index]->SLSD.value.unused2[4] = ((UINT8ARRAY)FieldValue)[4];
                            Menus.value[ListIndex]->VARS.value[ListX2Index]->SLSD.value.unused2[5] = ((UINT8ARRAY)FieldValue)[5];
                            Menus.value[ListIndex]->VARS.value[ListX2Index]->SLSD.value.unused2[6] = ((UINT8ARRAY)FieldValue)[6];
                            break;
                        case 5: //name
                            Menus.value[ListIndex]->VARS.value[ListX2Index]->SCVR.Copy((char *)FieldValue);
                            break;
                        default:
                            break;
                        }
                    break;
                case 15: //references
                    if(ListX2FieldID == 0) //referencesSize
                        {
                        Menus.value[ListIndex]->SCR_.resize(ArraySize);
                        return false;
                        }

                    if(ListX2Index >= Menus.value[ListIndex]->SCR_.value.size())
                        break;

                    switch(ListX2FieldID)
                        {
                        case 1: //reference
                            //Borrowing ArraySize to flag if the new value is a formID
                            Menus.value[ListIndex]->SCR_.value[ListX2Index]->reference = *(uint32_t *)FieldValue;
                            Menus.value[ListIndex]->SCR_.value[ListX2Index]->isSCRO = ArraySize ? true : false;
                            return ArraySize != 0;
                        default:
                            break;
                        }
                    break;
                case 16: //conditions
                    if(ListX2FieldID == 0) //conditionsSize
                        {
                        Menus.value[ListIndex]->CTDA.resize(ArraySize);
                        return false;
                        }

                    if(ListX2Index >= Menus.value[ListIndex]->CTDA.value.size())
                        break;

                    switch(ListX2FieldID)
                        {
                        case 1: //operType
                            Menus.value[ListIndex]->CTDA.value[ListX2Index]->operType = *(uint8_t *)FieldValue;
                            break;
                        case 2: //unused1
                            if(ArraySize != 3)
                                break;
                            Menus.value[ListIndex]->CTDA.value[ListX2Index]->unused1[0] = ((UINT8ARRAY)FieldValue)[0];
                            Menus.value[ListIndex]->CTDA.value[ListX2Index]->unused1[1] = ((UINT8ARRAY)FieldValue)[1];
                            Menus.value[ListIndex]->CTDA.value[ListX2Index]->unused1[2] = ((UINT8ARRAY)FieldValue)[2];
                            break;
                        case 3: //compValue
                            Menus.value[ListIndex]->CTDA.value[ListX2Index]->compValue = *(FORMID_OR_FLOAT32 *)FieldValue;
                            return true;
                        case 4: //ifunc
                            Menus.value[ListIndex]->CTDA.value[ListX2Index]->ifunc = *(uint32_t *)FieldValue;
                            return true;
                        case 5: //param1
                            Menus.value[ListIndex]->CTDA.value[ListX2Index]->param1 = *(FORMID_OR_UINT32 *)FieldValue;
                            return true;
                        case 6: //param2
                            Menus.value[ListIndex]->CTDA.value[ListX2Index]->param2 = *(FORMID_OR_UINT32 *)FieldValue;
                            return true;
                        case 7: //runOnType
                            Menus.value[ListIndex]->CTDA.value[ListX2Index]->runOnType = *(uint32_t *)FieldValue;
                            return true;
                        case 8: //reference
                            Menus.value[ListIndex]->CTDA.value[ListX2Index]->reference = *(FORMID_OR_UINT32 *)FieldValue;
                            return true;
                        default:
                            break;
                        }
                    break;
                default:
                    break;
                }
            break;
        default:
            break;
        }
    return false;
    }

void TERMRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    GENOBND defaultOBND;
    FNVMODS defaultMODS;
    GENDEST defaultDEST;
    DESTDSTD defaultDSTD;
    TERMDNAM defaultDNAM;

    FNVSCHR defaultSCHR;
    GENVARS defaultVARS;
    GENSCR_ defaultSCR_;
    FNVCTDA defaultCTDA;
    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(0);
            return;
        case 3: //versionControl1
            flagsUnk = 0;
            return;
        case 4: //eid
            EDID.Unload();
            return;
        case 5: //formVersion
            formVersion = 0;
            return;
        case 6: //versionControl2
            versionControl2[0] = 0;
            versionControl2[1] = 0;
            return;
        case 7: //boundX1
            OBND.value.x1 = defaultOBND.x1;
            return;
        case 8: //boundY1
            OBND.value.y1 = defaultOBND.y1;
            return;
        case 9: //boundZ1
            OBND.value.z1 = defaultOBND.z1;
            return;
        case 10: //boundX2
            OBND.value.x2 = defaultOBND.x2;
            return;
        case 11: //boundY2
            OBND.value.y2 = defaultOBND.y2;
            return;
        case 12: //boundZ2
            OBND.value.z2 = defaultOBND.z2;
            return;
        case 13: //full
            FULL.Unload();
            return;
        case 14: //modPath
            if(MODL.IsLoaded())
                MODL->MODL.Unload();
            return;
        case 15: //modb
            if(MODL.IsLoaded())
                MODL->MODB.Unload();
            return;
        case 16: //modt_p
            if(MODL.IsLoaded())
                MODL->MODT.Unload();
            return;
        case 17: //altTextures
            if(MODL.IsLoaded())
                {
                if(ListFieldID == 0) //altTextures
                    {
                    MODL->Textures.Unload();
                    return;
                    }

                if(ListIndex >= MODL->Textures.MODS.size())
                    return;

                switch(ListFieldID)
                    {
                    case 1: //name
                        delete []MODL->Textures.MODS[ListIndex]->name;
                        MODL->Textures.MODS[ListIndex]->name = NULL;
                        return;
                    case 2: //texture
                        MODL->Textures.MODS[ListIndex]->texture = defaultMODS.texture;
                        return;
                    case 3: //index
                        MODL->Textures.MODS[ListIndex]->index = defaultMODS.index;
                        return;
                    default:
                        return;
                    }
                }
            return;
        case 18: //modelFlags
            if(MODL.IsLoaded())
                MODL->MODD.Unload();
            return;
        case 19: //script
            SCRI.Unload();
            return;
        case 20: //destructableHealth
            if(Destructable.IsLoaded())
                Destructable->DEST.value.health = defaultDEST.health;
            return;
        case 21: //destructableCount
            if(Destructable.IsLoaded())
                Destructable->DEST.value.count = defaultDEST.count;
            return;
        case 22: //destructableFlags
            if(Destructable.IsLoaded())
                Destructable->SetFlagMask(defaultDEST.flags);
            return;
        case 23: //destructableUnused1
            if(Destructable.IsLoaded())
                {
                Destructable->DEST.value.unused1[0] = defaultDSTD.health;
                }
            return;
        case 24: //destructableStages
            if(Destructable.IsLoaded())
                {
                if(ListFieldID == 0) //destructableStages
                    {
                    Destructable->Stages.Unload();
                    return;
                    }

                if(ListIndex >= Destructable->Stages.value.size())
                    return;

                switch(ListFieldID)
                    {
                    case 1: //health
                        Destructable->Stages.value[ListIndex]->DSTD.value.health = defaultDSTD.health;
                        return;
                    case 2: //index
                        Destructable->Stages.value[ListIndex]->DSTD.value.index = defaultDSTD.index;
                        return;
                    case 3: //stage
                        Destructable->Stages.value[ListIndex]->DSTD.value.stage = defaultDSTD.stage;
                        return;
                    case 4: //flags
                        Destructable->Stages.value[ListIndex]->SetFlagMask(defaultDSTD.flags);
                        return;
                    case 5: //dps
                        Destructable->Stages.value[ListIndex]->DSTD.value.dps = defaultDSTD.dps;
                        return;
                    case 6: //explosion
                        Destructable->Stages.value[ListIndex]->DSTD.value.explosion = defaultDSTD.explosion;
                        return;
                    case 7: //debris
                        Destructable->Stages.value[ListIndex]->DSTD.value.debris = defaultDSTD.debris;
                        return;
                    case 8: //debrisCount
                        Destructable->Stages.value[ListIndex]->DSTD.value.debrisCount = defaultDSTD.debrisCount;
                        return;
                    case 9: //modPath
                        Destructable->Stages.value[ListIndex]->DMDL.Unload();
                        return;
                    case 10: //modt_p
                        Destructable->Stages.value[ListIndex]->DMDT.Unload();
                        return;
                    default:
                        return;
                    }
                }
            return;
        case 25: //description
            DESC.Unload();
            return;
        case 26: //loopSound
            SNAM.Unload();
            return;
        case 27: //passNote
            PNAM.Unload();
            return;
        case 28: //difficultyType
            DNAM.value.difficultyType = defaultDNAM.difficultyType;
            return;
        case 29: //flags
            DNAM.value.flags = defaultDNAM.flags;
            return;
        case 30: //serverType
            DNAM.value.serverType = defaultDNAM.serverType;
            return;
        case 31: //unused1
            DNAM.value.unused1 = defaultDNAM.unused1;
            return;
        case 32: //menus
            if(ListFieldID == 0) //menus
                {
                Menus.Unload();
                return;
                }

            if(ListIndex >= Menus.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //text
                    Menus.value[ListIndex]->ITXT.Unload();
                    return;
                case 2: //resultText
                    Menus.value[ListIndex]->RNAM.Unload();
                    return;
                case 3: //flags
                    Menus.value[ListIndex]->ANAM.Unload();
                    return;
                case 4: //displayNote
                    Menus.value[ListIndex]->INAM.Unload();
                    return;
                case 5: //subMenu
                    Menus.value[ListIndex]->TNAM.Unload();
                    return;
                case 6: //unused1
                    Menus.value[ListIndex]->SCHR.value.unused1[0] = defaultSCHR.unused1[0];
                    Menus.value[ListIndex]->SCHR.value.unused1[1] = defaultSCHR.unused1[1];
                    Menus.value[ListIndex]->SCHR.value.unused1[2] = defaultSCHR.unused1[2];
                    Menus.value[ListIndex]->SCHR.value.unused1[3] = defaultSCHR.unused1[3];
                    return;
                case 7: //numRefs
                    Menus.value[ListIndex]->SCHR.value.numRefs = defaultSCHR.numRefs;
                    return;
                case 8: //compiledSize
                    Menus.value[ListIndex]->SCHR.value.compiledSize = defaultSCHR.compiledSize;
                    return;
                case 9: //lastIndex
                    Menus.value[ListIndex]->SCHR.value.lastIndex = defaultSCHR.lastIndex;
                    return;
                case 10: //scriptType
                    Menus.value[ListIndex]->SetType(defaultSCHR.scriptType);
                    return;
                case 11: //scriptFlags
                    Menus.value[ListIndex]->SetScriptFlagMask(defaultSCHR.flags);
                    return;
                case 12: //compiled_p
                    Menus.value[ListIndex]->SCDA.Unload();
                    return;
                case 13: //scriptText
                    Menus.value[ListIndex]->SCTX.Unload();
                    return;
                case 14: //vars
                    if(ListX2FieldID == 0) //vars
                        {
                        Menus.value[ListIndex]->VARS.Unload();
                        return;
                        }

                    if(ListX2Index >= Menus.value[ListIndex]->VARS.value.size())
                        return;

                    switch(ListX2FieldID)
                        {
                        case 1: //index
                            Menus.value[ListIndex]->VARS.value[ListX2Index]->SLSD.value.index = defaultVARS.SLSD.value.index;
                            return;
                        case 2: //unused1
                            Menus.value[ListIndex]->VARS.value[ListX2Index]->SLSD.value.unused1[0] = defaultVARS.SLSD.value.unused1[0];
                            Menus.value[ListIndex]->VARS.value[ListX2Index]->SLSD.value.unused1[1] = defaultVARS.SLSD.value.unused1[1];
                            Menus.value[ListIndex]->VARS.value[ListX2Index]->SLSD.value.unused1[2] = defaultVARS.SLSD.value.unused1[2];
                            Menus.value[ListIndex]->VARS.value[ListX2Index]->SLSD.value.unused1[3] = defaultVARS.SLSD.value.unused1[3];
                            Menus.value[ListIndex]->VARS.value[ListX2Index]->SLSD.value.unused1[4] = defaultVARS.SLSD.value.unused1[4];
                            Menus.value[ListIndex]->VARS.value[ListX2Index]->SLSD.value.unused1[5] = defaultVARS.SLSD.value.unused1[5];
                            Menus.value[ListIndex]->VARS.value[ListX2Index]->SLSD.value.unused1[6] = defaultVARS.SLSD.value.unused1[6];
                            Menus.value[ListIndex]->VARS.value[ListX2Index]->SLSD.value.unused1[7] = defaultVARS.SLSD.value.unused1[7];
                            Menus.value[ListIndex]->VARS.value[ListX2Index]->SLSD.value.unused1[8] = defaultVARS.SLSD.value.unused1[8];
                            Menus.value[ListIndex]->VARS.value[ListX2Index]->SLSD.value.unused1[9] = defaultVARS.SLSD.value.unused1[9];
                            Menus.value[ListIndex]->VARS.value[ListX2Index]->SLSD.value.unused1[10] = defaultVARS.SLSD.value.unused1[10];
                            Menus.value[ListIndex]->VARS.value[ListX2Index]->SLSD.value.unused1[11] = defaultVARS.SLSD.value.unused1[11];
                            return;
                        case 3: //flags
                            Menus.value[ListIndex]->VARS.value[ListX2Index]->SLSD.value.flags = defaultVARS.SLSD.value.flags;
                            return;
                        case 4: //unused2
                            Menus.value[ListIndex]->VARS.value[ListX2Index]->SLSD.value.unused2[0] = defaultVARS.SLSD.value.unused2[0];
                            Menus.value[ListIndex]->VARS.value[ListX2Index]->SLSD.value.unused2[1] = defaultVARS.SLSD.value.unused2[1];
                            Menus.value[ListIndex]->VARS.value[ListX2Index]->SLSD.value.unused2[2] = defaultVARS.SLSD.value.unused2[2];
                            Menus.value[ListIndex]->VARS.value[ListX2Index]->SLSD.value.unused2[3] = defaultVARS.SLSD.value.unused2[3];
                            Menus.value[ListIndex]->VARS.value[ListX2Index]->SLSD.value.unused2[4] = defaultVARS.SLSD.value.unused2[4];
                            Menus.value[ListIndex]->VARS.value[ListX2Index]->SLSD.value.unused2[5] = defaultVARS.SLSD.value.unused2[5];
                            Menus.value[ListIndex]->VARS.value[ListX2Index]->SLSD.value.unused2[6] = defaultVARS.SLSD.value.unused2[6];
                            return;
                        case 5: //name
                            Menus.value[ListIndex]->VARS.value[ListX2Index]->SCVR.Unload();
                            return;
                        default:
                            return;
                        }
                    return;
                case 15: //references
                    if(ListX2FieldID == 0) //references
                        {
                        Menus.value[ListIndex]->SCR_.Unload();
                        return;
                        }

                    if(ListX2Index >= Menus.value[ListIndex]->SCR_.value.size())
                        return;

                    switch(ListX2FieldID)
                        {
                        case 1: //reference
                            Menus.value[ListIndex]->SCR_.value[ListX2Index]->reference = defaultSCR_.reference;
                            Menus.value[ListIndex]->SCR_.value[ListX2Index]->isSCRO = defaultSCR_.isSCRO;
                            return;
                        default:
                            return;
                        }
                    return;
                case 16: //conditions
                    if(ListX2FieldID == 0) //conditionsSize
                        {
                        Menus.value[ListIndex]->CTDA.Unload();
                        return;
                        }

                    if(ListX2Index >= Menus.value[ListIndex]->CTDA.value.size())
                        return;

                    switch(ListX2FieldID)
                        {
                        case 1: //operType
                            Menus.value[ListIndex]->CTDA.value[ListX2Index]->operType = defaultCTDA.operType;
                            return;
                        case 2: //unused1
                            Menus.value[ListIndex]->CTDA.value[ListX2Index]->unused1[0] = defaultCTDA.unused1[0];
                            Menus.value[ListIndex]->CTDA.value[ListX2Index]->unused1[1] = defaultCTDA.unused1[1];
                            Menus.value[ListIndex]->CTDA.value[ListX2Index]->unused1[2] = defaultCTDA.unused1[2];
                            return;
                        case 3: //compValue
                            Menus.value[ListIndex]->CTDA.value[ListX2Index]->compValue = defaultCTDA.compValue;
                            return;
                        case 4: //ifunc
                            Menus.value[ListIndex]->CTDA.value[ListX2Index]->ifunc = defaultCTDA.ifunc;
                            return;
                        case 5: //param1
                            Menus.value[ListIndex]->CTDA.value[ListX2Index]->param1 = defaultCTDA.param1;
                            return;
                        case 6: //param2
                            Menus.value[ListIndex]->CTDA.value[ListX2Index]->param2 = defaultCTDA.param2;
                            return;
                        case 7: //runOnType
                            Menus.value[ListIndex]->CTDA.value[ListX2Index]->runOnType = defaultCTDA.runOnType;
                            return;
                        case 8: //reference
                            Menus.value[ListIndex]->CTDA.value[ListX2Index]->reference = defaultCTDA.reference;
                            return;
                        default:
                            return;
                        }
                    return;
                default:
                    return;
                }
            return;
        default:
            return;
        }
    }
}