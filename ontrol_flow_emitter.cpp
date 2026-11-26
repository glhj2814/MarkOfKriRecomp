
========== D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\control_flow_emitter.cpp (1-390) ==========
    1: #include "ps2recomp/Emitters/control_flow_emitter.h"
    2: 
    3: #include "ps2recomp/control_flow_utils.h"
    4: #include "ps2recomp/instructions.h"
    5: #include "ps2recomp/r5900_decoder.h"
    6: #include "ps2_runtime_calls.h"
    7: 
    8: #include <algorithm>
    9: #include <fmt/format.h>
   10: #include <sstream>
   11: #include <utility>
   12: 
   13: namespace ps2recomp
   14: {
   15:     ControlFlowEmitter::ControlFlowEmitter(CodeGenerator &generator,
   16:                                            const Instruction &branchInst,
   17:                                            const Instruction &delaySlot,
   18:                                            const Function &function,
   19:                                            const CodeGenerator::AnalysisResult &analysisResult,
   20:                                            std::string delaySlotOverride)
   21:         : m_gen(generator),
   22:           m_branchInst(branchInst),
   23:           m_delaySlot(delaySlot),
   24:           m_function(function),
   25:           m_analysisResult(analysisResult),
   26:           m_delaySlotOverride(std::move(delaySlotOverride))
   27:     {
   28:     }
   29: 
   30:     uint32_t ControlFlowEmitter::branchPc() const
   31:     {
   32:         return m_branchInst.address;
   33:     }
   34: 
   35:     uint32_t ControlFlowEmitter::delayPc() const
   36:     {
   37:         return m_branchInst.address + 4u;
   38:     }
   39: 
   40:     uint32_t ControlFlowEmitter::fallthroughPc() const
   41:     {
   42:         return m_branchInst.address + 8u;
   43:     }
   44: 
   45:     bool ControlFlowEmitter::hasRealDelaySlot() const
   46:     {
   47:         return !m_delaySlotOverride.empty() || !isGuestNop(m_delaySlot);
   48:     }
   49: 
   50:     bool ControlFlowEmitter::isCallLikeEdge() const
   51:     {
   52:         return (m_branchInst.opcode == OPCODE_JAL) ||
   53:                (m_branchInst.opcode == OPCODE_SPECIAL && m_branchInst.function == SPECIAL_JALR);
   54:     }
   55: 
   56:     bool ControlFlowEmitter::isInternalTarget(uint32_t target) const
   57:     {
   58:         return m_analysisResult.entryPoints.contains(target);
   59:     }
   60: 
   61:     bool ControlFlowEmitter::isLikelyBranch() const
   62:     {
   63:         return (m_branchInst.opcode == OPCODE_BEQL || m_branchInst.opcode == OPCODE_BNEL ||
   64:                 m_branchInst.opcode == OPCODE_BLEZL || m_branchInst.opcode == OPCODE_BGTZL ||
   65:                 (m_branchInst.opcode == OPCODE_REGIMM &&
   66:                  (m_branchInst.rt == REGIMM_BLTZL || m_branchInst.rt == REGIMM_BGEZL ||
   67:                   m_branchInst.rt == REGIMM_BLTZALL || m_branchInst.rt == REGIMM_BGEZALL)) ||
   68:                 (m_branchInst.opcode == OPCODE_COP1 && m_branchInst.rs == COP1_BC &&
   69:                  (m_branchInst.rt == COP1_BC_BCFL || m_branchInst.rt == COP1_BC_BCTL)) ||
   70:                 (m_branchInst.opcode == OPCODE_COP2 && m_branchInst.rs == COP2_BC &&
   71:                  (m_branchInst.rt == COP2_BC_BCFL || m_branchInst.rt == COP2_BC_BCTL)));
   72:     }
   73: 
   74:     std::vector<uint32_t> ControlFlowEmitter::resolvedLocalIndirectTargets() const
   75:     {
   76:         if (m_branchInst.opcode != OPCODE_SPECIAL)
   77:         {
   78:             return {};
   79:         }
   80: 
   81:         if (!((m_branchInst.function == SPECIAL_JR && m_branchInst.rs != 31u) ||
   82:               m_branchInst.function == SPECIAL_JALR))
   83:         {
   84:             return {};
   85:         }
   86: 
   87:         auto jtIt = m_analysisResult.jumpTableTargets.find(m_branchInst.address);
   88:         if (jtIt == m_analysisResult.jumpTableTargets.end())
   89:         {
   90:             return {};
   91:         }
   92: 
   93:         std::vector<uint32_t> targets = jtIt->second;
   94:         std::sort(targets.begin(), targets.end());
   95:         targets.erase(std::unique(targets.begin(), targets.end()), targets.end());
   96:         return targets;
   97:     }
   98: 
   99:     std::string ControlFlowEmitter::delaySlotCode() const
  100:     {
  101:         if (!hasRealDelaySlot())
  102:         {
  103:             return {};
  104:         }
  105: 
  106:         if (!m_delaySlotOverride.empty())
  107:         {
  108:             return m_delaySlotOverride;
  109:         }
  110: 
  111:         std::string code;
  112:         if (m_gen.m_emitInstructionComments)
  113:         {
  114:             code = "// 0x" + fmt::format("{:x}", m_delaySlot.address) + ": 0x" + fmt::format("{:x}", m_delaySlot.raw);
  115:             std::string disassembly = R5900Decoder::disassembleInstruction(m_delaySlot);
  116:             if (!disassembly.empty())
  117:             {
  118:                 code += "  " + disassembly;
  119:             }
  120:             code += " (Delay Slot)\n";
  121:         }
  122: 
  123:         code += m_gen.translateInstruction(m_delaySlot);
  124:         return code;
  125:     }
  126: 
  127:     void ControlFlowEmitter::emitDelaySlot(std::string_view indent)
  128:     {
  129:         if (!hasRealDelaySlot())
  130:         {
  131:             return;
  132:         }
  133: 
  134:         m_ss << fmt::format("{}ctx->pc = 0x{:X}u;\n", indent, delayPc());
  135:         m_ss << fmt::format("{}ctx->in_delay_slot = true;\n", indent);
  136:         m_ss << fmt::format("{}ctx->branch_pc = 0x{:X}u;\n", indent, branchPc());
  137: 
  138:         const std::string code = delaySlotCode();
  139:         std::istringstream lines(code);
  140:         std::string line;
  141:         while (std::getline(lines, line))
  142:         {
  143:             if (!line.empty())
  144:             {
  145:                 m_ss << indent << line << "\n";
  146:             }
  147:         }
  148: 
  149:         m_ss << fmt::format("{}ctx->in_delay_slot = false;\n", indent);
  150:     }
  151: 
  152:     void ControlFlowEmitter::emitResumeFromDelaySlotEntry()
  153:     {
  154:         if (!isInternalTarget(delayPc()))
  155:         {
  156:             return;
  157:         }
  158: 
  159:         m_ss << fmt::format("    if (ctx->pc == 0x{:X}u) {{\n", delayPc());
  160:         emitDelaySlot("        ");
  161:         m_ss << fmt::format("        ctx->pc = 0x{:X}u;\n", fallthroughPc());
  162: 
  163:         if (isInternalTarget(fallthroughPc()))
  164:         {
  165:             m_ss << fmt::format("        goto label_{:x};\n", fallthroughPc());
  166:         }
  167:         else
  168:         {
  169:             m_ss << fmt::format("        goto label_fallthrough_0x{:x};\n", branchPc());
  170:         }
  171: 
  172:         m_ss << "    }\n";
  173:     }
  174: 
  175:     void ControlFlowEmitter::emitInternalTarget(uint32_t target, uint32_t sourcePc, std::string_view indent)
  176:     {
  177:         m_ss << fmt::format("{}ctx->pc = 0x{:X}u;\n", indent, target);
  178:         if (target <= sourcePc && !isCallLikeEdge())
  179:         {
  180:             m_ss << fmt::format("{}if (runtime->eeCheckpointDue()) {{\n", indent);
  181:             m_ss << fmt::format("{}    return;\n", indent);
  182:             m_ss << fmt::format("{}}}\n", indent);
  183:         }
  184:         m_ss << fmt::format("{}goto label_{:x};\n", indent, target);
  185:     }
  186: 
  187:     void ControlFlowEmitter::emitRuntimeBranchDispatch(std::string_view targetExpression,
  188:                                                        uint32_t sourcePc,
  189:                                                        uint32_t returnPc,
  190:                                                        std::string_view runtimeKind,
  191:                                                        std::string_view debugName,
  192:                                                        std::string_view indent,
  193:                                                        bool returnOnTransfer)
  194:     {
  195:         m_ss << fmt::format(
  196:             "{}if (!runtime->dispatchGuestBranch(rdram, ctx, {}, 0x{:X}u, 0x{:X}u, PS2Runtime::GuestBranchKind::{}, \"{}\")) {{\n",
  197:             indent,
  198:             targetExpression,
  199:             sourcePc,
  200:             returnPc,
  201:             runtimeKind,
  202:             debugName);
  203:         if (returnOnTransfer)
  204:         {
  205:             m_ss << fmt::format("{}    return;\n", indent);
  206:         }
  207:         m_ss << fmt::format("{}}}\n", indent);
  208:     }
  209: 
  210:     bool ControlFlowEmitter::emitDirectFunctionJumpIfAvailable(uint32_t target, StaticBranchKind kind, std::string_view indent)
  211:     {
  212:         if (kind != StaticBranchKind::Jump)
  213:         {
  214:             return false;
  215:         }
  216: 
  217:         const std::string functionName = m_gen.getFunctionName(target);
  218:         if (functionName.empty())
  219:         {
  220:             return false;
  221:         }
  222: 
  223:         m_ss << indent << functionName << "(rdram, ctx, runtime); return;\n";
  224:         return true;
  225:     }
  226: 
  227:     void ControlFlowEmitter::emitExternalJumpDispatch(uint32_t target, StaticBranchKind kind, std::string_view indent)
  228:     {
  229:         const bool isCall = kind == StaticBranchKind::Call;
  230:         emitRuntimeBranchDispatch(fmt::format("0x{:X}u", target),
  231:                                   branchPc(),
  232:                                   isCall ? fallthroughPc() : 0u,
  233:                                   isCall ? "DirectCall" : "DirectJump",
  234:                                   isCall ? "JAL" : "J",
  235:                                   indent,
  236:                                   true);
  237:     }
  238: 
  239:     void ControlFlowEmitter::emitExternalRegisterCallDispatch(std::string_view jumpTargetExpression, std::string_view indent)
  240:     {
  241:         emitRuntimeBranchDispatch(jumpTargetExpression,
  242:                                   branchPc(),
  243:                                   fallthroughPc(),
  244:                                   "IndirectCall",
  245:                                   "JALR",
  246:                                   indent,
  247:                                   true);
  248:     }
  249: 
  250:     void ControlFlowEmitter::emitExternalRegisterJumpDispatch(std::string_view jumpTargetExpression,
  251:                                                               RegisterBranchKind kind,
  252:                                                               uint8_t rsReg,
  253:                                                               std::string_view indent)
  254:     {
  255:         const bool isReturn = kind == RegisterBranchKind::Jump && rsReg == 31u;
  256: 
  257:         if (isReturn)
  258:         {
  259:             m_ss << indent << "#if defined(PS2X_STRICT_RETURN_DIAGNOSTICS) && PS2X_STRICT_RETURN_DIAGNOSTICS\n";
  260:             m_ss << indent << "(void)runtime->dispatchGuestBranch(rdram, ctx, " << jumpTargetExpression
  261:                  << ", 0x" << fmt::format("{:X}", branchPc())
  262:                  << "u, 0u, PS2Runtime::GuestBranchKind::Return, \"JR $ra\");\n";
  263:             m_ss << indent << "return;\n";
  264:             m_ss << indent << "#else\n";
  265:             m_ss << indent << "ctx->pc = " << jumpTargetExpression << ";\n";
  266:             m_ss << indent << "return;\n";
  267:             m_ss << indent << "#endif\n";
  268:             return;
  269:         }
  270: 
  271:         emitRuntimeBranchDispatch(jumpTargetExpression,
  272:                                   branchPc(),
  273:                                   0u,
  274:                                   "IndirectJump",
  275:                                   "JR",
  276:                                   indent,
  277:                                   true);
  278:     }
  279: 
  280:     bool ControlFlowEmitter::emitRelocationCallIfAvailable(StaticBranchKind kind, std::string_view indent)
  281:     {
  282:         const auto relocIt = m_gen.m_relocationCallNames.find(m_branchInst.address);
  283:         if (relocIt == m_gen.m_relocationCallNames.end() || relocIt->second.empty())
  284:         {
  285:             return false;
  286:         }
  287: 
  288:         const std::string_view resolvedSyscallName = ps2_runtime_calls::resolveSyscallName(relocIt->second);
  289:         const std::string_view resolvedStubName = ps2_runtime_calls::resolveStubName(relocIt->second);
  290:         if (resolvedSyscallName.empty() && resolvedStubName.empty())
  291:         {
  292:             return false;
  293:         }
  294: 
  295:         const bool isSyscall = !resolvedSyscallName.empty();
  296:         const std::string_view handlerName = isSyscall ? resolvedSyscallName : resolvedStubName;
  297: 
  298:         m_ss << indent << "{\n";
  299:         if (kind == StaticBranchKind::Call)
  300:         {
  301:             m_ss << fmt::format("{}    ctx->pc = 0x{:X}u;\n", indent, fallthroughPc());
  302:         }
  303:         else
  304:         {
  305:             m_ss << indent << "    ctx->pc = getRegU32(ctx, 31);\n";
  306:         }
  307:         m_ss << indent << "    " << (isSyscall ? "ps2_syscalls::" : "ps2_stubs::")
  308:              << handlerName << "(rdram, ctx, runtime);\n";
  309:         m_ss << indent << "}\n";
  310: 
  311:         if (kind == StaticBranchKind::Jump)
  312:         {
  313:             m_ss << indent << "return;\n";
  314:         }
  315:         else
  316:         {
  317:             m_ss << fmt::format("{}if (ctx->pc != 0x{:X}u) {{ return; }}\n", indent, fallthroughPc());
  318:         }
  319: 
  320:         return true;
  321:     }
  322: 
  323:     void ControlFlowEmitter::emitStaticJump(StaticBranchKind kind)
  324:     {
  325:         if (kind == StaticBranchKind::Call)
  326:         {
  327:             m_ss << fmt::format("    SET_GPR_U32(ctx, 31, 0x{:X}u);\n", fallthroughPc());
  328:         }
  329: 
  330:         emitDelaySlot("    ");
  331: 
  332:         const uint32_t target = buildAbsoluteJumpTarget(m_branchInst.address, m_branchInst.target);
  333:         if (isInternalTarget(target))
  334:         {
  335:             emitInternalTarget(target, branchPc(), "    ");
  336:             return;
  337:         }
  338: 
  339:         m_ss << fmt::format("    ctx->pc = 0x{:X}u;\n", target);
  340: 
  341:         if (kind == StaticBranchKind::Call && emitRelocationCallIfAvailable(kind, "    "))
  342:         {
  343:             return;
  344:         }
  345: 
  346:         if (emitDirectFunctionJumpIfAvailable(target, kind, "    "))
  347:         {
  348:             return;
  349:         }
  350: 
  351:         emitExternalJumpDispatch(target, kind, "    ");
  352:     }
  353: 
  354:     void ControlFlowEmitter::emitRegisterJump(RegisterBranchKind kind)
  355:     {
  356:         const uint8_t rsReg = static_cast<uint8_t>(m_branchInst.rs);
  357:         const uint8_t rdReg = static_cast<uint8_t>(m_branchInst.rd);
  358:         const std::vector<uint32_t> sortedInternalTargets = resolvedLocalIndirectTargets();
  359: 
  360:         m_ss << "    {\n";
  361:         m_ss << "        const uint32_t jumpTarget = GPR_U32(ctx, " << static_cast<int>(rsReg) << ");\n";
  362: 
  363:         if (kind == RegisterBranchKind::Call && rdReg != 0u)
  364:         {
  365:             m_ss << fmt::format("        SET_GPR_U32(ctx, {}, 0x{:X}u);\n", rdReg, fallthroughPc());
  366:         }
  367: 
  368:         emitDelaySlot("        ");
  369:         m_ss << "        ctx->pc = jumpTarget;\n";
  370: 
  371:         if (!sortedInternalTargets.empty())
  372:         {
  373:             m_ss << "        switch (jumpTarget) {\n";
  374:             for (uint32_t target : sortedInternalTargets)
  375:             {
  376:                 m_ss << fmt::format("            case 0x{:X}u: goto label_{:x};\n", target, target);
  377:             }
  378:             m_ss << "            default: break;\n";
  379:             m_ss << "        }\n";
  380:         }
  381: 
  382:         if (kind == RegisterBranchKind::Jump)
  383:         {
  384:             emitExternalRegisterJumpDispatch("jumpTarget", kind, rsReg, "        ");
  385:         }
  386:         else
  387:         {
  388:             emitExternalRegisterCallDispatch("jumpTarget", "        ");
  389:         }
  390: 

========== D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\control_flow_emitter.cpp (455-620) ==========
  455:     uint32_t ControlFlowEmitter::conditionalBranchTarget() const
  456:     {
  457:         const int32_t offsetBytes = static_cast<int32_t>(static_cast<int16_t>(m_branchInst.simmediate)) << 2;
  458:         return static_cast<uint32_t>(static_cast<int64_t>(m_branchInst.address + 4u) +
  459:                                      static_cast<int64_t>(offsetBytes));
  460:     }
  461: 
  462:     void ControlFlowEmitter::emitConditionalBranch()
  463:     {
  464:         const uint32_t target = conditionalBranchTarget();
  465:         const bool likely = isLikelyBranch();
  466:         const std::string branchTakenVar = fmt::format("branch_taken_0x{:x}", m_branchInst.address);
  467:         std::string unconditionalLinkCode;
  468:         std::string conditionalLinkCode;
  469: 
  470:         if (m_branchInst.opcode == OPCODE_REGIMM)
  471:         {
  472:             if (m_branchInst.rt == REGIMM_BLTZAL || m_branchInst.rt == REGIMM_BGEZAL)
  473:             {
  474:                 unconditionalLinkCode = fmt::format("SET_GPR_U32(ctx, 31, 0x{:X}u);", fallthroughPc());
  475:             }
  476:             else if (m_branchInst.rt == REGIMM_BLTZALL || m_branchInst.rt == REGIMM_BGEZALL)
  477:             {
  478:                 conditionalLinkCode = fmt::format("SET_GPR_U32(ctx, 31, 0x{:X}u);", fallthroughPc());
  479:             }
  480:         }
  481: 
  482:         m_ss << "    {\n";
  483:         m_ss << "        const bool " << branchTakenVar << " = (" << conditionalBranchExpression() << ");\n";
  484: 
  485:         if (!unconditionalLinkCode.empty())
  486:         {
  487:             m_ss << "        " << unconditionalLinkCode << "\n";
  488:         }
  489: 
  490:         if (likely)
  491:         {
  492:             m_ss << "        if (" << branchTakenVar << ") {\n";
  493:             if (!conditionalLinkCode.empty())
  494:             {
  495:                 m_ss << "            " << conditionalLinkCode << "\n";
  496:             }
  497:             emitDelaySlot("            ");
  498: 
  499:             if (isInternalTarget(target))
  500:             {
  501:                 emitInternalTarget(target, branchPc(), "            ");
  502:             }
  503:             else
  504:             {
  505:                 m_ss << fmt::format("            ctx->pc = 0x{:X}u;\n", target);
  506:                 m_ss << "            return;\n";
  507:             }
  508:             m_ss << "        }\n";
  509:         }
  510:         else
  511:         {
  512:             if (!conditionalLinkCode.empty())
  513:             {
  514:                 m_ss << "        if (" << branchTakenVar << ") { " << conditionalLinkCode << " }\n";
  515:             }
  516: 
  517:             emitDelaySlot("        ");
  518: 
  519:             m_ss << "        if (" << branchTakenVar << ") {\n";
  520:             if (isInternalTarget(target))
  521:             {
  522:                 emitInternalTarget(target, branchPc(), "            ");
  523:             }
  524:             else
  525:             {
  526:                 m_ss << fmt::format("            ctx->pc = 0x{:X}u;\n", target);
  527:                 m_ss << "            return;\n";
  528:             }
  529:             m_ss << "        }\n";
  530:         }
  531: 
  532:         m_ss << "    }\n";
  533:     }
  534: 
  535:     void ControlFlowEmitter::emitFallbackInstruction()
  536:     {
  537:         m_ss << "    " << m_gen.translateInstruction(m_branchInst) << "\n";
  538:         emitDelaySlot("    ");
  539:     }
  540: 
  541:     void ControlFlowEmitter::emitFallthroughLabelIfNeeded()
  542:     {
  543:         if (isInternalTarget(delayPc()) && !isInternalTarget(fallthroughPc()))
  544:         {
  545:             m_ss << fmt::format("label_fallthrough_0x{:x}:\n", branchPc());
  546:         }
  547:     }
  548: 
  549:     void ControlFlowEmitter::emitFinalFallthrough()
  550:     {
  551:         m_ss << fmt::format("    ctx->pc = 0x{:X}u;\n", fallthroughPc());
  552:     }
  553: 
  554:     std::string ControlFlowEmitter::emit()
  555:     {
  556:         (void)m_function;
  557:         emitResumeFromDelaySlotEntry();
  558:         m_ss << fmt::format("    ctx->pc = 0x{:X}u;\n", branchPc());
  559: 
  560:         if (m_branchInst.opcode == OPCODE_J || m_branchInst.opcode == OPCODE_JAL)
  561:         {
  562:             emitStaticJump(m_branchInst.opcode == OPCODE_JAL ? StaticBranchKind::Call : StaticBranchKind::Jump);
  563:         }
  564:         else if (m_branchInst.opcode == OPCODE_SPECIAL &&
  565:                  (m_branchInst.function == SPECIAL_JR || m_branchInst.function == SPECIAL_JALR))
  566:         {
  567:             emitRegisterJump(m_branchInst.function == SPECIAL_JALR ? RegisterBranchKind::Call : RegisterBranchKind::Jump);
  568:         }
  569:         else if (m_branchInst.isBranch)
  570:         {
  571:             emitConditionalBranch();
  572:         }
  573:         else
  574:         {
  575:             emitFallbackInstruction();
  576:         }
  577: 
  578:         emitFallthroughLabelIfNeeded();
  579:         emitFinalFallthrough();
  580:         return m_ss.str();
  581:     }
  582: }

========== D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\code_generator_tests.cpp (960-1080) ==========
  960:                      "definition should use sanitized name");
  961:             t.IsTrue(generated.find("ps2___is_pointer(rdram, ctx, runtime); return;") != std::string::npos,
  962:                 "call should use sanitized name but got: " + generated);
  963:         });
  964: 
  965:         tc.Run("COP0 MFC0/MTC0 translate to COP0 register access", [](TestCase &t) {
  966:             CodeGenerator gen({}, {});
  967: 
  968:             Instruction mfc0{};
  969:             mfc0.opcode = OPCODE_COP0;
  970:             mfc0.rs = COP0_MF;
  971:             mfc0.rt = 5;
  972:             mfc0.rd = COP0_REG_STATUS;
  973: 
  974:             std::string mfc0Code = gen.translateInstruction(mfc0);
  975:             printGeneratedCode("COP0 MFC0/MTC0 translate to COP0 register access (MFC0)", mfc0Code);
  976:             t.IsTrue(mfc0Code.find("SET_GPR_S32(ctx, 5") != std::string::npos, "MFC0 should write to rt");
  977:             t.IsTrue(mfc0Code.find("ctx->cop0_status") != std::string::npos, "MFC0 STATUS should read cop0_status");
  978:             t.IsTrue(mfc0Code.find("Unimplemented COP0 register") == std::string::npos, "MFC0 should not hit unimplemented COP0 register path");
  979:             t.IsTrue(mfc0Code.find("Unhandled COP0") == std::string::npos, "MFC0 should not hit unhandled COP0 path");
  980: 
  981:             Instruction mtc0{};
  982:             mtc0.opcode = OPCODE_COP0;
  983:             mtc0.rs = COP0_MT;
  984:             mtc0.rt = 7;
  985:             mtc0.rd = COP0_REG_STATUS;
  986: 
  987:             std::string mtc0Code = gen.translateInstruction(mtc0);
  988:             printGeneratedCode("COP0 MFC0/MTC0 translate to COP0 register access (MTC0)", mtc0Code);
  989:             t.IsTrue(mtc0Code.find("ctx->cop0_status") != std::string::npos, "MTC0 STATUS should write cop0_status");
  990:             t.IsTrue(mtc0Code.find("GPR_U32(ctx, 7)") != std::string::npos, "MTC0 should read from rt");
  991:             t.IsTrue(mtc0Code.find("Unimplemented MTC0") == std::string::npos, "MTC0 should not hit unimplemented path");
  992:             t.IsTrue(mtc0Code.find("Unhandled COP0") == std::string::npos, "MTC0 should not hit unhandled COP0 path");
  993:         });
  994: 
  995:         tc.Run("FCR access uses CFC1/CTC1", [](TestCase &t) {
  996:             CodeGenerator gen({}, {});
  997: 
  998:             Instruction cfc1{};
  999:             cfc1.opcode = OPCODE_COP1;
 1000:             cfc1.rs = COP1_CF;
 1001:             cfc1.rt = 4;
 1002:             cfc1.rd = 31;
 1003: 
 1004:             std::string cfc1Code = gen.translateInstruction(cfc1);
 1005:             printGeneratedCode("FCR access uses CFC1/CTC1 (CFC1)", cfc1Code);
 1006:             t.IsTrue(cfc1Code.find("SET_GPR_U32(ctx, 4") != std::string::npos, "CFC1 should write to rt");
 1007:             t.IsTrue(cfc1Code.find("ctx->fcr31") != std::string::npos, "CFC1 FCR31 should read fcr31");
 1008:             t.IsTrue(cfc1Code.find("Unimplemented FCR") == std::string::npos, "CFC1 should not hit unimplemented FCR path");
 1009: 
 1010:             Instruction ctc1{};
 1011:             ctc1.opcode = OPCODE_COP1;
 1012:             ctc1.rs = COP1_CT;
 1013:             ctc1.rt = 4;
 1014:             ctc1.rd = 31;
 1015: 
 1016:             std::string ctc1Code = gen.translateInstruction(ctc1);
 1017:             printGeneratedCode("FCR access uses CFC1/CTC1 (CTC1)", ctc1Code);
 1018:             t.IsTrue(ctc1Code.find("ctx->fcr31 = GPR_U32(ctx, 4) & 0x0183FFFF") != std::string::npos,
 1019:                      "CTC1 FCR31 should mask and write fcr31");
 1020:             t.IsTrue(ctc1Code.find("ignored") == std::string::npos, "CTC1 FCR31 should not be ignored");
 1021:         });
 1022: 
 1023:         tc.Run("SQRT.S reads its operand from ft", [](TestCase &t) {
 1024:             CodeGenerator gen({}, {});
 1025: 
 1026:             // 0x46160504: sqrt.s $f20, $f22 as the EE encodes it, with the fs field zero.
 1027:             Instruction sqrt{};
 1028:             sqrt.opcode = OPCODE_COP1;
 1029:             sqrt.rs = COP1_S;
 1030:             sqrt.rt = 22;
 1031:             sqrt.rd = 0;
 1032:             sqrt.sa = 20;
 1033:             sqrt.function = COP1_S_SQRT;
 1034: 
 1035:             std::string code = gen.translateInstruction(sqrt);
 1036:             printGeneratedCode("SQRT.S reads its operand from ft", code);
 1037:             t.IsTrue(code.find("ctx->f[20] = FPU_SQRT_S(ctx->f[22])") != std::string::npos,
 1038:                      "SQRT.S should take the square root of ft into fd");
 1039:         });
 1040: 
 1041:         tc.Run("VU CFC2/CTC2 access VI registers directly", [](TestCase& t)
 1042:             {
 1043:                 CodeGenerator gen({}, {});
 1044: 
 1045:                 Instruction cfc2{};
 1046:                 cfc2.opcode = OPCODE_COP2;
 1047:                 cfc2.rs = COP2_CFC2;
 1048:                 cfc2.rt = 2;
 1049:                 cfc2.rd = 11;
 1050: 
 1051:                 std::string cfc2Code = gen.translateInstruction(cfc2);
 1052:                 printGeneratedCode("VU CFC2/CTC2 access VI registers directly (CFC2)", cfc2Code);
 1053: 
 1054:                 t.IsTrue(cfc2Code.find("SET_GPR_U32(ctx, 2") != std::string::npos, "CFC2 should write to rt");
 1055: 
 1056:                 t.IsTrue(cfc2Code.find("ctx->vi[11]") != std::string::npos, "CFC2 VI11 should read VI11");
 1057: 
 1058:                 t.IsTrue(cfc2Code.find("vu0_cmsar1") == std::string::npos, "CFC2 VI11 must not read CMSAR1");
 1059: 
 1060:                 t.IsTrue(cfc2Code.find("Unimplemented") == std::string::npos, "CFC2 VI11 should be implemented");
 1061: 
 1062:                 Instruction ctc2{};
 1063:                 ctc2.opcode = OPCODE_COP2;
 1064:                 ctc2.rs = COP2_CTC2;
 1065:                 ctc2.rt = 3;
 1066:                 ctc2.rd = 4;
 1067: 
 1068:                 std::string ctc2Code = gen.translateInstruction(ctc2);
 1069:                 printGeneratedCode("VU CFC2/CTC2 access VI registers directly (CTC2)", ctc2Code);
 1070: 
 1071:                 t.IsTrue(ctc2Code.find("ctx->vi[4]") != std::string::npos, "CTC2 VI4 should write VI4");
 1072:                 t.IsTrue(ctc2Code.find("static_cast<uint16_t>(GPR_U32(ctx, 3))") != std::string::npos, "CTC2 VI4 should store the low 16 bits");
 1073:                 t.IsTrue(ctc2Code.find("vu0_i") == std::string::npos, "CTC2 VI4 must not write the I register");
 1074:                 t.IsTrue(ctc2Code.find("Unimplemented") == std::string::npos, "CTC2 VI4 should be implemented");
 1075:         });
 1076: 
 1077:         tc.Run("VU special control registers use hardware indices", [](TestCase& t)
 1078:             {
 1079:                 CodeGenerator gen({}, {});
 1080: 

========== D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\r5900_decoder_tests.cpp (220-290) ==========
  220:     tc.Run("COP1 transfers set correct register modification flags", [](TestCase &t) {
  221:         R5900Decoder decoder;
  222: 
  223:         const uint32_t mfc1 = (OPCODE_COP1 << 26) | (COP1_MF << 21) | (3 << 16) | (4 << 11);
  224:         const uint32_t mfc1Zero = (OPCODE_COP1 << 26) | (COP1_MF << 21) | (0 << 16) | (4 << 11);
  225:         const uint32_t cfc1 = (OPCODE_COP1 << 26) | (COP1_CF << 21) | (5 << 16) | (31 << 11);
  226:         const uint32_t mtc1 = (OPCODE_COP1 << 26) | (COP1_MT << 21) | (6 << 16) | (7 << 11);
  227:         const uint32_t ctc1 = (OPCODE_COP1 << 26) | (COP1_CT << 21) | (8 << 16) | (31 << 11);
  228: 
  229:         Instruction a = decoder.decodeInstruction(0xB000, mfc1);
  230:         Instruction b = decoder.decodeInstruction(0xB004, mfc1Zero);
  231:         Instruction c = decoder.decodeInstruction(0xB008, cfc1);
  232:         Instruction d = decoder.decodeInstruction(0xB00C, mtc1);
  233:         Instruction e = decoder.decodeInstruction(0xB010, ctc1);
  234: 
  235:         t.IsTrue(a.modificationInfo.modifiesGPR, "MFC1 should modify GPR");
  236:         t.IsFalse(b.modificationInfo.modifiesGPR, "MFC1 to zero register should not modify GPR");
  237:         t.IsTrue(c.modificationInfo.modifiesGPR, "CFC1 should modify GPR");
  238:         t.IsTrue(d.modificationInfo.modifiesFPR, "MTC1 should modify FPR");
  239:         t.IsTrue(e.modificationInfo.modifiesControl, "CTC1 should modify FPU control state");
  240:     });
  241: 
  242:     tc.Run("COP1 BC1F and BC1T set branch and delay-slot flags", [](TestCase &t) {
  243:         R5900Decoder decoder;
  244: 
  245:         const uint32_t bcf = (OPCODE_COP1 << 26) | (COP1_BC << 21) |
  246:                              (COP1_BC_BCF << 16) | 4;
  247:         const uint32_t bct = (OPCODE_COP1 << 26) | (COP1_BC << 21) |
  248:                              (COP1_BC_BCT << 16) | 4;
  249: 
  250:         Instruction a = decoder.decodeInstruction(0xB100, bcf);
  251:         Instruction b = decoder.decodeInstruction(0xB104, bct);
  252: 
  253:         t.IsTrue(a.isBranch, "BC1F should be marked as branch");
  254:         t.IsTrue(a.hasDelaySlot, "BC1F should have a delay slot");
  255:         t.IsTrue(a.modificationInfo.modifiesControl, "BC1F should modify control flow");
  256:         t.IsTrue(b.isBranch, "BC1T should be marked as branch");
  257:         t.IsTrue(b.hasDelaySlot, "BC1T should have a delay slot");
  258:         t.IsTrue(b.modificationInfo.modifiesControl, "BC1T should modify control flow");
  259:     });
  260: 
  261:     tc.Run("COP1 arithmetic modifies FPR while comparisons modify control only", [](TestCase &t) {
  262:         R5900Decoder decoder;
  263: 
  264:         const uint32_t subS = (OPCODE_COP1 << 26) | (COP1_S << 21) |
  265:                               (2 << 16) | (3 << 11) | (4 << 6) | COP1_S_SUB;
  266:         const uint32_t sqrtS = (OPCODE_COP1 << 26) | (COP1_S << 21) |
  267:                                (2 << 16) | (4 << 6) | COP1_S_SQRT;
  268:         const uint32_t compareEq = (OPCODE_COP1 << 26) | (COP1_S << 21) |
  269:                                    (2 << 16) | (3 << 11) | COP1_S_C_EQ;
  270:         const uint32_t compareLt = (OPCODE_COP1 << 26) | (COP1_S << 21) |
  271:                                    (2 << 16) | (3 << 11) | COP1_S_C_LT;
  272: 
  273:         Instruction a = decoder.decodeInstruction(0xB200, subS);
  274:         Instruction b = decoder.decodeInstruction(0xB204, sqrtS);
  275:         Instruction c = decoder.decodeInstruction(0xB208, compareEq);
  276:         Instruction d = decoder.decodeInstruction(0xB20C, compareLt);
  277: 
  278:         t.IsTrue(a.modificationInfo.modifiesFPR, "SUB.S should modify FPR");
  279:         t.IsTrue(b.modificationInfo.modifiesFPR, "SQRT.S should modify FPR");
  280:         t.IsFalse(c.modificationInfo.modifiesFPR, "C.EQ.S should not modify FPR");
  281:         t.IsTrue(c.modificationInfo.modifiesControl, "C.EQ.S should modify FPU condition state");
  282:         t.IsFalse(d.modificationInfo.modifiesFPR, "C.LT.S should not modify FPR");
  283:         t.IsTrue(d.modificationInfo.modifiesControl, "C.LT.S should modify FPU condition state");
  284:     });
  285: });
  286: }

========== D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRuntime\include\ps2_runtime.h (1-220) ==========
    1: #ifndef PS2_RUNTIME_H
    2: #define PS2_RUNTIME_H
    3: 
    4: #include <cstring>
    5: #include <cstdint>
    6: #include <vector>
    7: #include <string>
    8: #include <string_view>
    9: #include <functional>
   10: #if defined(_MSC_VER)
   11: #include <intrin.h>
   12: #elif defined(USE_SSE2NEON)
   13: #include "sse2neon.h"
   14: #else
   15: #include <immintrin.h> // For SSE/AVX instructions
   16: #include <smmintrin.h> // For SSE4.1 instructions
   17: #endif
   18: #include <atomic>
   19: #include <array>
   20: #include <mutex>
   21: #include <filesystem>
   22: #include <memory>
   23: #include <unordered_map>
   24: #include <unordered_set>
   25: 
   26: #include "ps2_log.h"
   27: #include "runtime/ps2_address.h"
   28: #include "runtime/gs/ps2_gif_arbiter.h"
   29: #include "runtime/ps2_memory.h"
   30: #include "runtime/gs/gs_frontend.h"
   31: #include "runtime/ps2_vu1.h"
   32: #include "runtime/ps2_audio.h"
   33: #include "runtime/ps2_pad.h"
   34: #include "runtime/ps2_rom_device.h"
   35: #include "runtime/ps2_vfs.h"
   36: #include "ps2x/iop/iop_types.h"
   37: 
   38: namespace ps2x::iop
   39: {
   40:     class IopSubsystem;
   41: }
   42: 
   43: class PS2IopHostAdapter;
   44: class PS2IopTransport;
   45: class EeScheduler;
   46: struct EeEvent;
   47: 
   48: enum PS2Exception
   49: {
   50:     EXCEPTION_TLB_REFILL = 0x02,          // TLB refill/load exception
   51:     EXCEPTION_ADDRESS_ERROR_LOAD = 0x04,  // Address error on load
   52:     EXCEPTION_ADDRESS_ERROR_STORE = 0x05, // Address error on store
   53:     EXCEPTION_SYSCALL = 0x08,             // SYSCALL instruction
   54:     EXCEPTION_BREAKPOINT = 0x09,          // BREAK instruction
   55:     EXCEPTION_RESERVED_INSTRUCTION = 0x0A,
   56:     EXCEPTION_INTEGER_OVERFLOW = 0x0C, // From MIPS spec
   57:     EXCEPTION_TRAP = 0x0D,             // Trap instruction condition met
   58: };
   59: 
   60: // PS2 CPU context (R5900)
   61: struct alignas(16) R5900Context
   62: {
   63:     // General Purpose Registers (128-bit)
   64:     __m128i r[32]; // Main registers
   65: 
   66:     // Control registers
   67:     uint32_t pc;         // Program counter
   68:     uint64_t insn_count; // Instruction counter
   69:     uint64_t hi, lo;     // HI/LO registers for mult/div results
   70:     uint64_t hi1, lo1;   // Secondary HI/LO registers for MULT1/DIV1
   71:     uint32_t sa;         // Shift amount register
   72: 
   73:     // VU0 registers (when used in macro mode)
   74:     __m128 vu0_vf[32];        // VU0 vector float registers
   75:     uint16_t vi[16];          // VU0 vector integer registers
   76:     float vu0_q;              // VU0 Q register (quotient)
   77:     float vu0_p;              // VU0 P register (EFU result)
   78:     float vu0_i;              // VU0 I register (integer value)
   79:     __m128 vu0_r;             // VU0 R register
   80:     __m128 vu0_acc;           // VU0 ACC accumulator register
   81:     uint16_t vu0_status;      // VU0 status register
   82:     uint32_t vu0_mac_flags;   // VU0 MAC flags
   83:     uint32_t vu0_clip_flags;  // VU0 clipping flags
   84:     uint32_t vu0_clip_flags2; // VU0 clipping flags
   85:     uint32_t vu0_cmsar0;      // VU0 microprogram start address
   86:     uint32_t vu0_cmsar1;      // VU0 microprogram start address
   87:     uint32_t vu0_cmsar2;      // VU0 microprogram start address
   88:     uint32_t vu0_cmsar3;      // VU0 microprogram start address
   89:     uint32_t vu0_vpu_stat;
   90:     uint32_t vu0_vpu_stat2; // extra VPU status (used by CR_VPU_STAT2)
   91:     uint32_t vu0_vpu_stat3; // extra VPU status 3
   92:     uint32_t vu0_vpu_stat4; // extra VPU status 4
   93:     uint32_t vu0_tpc;       // TPC (VU0 PC)
   94:     uint32_t vu0_tpc2;      // second TPC
   95:     uint32_t vu0_fbrst;     // VIF/VU reset register
   96:     uint32_t vu0_fbrst2;    // FBRST2
   97:     uint32_t vu0_fbrst3;    // FBRST3
   98:     uint32_t vu0_fbrst4;    // FBRST4
   99:     uint32_t vu0_itop;
  100:     uint32_t vu0_top;
  101:     uint32_t vu0_info;
  102:     uint32_t vu0_xitop; // VU0 XITOP - input ITOP for VIF/VU sync
  103:     uint32_t vu0_pc;
  104: 
  105:     float vu0_cf[4]; // VU0 FMAC control floating-point registers
  106: 
  107:     // COP0 System control registers
  108:     uint32_t cop0_index;
  109:     uint32_t cop0_random;
  110:     uint32_t cop0_entrylo0;
  111:     uint32_t cop0_entrylo1;
  112:     uint32_t cop0_context;
  113:     uint32_t cop0_pagemask;
  114:     uint32_t cop0_wired;
  115:     uint32_t cop0_badvaddr;
  116:     uint32_t cop0_count;
  117:     uint32_t cop0_entryhi;
  118:     uint32_t cop0_compare;
  119:     uint32_t cop0_status;
  120:     uint32_t cop0_cause;
  121:     uint32_t cop0_epc;
  122:     uint32_t cop0_prid;
  123:     uint32_t cop0_config;
  124:     uint32_t cop0_badpaddr;
  125:     uint32_t cop0_debug;
  126:     uint32_t cop0_perf;
  127:     uint32_t cop0_taglo;
  128:     uint32_t cop0_taghi;
  129:     uint32_t cop0_errorepc;
  130: 
  131:     // LL/SC reservation state (not part of COP0 Status bits).
  132:     uint32_t llbit;
  133:     uint32_t lladdr;
  134: 
  135:     // Delay slot state tracking
  136:     bool in_delay_slot;
  137:     uint32_t branch_pc;
  138: 
  139:     // COP2 control registers (VU0 integer + control)
  140:     uint32_t cop2_ccr[32];
  141: 
  142:     // FPU registers (COP1)
  143:     float f[32];
  144:     float f_acc;    // FPU accumulator
  145:     uint32_t fcr31; // Control/status register
  146: 
  147:     R5900Context()
  148:     {
  149:         std::memset(this, 0, sizeof(*this));
  150: 
  151:         // Initialize VU0 registers
  152:         vu0_q = 1.0f; // Q register usually initialized to 1.0
  153: 
  154:         // Reset COP0 registers
  155:         cop0_random = 47; // Start at maximum value
  156:         // Status as the EE kernel leaves it at handoff. IE (bit 0) and EIE
  157:         // (bit 16) are separate enables and guest code reads both; libkernel's
  158:         // StartThread refuses to run while IE is clear.
  159:         cop0_status = 0x00010001; // EIE | IE
  160:         cop0_prid = 0x00002e20; // CPU ID for R5900
  161: 
  162:         in_delay_slot = false;
  163:         branch_pc = 0;
  164:     }
  165: 
  166:     void dump() const
  167:     {
  168:         std::ios_base::fmtflags flags = std::cout.flags();
  169:         std::cout << std::hex << std::setfill('0');
  170:         std::cout << "--- R5900 Context Dump ---\n";
  171:         std::cout << "PC: 0x" << std::setw(8) << pc << "\n";
  172:         std::cout << "HI: 0x" << std::setw(8) << hi << " LO: 0x" << std::setw(8) << lo << "\n";
  173:         std::cout << "HI1:0x" << std::setw(8) << hi1 << " LO1:0x" << std::setw(8) << lo1 << "\n";
  174:         std::cout << "SA: 0x" << std::setw(8) << sa << "\n";
  175:         for (int i = 0; i < 32; ++i)
  176:         {
  177:             std::cout << "R" << std::setw(2) << std::dec << i << ": 0x" << std::hex
  178:                       << std::setw(8) << static_cast<uint32_t>(_mm_extract_epi32(r[i], 3))
  179:                       << std::setw(8) << static_cast<uint32_t>(_mm_extract_epi32(r[i], 2)) << "_"
  180:                       << std::setw(8) << static_cast<uint32_t>(_mm_extract_epi32(r[i], 1))
  181:                       << std::setw(8) << static_cast<uint32_t>(_mm_extract_epi32(r[i], 0)) << "\n";
  182:         }
  183:         std::cout << "Status: 0x" << std::setw(8) << cop0_status
  184:                   << " Cause: 0x" << std::setw(8) << cop0_cause
  185:                   << " EPC: 0x" << std::setw(8) << cop0_epc << "\n";
  186:         std::cout << "--- End Context Dump ---\n";
  187:         std::cout.flags(flags); // Restore format flags
  188:     }
  189: 
  190:     ~R5900Context() = default;
  191: };
  192: 
  193: inline uint32_t getRegU32(const R5900Context *ctx, int reg)
  194: {
  195:     // Check if reg is valid (0-31)
  196:     if (reg < 0 || reg > 31)
  197:         return 0;
  198:     if (reg == 0)
  199:         return 0;
  200:     return static_cast<uint32_t>(_mm_extract_epi32(ctx->r[reg], 0));
  201: }
  202: 
  203: inline void setReturnU32(R5900Context *ctx, uint32_t value)
  204: {
  205:     // R5900 sign-extends 32-bit results into 64-bit GPR, even for unsigned values.
  206:     ctx->r[2] = _mm_set_epi64x(0, static_cast<int64_t>(static_cast<int32_t>(value))); // $v0
  207: }
  208: 
  209: inline void setReturnS32(R5900Context *ctx, int32_t value)
  210: {
  211:     // Signed 32-bit return should be sign-extended when observed as 64-bit.
  212:     ctx->r[2] = _mm_set_epi64x(0, static_cast<int64_t>(value)); // $v0
  213: }
  214: 
  215: inline void setReturnU64(R5900Context *ctx, uint64_t value)
  216: {
  217:     // Keep both conventions: full 64-bit value in $v0 and high 32-bit in $v1.
  218:     ctx->r[2] = _mm_set_epi64x(0, static_cast<int64_t>(value));
  219:     ctx->r[3] = _mm_set_epi64x(0, static_cast<int64_t>(static_cast<uint32_t>(value >> 32)));
  220: }

========== SOURCE SEARCHES ==========

--- D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src ---
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\control_flow_analyzer.cpp:37: // The delay slot of a branch-likely only runs when the branch is taken, so it cannot change a
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\control_flow_analyzer.cpp:39: bool isBranchLikely(const Instruction &inst)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\control_flow_analyzer.cpp:185: // entry point there. +4, not +8: syscall has no delay slot.
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\control_flow_analyzer.cpp:401: !(i > 0 && isBranchLikely(instructions[i - 1])))
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\control_flow_emitter.cpp:61: bool ControlFlowEmitter::isLikelyBranch() const
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\control_flow_emitter.cpp:68: (m_branchInst.opcode == OPCODE_COP1 && m_branchInst.rs == COP1_BC &&
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\control_flow_emitter.cpp:69: (m_branchInst.rt == COP1_BC_BCFL || m_branchInst.rt == COP1_BC_BCTL)) ||
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\control_flow_emitter.cpp:120: code += " (Delay Slot)\n";
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\control_flow_emitter.cpp:135: m_ss << fmt::format("{}ctx->in_delay_slot = true;\n", indent);
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\control_flow_emitter.cpp:149: m_ss << fmt::format("{}ctx->in_delay_slot = false;\n", indent);
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\control_flow_emitter.cpp:431: if (m_branchInst.rs == COP1_BC)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\control_flow_emitter.cpp:434: return (bcCond == COP1_BC_BCF || bcCond == COP1_BC_BCFL)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\control_flow_emitter.cpp:435: ? "!(ctx->fcr31 & 0x800000)"
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\control_flow_emitter.cpp:436: : "(ctx->fcr31 & 0x800000)";
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\control_flow_emitter.cpp:465: const bool likely = isLikelyBranch();
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\control_flow_emitter.cpp:490: if (likely)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\elf_parser.cpp:802: bool IsLikelyBranch(uint32_t raw)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\elf_parser.cpp:905: // Both ordinary and likely branches resume after their delay
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\elf_parser.cpp:925: // Calls return after their delay slot; the callee is a separate
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\elf_parser.cpp:1034: enqueue(state.offset + (2u * MIPS_INSTRUCTION_SIZE), IsLikelyBranch(raw) ? state.trackedGprs : delayTracked);
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\elf_parser.cpp:1140: // control transfer names its delay slot. Promoting it would cut
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\elf_parser.cpp:1141: // the real owner before the delay instruction, as happened at Silent Hill's 0x325350 (the delay slot of JALR 0x32534c).
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\elf_parser.cpp:1251: if (!IsLikelyBranch(predecessorRaw))
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\elf_parser.cpp:1272: // The LUI ran in a call/jump delay slot. An incomplete
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\elf_parser.cpp:1376: enqueue(state.offset + (2u * MIPS_INSTRUCTION_SIZE), IsLikelyBranch(raw) ? state.trackedGprs : delayAliases);
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\elf_parser.cpp:1595: // delay slot), so the address can only be entered fresh. A function that follows another function's
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:34: return fmt::format("SET_GPR_U32(ctx, {}, ctx->fcr31);", ft); // FCR31 contains status/control
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:40: return fmt::format("ctx->fcr31 = GPR_U32(ctx, {}) & 0x0183FFFF;", ft);
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:44: case COP1_BC:
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:57: return fmt::format("{{ if (ctx->f[{}] == 0.0f) ctx->fcr31 |= 0x100000; /* DZ flag */ "
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:70: return fmt::format("{{ int32_t tmp = FPU_ROUND_W_S(ctx->f[{}]); std::memcpy(&ctx->f[{}], &tmp, sizeof(tmp)); }}", fs, fd);
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:78: return fmt::format("{{ int32_t tmp = FPU_CVT_W_S(ctx->f[{}]); std::memcpy(&ctx->f[{}], &tmp, sizeof(tmp)); }}", fs, fd);
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:101: return fmt::format("ctx->fcr31 &= ~0x800000;");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:103: return fmt::format("ctx->fcr31 = (FPU_C_UN_S(ctx->f[{}], ctx->f[{}])) ? (ctx->fcr31 | 0x800000) : (ctx->fcr31 & ~0x800000);", fs, ft);
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:105: return fmt::format("ctx->fcr31 = (FPU_C_EQ_S(ctx->f[{}], ctx->f[{}])) ? (ctx->fcr31 | 0x800000) : (ctx->fcr31 & ~0x800000);", fs, ft);
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:107: return fmt::format("ctx->fcr31 = (FPU_C_UEQ_S(ctx->f[{}], ctx->f[{}])) ? (ctx->fcr31 | 0x800000) : (ctx->fcr31 & ~0x800000);", fs, ft);
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:109: return fmt::format("ctx->fcr31 = (FPU_C_OLT_S(ctx->f[{}], ctx->f[{}])) ? (ctx->fcr31 | 0x800000) : (ctx->fcr31 & ~0x800000);", fs, ft);
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:111: return fmt::format("ctx->fcr31 = (FPU_C_ULT_S(ctx->f[{}], ctx->f[{}])) ? (ctx->fcr31 | 0x800000) : (ctx->fcr31 & ~0x800000);", fs, ft);
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:113: return fmt::format("ctx->fcr31 = (FPU_C_OLE_S(ctx->f[{}], ctx->f[{}])) ? (ctx->fcr31 | 0x800000) : (ctx->fcr31 & ~0x800000);", fs, ft);
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:115: return fmt::format("ctx->fcr31 = (FPU_C_ULE_S(ctx->f[{}], ctx->f[{}])) ? (ctx->fcr31 | 0x800000) : (ctx->fcr31 & ~0x800000);", fs, ft);
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:117: return fmt::format("ctx->fcr31 &= ~0x800000;");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:119: return fmt::format("ctx->fcr31 = (FPU_C_NGLE_S(ctx->f[{}], ctx->f[{}])) ? (ctx->fcr31 | 0x800000) : (ctx->fcr31 & ~0x800000);", fs, ft);
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:121: return fmt::format("ctx->fcr31 = (FPU_C_SEQ_S(ctx->f[{}], ctx->f[{}])) ? (ctx->fcr31 | 0x800000) : (ctx->fcr31 & ~0x800000);", fs, ft);
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:123: return fmt::format("ctx->fcr31 = (FPU_C_NGL_S(ctx->f[{}], ctx->f[{}])) ? (ctx->fcr31 | 0x800000) : (ctx->fcr31 & ~0x800000);", fs, ft);
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:125: return fmt::format("ctx->fcr31 = (FPU_C_LT_S(ctx->f[{}], ctx->f[{}])) ? (ctx->fcr31 | 0x800000) : (ctx->fcr31 & ~0x800000);", fs, ft);
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:127: return fmt::format("ctx->fcr31 = (FPU_C_NGE_S(ctx->f[{}], ctx->f[{}])) ? (ctx->fcr31 | 0x800000) : (ctx->fcr31 & ~0x800000);", fs, ft);
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:129: return fmt::format("ctx->fcr31 = (FPU_C_LE_S(ctx->f[{}], ctx->f[{}])) ? (ctx->fcr31 | 0x800000) : (ctx->fcr31 & ~0x800000);", fs, ft);
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\fpu_translator.cpp:131: return fmt::format("ctx->fcr31 = (FPU_C_NGT_S(ctx->f[{}], ctx->f[{}])) ? (ctx->fcr31 | 0x800000) : (ctx->fcr31 & ~0x800000);", fs, ft);
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\function_emitter.cpp:175: ++i; // Skip delay slot instruction (handled inside branch logic)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\gif_dma_kick_analyzer.cpp:287: code << " (Delay Slot)\n";
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\instruction_translator.cpp:242: return fmt::format("// Likely branch instruction at 0x{:X} - Handled by branch logic", inst.address);
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\ps2_recompiler.cpp:828: // Every instruction that follows an unconditional transfer and its delay slot starts a block no
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\ps2_recompiler.cpp:1941: ss << "struct R5900Context;\n";
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\src\lib\r5900_decoder.cpp:819: else if (format == COP1_BC)

--- D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\include ---
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\include\ps2recomp\Emitters\control_flow_emitter.h:52: bool isLikelyBranch() const;
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\include\ps2recomp\instructions.h:76: OPCODE_BEQL = 0x14,  // Branch on Equal Likely
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\include\ps2recomp\instructions.h:77: OPCODE_BNEL = 0x15,  // Branch on Not Equal Likely
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\include\ps2recomp\instructions.h:78: OPCODE_BLEZL = 0x16, // Branch on Less Than or Equal to Zero Likely
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\include\ps2recomp\instructions.h:79: OPCODE_BGTZL = 0x17, // Branch on Greater Than Zero Likely
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\include\ps2recomp\instructions.h:205: REGIMM_BLTZL = 0x02, // Branch on Less Than Zero Likely
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\include\ps2recomp\instructions.h:206: REGIMM_BGEZL = 0x03, // Branch on Greater Than or Equal to Zero Likely
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\include\ps2recomp\instructions.h:218: REGIMM_BLTZALL = 0x12, // Branch on Less Than Zero and Link Likely
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\include\ps2recomp\instructions.h:219: REGIMM_BGEZALL = 0x13, // Branch on Greater Than or Equal to Zero and Link Likely
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\include\ps2recomp\instructions.h:405: COP0_BC_BCFL = 0x02, // Branch on Condition False Likely
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\include\ps2recomp\instructions.h:406: COP0_BC_BCTL = 0x03, // Branch on Condition True Likely
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\include\ps2recomp\instructions.h:446: COP1_BC = 0x08, // Branch on FPU Condition (see Cop1BranchCondition)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\include\ps2recomp\instructions.h:467: COP1_S_ROUND_L = 0x08, // ROUND.L.S - Requires 64-bit int dest, likely unused
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\include\ps2recomp\instructions.h:468: COP1_S_TRUNC_L = 0x09, // TRUNC.L.S - Requires 64-bit int dest, likely unused
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\include\ps2recomp\instructions.h:469: COP1_S_CEIL_L = 0x0A,  // CEIL.L.S  - Requires 64-bit int dest, likely unused
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\include\ps2recomp\instructions.h:470: COP1_S_FLOOR_L = 0x0B, // FLOOR.L.S - Requires 64-bit int dest, likely unused
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\include\ps2recomp\instructions.h:489: COP1_S_CVT_L = 0x25, // CVT.L.S - Requires 64-bit int dest, likely unused
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\include\ps2recomp\instructions.h:522: // COP1 BC Condition Field ('fmt' or 'rt' field, bits 20-16) for COP1_BC Format
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\include\ps2recomp\instructions.h:525: COP1_BC_BCF = 0x00,  // Branch on FPU Condition False (BC1F)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\include\ps2recomp\instructions.h:526: COP1_BC_BCT = 0x01,  // Branch on FPU Condition True (BC1T)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\include\ps2recomp\instructions.h:527: COP1_BC_BCFL = 0x02, // Branch on FPU Condition False Likely (BC1FL)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\include\ps2recomp\instructions.h:528: COP1_BC_BCTL = 0x03, // Branch on FPU Condition True Likely (BC1TL)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\include\ps2recomp\instructions.h:548: COP2_BC_BCFL = 0x02, // Branch on VU0 Condition False Likely (BC2FL)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\include\ps2recomp\instructions.h:549: COP2_BC_BCTL = 0x03, // Branch on VU0 Condition True Likely (BC2TL)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRecomp\include\ps2recomp\types.h:35: bool hasDelaySlot; // Has delay slot

--- D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRuntime\src ---
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRuntime\src\lib\vu\ps2_vu1_core.cpp:1633: const bool useVuRounding = std::fesetround(FE_TOWARDZERO) == 0;
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRuntime\src\lib\vu\ps2_vu1_core.cpp:1837: std::fesetround(previousRoundingMode);
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRuntime\src\lib\ps2_iop_host.h:12: struct R5900Context;
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRuntime\src\lib\ps2_runtime.cpp:286: if (ctx->in_delay_slot)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRuntime\src\lib\ps2_runtime.cpp:302: ctx->in_delay_slot = false;
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRuntime\src\lib\ps2_runtime.cpp:1551: if (ctx->in_delay_slot)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRuntime\src\lib\ps2_runtime.cpp:1553: throw std::runtime_error("Attempted to execute a syscall inside a branch delay slot! "

--- D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRuntime\include ---
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRuntime\include\ps2_runtime.h:135: // Delay slot state tracking
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRuntime\include\ps2_runtime.h:136: bool in_delay_slot;
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRuntime\include\ps2_runtime.h:145: uint32_t fcr31; // Control/status register
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRuntime\include\ps2_runtime.h:162: in_delay_slot = false;
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRuntime\include\ps2_runtime_macros.h:918: #define FPU_ROUND_W_S(a) ((int32_t)nearbyintf((float)(a)))
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRuntime\include\ps2_runtime_macros.h:924: #define FPU_CVT_W_S(a) ((int32_t)nearbyintf((float)(a)))
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xRuntime\include\ps2_stubs.h:3: struct R5900Context;

--- D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src ---
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\code_generator_tests.cpp:412: tc.Run("GIF DMA kick coalesces when CHCR store is a return delay slot", [](TestCase &t) {
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\code_generator_tests.cpp:437: printGeneratedCode("GIF DMA kick coalesces when CHCR store is a return delay slot", generated);
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\code_generator_tests.cpp:443: t.IsTrue(generated.find("ctx->in_delay_slot = true;") != std::string::npos,
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\code_generator_tests.cpp:444: "coalesced helper should still run as the return delay slot");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\code_generator_tests.cpp:448: "coalesced delay-slot CHCR store should not remain as an individual WRITE32");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\code_generator_tests.cpp:461: // 0x1004: beq $1,$1, target (0x100c) with delay slot at 0x1008
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\code_generator_tests.cpp:462: // 0x1008: nop (delay slot)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\code_generator_tests.cpp:468: instructions.push_back(makeNop(0x1008));       // delay slot
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\code_generator_tests.cpp:478: t.IsTrue(generated.find("label_1008:") == std::string::npos, "delay slot without incoming branch should not get a label");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\code_generator_tests.cpp:481: tc.Run("labels delay slot when it is a branch target", [](TestCase &t) {
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\code_generator_tests.cpp:483: func.name = "delay_slot_label";
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\code_generator_tests.cpp:489: // Branch at 0x2000 targets 0x2004 (its own delay slot)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\code_generator_tests.cpp:492: instructions.push_back(makeNop(0x2004));       // delay slot and target
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\code_generator_tests.cpp:497: printGeneratedCode("labels delay slot when it is a branch target", generated);
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\code_generator_tests.cpp:499: t.IsTrue(generated.find("label_2004:") != std::string::npos, "delay slot that is a target should emit a label");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\code_generator_tests.cpp:500: t.IsTrue(generated.find("goto label_2004;") != std::string::npos, "branch to delay slot should use goto");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\code_generator_tests.cpp:660: //   addiu $v1, $zero, <num> ; syscall ; jr $ra ; <delay slot>
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\code_generator_tests.cpp:678: // +4, not +8: syscall has no delay slot.
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\code_generator_tests.cpp:684: "syscall must not claim a delay slot it does not have");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\code_generator_tests.cpp:836: instructions.push_back(makeNop(0x3004)); // delay slot
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\code_generator_tests.cpp:1007: t.IsTrue(cfc1Code.find("ctx->fcr31") != std::string::npos, "CFC1 FCR31 should read fcr31");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\code_generator_tests.cpp:1018: t.IsTrue(ctc1Code.find("ctx->fcr31 = GPR_U32(ctx, 4) & 0x0183FFFF") != std::string::npos,
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\code_generator_tests.cpp:1019: "CTC1 FCR31 should mask and write fcr31");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\code_generator_tests.cpp:1020: t.IsTrue(ctc1Code.find("ignored") == std::string::npos, "CTC1 FCR31 should not be ignored");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\code_generator_tests.cpp:1500: // 0xA004: NOP (delay slot)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\code_generator_tests.cpp:1511: // ... delay slot ...
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\code_generator_tests.cpp:1552: tc.Run("trailing JAL without decoded delay slot still emits call flow", [](TestCase &t) {
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\code_generator_tests.cpp:1569: printGeneratedCode("trailing JAL without decoded delay slot still emits call flow", generated);
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\code_generator_tests.cpp:1705: tc.Run("branch-likely places delay slot only in taken path", [](TestCase &t) {
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\code_generator_tests.cpp:1707: func.name = "branch_likely";
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\code_generator_tests.cpp:1715: br.opcode = OPCODE_BEQL;   // likely
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\code_generator_tests.cpp:1735: printGeneratedCode("branch-likely places delay slot only in taken path", generated);
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\code_generator_tests.cpp:1737: t.IsTrue(generated.find("SET_GPR_S32(ctx, 7,") != std::string::npos, "delay slot should be translated");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\code_generator_tests.cpp:1738: t.IsTrue(generated.find("if (branch_taken_0x1200)") != std::string::npos, "should generate branch_taken variable and if for likely branch");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\code_generator_tests.cpp:1783: // JR $31 at 0x1314 with delay slot at 0x1318
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\code_generator_tests.cpp:1805: tc.Run("trailing JR $31 without decoded delay slot still emits return flow", [](TestCase &t) {
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\code_generator_tests.cpp:1821: printGeneratedCode("trailing JR $31 without decoded delay slot still emits return flow", generated);
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\code_generator_tests.cpp:1845: // 0x1408: nop (delay slot)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\code_generator_tests.cpp:2183: "jalr fallback should not dispatch directly to tail-jump delay slot");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:193: textWords[21] = 0x27BD0010u; // addiu sp,sp,0x10 (delay slot)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:451: 0x27BD0010u, // slot_entry (also wrapper's delay slot): addiu $sp, $sp, 0x10
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:508: textWords[3] = 0x24840040u;  // addiu a0,a0,0x40 (delay slot)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:524: textWords[25] = 0x00000000u; // nop (delay slot)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:543: textWords[43] = 0x27BD0010u; // addiu sp,sp,0x10 (delay slot)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:555: textWords[51] = 0x00000000u; // nop (delay slot)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:571: textWords[70] = 0xAC600000u; // sw zero,0(v1) (delay slot)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:581: textWords[122] = 0x00000000u; // nop (delay slot)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:597: textWords[139] = 0x00000000u; // nop (delay slot)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:600: textWords[147] = 0x00000000u; // nop (delay slot)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:606: textWords[149] = 0x3C060010u; // lui a2,0x10 (delay slot)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:608: textWords[151] = 0x00000000u; // nop (delay slot)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:611: textWords[155] = 0x24040008u; // addiu a0,zero,8 (delay slot)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:618: textWords[165] = 0x0080102Du; // daddu v0,a0,zero (delay slot)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:625: textWords[181] = 0xAC850000u; // sw a1,0(a0) (delay slot)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:638: textWords[210] = 0x24420100u; // addiu v0,v0,0x100 (delay slot)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:655: textWords[189] = 0x00000000u; // nop (delay slot)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:657: textWords[193] = 0x00000000u; // nop (delay slot)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:659: textWords[241] = 0x0080102Du; // daddu v0,a0,zero (delay slot)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:661: textWords[243] = 0x0080102Du; // daddu v0,a0,zero (delay slot)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:671: textWords[200] = 0x24050A0Bu; // addiu a1,zero,0xA0B (delay slot)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:674: textWords[249] = 0x0080102Du; // daddu v0,a0,zero (delay slot)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:683: textWords[205] = 0x24050A06u; // addiu a1,zero,0xA06 (delay slot)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:691: textWords[337] = 0x00000000u; // nop (delay slot)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:695: // `jr ra`, its delay slot, then a fresh stack allocation.
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:699: textWords[341] = 0x27BD0010u; // addiu sp,sp,0x10 (delay slot)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:705: textWords[31] = 0x00000000u;  // nop (delay slot)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:712: textWords[218] = 0x00000000u; // nop (delay slot)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:715: textWords[221] = 0x27BD0010u; // addiu sp,sp,0x10 (delay slot)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:718: textWords[354] = 0x0200202Du; // daddu a0,s0,zero (delay slot at 0x00100588)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:722: textWords[358] = 0x27BD0010u; // addiu sp,sp,0x10 (delay slot)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:725: // delay slot of the JALR above. Its following body can look callable to a
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:728: textWords[13] = 0x00000000u;  // nop (delay slot)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:729: textWords[368] = 0x27BDFFF0u; // delay-slot pointer caller at 0x001005C0
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:733: textWords[372] = 0x00000000u; // nop (delay slot)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:735: textWords[374] = 0x27BD0010u; // addiu sp,sp,0x10 (delay slot)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:738: // delay slot. Only the first returns inside the eight-word probe; the others return 8 and 11 words
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:741: textWords[383] = 0x00000000u; // nop (delay slot)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:785: // Eight zero words keep the records outside the 32-byte cluster window of the delay-slot pointer above.
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:1113: "return entry 0x2008 slice should keep the jump and its delay slot");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:1373: t.Equals(added, static_cast<size_t>(2), "two block starts follow a transfer and its delay slot");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:1374: t.IsTrue(has(0x1008u), "the instruction after `jr ra` and its delay slot is a resume entry");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:1375: t.IsTrue(has(0x102Cu), "the instruction after `j` and its delay slot is a resume entry");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:1549: "jr ra entry should end after delay slot, not at container end");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:1780: tc.Run("a jump in a function's last word executes its delay slot even when the next function starts there", [](TestCase &t) {
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:1784: std::filesystem::temp_directory_path() / ("ps2recomp-delay-slot-boundary-" + uniqueSuffix);
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:1785: const std::filesystem::path elfPath = tempRoot / "delay-slot.elf";
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:1786: const std::filesystem::path configPath = tempRoot / "delay-slot.toml";
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:1792: t.IsTrue(elfWritten && configWritten, "delay slot boundary inputs should be generated");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:1797: t.IsTrue(recompiler.initialize(), "delay slot boundary config should initialize");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:1798: t.IsTrue(recompiler.recompile(), "delay slot boundary ELF should recompile");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:1810: // Dropping the delay slot left $sp 0x10 low after the tail jump, so the caller reloaded $ra from
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:1813: "the J at the end of wrapper should run its delay slot (addiu $sp, $sp, 0x10)");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:1996: "LUI plus delay-slot ADDIU should discover the callback entry");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:2010: "a delay-slot LUI should flow into the taken branch successor");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_recompiler_tests.cpp:2026: "a data pointer must not split a function at a control-transfer delay slot");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_runtime_expansion_tests.cpp:1134: tc.Run("SignalException marks EPC and BD for delay-slot exceptions", [](TestCase &t)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_runtime_expansion_tests.cpp:1141: ctx.in_delay_slot = true;
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_runtime_expansion_tests.cpp:1147: t.Equals(ctx.cop0_epc, 0x1FFCu, "delay-slot exception should capture branch_pc in EPC");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_runtime_expansion_tests.cpp:1148: t.IsTrue((ctx.cop0_cause & COP0_CAUSE_BD) != 0u, "delay-slot exception should set CAUSE.BD");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_runtime_expansion_tests.cpp:1154: t.IsFalse(ctx.in_delay_slot, "exception delivery should clear delay-slot state");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_runtime_expansion_tests.cpp:1163: ctx.in_delay_slot = false;
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_runtime_expansion_tests.cpp:1174: tc.Run("handleSyscall rejects invocation in delay slot", [](TestCase &t)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_runtime_expansion_tests.cpp:1179: ctx.in_delay_slot = true;
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_runtime_expansion_tests.cpp:1191: t.IsTrue(threw, "syscall from delay slot should throw to preserve block atomicity");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_vu1_tests.cpp:421: tc.Run("lower branch commits after one delay-slot instruction", [](TestCase &t)
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_vu1_tests.cpp:427: writeVuInstructionPair(fx.code, 8u, makeVuIaddiu(1u, 0u, 1), kVuUpperNop);      // delay slot
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_vu1_tests.cpp:434: t.Equals(vu1.state().vi[1], 1, "branch delay slot should execute");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_vu1_tests.cpp:435: t.Equals(vu1.state().vi[2], 0, "instruction between delay slot and target should be skipped");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_vu1_tests.cpp:436: t.Equals(vu1.state().vi[3], 7, "branch target should execute after the delay slot");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_vu1_tests.cpp:865: "E should execute exactly one sequential delay slot");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_vu1_tests.cpp:867: "E should stop before the instruction after its delay slot");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_vu1_tests.cpp:890: "enabled T should stop without an ordinary delay slot");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_vu1_tests.cpp:908: "enabled D should stop without an ordinary delay slot");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_vu1_tests.cpp:935: "T on a branch should still execute its branch delay slot");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_vu1_tests.cpp:969: "the instruction after a conditional branch remains its delay slot");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_vu1_tests.cpp:985: "taken branch should still execute its delay slot");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_vu1_tests.cpp:989: "taken branch should arrive at its target after the delay slot");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_vu1_tests.cpp:1011: "a stalled conditional branch should retain its delay slot");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_vu1_tests.cpp:1049: "the taken branch should still execute its delay slot");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_vu1_tests.cpp:1086: "JR should execute exactly one delay-slot pair");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\ps2_vu1_tests.cpp:1088: "JR should skip the sequential instruction after its delay slot");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\r5900_decoder_tests.cpp:21: t.IsTrue(inst.hasDelaySlot, "jal has a delay slot");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\r5900_decoder_tests.cpp:62: t.IsTrue(inst.hasDelaySlot, "beq has a delay slot");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\r5900_decoder_tests.cpp:103: t.IsTrue(inst.hasDelaySlot, "jr has delay slot");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\r5900_decoder_tests.cpp:116: t.IsTrue(inst.hasDelaySlot, "jalr has delay slot");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\r5900_decoder_tests.cpp:187: t.IsTrue(inst.hasDelaySlot, "bgezal has delay slot");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\r5900_decoder_tests.cpp:209: tc.Run("COP0 ERET is marked as return without delay slot", [](TestCase &t) {
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\r5900_decoder_tests.cpp:217: t.IsFalse(inst.hasDelaySlot, "eret should not have a delay slot");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\r5900_decoder_tests.cpp:242: tc.Run("COP1 BC1F and BC1T set branch and delay-slot flags", [](TestCase &t) {
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\r5900_decoder_tests.cpp:245: const uint32_t bcf = (OPCODE_COP1 << 26) | (COP1_BC << 21) |
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\r5900_decoder_tests.cpp:246: (COP1_BC_BCF << 16) | 4;
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\r5900_decoder_tests.cpp:247: const uint32_t bct = (OPCODE_COP1 << 26) | (COP1_BC << 21) |
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\r5900_decoder_tests.cpp:248: (COP1_BC_BCT << 16) | 4;
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\r5900_decoder_tests.cpp:254: t.IsTrue(a.hasDelaySlot, "BC1F should have a delay slot");
D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\r5900_decoder_tests.cpp:257: t.IsTrue(b.hasDelaySlot, "BC1T should have a delay slot");
