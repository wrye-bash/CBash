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
#include "SkyrimChunks.h"

namespace Sk {

SKLVLO::SKLVLO():
    level(0),
    listId(0),
    count(1)
    {
        memset(&unused1[0], 0x00, sizeof(unused1));
        memset(&unused2[0], 0x00, sizeof(unused2));
    }

SKLVLO::~SKLVLO()
    {
        //
    }

void SKLVLO::Write(FileWriter &writer)
    {
        writer.record_write_subrecord(REV32(LVLO), this, sizeof(SKLVLO));
    }

bool SKLVLO::operator == (const SKLVLO &other) const
    {
        return (level == other.level &&
                listId == other.listId &&
                count == other.count
                );
    }

bool SKLVLO::operator != (const SKLVLO &other) const
    {
        return !(*this == other);
    }

bool SKLVLOCOED::IsGlobal() const
    {
        return COED.IsLoaded() ? COED->IsGlobal() : false;
    }

bool SKLVLOCOED::IsRank() const
    {
        return COED.IsLoaded() ? COED->IsRank() : false;
    }

void SKLVLOCOED::Write(FileWriter &writer)
    {
        WRITE(LVLO);
        WRITE(COED);
    }

bool SKLVLOCOED::operator == (const SKLVLOCOED &other) const
    {
        return (LVLO == other.LVLO &&
                COED == other.COED
                );
    }

bool SKLVLOCOED::operator != (const SKLVLOCOED &other) const
    {
        return !(*this == other);
    }

MODEL::MODEL()
    {
        //
    }

MODEL::~MODEL()
    {
        //
    }

void MODEL::Write(FileWriter &writer)
    {
        WRITE(MODL);
        WRITE(MODT);
    }

bool MODEL::operator ==(const MODEL &other) const
    {
        return (MODL.equalsi(other.MODL) &&
                MODT == other.MODT);
    }

bool MODEL::operator !=(const MODEL &other) const
    {
        return !(*this == other);
    }

GENCNAM::GENCNAM() :
    red(0), green(0), blue(0), unk1(0)
    {
        //
    }

GENCNAM::~GENCNAM()
    {
        //
    }

bool GENCNAM::operator ==(const GENCNAM &other) const
    {
        return (red == other.red &&
                blue == other.blue &&
                green == other.green &&
                unk1 == other.unk1
                );
    }

bool GENCNAM::operator !=(const GENCNAM &other) const
    {
        return !(*this == other);
    }

void SKDESTSTAGE::Write(FileWriter &writer)
{
    WRITE(DSTD);
    if (DMDL.IsLoaded())
    {
        WRITE(DMDL);
        WRITE(DMDT);
        WRITE(DMDS);
    }
    WRITEEMPTY(DSTF);
}

void SKDESTSTAGE::VisitFormIDs(FormIDOp &op)
{
    op.Accept(DSTD->explosion);
    op.Accept(DSTD->debris);
    DMDS.VisitFormIDs(op);
}

bool SKDESTSTAGE::operator == (const SKDESTSTAGE &other) const
{
    return (DSTD == other.DSTD &&
            DMDL.equalsi(other.DMDL) &&
            DMDT == other.DMDT &&
            DMDS == other.DMDS
            );
}

bool SKDESTSTAGE::operator != (const SKDESTSTAGE &other) const
{
    return !(*this == other);
}

bool sortSKDESTStages::operator()(const SKDESTSTAGE *lhs, const SKDESTSTAGE *rhs) const
{
    return lhs->DSTD.value.index < rhs->DSTD.value.index;
}

void SKDESTRUCT::Write(FileWriter &writer)
{
    WRITE(DEST);
    Stages.Write(writer);
}

void SKDESTRUCT::VisitFormIDs(FormIDOp &op)
{
    for (UINT32 x = 0; x < Stages.value.size(); ++x)
        Stages.value[x]->VisitFormIDs(op);
}

bool SKDESTRUCT::operator == (const SKDESTRUCT &other) const
{
    return (DEST == other.DEST &&
            Stages == other.Stages
            );
}

bool SKDESTRUCT::operator != (const SKDESTRUCT &other) const
{
    return !(*this == other);
}

} // namespace Sk
