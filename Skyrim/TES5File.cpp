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
// TES5File.cpp
#include "../Common.h"
#include "../GenericRecord.h"
#include "TES5File.h"
#include "SkyrimCommon.h"

TES5File::TES5File(Collection *_Parent, STRING FileName, STRING ModName, const UINT32 _flags):
    ModFile(_Parent, FileName, ModName, _flags),
    LookupStrings(NULL)
    {
    //
    }

TES5File::~TES5File()
    {
        if (LookupStrings)
            delete LookupStrings;
    }

void TES5File::SetFilter(bool inclusive, boost::unordered_set<UINT32> &RecordTypes, boost::unordered_set<FORMID> &WorldSpaces) {
  filter_inclusive = inclusive;
  filter_records = RecordTypes;
  filter_wspaces = WorldSpaces;
}

SINT32 TES5File::LoadTES4()
    {
    if(TES4.IsLoaded() || !Open())
        {
        if(!TES4.IsLoaded() && !Open())
            printer("TES5File::LoadTES4: Error - Unable to load the TES4 record for mod \"%s\". The mod is not open for reading.\n", ModName);
        return 0;
        }
    buffer_position = buffer_start + 4;

    UINT32 recSize = 0;
    recSize = *(UINT32 *)buffer_position;
    buffer_position += 4;

    TES4.flags = *(UINT32 *)buffer_position;
    buffer_position += 4;

    TES4.formID = *(FORMID *)buffer_position;
    buffer_position += 4;

    TES4.flagsUnk = *(UINT32 *)buffer_position;
    buffer_position += 4;

    TES4.formVersion = *(UINT16 *)buffer_position;
    buffer_position += 2;

    TES4.versionControl2[0] = *(UINT8 *)buffer_position;
    buffer_position++;

    TES4.versionControl2[1] = *(UINT8 *)buffer_position;
    buffer_position++;

    TES4.recData = buffer_position;
    TES4.Read();
    TES4.IsChanged(true); //prevents the record from ever being unloaded
    buffer_position += recSize;
    return 1;
    }

SINT32 TES5File::Load(RecordOp &read_parser, RecordOp &indexer, std::vector<FormIDResolver *> &Expanders, std::vector<Record *> &DeletedRecords)
    {
    enum IgTopRecords {
        eIgGMST = REV32(GMST) | 0x00001000, //Record::fIsIgnored
        eIgTXST = REV32(TXST) | 0x00001000,
        eIgGLOB = REV32(GLOB) | 0x00001000,
        eIgCLAS = REV32(CLAS) | 0x00001000,
        eIgFACT = REV32(FACT) | 0x00001000,
        eIgHDPT = REV32(HDPT) | 0x00001000,
        eIgHAIR = REV32(HAIR) | 0x00001000,
        eIgEYES = REV32(EYES) | 0x00001000,
        eIgRACE = REV32(RACE) | 0x00001000,
        eIgSOUN = REV32(SOUN) | 0x00001000,
        eIgASPC = REV32(ASPC) | 0x00001000,
        eIgMGEF = REV32(MGEF) | 0x00001000,
        eIgSCPT = REV32(SCPT) | 0x00001000,
        eIgLTEX = REV32(LTEX) | 0x00001000,
        eIgENCH = REV32(ENCH) | 0x00001000,
        eIgSPEL = REV32(SPEL) | 0x00001000,
        eIgACTI = REV32(ACTI) | 0x00001000,
        eIgTACT = REV32(TACT) | 0x00001000,
        eIgARMO = REV32(ARMO) | 0x00001000,
        eIgBOOK = REV32(BOOK) | 0x00001000,
        eIgCONT = REV32(CONT) | 0x00001000,
        eIgDOOR = REV32(DOOR) | 0x00001000,
        eIgINGR = REV32(INGR) | 0x00001000,
        eIgLIGH = REV32(LIGH) | 0x00001000,
        eIgMISC = REV32(MISC) | 0x00001000,
        eIgAPPA = REV32(APPA) | 0x00001000,
        eIgSTAT = REV32(STAT) | 0x00001000,
        eIgSCOL = REV32(SCOL) | 0x00001000,
        eIgMSTT = REV32(MSTT) | 0x00001000,
        eIgPWAT = REV32(PWAT) | 0x00001000,
        eIgGRAS = REV32(GRAS) | 0x00001000,
        eIgTREE = REV32(TREE) | 0x00001000,
        eIgFLOR = REV32(FLOR) | 0x00001000,
        eIgFURN = REV32(FURN) | 0x00001000,
        eIgWEAP = REV32(WEAP) | 0x00001000,
        eIgAMMO = REV32(AMMO) | 0x00001000,
        eIgNPC_ = REV32(NPC_) | 0x00001000,
        eIgLVLN = REV32(LVLN) | 0x00001000,
        eIgKEYM = REV32(KEYM) | 0x00001000,
        eIgALCH = REV32(ALCH) | 0x00001000,
        eIgIDLM = REV32(IDLM) | 0x00001000,
        eIgCOBJ = REV32(COBJ) | 0x00001000,
        eIgPROJ = REV32(PROJ) | 0x00001000,
        eIgSLGM = REV32(SLGM) | 0x00001000,
        eIgLVLI = REV32(LVLI) | 0x00001000,
        eIgWTHR = REV32(WTHR) | 0x00001000,
        eIgCLMT = REV32(CLMT) | 0x00001000,
        eIgREGN = REV32(REGN) | 0x00001000,
        eIgNAVI = REV32(NAVI) | 0x00001000,
        eIgCELL = REV32(CELL) | 0x00001000,
        eIgWRLD = REV32(WRLD) | 0x00001000,
        eIgDIAL = REV32(DIAL) | 0x00001000,
        eIgQUST = REV32(QUST) | 0x00001000,
        eIgIDLE = REV32(IDLE) | 0x00001000,
        eIgPACK = REV32(PACK) | 0x00001000,
        eIgCSTY = REV32(CSTY) | 0x00001000,
        eIgLSCR = REV32(LSCR) | 0x00001000,
        eIgLVSP = REV32(LVSP) | 0x00001000,
        eIgANIO = REV32(ANIO) | 0x00001000,
        eIgWATR = REV32(WATR) | 0x00001000,
        eIgEFSH = REV32(EFSH) | 0x00001000,
        eIgEXPL = REV32(EXPL) | 0x00001000,
        eIgDEBR = REV32(DEBR) | 0x00001000,
        eIgIMGS = REV32(IMGS) | 0x00001000,
        eIgIMAD = REV32(IMAD) | 0x00001000,
        eIgFLST = REV32(FLST) | 0x00001000,
        eIgPERK = REV32(PERK) | 0x00001000,
        eIgBPTD = REV32(BPTD) | 0x00001000,
        eIgADDN = REV32(ADDN) | 0x00001000,
        eIgAVIF = REV32(AVIF) | 0x00001000,
        eIgCAMS = REV32(CAMS) | 0x00001000,
        eIgCPTH = REV32(CPTH) | 0x00001000,
        eIgVTYP = REV32(VTYP) | 0x00001000,
        eIgIPCT = REV32(IPCT) | 0x00001000,
        eIgIPDS = REV32(IPDS) | 0x00001000,
        eIgARMA = REV32(ARMA) | 0x00001000,
        eIgECZN = REV32(ECZN) | 0x00001000,
        eIgMESG = REV32(MESG) | 0x00001000,
        eIgRGDL = REV32(RGDL) | 0x00001000,
        eIgDOBJ = REV32(DOBJ) | 0x00001000,
        eIgLGTM = REV32(LGTM) | 0x00001000,
        eIgMUSC = REV32(MUSC) | 0x00001000,

        eIgKYWD = REV32(KYWD) | 0x00001000,
        eIgLCRT = REV32(LCRT) | 0x00001000,
        eIgAACT = REV32(AACT) | 0x00001000,
        eIgSCRL = REV32(CLDC) | 0x00001000,
        eIgCLDC = REV32(MUSC) | 0x00001000,
        eIgHAZD = REV32(HAZD) | 0x00001000,
        eIgSPGD = REV32(SPGD) | 0x00001000,
        eIgRFCT = REV32(MATT) | 0x00001000,
        eIgMATT = REV32(MUSC) | 0x00001000,
        eIgLCTN = REV32(LCTN) | 0x00001000,
        eIgFSTP = REV32(FSTP) | 0x00001000,
        eIgFSTS = REV32(FSTS) | 0x00001000,
        eIgSMBN = REV32(SMBN) | 0x00001000,
        eIgSMQN = REV32(SMQN) | 0x00001000,
        eIgSMEN = REV32(SMEN) | 0x00001000,
        eIgDLBR = REV32(DLBR) | 0x00001000,
        eIgMUST = REV32(MUST) | 0x00001000,
        eIgDLVW = REV32(DLVW) | 0x00001000,
        eIgWOOP = REV32(WOOP) | 0x00001000,
        eIgSHOU = REV32(SHOU) | 0x00001000,
        eIgEQUP = REV32(EQUP) | 0x00001000,
        eIgRELA = REV32(RELA) | 0x00001000,
        eIgSCEN = REV32(SCEN) | 0x00001000,
        eIgASTP = REV32(ASTP) | 0x00001000,
        eIgOTFT = REV32(OTFT) | 0x00001000,
        eIgARTO = REV32(ARTO) | 0x00001000,
        eIgMATO = REV32(MATO) | 0x00001000,
        eIgMOVT = REV32(MOVT) | 0x00001000,
        eIgSNDR = REV32(SNDR) | 0x00001000,
        eIgDUAL = REV32(DUAL) | 0x00001000,
        eIgSNCT = REV32(SNCT) | 0x00001000,
        eIgSOPM = REV32(SOPM) | 0x00001000,
        eIgCOLL = REV32(COLL) | 0x00001000,
        eIgCLFM = REV32(CLFM) | 0x00001000,
        eIgREVB = REV32(REVB) | 0x00001000,
    };

    if(Flags.IsNoLoad || Flags.IsCreateNew || !file_map.is_open() || Flags.LoadedGRUPs)
        {
        if(!(Flags.IsNoLoad || Flags.IsCreateNew))
            {
            if(!file_map.is_open())
                printer("TES5File::Load: Error - Unable to load mod \"%s\". The mod is not open.\n", ModName);
            else
                printer("TES5File::Load: Error - Unable to load mod \"%s\". The mod is already loaded.\n", ModName);
            }
        return 0;
        }

    // Load translation strings
    if (TES4.IsTurnOffFire())   // IsTurnOffFire == IsLookupStrings
    {
        if (LookupStrings == NULL)
        {
            LookupStrings = new StringLookups();
            LookupStrings->Open(FileName);
        }
    }

    Flags.LoadedGRUPs = true;
    unsigned char *group_buffer_end = NULL;
    UINT32 GRUPSize;
    UINT32 GRUPLabel;
    boost::unordered_set<UINT32> UsedFormIDs;

    RecordOp skip_parser;
    RecordOp &parser = Flags.IsFullLoad ? read_parser : skip_parser;

    RecordProcessor processor(this, FormIDHandler, Flags, UsedFormIDs);
    processor.SetFilter(filter_inclusive, filter_records, filter_wspaces);

    while(buffer_position < buffer_end){
        buffer_position += 4; //Skip "GRUP"
        GRUPSize = *(UINT32 *)buffer_position;
        group_buffer_end = buffer_position + GRUPSize - 4;
        buffer_position += 4;
        GRUPLabel = *(UINT32 *)buffer_position;
        buffer_position += 8; //Skip type (tops will all == 0)

        //printer("%c%c%c%c\n", ((char *)&GRUPLabel)[0], ((char *)&GRUPLabel)[1], ((char *)&GRUPLabel)[2], ((char *)&GRUPLabel)[3]);
        switch(GRUPLabel)
        {
          //case eIgLTEX: //Same as normal
            case REV32(LTEX):
                LTEX.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
          //case eIgTXST:
            case REV32(TXST): // EDID: VaerminaRobes
                TXST.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
          //case eIgMATT:
            case REV32(MATT): // EDID: MaterialInsect (new record-type)
                MATT.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgCELL:
            case REV32(CELL):
                CELL.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
          //case eIgWRLD: //Same as normal
            case REV32(WRLD): // EDID: Tamriel
                WRLD.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName, read_parser, CELL);
                break;

          //case eIgAACT:
            case REV32(AACT): // EDID: ActionRagdollInstant (new record-type)
                AACT.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;

          //case eIgASPC:  //Same as normal
            case REV32(ASPC): // EDID: ExtMQFlashbackInteriorAcousticSpace
                ASPC.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;

          //case eIgLVLN: //Same as normal
            case REV32(LVLN): // EDID: LCharDwarvenCenturion
                LVLN.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;

          //case eIgLVLI: //Same as normal
            case REV32(LVLI): // EDID: SublistEnchArmorShield06Dragonscale05
                LVLI.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;

          //case eIgLVSP:
            case REV32(LVSP): // EDID: LSpellDragonFrostBreath (Oblivion type)
                LVSP.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;

          //case eIgARTO:
            case REV32(ARTO): // EDID: FXDragonsBaneSwordStreakObject (new record-type)
                ARTO.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;

          //case eIgASTP:
            case REV32(ASTP): // EDID: FavorTarget (new record-type)
                ASTP.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;

          //case eIgAPPA:
            case REV32(APPA): // EDID: Grimoire05Master (Oblivion type)
                APPA.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;

            case eIgGMST:
            case REV32(GMST):

            case eIgGLOB:
            case REV32(GLOB): // EDID: DecapitationChance

            case eIgCLAS:
            case REV32(CLAS): // EDID: EncClassDremoraMelee

            case eIgFACT:
            case REV32(FACT): // EDID: WinterholdJailFaction

            case eIgHDPT:
            case REV32(HDPT): // EDID: HairFemaleImperial1

            case eIgHAIR:
            case REV32(HAIR): // EDID: ...

          //case eIgEYES:
            case REV32(EYES): // EDID: EyeKhajiitMale

            case eIgRACE:
            case REV32(RACE): // EDID: FoxRace

            case eIgSOUN:
            case REV32(SOUN): // EDID: OBJWindmillSolitudeLP

        case eIgMGEF:
        case REV32(MGEF): // EDID: BanishDmgHealthFFTargetActor
        case eIgSCPT:
        case REV32(SCPT): // EDID: ...
        case eIgENCH:
        case REV32(ENCH): // EDID: MGArchMageRobeHoodedEnchant
      //case eIgSPEL: //Same as normal
        case REV32(SPEL): // EDID: AbMG08AncanoMagicka
        case eIgACTI:
        case REV32(ACTI): // EDID: defaultBlankTrigger
        case eIgTACT:
        case REV32(TACT): // EDID: MGAugurTalkingActivator
      //case eIgARMO: //Same as normal
        case REV32(ARMO): // EDID: DremoraBoots
        case eIgBOOK:
        case REV32(BOOK): // EDID: SpellTomeConjureDremoraLord
        case eIgCONT:
        case REV32(CONT): // EDID: MerchantWhiterunEorlundChest
        case eIgDOOR:
        case REV32(DOOR): // EDID: dunTwilightSepulcherDoor
        case eIgINGR:
        case REV32(INGR): // EDID: CritterPondFish01Ingredient
        case eIgLIGH:
        case REV32(LIGH): // EDID: MagicVoiceDismay03
        case eIgMISC:
        case REV32(MISC): // EDID: MGRArniel04SoulGem
      //case eIgSTAT: //Same as normal
        case REV32(STAT): // EDID: LoadScreenMRaltar01
        case eIgSCOL:
        case REV32(SCOL): // EDID: ...
      //case eIgMSTT: //Same as normal
        case REV32(MSTT): // EDID: GallusFXBody01
      //case eIgPWAT: //Same as normal
        case REV32(PWAT): // EDID: ...
      //case eIgGRAS: //Same as normal
        case REV32(GRAS): // EDID: FieldGrass02
      //case eIgTREE: //Same as normal
        case REV32(TREE): // EDID: TreeReachTree01Winterhold
      //case eIgFURN: //Same as normal
        case REV32(FURN): // EDID: InvisibleChairMarkerFChild
        case eIgWEAP:
        case REV32(WEAP): // EDID: DA14DremoraGreatswordFire03
        case eIgAMMO:
        case REV32(AMMO): // EDID: DwarvenSphereBolt02
      //case eIgNPC_: //Same as normal
        case REV32(NPC_): // EDID: ...
        case eIgKEYM:
        case REV32(KEYM): // EDID: RiftenConfiscatedGoodsChestKey
        case eIgALCH:
        case REV32(ALCH): // EDID: FoodGourd
        case eIgIDLM:
        case REV32(IDLM): // EDID: TG00IdleSellMarker
        case eIgCOBJ:
        case REV32(COBJ): // EDID: TemperWeaponSkyforgeSteelWarAxe
      //case eIgPROJ: //Same as normal
        case REV32(PROJ): // EDID: VoiceDismayProjectile03
      //case eIgWTHR: //Same as normal
        case REV32(WTHR): // EDID: SovngardeDark
        case eIgCLMT:
        case REV32(CLMT): // EDID: KarthspireClimate
        case eIgREGN:
        case REV32(REGN): // EDID: SovngardeIntWeather
        case eIgNAVI:
        case REV32(NAVI): // EDID: ...
        case eIgDIAL:
        case REV32(DIAL): // EDID: ...
      //case eIgQUST: //Same as normal
        case REV32(QUST): // EDID: CreatureDialogueWerewolf
        case eIgIDLE:
        case REV32(IDLE): // EDID: ForceEquipWeaponsNotOut
        case eIgPACK:
        case REV32(PACK): // EDID: ThievesGuildSapphireSandboxMultiPackage0x0
      //case eIgCSTY: //Same as normal
        case REV32(CSTY): // EDID: DefaultCombatstyle
      //case eIgLSCR: //Same as normal
        case REV32(LSCR): // EDID: ChargenLoadScreen
        case eIgANIO:
        case REV32(ANIO): // EDID: AnimObjectIronSword
        case eIgWATR:
        case REV32(WATR): // EDID: DefaultWaterKatariahWorld
        case eIgEFSH:
        case REV32(EFSH): // EDID: InvisFXShaderNightingale
      //case eIgEXPL: //Same as normal
        case REV32(EXPL): // EDID: PowerSerpentStoneExplosion
        case eIgDEBR:
        case REV32(DEBR): // EDID: IceFormDebris14
        case eIgIMGS:
        case REV32(IMGS): // EDID: ISSovngardeDark
        case eIgIMAD:
        case REV32(IMAD): // EDID: ChargenImod
        case eIgFLST:
        case REV32(FLST): // EDID: CWMission07StewardVoiceTypes
        case eIgPERK:
        case REV32(PERK): // EDID: TGWellFitted
      //case eIgBPTD:
        case REV32(BPTD): // EDID: ChickenBodyPartData
        case eIgADDN:
        case REV32(ADDN): // EDID: MPSFrostMistSpiral
      //case eIgAVIF:
        case REV32(AVIF): // EDID: AVDragonSouls
        case eIgCAMS:
        case REV32(CAMS): // EDID: DS04aDragonKillCamA01L
      //case eIgCPTH:
        case REV32(CPTH): // EDID: DragonKillCam02Lmid
      //case eIgVTYP:
        case REV32(VTYP): // EDID: CrFoxVoice
      //case eIgIPCT:
        case REV32(IPCT): // EDID: MAGPowerSerpentStoneImpactImpact
      //case eIgIPDS:
        case REV32(IPDS): // EDID: MAGPowerSerpentStoneImpactImpactSet
      //case eIgARMA:
        case REV32(ARMA): // EDID: BoneCrownKhajiitAA
        case eIgECZN:
        case REV32(ECZN): // EDID: TowerOfMzarkZone
        case eIgMESG:
        case REV32(MESG): // EDID: HelpSprintLong
        case eIgRGDL:
        case REV32(RGDL): // EDID: ...
        case eIgDOBJ:
        case REV32(DOBJ): // EDID: ...
        case eIgLGTM:
        case REV32(LGTM): // EDID: GreenCaveCloseDark
      //case eIgMUSC:
        case REV32(MUSC): // EDID: MUSExploreSovngardeChantExterior

        case eIgFLOR:
        case REV32(FLOR): // EDID: DeadFXSalmon02 (Oblivion type)
        case eIgSLGM:
        case REV32(SLGM): // EDID: FFRiften14SoulGem (Oblivion type)

      //case eIgKYWD:
        case REV32(KYWD): // EDID: PowerAttackBash (new record-type)
        case eIgLCRT:
        case REV32(LCRT): // EDID: MapMarkerRefType (new record-type)
        case eIgSCRL:
        case REV32(SCRL): // EDID: MGR21ScrollMagicka (new record-type)
      //case eIgCLDC:
        case REV32(CLDC): // EDID: ... (new record-type)
        case eIgHAZD:
        case REV32(HAZD): // EDID: TrapFirePlateFXHaz06 (new record-type)
      //case eIgSPGD:
        case REV32(SPGD): // EDID: SovngardeStardust (new record-type)
        case eIgRFCT:
        case REV32(RFCT): // EDID: MGTeleportOutEffectNoRefraction (new record-type)
        case eIgLCTN:
        case REV32(LCTN): // EDID: RiftenMercerHouseInteriorLocation (new record-type)
      //case eIgFSTP:
        case REV32(FSTP): // EDID: NPCDragonFlightRoarPaarthurnaxFootstep (new record-type)
      //case eIgFSTS:
        case REV32(FSTS): // EDID: NPCDragonPaarthurnaxFootWalkFootstepSet (new record-type)
        case eIgSMBN:
        case REV32(SMBN): // EDID: SkyHavenTempleScenesNode (new record-type)
        case eIgSMQN:
        case REV32(SMQN): // EDID: SovngardeSparringNode (new record-type)
        case eIgSMEN:
        case REV32(SMEN): // EDID: ... (new record-type)
        case eIgDLBR:
        case REV32(DLBR): // EDID: WIAddItem03SayBranch (new record-type)
      //case eIgMUST:
        case REV32(MUST): // EDID: MUSCombatBoss03CG (new record-type)
        case eIgDLVW:
        case REV32(DLVW): // EDID: WIAddItem03VIew (new record-type)
        case eIgWOOP:
        case REV32(WOOP): // EDID: DragonFakeWord (new record-type)
        case eIgSHOU:
        case REV32(SHOU): // EDID: L_DragonFrostIceStormShout (new record-type)
      //case eIgEQUP:
        case REV32(EQUP): // EDID: ... (new record-type)
        case eIgRELA:
        case REV32(RELA): // EDID: IngeAtAfAlan (new record-type)
        case eIgSCEN:
        case REV32(SCEN): // EDID: MQSovngardeConv2SceneStarter (new record-type)
      //case eIgOTFT:
        case REV32(OTFT): // EDID: MQ101MagePrisonerOutfit (new record-type)
        case eIgMATO:
        case REV32(MATO): // EDID: SnowMaterialWinterhold (new record-type)
        case eIgMOVT:
        case REV32(MOVT): // EDID: Falmer_1HM_Run (new record-type)
        case eIgSNDR:
        case REV32(SNDR): // EDID: VOCShoutFXThrowVoice (new record-type)
      //case eIgDUAL:
        case REV32(DUAL): // EDID: doomSerpentDualCastData (new record-type)
        case eIgSNCT:
        case REV32(SNCT): // EDID: AudioCategoryFSTnpc (new record-type)
        case eIgSOPM:
        case REV32(SOPM): // EDID: SOMDialogue3D4000BARDS (new record-type)
        case eIgCOLL:
        case REV32(COLL): // EDID: L_TRAP_TRIGGER (new record-type)
        case eIgCLFM:
        case REV32(CLFM): // EDID: WoodElfSkinFemale05 (new record-type)
        case eIgREVB:
        case REV32(REVB): // EDID: IntRoomStoneLargeExtraReverb (new record-type)
          /*
            case eIgGMST:
            case REV32(GMST):
                GMST.Read(buffer_start, buffer_position, group_buffer_end, indexer, read_parser, DeletedRecords, processor, FileName);
        break;
            case eIgMICN:
            case REV32(MICN):
                MICN.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgGLOB:
            case REV32(GLOB):
                GLOB.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgCLAS:
            case REV32(CLAS):
                CLAS.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgFACT:
            case REV32(FACT):
                FACT.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgHDPT:
            case REV32(HDPT):
                HDPT.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgHAIR:
            case REV32(HAIR):
                HAIR.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgEYES: //Same as normal
            case REV32(EYES):
                EYES.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgRACE:
            case REV32(RACE):
                RACE.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgSOUN:
            case REV32(SOUN):
                SOUN.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgASPC:  //Same as normal
            case REV32(ASPC):
                ASPC.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgMGEF:
            case REV32(MGEF):
                MGEF.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgSCPT:
            case REV32(SCPT):
                SCPT.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgENCH:
            case REV32(ENCH):
                ENCH.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgSPEL: //Same as normal
            case REV32(SPEL):
                SPEL.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgACTI:
            case REV32(ACTI):
                ACTI.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgTACT:
            case REV32(TACT):
                TACT.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgTERM:
            case REV32(TERM):
                TERM.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgARMO: //Same as normal
            case REV32(ARMO):
                ARMO.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgBOOK:
            case REV32(BOOK):
                BOOK.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgCONT:
            case REV32(CONT):
                CONT.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgDOOR:
            case REV32(DOOR):
                DOOR.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgINGR:
            case REV32(INGR):
                INGR.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgLIGH:
            case REV32(LIGH):
                LIGH.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgMISC:
            case REV32(MISC):
                MISC.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgSTAT: //Same as normal
            case REV32(STAT):
                STAT.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgSCOL:
            case REV32(SCOL):
                SCOL.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgMSTT: //Same as normal
            case REV32(MSTT):
                MSTT.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgPWAT: //Same as normal
            case REV32(PWAT):
                PWAT.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgGRAS: //Same as normal
            case REV32(GRAS):
                GRAS.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgTREE: //Same as normal
            case REV32(TREE):
                TREE.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgFURN: //Same as normal
            case REV32(FURN):
                FURN.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgWEAP:
            case REV32(WEAP):
                WEAP.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgAMMO:
            case REV32(AMMO):
                AMMO.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgNPC_: //Same as normal
            case REV32(NPC_):
                NPC_.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgCREA: //Same as normal
            case REV32(CREA):
                CREA.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgLVLC: //Same as normal
            case REV32(LVLC):
                LVLC.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgLVLN: //Same as normal
            case REV32(LVLN):
                LVLN.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgKEYM:
            case REV32(KEYM):
                KEYM.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgALCH:
            case REV32(ALCH):
                ALCH.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgIDLM:
            case REV32(IDLM):
                IDLM.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgNOTE:
            case REV32(NOTE):
                NOTE.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgCOBJ:
            case REV32(COBJ):
                COBJ.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgPROJ: //Same as normal
            case REV32(PROJ):
                PROJ.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgLVLI: //Same as normal
            case REV32(LVLI):
                LVLI.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgWTHR: //Same as normal
            case REV32(WTHR):
                WTHR.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgCLMT:
            case REV32(CLMT):
                CLMT.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgREGN:
            case REV32(REGN):
                REGN.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgNAVI:
            case REV32(NAVI):
                NAVI.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgDIAL:
            case REV32(DIAL):
                DIAL.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgQUST: //Same as normal
            case REV32(QUST):
                QUST.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgIDLE:
            case REV32(IDLE):
                IDLE.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgPACK:
            case REV32(PACK):
                PACK.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgCSTY: //Same as normal
            case REV32(CSTY):
                CSTY.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgLSCR: //Same as normal
            case REV32(LSCR):
                LSCR.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgANIO:
            case REV32(ANIO):
                ANIO.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgWATR:
            case REV32(WATR):
                WATR.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgEFSH:
            case REV32(EFSH):
                EFSH.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgEXPL: //Same as normal
            case REV32(EXPL):
                EXPL.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgDEBR:
            case REV32(DEBR):
                DEBR.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgIMGS:
            case REV32(IMGS):
                //IMGS.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            case eIgIMAD:
            case REV32(IMAD):
                //IMAD.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            case eIgFLST:
            case REV32(FLST):
                //FLST.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            case eIgPERK:
            case REV32(PERK):
                //PERK.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            //case eIgBPTD: //Same as normal
            case REV32(BPTD):
                //BPTD.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            case eIgADDN:
            case REV32(ADDN):
                //ADDN.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            //case eIgAVIF: //Same as normal
            case REV32(AVIF):
                //AVIF.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            case eIgRADS:
            case REV32(RADS):
                //RADS.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            case eIgCAMS:
            case REV32(CAMS):
                //CAMS.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            //case eIgCPTH: //Same as normal
            case REV32(CPTH):
                //CPTH.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            //case eIgVTYP: //Same as normal
            case REV32(VTYP):
                //VTYP.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            //case eIgIPCT: //Same as normal
            case REV32(IPCT):
                //IPCT.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            //case eIgIPDS: //Same as normal
            case REV32(IPDS):
                //IPDS.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            //case eIgARMA: //Same as normal
            case REV32(ARMA):
                //ARMA.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            case eIgECZN:
            case REV32(ECZN):
                //ECZN.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            case eIgMESG:
            case REV32(MESG):
                //MESG.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            case eIgRGDL:
            case REV32(RGDL):
                //RGDL.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            case eIgDOBJ:
            case REV32(DOBJ):
                //DOBJ.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            case eIgLGTM:
            case REV32(LGTM):
                //LGTM.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            //case eIgMUSC: //Same as normal
            case REV32(MUSC):
                //MUSC.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            case eIgIMOD:
            case REV32(IMOD):
                //IMOD.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            case eIgREPU:
            case REV32(REPU):
                //REPU.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            case eIgRCPE:
            case REV32(RCPE):
                //RCPE.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            case eIgRCCT:
            case REV32(RCCT):
                //RCCT.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            case eIgCHIP:
            case REV32(CHIP):
                //CHIP.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            //case eIgCSNO: //Same as normal
            case REV32(CSNO):
                //CSNO.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            //case eIgLSCT: //Same as normal
            case REV32(LSCT):
                //LSCT.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            //case eIgMSET: //Same as normal
            case REV32(MSET):
                //MSET.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            case eIgALOC:
            case REV32(ALOC):
                //ALOC.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            case eIgCHAL:
            case REV32(CHAL):
                //CHAL.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            case eIgAMEF:
            case REV32(AMEF):
                //AMEF.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            case eIgCCRD:
            case REV32(CCRD):
                //CCRD.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            case eIgCMNY:
            case REV32(CMNY):
                //CMNY.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            case eIgCDCK:
            case REV32(CDCK):
                //CDCK.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            case eIgDEHY:
            case REV32(DEHY):
                //DEHY.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            //case eIgHUNG: //Same as normal
            case REV32(HUNG):
                //HUNG.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            case eIgSLPD:
            case REV32(SLPD):
                //SLPD.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
        */
        if(GRUPLabel == 0 && GRUPSize == 0)
            {
            printer("TES5File::Read: Warning - Unknown record group (%c%c%c%c) encountered in mod \"%s\". Bad file structure, zeros found past end of groups.\n", ((STRING)&GRUPLabel)[0], ((STRING)&GRUPLabel)[1], ((STRING)&GRUPLabel)[2], ((STRING)&GRUPLabel)[3], ModName);
            return 1;
            }
        //else
        //    printer("TES5File::Read: Error - Unknown record group (%c%c%c%c) encountered in mod \"%s\". ", ((STRING)&GRUPLabel)[0], ((STRING)&GRUPLabel)[1], ((STRING)&GRUPLabel)[2], ((STRING)&GRUPLabel)[3], ModName);

        if(GRUPSize == 0)
            {
            printer("Unable to continue loading.\n");
            return 1;
            }
        else
            {
            //printer("Attempting to skip and continue loading.\n");
            buffer_position = group_buffer_end;
            }
        break;
            default:
                if(GRUPLabel == 0 && GRUPSize == 0)
                    {
                    printer("TES5File::Read: Warning - Unknown record group (%c%c%c%c) encountered in mod \"%s\". Bad file structure, zeros found past end of groups.\n", ((STRING)&GRUPLabel)[0], ((STRING)&GRUPLabel)[1], ((STRING)&GRUPLabel)[2], ((STRING)&GRUPLabel)[3], ModName);
                    return 1;
                    }
                //else
                //    printer("TES5File::Read: Error - Unknown record group (%c%c%c%c) encountered in mod \"%s\". ", ((STRING)&GRUPLabel)[0], ((STRING)&GRUPLabel)[1], ((STRING)&GRUPLabel)[2], ((STRING)&GRUPLabel)[3], ModName);

                if(GRUPSize == 0)
                    {
                    printer("Unable to continue loading.\n");
                    return 1;
                    }
                else
                    {
                    //printer("Attempting to skip and continue loading.\n");
                    buffer_position = group_buffer_end;
                    }
                break;
            }
        };

    FormIDHandler.IsEmpty = UsedFormIDs.empty();
    //Testing snippet
    //if(Flags.IsFullLoad)
    //    {
    //    RecordChanger changer(FormIDHandler, Expanders);
    //    VisitAllRecords(changer);
    //    }
    return 1;
    }

UINT32 TES5File::GetNumRecords(const UINT32 &RecordType)
    {
    switch(RecordType)
    {
    case REV32(LTEX):
        return (UINT32)LTEX.pool.used_object_capacity();
        case REV32(TXST):
            return (UINT32)TXST.pool.used_object_capacity();
        case REV32(MATT):
            return (UINT32)MATT.pool.used_object_capacity();
    case REV32(CELL):
        return (UINT32)CELL.cell_pool.used_object_capacity();
    case REV32(LAND):
        return (UINT32)WRLD.land_pool.used_object_capacity();
    case REV32(WCEL):
        return (UINT32)WRLD.cell_pool.used_object_capacity();
    ///////////////////////////////////////////////
    case REV32(CLLS):
        return (UINT32)CELL.cell_pool.used_object_capacity() +
           (UINT32)WRLD.cell_pool.used_object_capacity();
    ///////////////////////////////////////////////
    case REV32(WRLD):
        return (UINT32)WRLD.wrld_pool.used_object_capacity();
      /*
        case REV32(GMST):
            return (UINT32)GMST.pool.used_object_capacity();
        case REV32(MICN):
            return (UINT32)MICN.pool.used_object_capacity();
        case REV32(GLOB):
            return (UINT32)GLOB.pool.used_object_capacity();
        case REV32(CLAS):
            return (UINT32)CLAS.pool.used_object_capacity();
        case REV32(FACT):
            return (UINT32)FACT.pool.used_object_capacity();
        case REV32(HDPT):
            return (UINT32)HDPT.pool.used_object_capacity();
        case REV32(HAIR):
            return (UINT32)HAIR.pool.used_object_capacity();
        case REV32(EYES):
            return (UINT32)EYES.pool.used_object_capacity();
        case REV32(RACE):
            return (UINT32)RACE.pool.used_object_capacity();
        case REV32(SOUN):
            return (UINT32)SOUN.pool.used_object_capacity();
        case REV32(ASPC):
            return (UINT32)ASPC.pool.used_object_capacity();
        case REV32(MGEF):
            return (UINT32)MGEF.pool.used_object_capacity();
        case REV32(SCPT):
            return (UINT32)SCPT.pool.used_object_capacity();
        case REV32(ENCH):
            return (UINT32)ENCH.pool.used_object_capacity();
        case REV32(SPEL):
            return (UINT32)SPEL.pool.used_object_capacity();
        case REV32(ACTI):
            return (UINT32)ACTI.pool.used_object_capacity();
        case REV32(TACT):
            return (UINT32)TACT.pool.used_object_capacity();
        case REV32(TERM):
            return (UINT32)TERM.pool.used_object_capacity();
        case REV32(ARMO):
            return (UINT32)ARMO.pool.used_object_capacity();
        case REV32(BOOK):
            return (UINT32)BOOK.pool.used_object_capacity();
        case REV32(CONT):
            return (UINT32)CONT.pool.used_object_capacity();
        case REV32(DOOR):
            return (UINT32)DOOR.pool.used_object_capacity();
        case REV32(INGR):
            return (UINT32)INGR.pool.used_object_capacity();
        case REV32(LIGH):
            return (UINT32)LIGH.pool.used_object_capacity();
        case REV32(MISC):
            return (UINT32)MISC.pool.used_object_capacity();
        case REV32(STAT):
            return (UINT32)STAT.pool.used_object_capacity();
        case REV32(SCOL):
            return (UINT32)SCOL.pool.used_object_capacity();
        case REV32(MSTT):
            return (UINT32)MSTT.pool.used_object_capacity();
        case REV32(PWAT):
            return (UINT32)PWAT.pool.used_object_capacity();
        case REV32(GRAS):
            return (UINT32)GRAS.pool.used_object_capacity();
        case REV32(TREE):
            return (UINT32)TREE.pool.used_object_capacity();
        case REV32(FURN):
            return (UINT32)FURN.pool.used_object_capacity();
        case REV32(WEAP):
            return (UINT32)WEAP.pool.used_object_capacity();
        case REV32(AMMO):
            return (UINT32)AMMO.pool.used_object_capacity();
        case REV32(NPC_):
            return (UINT32)NPC_.pool.used_object_capacity();
        case REV32(CREA):
            return (UINT32)CREA.pool.used_object_capacity();
        case REV32(LVLC):
            return (UINT32)LVLC.pool.used_object_capacity();
        case REV32(LVLN):
            return (UINT32)LVLN.pool.used_object_capacity();
        case REV32(KEYM):
            return (UINT32)KEYM.pool.used_object_capacity();
        case REV32(ALCH):
            return (UINT32)ALCH.pool.used_object_capacity();
        case REV32(IDLM):
            return (UINT32)IDLM.pool.used_object_capacity();
        case REV32(NOTE):
            return (UINT32)NOTE.pool.used_object_capacity();
        case REV32(COBJ):
            return (UINT32)COBJ.pool.used_object_capacity();
        case REV32(PROJ):
            return (UINT32)PROJ.pool.used_object_capacity();
        case REV32(LVLI):
            return (UINT32)LVLI.pool.used_object_capacity();
        case REV32(WTHR):
            return (UINT32)WTHR.pool.used_object_capacity();
        case REV32(CLMT):
            return (UINT32)CLMT.pool.used_object_capacity();
        case REV32(REGN):
            return (UINT32)REGN.pool.used_object_capacity();
        case REV32(NAVI):
            return (UINT32)NAVI.pool.used_object_capacity();
        ///////////////////////////////////////////////
        //These return the absolute total number of these SubRecords
        //Use the GetFieldAttribute API instead if you want the number
        // of SubRecords associated with a specific parent record
        case REV32(INFO):
            return (UINT32)DIAL.info_pool.used_object_capacity();
        case REV32(ACHR):
            return (UINT32)CELL.achr_pool.used_object_capacity();
        case REV32(ACRE):
            return (UINT32)CELL.acre_pool.used_object_capacity();
        case REV32(REFR):
            return (UINT32)CELL.refr_pool.used_object_capacity();
        case REV32(PGRE):
            return (UINT32)CELL.pgre_pool.used_object_capacity();
        case REV32(PMIS):
            return (UINT32)CELL.pmis_pool.used_object_capacity();
        case REV32(PBEA):
            return (UINT32)CELL.pbea_pool.used_object_capacity();
        case REV32(PFLA):
            return (UINT32)CELL.pfla_pool.used_object_capacity();
        case REV32(PCBE):
            return (UINT32)CELL.pcbe_pool.used_object_capacity();
        case REV32(NAVM):
            return (UINT32)CELL.navm_pool.used_object_capacity();
        ///////////////////////////////////////////////
        case REV32(DIAL):
            return (UINT32)DIAL.dial_pool.used_object_capacity();
        case REV32(QUST):
            return (UINT32)QUST.pool.used_object_capacity();
        case REV32(IDLE):
            return (UINT32)IDLE.pool.used_object_capacity();
        case REV32(PACK):
            return (UINT32)PACK.pool.used_object_capacity();
        case REV32(CSTY):
            return (UINT32)CSTY.pool.used_object_capacity();
        case REV32(LSCR):
            return (UINT32)LSCR.pool.used_object_capacity();
        case REV32(ANIO):
            return (UINT32)ANIO.pool.used_object_capacity();
        case REV32(WATR):
            return (UINT32)WATR.pool.used_object_capacity();
        case REV32(EFSH):
            return (UINT32)EFSH.pool.used_object_capacity();
        case REV32(EXPL):
            return (UINT32)EXPL.pool.used_object_capacity();
        case REV32(DEBR):
            return (UINT32)DEBR.pool.used_object_capacity();
        case REV32(IMGS):
            //return (UINT32)IMGS.pool.used_object_capacity();
        case REV32(IMAD):
            //return (UINT32)IMAD.pool.used_object_capacity();
        case REV32(FLST):
            //return (UINT32)FLST.pool.used_object_capacity();
        case REV32(PERK):
            //return (UINT32)PERK.pool.used_object_capacity();
        case REV32(BPTD):
            //return (UINT32)BPTD.pool.used_object_capacity();
        case REV32(ADDN):
            //return (UINT32)ADDN.pool.used_object_capacity();
        case REV32(AVIF):
            //return (UINT32)AVIF.pool.used_object_capacity();
        case REV32(RADS):
            //return (UINT32)RADS.pool.used_object_capacity();
        case REV32(CAMS):
            //return (UINT32)CAMS.pool.used_object_capacity();
        case REV32(CPTH):
            //return (UINT32)CPTH.pool.used_object_capacity();
        case REV32(VTYP):
            //return (UINT32)VTYP.pool.used_object_capacity();
        case REV32(IPCT):
            //return (UINT32)IPCT.pool.used_object_capacity();
        case REV32(IPDS):
            //return (UINT32)IPDS.pool.used_object_capacity();
        case REV32(ARMA):
            //return (UINT32)ARMA.pool.used_object_capacity();
        case REV32(ECZN):
            //return (UINT32)ECZN.pool.used_object_capacity();
        case REV32(MESG):
            //return (UINT32)MESG.pool.used_object_capacity();
        case REV32(RGDL):
            //return (UINT32)RGDL.pool.used_object_capacity();
        case REV32(DOBJ):
            //return (UINT32)DOBJ.pool.used_object_capacity();
        case REV32(LGTM):
            //return (UINT32)LGTM.pool.used_object_capacity();
        case REV32(MUSC):
            //return (UINT32)MUSC.pool.used_object_capacity();
        case REV32(IMOD):
            //return (UINT32)IMOD.pool.used_object_capacity();
        case REV32(REPU):
            //return (UINT32)REPU.pool.used_object_capacity();
        case REV32(RCPE):
            //return (UINT32)RCPE.pool.used_object_capacity();
        case REV32(RCCT):
            //return (UINT32)RCCT.pool.used_object_capacity();
        case REV32(CHIP):
            //return (UINT32)CHIP.pool.used_object_capacity();
        case REV32(CSNO):
            //return (UINT32)CSNO.pool.used_object_capacity();
        case REV32(LSCT):
            //return (UINT32)LSCT.pool.used_object_capacity();
        case REV32(MSET):
            //return (UINT32)MSET.pool.used_object_capacity();
        case REV32(ALOC):
            //return (UINT32)ALOC.pool.used_object_capacity();
        case REV32(CHAL):
            //return (UINT32)CHAL.pool.used_object_capacity();
        case REV32(AMEF):
            //return (UINT32)AMEF.pool.used_object_capacity();
        case REV32(CCRD):
            //return (UINT32)CCRD.pool.used_object_capacity();
        case REV32(CMNY):
            //return (UINT32)CMNY.pool.used_object_capacity();
        case REV32(CDCK):
            //return (UINT32)CDCK.pool.used_object_capacity();
        case REV32(DEHY):
            //return (UINT32)DEHY.pool.used_object_capacity();
        case REV32(HUNG):
            //return (UINT32)HUNG.pool.used_object_capacity();
        case REV32(SLPD):
            //return (UINT32)SLPD.pool.used_object_capacity();
        */
        default:
            printer("TES5File::GetNumRecords: Warning - Unable to count records (%c%c%c%c) in mod \"%s\". Unrecognized record type.\n", ((STRING)&RecordType)[0], ((STRING)&RecordType)[1], ((STRING)&RecordType)[2], ((STRING)&RecordType)[3], ModName);
            break;
        }
    return 0;
    }

Record * TES5File::CreateRecord(const UINT32 &RecordType, STRING const &RecordEditorID, Record *&SourceRecord, Record *&ParentRecord, CreationFlags &options)
    {
    if(Flags.IsNoLoad)
        {
        printer("TES5File::CreateRecord: Error - Unable to create any records in mod \"%s\". The mod is flagged not to be loaded.\n", ModName);
        return NULL;
        }

    Record *newRecord = NULL;

    switch(RecordType)
    {
    case REV32(LTEX):
        return LTEX.pool.construct(SourceRecord, this, true);
        case REV32(TXST):
            return TXST.pool.construct(SourceRecord, this, true);
        case REV32(MATT):
            return MATT.pool.construct(SourceRecord, this, true);
    case REV32(WCEL):
        if(ParentRecord == NULL || ParentRecord->GetType() != REV32(WRLD))
        {
          printer("TES5File::CreateRecord: Error - Unable to create world CELL record in mod \"%s\". Parent record type (%s) is invalid, only WRLD records can be world CELL parents.\n", ModName, ParentRecord->GetStrType());
          return NULL;
        }

        //If a world cell already exists, return it instead of making a new one
        if(((Sk::WRLDRecord *)ParentRecord)->CELL != NULL)
        {
          options.ExistingReturned = true;
          return ((Sk::WRLDRecord *)ParentRecord)->CELL;
        }

        ((Sk::WRLDRecord *)ParentRecord)->CELL = WRLD.cell_pool.construct(SourceRecord, ParentRecord, false);
        ((Sk::CELLRecord *)((Sk::WRLDRecord *)ParentRecord)->CELL)->IsInterior(false);
        return ((Sk::WRLDRecord *)ParentRecord)->CELL;
    case REV32(CELL):
        if(ParentRecord == NULL)
        {
          newRecord = CELL.cell_pool.construct(SourceRecord, this, true);
          ((Sk::CELLRecord *)newRecord)->IsInterior(true);
          return newRecord;
        }
        else
        {
          if(ParentRecord->GetType() != REV32(WRLD))
          {
        printer("TES5File::CreateRecord: Error - Unable to create CELL record in mod \"%s\". Parent record type (%s) is invalid, only WRLD records can be CELL parents.\n", ModName, ParentRecord->GetStrType());
        return NULL;
          }

          //If the SourceRecord is a world cell, then the copy will be a world cell
          if(SourceRecord != NULL && ((Sk::WRLDRecord *)((Sk::CELLRecord *)SourceRecord)->GetParentRecord())->CELL == SourceRecord)
          {
        //If a world cell already exists, return it instead of making a new one
        if(((Sk::WRLDRecord *)ParentRecord)->CELL != NULL)
        {
          options.ExistingReturned = true;
          return ((Sk::WRLDRecord *)ParentRecord)->CELL;
        }

        newRecord = ((Sk::WRLDRecord *)ParentRecord)->CELL = WRLD.cell_pool.construct(SourceRecord, ParentRecord, false);
          }
          else
          {
        newRecord = WRLD.cell_pool.construct(SourceRecord, ParentRecord, false);
        ((Sk::WRLDRecord *)ParentRecord)->CELLS.push_back(newRecord);
          }

          ((Sk::CELLRecord *)newRecord)->IsInterior(false);
          return newRecord;
        }
    case REV32(WRLD):
        return WRLD.wrld_pool.construct(SourceRecord, this, true);
    case REV32(LAND):
        if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
        {
          printer("TES5File::CreateRecord: Error - Unable to create LAND record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be LAND parents.\n", ModName, ParentRecord->GetStrType());
          return NULL;
        }

        //If a cell land already exists, return it instead of making a new one
        if(((Sk::CELLRecord *)ParentRecord)->LAND != NULL)
        {
          options.ExistingReturned = true;
          return ((Sk::CELLRecord *)ParentRecord)->LAND;
        }

        ((Sk::CELLRecord *)ParentRecord)->LAND = WRLD.land_pool.construct(SourceRecord, ParentRecord, false);
        return ((Sk::CELLRecord *)ParentRecord)->LAND;

      /*
        case REV32(GMST):
            if(RecordEditorID == NULL && SourceRecord == NULL)
                {
                printer("TES5File::CreateRecord: Error - Unable to create GMST record in mod \"%s\". No valid editorID is available.\n", ModName);
                return NULL;
                }
            newRecord = GMST.pool.construct(SourceRecord, this, true);

            if(RecordEditorID != NULL)
                {
                ((Sk::GMSTRecord *)newRecord)->EDID.Copy(RecordEditorID);
                ((Sk::GMSTRecord *)newRecord)->DATA.format = ((Sk::GMSTRecord *)newRecord)->EDID.value[0];
                }
        break;
        case REV32(MICN):
            return MICN.pool.construct(SourceRecord, this, true);
        case REV32(GLOB):
            return GLOB.pool.construct(SourceRecord, this, true);
        case REV32(CLAS):
            return CLAS.pool.construct(SourceRecord, this, true);
        case REV32(FACT):
            return FACT.pool.construct(SourceRecord, this, true);
        case REV32(HDPT):
            return HDPT.pool.construct(SourceRecord, this, true);
        case REV32(HAIR):
            return HAIR.pool.construct(SourceRecord, this, true);
        case REV32(EYES):
            return EYES.pool.construct(SourceRecord, this, true);
        case REV32(RACE):
            return RACE.pool.construct(SourceRecord, this, true);
        case REV32(SOUN):
            return SOUN.pool.construct(SourceRecord, this, true);
        case REV32(ASPC):
            return ASPC.pool.construct(SourceRecord, this, true);
        case REV32(MGEF):
            return MGEF.pool.construct(SourceRecord, this, true);
        case REV32(SCPT):
            return SCPT.pool.construct(SourceRecord, this, true);
        case REV32(ENCH):
            return ENCH.pool.construct(SourceRecord, this, true);
        case REV32(SPEL):
            return SPEL.pool.construct(SourceRecord, this, true);
        case REV32(ACTI):
            return ACTI.pool.construct(SourceRecord, this, true);
        case REV32(TACT):
            return TACT.pool.construct(SourceRecord, this, true);
        case REV32(TERM):
            return TERM.pool.construct(SourceRecord, this, true);
        case REV32(ARMO):
            return ARMO.pool.construct(SourceRecord, this, true);
        case REV32(BOOK):
            return BOOK.pool.construct(SourceRecord, this, true);
        case REV32(CONT):
            return CONT.pool.construct(SourceRecord, this, true);
        case REV32(DOOR):
            return DOOR.pool.construct(SourceRecord, this, true);
        case REV32(INGR):
            return INGR.pool.construct(SourceRecord, this, true);
        case REV32(LIGH):
            return LIGH.pool.construct(SourceRecord, this, true);
        case REV32(MISC):
            return MISC.pool.construct(SourceRecord, this, true);
        case REV32(STAT):
            return STAT.pool.construct(SourceRecord, this, true);
        case REV32(SCOL):
            return SCOL.pool.construct(SourceRecord, this, true);
        case REV32(MSTT):
            return MSTT.pool.construct(SourceRecord, this, true);
        case REV32(PWAT):
            return PWAT.pool.construct(SourceRecord, this, true);
        case REV32(GRAS):
            return GRAS.pool.construct(SourceRecord, this, true);
        case REV32(TREE):
            return TREE.pool.construct(SourceRecord, this, true);
        case REV32(FURN):
            return FURN.pool.construct(SourceRecord, this, true);
        case REV32(WEAP):
            return WEAP.pool.construct(SourceRecord, this, true);
        case REV32(AMMO):
            return AMMO.pool.construct(SourceRecord, this, true);
        case REV32(NPC_):
            return NPC_.pool.construct(SourceRecord, this, true);
        case REV32(CREA):
            return CREA.pool.construct(SourceRecord, this, true);
        case REV32(LVLC):
            return LVLC.pool.construct(SourceRecord, this, true);
        case REV32(LVLN):
            return LVLN.pool.construct(SourceRecord, this, true);
        case REV32(KEYM):
            return KEYM.pool.construct(SourceRecord, this, true);
        case REV32(ALCH):
            return ALCH.pool.construct(SourceRecord, this, true);
        case REV32(IDLM):
            return IDLM.pool.construct(SourceRecord, this, true);
        case REV32(NOTE):
            return NOTE.pool.construct(SourceRecord, this, true);
        case REV32(COBJ):
            return COBJ.pool.construct(SourceRecord, this, true);
        case REV32(PROJ):
            return PROJ.pool.construct(SourceRecord, this, true);
        case REV32(LVLI):
            return LVLI.pool.construct(SourceRecord, this, true);
        case REV32(WTHR):
            return WTHR.pool.construct(SourceRecord, this, true);
        case REV32(CLMT):
            return CLMT.pool.construct(SourceRecord, this, true);
        case REV32(REGN):
            return REGN.pool.construct(SourceRecord, this, true);
        case REV32(NAVI):
            return NAVI.pool.construct(SourceRecord, this, true);
        case REV32(DIAL):
            return DIAL.dial_pool.construct(SourceRecord, this, true);
        case REV32(INFO):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(DIAL))
                {
                printer("TES5File::CreateRecord: Error - Unable to create INFO record in mod \"%s\". Parent record type (%s) is invalid, only DIAL records can be INFO parents.\n", ModName, ParentRecord->GetStrType());
                return NULL;
                }

            ((Sk::DIALRecord *)ParentRecord)->INFO.push_back(DIAL.info_pool.construct(SourceRecord, ParentRecord, false));
            return ((Sk::DIALRecord *)ParentRecord)->INFO.back();
        case REV32(ACHR):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
                {
                printer("TES5File::CreateRecord: Error - Unable to create ACHR record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be ACHR parents.\n", ModName, ParentRecord->GetStrType());
                return NULL;
                }

            ((Sk::CELLRecord *)ParentRecord)->ACHR.push_back(CELL.achr_pool.construct(SourceRecord, ParentRecord, false));
            return ((Sk::CELLRecord *)ParentRecord)->ACHR.back();
        case REV32(ACRE):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
                {
                printer("TES5File::CreateRecord: Error - Unable to create ACRE record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be ACRE parents.\n", ModName, ParentRecord->GetStrType());
                return NULL;
                }

            ((Sk::CELLRecord *)ParentRecord)->ACRE.push_back(CELL.acre_pool.construct(SourceRecord, ParentRecord, false));
            return ((Sk::CELLRecord *)ParentRecord)->ACRE.back();
        case REV32(REFR):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
                {
                printer("TES5File::CreateRecord: Error - Unable to create REFR record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be REFR parents.\n", ModName, ParentRecord->GetStrType());
                return NULL;
                }

            ((Sk::CELLRecord *)ParentRecord)->REFR.push_back(CELL.refr_pool.construct(SourceRecord, ParentRecord, false));
            return ((Sk::CELLRecord *)ParentRecord)->REFR.back();
        case REV32(PGRE):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
                {
                printer("TES5File::CreateRecord: Error - Unable to create PGRE record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be REFR parents.\n", ModName, ParentRecord->GetStrType());
                return NULL;
                }

            ((Sk::CELLRecord *)ParentRecord)->PGRE.push_back(CELL.pgre_pool.construct(SourceRecord, ParentRecord, false));
            return ((Sk::CELLRecord *)ParentRecord)->PGRE.back();
        case REV32(PMIS):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
                {
                printer("TES5File::CreateRecord: Error - Unable to create PMIS record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be REFR parents.\n", ModName, ParentRecord->GetStrType());
                return NULL;
                }

            ((Sk::CELLRecord *)ParentRecord)->PMIS.push_back(CELL.pmis_pool.construct(SourceRecord, ParentRecord, false));
            return ((Sk::CELLRecord *)ParentRecord)->PMIS.back();
        case REV32(PBEA):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
                {
                printer("TES5File::CreateRecord: Error - Unable to create PBEA record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be REFR parents.\n", ModName, ParentRecord->GetStrType());
                return NULL;
                }

            ((Sk::CELLRecord *)ParentRecord)->PBEA.push_back(CELL.pbea_pool.construct(SourceRecord, ParentRecord, false));
            return ((Sk::CELLRecord *)ParentRecord)->PBEA.back();
        case REV32(PFLA):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
                {
                printer("TES5File::CreateRecord: Error - Unable to create PFLA record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be REFR parents.\n", ModName, ParentRecord->GetStrType());
                return NULL;
                }

            ((Sk::CELLRecord *)ParentRecord)->PFLA.push_back(CELL.pfla_pool.construct(SourceRecord, ParentRecord, false));
            return ((Sk::CELLRecord *)ParentRecord)->PFLA.back();
        case REV32(PCBE):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
                {
                printer("TES5File::CreateRecord: Error - Unable to create PCBE record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be REFR parents.\n", ModName, ParentRecord->GetStrType());
                return NULL;
                }

            ((Sk::CELLRecord *)ParentRecord)->PCBE.push_back(CELL.pcbe_pool.construct(SourceRecord, ParentRecord, false));
            return ((Sk::CELLRecord *)ParentRecord)->PCBE.back();
        case REV32(NAVM):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
                {
                printer("TES5File::CreateRecord: Error - Unable to create NAVM record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be REFR parents.\n", ModName, ParentRecord->GetStrType());
                return NULL;
                }

            ((Sk::CELLRecord *)ParentRecord)->NAVM.push_back(CELL.navm_pool.construct(SourceRecord, ParentRecord, false));
            return ((Sk::CELLRecord *)ParentRecord)->NAVM.back();
        case REV32(QUST):
            return QUST.pool.construct(SourceRecord, this, true);
        case REV32(IDLE):
            return IDLE.pool.construct(SourceRecord, this, true);
        case REV32(PACK):
            return PACK.pool.construct(SourceRecord, this, true);
        case REV32(CSTY):
            return CSTY.pool.construct(SourceRecord, this, true);
        case REV32(LSCR):
            return LSCR.pool.construct(SourceRecord, this, true);
        case REV32(ANIO):
            return ANIO.pool.construct(SourceRecord, this, true);
        case REV32(WATR):
            return WATR.pool.construct(SourceRecord, this, true);
        case REV32(EFSH):
            return EFSH.pool.construct(SourceRecord, this, true);
        case REV32(EXPL):
            return EXPL.pool.construct(SourceRecord, this, true);
        case REV32(DEBR):
            return DEBR.pool.construct(SourceRecord, this, true);
        case REV32(IMGS):
            //return IMGS.pool.construct(SourceRecord, this, true);
        case REV32(IMAD):
            //return IMAD.pool.construct(SourceRecord, this, true);
        case REV32(FLST):
            //return FLST.pool.construct(SourceRecord, this, true);
        case REV32(PERK):
            //return PERK.pool.construct(SourceRecord, this, true);
        case REV32(BPTD):
            //return BPTD.pool.construct(SourceRecord, this, true);
        case REV32(ADDN):
            //return ADDN.pool.construct(SourceRecord, this, true);
        case REV32(AVIF):
            //return AVIF.pool.construct(SourceRecord, this, true);
        case REV32(RADS):
            //return RADS.pool.construct(SourceRecord, this, true);
        case REV32(CAMS):
            //return CAMS.pool.construct(SourceRecord, this, true);
        case REV32(CPTH):
            //return CPTH.pool.construct(SourceRecord, this, true);
        case REV32(VTYP):
            //return VTYP.pool.construct(SourceRecord, this, true);
        case REV32(IPCT):
            //return IPCT.pool.construct(SourceRecord, this, true);
        case REV32(IPDS):
            //return IPDS.pool.construct(SourceRecord, this, true);
        case REV32(ARMA):
            //return ARMA.pool.construct(SourceRecord, this, true);
        case REV32(ECZN):
            //return ECZN.pool.construct(SourceRecord, this, true);
        case REV32(MESG):
            //return MESG.pool.construct(SourceRecord, this, true);
        case REV32(RGDL):
            //return RGDL.pool.construct(SourceRecord, this, true);
        case REV32(DOBJ):
            //return DOBJ.pool.construct(SourceRecord, this, true);
        case REV32(LGTM):
            //return LGTM.pool.construct(SourceRecord, this, true);
        case REV32(MUSC):
            //return MUSC.pool.construct(SourceRecord, this, true);
        case REV32(IMOD):
            //return IMOD.pool.construct(SourceRecord, this, true);
        case REV32(REPU):
            //return REPU.pool.construct(SourceRecord, this, true);
        case REV32(RCPE):
            //return RCPE.pool.construct(SourceRecord, this, true);
        case REV32(RCCT):
            //return RCCT.pool.construct(SourceRecord, this, true);
        case REV32(CHIP):
            //return CHIP.pool.construct(SourceRecord, this, true);
        case REV32(CSNO):
            //return CSNO.pool.construct(SourceRecord, this, true);
        case REV32(LSCT):
            //return LSCT.pool.construct(SourceRecord, this, true);
        case REV32(MSET):
            //return MSET.pool.construct(SourceRecord, this, true);
        case REV32(ALOC):
            //return ALOC.pool.construct(SourceRecord, this, true);
        case REV32(CHAL):
            //return CHAL.pool.construct(SourceRecord, this, true);
        case REV32(AMEF):
            //return AMEF.pool.construct(SourceRecord, this, true);
        case REV32(CCRD):
            //return CCRD.pool.construct(SourceRecord, this, true);
        case REV32(CMNY):
            //return CMNY.pool.construct(SourceRecord, this, true);
        case REV32(CDCK):
            //return CDCK.pool.construct(SourceRecord, this, true);
        case REV32(DEHY):
            //return DEHY.pool.construct(SourceRecord, this, true);
        case REV32(HUNG):
            //return HUNG.pool.construct(SourceRecord, this, true);
        case REV32(SLPD):
            //return SLPD.pool.construct(SourceRecord, this, true);
        */
        default:
            printer("TES5File::CreateRecord: Error - Unable to create (%c%c%c%c) record in mod \"%s\". Unknown record type.\n", ((STRING)&RecordType)[0], ((STRING)&RecordType)[1], ((STRING)&RecordType)[2], ((STRING)&RecordType)[3], ModName);
            break;
        }
    return newRecord;
    }

SINT32 TES5File::DeleteRecord(Record *&curRecord, RecordOp &deindexer)
    {
    switch(curRecord->GetType())
    {
    case REV32(LTEX):
        deindexer.Accept(curRecord);
        LTEX.pool.destroy(curRecord);
        return 1;
        case REV32(TXST):
            deindexer.Accept(curRecord);
            TXST.pool.destroy(curRecord);
            return 1;
        case REV32(MATT):
            deindexer.Accept(curRecord);
            MATT.pool.destroy(curRecord);
            return 1;
    case REV32(CELL):
        {
          Sk::WRLDRecord *wrld_record = (Sk::WRLDRecord *)curRecord->GetParentRecord();
          bool cell_found = false;
          if(wrld_record != NULL)
          {
        if(wrld_record->CELL == curRecord)
        {
          wrld_record->CELL = NULL;
          cell_found = true;
        }
        else
        {
          for(UINT32 ListIndex = 0; ListIndex < wrld_record->CELLS.size(); ++ListIndex)
          {
            if(wrld_record->CELLS[ListIndex] == curRecord)
            {
              wrld_record->CELLS.erase(wrld_record->CELLS.begin() + ListIndex);
              cell_found = true;
              break;
            }
          }
        }
        if(!cell_found)
        {
          printer("TES5File::DeleteRecord: Error - Unable to delete record type (%s) with parent type (%s) in mod \"%s\". The parent record (%08X) does not contain the record to be deleted (%08X).\n", curRecord->GetStrType(), curRecord->GetParentRecord()->GetStrType(), ModName, curRecord->GetParentRecord()->formID, curRecord->formID);
          return 0;
        }
          }
          Sk::CELLRecord *cell_record = (Sk::CELLRecord *)curRecord;

          /*
          for(UINT32 ListIndex = 0; ListIndex < cell_record->ACHR.size(); ++ListIndex)
          {
        deindexer.Accept(cell_record->ACHR[ListIndex]);
        CELL.achr_pool.destroy(cell_record->ACHR[ListIndex]);
          }

          for(UINT32 ListIndex = 0; ListIndex < cell_record->ACRE.size(); ++ListIndex)
          {
        deindexer.Accept(cell_record->ACRE[ListIndex]);
        CELL.acre_pool.destroy(cell_record->ACRE[ListIndex]);
          }

          for(UINT32 ListIndex = 0; ListIndex < cell_record->REFR.size(); ++ListIndex)
          {
        deindexer.Accept(cell_record->REFR[ListIndex]);
        CELL.refr_pool.destroy(cell_record->REFR[ListIndex]);
          }

          for(UINT32 ListIndex = 0; ListIndex < cell_record->PGRE.size(); ++ListIndex)
          {
        deindexer.Accept(cell_record->PGRE[ListIndex]);
        CELL.pgre_pool.destroy(cell_record->PGRE[ListIndex]);
          }

          for(UINT32 ListIndex = 0; ListIndex < cell_record->PMIS.size(); ++ListIndex)
          {
        deindexer.Accept(cell_record->PMIS[ListIndex]);
        CELL.pmis_pool.destroy(cell_record->PMIS[ListIndex]);
          }

          for(UINT32 ListIndex = 0; ListIndex < cell_record->PBEA.size(); ++ListIndex)
          {
        deindexer.Accept(cell_record->PBEA[ListIndex]);
        CELL.pbea_pool.destroy(cell_record->PBEA[ListIndex]);
          }

          for(UINT32 ListIndex = 0; ListIndex < cell_record->PFLA.size(); ++ListIndex)
          {
        deindexer.Accept(cell_record->PFLA[ListIndex]);
        CELL.pfla_pool.destroy(cell_record->PFLA[ListIndex]);
          }

          for(UINT32 ListIndex = 0; ListIndex < cell_record->PCBE.size(); ++ListIndex)
          {
        deindexer.Accept(cell_record->PCBE[ListIndex]);
        CELL.pcbe_pool.destroy(cell_record->PCBE[ListIndex]);
          }

          for(UINT32 ListIndex = 0; ListIndex < cell_record->NAVM.size(); ++ListIndex)
          {
        deindexer.Accept(cell_record->NAVM[ListIndex]);
        CELL.navm_pool.destroy(cell_record->NAVM[ListIndex]);
          }
          */

          deindexer.Accept(cell_record->LAND);
          WRLD.land_pool.destroy(cell_record->LAND);

          deindexer.Accept(curRecord);
          if(cell_found)
        WRLD.cell_pool.destroy(curRecord);
          else
        CELL.cell_pool.destroy(curRecord);
        }
        return 1;
    case REV32(WRLD):
        {
          Sk::WRLDRecord *wrld_record = (Sk::WRLDRecord *)curRecord;

          Sk::CELLRecord *cell_record = (Sk::CELLRecord *)wrld_record->CELL;
          if(cell_record != NULL) //Add it to list of cells to be deleted
        wrld_record->CELLS.push_back(cell_record);

          for(UINT32 ListIndex = 0; ListIndex < wrld_record->CELLS.size(); ++ListIndex)
          {
        cell_record = (Sk::CELLRecord *)wrld_record->CELLS[ListIndex];

        /*
        for(UINT32 ListX2Index = 0; ListX2Index < cell_record->ACHR.size(); ++ListX2Index)
        {
          deindexer.Accept(cell_record->ACHR[ListX2Index]);
          CELL.achr_pool.destroy(cell_record->ACHR[ListX2Index]);
        }

        for(UINT32 ListX2Index = 0; ListX2Index < cell_record->ACRE.size(); ++ListX2Index)
        {
          deindexer.Accept(cell_record->ACRE[ListX2Index]);
          CELL.acre_pool.destroy(cell_record->ACRE[ListX2Index]);
        }

        for(UINT32 ListX2Index = 0; ListX2Index < cell_record->REFR.size(); ++ListX2Index)
        {
          deindexer.Accept(cell_record->REFR[ListX2Index]);
          CELL.refr_pool.destroy(cell_record->REFR[ListX2Index]);
        }

        for(UINT32 ListX2Index = 0; ListX2Index < cell_record->PGRE.size(); ++ListX2Index)
        {
          deindexer.Accept(cell_record->PGRE[ListX2Index]);
          CELL.pgre_pool.destroy(cell_record->PGRE[ListX2Index]);
        }

        for(UINT32 ListX2Index = 0; ListX2Index < cell_record->PMIS.size(); ++ListX2Index)
        {
          deindexer.Accept(cell_record->PMIS[ListX2Index]);
          CELL.pmis_pool.destroy(cell_record->PMIS[ListX2Index]);
        }

        for(UINT32 ListX2Index = 0; ListX2Index < cell_record->PBEA.size(); ++ListX2Index)
        {
          deindexer.Accept(cell_record->PBEA[ListX2Index]);
          CELL.pbea_pool.destroy(cell_record->PBEA[ListX2Index]);
        }

        for(UINT32 ListX2Index = 0; ListX2Index < cell_record->PFLA.size(); ++ListX2Index)
        {
          deindexer.Accept(cell_record->PFLA[ListX2Index]);
          CELL.pfla_pool.destroy(cell_record->PFLA[ListX2Index]);
        }

        for(UINT32 ListX2Index = 0; ListX2Index < cell_record->PCBE.size(); ++ListX2Index)
        {
          deindexer.Accept(cell_record->PCBE[ListX2Index]);
          CELL.pcbe_pool.destroy(cell_record->PCBE[ListX2Index]);
        }

        for(UINT32 ListX2Index = 0; ListX2Index < cell_record->NAVM.size(); ++ListX2Index)
        {
          deindexer.Accept(cell_record->NAVM[ListX2Index]);
          CELL.navm_pool.destroy(cell_record->NAVM[ListX2Index]);
        }
        */

        deindexer.Accept(cell_record->LAND);
        WRLD.land_pool.destroy(cell_record->LAND);

        deindexer.Accept((Record *&)cell_record);
        WRLD.cell_pool.destroy(cell_record);
          }

          deindexer.Accept(curRecord);
          WRLD.wrld_pool.destroy(curRecord);
        }
        return 1;
    case REV32(LAND):
        {
          Sk::CELLRecord *cell_record = (Sk::CELLRecord *)curRecord->GetParentRecord();

          if(cell_record->LAND != curRecord)
          {
        printer("TES5File::DeleteRecord: Error - Unable to delete record type (%s) with parent type (%s) in mod \"%s\". The parent record (%08X) does not contain the record to be deleted (%08X).\n", curRecord->GetStrType(), curRecord->GetParentRecord()->GetStrType(), ModName, curRecord->GetParentRecord()->formID, curRecord->formID);
        return 0;
          }

          cell_record->LAND = NULL;
          deindexer.Accept(curRecord);
          WRLD.land_pool.destroy(curRecord);
        }
        return 1;
      /*
        case REV32(GMST):
            deindexer.Accept(curRecord);
            GMST.pool.destroy(curRecord);
            return 1;
        case REV32(MICN):
            deindexer.Accept(curRecord);
            MICN.pool.destroy(curRecord);
            return 1;
        case REV32(GLOB):
            deindexer.Accept(curRecord);
            GLOB.pool.destroy(curRecord);
            return 1;
        case REV32(CLAS):
            deindexer.Accept(curRecord);
            CLAS.pool.destroy(curRecord);
            return 1;
        case REV32(FACT):
            deindexer.Accept(curRecord);
            FACT.pool.destroy(curRecord);
            return 1;
        case REV32(HDPT):
            deindexer.Accept(curRecord);
            HDPT.pool.destroy(curRecord);
            return 1;
        case REV32(HAIR):
            deindexer.Accept(curRecord);
            HAIR.pool.destroy(curRecord);
            return 1;
        case REV32(EYES):
            deindexer.Accept(curRecord);
            EYES.pool.destroy(curRecord);
            return 1;
        case REV32(RACE):
            deindexer.Accept(curRecord);
            RACE.pool.destroy(curRecord);
            return 1;
        case REV32(SOUN):
            deindexer.Accept(curRecord);
            SOUN.pool.destroy(curRecord);
            return 1;
        case REV32(ASPC):
            deindexer.Accept(curRecord);
            ASPC.pool.destroy(curRecord);
            return 1;
        case REV32(MGEF):
            deindexer.Accept(curRecord);
            MGEF.pool.destroy(curRecord);
            return 1;
        case REV32(SCPT):
            deindexer.Accept(curRecord);
            SCPT.pool.destroy(curRecord);
            return 1;
        case REV32(ENCH):
            deindexer.Accept(curRecord);
            ENCH.pool.destroy(curRecord);
            return 1;
        case REV32(SPEL):
            deindexer.Accept(curRecord);
            SPEL.pool.destroy(curRecord);
            return 1;
        case REV32(ACTI):
            deindexer.Accept(curRecord);
            ACTI.pool.destroy(curRecord);
            return 1;
        case REV32(TACT):
            deindexer.Accept(curRecord);
            TACT.pool.destroy(curRecord);
            return 1;
        case REV32(TERM):
            deindexer.Accept(curRecord);
            TERM.pool.destroy(curRecord);
            return 1;
        case REV32(ARMO):
            deindexer.Accept(curRecord);
            ARMO.pool.destroy(curRecord);
            return 1;
        case REV32(BOOK):
            deindexer.Accept(curRecord);
            BOOK.pool.destroy(curRecord);
            return 1;
        case REV32(CONT):
            deindexer.Accept(curRecord);
            CONT.pool.destroy(curRecord);
            return 1;
        case REV32(DOOR):
            deindexer.Accept(curRecord);
            DOOR.pool.destroy(curRecord);
            return 1;
        case REV32(INGR):
            deindexer.Accept(curRecord);
            INGR.pool.destroy(curRecord);
            return 1;
        case REV32(LIGH):
            deindexer.Accept(curRecord);
            LIGH.pool.destroy(curRecord);
            return 1;
        case REV32(MISC):
            deindexer.Accept(curRecord);
            MISC.pool.destroy(curRecord);
            return 1;
        case REV32(STAT):
            deindexer.Accept(curRecord);
            STAT.pool.destroy(curRecord);
            return 1;
        case REV32(SCOL):
            deindexer.Accept(curRecord);
            SCOL.pool.destroy(curRecord);
            return 1;
        case REV32(MSTT):
            deindexer.Accept(curRecord);
            MSTT.pool.destroy(curRecord);
            return 1;
        case REV32(PWAT):
            deindexer.Accept(curRecord);
            PWAT.pool.destroy(curRecord);
            return 1;
        case REV32(GRAS):
            deindexer.Accept(curRecord);
            GRAS.pool.destroy(curRecord);
            return 1;
        case REV32(TREE):
            deindexer.Accept(curRecord);
            TREE.pool.destroy(curRecord);
            return 1;
        case REV32(FURN):
            deindexer.Accept(curRecord);
            FURN.pool.destroy(curRecord);
            return 1;
        case REV32(WEAP):
            deindexer.Accept(curRecord);
            WEAP.pool.destroy(curRecord);
            return 1;
        case REV32(AMMO):
            deindexer.Accept(curRecord);
            AMMO.pool.destroy(curRecord);
            return 1;
        case REV32(NPC_):
            deindexer.Accept(curRecord);
            NPC_.pool.destroy(curRecord);
            return 1;
        case REV32(CREA):
            deindexer.Accept(curRecord);
            CREA.pool.destroy(curRecord);
            return 1;
        case REV32(LVLC):
            deindexer.Accept(curRecord);
            LVLC.pool.destroy(curRecord);
            return 1;
        case REV32(LVLN):
            deindexer.Accept(curRecord);
            LVLN.pool.destroy(curRecord);
            return 1;
        case REV32(KEYM):
            deindexer.Accept(curRecord);
            KEYM.pool.destroy(curRecord);
            return 1;
        case REV32(ALCH):
            deindexer.Accept(curRecord);
            ALCH.pool.destroy(curRecord);
            return 1;
        case REV32(IDLM):
            deindexer.Accept(curRecord);
            IDLM.pool.destroy(curRecord);
            return 1;
        case REV32(NOTE):
            deindexer.Accept(curRecord);
            NOTE.pool.destroy(curRecord);
            return 1;
        case REV32(COBJ):
            deindexer.Accept(curRecord);
            COBJ.pool.destroy(curRecord);
            return 1;
        case REV32(PROJ):
            deindexer.Accept(curRecord);
            PROJ.pool.destroy(curRecord);
            return 1;
        case REV32(LVLI):
            deindexer.Accept(curRecord);
            LVLI.pool.destroy(curRecord);
            return 1;
        case REV32(WTHR):
            deindexer.Accept(curRecord);
            WTHR.pool.destroy(curRecord);
            return 1;
        case REV32(CLMT):
            deindexer.Accept(curRecord);
            CLMT.pool.destroy(curRecord);
            return 1;
        case REV32(REGN):
            deindexer.Accept(curRecord);
            REGN.pool.destroy(curRecord);
            return 1;
        case REV32(NAVI):
            deindexer.Accept(curRecord);
            NAVI.pool.destroy(curRecord);
            return 1;
        case REV32(DIAL):
            {
            Sk::DIALRecord *dial_record = (Sk::DIALRecord *)curRecord;
            for(UINT32 ListIndex = 0; ListIndex < dial_record->INFO.size(); ++ListIndex)
                {
                deindexer.Accept(dial_record->INFO[ListIndex]);
                DIAL.info_pool.destroy(dial_record->INFO[ListIndex]);
                }

            deindexer.Accept(curRecord);
            DIAL.dial_pool.destroy(curRecord);
            }
            return 1;
        case REV32(INFO):
            {
            Sk::DIALRecord *dial_record = (Sk::DIALRecord *)curRecord->GetParentRecord();
            bool info_found = false;
            for(UINT32 ListIndex = 0; ListIndex < dial_record->INFO.size(); ++ListIndex)
                {
                if(dial_record->INFO[ListIndex] == curRecord)
                    {
                    dial_record->INFO.erase(dial_record->INFO.begin() + ListIndex);
                    info_found = true;
                    break;
                    }
                }
            if(!info_found)
                {
                printer("TES5File::DeleteRecord: Error - Unable to delete record type (%s) with parent type (%s) in mod \"%s\". The parent record (%08X) does not contain the record to be deleted (%08X).\n", curRecord->GetStrType(), curRecord->GetParentRecord()->GetStrType(), ModName, curRecord->GetParentRecord()->formID, curRecord->formID);
                return 0;
                }

            deindexer.Accept(curRecord);
            DIAL.info_pool.destroy(curRecord);
            }
            return 1;
        case REV32(ACHR):
            {
            Sk::CELLRecord *cell_record = (Sk::CELLRecord *)curRecord->GetParentRecord();
            bool achr_found = false;
            for(UINT32 ListIndex = 0; ListIndex < cell_record->ACHR.size(); ++ListIndex)
                {
                if(cell_record->ACHR[ListIndex] == curRecord)
                    {
                    cell_record->ACHR.erase(cell_record->ACHR.begin() + ListIndex);
                    achr_found = true;
                    break;
                    }
                }
            if(!achr_found)
                {
                printer("TES5File::DeleteRecord: Error - Unable to delete record type (%s) with parent type (%s) in mod \"%s\". The parent record (%08X) does not contain the record to be deleted (%08X).\n", curRecord->GetStrType(), curRecord->GetParentRecord()->GetStrType(), ModName, curRecord->GetParentRecord()->formID, curRecord->formID);
                return 0;
                }

            deindexer.Accept(curRecord);
            CELL.achr_pool.destroy(curRecord);
            }
            return 1;
        case REV32(ACRE):
            {
            Sk::CELLRecord *cell_record = (Sk::CELLRecord *)curRecord->GetParentRecord();
            bool child_found = false;
            for(UINT32 ListIndex = 0; ListIndex < cell_record->ACRE.size(); ++ListIndex)
                {
                if(cell_record->ACRE[ListIndex] == curRecord)
                    {
                    cell_record->ACRE.erase(cell_record->ACRE.begin() + ListIndex);
                    child_found = true;
                    break;
                    }
                }
            if(!child_found)
                {
                printer("TES5File::DeleteRecord: Error - Unable to delete record type (%s) with parent type (%s) in mod \"%s\". The parent record (%08X) does not contain the record to be deleted (%08X).\n", curRecord->GetStrType(), curRecord->GetParentRecord()->GetStrType(), ModName, curRecord->GetParentRecord()->formID, curRecord->formID);
                return 0;
                }

            deindexer.Accept(curRecord);
            CELL.acre_pool.destroy(curRecord);
            }
            return 1;
        case REV32(REFR):
            {
            Sk::CELLRecord *cell_record = (Sk::CELLRecord *)curRecord->GetParentRecord();
            bool child_found = false;
            for(UINT32 ListIndex = 0; ListIndex < cell_record->REFR.size(); ++ListIndex)
                {
                if(cell_record->REFR[ListIndex] == curRecord)
                    {
                    cell_record->REFR.erase(cell_record->REFR.begin() + ListIndex);
                    child_found = true;
                    break;
                    }
                }
            if(!child_found)
                {
                printer("TES5File::DeleteRecord: Error - Unable to delete record type (%s) with parent type (%s) in mod \"%s\". The parent record (%08X) does not contain the record to be deleted (%08X).\n", curRecord->GetStrType(), curRecord->GetParentRecord()->GetStrType(), ModName, curRecord->GetParentRecord()->formID, curRecord->formID);
                return 0;
                }

            deindexer.Accept(curRecord);
            CELL.refr_pool.destroy(curRecord);
            }
            return 1;
        case REV32(PGRE):
            {
            Sk::CELLRecord *cell_record = (Sk::CELLRecord *)curRecord->GetParentRecord();
            bool child_found = false;
            for(UINT32 ListIndex = 0; ListIndex < cell_record->PGRE.size(); ++ListIndex)
                {
                if(cell_record->PGRE[ListIndex] == curRecord)
                    {
                    cell_record->PGRE.erase(cell_record->PGRE.begin() + ListIndex);
                    child_found = true;
                    break;
                    }
                }
            if(!child_found)
                {
                printer("TES5File::DeleteRecord: Error - Unable to delete record type (%s) with parent type (%s) in mod \"%s\". The parent record (%08X) does not contain the record to be deleted (%08X).\n", curRecord->GetStrType(), curRecord->GetParentRecord()->GetStrType(), ModName, curRecord->GetParentRecord()->formID, curRecord->formID);
                return 0;
                }

            deindexer.Accept(curRecord);
            CELL.pgre_pool.destroy(curRecord);
            }
            return 1;
        case REV32(PMIS):
            {
            Sk::CELLRecord *cell_record = (Sk::CELLRecord *)curRecord->GetParentRecord();
            bool child_found = false;
            for(UINT32 ListIndex = 0; ListIndex < cell_record->PMIS.size(); ++ListIndex)
                {
                if(cell_record->PMIS[ListIndex] == curRecord)
                    {
                    cell_record->PMIS.erase(cell_record->PMIS.begin() + ListIndex);
                    child_found = true;
                    break;
                    }
                }
            if(!child_found)
                {
                printer("TES5File::DeleteRecord: Error - Unable to delete record type (%s) with parent type (%s) in mod \"%s\". The parent record (%08X) does not contain the record to be deleted (%08X).\n", curRecord->GetStrType(), curRecord->GetParentRecord()->GetStrType(), ModName, curRecord->GetParentRecord()->formID, curRecord->formID);
                return 0;
                }

            deindexer.Accept(curRecord);
            CELL.pmis_pool.destroy(curRecord);
            }
            return 1;
        case REV32(PBEA):
            {
            Sk::CELLRecord *cell_record = (Sk::CELLRecord *)curRecord->GetParentRecord();
            bool child_found = false;
            for(UINT32 ListIndex = 0; ListIndex < cell_record->PBEA.size(); ++ListIndex)
                {
                if(cell_record->PBEA[ListIndex] == curRecord)
                    {
                    cell_record->PBEA.erase(cell_record->PBEA.begin() + ListIndex);
                    child_found = true;
                    break;
                    }
                }
            if(!child_found)
                {
                printer("TES5File::DeleteRecord: Error - Unable to delete record type (%s) with parent type (%s) in mod \"%s\". The parent record (%08X) does not contain the record to be deleted (%08X).\n", curRecord->GetStrType(), curRecord->GetParentRecord()->GetStrType(), ModName, curRecord->GetParentRecord()->formID, curRecord->formID);
                return 0;
                }

            deindexer.Accept(curRecord);
            CELL.pbea_pool.destroy(curRecord);
            }
            return 1;
        case REV32(PFLA):
            {
            Sk::CELLRecord *cell_record = (Sk::CELLRecord *)curRecord->GetParentRecord();
            bool child_found = false;
            for(UINT32 ListIndex = 0; ListIndex < cell_record->PFLA.size(); ++ListIndex)
                {
                if(cell_record->PFLA[ListIndex] == curRecord)
                    {
                    cell_record->PFLA.erase(cell_record->PFLA.begin() + ListIndex);
                    child_found = true;
                    break;
                    }
                }
            if(!child_found)
                {
                printer("TES5File::DeleteRecord: Error - Unable to delete record type (%s) with parent type (%s) in mod \"%s\". The parent record (%08X) does not contain the record to be deleted (%08X).\n", curRecord->GetStrType(), curRecord->GetParentRecord()->GetStrType(), ModName, curRecord->GetParentRecord()->formID, curRecord->formID);
                return 0;
                }

            deindexer.Accept(curRecord);
            CELL.pfla_pool.destroy(curRecord);
            }
            return 1;
        case REV32(PCBE):
            {
            Sk::CELLRecord *cell_record = (Sk::CELLRecord *)curRecord->GetParentRecord();
            bool child_found = false;
            for(UINT32 ListIndex = 0; ListIndex < cell_record->PCBE.size(); ++ListIndex)
                {
                if(cell_record->PCBE[ListIndex] == curRecord)
                    {
                    cell_record->PCBE.erase(cell_record->PCBE.begin() + ListIndex);
                    child_found = true;
                    break;
                    }
                }
            if(!child_found)
                {
                printer("TES5File::DeleteRecord: Error - Unable to delete record type (%s) with parent type (%s) in mod \"%s\". The parent record (%08X) does not contain the record to be deleted (%08X).\n", curRecord->GetStrType(), curRecord->GetParentRecord()->GetStrType(), ModName, curRecord->GetParentRecord()->formID, curRecord->formID);
                return 0;
                }

            deindexer.Accept(curRecord);
            CELL.pcbe_pool.destroy(curRecord);
            }
            return 1;
        case REV32(NAVM):
            {
            Sk::CELLRecord *cell_record = (Sk::CELLRecord *)curRecord->GetParentRecord();
            bool child_found = false;
            for(UINT32 ListIndex = 0; ListIndex < cell_record->NAVM.size(); ++ListIndex)
                {
                if(cell_record->NAVM[ListIndex] == curRecord)
                    {
                    cell_record->NAVM.erase(cell_record->NAVM.begin() + ListIndex);
                    child_found = true;
                    break;
                    }
                }
            if(!child_found)
                {
                printer("TES5File::DeleteRecord: Error - Unable to delete record type (%s) with parent type (%s) in mod \"%s\". The parent record (%08X) does not contain the record to be deleted (%08X).\n", curRecord->GetStrType(), curRecord->GetParentRecord()->GetStrType(), ModName, curRecord->GetParentRecord()->formID, curRecord->formID);
                return 0;
                }

            deindexer.Accept(curRecord);
            CELL.navm_pool.destroy(curRecord);
            }
            return 1;
        case REV32(QUST):
            deindexer.Accept(curRecord);
            QUST.pool.destroy(curRecord);
            return 1;
        case REV32(IDLE):
            deindexer.Accept(curRecord);
            IDLE.pool.destroy(curRecord);
            return 1;
        case REV32(PACK):
            deindexer.Accept(curRecord);
            PACK.pool.destroy(curRecord);
            return 1;
        case REV32(CSTY):
            deindexer.Accept(curRecord);
            CSTY.pool.destroy(curRecord);
            return 1;
        case REV32(LSCR):
            deindexer.Accept(curRecord);
            LSCR.pool.destroy(curRecord);
            return 1;
        case REV32(ANIO):
            deindexer.Accept(curRecord);
            ANIO.pool.destroy(curRecord);
            return 1;
        case REV32(WATR):
            deindexer.Accept(curRecord);
            WATR.pool.destroy(curRecord);
            return 1;
        case REV32(EFSH):
            deindexer.Accept(curRecord);
            EFSH.pool.destroy(curRecord);
            return 1;
        case REV32(EXPL):
            deindexer.Accept(curRecord);
            EXPL.pool.destroy(curRecord);
            return 1;
        case REV32(DEBR):
            deindexer.Accept(curRecord);
            DEBR.pool.destroy(curRecord);
            return 1;
        //case REV32(IMGS):
        //    deindexer.Accept(curRecord);
        //    IMGS.pool.destroy(curRecord);
        //    return 1;
        //case REV32(IMAD):
        //    deindexer.Accept(curRecord);
        //    IMAD.pool.destroy(curRecord);
        //    return 1;
        //case REV32(FLST):
        //    deindexer.Accept(curRecord);
        //    FLST.pool.destroy(curRecord);
        //    return 1;
        //case REV32(PERK):
        //    deindexer.Accept(curRecord);
        //    PERK.pool.destroy(curRecord);
        //    return 1;
        //case REV32(BPTD):
        //    deindexer.Accept(curRecord);
        //    BPTD.pool.destroy(curRecord);
        //    return 1;
        //case REV32(ADDN):
        //    deindexer.Accept(curRecord);
        //    ADDN.pool.destroy(curRecord);
        //    return 1;
        //case REV32(AVIF):
        //    deindexer.Accept(curRecord);
        //    AVIF.pool.destroy(curRecord);
        //    return 1;
        //case REV32(RADS):
        //    deindexer.Accept(curRecord);
        //    RADS.pool.destroy(curRecord);
        //    return 1;
        //case REV32(CAMS):
        //    deindexer.Accept(curRecord);
        //    CAMS.pool.destroy(curRecord);
        //    return 1;
        //case REV32(CPTH):
        //    deindexer.Accept(curRecord);
        //    CPTH.pool.destroy(curRecord);
        //    return 1;
        //case REV32(VTYP):
        //    deindexer.Accept(curRecord);
        //    VTYP.pool.destroy(curRecord);
        //    return 1;
        //case REV32(IPCT):
        //    deindexer.Accept(curRecord);
        //    IPCT.pool.destroy(curRecord);
        //    return 1;
        //case REV32(IPDS):
        //    deindexer.Accept(curRecord);
        //    IPDS.pool.destroy(curRecord);
        //    return 1;
        //case REV32(ARMA):
        //    deindexer.Accept(curRecord);
        //    ARMA.pool.destroy(curRecord);
        //    return 1;
        //case REV32(ECZN):
        //    deindexer.Accept(curRecord);
        //    ECZN.pool.destroy(curRecord);
        //    return 1;
        //case REV32(MESG):
        //    deindexer.Accept(curRecord);
        //    MESG.pool.destroy(curRecord);
        //    return 1;
        //case REV32(RGDL):
        //    deindexer.Accept(curRecord);
        //    RGDL.pool.destroy(curRecord);
        //    return 1;
        //case REV32(DOBJ):
        //    deindexer.Accept(curRecord);
        //    DOBJ.pool.destroy(curRecord);
        //    return 1;
        //case REV32(LGTM):
        //    deindexer.Accept(curRecord);
        //    LGTM.pool.destroy(curRecord);
        //    return 1;
        //case REV32(MUSC):
        //    deindexer.Accept(curRecord);
        //    MUSC.pool.destroy(curRecord);
        //    return 1;
        //case REV32(IMOD):
        //    deindexer.Accept(curRecord);
        //    IMOD.pool.destroy(curRecord);
        //    return 1;
        //case REV32(REPU):
        //    deindexer.Accept(curRecord);
        //    REPU.pool.destroy(curRecord);
        //    return 1;
        //case REV32(RCPE):
        //    deindexer.Accept(curRecord);
        //    RCPE.pool.destroy(curRecord);
        //    return 1;
        //case REV32(RCCT):
        //    deindexer.Accept(curRecord);
        //    RCCT.pool.destroy(curRecord);
        //    return 1;
        //case REV32(CHIP):
        //    deindexer.Accept(curRecord);
        //    CHIP.pool.destroy(curRecord);
        //    return 1;
        //case REV32(CSNO):
        //    deindexer.Accept(curRecord);
        //    CSNO.pool.destroy(curRecord);
        //    return 1;
        //case REV32(LSCT):
        //    deindexer.Accept(curRecord);
        //    LSCT.pool.destroy(curRecord);
        //    return 1;
        //case REV32(MSET):
        //    deindexer.Accept(curRecord);
        //    MSET.pool.destroy(curRecord);
        //    return 1;
        //case REV32(ALOC):
        //    deindexer.Accept(curRecord);
        //    ALOC.pool.destroy(curRecord);
        //    return 1;
        //case REV32(CHAL):
        //    deindexer.Accept(curRecord);
        //    CHAL.pool.destroy(curRecord);
        //    return 1;
        //case REV32(AMEF):
        //    deindexer.Accept(curRecord);
        //    AMEF.pool.destroy(curRecord);
        //    return 1;
        //case REV32(CCRD):
        //    deindexer.Accept(curRecord);
        //    CCRD.pool.destroy(curRecord);
        //    return 1;
        //case REV32(CMNY):
        //    deindexer.Accept(curRecord);
        //    CMNY.pool.destroy(curRecord);
        //    return 1;
        //case REV32(CDCK):
        //    deindexer.Accept(curRecord);
        //    CDCK.pool.destroy(curRecord);
        //    return 1;
        //case REV32(DEHY):
        //    deindexer.Accept(curRecord);
        //    DEHY.pool.destroy(curRecord);
        //    return 1;
        //case REV32(HUNG):
        //    deindexer.Accept(curRecord);
        //    HUNG.pool.destroy(curRecord);
        //    return 1;
        //case REV32(SLPD):
        //    deindexer.Accept(curRecord);
        //    SLPD.pool.destroy(curRecord);
        //    return 1;
    */
        default:
            {
            Record *Parent = curRecord->GetParentRecord();
            if(Parent != NULL)
                {
                Record *TopParent = Parent->GetParentRecord();
                if(TopParent != NULL)
                    printer("TES4File::DeleteRecord: Error - Unable to delete record type (%s) with parent type (%s) in group (%s) in mod \"%s\". The parent record (%08X) does not contain the record to be deleted (%08X).\n", curRecord->GetStrType(), Parent->GetStrType(), TopParent->GetStrType(), ModName, Parent->formID, curRecord->formID);
                else
                    printer("TES4File::DeleteRecord: Error - Unable to delete record type (%s) in group (%s) in mod \"%s\". The parent record (%08X) does not contain the record to be deleted (%08X).\n", curRecord->GetStrType(), Parent->GetStrType(), ModName, Parent->formID, curRecord->formID);
                }
            else
                printer("TES4File::DeleteRecord: Error - Unable to delete record type (%s) in group (%s) in mod \"%s\". The group does not contain the record to be deleted (%08X).\n", curRecord->GetStrType(), curRecord->GetStrType(), ModName, curRecord->formID);
            }
            return 0;
        }
    return 0;
    }

SINT32 TES5File::Save(STRING const &SaveName, std::vector<FormIDResolver *> &Expanders, bool CloseMod, RecordOp &indexer)
    {
    if(!Flags.IsSaveable)
        {
        printer("TES5File::Save: Error - Unable to save mod \"%s\". It is flagged as being non-saveable.\n", ModName);
        return -1;
        }

    FileWriter writer(SaveName, BUFFERSIZE);
    if(writer.open() == -1)
        throw std::exception("TES5File::Save: Error - Unable to open temporary file for writing\n");

    UINT32 formCount = 0;
    FormIDResolver expander(FormIDHandler.ExpandTable, FormIDHandler.FileStart, FormIDHandler.FileEnd);
    FormIDResolver collapser(FormIDHandler.CollapseTable, FormIDHandler.FileStart, FormIDHandler.FileEnd);
    //RecordReader reader(FormIDHandler);
    const bool bMastersChanged = FormIDHandler.MastersChanged();

    TES4.Write(writer, bMastersChanged, expander, collapser, Expanders);

    //ADD DEFINITIONS HERE
    formCount += LTEX.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += TXST.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += MATT.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += CELL.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += WRLD.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod, FormIDHandler, CELL, indexer);
    /*
    formCount += GMST.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += MICN.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += GLOB.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += CLAS.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += FACT.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += HDPT.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += HAIR.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += EYES.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += RACE.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += SOUN.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += ASPC.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += MGEF.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += SCPT.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += ENCH.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += SPEL.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += ACTI.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += TACT.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += TERM.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += ARMO.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += BOOK.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += CONT.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += DOOR.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += INGR.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += LIGH.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += MISC.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += STAT.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += SCOL.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += MSTT.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += PWAT.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += GRAS.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += TREE.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += FURN.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += WEAP.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += AMMO.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += NPC_.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += CREA.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += LVLC.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += LVLN.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += KEYM.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += ALCH.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += IDLM.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += NOTE.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += COBJ.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += PROJ.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += LVLI.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += WTHR.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += CLMT.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += REGN.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += NAVI.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += DIAL.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += QUST.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += IDLE.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += PACK.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += CSTY.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += LSCR.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += ANIO.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += WATR.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += EFSH.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += EXPL.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += DEBR.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += IMGS.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += IMAD.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += FLST.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += PERK.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += BPTD.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += ADDN.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += AVIF.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += RADS.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += CAMS.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += CPTH.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += VTYP.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += IPCT.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += IPDS.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += ARMA.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += ECZN.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += MESG.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += RGDL.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += DOBJ.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += LGTM.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += MUSC.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += IMOD.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += REPU.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += RCPE.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += RCCT.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += CHIP.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += CSNO.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += LSCT.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += MSET.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += ALOC.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += CHAL.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += AMEF.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += CCRD.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += CMNY.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += CDCK.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += DEHY.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += HUNG.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += SLPD.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    */

    //update formCount. Cheaper to go back and write it at the end than to calculate it before any writing.
    writer.file_write(34, &formCount, 4);
    writer.close();

    return 0;
    }

void TES5File::VisitAllRecords(RecordOp &op)
    {
    if(Flags.IsNoLoad)
        {
        printer("TES5File::VisitAllRecords: Error - Unable to visit records in mod \"%s\". The mod is flagged not to be loaded.\n", ModName);
        return;
        }

    //This visits every record and subrecord
    {
    Record *temp = &TES4;
    op.Accept(temp);
    }

    LTEX.pool.VisitRecords(op);
    TXST.pool.VisitRecords(op);
    MATT.pool.VisitRecords(op);
    WRLD.land_pool.VisitRecords(op);
    CELL.cell_pool.VisitRecords(op);
    WRLD.cell_pool.VisitRecords(op);
    WRLD.wrld_pool.VisitRecords(op);
    /*
    GMST.pool.VisitRecords(op);
    MICN.pool.VisitRecords(op);
    GLOB.pool.VisitRecords(op);
    CLAS.pool.VisitRecords(op);
    FACT.pool.VisitRecords(op);
    HDPT.pool.VisitRecords(op);
    HAIR.pool.VisitRecords(op);
    EYES.pool.VisitRecords(op);
    RACE.pool.VisitRecords(op);
    SOUN.pool.VisitRecords(op);
    ASPC.pool.VisitRecords(op);
    MGEF.pool.VisitRecords(op);
    SCPT.pool.VisitRecords(op);
    ENCH.pool.VisitRecords(op);
    SPEL.pool.VisitRecords(op);
    ACTI.pool.VisitRecords(op);
    TACT.pool.VisitRecords(op);
    TERM.pool.VisitRecords(op);
    ARMO.pool.VisitRecords(op);
    BOOK.pool.VisitRecords(op);
    CONT.pool.VisitRecords(op);
    DOOR.pool.VisitRecords(op);
    INGR.pool.VisitRecords(op);
    LIGH.pool.VisitRecords(op);
    MISC.pool.VisitRecords(op);
    STAT.pool.VisitRecords(op);
    SCOL.pool.VisitRecords(op);
    MSTT.pool.VisitRecords(op);
    PWAT.pool.VisitRecords(op);
    GRAS.pool.VisitRecords(op);
    TREE.pool.VisitRecords(op);
    FURN.pool.VisitRecords(op);
    WEAP.pool.VisitRecords(op);
    AMMO.pool.VisitRecords(op);
    NPC_.pool.VisitRecords(op);
    CREA.pool.VisitRecords(op);
    LVLC.pool.VisitRecords(op);
    LVLN.pool.VisitRecords(op);
    KEYM.pool.VisitRecords(op);
    ALCH.pool.VisitRecords(op);
    IDLM.pool.VisitRecords(op);
    NOTE.pool.VisitRecords(op);
    COBJ.pool.VisitRecords(op);
    PROJ.pool.VisitRecords(op);
    LVLI.pool.VisitRecords(op);
    WTHR.pool.VisitRecords(op);
    CLMT.pool.VisitRecords(op);
    REGN.pool.VisitRecords(op);
    NAVI.pool.VisitRecords(op);
    //Child records need to be visited prior to the parent in order for identical to master cleaning to work nicely
    CELL.achr_pool.VisitRecords(op);
    CELL.acre_pool.VisitRecords(op);
    CELL.refr_pool.VisitRecords(op);
    CELL.pgre_pool.VisitRecords(op);
    CELL.pmis_pool.VisitRecords(op);
    CELL.pbea_pool.VisitRecords(op);
    CELL.pfla_pool.VisitRecords(op);
    CELL.pcbe_pool.VisitRecords(op);
    CELL.navm_pool.VisitRecords(op);
    DIAL.info_pool.VisitRecords(op);

    DIAL.dial_pool.VisitRecords(op);
    QUST.pool.VisitRecords(op);
    IDLE.pool.VisitRecords(op);
    PACK.pool.VisitRecords(op);
    CSTY.pool.VisitRecords(op);
    LSCR.pool.VisitRecords(op);
    ANIO.pool.VisitRecords(op);
    WATR.pool.VisitRecords(op);
    EFSH.pool.VisitRecords(op);
    EXPL.pool.VisitRecords(op);
    DEBR.pool.VisitRecords(op);
    //IMGS.pool.VisitRecords(op);
    //IMAD.pool.VisitRecords(op);
    //FLST.pool.VisitRecords(op);
    //PERK.pool.VisitRecords(op);
    //BPTD.pool.VisitRecords(op);
    //ADDN.pool.VisitRecords(op);
    //AVIF.pool.VisitRecords(op);
    //RADS.pool.VisitRecords(op);
    //CAMS.pool.VisitRecords(op);
    //CPTH.pool.VisitRecords(op);
    //VTYP.pool.VisitRecords(op);
    //IPCT.pool.VisitRecords(op);
    //IPDS.pool.VisitRecords(op);
    //ARMA.pool.VisitRecords(op);
    //ECZN.pool.VisitRecords(op);
    //MESG.pool.VisitRecords(op);
    //RGDL.pool.VisitRecords(op);
    //DOBJ.pool.VisitRecords(op);
    //LGTM.pool.VisitRecords(op);
    //MUSC.pool.VisitRecords(op);
    //IMOD.pool.VisitRecords(op);
    //REPU.pool.VisitRecords(op);
    //RCPE.pool.VisitRecords(op);
    //RCCT.pool.VisitRecords(op);
    //CHIP.pool.VisitRecords(op);
    //CSNO.pool.VisitRecords(op);
    //LSCT.pool.VisitRecords(op);
    //MSET.pool.VisitRecords(op);
    //ALOC.pool.VisitRecords(op);
    //CHAL.pool.VisitRecords(op);
    //AMEF.pool.VisitRecords(op);
    //CCRD.pool.VisitRecords(op);
    //CMNY.pool.VisitRecords(op);
    //CDCK.pool.VisitRecords(op);
    //DEHY.pool.VisitRecords(op);
    //HUNG.pool.VisitRecords(op);
    //SLPD.pool.VisitRecords(op);
    */

    return;
    }

void TES5File::VisitRecords(const UINT32 &RecordType, RecordOp &op)
    {
    if(Flags.IsNoLoad)
        {
        printer("TES5File::VisitRecords: Error - Unable to visit records in mod \"%s\". The mod is flagged not to be loaded.\n", ModName);
        return;
        }

    switch(RecordType)
        {
        case REV32(TES4):
            {
            Record *temp = &TES4;
            op.Accept(temp);
            }
        break;
    case REV32(LTEX):
        LTEX.pool.VisitRecords(op);
        break;
        case REV32(TXST):
            TXST.pool.VisitRecords(op);
            break;
        case REV32(MATT):
            MATT.pool.VisitRecords(op);
            break;
    case REV32(CELL):
        CELL.cell_pool.VisitRecords(op);
        break;
    case REV32(WRLD):
        WRLD.wrld_pool.VisitRecords(op);
        break;
    case REV32(LAND):
        WRLD.land_pool.VisitRecords(op);
        break;
    case REV32(WCEL):
        WRLD.cell_pool.VisitRecords(op);
        break;
        /*
        case REV32(GMST):
            GMST.pool.VisitRecords(op);
            break;
        case REV32(MICN):
            MICN.pool.VisitRecords(op);
            break;
        case REV32(GLOB):
            GLOB.pool.VisitRecords(op);
            break;
        case REV32(CLAS):
            CLAS.pool.VisitRecords(op);
            break;
        case REV32(FACT):
            FACT.pool.VisitRecords(op);
            break;
        case REV32(HDPT):
            HDPT.pool.VisitRecords(op);
            break;
        case REV32(HAIR):
            HAIR.pool.VisitRecords(op);
            break;
        case REV32(EYES):
            EYES.pool.VisitRecords(op);
            break;
        case REV32(RACE):
            RACE.pool.VisitRecords(op);
            break;
        case REV32(SOUN):
            SOUN.pool.VisitRecords(op);
            break;
        case REV32(ASPC):
            ASPC.pool.VisitRecords(op);
            break;
        case REV32(MGEF):
            MGEF.pool.VisitRecords(op);
            break;
        case REV32(SCPT):
            SCPT.pool.VisitRecords(op);
            break;
        case REV32(ENCH):
            ENCH.pool.VisitRecords(op);
            break;
        case REV32(SPEL):
            SPEL.pool.VisitRecords(op);
            break;
        case REV32(ACTI):
            ACTI.pool.VisitRecords(op);
            break;
        case REV32(TACT):
            TACT.pool.VisitRecords(op);
            break;
        case REV32(TERM):
            TERM.pool.VisitRecords(op);
            break;
        case REV32(ARMO):
            ARMO.pool.VisitRecords(op);
            break;
        case REV32(BOOK):
            BOOK.pool.VisitRecords(op);
            break;
        case REV32(CONT):
            CONT.pool.VisitRecords(op);
            break;
        case REV32(DOOR):
            DOOR.pool.VisitRecords(op);
            break;
        case REV32(INGR):
            INGR.pool.VisitRecords(op);
            break;
        case REV32(LIGH):
            LIGH.pool.VisitRecords(op);
            break;
        case REV32(MISC):
            MISC.pool.VisitRecords(op);
            break;
        case REV32(STAT):
            STAT.pool.VisitRecords(op);
            break;
        case REV32(SCOL):
            SCOL.pool.VisitRecords(op);
            break;
        case REV32(MSTT):
            MSTT.pool.VisitRecords(op);
            break;
        case REV32(PWAT):
            PWAT.pool.VisitRecords(op);
            break;
        case REV32(GRAS):
            GRAS.pool.VisitRecords(op);
            break;
        case REV32(TREE):
            TREE.pool.VisitRecords(op);
            break;
        case REV32(FURN):
            FURN.pool.VisitRecords(op);
            break;
        case REV32(WEAP):
            WEAP.pool.VisitRecords(op);
            break;
        case REV32(AMMO):
            AMMO.pool.VisitRecords(op);
            break;
        case REV32(NPC_):
            NPC_.pool.VisitRecords(op);
            break;
        case REV32(CREA):
            CREA.pool.VisitRecords(op);
            break;
        case REV32(LVLC):
            LVLC.pool.VisitRecords(op);
            break;
        case REV32(LVLN):
            LVLN.pool.VisitRecords(op);
            break;
        case REV32(KEYM):
            KEYM.pool.VisitRecords(op);
            break;
        case REV32(ALCH):
            ALCH.pool.VisitRecords(op);
            break;
        case REV32(IDLM):
            IDLM.pool.VisitRecords(op);
            break;
        case REV32(NOTE):
            NOTE.pool.VisitRecords(op);
            break;
        case REV32(COBJ):
            COBJ.pool.VisitRecords(op);
            break;
        case REV32(PROJ):
            PROJ.pool.VisitRecords(op);
            break;
        case REV32(LVLI):
            LVLI.pool.VisitRecords(op);
            break;
        case REV32(WTHR):
            WTHR.pool.VisitRecords(op);
            break;
        case REV32(CLMT):
            CLMT.pool.VisitRecords(op);
            break;
        case REV32(REGN):
            REGN.pool.VisitRecords(op);
            break;
        case REV32(NAVI):
            NAVI.pool.VisitRecords(op);
            break;
        case REV32(ACHR):
            CELL.achr_pool.VisitRecords(op);
            break;
        case REV32(ACRE):
            CELL.acre_pool.VisitRecords(op);
            break;
        case REV32(REFR):
            CELL.refr_pool.VisitRecords(op);
            break;
        case REV32(PGRE):
            CELL.pgre_pool.VisitRecords(op);
            break;
        case REV32(PMIS):
            CELL.pmis_pool.VisitRecords(op);
            break;
        case REV32(PBEA):
            CELL.pbea_pool.VisitRecords(op);
            break;
        case REV32(PFLA):
            CELL.pfla_pool.VisitRecords(op);
            break;
        case REV32(PCBE):
            CELL.pcbe_pool.VisitRecords(op);
            break;
        case REV32(NAVM):
            CELL.navm_pool.VisitRecords(op);
            break;
        case REV32(CLLS):
            CELL.cell_pool.VisitRecords(op);
            WRLD.cell_pool.VisitRecords(op);
            break;
        case REV32(DIAL):
            DIAL.dial_pool.VisitRecords(op);
            break;
        case REV32(INFO):
            DIAL.info_pool.VisitRecords(op);
            break;
        case REV32(QUST):
            QUST.pool.VisitRecords(op);
            break;
        case REV32(IDLE):
            IDLE.pool.VisitRecords(op);
            break;
        case REV32(PACK):
            PACK.pool.VisitRecords(op);
            break;
        case REV32(CSTY):
            CSTY.pool.VisitRecords(op);
            break;
        case REV32(LSCR):
            LSCR.pool.VisitRecords(op);
            break;
        case REV32(ANIO):
            ANIO.pool.VisitRecords(op);
            break;
        case REV32(WATR):
            WATR.pool.VisitRecords(op);
            break;
        case REV32(EFSH):
            EFSH.pool.VisitRecords(op);
            break;
        case REV32(EXPL):
            EXPL.pool.VisitRecords(op);
            break;
        case REV32(DEBR):
            DEBR.pool.VisitRecords(op);
            break;
        case REV32(IMGS):
            //IMGS.pool.VisitRecords(op);
            //break;
        case REV32(IMAD):
            //IMAD.pool.VisitRecords(op);
            //break;
        case REV32(FLST):
            //FLST.pool.VisitRecords(op);
            //break;
        case REV32(PERK):
            //PERK.pool.VisitRecords(op);
            //break;
        case REV32(BPTD):
            //BPTD.pool.VisitRecords(op);
            //break;
        case REV32(ADDN):
            //ADDN.pool.VisitRecords(op);
            //break;
        case REV32(AVIF):
            //AVIF.pool.VisitRecords(op);
            //break;
        case REV32(RADS):
            //RADS.pool.VisitRecords(op);
            //break;
        case REV32(CAMS):
            //CAMS.pool.VisitRecords(op);
            //break;
        case REV32(CPTH):
            //CPTH.pool.VisitRecords(op);
            //break;
        case REV32(VTYP):
            //VTYP.pool.VisitRecords(op);
            //break;
        case REV32(IPCT):
            //IPCT.pool.VisitRecords(op);
            //break;
        case REV32(IPDS):
            //IPDS.pool.VisitRecords(op);
            //break;
        case REV32(ARMA):
            //ARMA.pool.VisitRecords(op);
            //break;
        case REV32(ECZN):
            //ECZN.pool.VisitRecords(op);
            //break;
        case REV32(MESG):
            //MESG.pool.VisitRecords(op);
            //break;
        case REV32(RGDL):
            //RGDL.pool.VisitRecords(op);
            //break;
        case REV32(DOBJ):
            //DOBJ.pool.VisitRecords(op);
            //break;
        case REV32(LGTM):
            //LGTM.pool.VisitRecords(op);
            //break;
        case REV32(MUSC):
            //MUSC.pool.VisitRecords(op);
            //break;
        case REV32(IMOD):
            //IMOD.pool.VisitRecords(op);
            //break;
        case REV32(REPU):
            //REPU.pool.VisitRecords(op);
            //break;
        case REV32(RCPE):
            //RCPE.pool.VisitRecords(op);
            //break;
        case REV32(RCCT):
            //RCCT.pool.VisitRecords(op);
            //break;
        case REV32(CHIP):
            //CHIP.pool.VisitRecords(op);
            //break;
        case REV32(CSNO):
            //CSNO.pool.VisitRecords(op);
            //break;
        case REV32(LSCT):
            //LSCT.pool.VisitRecords(op);
            //break;
        case REV32(MSET):
            //MSET.pool.VisitRecords(op);
            //break;
        case REV32(ALOC):
            //ALOC.pool.VisitRecords(op);
            //break;
        case REV32(CHAL):
            //CHAL.pool.VisitRecords(op);
            //break;
        case REV32(AMEF):
            //AMEF.pool.VisitRecords(op);
            //break;
        case REV32(CCRD):
            //CCRD.pool.VisitRecords(op);
            //break;
        case REV32(CMNY):
            //CMNY.pool.VisitRecords(op);
            //break;
        case REV32(CDCK):
            //CDCK.pool.VisitRecords(op);
            //break;
        case REV32(DEHY):
            //DEHY.pool.VisitRecords(op);
            //break;
        case REV32(HUNG):
            //HUNG.pool.VisitRecords(op);
            //break;
        case REV32(SLPD):
            //SLPD.pool.VisitRecords(op);
            //break;
        */
        default:
            printer("TES5File::VisitRecords: Error - Unable to visit record type (%c%c%c%c) in mod \"%s\". Unknown record type.\n", ((STRING)&RecordType)[0], ((STRING)&RecordType)[1], ((STRING)&RecordType)[2], ((STRING)&RecordType)[3], ModName);
            break;
        }
    return;
    }