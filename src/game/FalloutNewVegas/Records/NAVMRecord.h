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
#pragma once
#include "common/Common.h"
#include "common/GenericRecord.h"
#include "../FNVRecord.h"

namespace FNV
{
class NAVMRecord : public FNVRecord //Navigation Mesh
    {
    private:
        struct NAVMDATA //Data
            {
            FORMID  cell;
            uint32_t  numVertices, numTriangles, numConnections, numNVCA, numDoors;

            NAVMDATA();
            ~NAVMDATA();

            bool operator ==(const NAVMDATA &other) const;
            bool operator !=(const NAVMDATA &other) const;
            };

        struct NAVMVertex //Vertex
            {
            float x, y, z;

            NAVMVertex();
            ~NAVMVertex();

            bool operator ==(const NAVMVertex &other) const;
            bool operator !=(const NAVMVertex &other) const;
            };

        struct NAVMNVTR //Triangle
            {
            int16_t  vertex1, vertex2, vertex3;
            int16_t  edge1, edge2, edge3;
            uint32_t  flags;

            enum flagsFlags
                {
                fIsTriangle0External = 0x00000001,
                fIsTriangle1External = 0x00000002,
                fIsTriangle2External = 0x00000004,
                fIsUnknown4          = 0x00000008,
                fIsUnknown5          = 0x00000010,
                fIsUnknown6          = 0x00000020,
                fIsUnknown7          = 0x00000040,
                fIsUnknown8          = 0x00000080,
                fIsUnknown9          = 0x00000100,
                fIsUnknown10         = 0x00000200,
                fIsUnknown11         = 0x00000400,
                fIsUnknown12         = 0x00000800,
                fIsUnknown13         = 0x00001000,
                fIsUnknown14         = 0x00002000,
                fIsUnknown15         = 0x00004000,
                fIsUnknown16         = 0x00008000,
                fIsUnknown17         = 0x00010000,
                fIsUnknown18         = 0x00020000,
                fIsUnknown19         = 0x00040000,
                fIsUnknown20         = 0x00080000,
                fIsUnknown21         = 0x00100000,
                fIsUnknown22         = 0x00200000,
                fIsUnknown23         = 0x00400000,
                fIsUnknown24         = 0x00800000,
                fIsUnknown25         = 0x01000000,
                fIsUnknown26         = 0x02000000,
                fIsUnknown27         = 0x04000000,
                fIsUnknown28         = 0x08000000,
                fIsUnknown29         = 0x10000000,
                fIsUnknown30         = 0x20000000,
                fIsUnknown31         = 0x40000000,
                fIsUnknown32         = 0x80000000
                };

            NAVMNVTR();
            ~NAVMNVTR();

            bool   IsTriangle0External();
            void   IsTriangle0External(bool value);
            bool   IsTriangle1External();
            void   IsTriangle1External(bool value);
            bool   IsTriangle2External();
            void   IsTriangle2External(bool value);
            bool   IsUnknown4();
            void   IsUnknown4(bool value);
            bool   IsUnknown5();
            void   IsUnknown5(bool value);
            bool   IsUnknown6();
            void   IsUnknown6(bool value);
            bool   IsUnknown7();
            void   IsUnknown7(bool value);
            bool   IsUnknown8();
            void   IsUnknown8(bool value);
            bool   IsUnknown9();
            void   IsUnknown9(bool value);
            bool   IsUnknown10();
            void   IsUnknown10(bool value);
            bool   IsUnknown11();
            void   IsUnknown11(bool value);
            bool   IsUnknown12();
            void   IsUnknown12(bool value);
            bool   IsUnknown13();
            void   IsUnknown13(bool value);
            bool   IsUnknown14();
            void   IsUnknown14(bool value);
            bool   IsUnknown15();
            void   IsUnknown15(bool value);
            bool   IsUnknown16();
            void   IsUnknown16(bool value);
            bool   IsUnknown17();
            void   IsUnknown17(bool value);
            bool   IsUnknown18();
            void   IsUnknown18(bool value);
            bool   IsUnknown19();
            void   IsUnknown19(bool value);
            bool   IsUnknown20();
            void   IsUnknown20(bool value);
            bool   IsUnknown21();
            void   IsUnknown21(bool value);
            bool   IsUnknown22();
            void   IsUnknown22(bool value);
            bool   IsUnknown23();
            void   IsUnknown23(bool value);
            bool   IsUnknown24();
            void   IsUnknown24(bool value);
            bool   IsUnknown25();
            void   IsUnknown25(bool value);
            bool   IsUnknown26();
            void   IsUnknown26(bool value);
            bool   IsUnknown27();
            void   IsUnknown27(bool value);
            bool   IsUnknown28();
            void   IsUnknown28(bool value);
            bool   IsUnknown29();
            void   IsUnknown29(bool value);
            bool   IsUnknown30();
            void   IsUnknown30(bool value);
            bool   IsUnknown31();
            void   IsUnknown31(bool value);
            bool   IsUnknown32();
            void   IsUnknown32(bool value);
            bool   IsFlagMask(uint32_t Mask, bool Exact=false);
            void   SetFlagMask(uint32_t Mask);

            bool operator ==(const NAVMNVTR &other) const;
            bool operator !=(const NAVMNVTR &other) const;
            };

        struct NAVMNVDP //Door
            {
            FORMID  door;
            uint16_t  unknown1;
            uint8_t   unused1[2];

            NAVMNVDP();
            ~NAVMNVDP();

            bool operator ==(const NAVMNVDP &other) const;
            bool operator !=(const NAVMNVDP &other) const;
            };

        #pragma pack(push)
        #pragma pack(2)
        struct NAVMNVEX //External Connection
            {
            uint8_t   unknown1[4];
            FORMID  mesh; //Navigation Mesh
            uint16_t  triangle;

            NAVMNVEX();
            ~NAVMNVEX();

            bool operator ==(const NAVMNVEX &other) const;
            bool operator !=(const NAVMNVEX &other) const;
            };
        #pragma pack(pop)

    public:
        StringRecord EDID; //Editor ID
        ReqSimpleSubRecord<uint32_t> NVER; //Version
        ReqSubRecord<NAVMDATA> DATA; //Data
        UnorderedPackedArray<NAVMVertex> NVVX; //Vertices
        UnorderedPackedArray<NAVMNVTR> NVTR; //Triangles
        UnorderedPackedArray<int16_t> NVCA; //Unknown
        UnorderedPackedArray<NAVMNVDP> NVDP; //Doors
        RawRecord NVGD; //Unknown
        UnorderedPackedArray<NAVMNVEX> NVEX; //External Connections

        NAVMRecord(unsigned char *_recData=NULL);
        NAVMRecord(NAVMRecord *srcRecord);
        ~NAVMRecord();

        bool   VisitFormIDs(FormIDOp &op);

        uint32_t GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, uint32_t WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, uint32_t ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        uint32_t GetType();
        char * GetStrType();

        int32_t ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        int32_t Unload();
        int32_t WriteRecord(FileWriter &writer);

        bool operator ==(const NAVMRecord &other) const;
        bool operator !=(const NAVMRecord &other) const;
        bool equals(Record *other);
        bool deep_equals(Record *master, RecordOp &read_self, RecordOp &read_master, boost::unordered_set<Record *> &identical_records);
    };
}