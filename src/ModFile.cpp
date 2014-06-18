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
// ModFile.cpp
#include "Common.h"
#include "ModFile.h"
#include "GenericRecord.h"

ModFile::ModFile(Collection *_Parent, char * filename, char * modname, const uint32_t _flags):
    Parent(_Parent),
    Flags(_flags),
    TES4(),
    FormIDHandler(TES4.MAST, TES4.HEDR.value.nextObject),
    ModID(0),
    FileName(filename),
    ModName(modname),
    file_map(),
    buffer_position(NULL),
    buffer_start(NULL),
    buffer_end(NULL),
    filter_records(),
    filter_wspaces(),
    filter_inclusive(false)
    {
    TES4.IsLoaded(false);
    TES4.SetParent(this, true);
    ModTime = mtime();
    if(Flags.IsNoLoad || Flags.IsCreateNew || !exists())
        {
        Flags.IsNoLoad = Flags.IsNoLoad || !exists();
        TES4.IsLoaded(true);
        char * const _Name = ModName;
        TES4.IsESM(icmps(".esm",_Name + strlen(_Name) - 4) == 0);
        }
    }

ModFile::~ModFile()
    {
    if(FileName != ModName)
        delete []FileName;
    delete []ModName;
    Close();
    }

bool ModFile::operator <(ModFile &other)
    {
    return ModID < other.ModID;
    }

bool ModFile::operator >(ModFile &other)
    {
    return ModID > other.ModID;
    }

time_t ModFile::mtime()
    {
    struct stat buf;
    stat(FileName, &buf);
    return exists() ? buf.st_mtime : 0;
    }

bool ModFile::exists()
    {
    struct stat statBuffer;
    return (stat(FileName, &statBuffer) >= 0 && statBuffer.st_mode & S_IFREG);
    }

bool ModFile::Open()
    {
    PROFILE_FUNC

    if(Flags.IsCreateNew || Flags.IsNoLoad || file_map.is_open() || !exists())
        {
        if(!Flags.IsCreateNew)
            {
            //if(Flags.IsNoLoad)
            //    printer("ModFile::Open: Error - Unable to open mod \"%s\". Loading is explicitly disabled via flags.\n", ModName);
            if(file_map.is_open())
                printer("ModFile::Open: Error - Unable to open mod \"%s\". It is already open.\n", ModName);
            else if(!exists())
                printer("ModFile::Open: Error - Unable to open mod \"%s\". Unable to locate file.\n", ModName);
            }
        return false;
        }

    if(FileName == NULL || file_map.is_open())
        return false;
    try
        {
        file_map.open(FileName);
        }
    catch(std::ios::failure const &ex)
        {
        printer("ModFile: Error - Unable to open \"%s\" as read only via memory mapping. The file is probably open in another application such as TES4Edit.\n", FileName);
        throw ex;
        }
    catch(std::exception &ex)
        {
        printer("ModFile: Error - Unable to open \"%s\" as read only via memory mapping.\n", FileName);
        throw ex;
        }
    catch(...)
        {
        printer("ModFile: Error - Unable to open \"%s\" as read only via memory mapping. An unhandled exception occurred.\n", FileName);
        throw;
        }
    buffer_position = buffer_start = (unsigned char *)file_map.data();
    buffer_end = buffer_start + file_map.size();

    FormIDHandler.FileStart = buffer_start;
    FormIDHandler.FileEnd = buffer_end;
    return true;
    }

bool ModFile::Close()
    {
    PROFILE_FUNC

    if(!file_map.is_open())
        return false;

    file_map.close();
    return true;
    }

FormIDMasterUpdater::FormIDMasterUpdater(FormIDHandlerClass &_FormIDHandler):
    FormIDOp(),
    FormIDHandler(_FormIDHandler),
    ExpandedIndex(_FormIDHandler.ExpandedIndex),
    CollapsedIndex(_FormIDHandler.CollapsedIndex),
    ExpandTable(_FormIDHandler.ExpandTable),
    CollapseTable(_FormIDHandler.CollapseTable)
    {
    //
    }

FormIDMasterUpdater::FormIDMasterUpdater(ModFile *ModID):
    FormIDOp(),
    FormIDHandler(ModID->FormIDHandler),
    ExpandedIndex(ModID->FormIDHandler.ExpandedIndex),
    CollapsedIndex(ModID->FormIDHandler.CollapsedIndex),
    ExpandTable(ModID->FormIDHandler.ExpandTable),
    CollapseTable(ModID->FormIDHandler.CollapseTable)
    {
    //
    }

FormIDMasterUpdater::FormIDMasterUpdater(Record *RecordID):
    FormIDOp(),
    FormIDHandler(RecordID->GetParentMod()->FormIDHandler),
    ExpandedIndex(RecordID->GetParentMod()->FormIDHandler.ExpandedIndex),
    CollapsedIndex(RecordID->GetParentMod()->FormIDHandler.CollapsedIndex),
    ExpandTable(RecordID->GetParentMod()->FormIDHandler.ExpandTable),
    CollapseTable(RecordID->GetParentMod()->FormIDHandler.CollapseTable)
    {
    //
    }

FormIDMasterUpdater::~FormIDMasterUpdater()
    {
    //
    }

bool FormIDMasterUpdater::Accept(uint32_t &curFormID)
    {
    //If formID is not set, or the formID belongs to the engine, do nothing
    //Any formID whose objectID is less than END_HARDCODED_IDS is given the 00 modIndex by the engine regardless of what it actually is
    //I.e. the CS will complain of duplicate formIDs if a mod has both 0x00000042 and 0x01000042
    //In short, formIDs with an objectID < END_HARDCODED_IDS all collide. They don't use the modIndex.
    if((curFormID & 0x00FFFFFF) < END_HARDCODED_IDS)
        {
        curFormID &= 0x00FFFFFF;
        return stop;
        }

    uint32_t modIndex = curFormID >> 24;
    //result = result || modIndex == 0xFF;
    //printer("Checking %08X against %02X, %02X, %02X\n", curFormID, ExpandedIndex, CollapseTable[modIndex], CollapsedIndex);
    //If the formID belongs to the mod, or if the master is already present, do nothing
    if((modIndex == ExpandedIndex) || (CollapseTable[modIndex] != CollapsedIndex))
        return stop;
    //If the modIndex doesn't match to a loaded mod, it gets assigned to the mod that it is in.
    if(modIndex >= FormIDHandler.LoadOrder255.size())
        {
        curFormID = (ExpandTable[CollapseTable[modIndex]] << 24) | (curFormID & 0x00FFFFFF);
        return stop;
        }
    FormIDHandler.AddMaster(FormIDHandler.LoadOrder255[modIndex]);
    ++count;
    return stop;
    }

bool FormIDMasterUpdater::AcceptMGEF(uint32_t &curMgefCode)
    {
    //If MgefCode is not set, do nothing
    if(curMgefCode == 0)
        return stop;

    uint32_t modIndex = curMgefCode & 0x000000FF;
    //result = result || modIndex == 0xFF;
    //If the MgefCode belongs to the mod, or if the master is already present, do nothing
    if((modIndex == ExpandedIndex) || (CollapseTable[modIndex] != CollapsedIndex))
        return stop;

    //If the modIndex doesn't match to a loaded mod, it gets assigned to the mod that it is in.
    if(modIndex >= FormIDHandler.LoadOrder255.size())
        {
        curMgefCode = (ExpandTable[CollapseTable[modIndex]]) | (curMgefCode & 0xFFFFFF00);
        return stop;
        }

    FormIDHandler.AddMaster(FormIDHandler.LoadOrder255[modIndex]);
    ++count;
    return stop;
    }