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

#ifndef __CBASH_TES5_RECORD__
#define __CBASH_TES5_RECORD__

#pragma once

#include "common/GenericRecord.h"
#include "TES5ModFile.h"

class TES5Record : public Record
    {
    protected:
        enum TES5HeaderFlags
            {
            fIsESM = 0x00000001,
            fUnknown01 = 0x00000002,
            fUnknown02 = 0x00000004,
            fUnknown03 = 0x00000008,
            fUnknown04 = 0x00000010,
            fUnknown05 = 0x00000020,
            fUnknown06 = 0x00000040,
            fUnknown07 = 0x00000080,
            fUnknown08 = 0x00000100,
            fUnknown09 = 0x00000200,
            fUnknown10 = 0x00000400,
            fUnknown11 = 0x00000800,
            fUnknown12 = 0x00001000,
            fUnknown13 = 0x00002000,
            fUnknown14 = 0x00004000,
            fUnknown15 = 0x00008000,
            fUnknown16 = 0x00010000,
            fUnknown17 = 0x00020000,
            fUnknown18 = 0x00040000,
            fUnknown19 = 0x00080000,
            fUnknown20 = 0x00100000,
            fUnknown21 = 0x00200000,
            fUnknown22 = 0x00400000,
            fUnknown23 = 0x00800000,
            fUnknown24 = 0x01000000,
            fUnknown25 = 0x02000000,
            fUnknown26 = 0x04000000,
            fUnknown27 = 0x08000000,
            fUnknown28 = 0x10000000,
            fUnknown29 = 0x20000000,
            fUnknown30 = 0x40000000,
            fUnknown31 = 0x80000000
            };

    public:
        uint16_t formVersion; //TES5
        uint8_t  versionControl2[2]; //TES5

        TES5Record(unsigned char *_recData = NULL);
        TES5Record(TES5Record *srcRecord);
        virtual ~TES5Record();

        TES5ModFile * GetParentMod() const;

        bool Read();
        uint32_t Write(FileWriter &writer, const bool &bMastersChanged, FormIDResolver &expander, FormIDResolver &collapser, std::vector<FormIDResolver *> &Expanders);
    };
 
#endif