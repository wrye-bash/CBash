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
    for (uint32_t x = 0; x < Stages.value.size(); ++x)
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

SKCTDA::SKCTDA() :
    operType(0),
    compValue(0),
    ifunc(5), // 5 type makes sure conditions don't try to resolve param1/param2
    param1(0),
    param2(0),
    runOnType(0),
    reference(0),
    param3(0)
{
    memset(&unused1, 0, sizeof(unused1));
    memset(&unused2, 0, sizeof(unused2));
}

SKCTDA::~SKCTDA()
{
    //
}

bool SKCTDA::VisitFormIDs(FormIDOp &op)
{
    Function_Arguments_Iterator curCTDAFunction = SKFunction_Arguments.find(ifunc);

    if (IsUseGlobal())
        op.Accept(compValue);

    if (curCTDAFunction != SKFunction_Arguments.end())
    {
        const FunctionArguments &CTDAFunction = curCTDAFunction->second;
        if (CTDAFunction.first == eFORMID)
            op.Accept(param1);
        if (CTDAFunction.second == eFORMID)
            op.Accept(param2);
    }
    else
        printer("Warning: CTDA uses an unkown function (%d)!\n", ifunc);

    if (IsResultOnReference())
        op.Accept(reference);

    return op.Stop();
}

void SKCTDA::Write(FileWriter &writer)
{
    Function_Arguments_Iterator curCTDAFunction = SKFunction_Arguments.find(ifunc);
    if (curCTDAFunction != SKFunction_Arguments.end())
    {
        const FunctionArguments &CTDAFunction = curCTDAFunction->second;
        if (CTDAFunction.first == eNONE)
            param1 = 0;
        if (CTDAFunction.second == eNONE)
            param2 = 0;
    }
    else
        printer("Warning: CTDA uses an unknown function (%d)!\n", ifunc);

    writer.record_write_subrecord(REV32(CTDA), this, sizeof(SKCTDA));
}

bool SKCTDA::operator == (const SKCTDA &other) const
{
    return (operType == other.operType &&
            (IsUseGlobal() ? compValue == other.compValue : AlmostEqual(*(float *)&compValue, *(float *)&other.compValue, 2)) &&
            ifunc == other.ifunc &&
            param1 == other.param1 &&
            param2 == other.param2 &&
            runOnType == other.runOnType &&
            reference == other.reference &&
            param3 == other.param3
            );
}

bool SKCTDA::operator != (const SKCTDA &other) const
{
    return !(*this == other);
}

bool SKCTDA::IsEqual() const
{
    return (operType & eOperTypeMask) == eEqual;
}

void SKCTDA::IsEqual(bool value)
{
    if (value)
        operType = (operType & fOperFlagMask) | eEqual;
    else
        operType = (operType & fOperFlagMask) | eNotEqual;
}

bool SKCTDA::IsNotEqual() const
{
    return (operType & eOperTypeMask) == eNotEqual;
}

void SKCTDA::IsNotEqual(bool value)
{
    if (value)
        operType = (operType & fOperFlagMask) | eNotEqual;
    else
        operType = (operType & fOperFlagMask) | eEqual;
}

bool SKCTDA::IsGreater() const
{
    return  (operType & eOperTypeMask) == eGreater;
}

void SKCTDA::IsGreater(bool value)
{
    if (value)
        operType = (operType & fOperFlagMask) | eGreater;
    else
        operType = (operType & fOperFlagMask) | eLessOrEqual;
}

bool SKCTDA::IsGreaterOrEqual() const
{
    return (operType & eOperTypeMask) == eGreaterOrEqual;
}

void SKCTDA::IsGreaterOrEqual(bool value)
{
    if (value)
        operType = (operType & fOperFlagMask) | eGreaterOrEqual;
    else
        operType = (operType & fOperFlagMask) | eLess;
}

bool SKCTDA::IsLess() const
{
    return (operType & eOperTypeMask) == eLess;
}

void SKCTDA::IsLess(bool value)
{
    if (value)
        operType = (operType & fOperFlagMask) | eLess;
    else
        operType = (operType & fOperFlagMask) | eGreaterOrEqual;
}

bool SKCTDA::IsLessOrEqual() const
{
    return (operType & eOperTypeMask) == eLessOrEqual;
}

void SKCTDA::IsLessOrEqual(bool value)
{
    if (value)
        operType = (operType & fOperFlagMask) | eLessOrEqual;
    else
        operType = (operType & fOperFlagMask) | eGreater;
}

bool SKCTDA::IsType(uint8_t Type) const
{
    return (operType & eOperTypeMask) == (Type & eOperTypeMask);
}

void SKCTDA::SetType(uint8_t Type)
{
    operType = (operType & fOperFlagMask) | (Type & eOperTypeMask);
}

bool SKCTDA::IsNone() const
{
    return (operType & fOperFlagMask) == fIsNone;
}

void SKCTDA::IsNone(bool value)
{
    if (value)
        operType &= eOperTypeMask;
}

bool SKCTDA::IsOr() const
{
    return (operType & fIsOr) != 0;
}

void SKCTDA::IsOr(bool value)
{
    SETBIT(operType, fIsOr, value);
}

bool SKCTDA::IsUseAliases() const
{
    return (operType & fIsUseAliases) != 0;
}

void SKCTDA::IsUseAliases(bool value)
{
    SETBIT(operType, fIsUseAliases, value);
}

bool SKCTDA::IsUseGlobal() const
{
    return (operType & fIsUseGlobal) != 0;
}

void SKCTDA::IsUseGlobal(bool value)
{
    SETBIT(operType, fIsUseGlobal, value);
}

bool SKCTDA::IsUsePackData() const
{
    return (operType & fIsUsePackData) != 0;
}

void SKCTDA::IsUsePackData(bool value)
{
    SETBIT(operType, fIsUsePackData, value);
}

bool SKCTDA::IsSwapSubject() const
{
    return (operType & fIsSwapSubject) != 0;
}

void SKCTDA::IsSwapSubject(bool value)
{
    SETBIT(operType, fIsSwapSubject, value);
}

bool SKCTDA::IsFlagMask(uint8_t Mask, bool Exact) const
{
    return Exact ? (operType & fOperFlagMask & Mask) == (Mask & fOperFlagMask)
                 : (operType & fOperFlagMask & Mask) != 0;
}

void SKCTDA::SetFlagMask(uint8_t Mask)
{
    operType = (operType & eOperTypeMask) | (Mask & fOperFlagMask);
}

bool SKCTDA::IsResultOnSubject() const
{
    return runOnType == eSubject;
}

void SKCTDA::IsResultOnSubject(bool value)
{
    runOnType = value ? eSubject : eTarget;
}

bool SKCTDA::IsResultOnTarget() const
{
    return runOnType == eTarget;
}

void SKCTDA::IsResultOnTarget(bool value)
{
    runOnType = value ? eTarget : eSubject;
}

bool SKCTDA::IsResultOnReference() const
{
    return runOnType == eReference;
}

void SKCTDA::IsResultOnReference(bool value)
{
    runOnType = value ? eReference : eSubject;
}

bool SKCTDA::IsResultOnCombatTarget() const
{
    return runOnType == eCombatTarget;
}

void SKCTDA::IsResultOnCombatTarget(bool value)
{
    runOnType = value ? eCombatTarget : eSubject;
}

bool SKCTDA::IsResultOnLinkedReference() const
{
    return runOnType == eLinkedReference;
}

void SKCTDA::IsResultOnLinkedReference(bool value)
{
    runOnType = value ? eLinkedReference : eSubject;
}

bool SKCTDA::IsResultOnQuestAlias() const
{
    return runOnType == eQuestAlias;
}

void SKCTDA::IsResultOnQuestAlias(bool value)
{
    runOnType = value ? eQuestAlias : eSubject;
}

bool SKCTDA::IsResultOnPackageData() const
{
    return runOnType == ePackageData;
}

void SKCTDA::IsResultOnPackageData(bool value)
{
    runOnType = value ? ePackageData : eSubject;
}

bool SKCTDA::IsResultOnEventData() const
{
    return runOnType == eEventData;
}

void SKCTDA::IsResultOnEventData(bool value)
{
    runOnType = value ? ePackageData : eSubject;
}

bool SKCTDA::IsResultOnType(uint32_t Type) const
{
    return runOnType == Type;
}

void SKCTDA::SetResultOnType(uint32_t Type)
{
    runOnType = Type;
}

bool SKCondition::VisitFormIDs(FormIDOp &op)
{
    return CTDA.value.VisitFormIDs(op);
}

void SKCondition::Write(FileWriter &writer)
{
    WRITE(CTDA);
    WRITE(CIS1);
    WRITE(CIS2);
}

bool SKCondition::operator == (const SKCondition &other) const
{
    return (CTDA == other.CTDA &&
            CIS1.equals(other.CIS1) &&
            CIS2.equals(other.CIS2)
            );
}

bool SKCondition::operator != (const SKCondition &other) const
{
    return !(*this == other);
}

SKEFIT::SKEFIT() :
    magnitude(0.0),
    area(0),
    duration(0)
{
    //
}

SKEFIT::~SKEFIT()
{
    //
}

bool SKEFIT::operator == (const SKEFIT &other) const
{
    return (AlmostEqual(magnitude, other.magnitude, 2) &&
            area == other.area &&
            duration == other.duration
            );
}

bool SKEFIT::operator != (const SKEFIT &other) const
{
    return !(*this == other);
}

bool SKEffect::VisitFormIDs(FormIDOp &op)
{
    op.Accept(EFID.value);
    for (uint32_t i = 0; i < CTDA.value.size(); ++i)
        CTDA.value[i]->VisitFormIDs(op);
    return op.Stop();
}

void SKEffect::Write(FileWriter &writer)
{
    WRITE(EFID);
    WRITE(EFIT);
    CTDA.Write(writer, true);
}

bool SKEffect::operator == (const SKEffect &other) const
{
    return (EFID == other.EFID &&
            EFIT == other.EFIT &&
            CTDA == other.CTDA
            );
}

bool SKEffect::operator != (const SKEffect &other) const
{
    return !(*this == other);
}

} // namespace Sk
