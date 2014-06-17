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
// VMAD.cpp
#include "VMAD.h"
#include "Fragment/Fragment.h"
#include "Fragment/FragmentINFO.h"
#include "Fragment/FragmentPACK.h"
#include "Fragment/FragmentPERK.h"
#include "Fragment/FragmentQUST.h"
#include "Fragment/FragmentSCEN.h"
#include "Script.h"
#include "../../GenericChunks.h"


VMADRecord::VMADRecord() :
fragment(NULL)
{
    //
}

VMADRecord::~VMADRecord()
{
    Unload();
}

bool VMADRecord::IsLoaded() const
{
    return (fragment == NULL &&
            scripts.size() == 0);
}

void VMADRecord::Load()
{
    if (!IsLoaded())
        fragment = NULL;
}

void VMADRecord::Unload()
{
    for (UINT16 i = 0; i, scripts.size(); ++i)
        delete scripts[i];
    scripts.clear();
    delete fragment;
    fragment = NULL;
}

void VMADRecord::VisitFormIDs(FormIDOp &op)
{
    for (UINT16 i = 0; i < scripts.size(); ++i)
        scripts[i]->VisitFormIDs(op);
    if (fragment != NULL)
        fragment->VisitFormIDs(op);
}

UINT32 VMADRecord::GetSize() const
{
    // version + objFormat + scriptCount
    UINT32 total = sizeof(SINT16) + sizeof(SINT16) + sizeof(UINT16);
    // scripts
    for (UINT16 i = 0; i < scripts.size(); ++i)
        total += scripts[i]->GetSize();
    // script fragments
    if (fragment != NULL)
        total += fragment->GetSize();
    return total;
}

void VMADRecord::Read(unsigned char *&buffer, const UINT32 &subSize, const UINT32 &recordType, bool CompressedOnDisk)
{
    unsigned char *end_buffer = buffer + subSize;

    // objFormat/version
    SINT16 version = *(SINT16 *)buffer;
    buffer += 2;
    SINT16 objFormat = *(SINT16 *)buffer;
    buffer += 2;

    // Scripts
    UINT16 count = *(UINT16 *)buffer;
    buffer += 2;
    for (UINT16 i = 0; i < count; ++i)
    {
        scripts.push_back(new Script);
        scripts.back()->Read(buffer, version, objFormat, CompressedOnDisk);
    }

    // Check for script fragments
    fragment = NULL;
    if (buffer < end_buffer)
    {
        switch (recordType)
        {
        case REV32(INFO):
            fragment = (Fragments *)new FragmentINFO;
            ((FragmentINFO *)fragment)->Read(buffer, CompressedOnDisk);
            break;
        case REV32(PACK):
            fragment = (Fragments *)new FragmentPACK;
            ((FragmentPACK *)fragment)->Read(buffer, CompressedOnDisk);
            break;
        case REV32(PERK):
            fragment = (Fragments *)new FragmentPERK;
            ((FragmentPERK *)fragment)->Read(buffer, CompressedOnDisk);
            break;
        case REV32(QUST):
            fragment = (Fragments *)new FragmentQUST;
            ((FragmentQUST *)fragment)->Read(buffer, version, objFormat, CompressedOnDisk);
            break;
        case REV32(SCEN):
            fragment = (Fragments *)new FragmentSCEN;
            ((FragmentSCEN *)fragment)->Read(buffer, CompressedOnDisk);
            break;
        default:
            // TODO: error message
            break;
        };
    }
    else if (buffer > end_buffer)
    {
        // TODO: error message
    }
    buffer = end_buffer;
}

void VMADRecord::Write(UINT32 _Type, FileWriter &writer)
{
    if (!IsLoaded())
        return;

    ReqWrite(_Type, writer);
}

void VMADRecord::ReqWrite(UINT32 _Type, FileWriter &writer)
{
    // Subrecord header
    writer.record_write_subheader(_Type, GetSize());

    // version: always write in version 5
    SINT16 version = 5;
    writer.record_write(&version, 2);
    // objFormat: always write in format 2
    SINT16 objFormat = 2;
    writer.record_write(&objFormat, 2);

    // scriptCount
    UINT16 count = scripts.size();
    writer.record_write(&count, 2);

    // scripts
    for (UINT16 i = 0; i < count; ++i)
        scripts[i]->Write(writer);

    // script fragments
    if (fragment)
        fragment->Write(writer);
}

VMADRecord & VMADRecord::operator = (const VMADRecord &other)
{
    Unload();
    // scripts
    for (UINT16 i = 0; i < other.scripts.size(); ++i)
    {
        scripts.push_back(new Script);
        *(scripts.back()) = *(other.scripts[i]);
    }
    // fragments
    if (other.fragment != NULL)
        fragment = other.fragment->Copy();

    return *this;
}

bool VMADRecord::operator == (const VMADRecord &other) const
{
    // Scripts
    if (scripts.size() != other.scripts.size())
        return false;
    for (UINT16 i = 0; i < scripts.size(); ++i)
        if (*(scripts[i]) != *(other.scripts[i]))
            return false;
    // Script fragments
    if (fragment != NULL && other.fragment != NULL)
        if (*fragment != *(other.fragment))
            return false;
    if (fragment != NULL && other.fragment == NULL)
        return false;
    if (fragment == NULL && other.fragment != NULL)
        return false;
    // All check passed
    return true;
}

bool VMADRecord::operator != (const VMADRecord &other) const
{
    return !(*this == other);
}
