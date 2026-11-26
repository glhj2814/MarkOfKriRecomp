
========== D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp ==========
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:32:        case COP1_CF:
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:33:            if (fs == 31)
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:34:                return fmt::format("SET_GPR_U32(ctx, {}, ctx->fcr31);", ft); // FCR31 contains status/control
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:35:            if (fs == 0)
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:36:                return fmt::format("SET_GPR_U32(ctx, {}, 0x00000000);", ft); // FCR0 is the FPU implementation register
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:37:            return fmt::format("SET_GPR_U32(ctx, {}, 0); // Unimplemented FCR{}", ft, fs);
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:38:        case COP1_CT:
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:39:            if (fs == 31)
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:40:                return fmt::format("ctx->fcr31 = GPR_U32(ctx, {}) & 0x0183FFFF;", ft);
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:41:            else
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:42:                return fmt::format("// CTC1 to FCR{} ignored", fs);
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:43:            return "";
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:55:            case COP1_S_DIV:
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:56:                // The EE has no Inf/NaN: x/0 gives +-max (sign of fs xor ft), see ps2_fdiv.
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:57:                return fmt::format("{{ if (ctx->f[{}] == 0.0f) ctx->fcr31 |= 0x100000; /* DZ flag */ "
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:58:                                   "ctx->f[{}] = FPU_DIV_S(ctx->f[{}], ctx->f[{}]); }}",
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:59:                                   ft, fd, fs, ft);
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:60:            case COP1_S_SQRT:
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:90:            case COP1_S_MIN:
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:91:                return fmt::format("ctx->f[{}] = std::min(ctx->f[{}], ctx->f[{}]);", fd, fs, ft);
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:92:            case COP1_S_C_F:
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:93:                return fmt::format("ctx->fcr31 &= ~0x800000;");
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:94:            case COP1_S_C_UN:
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:95:                return fmt::format("ctx->fcr31 = (FPU_C_UN_S(ctx->f[{}], ctx->f[{}])) ? (ctx->fcr31 | 0x800000) : (ctx->fcr31 & ~0x800000);", fs, ft);
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:96:            case COP1_S_C_EQ:
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:97:                return fmt::format("ctx->fcr31 = (FPU_C_EQ_S(ctx->f[{}], ctx->f[{}])) ? (ctx->fcr31 | 0x800000) : (ctx->fcr31 & ~0x800000);", fs, ft);
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:98:            case COP1_S_C_UEQ:
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:99:                return fmt::format("ctx->fcr31 = (FPU_C_UEQ_S(ctx->f[{}], ctx->f[{}])) ? (ctx->fcr31 | 0x800000) : (ctx->fcr31 & ~0x800000);", fs, ft);
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:100:            case COP1_S_C_OLT:
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:101:                return fmt::format("ctx->fcr31 = (FPU_C_OLT_S(ctx->f[{}], ctx->f[{}])) ? (ctx->fcr31 | 0x800000) : (ctx->fcr31 & ~0x800000);", fs, ft);
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:102:            case COP1_S_C_ULT:
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:103:                return fmt::format("ctx->fcr31 = (FPU_C_ULT_S(ctx->f[{}], ctx->f[{}])) ? (ctx->fcr31 | 0x800000) : (ctx->fcr31 & ~0x800000);", fs, ft);
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:104:            case COP1_S_C_OLE:
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:105:                return fmt::format("ctx->fcr31 = (FPU_C_OLE_S(ctx->f[{}], ctx->f[{}])) ? (ctx->fcr31 | 0x800000) : (ctx->fcr31 & ~0x800000);", fs, ft);
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:106:            case COP1_S_C_ULE:
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:107:                return fmt::format("ctx->fcr31 = (FPU_C_ULE_S(ctx->f[{}], ctx->f[{}])) ? (ctx->fcr31 | 0x800000) : (ctx->fcr31 & ~0x800000);", fs, ft);
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:108:            case COP1_S_C_SF:
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:109:                return fmt::format("ctx->fcr31 &= ~0x800000;");
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:110:            case COP1_S_C_NGLE:
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:111:                return fmt::format("ctx->fcr31 = (FPU_C_NGLE_S(ctx->f[{}], ctx->f[{}])) ? (ctx->fcr31 | 0x800000) : (ctx->fcr31 & ~0x800000);", fs, ft);
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:112:            case COP1_S_C_SEQ:
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:113:                return fmt::format("ctx->fcr31 = (FPU_C_SEQ_S(ctx->f[{}], ctx->f[{}])) ? (ctx->fcr31 | 0x800000) : (ctx->fcr31 & ~0x800000);", fs, ft);
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:114:            case COP1_S_C_NGL:
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:115:                return fmt::format("ctx->fcr31 = (FPU_C_NGL_S(ctx->f[{}], ctx->f[{}])) ? (ctx->fcr31 | 0x800000) : (ctx->fcr31 & ~0x800000);", fs, ft);
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:116:            case COP1_S_C_LT:
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:117:                return fmt::format("ctx->fcr31 = (FPU_C_LT_S(ctx->f[{}], ctx->f[{}])) ? (ctx->fcr31 | 0x800000) : (ctx->fcr31 & ~0x800000);", fs, ft);
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:118:            case COP1_S_C_NGE:
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:119:                return fmt::format("ctx->fcr31 = (FPU_C_NGE_S(ctx->f[{}], ctx->f[{}])) ? (ctx->fcr31 | 0x800000) : (ctx->fcr31 & ~0x800000);", fs, ft);
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:120:            case COP1_S_C_LE:
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:121:                return fmt::format("ctx->fcr31 = (FPU_C_LE_S(ctx->f[{}], ctx->f[{}])) ? (ctx->fcr31 | 0x800000) : (ctx->fcr31 & ~0x800000);", fs, ft);
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:122:            case COP1_S_C_NGT:
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:123:                return fmt::format("ctx->fcr31 = (FPU_C_NGT_S(ctx->f[{}], ctx->f[{}])) ? (ctx->fcr31 | 0x800000) : (ctx->fcr31 & ~0x800000);", fs, ft);
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:124:            default:
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:125:                return m_codeGenerator.emitUnhandledInstruction(inst, fmt::format("Unhandled FPU.S instruction: function 0x{:X}", function));
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:126:            }

========== D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp ==========
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:25:        uint32_t function;
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:26:    } ops[] = {
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:27:        {"generated_fpu_adda", COP1_S_ADDA},
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:28:        {"generated_fpu_suba", COP1_S_SUBA},
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:29:        {"generated_fpu_mula", COP1_S_MULA},
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:30:        {"generated_fpu_madd", COP1_S_MADD},
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:31:        {"generated_fpu_msub", COP1_S_MSUB},
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:32:        {"generated_fpu_madda", COP1_S_MADDA},
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:33:        {"generated_fpu_msuba", COP1_S_MSUBA}
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:34:    };
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:35:
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:36:    const struct Op scalarOps[] = {
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:37:        {"generated_fpu_add", COP1_S_ADD},
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:38:        {"generated_fpu_sub", COP1_S_SUB},
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:39:        {"generated_fpu_mul", COP1_S_MUL},
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:40:        {"generated_fpu_div", COP1_S_DIV},
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:41:        {"generated_fpu_sqrt", COP1_S_SQRT},
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:42:        {"generated_fpu_abs", COP1_S_ABS},
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:43:        {"generated_fpu_mov", COP1_S_MOV},
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:44:        {"generated_fpu_neg", COP1_S_NEG},
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:45:        {"generated_fpu_rsqrt", COP1_S_RSQRT},
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:46:        {"generated_fpu_max", COP1_S_MAX},
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:47:        {"generated_fpu_min", COP1_S_MIN},
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:48:        {"generated_fpu_cvt_w", COP1_S_CVT_W}
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:49:    };
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:50:    std::vector<Symbol> symbols;
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:51:    std::vector<Section> sections;
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:54:    std::unordered_map<uint32_t, std::string> names;
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:55:    std::vector<Function> functions;
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:56:    std::vector<std::vector<Instruction>> instructionSets;
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:57:
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:58:    constexpr uint32_t base = 0x00100000u;
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:59:    for (size_t i = 0; i < std::size(ops); ++i)
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:78:        names.emplace(address, ops[i].name);
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:79:        functions.push_back(function);
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:80:        instructionSets.push_back({inst});
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:81:    }
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:82:
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:83:    constexpr uint32_t sequenceAddress = base + 0x70u;
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:102:
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:103:    Function sequence{};
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:104:    sequence.name = "generated_fpu_sequence_mula_madda";
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:105:    sequence.start = sequenceAddress;
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:106:    sequence.end = sequenceAddress + 8u;
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:107:    sequence.instructions.push_back(mula);
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:110:    names.emplace(sequenceAddress, sequence.name);
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:111:
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:112:    for (size_t i = 0; i < std::size(scalarOps); ++i)
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:113:    {
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:114:        const uint32_t address =
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:115:            base + 0x80u + static_cast<uint32_t>(i * 0x10u);
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:122:        inst.rd = 1;
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:123:        inst.sa = 3;
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:124:        inst.function = scalarOps[i].function;
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:125:
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:126:        Function function{};
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:127:        function.name = scalarOps[i].name;
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:128:        function.start = address;
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:129:        function.end = address + 4u;
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:130:        function.instructions.push_back(inst);
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:131:
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:132:        names.emplace(address, scalarOps[i].name);
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:133:        functions.push_back(function);
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:134:        instructionSets.push_back({inst});
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:135:    }
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:136:    generator.setRenamedFunctions(names);
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:137:    generator.setEmitInstructionComments(false);
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:148:    {
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:149:        const std::string emitted =
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:150:            generator.generateFunction(functions[i], instructionSets[i], false);
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:151:
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:152:        if (emitted.find("runtime->") != std::string::npos ||
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generate_fpu_execution_fixture.cpp:153:            emitted.find("runtime.") != std::string::npos)

========== D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp ==========
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:9:    void (*)(uint8_t*, R5900Context*, PS2Runtime*);
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:10:
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:11:void generated_fpu_adda(uint8_t*, R5900Context*, PS2Runtime*);
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:12:void generated_fpu_suba(uint8_t*, R5900Context*, PS2Runtime*);
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:13:void generated_fpu_mula(uint8_t*, R5900Context*, PS2Runtime*);
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:14:void generated_fpu_madd(uint8_t*, R5900Context*, PS2Runtime*);
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:15:void generated_fpu_msub(uint8_t*, R5900Context*, PS2Runtime*);
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:16:void generated_fpu_madda(uint8_t*, R5900Context*, PS2Runtime*);
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:17:void generated_fpu_msuba(uint8_t*, R5900Context*, PS2Runtime*);
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:18:void generated_fpu_add(uint8_t*, R5900Context*, PS2Runtime*);
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:19:void generated_fpu_sub(uint8_t*, R5900Context*, PS2Runtime*);
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:20:void generated_fpu_mul(uint8_t*, R5900Context*, PS2Runtime*);
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:21:void generated_fpu_div(uint8_t*, R5900Context*, PS2Runtime*);
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:22:void generated_fpu_sqrt(uint8_t*, R5900Context*, PS2Runtime*);
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:23:void generated_fpu_abs(uint8_t*, R5900Context*, PS2Runtime*);
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:24:void generated_fpu_mov(uint8_t*, R5900Context*, PS2Runtime*);
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:25:void generated_fpu_neg(uint8_t*, R5900Context*, PS2Runtime*);
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:26:void generated_fpu_rsqrt(uint8_t*, R5900Context*, PS2Runtime*);
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:27:void generated_fpu_max(uint8_t*, R5900Context*, PS2Runtime*);
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:28:void generated_fpu_min(uint8_t*, R5900Context*, PS2Runtime*);
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:29:void generated_fpu_cvt_w(uint8_t*, R5900Context*, PS2Runtime*);
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:30:void generated_fpu_sequence_mula_madda(uint8_t*, R5900Context*, PS2Runtime*);
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:31:
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:32:static R5900Context makeGeneratedFpuContext()
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:33:{
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:40:}
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:41:
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:42:void register_generated_fpu_execution_tests()
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:43:{
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:44:    MiniTest::Case("GeneratedFPUExecution", [](TestCase& tc)
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:45:    {
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:47:            auto ctx = makeGeneratedFpuContext();
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:48:            ctx.f_acc = 9.0f;
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:49:            generated_fpu_adda(nullptr, &ctx, nullptr);
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:50:            t.Equals(ctx.f_acc, 5.0f, "ADDA.S overwrites prior accumulator");
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:51:            t.Equals(ctx.pc, 0x100004u, "ADDA.S final PC");
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:52:        });
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:54:        tc.Run("generated SUBA.S updates live accumulator", [](TestCase& t) {
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:55:            auto ctx = makeGeneratedFpuContext();
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:56:            generated_fpu_suba(nullptr, &ctx, nullptr);
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:57:            t.Equals(ctx.f_acc, -1.0f, "SUBA.S accumulator");
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:58:            t.Equals(ctx.pc, 0x100014u, "SUBA.S final PC");
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:59:        });
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:61:        tc.Run("generated MULA.S updates live accumulator", [](TestCase& t) {
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:62:            auto ctx = makeGeneratedFpuContext();
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:63:            generated_fpu_mula(nullptr, &ctx, nullptr);
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:64:            t.Equals(ctx.f_acc, 6.0f, "MULA.S accumulator");
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:65:            t.Equals(ctx.pc, 0x100024u, "MULA.S final PC");
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:66:        });
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:68:        tc.Run("generated MADD.S writes destination FPR", [](TestCase& t) {
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:69:            auto ctx = makeGeneratedFpuContext();
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:70:            generated_fpu_madd(nullptr, &ctx, nullptr);
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:71:            t.Equals(ctx.f[3], 11.0f, "MADD.S destination");
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:72:            t.Equals(ctx.pc, 0x100034u, "MADD.S final PC");
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:73:        });
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:75:        tc.Run("generated MSUB.S writes destination FPR", [](TestCase& t) {
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:76:            auto ctx = makeGeneratedFpuContext();
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:77:            generated_fpu_msub(nullptr, &ctx, nullptr);
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:78:            t.Equals(ctx.f[3], -1.0f, "MSUB.S destination");
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:79:            t.Equals(ctx.pc, 0x100044u, "MSUB.S final PC");
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:80:        });
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:82:        tc.Run("generated MADDA.S updates live accumulator", [](TestCase& t) {
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:83:            auto ctx = makeGeneratedFpuContext();
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:84:            generated_fpu_madda(nullptr, &ctx, nullptr);
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:85:            t.Equals(ctx.f_acc, 11.0f, "MADDA.S accumulator");
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:86:            t.Equals(ctx.pc, 0x100054u, "MADDA.S final PC");
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:87:        });
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:89:        tc.Run("generated MSUBA.S updates live accumulator", [](TestCase& t) {
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:90:            auto ctx = makeGeneratedFpuContext();
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:91:            generated_fpu_msuba(nullptr, &ctx, nullptr);
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:92:            t.Equals(ctx.f_acc, -1.0f, "MSUBA.S accumulator");
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:93:            t.Equals(ctx.pc, 0x100064u, "MSUBA.S final PC");
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:94:        });
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:96:        tc.Run("generated ADD.S writes destination FPR", [](TestCase& t) {
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:97:            auto ctx = makeGeneratedFpuContext();
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:98:            generated_fpu_add(nullptr, &ctx, nullptr);
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:99:            t.Equals(ctx.f[3], 5.0f, "ADD.S destination");
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:100:            t.Equals(ctx.pc, 0x100084u, "ADD.S final PC");
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:101:        });
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:102:        tc.Run("generated SUB.S writes destination FPR", [](TestCase& t) {
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:103:            auto ctx = makeGeneratedFpuContext();
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:104:            generated_fpu_sub(nullptr, &ctx, nullptr);
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:105:            t.Equals(ctx.f[3], -1.0f, "SUB.S destination");
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:106:            t.Equals(ctx.pc, 0x100094u, "SUB.S final PC");
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:107:        });
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:108:        tc.Run("generated MUL.S writes destination FPR", [](TestCase& t) {
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:109:            auto ctx = makeGeneratedFpuContext();
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:110:            generated_fpu_mul(nullptr, &ctx, nullptr);
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:111:            t.Equals(ctx.f[3], 6.0f, "MUL.S destination");
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:112:            t.Equals(ctx.pc, 0x1000A4u, "MUL.S final PC");
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:113:        });
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:114:        tc.Run("generated DIV.S writes destination FPR", [](TestCase& t) {
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:115:            auto ctx = makeGeneratedFpuContext();
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:116:            generated_fpu_div(nullptr, &ctx, nullptr);
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:117:            t.Equals(ctx.f[3], 0.6666667f, "DIV.S destination");
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:118:            t.Equals(ctx.pc, 0x1000B4u, "DIV.S final PC");
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:119:        });
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:120:        tc.Run("generated SQRT.S reads ft", [](TestCase& t) {
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:121:            auto ctx = makeGeneratedFpuContext();
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:122:            generated_fpu_sqrt(nullptr, &ctx, nullptr);
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:123:            t.Equals(ctx.f[3], 1.7320508f, "SQRT.S destination");
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:124:            t.Equals(ctx.pc, 0x1000C4u, "SQRT.S final PC");
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:125:        });
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:127:            auto ctx = makeGeneratedFpuContext();
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:128:            ctx.f[1] = -2.0f;
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:129:            generated_fpu_abs(nullptr, &ctx, nullptr);
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:130:            t.Equals(ctx.f[3], 2.0f, "ABS.S destination");
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:131:            t.Equals(ctx.pc, 0x1000D4u, "ABS.S final PC");
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:132:        });
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:133:        tc.Run("generated MOV.S writes destination FPR", [](TestCase& t) {
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:134:            auto ctx = makeGeneratedFpuContext();
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:135:            generated_fpu_mov(nullptr, &ctx, nullptr);
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:136:            t.Equals(ctx.f[3], 2.0f, "MOV.S destination");
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:137:            t.Equals(ctx.pc, 0x1000E4u, "MOV.S final PC");
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:138:        });
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:139:        tc.Run("generated NEG.S writes destination FPR", [](TestCase& t) {
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:140:            auto ctx = makeGeneratedFpuContext();
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:141:            generated_fpu_neg(nullptr, &ctx, nullptr);
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:142:            t.Equals(ctx.f[3], -2.0f, "NEG.S destination");
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:143:            t.Equals(ctx.pc, 0x1000F4u, "NEG.S final PC");
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:144:        });
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:145:        tc.Run("generated RSQRT.S writes destination FPR", [](TestCase& t) {
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:146:            auto ctx = makeGeneratedFpuContext();
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:147:            generated_fpu_rsqrt(nullptr, &ctx, nullptr);
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:148:            t.Equals(ctx.f[3], 1.1547005f, "RSQRT.S destination");
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:149:            t.Equals(ctx.pc, 0x100104u, "RSQRT.S final PC");
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:150:        });
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:151:        tc.Run("generated MAX.S writes destination FPR", [](TestCase& t) {
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:152:            auto ctx = makeGeneratedFpuContext();
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:153:            generated_fpu_max(nullptr, &ctx, nullptr);
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:154:            t.Equals(ctx.f[3], 3.0f, "MAX.S destination");
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:155:            t.Equals(ctx.pc, 0x100114u, "MAX.S final PC");
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:156:        });
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:157:        tc.Run("generated MIN.S writes destination FPR", [](TestCase& t) {
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:158:            auto ctx = makeGeneratedFpuContext();
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:159:            generated_fpu_min(nullptr, &ctx, nullptr);
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:160:            t.Equals(ctx.f[3], 2.0f, "MIN.S destination");
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:161:            t.Equals(ctx.pc, 0x100124u, "MIN.S final PC");
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:162:        });
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:182:
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:183:            const Case cases[] = {
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:184:                { generated_fpu_max, "MAX.S NaN fs", 0x7FC00000u, 0x3F800000u, 0x7FC00000u },
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:185:                { generated_fpu_max, "MAX.S NaN ft", 0x3F800000u, 0x7FC00000u, 0x3F800000u },
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:186:                { generated_fpu_min, "MIN.S NaN fs", 0x7FC00000u, 0x3F800000u, 0x7FC00000u },
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:187:                { generated_fpu_min, "MIN.S NaN ft", 0x3F800000u, 0x7FC00000u, 0x3F800000u }
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:188:            };
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:189:
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:190:            for (const auto& test : cases) {
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:213:
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:214:            const Case cases[] = {
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:215:                { generated_fpu_max, "MAX.S +0 fs, -0 ft", 0x00000000u, 0x80000000u, 0x00000000u },
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:216:                { generated_fpu_max, "MAX.S -0 fs, +0 ft", 0x80000000u, 0x00000000u, 0x80000000u },
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:217:                { generated_fpu_min, "MIN.S +0 fs, -0 ft", 0x00000000u, 0x80000000u, 0x00000000u },
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:218:                { generated_fpu_min, "MIN.S -0 fs, +0 ft", 0x80000000u, 0x00000000u, 0x80000000u }
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:219:            };
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:220:
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:221:            for (const auto& test : cases) {
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:227:            }
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:228:        });
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:229:        tc.Run("generated CVT.W.S truncates toward zero independent of FCR31 rounding mode", [](TestCase& t) {
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:230:            const float inputs[] = { 3.75f, -3.75f, 2.5f, -2.5f };
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:231:            const int32_t expected[] = { 3, -3, 2, -2 };
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:232:
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:235:                    auto ctx = makeGeneratedFpuContext();
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:236:                    ctx.f[1] = inputs[i];
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:237:                    ctx.fcr31 = mode;
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:238:                    generated_fpu_cvt_w(nullptr, &ctx, nullptr);
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:239:
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:240:                    int32_t actual = 0;
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:241:                    std::memcpy(&actual, &ctx.f[3], sizeof(actual));
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:242:                    t.Equals(actual, expected[i],
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:243:                        "CVT.W.S truncation result for FCR31 mode " + std::to_string(mode));
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:244:                }
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:245:            }
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:246:        });
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:271:                    auto ctx = makeGeneratedFpuContext();
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:272:                    ctx.f[1] = input;
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:273:                    ctx.fcr31 = mode;
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:274:                    generated_fpu_cvt_w(nullptr, &ctx, nullptr);
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:275:
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:276:                    int32_t actual = 0;
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:277:                    std::memcpy(&actual, &ctx.f[3], sizeof(actual));
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:278:
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:279:                    t.Equals(actual, edge.expected,
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:280:                        std::string(edge.label) + " (FCR31 mode " +
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:281:                        std::to_string(mode) + ")");
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:282:                }
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:283:            }
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:286:            auto ctx = makeGeneratedFpuContext();
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:287:            ctx.f_acc = 99.0f;
> D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:288:            generated_fpu_sequence_mula_madda(nullptr, &ctx, nullptr);
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:289:            t.Equals(ctx.f_acc, 12.0f, "MADDA.S consumes MULA.S accumulator");
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:290:            t.Equals(ctx.pc, 0x100078u, "two-instruction sequence final PC");
  D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\generated_fpu_execution_tests.cpp:291:        });
