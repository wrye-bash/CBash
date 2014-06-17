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
// PropertyInt.cpp

#include "PropertyInt.h"

UINT32 PropertyInt::GetSize() const
{
    // common + value
    return Property::GetSize() + sizeof(SINT32);
}

void PropertyInt::Read(unsigned char *&buffer, const SINT16 &version, const SINT16 &objFormat, const bool &CompressedOnDisk)
{
    Property::Read(buffer, version, objFormat, CompressedOnDisk);
    value = *(SINT32 *)buffer;
    buffer += 4;
}

void PropertyInt::Write(FileWriter &writer)
{
    Property::Write(writer);
    writer.record_write(&value, sizeof(value));
}

bool PropertyInt::equals(const Property *other) const
{
    try
    {
        const PropertyInt *o = reinterpret_cast<const PropertyInt *>(other);
        return value == o->value;
    }
    catch (...)
    {
        return false;
    }
}

Property * PropertyInt::Copy() const
{
    PropertyInt *p = new PropertyInt;
    *p = *this;
    return (Property *)p;
}

PropertyInt & PropertyInt::operator = (const PropertyInt &other)
{
    name = other.name;
    // type - same already
    status = other.status;
    value = other.value;
    return *this;
}

UINT32 PropertyIntArray::GetSize() const
{
    // common + itemCount + items
    return Property::GetSize() + sizeof(UINT32) + (size() * sizeof(SINT32));
}

void PropertyIntArray::Read(unsigned char *&buffer, const SINT16 &version, const SINT16 &objFormat, const bool &CompressedOnDisk)
{
    UINT32 count = *(UINT32 *)buffer;
    buffer += 4;

    resize(count);
    memcpy(&((*this)[0]), buffer, count * sizeof(SINT32));
    buffer += count * sizeof(SINT32);
}

void PropertyIntArray::Write(FileWriter &writer)
{
    Property::Write(writer);
    UINT32 count = size();
    writer.record_write(&count, sizeof(count));
    writer.record_write(&((*this)[0]), count * sizeof(SINT32));
}

bool PropertyIntArray::equals(const Property *other) const
{
    try
    {
        const PropertyIntArray *o = reinterpret_cast<const PropertyIntArray *>(other);
        if (size() != o->size())
            return false;
        return memcmp(&((*this)[0]), &((*o)[0]), size() * sizeof(SINT32)) == 0;
    }
    catch (...)
    {
        return false;
    }
}

Property * PropertyIntArray::Copy() const
{
    PropertyIntArray *p = new PropertyIntArray;
    *p = *this;
    return (Property *)p;
}

PropertyIntArray & PropertyIntArray::operator = (const PropertyIntArray &other)
{
    name = other.name;
    status = other.status;
    assign(other.begin(), other.end());
    return *this;
}
