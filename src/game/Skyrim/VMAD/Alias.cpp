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
// Alias.cpp

#include "Alias.h"
#include "Script.h"
#include "../../GenericChunks.h"

Alias::Alias():
formId(0), aliasId(0)
{
    //
}

Alias::~Alias()
{
    for (uint16_t i = 0; i < scripts.size(); ++i)
        delete scripts[i];
}

void Alias::VisitFormIDs(FormIDOp &op)
{
    op.Accept(formId);
    for (uint16_t i = 0; i < scripts.size(); ++i)
        scripts[i]->VisitFormIDs(op);
}

void Alias::Read(unsigned char *&buffer, const int16_t &version, const int16_t &objFormat, const bool &CompressedOnDisk)
{
    // object
    if (objFormat == 1)
    {
        formId = *(uint32_t *)buffer;
        buffer += 4;
        aliasId = *(uint16_t *)buffer;
        buffer += 4;
    }
    else
    {
        buffer += 2;
        aliasId = *(uint16_t *)buffer;
        buffer += 2;
        formId = *(uint32_t *)buffer;
        buffer += 4;
    }
    // version, objFormat
    buffer += 8;
    // scriptCount
    uint16_t count = *(uint16_t *)buffer;
    buffer += 2;
    // scripts
    for (uint16_t i = 0; i < count; ++i)
    {
        scripts.push_back(new Script);
        scripts.back()->Read(buffer, version, objFormat, CompressedOnDisk);
    }
}

uint32_t Alias::GetSize() const
{
    // object (formid(4) + aliasId(2) + null(2)) + version + objFormat + scriptCount
    uint32_t total = sizeof(uint32_t)+ (5 * sizeof(uint16_t)+sizeof(uint16_t));
    for (uint16_t i = 0; i < scripts.size(); ++i)
        total += scripts[i]->GetSize();
    return total;
}

void Alias::Write(FileWriter &writer)
{
    // always write format 2
    uint16_t null = 0;
    writer.record_write(&null, sizeof(null));
    writer.record_write(&aliasId, sizeof(aliasId));
    writer.record_write(&formId, sizeof(formId));
    int16_t version = 5;
    writer.record_write(&version, sizeof(version));
    int16_t objFormat = 2;
    writer.record_write(&objFormat, sizeof(objFormat));
    uint16_t count = static_cast<uint16_t>(scripts.size());
    writer.record_write(&count, sizeof(count));
    for (uint16_t i = 0; i < count; ++i)
        scripts[i]->Write(writer);
}

Alias & Alias::operator = (const Alias &other)
{
    formId = other.formId;
    aliasId = other.aliasId;

    for (uint16_t i = 0; i < scripts.size(); ++i)
        delete scripts[i];
    scripts.clear();

    for (uint16_t i = 0; i < other.scripts.size(); ++i)
    {
        scripts.push_back(new Script);
        *(scripts.back()) = *(other.scripts[i]);
    }

    return *this;
}

bool Alias::operator == (const Alias &other) const
{
    if (formId != other.formId ||
        aliasId != other.aliasId)
        return false;
    if (scripts.size() != other.scripts.size())
        return false;
    for (uint16_t i = 0; i < scripts.size(); ++i)
        if (*(scripts[i]) != *(other.scripts[i]))
            return false;
    return true;
}

bool Alias::operator != (const Alias &other) const
{
    return !(*this == other);
}
