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

#ifndef __CBASH_FNV_RECORD__
#define __CBASH_FNV_RECORD__

#pragma once

#include "common/GenericRecord.h"

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
        uint16_t formVersion; //FNV
        uint8_t  versionControl2[2]; //FNV

        FNVRecord(unsigned char *_recData=NULL);
        virtual ~FNVRecord();

        bool Read();
        uint32_t Write(FileWriter &writer, const bool &bMastersChanged, FormIDResolver &expander, FormIDResolver &collapser, std::vector<FormIDResolver *> &Expanders);
    };

#endif
