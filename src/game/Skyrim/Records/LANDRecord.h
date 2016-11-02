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

namespace Sk
{
class LANDRecord : public TES5Record //Landscape
    {
    public:
        struct LANDNORMALS
            {
            uint8_t   x;
            uint8_t   y;
            uint8_t   z;

            LANDNORMALS();
            ~LANDNORMALS();

            bool operator ==(const LANDNORMALS &other) const;
            bool operator !=(const LANDNORMALS &other) const;
            };

        struct LANDVNML
            {
            LANDNORMALS VNML[33][33];

            bool operator ==(const LANDVNML &other) const;
            bool operator !=(const LANDVNML &other) const;
            };

        struct LANDVHGT
            {
            float offset;
            int8_t   VHGT[33][33];
            uint8_t   unused1[3];

            LANDVHGT();
            ~LANDVHGT();

            bool operator ==(const LANDVHGT &other) const;
            bool operator !=(const LANDVHGT &other) const;
            };

        struct LANDCOLORS
            {
            uint8_t   red;
            uint8_t   green;
            uint8_t   blue;

            LANDCOLORS();
            ~LANDCOLORS();

            bool operator ==(const LANDCOLORS &other) const;
            bool operator !=(const LANDCOLORS &other) const;
            };

        struct LANDVCLR
            {
            LANDCOLORS VCLR[33][33];

            bool operator ==(const LANDVCLR &other) const;
            bool operator !=(const LANDVCLR &other) const;
            };

        struct LANDGENTXT
            {
            FORMID  texture;
            uint8_t   quadrant;
            uint8_t   unused1;
            int16_t  layer;

            LANDGENTXT();
            ~LANDGENTXT();

            bool operator ==(const LANDGENTXT &other) const;
            bool operator !=(const LANDGENTXT &other) const;
            };

        struct LANDVTXT
            {
            uint16_t  position;
            uint8_t   unused1[2];
            float opacity;

            LANDVTXT();
            ~LANDVTXT();

            bool operator ==(const LANDVTXT &other) const;
            bool operator !=(const LANDVTXT &other) const;
            };

        struct LANDLAYERS
            {
            ReqSubRecord<LANDGENTXT> ATXT;
            UnorderedPackedArray<LANDVTXT> VTXT; //Actually ordered...
            //Record order doesn't matter on opacities, so equality testing isn't easy
            //Instead, they're keyed by position (VTXT.value.position)
            //The proper solution would be to see if the opacity at each position matches
            //Fix-up later

            void Write(FileWriter &writer);

            bool operator ==(const LANDLAYERS &other) const;
            bool operator !=(const LANDLAYERS &other) const;
            };

        //struct LANDPOINTS
        //    {
        //    float AlphaLayer[8];
        //    unsigned char height;
        //    unsigned char normalX;
        //    unsigned char normalY;
        //    unsigned char normalZ;
        //    unsigned char red;
        //    unsigned char green;
        //    unsigned char blue;
        //    LANDPOINTS():AlphaLayer(8, 0.0) {}
        //    };
        //
        //struct LANDMERGED
        //    {//156B, 40*33*33 (1.319GB), 28B - 7B*33*33 (265MB)
        //    LANDPOINTS Points[33][33];
        //    //uint32_t bottomLeftAlphas[8];
        //    //uint32_t bottomRightAlphas[8];
        //    //uint32_t topLeftAlphas[8];
        //    //uint32_t topRightAlphas[8];
        //    uint32_t bottomLeftBaseTexture;
        //    uint32_t bottomRightBaseTexture;
        //    uint32_t topLeftBaseTexture;
        //    uint32_t topRightBaseTexture;
        //    float heightOffset;
        //    short bottomLeftBaseLayer;
        //    short bottomRightBaseLayer;
        //    short topLeftBaseLayer;
        //    short topRightBaseLayer;
        //    //LANDMERGED():Points(33, std::vector<LANDPOINTS>(33)), bottomLeftAlphas(8),  bottomRightAlphas(8),  topLeftAlphas(8),  topRightAlphas(8) {}
        //    };

        enum QuadrantEnum {
            eBottomLeft,
            eBottomRight,
            eTopLeft,
            eTopRight
            };

    public:
        RawRecord DATA; //Unknown
        OptSubRecord<LANDVNML> VNML; //Vertex Normals
        OptSubRecord<LANDVHGT> VHGT; //Vertex Height Map
        OptSubRecord<LANDVCLR> VCLR; //Vertex Colours
        UnorderedSparseArray<LANDGENTXT *> BTXT; //Base Layer Header
        UnorderedSparseArray<LANDLAYERS *> Layers; //Layers
        UnorderedPackedArray<FORMID> VTEX; //Textures
        //LANDMERGED *Merged;

        LANDRecord *WestLand;
        LANDRecord *EastLand;
        LANDRecord *NorthLand;
        LANDRecord *SouthLand;

        LANDRecord(unsigned char *_recData=NULL);
        LANDRecord(LANDRecord *srcRecord);
        ~LANDRecord();

        bool    VisitFormIDs(FormIDOp &op);

        uint8_t   CalcQuadrant(const uint32_t &row, const uint32_t &column);
        uint16_t  CalcPosition(const uint8_t &curQuadrant, const uint32_t &row, const uint32_t &column);
        float CalcHeight(const uint32_t &row, const uint32_t &column);

        uint32_t  GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, uint32_t WhichAttribute=0);
        void *  GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool    SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, uint32_t ArraySize=0);
        void    DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        uint32_t  GetSize(bool forceCalc=false);
        uint32_t  GetType();
        char *  GetStrType();

        int32_t  ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk);
        int32_t  Unload();
        int32_t  WriteRecord(FileWriter &writer);

        bool operator ==(const LANDRecord &other) const;
        bool operator !=(const LANDRecord &other) const;
        bool equals(Record *other);
        bool deep_equals(Record *master, RecordOp &read_self, RecordOp &read_master, boost::unordered_set<Record *> &identical_records);
    };
}