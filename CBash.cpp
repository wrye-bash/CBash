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
// CBash.cpp
//#define CBASH_PYTHON
//#ifdef CBASH_PYTHON
//   #include "Python.h"
//    //#define BOOST_PYTHON_STATIC_LIB
//    //#include <boost/python.hpp>
//#endif
#define COMPILING_CBASH
#include "Version.h"
#include "CBash.h"
#include <vector>
#include <stdarg.h>
#include <new.h>
//#include "mmgr.h"

#ifdef CBASH_STATIC
    #define CPPDLLEXTERN 
#else
    #define CPPDLLEXTERN extern "C" __declspec(dllexport)
#endif

static std::vector<Collection *> Collections;
#ifdef CBASH_CALLTIMING
    extern std::map<char *, double> CallTime;
#endif
#ifdef CBASH_CALLCOUNT
    extern std::map<char *, unsigned long> CallCount;
#endif
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//Internal Functions
inline void ValidatePointer(const void *testPointer)
    {
    if(testPointer == NULL)
        throw Ex_NULL();
    }

ModFile *ValidateLoadOrderIndex(Collection *curCollection, const UINT32 ModIndex)
    {
    //ModFiles will never contain null pointers
    if(ModIndex >= curCollection->LoadOrder255.size())
        throw Ex_INVALIDMODINDEX();
    return curCollection->LoadOrder255[ModIndex];
    }

ModFile *ValidateLoadOrderIndex(Collection *curCollection, STRING const ModName)
    {
    //ValidatePointer(ModName);
    STRING NonGhostName = DeGhostModName(ModName);
    STRING const &CompName = NonGhostName ? NonGhostName : ModName;
    //ModFiles will never contain null pointers
    for(UINT32 x = 0; x < curCollection->LoadOrder255.size();++x)
        if(icmps(CompName, curCollection->LoadOrder255[x]->ModName) == 0)
            {
            delete []NonGhostName;
            return curCollection->LoadOrder255[x];
            }
    delete []NonGhostName;
    throw Ex_INVALIDMODINDEX();
    return NULL;
    }

//Exported Functions
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//Exported Python
//#ifdef CBASH_PYTHON

//PyMODINIT_FUNC
//init_CBashTest(void)

//class CBashUINT32
//    {
//    private:
//        UINT32 _FieldID;
//    public:
//        CBashUINT32(UINT32 FieldID):_FieldID(FieldID) {}
//        UINT32 get()
//            {
//            return 0;
//            }
//        UINT32 set()
//            {
//            return 0;
//            }
//    };

//BOOST_PYTHON_MODULE(CBashTest)
//    {
//    using namespace boost::python;
//
//    class_<CBashUINT32>("CBashUINT32", init<UINT32>())
//        .def("__get__", &CBashUINT32::get)
//        .def("__set__", &CBashUINT32::set);
//    }

//#endif
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//Exported DLL
//Version info functions
CPPDLLEXTERN UINT32 GetVersionMajor()
    {
    return MAJOR_VERSION;
    }

CPPDLLEXTERN UINT32 GetVersionMinor()
    {
    return MINOR_VERSION;
    }

CPPDLLEXTERN UINT32 GetVersionRevision()
    {
    return REVISION_VERSION;
    }
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//Logging action functions
int logback_printer(const char * _Format, ...)
    {
    int nSize = 0;
    char buff[1024];
    va_list args;
    va_start(args, _Format);
    nSize = vsnprintf_s(buff, sizeof(buff), _TRUNCATE, _Format, args);
    va_end(args);
    LoggingCallback(buff);
    return nSize;
    }

CPPDLLEXTERN void RedirectMessages(SINT32 (*_LoggingCallback)(const STRING))
    {
    if(_LoggingCallback)
        {
        LoggingCallback = _LoggingCallback;
        printer = &logback_printer;
        }
    else
        {
        LoggingCallback = NULL;
        printer = &printf;
        }
    }

CPPDLLEXTERN void AllowRaising(void (*_RaiseCallback)(const STRING))
    {
    RaiseCallback = _RaiseCallback;
    }

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//Collection action functions
int handle_program_memory_depletion(size_t size)
    {
    static int retrying = 0;

    if(retrying == 0)
        {
        printer("Warning - Allocation of %u bytes failed. Attempting to free memory and continue.\n", size);
        //try to free up some memory
        if(UnloadAllCollections() == 0)
            {
            //see if enough memory was freed
            //flag the function so that if the new fails, it doesn't infi-loop
            retrying = 1;
            char *test = new char[size];
            //if the code gets this far, there's enough memory
            //so free the test, and retry the initial allocation
            delete []test;
            retrying = 0;
            return 1;
            }
        }

    printer("Error - Unable to allocate %u bytes. CBash will terminate.\n", size);
    DeleteAllCollections();
    throw std::bad_alloc();
    return 0;
    }

CPPDLLEXTERN Collection * CreateCollection(STRING const ModsPath, const UINT32 CollectionType)
    {
    PROFILE_FUNC

    try
        {
        _set_new_handler(handle_program_memory_depletion);
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }

    try
        {
        ValidatePointer(ModsPath);
        for(UINT32 p = 0; p < Collections.size(); ++p)
            {
            if(Collections[p] == NULL)
                {
                Collections[p] = new Collection(ModsPath, CollectionType);
                return Collections[p];
                }
            }
        Collections.push_back(new Collection(ModsPath, CollectionType));
        return Collections.back();
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return NULL;
    }

CPPDLLEXTERN SINT32 DeleteCollection(Collection *CollectionID)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        for(UINT32 ListIndex = 0; ListIndex < Collections.size(); ++ListIndex)
            {
            if(Collections[ListIndex] == CollectionID)
                {
                for(UINT32 ListX2Index = 0; ListX2Index < CollectionID->ModFiles.size(); ++ListX2Index)
                    CollectionID->ModFiles[ListX2Index]->Close();
                for(UINT32 ListX2Index = 0; ListX2Index < CollectionID->closing_ops.size(); ++ListX2Index)
                    {
                    CollectionID->closing_ops[ListX2Index]->perform();
                    delete CollectionID->closing_ops[ListX2Index];
                    }
                delete CollectionID;
                Collections[ListIndex] = NULL;
                }
            }
        for(UINT32 ListIndex = 0; ListIndex < Collections.size(); ++ListIndex)
            {
            if(Collections[ListIndex] != NULL)
                return 0;
            }
        Collections.clear();

        #ifdef CBASH_CALLCOUNT
            cbcounter.end();
            printer("counts = [");
            for(std::map<char *, unsigned long>::iterator it = CallCount.begin(); it != CallCount.end(); ++it)
                printer("(%d, '%s'),", it->second, it->first);
            printer("]\n");
            #ifndef CBASH_CALLTIMING
                CallCount.clear();
            #endif
        #endif
        #ifdef CBASH_CALLTIMING
            cbtimer.end();
            double TotTime = 0.0f;
            printer("times = [");
            for(std::map<char *, double>::iterator it = CallTime.begin(); it != CallTime.end(); ++it)
                {
                TotTime += it->second;
                printer("(%.10f, '%s'),", it->second, it->first);
                }
            printer("]\n\n");
            #ifdef CBASH_CALLCOUNT
                printer("Time in CBash = %.10f\n\n", TotTime);
                printer("Time in CBash = sum(total time)\n");
                printer("Total %% = Time in CBash / total time * 100%%\n");
                printer("avg execution = total time / times called\n\n");
                printer("Total %%,avg execution,total time,function,times called\n");
                std::multimap<double, char *> CBashProfiling;
                for(std::map<char *, double>::iterator it = CallTime.begin(); it != CallTime.end(); ++it)
                    CBashProfiling.insert(std::make_pair((it->second / TotTime) * 100, it->first));
                for(std::multimap<double, char *>::iterator it = CBashProfiling.end(); it != CBashProfiling.begin();)
                    {
                    --it;
                    if(it->first < 10.0)
                        printer("0");
                    printer("%02.2f%%,%.10f,%.10f,%s,%d\n", it->first, CallTime[it->second] / CallCount[it->second], CallTime[it->second], it->second, CallCount[it->second]);
                    }
                printer("\n\n");
                CBashProfiling.clear();
                CallCount.clear();
            #endif
            CallTime.clear();
        #endif
        return 0;
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return -1;
    }

CPPDLLEXTERN SINT32 LoadCollection(Collection *CollectionID, bool (*_ProgressCallback)(const UINT32, const UINT32, const STRING))
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        CollectionID->Load(_ProgressCallback);
        return 0;
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return -1;
    }

CPPDLLEXTERN SINT32 UnloadCollection(Collection *CollectionID)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        CollectionID->Unload();
        return 0;
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return -1;
    }

CPPDLLEXTERN SINT32 GetCollectionType(Collection *CollectionID)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        return CollectionID->CollectionType;
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return -1;
    }

CPPDLLEXTERN SINT32 UnloadAllCollections()
    {
    PROFILE_FUNC

    try
        {
        for(UINT32 p = 0; p < Collections.size(); ++p)
            Collections[p]->Unload();
        return 0;
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return -1;
    }

CPPDLLEXTERN SINT32 DeleteAllCollections()
    {
    PROFILE_FUNC

    try
        {
        for(UINT32 p = 0; p < Collections.size(); ++p)
            delete Collections[p];
        Collections.clear();
        return 0;
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return -1;
    }
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//Mod action functions
CPPDLLEXTERN ModFile * AddMod(Collection *CollectionID, STRING const ModName, const UINT32 ModFlagsField)
    {
    PROFILE_FUNC

    ModFlags flags(ModFlagsField);

    try
        {
        //ValidatePointer(CollectionID);
        ValidatePointer(ModName);
        return CollectionID->AddMod(ModName, flags);
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return NULL;
    }

CPPDLLEXTERN SINT32 LoadMod(ModFile *ModID)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        //ValidatePointer(ModID);
        RecordReader reader(ModID->FormIDHandler, ModID->Parent->Expanders);
        ModID->VisitAllRecords(reader);
        return 0;
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return -1;
    }

CPPDLLEXTERN SINT32 UnloadMod(ModFile *ModID)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(ModID);
        RecordUnloader unloader;
        ModID->VisitAllRecords(unloader);
        return 0;
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return -1;
    }

CPPDLLEXTERN SINT32 CleanModMasters(ModFile *ModID)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        //ValidatePointer(ModID);
        return ModID->Parent->CleanModMasters(ModID);
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return -1;
    }

CPPDLLEXTERN SINT32 SaveMod(ModFile *ModID, const UINT32 SaveFlagsField, STRING const DestinationName)
    {
    SINT32 err = 0;
    SaveFlags flags(SaveFlagsField);
    try
        {
        //Profiling is in try block so that the timer gets destructed before DeleteCollection is called
        PROFILE_FUNC
        //ValidatePointer(CollectionID);
        //ValidatePointer(ModID);
        err = ModID->Parent->SaveMod(ModID, flags, DestinationName);
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }

    if(flags.IsCloseCollection)
        err = DeleteCollection(ModID->Parent) != 0 ? -1 : err;
    if(err == -1)
        {
        printer("\n\n");
        if(RaiseCallback != NULL)
            RaiseCallback(__FUNCTION__);
        }
    return err;
    }
////////////////////////////////////////////////////////////////////////
//Mod info functions
CPPDLLEXTERN SINT32 GetAllNumMods(Collection *CollectionID)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        return (SINT32)CollectionID->ModFiles.size();
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return -1;
    }

CPPDLLEXTERN SINT32 GetAllModIDs(Collection *CollectionID, MODIDARRAY ModIDs)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        UINT32 numMods = (UINT32)CollectionID->ModFiles.size();
        for(UINT32 x = 0; x < numMods; ++x)
            ModIDs[x] = CollectionID->ModFiles[x];
        return 0;
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return -1;
    }

CPPDLLEXTERN SINT32 GetLoadOrderNumMods(Collection *CollectionID)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        return (SINT32)CollectionID->LoadOrder255.size();
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return -1;
    }

CPPDLLEXTERN SINT32 GetLoadOrderModIDs(Collection *CollectionID, MODIDARRAY ModIDs)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        UINT32 numMods = (UINT32)CollectionID->LoadOrder255.size();
        for(UINT32 x = 0; x < numMods; ++x)
            ModIDs[x] = CollectionID->LoadOrder255[x];
        return 0;
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return -1;
    }

CPPDLLEXTERN STRING GetFileNameByID(ModFile *ModID)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(ModID);
        return ModID->FileName;
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return NULL;
    }

CPPDLLEXTERN STRING GetFileNameByLoadOrder(Collection *CollectionID, const UINT32 ModIndex)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        return ValidateLoadOrderIndex(CollectionID, ModIndex)->FileName;
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return NULL;
    }

CPPDLLEXTERN STRING GetModNameByID(ModFile *ModID)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(ModID);
        return ModID->ModName;
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return NULL;
    }

CPPDLLEXTERN STRING GetModNameByLoadOrder(Collection *CollectionID, const UINT32 ModIndex)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        return ValidateLoadOrderIndex(CollectionID, ModIndex)->ModName;
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return NULL;
    }

CPPDLLEXTERN ModFile * GetModIDByName(Collection *CollectionID, STRING const ModName)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        //ValidatePointer(ModName);
        STRING NonGhostName = DeGhostModName(ModName);
        STRING const &CompName = NonGhostName ? NonGhostName : ModName;
        //ModFiles will never contain null pointers
        for(UINT32 x = 0; x < CollectionID->ModFiles.size();++x)
            if(_stricmp(CompName, CollectionID->ModFiles[x]->ModName) == 0)
                {
                delete []NonGhostName;
                return CollectionID->ModFiles[x];
                }
        delete []NonGhostName;
        return NULL;
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return NULL;
    }

CPPDLLEXTERN ModFile * GetModIDByLoadOrder(Collection *CollectionID, const UINT32 ModIndex)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        return ValidateLoadOrderIndex(CollectionID, ModIndex);
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        printer("\n\n");
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return NULL;
    }

CPPDLLEXTERN SINT32 GetModLoadOrderByName(Collection *CollectionID, STRING const ModName)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        return ValidateLoadOrderIndex(CollectionID, ModName)->FormIDHandler.ExpandedIndex;
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return -1;
    }

CPPDLLEXTERN SINT32 GetModLoadOrderByID(ModFile *ModID)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(ModID);
        if(ModID->Flags.IsInLoadOrder)
            return ModID->FormIDHandler.ExpandedIndex;
        //if(RaiseCallback != NULL)
        //    RaiseCallback(__FUNCTION__);
        return -1;
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return -2;
    }

CPPDLLEXTERN ModFile * GetModIDByRecordID(Record *RecordID)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(ModID);
        return RecordID->GetParentMod();
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return NULL;
    }

CPPDLLEXTERN Collection * GetCollectionIDByRecordID(Record *RecordID)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(ModID);
        return RecordID->GetParentMod()->Parent;
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return NULL;
    }

CPPDLLEXTERN Collection * GetCollectionIDByModID(ModFile *ModID)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(ModID);
        return ModID->Parent;
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return NULL;
    }

CPPDLLEXTERN UINT32 IsModEmpty(ModFile *ModID)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(ModID);
        return ModID->FormIDHandler.IsEmpty;
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return 0;
    }

CPPDLLEXTERN SINT32 GetModNumTypes(ModFile *ModID)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(ModID);
        if(!ModID->Flags.IsTrackNewTypes)
            {
            printer("GetModNumTypes: Warning - Unable to report record types for mod \"%s\". Tracking is disabled via flag.\n", ModID->ModName);
            if(RaiseCallback != NULL)
                RaiseCallback(__FUNCTION__);
            return -1;
            }

        return (SINT32)ModID->FormIDHandler.NewTypes.size();
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return -1;
    }

CPPDLLEXTERN SINT32 GetModTypes(ModFile *ModID, UINT32ARRAY RecordTypes)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(ModID);
        if(!ModID->Flags.IsTrackNewTypes)
            {
            printer("GetModTypes: Warning - Unable to report record types for mod \"%s\". Tracking is disabled via flag.\n", ModID->ModName);
            if(RaiseCallback != NULL)
                RaiseCallback(__FUNCTION__);
            return -1;
            }

        UINT32 x = 0;
        for(boost::unordered_set<UINT32>::iterator it = ModID->FormIDHandler.NewTypes.begin(); it != ModID->FormIDHandler.NewTypes.end(); ++it, ++x)
            RecordTypes[x] = *it;
        return 0;
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return -1;
    }

CPPDLLEXTERN SINT32 GetModNumEmptyGRUPs(ModFile *ModID)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(ModID);
        return ModID->FormIDHandler.EmptyGRUPs;
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return -1;
    }

CPPDLLEXTERN SINT32 GetModNumOrphans(ModFile *ModID)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(ModID);
        return ModID->FormIDHandler.OrphanedRecords.size();
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return -1;
    }

CPPDLLEXTERN SINT32 GetModOrphansFormIDs(ModFile *ModID, FORMIDARRAY FormIDs)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(ModID);
        for(UINT32 ListIndex = 0; ListIndex < ModID->FormIDHandler.OrphanedRecords.size(); ++ListIndex)
            FormIDs[ListIndex] = ModID->FormIDHandler.OrphanedRecords[ListIndex];
        return 0;
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return -1;
    }

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//FormID functions
CPPDLLEXTERN STRING GetLongIDName(Record *RecordID, const UINT32 FormID, const bool IsMGEFCode)
    {
    PROFILE_FUNC

    UINT8 ModIndex = IsMGEFCode ? (UINT8)(FormID & 0x000000FF) : (UINT8)(FormID >> 24);
    if(ModIndex == 0xFF)
        return NULL;

    try
        {
        //ValidatePointer(ModID);
        ModFile *ModID = RecordID->GetParentMod();
        UINT8 CollapsedIndex = ModID->FormIDHandler.CollapseTable[ModIndex];
        if(CollapsedIndex >= ModID->TES4.MAST.size())
            return ModID->ModName;
        return ModID->TES4.MAST[CollapsedIndex];
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return NULL;
    }

CPPDLLEXTERN UINT32 MakeShortFormID(ModFile *ModID, const UINT32 ObjectID, const bool IsMGEFCode)
    {
    PROFILE_FUNC

    try
        {
        return IsMGEFCode ? (ModID->FormIDHandler.ExpandedIndex | (ObjectID & 0xFFFFFF00)) : ((ModID->FormIDHandler.ExpandedIndex << 24) | (ObjectID & 0x00FFFFFF));
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return NULL;
    }
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//Record action functions
CPPDLLEXTERN Record * CreateRecord(ModFile *ModID, const UINT32 RecordType, const FORMID RecordFormID, STRING const RecordEditorID, Record *ParentID, const UINT32 CreateFlags)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        //ValidatePointer(ModID);

        return ModID->Parent->CreateRecord(ModID, RecordType, RecordFormID, RecordEditorID, (ParentID != NULL ? ParentID->formID: NULL), CreateFlags);
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return 0;
    }

CPPDLLEXTERN Record * CopyRecord(Record *RecordID, ModFile *DestModID, Record *DestParentID, const FORMID DestRecordFormID, STRING const DestRecordEditorID, const UINT32 CreateFlags)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        //ValidatePointer(ModID);
        //ValidatePointer(RecordID);
        //ValidatePointer(DestModID);
        return RecordID->GetParentMod()->Parent->CopyRecord(RecordID, DestModID, (DestParentID != NULL) ? DestParentID->formID : NULL, DestRecordFormID, DestRecordEditorID, CreateFlags);
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return NULL;
    }

CPPDLLEXTERN SINT32 UnloadRecord(Record *RecordID)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(RecordID);
        return RecordID->IsChanged() ? 0 : RecordID->Unload();
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return 0;
    }

CPPDLLEXTERN SINT32 ResetRecord(Record *RecordID)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        //ValidatePointer(ModID);
        return RecordID->GetParentMod()->file_map.is_open() ? RecordID->Unload() : 0;
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return 0;
    }

CPPDLLEXTERN SINT32 DeleteRecord(Record *RecordID)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        //ValidatePointer(ModID);
        RecordDeindexer deindexer(RecordID);

        if(RecordID->IsWinningDetermined() && (RecordID->IsWinning() || RecordID->IsExtendedWinning()))
            {
            FORMID FormID = RecordID->formID;
            STRING EditorID = RecordID->GetEditorIDKey();
            bool IsKeyedByEditorID = RecordID->IsKeyedByEditorID();
            Collection *CollectionID = RecordID->GetParentMod()->Parent;
            if(RecordID->GetParentMod()->DeleteRecord(RecordID, deindexer))
                {
                //Update the IsWinning flags for all related records
                ModFile *WinningModfile = NULL;
                Record *WinningRecord = NULL;

                if(IsKeyedByEditorID)
                    CollectionID->LookupWinningRecord(EditorID, WinningModfile, WinningRecord, true);
                else
                    CollectionID->LookupWinningRecord(FormID, WinningModfile, WinningRecord, true);
                return 1;
                }
            return 0;
            }

        return RecordID->GetParentMod()->DeleteRecord(RecordID, deindexer);
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return 0;
    }
////////////////////////////////////////////////////////////////////////
//Record info functions
CPPDLLEXTERN Record * GetRecordID(ModFile *ModID, const FORMID RecordFormID, STRING const RecordEditorID)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        //ValidatePointer(ModID);
        Record * curRecord = NULL;
        if(RecordFormID == 0 && RecordEditorID == 0)
            return &ModID->TES4;
        if(RecordFormID != 0)
            ModID->Parent->LookupRecord(ModID, RecordFormID, curRecord);
        if(curRecord != NULL)
            return curRecord;
        if(RecordEditorID != 0)
            ModID->Parent->LookupRecord(ModID, RecordEditorID, curRecord);
        return curRecord;
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return NULL;
    }

CPPDLLEXTERN SINT32 GetNumRecords(ModFile *ModID, const UINT32 RecordType)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(ModID);
        return ModID->GetNumRecords(RecordType);
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return -1;
    }

CPPDLLEXTERN SINT32 GetRecordIDs(ModFile *ModID, const UINT32 RecordType, RECORDIDARRAY RecordIDs)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(ModID);
        RecordIDRetriever retriever(RecordIDs);
        ModID->VisitRecords(RecordType, retriever);
        return retriever.GetCount();
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return -1;
    }

CPPDLLEXTERN SINT32 IsRecordWinning(Record *RecordID, const bool GetExtendedConflicts)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        //ValidatePointer(ModID);
        if(!RecordID->IsWinningDetermined())
            {
            ModFile *WinningModfile = NULL;
            Record *WinningRecord = NULL;
            if(RecordID->IsKeyedByEditorID())
                RecordID->GetParentMod()->Parent->LookupWinningRecord(RecordID->GetEditorIDKey(), WinningModfile, WinningRecord, true);
            else
                RecordID->GetParentMod()->Parent->LookupWinningRecord(RecordID->formID, WinningModfile, WinningRecord, true);
            }
        if(GetExtendedConflicts)
            return RecordID->IsExtendedWinning();
        else if(RecordID->GetParentMod()->Flags.IsExtendedConflicts)
            return false;
        return RecordID->IsWinning();
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return -1;
    }

CPPDLLEXTERN SINT32 GetNumRecordConflicts(Record *RecordID, const bool GetExtendedConflicts)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        return RecordID->GetParentMod()->Parent->GetNumRecordConflicts(RecordID, GetExtendedConflicts);
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return -1;
    }

CPPDLLEXTERN SINT32 GetRecordConflicts(Record *RecordID, RECORDIDARRAY RecordIDs, const bool GetExtendedConflicts)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        return RecordID->GetParentMod()->Parent->GetRecordConflicts(RecordID, RecordIDs, GetExtendedConflicts);
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return -1;
    }

CPPDLLEXTERN SINT32 GetRecordHistory(Record *RecordID, RECORDIDARRAY RecordIDs)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        //ValidatePointer(ModID);
        return RecordID->GetParentMod()->Parent->GetRecordHistory(RecordID, RecordIDs);
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return -1;
    }

CPPDLLEXTERN SINT32 GetNumIdenticalToMasterRecords(ModFile *ModID)
    {
    PROFILE_FUNC
    if(ModID->Flags.IsExtendedConflicts)
        {
        printer("GetNumIdenticalToMasterRecords: Warning - No history available. Mod \"%s\" uses extended conflicts.\n", ModID->ModName);
        return -1;
        }

    try
        {
        //ValidatePointer(RecordID1);
                //ValidatePointer(RecordID2);

        ModID->Parent->identical_records.clear();

        IdenticalToMasterRetriever identical(ModID);

        ModID->VisitAllRecords(identical);
        return ModID->Parent->identical_records.size();
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return -1;
    }

CPPDLLEXTERN SINT32 GetIdenticalToMasterRecords(ModFile *ModID, RECORDIDARRAY RecordIDs)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(RecordID1);
                //ValidatePointer(RecordID2);
        typedef boost::unordered_set<Record *>::iterator identical_it;
        UINT32 count = 0;
        for(identical_it item = ModID->Parent->identical_records.begin(); item != ModID->Parent->identical_records.end(); item++)
            RecordIDs[count++] = *item;

        ModID->Parent->identical_records.clear();
        return count;
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return -1;
    }

CPPDLLEXTERN SINT32 IsRecordFormIDsInvalid(Record *RecordID)
    {
    PROFILE_FUNC

    try
        {
        RecordInvalidFormIDChecker checker;
        return checker.Accept(RecordID);
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return -1;
    }
////////////////////////////////////////////////////////////////////////
//Mod or Record action functions
CPPDLLEXTERN SINT32 UpdateReferences(ModFile *ModID, Record *RecordID, FORMIDARRAY OldFormIDs, FORMIDARRAY NewFormIDs, UINT32ARRAY Changes, const UINT32 ArraySize)
    {
    PROFILE_FUNC

    //Sanity check.
    if(ArraySize == 0)
        return -1;

    //Sanity check.
    try
        {
        //ValidatePointer(CollectionID);
        //ValidatePointer(ModID);
        UINT32 count = 0;
        if(RecordID != NULL) //Swap possible uses of FormIDToReplace in a specific record only
            {
            for(UINT32 ListIndex = 0; ListIndex < ArraySize; ++ListIndex)
                {
                //Sanity check.
                if(OldFormIDs[ListIndex] == NewFormIDs[ListIndex])
                    continue;
                RecordFormIDSwapper swapper(OldFormIDs[ListIndex], NewFormIDs[ListIndex], RecordID->GetParentMod()->FormIDHandler, RecordID->GetParentMod()->Parent->Expanders);
                swapper.Accept(RecordID);
                Changes[ListIndex] = swapper.GetCount();
                count += swapper.GetCount();
                }
            if(count)
                {
                RecordID->IsChanged(true);
                RecordID->GetParentMod()->Parent->changed_records.insert(RecordID);
                }
            }
        else
            {
            ModID->Parent->changed_records.clear();
            //Build a map of references to avoid iterating through every single record N times
            std::map<FORMID, std::vector<Record *> > formID_users;
            RecordFormIDMapper mapper(formID_users, ModID->FormIDHandler, ModID->Parent->Expanders);
            ModID->VisitAllRecords(mapper);
            UINT32 OldFormID = 0, NewFormID = 0;
            RecordReader reader(ModID);
            Record *curRecord;
            for(UINT32 ListIndex = 0; ListIndex < ArraySize; ++ListIndex)
                {
                //Sanity check.
                OldFormID = OldFormIDs[ListIndex];
                NewFormID = NewFormIDs[ListIndex];
                if(OldFormID == NewFormID)
                    continue;
                FormIDSwapper swapper(OldFormID, NewFormID, ModID->FormIDHandler);
                std::vector<Record *> &users = formID_users[OldFormID];
                for(UINT32 ListX2Index = 0; ListX2Index < users.size(); ++ListX2Index)
                    {
                    curRecord = users[ListX2Index];
                    reader.Accept(curRecord);
                    curRecord->VisitFormIDs(swapper);
                    curRecord->IsChanged(true);
                    ModID->Parent->changed_records.insert(curRecord);
                    }
                Changes[ListIndex] = swapper.GetCount();
                count += swapper.GetCount();
                }
            }
        return count;
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return -1;
    }
////////////////////////////////////////////////////////////////////////
//Mod or Record info functions
CPPDLLEXTERN SINT32 GetRecordUpdatedReferences(Collection *CollectionID, Record *RecordID)
    {
    PROFILE_FUNC

    try
        {
        if(RecordID == NULL)
            {
            CollectionID->changed_records.clear();
            return 0;
            }

        return RecordID->GetParentMod()->Parent->changed_records.count(RecordID);
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return -1;
    }
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//Field action functions
CPPDLLEXTERN SINT32 SetIDFields(Record *RecordID, const FORMID FormID, STRING const EditorID)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        //ValidatePointer(ModID);
        //ValidatePointer(RecordID);
        return RecordID->GetParentMod()->Parent->SetIDFields(RecordID, FormID, EditorID);
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return -1;
    }

CPPDLLEXTERN void SetField(Record *RecordID, FIELD_IDENTIFIERS, void *FieldValue, const UINT32 ArraySize)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        //ValidatePointer(ModID);
        //ValidatePointer(RecordID);

        //Ensure the record is fully loaded
        if(!RecordID->IsLoaded())
            {
            RecordReader reader(RecordID);
            reader.Accept(RecordID);
            }

        if(RecordID->SetField(FieldID, ListIndex, ListFieldID, ListX2Index, ListX2FieldID, ListX3Index, ListX3FieldID, FieldValue, ArraySize))
            {
            //returns true if formIDs need to be checked
            //Update the master list if needed
            FormIDMasterUpdater checker(RecordID);
            //checker.Accept(curRecord->formID); //FormID can only be changed through SetRecordIDs, so no need to check
            RecordID->VisitFormIDs(checker);
            //RecordID->HasInvalidFormIDs(checker.result);
            //if(checker.result)
            //    {
            //    UINT8 ModIndex = (UINT8)(RecordID->formID >> 24);
            //    ModFile *ModID = RecordID->GetParentMod();
            //    UINT8 CollapsedIndex = ModID->FormIDHandler.CollapseTable[ModIndex];
            //    STRING LongID = CollapsedIndex >= ModID->TES4.MAST.size() ? ModID->ModName : ModID->TES4.MAST[CollapsedIndex];
            //    VSDPRINT(RecordID->GetStrType());
            //    PRINT_FIELD_IDENTIFIERS;
            //    printer("SetField: Error! Record (%s, 0x%06X) in mod (%s) contains an invalid FormID!\n", LongID, RecordID->formID & 0x00FFFFFF, ModID->ModName);
            //    }
            }

        RecordID->IsChanged(true);
        return;
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    //PRINT_RECORD_IDENTIFIERS;
    PRINT_FIELD_IDENTIFIERS;
    printer("ArraySize: %i\n\n", ArraySize);
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return;
    }

CPPDLLEXTERN void DeleteField(Record *RecordID, FIELD_IDENTIFIERS)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        //ValidatePointer(ModID);
        //ValidatePointer(RecordID);

        //Ensure the record is fully loaded
        if(!RecordID->IsLoaded())
            {
            RecordReader reader(RecordID);
            reader.Accept(RecordID);
            }

        RecordID->DeleteField(FieldID, ListIndex, ListFieldID, ListX2Index, ListX2FieldID, ListX3Index, ListX3FieldID);

        RecordID->IsChanged(true);
        return;
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    //PRINT_RECORD_IDENTIFIERS;
    PRINT_FIELD_IDENTIFIERS;
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return;
    }
////////////////////////////////////////////////////////////////////////
//Field info functions
CPPDLLEXTERN UINT32 GetFieldAttribute(Record *RecordID, FIELD_IDENTIFIERS, const UINT32 WhichAttribute)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        //ValidatePointer(ModID);
        //ValidatePointer(RecordID);

        if(WhichAttribute > 0)
            {
            //Any attribute other than type requires the record to be read
            //Ensure the record is fully loaded
            if(!RecordID->IsLoaded())
                {
                RecordReader reader(RecordID);
                reader.Accept(RecordID);
                }
            }

        return RecordID->GetFieldAttribute(FieldID, ListIndex, ListFieldID, ListX2Index, ListX2FieldID, ListX3Index, ListX3FieldID, WhichAttribute);
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    //PRINT_RECORD_IDENTIFIERS;
    PRINT_FIELD_IDENTIFIERS;
    printer("WhichAttribute: %i\n\n", WhichAttribute);
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return UNKNOWN_FIELD;
    }

CPPDLLEXTERN void * GetField(Record *RecordID, FIELD_IDENTIFIERS, void **FieldValues)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        //ValidatePointer(ModID);
        //ValidatePointer(RecordID);

        //Ensure the record is fully loaded
        if(!RecordID->IsLoaded())
            {
            RecordReader reader(RecordID);
            reader.Accept(RecordID);
            }

        return RecordID->GetField(FieldID, ListIndex, ListFieldID, ListX2Index, ListX2FieldID, ListX3Index, ListX3FieldID, FieldValues);
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    //PRINT_RECORD_IDENTIFIERS;
    PRINT_FIELD_IDENTIFIERS;
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback(__FUNCTION__);
    return NULL;
    }
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////