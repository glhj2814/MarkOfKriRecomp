
========== D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\code_generator_tests.cpp ==========

--- Lines 400-434 ---
  400:         printGeneratedCode("known GIF DMA MMIO sequence emits native kick helper", generated);
  401: 
  402:         t.IsTrue(generated.find("uint32_t gifDmaKickValue_3024_2 = GPR_U32(ctx, 4);") != std::string::npos,
  403:                  "dynamic GIF TADR source should be captured when the store is coalesced");
  404:         t.IsTrue(generated.find("runtime->kickGifDmaChainFromMMIO(rdram, ctx, 0x4u, 0x4u, gifDmaKickValue_3024_2, 0x105u);") != std::string::npos,
  405:                  "known GIF DMA MMIO stores should coalesce into the native kick helper");
  406:         t.IsTrue(generated.find("runtime->Store32(rdram, ctx, 0x1000E020u") == std::string::npos,
  407:                  "coalesced D_PCR store should not remain as an individual Store32");
  408:         t.IsTrue(generated.find("runtime->Store32(rdram, ctx, 0x1000A000u") == std::string::npos,
  409:                  "coalesced GIF CHCR store should not remain as an individual Store32");
  410:     });
  411: 
  412:     tc.Run("GIF DMA kick coalesces when CHCR store is a return delay slot", [](TestCase &t) {
  413:         Function func;
  414:         func.name = "loadImage_like";
  415:         func.start = 0x2E7C90;
  416:         func.end = 0x2E7CC8;
  417:         func.isRecompiled = true;
  418: 
  419:         std::vector<Instruction> instructions;
  420:         instructions.push_back(makeBranch(0x2E7C90, 2));
  421:         instructions.push_back(makeLui(0x2E7C94, 5, 0x1000));
  422:         instructions.push_back(makeLui(0x2E7C98, 5, 0x1000));
  423:         instructions.push_back(makeAddiu(0x2E7C9C, 6, 0, 4));
  424:         instructions.push_back(makeOri(0x2E7CA0, 3, 5, 0xE020));
  425:         instructions.push_back(makeSw(0x2E7CA4, 6, 3, 0));
  426:         instructions.push_back(makeOri(0x2E7CA8, 3, 5, 0xE010));
  427:         instructions.push_back(makeSw(0x2E7CAC, 6, 3, 0));
  428:         instructions.push_back(makeOri(0x2E7CB0, 3, 5, 0xA030));
  429:         instructions.push_back(makeSw(0x2E7CB4, 4, 3, 0));
  430:         instructions.push_back(makeAddiu(0x2E7CB8, 4, 0, 0x0105));
  431:         instructions.push_back(makeOri(0x2E7CBC, 3, 5, 0xA000));
  432:         instructions.push_back(makeJr(0x2E7CC0, 31));
  433:         instructions.push_back(makeSw(0x2E7CC4, 4, 3, 0));
  434: 

--- Lines 425-459 ---
  425:         instructions.push_back(makeSw(0x2E7CA4, 6, 3, 0));
  426:         instructions.push_back(makeOri(0x2E7CA8, 3, 5, 0xE010));
  427:         instructions.push_back(makeSw(0x2E7CAC, 6, 3, 0));
  428:         instructions.push_back(makeOri(0x2E7CB0, 3, 5, 0xA030));
  429:         instructions.push_back(makeSw(0x2E7CB4, 4, 3, 0));
  430:         instructions.push_back(makeAddiu(0x2E7CB8, 4, 0, 0x0105));
  431:         instructions.push_back(makeOri(0x2E7CBC, 3, 5, 0xA000));
  432:         instructions.push_back(makeJr(0x2E7CC0, 31));
  433:         instructions.push_back(makeSw(0x2E7CC4, 4, 3, 0));
  434: 
  435:         CodeGenerator gen({}, {});
  436:         std::string generated = gen.generateFunction(func, instructions, false);
  437:         printGeneratedCode("GIF DMA kick coalesces when CHCR store is a return delay slot", generated);
  438: 
  439:         t.IsTrue(generated.find("label_2e7c9c:") != std::string::npos,
  440:                  "test should cover a branch target inside the GIF DMA setup");
  441:         t.IsTrue(generated.find("uint32_t gifDmaKickValue_2e7cb4_2 = GPR_U32(ctx, 4);") != std::string::npos,
  442:                  "TADR value should be captured before a0 is reused for CHCR");
  443:         t.IsTrue(generated.find("ctx->in_delay_slot = true;") != std::string::npos,
  444:                  "coalesced helper should still run as the return delay slot");
  445:         t.IsTrue(generated.find("runtime->kickGifDmaChainFromMMIO(rdram, ctx, 0x4u, 0x4u, gifDmaKickValue_2e7cb4_2, 0x105u);") != std::string::npos,
  446:                  "loadImage-like GIF DMA stores should coalesce into the native kick helper");
  447:         t.IsTrue(generated.find("WRITE32(ADD32(GPR_U32(ctx, 3), 0), GPR_U32(ctx, 4));") == std::string::npos,
  448:                  "coalesced delay-slot CHCR store should not remain as an individual WRITE32");
  449:     });
  450: 
  451:         tc.Run("emits labels and gotos for internal branches", [](TestCase &t) {
  452:             Function func;
  453:             func.name = "test_func";
  454:             func.start = 0x1000;
  455:         func.end = 0x1020;
  456:         func.isRecompiled = true;
  457:         func.isStub = false;
  458: 
  459:         // Build a small function:

--- Lines 432-466 ---
  432:         instructions.push_back(makeJr(0x2E7CC0, 31));
  433:         instructions.push_back(makeSw(0x2E7CC4, 4, 3, 0));
  434: 
  435:         CodeGenerator gen({}, {});
  436:         std::string generated = gen.generateFunction(func, instructions, false);
  437:         printGeneratedCode("GIF DMA kick coalesces when CHCR store is a return delay slot", generated);
  438: 
  439:         t.IsTrue(generated.find("label_2e7c9c:") != std::string::npos,
  440:                  "test should cover a branch target inside the GIF DMA setup");
  441:         t.IsTrue(generated.find("uint32_t gifDmaKickValue_2e7cb4_2 = GPR_U32(ctx, 4);") != std::string::npos,
  442:                  "TADR value should be captured before a0 is reused for CHCR");
  443:         t.IsTrue(generated.find("ctx->in_delay_slot = true;") != std::string::npos,
  444:                  "coalesced helper should still run as the return delay slot");
  445:         t.IsTrue(generated.find("runtime->kickGifDmaChainFromMMIO(rdram, ctx, 0x4u, 0x4u, gifDmaKickValue_2e7cb4_2, 0x105u);") != std::string::npos,
  446:                  "loadImage-like GIF DMA stores should coalesce into the native kick helper");
  447:         t.IsTrue(generated.find("WRITE32(ADD32(GPR_U32(ctx, 3), 0), GPR_U32(ctx, 4));") == std::string::npos,
  448:                  "coalesced delay-slot CHCR store should not remain as an individual WRITE32");
  449:     });
  450: 
  451:         tc.Run("emits labels and gotos for internal branches", [](TestCase &t) {
  452:             Function func;
  453:             func.name = "test_func";
  454:             func.start = 0x1000;
  455:         func.end = 0x1020;
  456:         func.isRecompiled = true;
  457:         func.isStub = false;
  458: 
  459:         // Build a small function:
  460:         // 0x1000: nop
  461:         // 0x1004: beq $1,$1, target (0x100c) with delay slot at 0x1008
  462:         // 0x1008: nop (delay slot)
  463:         // 0x100c: nop (branch target)
  464:         // 0x1010: nop (fallthrough)
  465:         std::vector<Instruction> instructions;
  466:         instructions.push_back(makeNop(0x1000));

--- Lines 449-483 ---
  449:     });
  450: 
  451:         tc.Run("emits labels and gotos for internal branches", [](TestCase &t) {
  452:             Function func;
  453:             func.name = "test_func";
  454:             func.start = 0x1000;
  455:         func.end = 0x1020;
  456:         func.isRecompiled = true;
  457:         func.isStub = false;
  458: 
  459:         // Build a small function:
  460:         // 0x1000: nop
  461:         // 0x1004: beq $1,$1, target (0x100c) with delay slot at 0x1008
  462:         // 0x1008: nop (delay slot)
  463:         // 0x100c: nop (branch target)
  464:         // 0x1010: nop (fallthrough)
  465:         std::vector<Instruction> instructions;
  466:         instructions.push_back(makeNop(0x1000));
  467:         instructions.push_back(makeBranch(0x1004, 1)); // target = 0x1004 + 4 + (1<<2) = 0x100c
  468:         instructions.push_back(makeNop(0x1008));       // delay slot
  469:         instructions.push_back(makeNop(0x100c));       // branch target
  470:         instructions.push_back(makeNop(0x1010));       // extra
  471: 
  472:         CodeGenerator gen({}, {});
  473:         std::string generated = gen.generateFunction(func, instructions, false);
  474:         printGeneratedCode("emits labels and gotos for internal branches", generated);
  475: 
  476:         t.IsTrue(generated.find("label_100c:") != std::string::npos, "branch target should emit a label");
  477:         t.IsTrue(generated.find("goto label_100c;") != std::string::npos, "internal branch should jump via goto");
  478:         t.IsTrue(generated.find("label_1008:") == std::string::npos, "delay slot without incoming branch should not get a label");
  479:     });
  480: 
  481:     tc.Run("labels delay slot when it is a branch target", [](TestCase &t) {
  482:         Function func;
  483:         func.name = "delay_slot_label";

--- Lines 450-484 ---
  450: 
  451:         tc.Run("emits labels and gotos for internal branches", [](TestCase &t) {
  452:             Function func;
  453:             func.name = "test_func";
  454:             func.start = 0x1000;
  455:         func.end = 0x1020;
  456:         func.isRecompiled = true;
  457:         func.isStub = false;
  458: 
  459:         // Build a small function:
  460:         // 0x1000: nop
  461:         // 0x1004: beq $1,$1, target (0x100c) with delay slot at 0x1008
  462:         // 0x1008: nop (delay slot)
  463:         // 0x100c: nop (branch target)
  464:         // 0x1010: nop (fallthrough)
  465:         std::vector<Instruction> instructions;
  466:         instructions.push_back(makeNop(0x1000));
  467:         instructions.push_back(makeBranch(0x1004, 1)); // target = 0x1004 + 4 + (1<<2) = 0x100c
  468:         instructions.push_back(makeNop(0x1008));       // delay slot
  469:         instructions.push_back(makeNop(0x100c));       // branch target
  470:         instructions.push_back(makeNop(0x1010));       // extra
  471: 
  472:         CodeGenerator gen({}, {});
  473:         std::string generated = gen.generateFunction(func, instructions, false);
  474:         printGeneratedCode("emits labels and gotos for internal branches", generated);
  475: 
  476:         t.IsTrue(generated.find("label_100c:") != std::string::npos, "branch target should emit a label");
  477:         t.IsTrue(generated.find("goto label_100c;") != std::string::npos, "internal branch should jump via goto");
  478:         t.IsTrue(generated.find("label_1008:") == std::string::npos, "delay slot without incoming branch should not get a label");
  479:     });
  480: 
  481:     tc.Run("labels delay slot when it is a branch target", [](TestCase &t) {
  482:         Function func;
  483:         func.name = "delay_slot_label";
  484:         func.start = 0x2000;

--- Lines 456-490 ---
  456:         func.isRecompiled = true;
  457:         func.isStub = false;
  458: 
  459:         // Build a small function:
  460:         // 0x1000: nop
  461:         // 0x1004: beq $1,$1, target (0x100c) with delay slot at 0x1008
  462:         // 0x1008: nop (delay slot)
  463:         // 0x100c: nop (branch target)
  464:         // 0x1010: nop (fallthrough)
  465:         std::vector<Instruction> instructions;
  466:         instructions.push_back(makeNop(0x1000));
  467:         instructions.push_back(makeBranch(0x1004, 1)); // target = 0x1004 + 4 + (1<<2) = 0x100c
  468:         instructions.push_back(makeNop(0x1008));       // delay slot
  469:         instructions.push_back(makeNop(0x100c));       // branch target
  470:         instructions.push_back(makeNop(0x1010));       // extra
  471: 
  472:         CodeGenerator gen({}, {});
  473:         std::string generated = gen.generateFunction(func, instructions, false);
  474:         printGeneratedCode("emits labels and gotos for internal branches", generated);
  475: 
  476:         t.IsTrue(generated.find("label_100c:") != std::string::npos, "branch target should emit a label");
  477:         t.IsTrue(generated.find("goto label_100c;") != std::string::npos, "internal branch should jump via goto");
  478:         t.IsTrue(generated.find("label_1008:") == std::string::npos, "delay slot without incoming branch should not get a label");
  479:     });
  480: 
  481:     tc.Run("labels delay slot when it is a branch target", [](TestCase &t) {
  482:         Function func;
  483:         func.name = "delay_slot_label";
  484:         func.start = 0x2000;
  485:         func.end = 0x2020;
  486:         func.isRecompiled = true;
  487:         func.isStub = false;
  488: 
  489:         // Branch at 0x2000 targets 0x2004 (its own delay slot)
  490:         std::vector<Instruction> instructions;

--- Lines 466-500 ---
  466:         instructions.push_back(makeNop(0x1000));
  467:         instructions.push_back(makeBranch(0x1004, 1)); // target = 0x1004 + 4 + (1<<2) = 0x100c
  468:         instructions.push_back(makeNop(0x1008));       // delay slot
  469:         instructions.push_back(makeNop(0x100c));       // branch target
  470:         instructions.push_back(makeNop(0x1010));       // extra
  471: 
  472:         CodeGenerator gen({}, {});
  473:         std::string generated = gen.generateFunction(func, instructions, false);
  474:         printGeneratedCode("emits labels and gotos for internal branches", generated);
  475: 
  476:         t.IsTrue(generated.find("label_100c:") != std::string::npos, "branch target should emit a label");
  477:         t.IsTrue(generated.find("goto label_100c;") != std::string::npos, "internal branch should jump via goto");
  478:         t.IsTrue(generated.find("label_1008:") == std::string::npos, "delay slot without incoming branch should not get a label");
  479:     });
  480: 
  481:     tc.Run("labels delay slot when it is a branch target", [](TestCase &t) {
  482:         Function func;
  483:         func.name = "delay_slot_label";
  484:         func.start = 0x2000;
  485:         func.end = 0x2020;
  486:         func.isRecompiled = true;
  487:         func.isStub = false;
  488: 
  489:         // Branch at 0x2000 targets 0x2004 (its own delay slot)
  490:         std::vector<Instruction> instructions;
  491:         instructions.push_back(makeBranch(0x2000, 0)); // target = 0x2004
  492:         instructions.push_back(makeNop(0x2004));       // delay slot and target
  493:         instructions.push_back(makeNop(0x2008));       // extra
  494: 
  495:         CodeGenerator gen({}, {});
  496:         std::string generated = gen.generateFunction(func, instructions, false);
  497:         printGeneratedCode("labels delay slot when it is a branch target", generated);
  498: 
  499:         t.IsTrue(generated.find("label_2004:") != std::string::npos, "delay slot that is a target should emit a label");
  500:         t.IsTrue(generated.find("goto label_2004;") != std::string::npos, "branch to delay slot should use goto");

--- Lines 469-503 ---
  469:         instructions.push_back(makeNop(0x100c));       // branch target
  470:         instructions.push_back(makeNop(0x1010));       // extra
  471: 
  472:         CodeGenerator gen({}, {});
  473:         std::string generated = gen.generateFunction(func, instructions, false);
  474:         printGeneratedCode("emits labels and gotos for internal branches", generated);
  475: 
  476:         t.IsTrue(generated.find("label_100c:") != std::string::npos, "branch target should emit a label");
  477:         t.IsTrue(generated.find("goto label_100c;") != std::string::npos, "internal branch should jump via goto");
  478:         t.IsTrue(generated.find("label_1008:") == std::string::npos, "delay slot without incoming branch should not get a label");
  479:     });
  480: 
  481:     tc.Run("labels delay slot when it is a branch target", [](TestCase &t) {
  482:         Function func;
  483:         func.name = "delay_slot_label";
  484:         func.start = 0x2000;
  485:         func.end = 0x2020;
  486:         func.isRecompiled = true;
  487:         func.isStub = false;
  488: 
  489:         // Branch at 0x2000 targets 0x2004 (its own delay slot)
  490:         std::vector<Instruction> instructions;
  491:         instructions.push_back(makeBranch(0x2000, 0)); // target = 0x2004
  492:         instructions.push_back(makeNop(0x2004));       // delay slot and target
  493:         instructions.push_back(makeNop(0x2008));       // extra
  494: 
  495:         CodeGenerator gen({}, {});
  496:         std::string generated = gen.generateFunction(func, instructions, false);
  497:         printGeneratedCode("labels delay slot when it is a branch target", generated);
  498: 
  499:         t.IsTrue(generated.find("label_2004:") != std::string::npos, "delay slot that is a target should emit a label");
  500:         t.IsTrue(generated.find("goto label_2004;") != std::string::npos, "branch to delay slot should use goto");
  501:     });
  502: 
  503:     tc.Run("control-flow analysis keeps same-function JAL target internal and promotes only the return pc", [](TestCase &t) {

--- Lines 477-511 ---
  477:         t.IsTrue(generated.find("goto label_100c;") != std::string::npos, "internal branch should jump via goto");
  478:         t.IsTrue(generated.find("label_1008:") == std::string::npos, "delay slot without incoming branch should not get a label");
  479:     });
  480: 
  481:     tc.Run("labels delay slot when it is a branch target", [](TestCase &t) {
  482:         Function func;
  483:         func.name = "delay_slot_label";
  484:         func.start = 0x2000;
  485:         func.end = 0x2020;
  486:         func.isRecompiled = true;
  487:         func.isStub = false;
  488: 
  489:         // Branch at 0x2000 targets 0x2004 (its own delay slot)
  490:         std::vector<Instruction> instructions;
  491:         instructions.push_back(makeBranch(0x2000, 0)); // target = 0x2004
  492:         instructions.push_back(makeNop(0x2004));       // delay slot and target
  493:         instructions.push_back(makeNop(0x2008));       // extra
  494: 
  495:         CodeGenerator gen({}, {});
  496:         std::string generated = gen.generateFunction(func, instructions, false);
  497:         printGeneratedCode("labels delay slot when it is a branch target", generated);
  498: 
  499:         t.IsTrue(generated.find("label_2004:") != std::string::npos, "delay slot that is a target should emit a label");
  500:         t.IsTrue(generated.find("goto label_2004;") != std::string::npos, "branch to delay slot should use goto");
  501:     });
  502: 
  503:     tc.Run("control-flow analysis keeps same-function JAL target internal and promotes only the return pc", [](TestCase &t) {
  504:         Function func;
  505:         func.name = "same_function_call";
  506:         func.start = 0x1000;
  507:         func.end = 0x101C;
  508:         func.isRecompiled = true;
  509:         func.isStub = false;
  510: 
  511:         std::vector<Instruction> instructions;

--- Lines 480-514 ---
  480: 
  481:     tc.Run("labels delay slot when it is a branch target", [](TestCase &t) {
  482:         Function func;
  483:         func.name = "delay_slot_label";
  484:         func.start = 0x2000;
  485:         func.end = 0x2020;
  486:         func.isRecompiled = true;
  487:         func.isStub = false;
  488: 
  489:         // Branch at 0x2000 targets 0x2004 (its own delay slot)
  490:         std::vector<Instruction> instructions;
  491:         instructions.push_back(makeBranch(0x2000, 0)); // target = 0x2004
  492:         instructions.push_back(makeNop(0x2004));       // delay slot and target
  493:         instructions.push_back(makeNop(0x2008));       // extra
  494: 
  495:         CodeGenerator gen({}, {});
  496:         std::string generated = gen.generateFunction(func, instructions, false);
  497:         printGeneratedCode("labels delay slot when it is a branch target", generated);
  498: 
  499:         t.IsTrue(generated.find("label_2004:") != std::string::npos, "delay slot that is a target should emit a label");
  500:         t.IsTrue(generated.find("goto label_2004;") != std::string::npos, "branch to delay slot should use goto");
  501:     });
  502: 
  503:     tc.Run("control-flow analysis keeps same-function JAL target internal and promotes only the return pc", [](TestCase &t) {
  504:         Function func;
  505:         func.name = "same_function_call";
  506:         func.start = 0x1000;
  507:         func.end = 0x101C;
  508:         func.isRecompiled = true;
  509:         func.isStub = false;
  510: 
  511:         std::vector<Instruction> instructions;
  512:         instructions.push_back(makeJal(0x1000, 0x100C));
  513:         instructions.push_back(makeNop(0x1004));
  514:         instructions.push_back(makeNop(0x1008));

--- Lines 485-519 ---
  485:         func.end = 0x2020;
  486:         func.isRecompiled = true;
  487:         func.isStub = false;
  488: 
  489:         // Branch at 0x2000 targets 0x2004 (its own delay slot)
  490:         std::vector<Instruction> instructions;
  491:         instructions.push_back(makeBranch(0x2000, 0)); // target = 0x2004
  492:         instructions.push_back(makeNop(0x2004));       // delay slot and target
  493:         instructions.push_back(makeNop(0x2008));       // extra
  494: 
  495:         CodeGenerator gen({}, {});
  496:         std::string generated = gen.generateFunction(func, instructions, false);
  497:         printGeneratedCode("labels delay slot when it is a branch target", generated);
  498: 
  499:         t.IsTrue(generated.find("label_2004:") != std::string::npos, "delay slot that is a target should emit a label");
  500:         t.IsTrue(generated.find("goto label_2004;") != std::string::npos, "branch to delay slot should use goto");
  501:     });
  502: 
  503:     tc.Run("control-flow analysis keeps same-function JAL target internal and promotes only the return pc", [](TestCase &t) {
  504:         Function func;
  505:         func.name = "same_function_call";
  506:         func.start = 0x1000;
  507:         func.end = 0x101C;
  508:         func.isRecompiled = true;
  509:         func.isStub = false;
  510: 
  511:         std::vector<Instruction> instructions;
  512:         instructions.push_back(makeJal(0x1000, 0x100C));
  513:         instructions.push_back(makeNop(0x1004));
  514:         instructions.push_back(makeNop(0x1008));
  515:         instructions.push_back(makeNop(0x100C));
  516:         instructions.push_back(makeNop(0x1010));
  517:         instructions.push_back(makeJr(0x1014, 31));
  518:         instructions.push_back(makeNop(0x1018));
  519: 

--- Lines 487-521 ---
  487:         func.isStub = false;
  488: 
  489:         // Branch at 0x2000 targets 0x2004 (its own delay slot)
  490:         std::vector<Instruction> instructions;
  491:         instructions.push_back(makeBranch(0x2000, 0)); // target = 0x2004
  492:         instructions.push_back(makeNop(0x2004));       // delay slot and target
  493:         instructions.push_back(makeNop(0x2008));       // extra
  494: 
  495:         CodeGenerator gen({}, {});
  496:         std::string generated = gen.generateFunction(func, instructions, false);
  497:         printGeneratedCode("labels delay slot when it is a branch target", generated);
  498: 
  499:         t.IsTrue(generated.find("label_2004:") != std::string::npos, "delay slot that is a target should emit a label");
  500:         t.IsTrue(generated.find("goto label_2004;") != std::string::npos, "branch to delay slot should use goto");
  501:     });
  502: 
  503:     tc.Run("control-flow analysis keeps same-function JAL target internal and promotes only the return pc", [](TestCase &t) {
  504:         Function func;
  505:         func.name = "same_function_call";
  506:         func.start = 0x1000;
  507:         func.end = 0x101C;
  508:         func.isRecompiled = true;
  509:         func.isStub = false;
  510: 
  511:         std::vector<Instruction> instructions;
  512:         instructions.push_back(makeJal(0x1000, 0x100C));
  513:         instructions.push_back(makeNop(0x1004));
  514:         instructions.push_back(makeNop(0x1008));
  515:         instructions.push_back(makeNop(0x100C));
  516:         instructions.push_back(makeNop(0x1010));
  517:         instructions.push_back(makeJr(0x1014, 31));
  518:         instructions.push_back(makeNop(0x1018));
  519: 
  520:         std::vector<Function> functions{func};
  521:         std::vector<Section> sections = {

--- Lines 488-522 ---
  488: 
  489:         // Branch at 0x2000 targets 0x2004 (its own delay slot)
  490:         std::vector<Instruction> instructions;
  491:         instructions.push_back(makeBranch(0x2000, 0)); // target = 0x2004
  492:         instructions.push_back(makeNop(0x2004));       // delay slot and target
  493:         instructions.push_back(makeNop(0x2008));       // extra
  494: 
  495:         CodeGenerator gen({}, {});
  496:         std::string generated = gen.generateFunction(func, instructions, false);
  497:         printGeneratedCode("labels delay slot when it is a branch target", generated);
  498: 
  499:         t.IsTrue(generated.find("label_2004:") != std::string::npos, "delay slot that is a target should emit a label");
  500:         t.IsTrue(generated.find("goto label_2004;") != std::string::npos, "branch to delay slot should use goto");
  501:     });
  502: 
  503:     tc.Run("control-flow analysis keeps same-function JAL target internal and promotes only the return pc", [](TestCase &t) {
  504:         Function func;
  505:         func.name = "same_function_call";
  506:         func.start = 0x1000;
  507:         func.end = 0x101C;
  508:         func.isRecompiled = true;
  509:         func.isStub = false;
  510: 
  511:         std::vector<Instruction> instructions;
  512:         instructions.push_back(makeJal(0x1000, 0x100C));
  513:         instructions.push_back(makeNop(0x1004));
  514:         instructions.push_back(makeNop(0x1008));
  515:         instructions.push_back(makeNop(0x100C));
  516:         instructions.push_back(makeNop(0x1010));
  517:         instructions.push_back(makeJr(0x1014, 31));
  518:         instructions.push_back(makeNop(0x1018));
  519: 
  520:         std::vector<Function> functions{func};
  521:         std::vector<Section> sections = {
  522:             {".text", 0x1000u, 0x100u, 0u, true, false, false, true, nullptr}

--- Lines 648-682 ---
  648:         CodeGenerator::AnalysisResult analysis = gen.collectInternalBranchTargets(func, instructions);
  649: 
  650:         t.IsTrue(analysis.indirectFallbackEntryPoints.contains(0x320Cu),
  651:                  "unresolved JALR should register internal labels as resumable entries for the owning function");
  652:         t.IsTrue(analysis.entryPoints.contains(0x320Cu),
  653:                  "unresolved JALR fallback targets should still emit labels in the owner");
  654:         t.IsFalse(analysis.jumpTableTargets.contains(0x3204u),
  655:                   "unresolved JALR should not pretend it has a resolved local jump table");
  656:     });
  657: 
  658:     tc.Run("syscall marks the following instruction as a resume entry", [](TestCase &t) {
  659:         // Shape of a real SDK syscall wrapper:
  660:         //   addiu $v1, $zero, <num> ; syscall ; jr $ra ; <delay slot>
  661:         Function func;
  662:         func.name = "syscall_wrapper";
  663:         func.start = 0x4000;
  664:         func.end = 0x4010;
  665:         func.isRecompiled = true;
  666:         func.isStub = false;
  667: 
  668:         std::vector<Instruction> instructions{
  669:             makeAddiu(0x4000, 3, 0, 0x83),
  670:             makeSyscall(0x4004),
  671:             makeJr(0x4008, 31),
  672:             makeNop(0x400C),
  673:         };
  674: 
  675:         CodeGenerator gen({}, {});
  676:         CodeGenerator::AnalysisResult analysis = gen.collectInternalBranchTargets(func, instructions);
  677: 
  678:         // +4, not +8: syscall has no delay slot.
  679:         t.IsTrue(analysis.resumeEntryPoints.contains(0x4008u),
  680:                  "syscall should mark the next instruction as resumable");
  681:         t.IsTrue(analysis.entryPoints.contains(0x4008u),
  682:                  "syscall resume pc should emit a label in the owner");

--- Lines 666-700 ---
  666:         func.isStub = false;
  667: 
  668:         std::vector<Instruction> instructions{
  669:             makeAddiu(0x4000, 3, 0, 0x83),
  670:             makeSyscall(0x4004),
  671:             makeJr(0x4008, 31),
  672:             makeNop(0x400C),
  673:         };
  674: 
  675:         CodeGenerator gen({}, {});
  676:         CodeGenerator::AnalysisResult analysis = gen.collectInternalBranchTargets(func, instructions);
  677: 
  678:         // +4, not +8: syscall has no delay slot.
  679:         t.IsTrue(analysis.resumeEntryPoints.contains(0x4008u),
  680:                  "syscall should mark the next instruction as resumable");
  681:         t.IsTrue(analysis.entryPoints.contains(0x4008u),
  682:                  "syscall resume pc should emit a label in the owner");
  683:         t.IsFalse(analysis.resumeEntryPoints.contains(0x400Cu),
  684:                   "syscall must not claim a delay slot it does not have");
  685:     });
  686: 
  687:     tc.Run("resume entry targets emit a top-level pc switch in the owner wrapper", [](TestCase &t) {
  688:         Function func;
  689:         func.name = "resume_owner";
  690:         func.start = 0x6000;
  691:         func.end = 0x6010;
  692:         func.isRecompiled = true;
  693:         func.isStub = false;
  694: 
  695:         std::vector<Instruction> instructions{
  696:             makeNop(0x6000),
  697:             makeNop(0x6004),
  698:             makeNop(0x6008),
  699:             makeNop(0x600C)
  700:         };

--- Lines 672-706 ---
  672:             makeNop(0x400C),
  673:         };
  674: 
  675:         CodeGenerator gen({}, {});
  676:         CodeGenerator::AnalysisResult analysis = gen.collectInternalBranchTargets(func, instructions);
  677: 
  678:         // +4, not +8: syscall has no delay slot.
  679:         t.IsTrue(analysis.resumeEntryPoints.contains(0x4008u),
  680:                  "syscall should mark the next instruction as resumable");
  681:         t.IsTrue(analysis.entryPoints.contains(0x4008u),
  682:                  "syscall resume pc should emit a label in the owner");
  683:         t.IsFalse(analysis.resumeEntryPoints.contains(0x400Cu),
  684:                   "syscall must not claim a delay slot it does not have");
  685:     });
  686: 
  687:     tc.Run("resume entry targets emit a top-level pc switch in the owner wrapper", [](TestCase &t) {
  688:         Function func;
  689:         func.name = "resume_owner";
  690:         func.start = 0x6000;
  691:         func.end = 0x6010;
  692:         func.isRecompiled = true;
  693:         func.isStub = false;
  694: 
  695:         std::vector<Instruction> instructions{
  696:             makeNop(0x6000),
  697:             makeNop(0x6004),
  698:             makeNop(0x6008),
  699:             makeNop(0x600C)
  700:         };
  701: 
  702:         CodeGenerator gen({}, {});
  703:         gen.setResumeEntryTargets({{0x6000u, {0x6008u}}});
  704: 
  705:         std::string generated = gen.generateFunction(func, instructions, false);
  706:         printGeneratedCode("resume entry targets emit a top-level pc switch in the owner wrapper", generated);

--- Lines 824-858 ---
  824:         func.name = "external_branch";
  825:         func.start = 0x3000;
  826:         func.end = 0x3020;
  827:         func.isRecompiled = true;
  828:         func.isStub = false;
  829: 
  830:         // Branch targets outside the function range
  831:         std::vector<Instruction> instructions;
  832:         instructions.push_back(makeBranch(0x3000, 4)); // target = 0x3014 (inside) -> make it outside by adjusting end? easier: set end smaller? Instead use large offset
  833:         instructions.clear();
  834:         Instruction br = makeBranch(0x3000, 0x100); // target far outside
  835:         instructions.push_back(br);
  836:         instructions.push_back(makeNop(0x3004)); // delay slot
  837: 
  838:         CodeGenerator gen({}, {});
  839:         std::string generated = gen.generateFunction(func, instructions, false);
  840:         printGeneratedCode("branches outside function still set pc", generated);
  841: 
  842:         t.IsTrue(generated.find("ctx->pc = 0x") != std::string::npos, "external branch should set ctx->pc");
  843:         t.IsTrue(generated.find("goto label_") == std::string::npos, "external branch should not use goto");
  844:     });
  845: 
  846:     tc.Run("jumps to known symbols call by name", [](TestCase &t) {
  847:         Function func;
  848:         func.name = "call_symbol";
  849:         func.start = 0x4000;
  850:         func.end = 0x4018;
  851:         func.isRecompiled = true;
  852:         func.isStub = false;
  853: 
  854:         Symbol targetSym;
  855:         targetSym.name = "target_func";
  856:         targetSym.address = 0x5000;
  857:         targetSym.isFunction = true;
  858: 

--- Lines 1488-1522 ---
 1488:             func.name = "jal_test";
 1489:             func.start = 0xA000;
 1490:             func.end = 0xA020;
 1491:             func.isRecompiled = true;
 1492:             func.isStub = false;
 1493: 
 1494:             Symbol targetSym;
 1495:             targetSym.name = "some_func";
 1496:             targetSym.address = 0xB000;
 1497:             targetSym.isFunction = true;
 1498: 
 1499:             // 0xA000: JAL 0xB000
 1500:             // 0xA004: NOP (delay slot)
 1501:             Instruction jal = makeJal(0xA000, 0xB000);
 1502:             Instruction delay = makeNop(0xA004);
 1503:             
 1504:             CodeGenerator gen({targetSym}, {});
 1505:             std::string generated = gen.generateFunction(func, {jal, delay}, false);
 1506:             printGeneratedCode("JAL to known function emits call and check", generated);
 1507: 
 1508:             // Expect:
 1509:             // SET_GPR_U32(ctx, 31, 0xA008u);
 1510:             // ctx->pc = 0xA004u;
 1511:             // ... delay slot ...
 1512:             // runtime->dispatchGuestBranch(..., DirectCall, "JAL")
 1513: 
 1514:             t.IsTrue(generated.find("SET_GPR_U32(ctx, 31, 0xA008u);") != std::string::npos, "JAL should set RA");
 1515:             t.IsTrue(generated.find("runtime->dispatchGuestBranch(rdram, ctx, 0xB000u") != std::string::npos,
 1516:                      "JAL should dispatch through the runtime branch helper");
 1517:             t.IsTrue(generated.find("PS2Runtime::GuestBranchKind::DirectCall") != std::string::npos,
 1518:                      "JAL should identify itself as a direct call");
 1519:             t.IsTrue(generated.find("0xA000u, 0xA008u") != std::string::npos,
 1520:                      "JAL should pass call-site and fallthrough PCs to the runtime helper");
 1521:         });
 1522: 

--- Lines 1499-1533 ---
 1499:             // 0xA000: JAL 0xB000
 1500:             // 0xA004: NOP (delay slot)
 1501:             Instruction jal = makeJal(0xA000, 0xB000);
 1502:             Instruction delay = makeNop(0xA004);
 1503:             
 1504:             CodeGenerator gen({targetSym}, {});
 1505:             std::string generated = gen.generateFunction(func, {jal, delay}, false);
 1506:             printGeneratedCode("JAL to known function emits call and check", generated);
 1507: 
 1508:             // Expect:
 1509:             // SET_GPR_U32(ctx, 31, 0xA008u);
 1510:             // ctx->pc = 0xA004u;
 1511:             // ... delay slot ...
 1512:             // runtime->dispatchGuestBranch(..., DirectCall, "JAL")
 1513: 
 1514:             t.IsTrue(generated.find("SET_GPR_U32(ctx, 31, 0xA008u);") != std::string::npos, "JAL should set RA");
 1515:             t.IsTrue(generated.find("runtime->dispatchGuestBranch(rdram, ctx, 0xB000u") != std::string::npos,
 1516:                      "JAL should dispatch through the runtime branch helper");
 1517:             t.IsTrue(generated.find("PS2Runtime::GuestBranchKind::DirectCall") != std::string::npos,
 1518:                      "JAL should identify itself as a direct call");
 1519:             t.IsTrue(generated.find("0xA000u, 0xA008u") != std::string::npos,
 1520:                      "JAL should pass call-site and fallthrough PCs to the runtime helper");
 1521:         });
 1522: 
 1523:         tc.Run("JAL to a resolved syscall publishes fallthrough before the handler", [](TestCase &t) {
 1524:             Function func;
 1525:             func.name = "jal_syscall_resume";
 1526:             func.start = 0xA040;
 1527:             func.end = 0xA048;
 1528:             func.isRecompiled = true;
 1529: 
 1530:             Symbol target;
 1531:             target.name = "GetThreadId";
 1532:             target.address = 0xB040;
 1533:             target.isFunction = true;

--- Lines 1540-1574 ---
 1540:             const size_t handler = generated.find("ps2_syscalls::GetThreadId(rdram, ctx, runtime);");
 1541: 
 1542:             t.IsTrue(continuation != std::string::npos,
 1543:                      "a resolved HLE JAL should publish its fallthrough PC");
 1544:             t.IsTrue(handler != std::string::npos,
 1545:                      "the resolved syscall handler should still be called directly");
 1546:             t.IsTrue(continuation < handler,
 1547:                      "the fallthrough must be restart-safe before a blocking HLE handler runs");
 1548:             t.IsTrue(generated.find("__entryPc") == std::string::npos,
 1549:                      "resolved HLE calls must not retain the unchanged-PC compatibility guard");
 1550:         });
 1551: 
 1552:         tc.Run("trailing JAL without decoded delay slot still emits call flow", [](TestCase &t) {
 1553:             Function func;
 1554:             func.name = "jal_truncated";
 1555:             func.start = 0xA100;
 1556:             func.end = 0xA108;
 1557:             func.isRecompiled = true;
 1558:             func.isStub = false;
 1559: 
 1560:             Symbol targetSym;
 1561:             targetSym.name = "some_func";
 1562:             targetSym.address = 0xB000;
 1563:             targetSym.isFunction = true;
 1564: 
 1565:             Instruction jal = makeJal(0xA100, 0xB000);
 1566: 
 1567:             CodeGenerator gen({targetSym}, {});
 1568:             std::string generated = gen.generateFunction(func, {jal}, false);
 1569:             printGeneratedCode("trailing JAL without decoded delay slot still emits call flow", generated);
 1570: 
 1571:             t.IsTrue(generated.find("SET_GPR_U32(ctx, 31, 0xA108u);") != std::string::npos,
 1572:                      "truncated trailing JAL should still set RA");
 1573:             t.IsTrue(generated.find("runtime->dispatchGuestBranch(rdram, ctx, 0xB000u") != std::string::npos,
 1574:                      "truncated trailing JAL should still emit the call dispatch");

--- Lines 1557-1591 ---
 1557:             func.isRecompiled = true;
 1558:             func.isStub = false;
 1559: 
 1560:             Symbol targetSym;
 1561:             targetSym.name = "some_func";
 1562:             targetSym.address = 0xB000;
 1563:             targetSym.isFunction = true;
 1564: 
 1565:             Instruction jal = makeJal(0xA100, 0xB000);
 1566: 
 1567:             CodeGenerator gen({targetSym}, {});
 1568:             std::string generated = gen.generateFunction(func, {jal}, false);
 1569:             printGeneratedCode("trailing JAL without decoded delay slot still emits call flow", generated);
 1570: 
 1571:             t.IsTrue(generated.find("SET_GPR_U32(ctx, 31, 0xA108u);") != std::string::npos,
 1572:                      "truncated trailing JAL should still set RA");
 1573:             t.IsTrue(generated.find("runtime->dispatchGuestBranch(rdram, ctx, 0xB000u") != std::string::npos,
 1574:                      "truncated trailing JAL should still emit the call dispatch");
 1575:             t.IsTrue(generated.find("0xA100u, 0xA108u") != std::string::npos,
 1576:                      "truncated trailing JAL should still pass the fallthrough to runtime dispatch");
 1577:             t.IsTrue(generated.find("// JAL 0xB000 - Handled by branch logic") == std::string::npos,
 1578:                      "truncated trailing JAL must not degrade to comment-only output");
 1579:         });
 1580: 
 1581:         tc.Run("JAL to internal target becomes goto", [](TestCase &t) {
 1582:             Function func;
 1583:             func.name = "jal_internal";
 1584:             func.start = 0xC000;
 1585:             func.end = 0xC020;
 1586:             func.isRecompiled = true;
 1587:             func.isStub = false;
 1588: 
 1589:             // 0xC000: JAL 0xC010
 1590:             // 0xC004: NOP
 1591:             // ...

--- Lines 1693-1727 ---
 1693:             t.IsTrue(generated.find("ctx->pc = 0x1104u;") != std::string::npos,
 1694:                      "backward internal branch should preserve the loop target in ctx->pc");
 1695:             t.IsTrue(generated.find("if (runtime->eeCheckpointDue()) {") != std::string::npos,
 1696:                      "backward internal branch should consult the EE event checkpoint before re-entering the loop");
 1697:             t.IsTrue(generated.find("return;") != std::string::npos,
 1698:                      "backward internal branch should return to the dispatcher when the runtime preemption policy requests it");
 1699:             t.IsTrue(generated.find("runtime->cooperativeGuestYield();") == std::string::npos,
 1700:                      "backward internal branch should no longer emit an unconditional cooperative-yield call");
 1701:             t.IsTrue(generated.find("goto label_1104;") != std::string::npos,
 1702:                      "backward internal branch should still re-enter the in-function label when it keeps the current slice");
 1703:         });
 1704: 
 1705:         tc.Run("branch-likely places delay slot only in taken path", [](TestCase &t) {
 1706:             Function func;
 1707:             func.name = "branch_likely";
 1708:             func.start = 0x1200;
 1709:             func.end = 0x1220;
 1710:             func.isRecompiled = true;
 1711:             func.isStub = false;
 1712: 
 1713:             Instruction br{};
 1714:             br.address = 0x1200;
 1715:             br.opcode = OPCODE_BEQL;   // likely
 1716:             br.rs = 1;
 1717:             br.rt = 2;
 1718:             br.simmediate = 1;         // target = 0x1208
 1719:             br.isBranch = true;
 1720:             br.hasDelaySlot = true;
 1721:             br.raw = 0;  
 1722: 
 1723:             Instruction delay{};
 1724:             delay.address = 0x1204;
 1725:             delay.opcode = OPCODE_ADDIU;
 1726:             delay.rs = 0;
 1727:             delay.rt = 7;              // make it non-nop so translation is distinctive

--- Lines 1723-1757 ---
 1723:             Instruction delay{};
 1724:             delay.address = 0x1204;
 1725:             delay.opcode = OPCODE_ADDIU;
 1726:             delay.rs = 0;
 1727:             delay.rt = 7;              // make it non-nop so translation is distinctive
 1728:             delay.simmediate = 123;
 1729:             delay.raw = 0;
 1730: 
 1731:             Instruction target = makeNop(0x1208);
 1732: 
 1733:             CodeGenerator gen({}, {});
 1734:             std::string generated = gen.generateFunction(func, { br, delay, target }, false);
 1735:             printGeneratedCode("branch-likely places delay slot only in taken path", generated);
 1736:  
 1737:             t.IsTrue(generated.find("SET_GPR_S32(ctx, 7,") != std::string::npos, "delay slot should be translated");
 1738:             t.IsTrue(generated.find("if (branch_taken_0x1200)") != std::string::npos, "should generate branch_taken variable and if for likely branch");
 1739:         });
 1740: 
 1741:         tc.Run("sign branches compare the full 64-bit register", [](TestCase &t) {
 1742:             // libmpeg polls IPU_CMD with ld and bgezl; a 32-bit test reads DATA bit 31 as BUSY.
 1743:             const auto conditionFor = [](uint8_t opcode, uint8_t rt) {
 1744:                 Function func;
 1745:                 func.name = "sign_branch";
 1746:                 func.start = 0x1300;
 1747:                 func.end = 0x1310;
 1748:                 func.isRecompiled = true;
 1749:                 func.isStub = false;
 1750: 
 1751:                 Instruction br{};
 1752:                 br.address = 0x1300;
 1753:                 br.opcode = opcode;
 1754:                 br.rs = 17;
 1755:                 br.rt = rt;
 1756:                 br.simmediate = 1;
 1757:                 br.isBranch = true;

--- Lines 1725-1759 ---
 1725:             delay.opcode = OPCODE_ADDIU;
 1726:             delay.rs = 0;
 1727:             delay.rt = 7;              // make it non-nop so translation is distinctive
 1728:             delay.simmediate = 123;
 1729:             delay.raw = 0;
 1730: 
 1731:             Instruction target = makeNop(0x1208);
 1732: 
 1733:             CodeGenerator gen({}, {});
 1734:             std::string generated = gen.generateFunction(func, { br, delay, target }, false);
 1735:             printGeneratedCode("branch-likely places delay slot only in taken path", generated);
 1736:  
 1737:             t.IsTrue(generated.find("SET_GPR_S32(ctx, 7,") != std::string::npos, "delay slot should be translated");
 1738:             t.IsTrue(generated.find("if (branch_taken_0x1200)") != std::string::npos, "should generate branch_taken variable and if for likely branch");
 1739:         });
 1740: 
 1741:         tc.Run("sign branches compare the full 64-bit register", [](TestCase &t) {
 1742:             // libmpeg polls IPU_CMD with ld and bgezl; a 32-bit test reads DATA bit 31 as BUSY.
 1743:             const auto conditionFor = [](uint8_t opcode, uint8_t rt) {
 1744:                 Function func;
 1745:                 func.name = "sign_branch";
 1746:                 func.start = 0x1300;
 1747:                 func.end = 0x1310;
 1748:                 func.isRecompiled = true;
 1749:                 func.isStub = false;
 1750: 
 1751:                 Instruction br{};
 1752:                 br.address = 0x1300;
 1753:                 br.opcode = opcode;
 1754:                 br.rs = 17;
 1755:                 br.rt = rt;
 1756:                 br.simmediate = 1;
 1757:                 br.isBranch = true;
 1758:                 br.hasDelaySlot = true;
 1759: 

--- Lines 1726-1760 ---
 1726:             delay.rs = 0;
 1727:             delay.rt = 7;              // make it non-nop so translation is distinctive
 1728:             delay.simmediate = 123;
 1729:             delay.raw = 0;
 1730: 
 1731:             Instruction target = makeNop(0x1208);
 1732: 
 1733:             CodeGenerator gen({}, {});
 1734:             std::string generated = gen.generateFunction(func, { br, delay, target }, false);
 1735:             printGeneratedCode("branch-likely places delay slot only in taken path", generated);
 1736:  
 1737:             t.IsTrue(generated.find("SET_GPR_S32(ctx, 7,") != std::string::npos, "delay slot should be translated");
 1738:             t.IsTrue(generated.find("if (branch_taken_0x1200)") != std::string::npos, "should generate branch_taken variable and if for likely branch");
 1739:         });
 1740: 
 1741:         tc.Run("sign branches compare the full 64-bit register", [](TestCase &t) {
 1742:             // libmpeg polls IPU_CMD with ld and bgezl; a 32-bit test reads DATA bit 31 as BUSY.
 1743:             const auto conditionFor = [](uint8_t opcode, uint8_t rt) {
 1744:                 Function func;
 1745:                 func.name = "sign_branch";
 1746:                 func.start = 0x1300;
 1747:                 func.end = 0x1310;
 1748:                 func.isRecompiled = true;
 1749:                 func.isStub = false;
 1750: 
 1751:                 Instruction br{};
 1752:                 br.address = 0x1300;
 1753:                 br.opcode = opcode;
 1754:                 br.rs = 17;
 1755:                 br.rt = rt;
 1756:                 br.simmediate = 1;
 1757:                 br.isBranch = true;
 1758:                 br.hasDelaySlot = true;
 1759: 
 1760:                 CodeGenerator gen({}, {});

--- Lines 1771-1805 ---
 1771:             func.name = "jr_ra_return";
 1772:             func.start = 0x1300;
 1773:             func.end = 0x1340;
 1774:             func.isRecompiled = true;
 1775:             func.isStub = false;
 1776: 
 1777:             // Create an internal JAL with an explicit instruction at returnAddr (0x1308).
 1778:             Instruction jal = makeJal(0x1300, 0x1310);
 1779:             Instruction jalDelay = makeNop(0x1304);
 1780:             Instruction atReturn = makeNop(0x1308);
 1781:             Instruction atTarget = makeNop(0x1310);
 1782: 
 1783:             // JR $31 at 0x1314 with delay slot at 0x1318
 1784:             Instruction jr = makeJr(0x1314, 31);
 1785:             Instruction jrDelay = makeNop(0x1318);
 1786: 
 1787:             CodeGenerator gen({}, {});
 1788:             std::string generated = gen.generateFunction(func, { jal, jalDelay, atReturn, atTarget, jr, jrDelay }, false);
 1789:             printGeneratedCode("JR $31 returns through dynamic target without broad local switch", generated);
 1790: 
 1791:             t.IsTrue(generated.find("const uint32_t jumpTarget = GPR_U32(ctx, 31);") != std::string::npos,
 1792:                      "JR $31 should still read the dynamic return target");
 1793:             t.IsFalse(generated.find("switch (jumpTarget)") != std::string::npos,
 1794:                       "JR $31 should not emit a broad local switch over internal labels");
 1795:             t.IsTrue(generated.find("label_1308:") != std::string::npos,
 1796:                      "internal JAL return address should still be emitted as a label");
 1797:             t.IsTrue(generated.find("        return;") != std::string::npos,
 1798:                      "JR $31 should return to the dispatcher/runtime after setting ctx->pc");
 1799:             t.IsTrue(generated.find("PS2Runtime::GuestBranchKind::Return") != std::string::npos,
 1800:                      "JR $31 should use the Return branch kind for precise diagnostics");
 1801:             t.IsTrue(generated.find("\"JR $ra\"") != std::string::npos,
 1802:                      "JR $31 should pass a return-specific debug name");
 1803:         });
 1804: 
 1805:         tc.Run("trailing JR $31 without decoded delay slot still emits return flow", [](TestCase &t) {

--- Lines 1793-1827 ---
 1793:             t.IsFalse(generated.find("switch (jumpTarget)") != std::string::npos,
 1794:                       "JR $31 should not emit a broad local switch over internal labels");
 1795:             t.IsTrue(generated.find("label_1308:") != std::string::npos,
 1796:                      "internal JAL return address should still be emitted as a label");
 1797:             t.IsTrue(generated.find("        return;") != std::string::npos,
 1798:                      "JR $31 should return to the dispatcher/runtime after setting ctx->pc");
 1799:             t.IsTrue(generated.find("PS2Runtime::GuestBranchKind::Return") != std::string::npos,
 1800:                      "JR $31 should use the Return branch kind for precise diagnostics");
 1801:             t.IsTrue(generated.find("\"JR $ra\"") != std::string::npos,
 1802:                      "JR $31 should pass a return-specific debug name");
 1803:         });
 1804: 
 1805:         tc.Run("trailing JR $31 without decoded delay slot still emits return flow", [](TestCase &t) {
 1806:             Function func;
 1807:             func.name = "jr_ra_truncated";
 1808:             func.start = 0x1500;
 1809:             func.end = 0x1540;
 1810:             func.isRecompiled = true;
 1811:             func.isStub = false;
 1812: 
 1813:             Instruction jal = makeJal(0x1500, 0x1510);
 1814:             Instruction jalDelay = makeNop(0x1504);
 1815:             Instruction atReturn = makeNop(0x1508);
 1816:             Instruction atTarget = makeNop(0x1510);
 1817:             Instruction jr = makeJr(0x1514, 31);
 1818: 
 1819:             CodeGenerator gen({}, {});
 1820:             std::string generated = gen.generateFunction(func, {jal, jalDelay, atReturn, atTarget, jr}, false);
 1821:             printGeneratedCode("trailing JR $31 without decoded delay slot still emits return flow", generated);
 1822: 
 1823:             t.IsTrue(generated.find("const uint32_t jumpTarget = GPR_U32(ctx, 31);") != std::string::npos,
 1824:                      "truncated trailing JR should still read the return target");
 1825:             t.IsFalse(generated.find("switch (jumpTarget)") != std::string::npos,
 1826:                       "truncated trailing JR should not emit a broad local return-target switch");
 1827:             t.IsTrue(generated.find("label_1508:") != std::string::npos,

--- Lines 1809-1843 ---
 1809:             func.end = 0x1540;
 1810:             func.isRecompiled = true;
 1811:             func.isStub = false;
 1812: 
 1813:             Instruction jal = makeJal(0x1500, 0x1510);
 1814:             Instruction jalDelay = makeNop(0x1504);
 1815:             Instruction atReturn = makeNop(0x1508);
 1816:             Instruction atTarget = makeNop(0x1510);
 1817:             Instruction jr = makeJr(0x1514, 31);
 1818: 
 1819:             CodeGenerator gen({}, {});
 1820:             std::string generated = gen.generateFunction(func, {jal, jalDelay, atReturn, atTarget, jr}, false);
 1821:             printGeneratedCode("trailing JR $31 without decoded delay slot still emits return flow", generated);
 1822: 
 1823:             t.IsTrue(generated.find("const uint32_t jumpTarget = GPR_U32(ctx, 31);") != std::string::npos,
 1824:                      "truncated trailing JR should still read the return target");
 1825:             t.IsFalse(generated.find("switch (jumpTarget)") != std::string::npos,
 1826:                       "truncated trailing JR should not emit a broad local return-target switch");
 1827:             t.IsTrue(generated.find("label_1508:") != std::string::npos,
 1828:                      "truncated trailing JR should still include the internal return label");
 1829:             t.IsTrue(generated.find("// JR $31 - Handled by branch logic") == std::string::npos,
 1830:                      "truncated trailing JR must not degrade to comment-only output");
 1831:             t.IsTrue(generated.find("PS2Runtime::GuestBranchKind::Return") != std::string::npos,
 1832:                      "truncated JR $31 should still use return diagnostics");
 1833:         });
 1834: 
 1835:         tc.Run("unresolved JR non-RA uses dispatcher resume entries without broad local switch", [](TestCase &t) {
 1836:             Function func;
 1837:             func.name = "jr_non_ra_dispatcher_resume";
 1838:             func.start = 0x1400;
 1839:             func.end = 0x1420;
 1840:             func.isRecompiled = true;
 1841:             func.isStub = false;
 1842: 
 1843:             // 0x1400: nop

--- Lines 1833-1867 ---
 1833:         });
 1834: 
 1835:         tc.Run("unresolved JR non-RA uses dispatcher resume entries without broad local switch", [](TestCase &t) {
 1836:             Function func;
 1837:             func.name = "jr_non_ra_dispatcher_resume";
 1838:             func.start = 0x1400;
 1839:             func.end = 0x1420;
 1840:             func.isRecompiled = true;
 1841:             func.isStub = false;
 1842: 
 1843:             // 0x1400: nop
 1844:             // 0x1404: jr $16 (register jump)
 1845:             // 0x1408: nop (delay slot)
 1846:             // 0x140c: nop
 1847:             Instruction i0 = makeNop(0x1400);
 1848:             Instruction jr = makeJr(0x1404, 16);
 1849:             Instruction delay = makeNop(0x1408);
 1850:             Instruction i3 = makeNop(0x140c);
 1851: 
 1852:             CodeGenerator gen({}, {});
 1853:             CodeGenerator::AnalysisResult analysis = gen.collectInternalBranchTargets(func, {i0, jr, delay, i3});
 1854:             gen.setResumeEntryTargets({{func.start, std::vector<uint32_t>(
 1855:                                                         analysis.indirectFallbackEntryPoints.begin(),
 1856:                                                         analysis.indirectFallbackEntryPoints.end())}});
 1857:             std::string generated = gen.generateFunction(func, {i0, jr, delay, i3}, false);
 1858:             printGeneratedCode("unresolved JR non-RA uses dispatcher resume entries without broad local switch", generated);
 1859: 
 1860:             t.IsFalse(generated.find("switch (jumpTarget)") != std::string::npos,
 1861:                       "unresolved JR via non-RA register should not emit a broad local switch over internal labels");
 1862:             t.IsTrue(generated.find("switch (ctx->pc)") != std::string::npos,
 1863:                      "JR fallback labels should be promoted to dispatcher resume sites");
 1864:             t.IsTrue(generated.find("case 0x140cu: goto label_140c;") != std::string::npos,
 1865:                      "owner resume switch should include internal fallback labels");
 1866:             t.IsTrue(generated.find("ctx->pc = jumpTarget;") != std::string::npos,
 1867:                      "unresolved JR should hand the dynamic target back through ctx->pc");

--- Lines 2171-2205 ---
 2171:             tailDelay.raw = 0;
 2172: 
 2173:             CodeGenerator gen({}, {});
 2174:             std::string generated = gen.generateFunction(
 2175:                 func,
 2176:                 {prolog, saveRa, jalr, jalrDelay, restoreRa, tailJump, tailDelay},
 2177:                 false);
 2178:             printGeneratedCode("JALR fallback should not expose epilogue tail-jump labels", generated);
 2179: 
 2180:             t.IsTrue(generated.find("case 0x2014u: goto label_2014;") == std::string::npos,
 2181:                      "jalr fallback should not dispatch directly to epilogue tail-jump block");
 2182:             t.IsTrue(generated.find("case 0x2018u: goto label_2018;") == std::string::npos,
 2183:                      "jalr fallback should not dispatch directly to tail-jump delay slot");
 2184:         });
 2185: 
 2186:         tc.Run("VU random helpers emit line comments on separate lines", [](TestCase &t) {
 2187:             CodeGenerator gen({}, {});
 2188: 
 2189:             Instruction inst{};
 2190:             inst.rd = 7;
 2191:             inst.vectorInfo.fsf = 2;
 2192: 
 2193:             std::string vrnext = gen.translateVU_VRNEXT(inst);
 2194:             printGeneratedCode("VU random helpers emit line comments on separate lines - VRNEXT", vrnext);
 2195:             t.IsTrue(vrnext.find("// Simple LFSR-based random number generation (PS2-like behavior)\n"
 2196:                                  "    uint32_t feedback") != std::string::npos,
 2197:                      "VRNEXT should place the generated line comment on its own line");
 2198: 
 2199:             std::string vrinit = gen.translateVU_VRINIT(inst);
 2200:             printGeneratedCode("VU random helpers emit line comments on separate lines - VRINIT", vrinit);
 2201:             t.IsTrue(vrinit.find("// PS2 uses a specific LFSR initialization pattern\n"
 2202:                                  "    if (seed == 0) seed = 1;") != std::string::npos,
 2203:                      "VRINIT should place the generated line comment on its own line");
 2204: 
 2205:             std::string vrxor = gen.translateVU_VRXOR(inst);

========== D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\src\r5900_decoder_tests.cpp ==========

--- Lines 9-43 ---
    9:                    {
   10:     tc.Run("decodes JAL with jump target and call flag", [](TestCase &t) {
   11:         // jal 0x00400000 at address 0x1000 => opcode 0x0C100000 (target = 0x00400000 >> 2)
   12:         uint32_t address = 0x1000;
   13:         uint32_t target = 0x00400000;
   14:         uint32_t raw = (OPCODE_JAL << 26) | ((target >> 2) & 0x03FFFFFF);
   15: 
   16:         R5900Decoder decoder;
   17:         Instruction inst = decoder.decodeInstruction(address, raw);
   18: 
   19:         t.IsTrue(inst.isJump, "jal should be marked as jump");
   20:         t.IsTrue(inst.isCall, "jal should be marked as call");
   21:         t.IsTrue(inst.hasDelaySlot, "jal has a delay slot");
   22:         t.Equals(decoder.getJumpTarget(inst), target, "jal jump target should match encoded target");
   23:     });
   24: 
   25:     tc.Run("J computes target with upper PC bits", [](TestCase &t) {
   26:         // Place J at address 0x8FFF_FFFC targeting 0x8123_4560 (upper bits from PC+4)
   27:         uint32_t address = 0x8FFFFFFC;
   28:         uint32_t encodedTarget = 0x0123456; // 0x048D1598 >> 2, but we want lower bits of 0x1234560
   29:         uint32_t raw = (OPCODE_J << 26) | (encodedTarget & 0x03FFFFFF);
   30: 
   31:         R5900Decoder decoder;
   32:         Instruction inst = decoder.decodeInstruction(address, raw);
   33: 
   34:         uint32_t expectedPcUpper = (address + 4) & 0xF0000000;
   35:         uint32_t expected = expectedPcUpper | (encodedTarget << 2);
   36:         t.Equals(decoder.getJumpTarget(inst), expected, "J target should combine PC upper bits with encoded target");
   37:     });
   38: 
   39:     tc.Run("JR/JALR jump target is zero (dynamic)", [](TestCase &t) {
   40:         uint32_t address = 0x1200;
   41:         uint32_t jrRaw = (OPCODE_SPECIAL << 26) | (2 << 21) | SPECIAL_JR;
   42:         uint32_t jalrRaw = (OPCODE_SPECIAL << 26) | (3 << 21) | (31 << 11) | SPECIAL_JALR;
   43: 

--- Lines 50-84 ---
   50:     });
   51: 
   52:     tc.Run("decodes BEQ sets branch flags and target", [](TestCase &t) {
   53:         // beq r1, r2, offset 0x4 (word offset) at address 0x2000
   54:         uint32_t address = 0x2000;
   55:         uint16_t offset = 0x0004;
   56:         uint32_t raw = (OPCODE_BEQ << 26) | (1 << 21) | (2 << 16) | offset;
   57: 
   58:         R5900Decoder decoder;
   59:         Instruction inst = decoder.decodeInstruction(address, raw);
   60: 
   61:         t.IsTrue(inst.isBranch, "beq should be marked as branch");
   62:         t.IsTrue(inst.hasDelaySlot, "beq has a delay slot");
   63:         uint32_t expectedTarget = address + 4 + (static_cast<int16_t>(offset) << 2);
   64:         t.Equals(decoder.getBranchTarget(inst), expectedTarget, "beq target should be computed from simmediate");
   65:     });
   66: 
   67:     tc.Run("branch target sign-extends negative offset", [](TestCase &t) {
   68:         uint32_t address = 0x2100;
   69:         int16_t negOffset = -4; // jump back 16 bytes
   70:         uint32_t raw = (OPCODE_BNE << 26) | (1 << 21) | (2 << 16) | (negOffset & 0xFFFF);
   71: 
   72:         R5900Decoder decoder;
   73:         Instruction inst = decoder.decodeInstruction(address, raw);
   74: 
   75:         uint32_t expectedTarget = address + 4 + (static_cast<int16_t>(negOffset) << 2);
   76:         t.Equals(decoder.getBranchTarget(inst), expectedTarget, "negative branch offsets should sign-extend");
   77:     });
   78: 
   79:     tc.Run("decodes load/store flags", [](TestCase &t) {
   80:         uint32_t address = 0x3000;
   81:         uint32_t lwRaw = (OPCODE_LW << 26) | (1 << 21) | (2 << 16) | 0x10;
   82:         uint32_t swRaw = (OPCODE_SW << 26) | (3 << 21) | (4 << 16) | 0x20;
   83: 
   84:         R5900Decoder decoder;

--- Lines 91-125 ---
   91:         t.IsFalse(sw.isLoad, "sw should not be marked as load");
   92:     });
   93: 
   94:     tc.Run("JR is marked as return when rs is $ra", [](TestCase &t) {
   95:         uint32_t address = 0x4000;
   96:         uint32_t raw = (OPCODE_SPECIAL << 26) | (31 << 21) | SPECIAL_JR; // jr $ra
   97: 
   98:         R5900Decoder decoder;
   99:         Instruction inst = decoder.decodeInstruction(address, raw);
  100: 
  101:         t.IsTrue(inst.isJump, "jr should be jump");
  102:         t.IsTrue(inst.isReturn, "jr $ra should be marked as return");
  103:         t.IsTrue(inst.hasDelaySlot, "jr has delay slot");
  104:     });
  105: 
  106:     tc.Run("JALR marks call and writes rd when non-zero", [](TestCase &t) {
  107:         uint32_t address = 0x5000;
  108:         uint32_t rd = 5;
  109:         uint32_t raw = (OPCODE_SPECIAL << 26) | (2 << 21) | (rd << 11) | SPECIAL_JALR; // jalr $v0, $a0
  110: 
  111:         R5900Decoder decoder;
  112:         Instruction inst = decoder.decodeInstruction(address, raw);
  113: 
  114:         t.IsTrue(inst.isJump, "jalr should be jump");
  115:         t.IsTrue(inst.isCall, "jalr should be call");
  116:         t.IsTrue(inst.hasDelaySlot, "jalr has delay slot");
  117:         t.IsTrue(inst.modificationInfo.modifiesGPR, "jalr with rd!=0 should mark GPR modification");
  118:     });
  119: 
  120:     tc.Run("R5900 MULT marks rd modification when rd is non-zero", [](TestCase &t) {
  121:         uint32_t address = 0x5800;
  122:         uint32_t rawWithRd = (OPCODE_SPECIAL << 26) | (4 << 21) | (5 << 16) | (3 << 11) | SPECIAL_MULT;
  123:         uint32_t rawRdZero = (OPCODE_SPECIAL << 26) | (4 << 21) | (5 << 16) | (0 << 11) | SPECIAL_MULT;
  124: 
  125:         R5900Decoder decoder;

--- Lines 104-138 ---
  104:     });
  105: 
  106:     tc.Run("JALR marks call and writes rd when non-zero", [](TestCase &t) {
  107:         uint32_t address = 0x5000;
  108:         uint32_t rd = 5;
  109:         uint32_t raw = (OPCODE_SPECIAL << 26) | (2 << 21) | (rd << 11) | SPECIAL_JALR; // jalr $v0, $a0
  110: 
  111:         R5900Decoder decoder;
  112:         Instruction inst = decoder.decodeInstruction(address, raw);
  113: 
  114:         t.IsTrue(inst.isJump, "jalr should be jump");
  115:         t.IsTrue(inst.isCall, "jalr should be call");
  116:         t.IsTrue(inst.hasDelaySlot, "jalr has delay slot");
  117:         t.IsTrue(inst.modificationInfo.modifiesGPR, "jalr with rd!=0 should mark GPR modification");
  118:     });
  119: 
  120:     tc.Run("R5900 MULT marks rd modification when rd is non-zero", [](TestCase &t) {
  121:         uint32_t address = 0x5800;
  122:         uint32_t rawWithRd = (OPCODE_SPECIAL << 26) | (4 << 21) | (5 << 16) | (3 << 11) | SPECIAL_MULT;
  123:         uint32_t rawRdZero = (OPCODE_SPECIAL << 26) | (4 << 21) | (5 << 16) | (0 << 11) | SPECIAL_MULT;
  124: 
  125:         R5900Decoder decoder;
  126:         Instruction withRd = decoder.decodeInstruction(address, rawWithRd);
  127:         Instruction rdZero = decoder.decodeInstruction(address + 4, rawRdZero);
  128: 
  129:         t.IsTrue(withRd.modificationInfo.modifiesControl, "MULT should modify HI/LO");
  130:         t.IsTrue(withRd.modificationInfo.modifiesGPR, "MULT should mark rd modification when rd!=0");
  131:         t.IsFalse(rdZero.modificationInfo.modifiesGPR, "MULT should not mark rd modification when rd==0");
  132:     });
  133: 
  134:     tc.Run("R5900 MMI MULT1 marks rd modification when rd is non-zero", [](TestCase &t) {
  135:         uint32_t address = 0x5900;
  136:         uint32_t raw = (OPCODE_MMI << 26) | (6 << 21) | (7 << 16) | (8 << 11) | MMI_MULT1;
  137: 
  138:         R5900Decoder decoder;

--- Lines 175-209 ---
  175:     });
  176: 
  177:     tc.Run("REGIMM branch and link marks call and GPR modification", [](TestCase &t) {
  178:         uint32_t address = 0x8000;
  179:         uint16_t offset = 0x2;
  180:         uint32_t raw = (OPCODE_REGIMM << 26) | (1 << 21) | (REGIMM_BGEZAL << 16) | offset;
  181: 
  182:         R5900Decoder decoder;
  183:         Instruction inst = decoder.decodeInstruction(address, raw);
  184: 
  185:         t.IsTrue(inst.isBranch, "bgezal should be branch");
  186:         t.IsTrue(inst.isCall, "bgezal should be call (link)");
  187:         t.IsTrue(inst.hasDelaySlot, "bgezal has delay slot");
  188:         t.IsTrue(inst.modificationInfo.modifiesGPR, "bgezal should mark GPR modification for $ra");
  189:         uint32_t expectedTarget = address + 4 + (static_cast<int16_t>(offset) << 2);
  190:         t.Equals(decoder.getBranchTarget(inst), expectedTarget, "bgezal target should be computed");
  191:     });
  192: 
  193:     tc.Run("LL/SC modify control and set load/store flags", [](TestCase &t) {
  194:         uint32_t address = 0x9000;
  195:         uint32_t llRaw = (OPCODE_LL << 26) | (2 << 21) | (3 << 16) | 0x10;
  196:         uint32_t scRaw = (OPCODE_SC << 26) | (4 << 21) | (5 << 16) | 0x20;
  197: 
  198:         R5900Decoder decoder;
  199:         Instruction ll = decoder.decodeInstruction(address, llRaw);
  200:         Instruction sc = decoder.decodeInstruction(address + 4, scRaw);
  201: 
  202:         t.IsTrue(ll.isLoad, "ll should be load");
  203:         t.IsTrue(ll.modificationInfo.modifiesControl, "ll should modify control (LL bit)");
  204:         t.IsTrue(sc.isStore, "sc should be store");
  205:         t.IsTrue(sc.modificationInfo.modifiesControl, "sc should modify control (LL bit)");
  206:         t.IsTrue(sc.modificationInfo.modifiesGPR, "sc writes success flag to rt");
  207:     });
  208: 
  209:     tc.Run("COP0 ERET is marked as return without delay slot", [](TestCase &t) {

--- Lines 197-231 ---
  197: 
  198:         R5900Decoder decoder;
  199:         Instruction ll = decoder.decodeInstruction(address, llRaw);
  200:         Instruction sc = decoder.decodeInstruction(address + 4, scRaw);
  201: 
  202:         t.IsTrue(ll.isLoad, "ll should be load");
  203:         t.IsTrue(ll.modificationInfo.modifiesControl, "ll should modify control (LL bit)");
  204:         t.IsTrue(sc.isStore, "sc should be store");
  205:         t.IsTrue(sc.modificationInfo.modifiesControl, "sc should modify control (LL bit)");
  206:         t.IsTrue(sc.modificationInfo.modifiesGPR, "sc writes success flag to rt");
  207:     });
  208: 
  209:     tc.Run("COP0 ERET is marked as return without delay slot", [](TestCase &t) {
  210:         uint32_t address = 0xA000;
  211:         uint32_t raw = (OPCODE_COP0 << 26) | (COP0_CO << 21) | COP0_CO_ERET;
  212: 
  213:         R5900Decoder decoder;
  214:         Instruction inst = decoder.decodeInstruction(address, raw);
  215: 
  216:         t.IsTrue(inst.isReturn, "eret should be marked as return");
  217:         t.IsFalse(inst.hasDelaySlot, "eret should not have a delay slot");
  218:         t.IsTrue(inst.modificationInfo.modifiesControl, "eret changes control state");
  219:     });
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

--- Lines 205-239 ---
  205:         t.IsTrue(sc.modificationInfo.modifiesControl, "sc should modify control (LL bit)");
  206:         t.IsTrue(sc.modificationInfo.modifiesGPR, "sc writes success flag to rt");
  207:     });
  208: 
  209:     tc.Run("COP0 ERET is marked as return without delay slot", [](TestCase &t) {
  210:         uint32_t address = 0xA000;
  211:         uint32_t raw = (OPCODE_COP0 << 26) | (COP0_CO << 21) | COP0_CO_ERET;
  212: 
  213:         R5900Decoder decoder;
  214:         Instruction inst = decoder.decodeInstruction(address, raw);
  215: 
  216:         t.IsTrue(inst.isReturn, "eret should be marked as return");
  217:         t.IsFalse(inst.hasDelaySlot, "eret should not have a delay slot");
  218:         t.IsTrue(inst.modificationInfo.modifiesControl, "eret changes control state");
  219:     });
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

--- Lines 230-264 ---
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

--- Lines 233-267 ---
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

--- Lines 234-268 ---
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

--- Lines 235-269 ---
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

--- Lines 236-270 ---
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

--- Lines 241-275 ---
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

--- Lines 242-276 ---
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

--- Lines 243-277 ---
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

--- Lines 244-278 ---
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

--- Lines 245-279 ---
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

--- Lines 246-280 ---
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

========== D:\Games\MarkOfKriRecomp\external\PS2Recomp\ps2xTest\CMakeLists.txt ==========
