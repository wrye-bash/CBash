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
// PropertyBool.cpp

#include "PropertyBool.h"

UINT32 PropertyBool::GetSize() const
{
    // common + value
    return Property::GetSize() + sizeof(UINT8);
}

void PropertyBool::Read(unsigned char *&buffer, const SINT16 &version, const SINT16 &objFormat, const bool &CompressedOnDisk)
{
    Property::Read(buffer, version, objFormat, CompressedOnDisk);
    value = *(UINT8 *)buffer ? true : false;
    buffer += 1;
}

void PropertyBool::Write(FileWriter &writer)
{
    Property::Write(writer);
    UINT8 b = value ? 1 : 0;
    writer.record_write(&b, sizeof(b));
}

bool PropertyBool::equals(const Property *other) const
{
    try
    {
        const PropertyBool *o = reinterpret_cast<const PropertyBool *>(other);
        return value == o->value;
    }
    catch (...)
    {
        return false;
    }
}

Property * PropertyBool::Copy() const
{
    PropertyBool *p = new PropertyBool;
    *p = *this;
    return (Property *)p;
}

PropertyBool & PropertyBool::operator = (const PropertyBool &other)
{
    name = other.name;
    // type is the same already
    status = other.status;
    value = other.value;

    return *this;
}

UINT32 PropertyBoolArray::GetSize() const
{
    // common + itemCount + items
    return Property::GetSize() + sizeof(UINT32) + (size() * sizeof(UINT8));
}

void PropertyBoolArray::Read(unsigned char *&buffer, const SINT16 &version, const SINT16 &objFormat, const bool &CompressedOnDisk)
{
    UINT32 count = *(UINT32 *)buffer;
    buffer += 4;

    resize(count);
    for (UINT32 i = 0; i < count; ++i)
    {
        (*this)[i] = *(UINT8 *)buffer ? true : false;
        buffer += 1;
    }
}

void PropertyBoolArray::Write(FileWriter &writer)
{
    Property::Write(writer);
    UINT32 count = size();
    writer.record_write(&count, sizeof(count));
    for (UINT32 i = 0; i < count; ++i)
    {
        UINT8 b = (*this)[i] ? 1 : 0;
        writer.record_write(&b, sizeof(b));
    }
}

bool PropertyBoolArray::equals(const Property *other) const
{
    try
    {
        const PropertyBoolArray *o = reinterpret_cast<const PropertyBoolArray *>(other);
        if (size() != o->size())
            return false;
        for (UINT32 i = 0; i < size(); ++i)
            if ((*this)[i] != (*o)[i])
                return false;
        return true;
    }
    catch (...)
    {
        return false;
    }
}

Property * PropertyBoolArray::Copy() const
{
    PropertyBoolArray *p = new PropertyBoolArray;
    *p = *this;
    return (Property *)p;
}

PropertyBoolArray & PropertyBoolArray::operator = (const PropertyBoolArray &other)
{
    name = other.name;
    status = other.status;
    assign(other.begin(), other.end());
    return *this;
}
