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
// Script.cpp

#include "Script.h"
#include "Property/Property.h"
#include "Property/PropertyObject.h"
#include "Property/PropertyString.h"
#include "Property/PropertyInt.h"
#include "Property/PropertyFloat.h"
#include "Property/PropertyBool.h"
#include "../../GenericChunks.h"

Script::Script() :
status(fDefault)
{
    //
}

Script::~Script()
{
    for (uint32_t i = 0; i < properties.size(); ++i)
        delete properties[i];
}

void Script::VisitFormIDs(FormIDOp &op)
{
    for (uint32_t i = 0; i < properties.size(); ++i)
    {
        if (properties[i]->type == Property::eObject)
            op.Accept(((PropertyObject *)properties[i])->formId);
        else if (properties[i]->type == Property::eObjectArray)
        {
            PropertyObjectArray *p = reinterpret_cast<PropertyObjectArray *>(properties[i]);
            for (uint32_t j = 0; j < p->size(); ++j)
                op.Accept((*p)[j].formId);
        }
    }
}

uint32_t Script::GetSize() const
{
    // status + nameSize + propertyCount
    uint32_t total = sizeof(status) + sizeof(uint16_t) + sizeof(uint16_t);
    total += name.GetSize();
    for (uint16_t i = 0; i < properties.size(); ++i)
        total += properties[i]->GetSize();
    return total;
}

void Script::Read(unsigned char *&buffer, const int16_t &version, const int16_t &objFormat, const bool &CompressedOnDisk)
{
    // name
    uint16_t nameSize = *(uint16_t *)buffer;
    buffer += 2;
    name.Read(buffer, nameSize, CompressedOnDisk);
    // status
    status = *(uint8_t *)buffer;
    buffer += 1;
    // propertyCount
    uint16_t count = *(uint16_t *)buffer;
    buffer += 2;
    // properties
    for (uint16_t i = 0; i < count; ++i)
    {
        unsigned char *read_ahead = buffer;
        nameSize = *(uint16_t *)read_ahead;
        read_ahead += 2 + nameSize;
        uint8_t type = *(uint8_t *)read_ahead;
        switch (type)
        {
        case Property::eObject:
            properties.push_back((Property *)(new PropertyObject));
            properties.back()->Read(buffer, version, objFormat, CompressedOnDisk);
            break;
        case Property::eObjectArray:
            properties.push_back((Property *)(new PropertyObjectArray));
            properties.back()->Read(buffer, version, objFormat, CompressedOnDisk);
            break;
        case Property::eString:
            properties.push_back((Property *)(new PropertyString));
            properties.back()->Read(buffer, version, objFormat, CompressedOnDisk);
            break;
        case Property::eStringArray:
            properties.push_back((Property *)(new PropertyStringArray));
            properties.back()->Read(buffer, version, objFormat, CompressedOnDisk);
            break;
        case Property::eInt:
            properties.push_back((Property *)(new PropertyInt));
            properties.back()->Read(buffer, version, objFormat, CompressedOnDisk);
            break;
        case Property::eIntArray:
            properties.push_back((Property *)(new PropertyIntArray));
            properties.back()->Read(buffer, version, objFormat, CompressedOnDisk);
            break;
        case Property::eFloat:
            properties.push_back((Property *)(new PropertyFloat));
            properties.back()->Read(buffer, version, objFormat, CompressedOnDisk);
            break;
        case Property::eFloatArray:
            properties.push_back((Property *)(new PropertyFloatArray));
            properties.back()->Read(buffer, version, objFormat, CompressedOnDisk);
            break;
        case Property::eBool:
            properties.push_back((Property *)(new PropertyBool));
            properties.back()->Read(buffer, version, objFormat, CompressedOnDisk);
            break;
        case Property::eBoolArray:
            properties.push_back((Property *)(new PropertyBoolArray));
            properties.back()->Read(buffer, version, objFormat, CompressedOnDisk);
            break;
        default:
            // raise error
            break;
        };
    }
}

void Script::Write(FileWriter &writer)
{
    name.Write16(writer);
    writer.record_write(&status, sizeof(status));
    uint16_t count = static_cast<uint16_t>(properties.size());
    writer.record_write(&count, sizeof(count));
    for (uint16_t i = 0; i < count; ++i)
        properties[i]->Write(writer);
}

Script & Script::operator = (const Script &other)
{
    name = other.name;
    status = other.status;

    for (uint32_t i = 0; i < properties.size(); ++i)
        delete properties[i];
    properties.clear();

    for (uint32_t i = 0; i < other.properties.size(); ++i)
        properties.push_back(other.properties[i]->Copy());

    return *this;
}

bool Script::operator == (const Script &other) const
{
    if (properties.size() != other.properties.size())
        return false;
    for (uint16_t i = 0; i < properties.size(); ++i)
        if (*(properties[i]) != *(other.properties[i]))
            return false;
    return (status == other.status &&
            name.equals(other.name)
            );
}

bool Script::operator != (const Script &other) const
{
    return !(*this == other);
}
