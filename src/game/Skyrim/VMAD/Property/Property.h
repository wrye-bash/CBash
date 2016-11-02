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
// Property.h

#include "common/Common.h"

class Property
{
public:
    NonNullStringRecord name;
    uint8_t type;
    uint8_t status;

    enum statusFlags
        {
        fIsEdited = 0x01,
        fIsRemoved = 0x03
        };

    enum typeTypes
        {
        eObject = 1,
        eString = 2,
        eInt = 3,
        eFloat = 4,
        eBool = 5,
        eObjectArray = 11,
        eStringArray = 12,
        eIntArray = 13,
        eFloatArray = 14,
        eBoolArray = 15
        };

    bool IsObject() const;
    bool IsString() const;
    bool IsInt() const;
    bool IsFloat() const;
    bool IsBool() const;
    bool IsObjectArray() const;
    bool IsStringArray() const;
    bool IsIntArray() const;
    bool IsFloatArray() const;
    bool IsBoolArray() const;
    bool IsType(uint8_t Type) const;

    bool IsEdited() const;
    void IsEdited(bool value);
    bool IsRemoved() const;
    void IsRemoved(bool value);
    bool IsStatusMask(uint8_t Mask, bool Exact=false);
    void SetStatusMask(uint8_t Mask);

    virtual uint32_t GetSize() const = 0;
    virtual void Read(unsigned char *&buffer, const int16_t &version, const int16_t &objFormat, const bool &CompressedOnDisk) = 0;
    virtual void Write(FileWriter &writer) = 0;
    virtual bool equals(const Property *other) const = 0;
    virtual Property * Copy() const = 0;

    bool operator == (const Property &other) const;
    bool operator != (const Property &other) const;
};
