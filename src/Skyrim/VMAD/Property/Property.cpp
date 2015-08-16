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
// Property.cpp

#include "Property.h"

bool Property::IsObject() const
    {
    return type == eObject;
    }

bool Property::IsString() const
    {
    return type == eString;
    }

bool Property::IsInt() const
    {
    return type == eInt;
    }

bool Property::IsFloat() const
    {
    return type == eFloat;
    }

bool Property::IsBool() const
    {
    return type == eBool;
    }

bool Property::IsObjectArray() const
    {
    return type == eObjectArray;
    }

bool Property::IsStringArray() const
    {
    return type == eStringArray;
    }

bool Property::IsIntArray() const
    {
    return type == eIntArray;
    }

bool Property::IsFloatArray() const
    {
    return type == eFloatArray;
    }

bool Property::IsBoolArray() const
    {
    return type == eBoolArray;
    }

bool Property::IsType(uint8_t Type) const
    {
    return type == Type;
    }

bool Property::IsEdited() const
    {
    return (status & fIsEdited) != 0;
    }

void Property::IsEdited(bool value)
    {
    SETBIT(status, fIsEdited, value);
    }

bool Property::IsRemoved() const
    {
    return (status & fIsRemoved) != 0;
    }

void Property::IsRemoved(bool value)
    {
    SETBIT(status, fIsRemoved, value);
    }

bool Property::IsStatusMask(uint8_t Mask, bool Exact)
    {
    return Exact ? (status & Mask) == Mask : (status & Mask) != 0;
    }

void Property::SetStatusMask(uint8_t Mask)
    {
    status = Mask;
    }

uint32_t Property::GetSize() const
    {
    return (sizeof(type) + sizeof(status) +
            sizeof(uint16_t) + name.GetSize());
    }

void Property::Read(unsigned char *&buffer, const int16_t &version, const int16_t &objFormat, const bool &CompressedOnDisk)
{
    // name
    uint16_t nameSize = *(uint16_t *)buffer;
    buffer += 2;
    name.Read(buffer, nameSize, CompressedOnDisk);
    // type
    type = *(uint8_t *)buffer;
    buffer += 1;
    // status
    if (version >= 4)
    {
        status = *(uint8_t *)buffer;
        buffer += 1;
    }
    else
        status = fIsEdited;
    // Derived classes read in Data
}

void Property::Write(FileWriter &writer)
{
    // name
    name.Write16(writer);
    // type
    writer.record_write(&type, sizeof(type));
    // status
    writer.record_write(&status, sizeof(status));
}

bool Property::operator == (const Property &other) const
    {
    if (type != other.type ||
        status != other.status)
        return false;
    return this->equals(&other);
    }

bool Property::operator != (const Property &other) const
    {
    return !(*this == other);
    }
