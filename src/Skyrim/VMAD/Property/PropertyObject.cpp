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
// PropertyObject.cpp

#include "PropertyObject.h"

UINT32 PropertyObject::GetSize() const
{
    // common + formId + aliasId + 2 NULL bytes
    return Property::GetSize() + sizeof(formId) + sizeof(aliasId) + sizeof(UINT16);
}

void PropertyObject::Read(unsigned char *&buffer, const SINT16 &version, const SINT16 &objFormat, const bool &CompressedOnDisk)
{
    Property::Read(buffer, version, objFormat, CompressedOnDisk);
    if (objFormat == 1)
    {
        formId = *(UINT32 *)buffer;
        buffer += 4;
        aliasId = *(UINT16 *)buffer;
        buffer += 4;
    }
    else
    {
        buffer += 2;
        aliasId = *(UINT16 *)buffer;
        buffer += 2;
        formId = *(UINT32 *)buffer;
        buffer += 4;
    }
}

void PropertyObject::Write(FileWriter &writer)
{
    // Always in format 2
    UINT16 null = 0;
    Property::Write(writer);
    writer.record_write(&null, sizeof(null));
    writer.record_write(&aliasId, sizeof(aliasId));
    writer.record_write(&formId, sizeof(formId));
    // format 1:
    // writer.record_write(&formId, sizeof(formId));
    // writer.record_write(&aliasId, sizeof(aliasId));
    // writer.record_write(&null, sizeof(null));
}

bool PropertyObject::equals(const Property *other) const
{
    try
    {
        const PropertyObject *o = reinterpret_cast<const PropertyObject *>(other);
        return (formId == o->formId &&
                aliasId == o->aliasId
                );
    }
    catch (...)
    {
        return false;
    }
}

Property * PropertyObject::Copy() const
{
    PropertyObject *p = new PropertyObject;
    *p = *this;
    return (Property *)p;
}

PropertyObject & PropertyObject::operator = (const PropertyObject &other)
{
    name = other.name;
    // type - same already
    status = other.status;
    formId = other.formId;
    aliasId = other.aliasId;
    return *this;
}

UINT32 PropertyObjectArray::GetSize() const
{
    // common + itemCount + itemCount * (formId + aliasId + null)
    return Property::GetSize() + sizeof(UINT32)+(size() * 8);
}

void PropertyObjectArray::Read(unsigned char *&buffer, const SINT16 &version, const SINT16 &objFormat, const bool &CompressedOnDisk)
{
    UINT32 count = *(UINT32 *)buffer;
    buffer += 4;

    resize(count);
    if (objFormat == 1)
    {
        for (UINT32 i = 0; i < count; ++i)
        {
            (*this)[i].formId = *(UINT32 *)buffer;
            buffer += 4;
            (*this)[i].aliasId = *(UINT16 *)buffer;
            buffer += 4;
        }
    }
    else
    {
        for (UINT32 i = 0; i < count; ++i)
        {
            buffer += 2;
            (*this)[i].aliasId = *(UINT16 *)buffer;
            buffer += 2;
            (*this)[i].formId = *(UINT32 *)buffer;
            buffer += 4;
        }
    }
}

void PropertyObjectArray::Write(FileWriter &writer)
{
    Property::Write(writer);
    UINT32 count = size();
    UINT16 null = 0;
    writer.record_write(&count, sizeof(count));
    for (UINT32 i = 0; i < count; ++i)
    {
        // always write format 2
        writer.record_write(&null, sizeof(null));
        writer.record_write(&((*this)[i].aliasId), sizeof(UINT16));
        writer.record_write(&((*this)[i].formId), sizeof(UINT32));
        // format 1:
        // writer.record_write(&((*this)[i].formId), sizeof(UINT32));
        // writer.record_write(&((*this)[i].aliasId), sizeof(UINT16));
        // writer.record_write(&null, sizeof(null));
    }
}

bool PropertyObjectArray::equals(const Property *other) const
{
    try
    {
        const PropertyObjectArray *o = reinterpret_cast<const PropertyObjectArray *>(other);
        if (size() != o->size())
            return false;
        for (UINT32 i = 0; i < size(); ++i)
        {
            if ((*this)[i].formId != (*o)[i].formId ||
                (*this)[i].aliasId != (*o)[i].aliasId)
                return false;
        }
        return true;
    }
    catch (...)
    {
        return false;
    }
}

Property * PropertyObjectArray::Copy() const
{
    PropertyObjectArray *p = new PropertyObjectArray;
    *p = *this;
    return (Property *)p;
}

PropertyObjectArray & PropertyObjectArray::operator = (const PropertyObjectArray &other)
{
    name = other.name;
    status = other.status;
    assign(other.begin(), other.end());
    return *this;
}
