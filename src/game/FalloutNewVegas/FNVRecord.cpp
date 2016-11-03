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

#include "FNVRecord.h"
#include "FNVFile.h"
#include <zlib.h>

FNVRecord::FNVRecord(unsigned char *_recData):
    Record(_recData),
    formVersion(0)
    {
    memset(&versionControl2[0], 0x00, 2);
    }

FNVRecord::~FNVRecord()
    {
    //
    }

bool FNVRecord::Read()
    {
    if(IsLoaded() || IsChanged())
        return false;
    uint32_t recSize = *(uint32_t*)&recData[-20];

    //Check against the original record flags to see if it is compressed since the current flags may have changed
    if ((*(uint32_t*)&recData[-16] & fIsCompressed) != 0)
        {
        unsigned char localBuffer[BUFFERSIZE];
        uint32_t expandedRecSize = *(uint32_t*)recData;
        unsigned char *buffer = (expandedRecSize >= BUFFERSIZE) ? new unsigned char[expandedRecSize] : &localBuffer[0];
        uncompress(buffer, (uLongf*)&expandedRecSize, &recData[4], recSize - 4);
        ParseRecord(buffer, buffer + expandedRecSize, true);
        if(buffer != &localBuffer[0])
            delete [] buffer;
        }
    else
        ParseRecord(recData, recData + recSize);

    IsLoaded(true);
    return true;
    }

uint32_t FNVRecord::Write(FileWriter &writer, const bool &bMastersChanged, FormIDResolver &expander, FormIDResolver &collapser, std::vector<FormIDResolver *> &Expanders)
    {
    uint32_t recSize = 0;
    uint32_t recType = GetType();

    collapser.Accept(formID);

    if(!IsChanged())
        {
        if(bMastersChanged || flags != *(uint32_t*)&recData[-16])
            {
            //if masters have changed, all formIDs have to be updated...
            //or if the flags have changed internally (notably fIsDeleted or fIsCompressed, possibly others)
            //so the record can't just be written as is.
            if(Read())
                {
                //if(expander.IsValid(data)) //optimization disabled for testing
                //    VisitFormIDs(expander);
                //printer("Looking for correct expander\n");
                int32_t index = -1;
                for(uint32_t x = 0; x < Expanders.size(); ++x)
                    if(IsValid(*Expanders[x]))
                        {
                        //if(index != -1)
                        //    {
                        //    printer("Multiple 'Correct' expanders found (%08X)! Using last one found (likely incorrect unless lucky)\n", formID);
                        //    printer("  %i:   %08X, %08X, %08X\n", index, Expanders[index]->FileStart, data, Expanders[index]->FileEnd);
                        //    printer("  %i:   %08X, %08X, %08X\n", x, Expanders[x]->FileStart, data, Expanders[x]->FileEnd);
                        //    printer("Expanders:\n");
                        //    for(uint32_t z = 0; z < Expanders.size(); ++z)
                        //        printer("  %i of %i:   %08X, %08X\n", z, Expanders.size(), Expanders[z]->FileStart, Expanders[z]->FileEnd);
                        //    }
                        index = x;
                        break;
                        }
                if(index == -1)
                    {
                    printer("Unable to find the correct expander!\n");
                    VisitFormIDs(expander);
                    }
                else
                    VisitFormIDs(*Expanders[index]);
                }
            }
        else
            {
            //if masters have not changed, the record can just be written from the read buffer
            recSize = *(uint32_t*)&recData[-20];

            writer.file_write(&recType, 4);
            writer.file_write(&recSize, 4);
            writer.file_write(&flags, 4);
            writer.file_write(&formID, 4);
            writer.file_write(&flagsUnk, 4);
            writer.file_write(&formVersion, 2);
            writer.file_write(&versionControl2[0], 2);
            writer.file_write(recData, recSize);
            Unload();
            return recSize + 24;
            }
        }

    VisitFormIDs(collapser);

    if(!IsDeleted())
        {
        //IsCompressed(true); //Test code
        WriteRecord(writer);
        recSize = IsCompressed() ? writer.record_compress() : writer.record_size();
        writer.file_write(&recType, 4);
        writer.file_write(&recSize, 4);
        writer.file_write(&flags, 4);
        writer.file_write(&formID, 4);
        writer.file_write(&flagsUnk, 4);
        writer.file_write(&formVersion, 2);
        writer.file_write(&versionControl2[0], 2);
        //if(IsCompressed())
        //    {
        //    printer("Compressed: %08X\n", formID);
        //    }
        writer.record_flush();
        }
    else
        {
        writer.file_write(&recType, 4);
        writer.file_write(&recSize, 4);
        writer.file_write(&flags, 4);
        writer.file_write(&formID, 4);
        writer.file_write(&flagsUnk, 4);
        writer.file_write(&formVersion, 2);
        writer.file_write(&versionControl2[0], 2);
        }

    expander.Accept(formID);
    if(IsChanged())
        VisitFormIDs(expander);
    else
        Unload();
    return recSize + 24;
    }
