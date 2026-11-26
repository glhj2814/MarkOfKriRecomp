
===== ps2xTest\src\main.cpp =====
--- lines 1-50 ---
    1: #include "MiniTest.h"
    2: #include <cstdlib>
    3: #include <iostream>
    4: 
    5: void register_code_generator_tests();
    6: void register_r5900_decoder_tests();
    7: void register_elf_analyzer_tests();
    8: void register_pad_input_tests();
    9: void register_ps2_runtime_io_tests();
   10: void register_ps2_runtime_kernel_tests();
   11: void register_ps2_runtime_interrupt_tests();
   12: void register_ps2_memory_tests();
   13: void register_ps2_vu1_tests();
   14: void register_ps2_vu_tests();
   15: void register_ps2_gs_tests();
   16: void register_ps2_iop_tests();
   17: void register_ps2_sif_rpc_tests();
   18: void register_ps2_sif_dma_tests();
   19: void register_ps2_recompiler_tests();
   20: void register_ps2_runtime_expansion_tests();
   21: void register_ps2_float_semantics_tests();
   22: void register_ps2_audio_stream_tests();
   23: void reset_ps2_test_function_table();
   24: 
   25: int main()
   26: {
   27:     MiniTest::BeforeEach(reset_ps2_test_function_table);
   28: 
   29:     register_code_generator_tests();
   30:     register_r5900_decoder_tests();
   31:     register_elf_analyzer_tests();
   32:     register_pad_input_tests();
   33:     register_ps2_runtime_io_tests();
   34:     register_ps2_runtime_kernel_tests();
   35:     register_ps2_runtime_interrupt_tests();
   36:     register_ps2_memory_tests();
   37:     register_ps2_vu1_tests();
   38:     register_ps2_vu_tests();
   39:     register_ps2_gs_tests();
   40:     register_ps2_iop_tests();
   41:     register_ps2_sif_rpc_tests();
   42:     register_ps2_sif_dma_tests();
   43:     register_ps2_recompiler_tests();
   44:     register_ps2_runtime_expansion_tests();
   45:     register_ps2_float_semantics_tests();
   46:     register_ps2_audio_stream_tests();
   47:     int res = MiniTest::Run();
   48:     std::cout.flush();
   49:     std::cerr.flush();
   50:     std::_Exit(res);
--- lines 1-51 ---
    1: #include "MiniTest.h"
    2: #include <cstdlib>
    3: #include <iostream>
    4: 
    5: void register_code_generator_tests();
    6: void register_r5900_decoder_tests();
    7: void register_elf_analyzer_tests();
    8: void register_pad_input_tests();
    9: void register_ps2_runtime_io_tests();
   10: void register_ps2_runtime_kernel_tests();
   11: void register_ps2_runtime_interrupt_tests();
   12: void register_ps2_memory_tests();
   13: void register_ps2_vu1_tests();
   14: void register_ps2_vu_tests();
   15: void register_ps2_gs_tests();
   16: void register_ps2_iop_tests();
   17: void register_ps2_sif_rpc_tests();
   18: void register_ps2_sif_dma_tests();
   19: void register_ps2_recompiler_tests();
   20: void register_ps2_runtime_expansion_tests();
   21: void register_ps2_float_semantics_tests();
   22: void register_ps2_audio_stream_tests();
   23: void reset_ps2_test_function_table();
   24: 
   25: int main()
   26: {
   27:     MiniTest::BeforeEach(reset_ps2_test_function_table);
   28: 
   29:     register_code_generator_tests();
   30:     register_r5900_decoder_tests();
   31:     register_elf_analyzer_tests();
   32:     register_pad_input_tests();
   33:     register_ps2_runtime_io_tests();
   34:     register_ps2_runtime_kernel_tests();
   35:     register_ps2_runtime_interrupt_tests();
   36:     register_ps2_memory_tests();
   37:     register_ps2_vu1_tests();
   38:     register_ps2_vu_tests();
   39:     register_ps2_gs_tests();
   40:     register_ps2_iop_tests();
   41:     register_ps2_sif_rpc_tests();
   42:     register_ps2_sif_dma_tests();
   43:     register_ps2_recompiler_tests();
   44:     register_ps2_runtime_expansion_tests();
   45:     register_ps2_float_semantics_tests();
   46:     register_ps2_audio_stream_tests();
   47:     int res = MiniTest::Run();
   48:     std::cout.flush();
   49:     std::cerr.flush();
   50:     std::_Exit(res);
   51: }
--- lines 1-51 ---
    1: #include "MiniTest.h"
    2: #include <cstdlib>
    3: #include <iostream>
    4: 
    5: void register_code_generator_tests();
    6: void register_r5900_decoder_tests();
    7: void register_elf_analyzer_tests();
    8: void register_pad_input_tests();
    9: void register_ps2_runtime_io_tests();
   10: void register_ps2_runtime_kernel_tests();
   11: void register_ps2_runtime_interrupt_tests();
   12: void register_ps2_memory_tests();
   13: void register_ps2_vu1_tests();
   14: void register_ps2_vu_tests();
   15: void register_ps2_gs_tests();
   16: void register_ps2_iop_tests();
   17: void register_ps2_sif_rpc_tests();
   18: void register_ps2_sif_dma_tests();
   19: void register_ps2_recompiler_tests();
   20: void register_ps2_runtime_expansion_tests();
   21: void register_ps2_float_semantics_tests();
   22: void register_ps2_audio_stream_tests();
   23: void reset_ps2_test_function_table();
   24: 
   25: int main()
   26: {
   27:     MiniTest::BeforeEach(reset_ps2_test_function_table);
   28: 
   29:     register_code_generator_tests();
   30:     register_r5900_decoder_tests();
   31:     register_elf_analyzer_tests();
   32:     register_pad_input_tests();
   33:     register_ps2_runtime_io_tests();
   34:     register_ps2_runtime_kernel_tests();
   35:     register_ps2_runtime_interrupt_tests();
   36:     register_ps2_memory_tests();
   37:     register_ps2_vu1_tests();
   38:     register_ps2_vu_tests();
   39:     register_ps2_gs_tests();
   40:     register_ps2_iop_tests();
   41:     register_ps2_sif_rpc_tests();
   42:     register_ps2_sif_dma_tests();
   43:     register_ps2_recompiler_tests();
   44:     register_ps2_runtime_expansion_tests();
   45:     register_ps2_float_semantics_tests();
   46:     register_ps2_audio_stream_tests();
   47:     int res = MiniTest::Run();
   48:     std::cout.flush();
   49:     std::cerr.flush();
   50:     std::_Exit(res);
   51: }
--- lines 1-51 ---
    1: #include "MiniTest.h"
    2: #include <cstdlib>
    3: #include <iostream>
    4: 
    5: void register_code_generator_tests();
    6: void register_r5900_decoder_tests();
    7: void register_elf_analyzer_tests();
    8: void register_pad_input_tests();
    9: void register_ps2_runtime_io_tests();
   10: void register_ps2_runtime_kernel_tests();
   11: void register_ps2_runtime_interrupt_tests();
   12: void register_ps2_memory_tests();
   13: void register_ps2_vu1_tests();
   14: void register_ps2_vu_tests();
   15: void register_ps2_gs_tests();
   16: void register_ps2_iop_tests();
   17: void register_ps2_sif_rpc_tests();
   18: void register_ps2_sif_dma_tests();
   19: void register_ps2_recompiler_tests();
   20: void register_ps2_runtime_expansion_tests();
   21: void register_ps2_float_semantics_tests();
   22: void register_ps2_audio_stream_tests();
   23: void reset_ps2_test_function_table();
   24: 
   25: int main()
   26: {
   27:     MiniTest::BeforeEach(reset_ps2_test_function_table);
   28: 
   29:     register_code_generator_tests();
   30:     register_r5900_decoder_tests();
   31:     register_elf_analyzer_tests();
   32:     register_pad_input_tests();
   33:     register_ps2_runtime_io_tests();
   34:     register_ps2_runtime_kernel_tests();
   35:     register_ps2_runtime_interrupt_tests();
   36:     register_ps2_memory_tests();
   37:     register_ps2_vu1_tests();
   38:     register_ps2_vu_tests();
   39:     register_ps2_gs_tests();
   40:     register_ps2_iop_tests();
   41:     register_ps2_sif_rpc_tests();
   42:     register_ps2_sif_dma_tests();
   43:     register_ps2_recompiler_tests();
   44:     register_ps2_runtime_expansion_tests();
   45:     register_ps2_float_semantics_tests();
   46:     register_ps2_audio_stream_tests();
   47:     int res = MiniTest::Run();
   48:     std::cout.flush();
   49:     std::cerr.flush();
   50:     std::_Exit(res);
   51: }
--- lines 1-51 ---
    1: #include "MiniTest.h"
    2: #include <cstdlib>
    3: #include <iostream>
    4: 
    5: void register_code_generator_tests();
    6: void register_r5900_decoder_tests();
    7: void register_elf_analyzer_tests();
    8: void register_pad_input_tests();
    9: void register_ps2_runtime_io_tests();
   10: void register_ps2_runtime_kernel_tests();
   11: void register_ps2_runtime_interrupt_tests();
   12: void register_ps2_memory_tests();
   13: void register_ps2_vu1_tests();
   14: void register_ps2_vu_tests();
   15: void register_ps2_gs_tests();
   16: void register_ps2_iop_tests();
   17: void register_ps2_sif_rpc_tests();
   18: void register_ps2_sif_dma_tests();
   19: void register_ps2_recompiler_tests();
   20: void register_ps2_runtime_expansion_tests();
   21: void register_ps2_float_semantics_tests();
   22: void register_ps2_audio_stream_tests();
   23: void reset_ps2_test_function_table();
   24: 
   25: int main()
   26: {
   27:     MiniTest::BeforeEach(reset_ps2_test_function_table);
   28: 
   29:     register_code_generator_tests();
   30:     register_r5900_decoder_tests();
   31:     register_elf_analyzer_tests();
   32:     register_pad_input_tests();
   33:     register_ps2_runtime_io_tests();
   34:     register_ps2_runtime_kernel_tests();
   35:     register_ps2_runtime_interrupt_tests();
   36:     register_ps2_memory_tests();
   37:     register_ps2_vu1_tests();
   38:     register_ps2_vu_tests();
   39:     register_ps2_gs_tests();
   40:     register_ps2_iop_tests();
   41:     register_ps2_sif_rpc_tests();
   42:     register_ps2_sif_dma_tests();
   43:     register_ps2_recompiler_tests();
   44:     register_ps2_runtime_expansion_tests();
   45:     register_ps2_float_semantics_tests();
   46:     register_ps2_audio_stream_tests();
   47:     int res = MiniTest::Run();
   48:     std::cout.flush();
   49:     std::cerr.flush();
   50:     std::_Exit(res);
   51: }
--- lines 2-51 ---
    2: #include <cstdlib>
    3: #include <iostream>
    4: 
    5: void register_code_generator_tests();
    6: void register_r5900_decoder_tests();
    7: void register_elf_analyzer_tests();
    8: void register_pad_input_tests();
    9: void register_ps2_runtime_io_tests();
   10: void register_ps2_runtime_kernel_tests();
   11: void register_ps2_runtime_interrupt_tests();
   12: void register_ps2_memory_tests();
   13: void register_ps2_vu1_tests();
   14: void register_ps2_vu_tests();
   15: void register_ps2_gs_tests();
   16: void register_ps2_iop_tests();
   17: void register_ps2_sif_rpc_tests();
   18: void register_ps2_sif_dma_tests();
   19: void register_ps2_recompiler_tests();
   20: void register_ps2_runtime_expansion_tests();
   21: void register_ps2_float_semantics_tests();
   22: void register_ps2_audio_stream_tests();
   23: void reset_ps2_test_function_table();
   24: 
   25: int main()
   26: {
   27:     MiniTest::BeforeEach(reset_ps2_test_function_table);
   28: 
   29:     register_code_generator_tests();
   30:     register_r5900_decoder_tests();
   31:     register_elf_analyzer_tests();
   32:     register_pad_input_tests();
   33:     register_ps2_runtime_io_tests();
   34:     register_ps2_runtime_kernel_tests();
   35:     register_ps2_runtime_interrupt_tests();
   36:     register_ps2_memory_tests();
   37:     register_ps2_vu1_tests();
   38:     register_ps2_vu_tests();
   39:     register_ps2_gs_tests();
   40:     register_ps2_iop_tests();
   41:     register_ps2_sif_rpc_tests();
   42:     register_ps2_sif_dma_tests();
   43:     register_ps2_recompiler_tests();
   44:     register_ps2_runtime_expansion_tests();
   45:     register_ps2_float_semantics_tests();
   46:     register_ps2_audio_stream_tests();
   47:     int res = MiniTest::Run();
   48:     std::cout.flush();
   49:     std::cerr.flush();
   50:     std::_Exit(res);
   51: }
--- lines 3-51 ---
    3: #include <iostream>
    4: 
    5: void register_code_generator_tests();
    6: void register_r5900_decoder_tests();
    7: void register_elf_analyzer_tests();
    8: void register_pad_input_tests();
    9: void register_ps2_runtime_io_tests();
   10: void register_ps2_runtime_kernel_tests();
   11: void register_ps2_runtime_interrupt_tests();
   12: void register_ps2_memory_tests();
   13: void register_ps2_vu1_tests();
   14: void register_ps2_vu_tests();
   15: void register_ps2_gs_tests();
   16: void register_ps2_iop_tests();
   17: void register_ps2_sif_rpc_tests();
   18: void register_ps2_sif_dma_tests();
   19: void register_ps2_recompiler_tests();
   20: void register_ps2_runtime_expansion_tests();
   21: void register_ps2_float_semantics_tests();
   22: void register_ps2_audio_stream_tests();
   23: void reset_ps2_test_function_table();
   24: 
   25: int main()
   26: {
   27:     MiniTest::BeforeEach(reset_ps2_test_function_table);
   28: 
   29:     register_code_generator_tests();
   30:     register_r5900_decoder_tests();
   31:     register_elf_analyzer_tests();
   32:     register_pad_input_tests();
   33:     register_ps2_runtime_io_tests();
   34:     register_ps2_runtime_kernel_tests();
   35:     register_ps2_runtime_interrupt_tests();
   36:     register_ps2_memory_tests();
   37:     register_ps2_vu1_tests();
   38:     register_ps2_vu_tests();
   39:     register_ps2_gs_tests();
   40:     register_ps2_iop_tests();
   41:     register_ps2_sif_rpc_tests();
   42:     register_ps2_sif_dma_tests();
   43:     register_ps2_recompiler_tests();
   44:     register_ps2_runtime_expansion_tests();
   45:     register_ps2_float_semantics_tests();
   46:     register_ps2_audio_stream_tests();
   47:     int res = MiniTest::Run();
   48:     std::cout.flush();
   49:     std::cerr.flush();
   50:     std::_Exit(res);
   51: }
--- lines 4-51 ---
    4: 
    5: void register_code_generator_tests();
    6: void register_r5900_decoder_tests();
    7: void register_elf_analyzer_tests();
    8: void register_pad_input_tests();
    9: void register_ps2_runtime_io_tests();
   10: void register_ps2_runtime_kernel_tests();
   11: void register_ps2_runtime_interrupt_tests();
   12: void register_ps2_memory_tests();
   13: void register_ps2_vu1_tests();
   14: void register_ps2_vu_tests();
   15: void register_ps2_gs_tests();
   16: void register_ps2_iop_tests();
   17: void register_ps2_sif_rpc_tests();
   18: void register_ps2_sif_dma_tests();
   19: void register_ps2_recompiler_tests();
   20: void register_ps2_runtime_expansion_tests();
   21: void register_ps2_float_semantics_tests();
   22: void register_ps2_audio_stream_tests();
   23: void reset_ps2_test_function_table();
   24: 
   25: int main()
   26: {
   27:     MiniTest::BeforeEach(reset_ps2_test_function_table);
   28: 
   29:     register_code_generator_tests();
   30:     register_r5900_decoder_tests();
   31:     register_elf_analyzer_tests();
   32:     register_pad_input_tests();
   33:     register_ps2_runtime_io_tests();
   34:     register_ps2_runtime_kernel_tests();
   35:     register_ps2_runtime_interrupt_tests();
   36:     register_ps2_memory_tests();
   37:     register_ps2_vu1_tests();
   38:     register_ps2_vu_tests();
   39:     register_ps2_gs_tests();
   40:     register_ps2_iop_tests();
   41:     register_ps2_sif_rpc_tests();
   42:     register_ps2_sif_dma_tests();
   43:     register_ps2_recompiler_tests();
   44:     register_ps2_runtime_expansion_tests();
   45:     register_ps2_float_semantics_tests();
   46:     register_ps2_audio_stream_tests();
   47:     int res = MiniTest::Run();
   48:     std::cout.flush();
   49:     std::cerr.flush();
   50:     std::_Exit(res);
   51: }
--- lines 5-51 ---
    5: void register_code_generator_tests();
    6: void register_r5900_decoder_tests();
    7: void register_elf_analyzer_tests();
    8: void register_pad_input_tests();
    9: void register_ps2_runtime_io_tests();
   10: void register_ps2_runtime_kernel_tests();
   11: void register_ps2_runtime_interrupt_tests();
   12: void register_ps2_memory_tests();
   13: void register_ps2_vu1_tests();
   14: void register_ps2_vu_tests();
   15: void register_ps2_gs_tests();
   16: void register_ps2_iop_tests();
   17: void register_ps2_sif_rpc_tests();
   18: void register_ps2_sif_dma_tests();
   19: void register_ps2_recompiler_tests();
   20: void register_ps2_runtime_expansion_tests();
   21: void register_ps2_float_semantics_tests();
   22: void register_ps2_audio_stream_tests();
   23: void reset_ps2_test_function_table();
   24: 
   25: int main()
   26: {
   27:     MiniTest::BeforeEach(reset_ps2_test_function_table);
   28: 
   29:     register_code_generator_tests();
   30:     register_r5900_decoder_tests();
   31:     register_elf_analyzer_tests();
   32:     register_pad_input_tests();
   33:     register_ps2_runtime_io_tests();
   34:     register_ps2_runtime_kernel_tests();
   35:     register_ps2_runtime_interrupt_tests();
   36:     register_ps2_memory_tests();
   37:     register_ps2_vu1_tests();
   38:     register_ps2_vu_tests();
   39:     register_ps2_gs_tests();
   40:     register_ps2_iop_tests();
   41:     register_ps2_sif_rpc_tests();
   42:     register_ps2_sif_dma_tests();
   43:     register_ps2_recompiler_tests();
   44:     register_ps2_runtime_expansion_tests();
   45:     register_ps2_float_semantics_tests();
   46:     register_ps2_audio_stream_tests();
   47:     int res = MiniTest::Run();
   48:     std::cout.flush();
   49:     std::cerr.flush();
   50:     std::_Exit(res);
   51: }
--- lines 6-51 ---
    6: void register_r5900_decoder_tests();
    7: void register_elf_analyzer_tests();
    8: void register_pad_input_tests();
    9: void register_ps2_runtime_io_tests();
   10: void register_ps2_runtime_kernel_tests();
   11: void register_ps2_runtime_interrupt_tests();
   12: void register_ps2_memory_tests();
   13: void register_ps2_vu1_tests();
   14: void register_ps2_vu_tests();
   15: void register_ps2_gs_tests();
   16: void register_ps2_iop_tests();
   17: void register_ps2_sif_rpc_tests();
   18: void register_ps2_sif_dma_tests();
   19: void register_ps2_recompiler_tests();
   20: void register_ps2_runtime_expansion_tests();
   21: void register_ps2_float_semantics_tests();
   22: void register_ps2_audio_stream_tests();
   23: void reset_ps2_test_function_table();
   24: 
   25: int main()
   26: {
   27:     MiniTest::BeforeEach(reset_ps2_test_function_table);
   28: 
   29:     register_code_generator_tests();
   30:     register_r5900_decoder_tests();
   31:     register_elf_analyzer_tests();
   32:     register_pad_input_tests();
   33:     register_ps2_runtime_io_tests();
   34:     register_ps2_runtime_kernel_tests();
   35:     register_ps2_runtime_interrupt_tests();
   36:     register_ps2_memory_tests();
   37:     register_ps2_vu1_tests();
   38:     register_ps2_vu_tests();
   39:     register_ps2_gs_tests();
   40:     register_ps2_iop_tests();
   41:     register_ps2_sif_rpc_tests();
   42:     register_ps2_sif_dma_tests();
   43:     register_ps2_recompiler_tests();
   44:     register_ps2_runtime_expansion_tests();
   45:     register_ps2_float_semantics_tests();
   46:     register_ps2_audio_stream_tests();
   47:     int res = MiniTest::Run();
   48:     std::cout.flush();
   49:     std::cerr.flush();
   50:     std::_Exit(res);
   51: }
--- lines 7-51 ---
    7: void register_elf_analyzer_tests();
    8: void register_pad_input_tests();
    9: void register_ps2_runtime_io_tests();
   10: void register_ps2_runtime_kernel_tests();
   11: void register_ps2_runtime_interrupt_tests();
   12: void register_ps2_memory_tests();
   13: void register_ps2_vu1_tests();
   14: void register_ps2_vu_tests();
   15: void register_ps2_gs_tests();
   16: void register_ps2_iop_tests();
   17: void register_ps2_sif_rpc_tests();
   18: void register_ps2_sif_dma_tests();
   19: void register_ps2_recompiler_tests();
   20: void register_ps2_runtime_expansion_tests();
   21: void register_ps2_float_semantics_tests();
   22: void register_ps2_audio_stream_tests();
   23: void reset_ps2_test_function_table();
   24: 
   25: int main()
   26: {
   27:     MiniTest::BeforeEach(reset_ps2_test_function_table);
   28: 
   29:     register_code_generator_tests();
   30:     register_r5900_decoder_tests();
   31:     register_elf_analyzer_tests();
   32:     register_pad_input_tests();
   33:     register_ps2_runtime_io_tests();
   34:     register_ps2_runtime_kernel_tests();
   35:     register_ps2_runtime_interrupt_tests();
   36:     register_ps2_memory_tests();
   37:     register_ps2_vu1_tests();
   38:     register_ps2_vu_tests();
   39:     register_ps2_gs_tests();
   40:     register_ps2_iop_tests();
   41:     register_ps2_sif_rpc_tests();
   42:     register_ps2_sif_dma_tests();
   43:     register_ps2_recompiler_tests();
   44:     register_ps2_runtime_expansion_tests();
   45:     register_ps2_float_semantics_tests();
   46:     register_ps2_audio_stream_tests();
   47:     int res = MiniTest::Run();
   48:     std::cout.flush();
   49:     std::cerr.flush();
   50:     std::_Exit(res);
   51: }
--- lines 8-51 ---
    8: void register_pad_input_tests();
    9: void register_ps2_runtime_io_tests();
   10: void register_ps2_runtime_kernel_tests();
   11: void register_ps2_runtime_interrupt_tests();
   12: void register_ps2_memory_tests();
   13: void register_ps2_vu1_tests();
   14: void register_ps2_vu_tests();
   15: void register_ps2_gs_tests();
   16: void register_ps2_iop_tests();
   17: void register_ps2_sif_rpc_tests();
   18: void register_ps2_sif_dma_tests();
   19: void register_ps2_recompiler_tests();
   20: void register_ps2_runtime_expansion_tests();
   21: void register_ps2_float_semantics_tests();
   22: void register_ps2_audio_stream_tests();
   23: void reset_ps2_test_function_table();
   24: 
   25: int main()
   26: {
   27:     MiniTest::BeforeEach(reset_ps2_test_function_table);
   28: 
   29:     register_code_generator_tests();
   30:     register_r5900_decoder_tests();
   31:     register_elf_analyzer_tests();
   32:     register_pad_input_tests();
   33:     register_ps2_runtime_io_tests();
   34:     register_ps2_runtime_kernel_tests();
   35:     register_ps2_runtime_interrupt_tests();
   36:     register_ps2_memory_tests();
   37:     register_ps2_vu1_tests();
   38:     register_ps2_vu_tests();
   39:     register_ps2_gs_tests();
   40:     register_ps2_iop_tests();
   41:     register_ps2_sif_rpc_tests();
   42:     register_ps2_sif_dma_tests();
   43:     register_ps2_recompiler_tests();
   44:     register_ps2_runtime_expansion_tests();
   45:     register_ps2_float_semantics_tests();
   46:     register_ps2_audio_stream_tests();
   47:     int res = MiniTest::Run();
   48:     std::cout.flush();
   49:     std::cerr.flush();
   50:     std::_Exit(res);
   51: }
--- lines 9-51 ---
    9: void register_ps2_runtime_io_tests();
   10: void register_ps2_runtime_kernel_tests();
   11: void register_ps2_runtime_interrupt_tests();
   12: void register_ps2_memory_tests();
   13: void register_ps2_vu1_tests();
   14: void register_ps2_vu_tests();
   15: void register_ps2_gs_tests();
   16: void register_ps2_iop_tests();
   17: void register_ps2_sif_rpc_tests();
   18: void register_ps2_sif_dma_tests();
   19: void register_ps2_recompiler_tests();
   20: void register_ps2_runtime_expansion_tests();
   21: void register_ps2_float_semantics_tests();
   22: void register_ps2_audio_stream_tests();
   23: void reset_ps2_test_function_table();
   24: 
   25: int main()
   26: {
   27:     MiniTest::BeforeEach(reset_ps2_test_function_table);
   28: 
   29:     register_code_generator_tests();
   30:     register_r5900_decoder_tests();
   31:     register_elf_analyzer_tests();
   32:     register_pad_input_tests();
   33:     register_ps2_runtime_io_tests();
   34:     register_ps2_runtime_kernel_tests();
   35:     register_ps2_runtime_interrupt_tests();
   36:     register_ps2_memory_tests();
   37:     register_ps2_vu1_tests();
   38:     register_ps2_vu_tests();
   39:     register_ps2_gs_tests();
   40:     register_ps2_iop_tests();
   41:     register_ps2_sif_rpc_tests();
   42:     register_ps2_sif_dma_tests();
   43:     register_ps2_recompiler_tests();
   44:     register_ps2_runtime_expansion_tests();
   45:     register_ps2_float_semantics_tests();
   46:     register_ps2_audio_stream_tests();
   47:     int res = MiniTest::Run();
   48:     std::cout.flush();
   49:     std::cerr.flush();
   50:     std::_Exit(res);
   51: }
--- lines 10-51 ---
   10: void register_ps2_runtime_kernel_tests();
   11: void register_ps2_runtime_interrupt_tests();
   12: void register_ps2_memory_tests();
   13: void register_ps2_vu1_tests();
   14: void register_ps2_vu_tests();
   15: void register_ps2_gs_tests();
   16: void register_ps2_iop_tests();
   17: void register_ps2_sif_rpc_tests();
   18: void register_ps2_sif_dma_tests();
   19: void register_ps2_recompiler_tests();
   20: void register_ps2_runtime_expansion_tests();
   21: void register_ps2_float_semantics_tests();
   22: void register_ps2_audio_stream_tests();
   23: void reset_ps2_test_function_table();
   24: 
   25: int main()
   26: {
   27:     MiniTest::BeforeEach(reset_ps2_test_function_table);
   28: 
   29:     register_code_generator_tests();
   30:     register_r5900_decoder_tests();
   31:     register_elf_analyzer_tests();
   32:     register_pad_input_tests();
   33:     register_ps2_runtime_io_tests();
   34:     register_ps2_runtime_kernel_tests();
   35:     register_ps2_runtime_interrupt_tests();
   36:     register_ps2_memory_tests();
   37:     register_ps2_vu1_tests();
   38:     register_ps2_vu_tests();
   39:     register_ps2_gs_tests();
   40:     register_ps2_iop_tests();
   41:     register_ps2_sif_rpc_tests();
   42:     register_ps2_sif_dma_tests();
   43:     register_ps2_recompiler_tests();
   44:     register_ps2_runtime_expansion_tests();
   45:     register_ps2_float_semantics_tests();
   46:     register_ps2_audio_stream_tests();
   47:     int res = MiniTest::Run();
   48:     std::cout.flush();
   49:     std::cerr.flush();
   50:     std::_Exit(res);
   51: }
--- lines 11-51 ---
   11: void register_ps2_runtime_interrupt_tests();
   12: void register_ps2_memory_tests();
   13: void register_ps2_vu1_tests();
   14: void register_ps2_vu_tests();
   15: void register_ps2_gs_tests();
   16: void register_ps2_iop_tests();
   17: void register_ps2_sif_rpc_tests();
   18: void register_ps2_sif_dma_tests();
   19: void register_ps2_recompiler_tests();
   20: void register_ps2_runtime_expansion_tests();
   21: void register_ps2_float_semantics_tests();
   22: void register_ps2_audio_stream_tests();
   23: void reset_ps2_test_function_table();
   24: 
   25: int main()
   26: {
   27:     MiniTest::BeforeEach(reset_ps2_test_function_table);
   28: 
   29:     register_code_generator_tests();
   30:     register_r5900_decoder_tests();
   31:     register_elf_analyzer_tests();
   32:     register_pad_input_tests();
   33:     register_ps2_runtime_io_tests();
   34:     register_ps2_runtime_kernel_tests();
   35:     register_ps2_runtime_interrupt_tests();
   36:     register_ps2_memory_tests();
   37:     register_ps2_vu1_tests();
   38:     register_ps2_vu_tests();
   39:     register_ps2_gs_tests();
   40:     register_ps2_iop_tests();
   41:     register_ps2_sif_rpc_tests();
   42:     register_ps2_sif_dma_tests();
   43:     register_ps2_recompiler_tests();
   44:     register_ps2_runtime_expansion_tests();
   45:     register_ps2_float_semantics_tests();
   46:     register_ps2_audio_stream_tests();
   47:     int res = MiniTest::Run();
   48:     std::cout.flush();
   49:     std::cerr.flush();
   50:     std::_Exit(res);
   51: }
--- lines 12-51 ---
   12: void register_ps2_memory_tests();
   13: void register_ps2_vu1_tests();
   14: void register_ps2_vu_tests();
   15: void register_ps2_gs_tests();
   16: void register_ps2_iop_tests();
   17: void register_ps2_sif_rpc_tests();
   18: void register_ps2_sif_dma_tests();
   19: void register_ps2_recompiler_tests();
   20: void register_ps2_runtime_expansion_tests();
   21: void register_ps2_float_semantics_tests();
   22: void register_ps2_audio_stream_tests();
   23: void reset_ps2_test_function_table();
   24: 
   25: int main()
   26: {
   27:     MiniTest::BeforeEach(reset_ps2_test_function_table);
   28: 
   29:     register_code_generator_tests();
   30:     register_r5900_decoder_tests();
   31:     register_elf_analyzer_tests();
   32:     register_pad_input_tests();
   33:     register_ps2_runtime_io_tests();
   34:     register_ps2_runtime_kernel_tests();
   35:     register_ps2_runtime_interrupt_tests();
   36:     register_ps2_memory_tests();
   37:     register_ps2_vu1_tests();
   38:     register_ps2_vu_tests();
   39:     register_ps2_gs_tests();
   40:     register_ps2_iop_tests();
   41:     register_ps2_sif_rpc_tests();
   42:     register_ps2_sif_dma_tests();
   43:     register_ps2_recompiler_tests();
   44:     register_ps2_runtime_expansion_tests();
   45:     register_ps2_float_semantics_tests();
   46:     register_ps2_audio_stream_tests();
   47:     int res = MiniTest::Run();
   48:     std::cout.flush();
   49:     std::cerr.flush();
   50:     std::_Exit(res);
   51: }
--- lines 13-51 ---
   13: void register_ps2_vu1_tests();
   14: void register_ps2_vu_tests();
   15: void register_ps2_gs_tests();
   16: void register_ps2_iop_tests();
   17: void register_ps2_sif_rpc_tests();
   18: void register_ps2_sif_dma_tests();
   19: void register_ps2_recompiler_tests();
   20: void register_ps2_runtime_expansion_tests();
   21: void register_ps2_float_semantics_tests();
   22: void register_ps2_audio_stream_tests();
   23: void reset_ps2_test_function_table();
   24: 
   25: int main()
   26: {
   27:     MiniTest::BeforeEach(reset_ps2_test_function_table);
   28: 
   29:     register_code_generator_tests();
   30:     register_r5900_decoder_tests();
   31:     register_elf_analyzer_tests();
   32:     register_pad_input_tests();
   33:     register_ps2_runtime_io_tests();
   34:     register_ps2_runtime_kernel_tests();
   35:     register_ps2_runtime_interrupt_tests();
   36:     register_ps2_memory_tests();
   37:     register_ps2_vu1_tests();
   38:     register_ps2_vu_tests();
   39:     register_ps2_gs_tests();
   40:     register_ps2_iop_tests();
   41:     register_ps2_sif_rpc_tests();
   42:     register_ps2_sif_dma_tests();
   43:     register_ps2_recompiler_tests();
   44:     register_ps2_runtime_expansion_tests();
   45:     register_ps2_float_semantics_tests();
   46:     register_ps2_audio_stream_tests();
   47:     int res = MiniTest::Run();
   48:     std::cout.flush();
   49:     std::cerr.flush();
   50:     std::_Exit(res);
   51: }
--- lines 14-51 ---
   14: void register_ps2_vu_tests();
   15: void register_ps2_gs_tests();
   16: void register_ps2_iop_tests();
   17: void register_ps2_sif_rpc_tests();
   18: void register_ps2_sif_dma_tests();
   19: void register_ps2_recompiler_tests();
   20: void register_ps2_runtime_expansion_tests();
   21: void register_ps2_float_semantics_tests();
   22: void register_ps2_audio_stream_tests();
   23: void reset_ps2_test_function_table();
   24: 
   25: int main()
   26: {
   27:     MiniTest::BeforeEach(reset_ps2_test_function_table);
   28: 
   29:     register_code_generator_tests();
   30:     register_r5900_decoder_tests();
   31:     register_elf_analyzer_tests();
   32:     register_pad_input_tests();
   33:     register_ps2_runtime_io_tests();
   34:     register_ps2_runtime_kernel_tests();
   35:     register_ps2_runtime_interrupt_tests();
   36:     register_ps2_memory_tests();
   37:     register_ps2_vu1_tests();
   38:     register_ps2_vu_tests();
   39:     register_ps2_gs_tests();
   40:     register_ps2_iop_tests();
   41:     register_ps2_sif_rpc_tests();
   42:     register_ps2_sif_dma_tests();
   43:     register_ps2_recompiler_tests();
   44:     register_ps2_runtime_expansion_tests();
   45:     register_ps2_float_semantics_tests();
   46:     register_ps2_audio_stream_tests();
   47:     int res = MiniTest::Run();
   48:     std::cout.flush();
   49:     std::cerr.flush();
   50:     std::_Exit(res);
   51: }
--- lines 17-51 ---
   17: void register_ps2_sif_rpc_tests();
   18: void register_ps2_sif_dma_tests();
   19: void register_ps2_recompiler_tests();
   20: void register_ps2_runtime_expansion_tests();
   21: void register_ps2_float_semantics_tests();
   22: void register_ps2_audio_stream_tests();
   23: void reset_ps2_test_function_table();
   24: 
   25: int main()
   26: {
   27:     MiniTest::BeforeEach(reset_ps2_test_function_table);
   28: 
   29:     register_code_generator_tests();
   30:     register_r5900_decoder_tests();
   31:     register_elf_analyzer_tests();
   32:     register_pad_input_tests();
   33:     register_ps2_runtime_io_tests();
   34:     register_ps2_runtime_kernel_tests();
   35:     register_ps2_runtime_interrupt_tests();
   36:     register_ps2_memory_tests();
   37:     register_ps2_vu1_tests();
   38:     register_ps2_vu_tests();
   39:     register_ps2_gs_tests();
   40:     register_ps2_iop_tests();
   41:     register_ps2_sif_rpc_tests();
   42:     register_ps2_sif_dma_tests();
   43:     register_ps2_recompiler_tests();
   44:     register_ps2_runtime_expansion_tests();
   45:     register_ps2_float_semantics_tests();
   46:     register_ps2_audio_stream_tests();
   47:     int res = MiniTest::Run();
   48:     std::cout.flush();
   49:     std::cerr.flush();
   50:     std::_Exit(res);
   51: }
--- lines 21-51 ---
   21: void register_ps2_float_semantics_tests();
   22: void register_ps2_audio_stream_tests();
   23: void reset_ps2_test_function_table();
   24: 
   25: int main()
   26: {
   27:     MiniTest::BeforeEach(reset_ps2_test_function_table);
   28: 
   29:     register_code_generator_tests();
   30:     register_r5900_decoder_tests();
   31:     register_elf_analyzer_tests();
   32:     register_pad_input_tests();
   33:     register_ps2_runtime_io_tests();
   34:     register_ps2_runtime_kernel_tests();
   35:     register_ps2_runtime_interrupt_tests();
   36:     register_ps2_memory_tests();
   37:     register_ps2_vu1_tests();
   38:     register_ps2_vu_tests();
   39:     register_ps2_gs_tests();
   40:     register_ps2_iop_tests();
   41:     register_ps2_sif_rpc_tests();
   42:     register_ps2_sif_dma_tests();
   43:     register_ps2_recompiler_tests();
   44:     register_ps2_runtime_expansion_tests();
   45:     register_ps2_float_semantics_tests();
   46:     register_ps2_audio_stream_tests();
   47:     int res = MiniTest::Run();
   48:     std::cout.flush();
   49:     std::cerr.flush();
   50:     std::_Exit(res);
   51: }
--- lines 22-51 ---
   22: void register_ps2_audio_stream_tests();
   23: void reset_ps2_test_function_table();
   24: 
   25: int main()
   26: {
   27:     MiniTest::BeforeEach(reset_ps2_test_function_table);
   28: 
   29:     register_code_generator_tests();
   30:     register_r5900_decoder_tests();
   31:     register_elf_analyzer_tests();
   32:     register_pad_input_tests();
   33:     register_ps2_runtime_io_tests();
   34:     register_ps2_runtime_kernel_tests();
   35:     register_ps2_runtime_interrupt_tests();
   36:     register_ps2_memory_tests();
   37:     register_ps2_vu1_tests();
   38:     register_ps2_vu_tests();
   39:     register_ps2_gs_tests();
   40:     register_ps2_iop_tests();
   41:     register_ps2_sif_rpc_tests();
   42:     register_ps2_sif_dma_tests();
   43:     register_ps2_recompiler_tests();
   44:     register_ps2_runtime_expansion_tests();
   45:     register_ps2_float_semantics_tests();
   46:     register_ps2_audio_stream_tests();
   47:     int res = MiniTest::Run();
   48:     std::cout.flush();
   49:     std::cerr.flush();
   50:     std::_Exit(res);
   51: }
--- lines 23-51 ---
   23: void reset_ps2_test_function_table();
   24: 
   25: int main()
   26: {
   27:     MiniTest::BeforeEach(reset_ps2_test_function_table);
   28: 
   29:     register_code_generator_tests();
   30:     register_r5900_decoder_tests();
   31:     register_elf_analyzer_tests();
   32:     register_pad_input_tests();
   33:     register_ps2_runtime_io_tests();
   34:     register_ps2_runtime_kernel_tests();
   35:     register_ps2_runtime_interrupt_tests();
   36:     register_ps2_memory_tests();
   37:     register_ps2_vu1_tests();
   38:     register_ps2_vu_tests();
   39:     register_ps2_gs_tests();
   40:     register_ps2_iop_tests();
   41:     register_ps2_sif_rpc_tests();
   42:     register_ps2_sif_dma_tests();
   43:     register_ps2_recompiler_tests();
   44:     register_ps2_runtime_expansion_tests();
   45:     register_ps2_float_semantics_tests();
   46:     register_ps2_audio_stream_tests();
   47:     int res = MiniTest::Run();
   48:     std::cout.flush();
   49:     std::cerr.flush();
   50:     std::_Exit(res);
   51: }
--- lines 24-51 ---
   24: 
   25: int main()
   26: {
   27:     MiniTest::BeforeEach(reset_ps2_test_function_table);
   28: 
   29:     register_code_generator_tests();
   30:     register_r5900_decoder_tests();
   31:     register_elf_analyzer_tests();
   32:     register_pad_input_tests();
   33:     register_ps2_runtime_io_tests();
   34:     register_ps2_runtime_kernel_tests();
   35:     register_ps2_runtime_interrupt_tests();
   36:     register_ps2_memory_tests();
   37:     register_ps2_vu1_tests();
   38:     register_ps2_vu_tests();
   39:     register_ps2_gs_tests();
   40:     register_ps2_iop_tests();
   41:     register_ps2_sif_rpc_tests();
   42:     register_ps2_sif_dma_tests();
   43:     register_ps2_recompiler_tests();
   44:     register_ps2_runtime_expansion_tests();
   45:     register_ps2_float_semantics_tests();
   46:     register_ps2_audio_stream_tests();
   47:     int res = MiniTest::Run();
   48:     std::cout.flush();
   49:     std::cerr.flush();
   50:     std::_Exit(res);
   51: }
--- lines 25-51 ---
   25: int main()
   26: {
   27:     MiniTest::BeforeEach(reset_ps2_test_function_table);
   28: 
   29:     register_code_generator_tests();
   30:     register_r5900_decoder_tests();
   31:     register_elf_analyzer_tests();
   32:     register_pad_input_tests();
   33:     register_ps2_runtime_io_tests();
   34:     register_ps2_runtime_kernel_tests();
   35:     register_ps2_runtime_interrupt_tests();
   36:     register_ps2_memory_tests();
   37:     register_ps2_vu1_tests();
   38:     register_ps2_vu_tests();
   39:     register_ps2_gs_tests();
   40:     register_ps2_iop_tests();
   41:     register_ps2_sif_rpc_tests();
   42:     register_ps2_sif_dma_tests();
   43:     register_ps2_recompiler_tests();
   44:     register_ps2_runtime_expansion_tests();
   45:     register_ps2_float_semantics_tests();
   46:     register_ps2_audio_stream_tests();
   47:     int res = MiniTest::Run();
   48:     std::cout.flush();
   49:     std::cerr.flush();
   50:     std::_Exit(res);
   51: }
--- lines 26-51 ---
   26: {
   27:     MiniTest::BeforeEach(reset_ps2_test_function_table);
   28: 
   29:     register_code_generator_tests();
   30:     register_r5900_decoder_tests();
   31:     register_elf_analyzer_tests();
   32:     register_pad_input_tests();
   33:     register_ps2_runtime_io_tests();
   34:     register_ps2_runtime_kernel_tests();
   35:     register_ps2_runtime_interrupt_tests();
   36:     register_ps2_memory_tests();
   37:     register_ps2_vu1_tests();
   38:     register_ps2_vu_tests();
   39:     register_ps2_gs_tests();
   40:     register_ps2_iop_tests();
   41:     register_ps2_sif_rpc_tests();
   42:     register_ps2_sif_dma_tests();
   43:     register_ps2_recompiler_tests();
   44:     register_ps2_runtime_expansion_tests();
   45:     register_ps2_float_semantics_tests();
   46:     register_ps2_audio_stream_tests();
   47:     int res = MiniTest::Run();
   48:     std::cout.flush();
   49:     std::cerr.flush();
   50:     std::_Exit(res);
   51: }
--- lines 27-51 ---
   27:     MiniTest::BeforeEach(reset_ps2_test_function_table);
   28: 
   29:     register_code_generator_tests();
   30:     register_r5900_decoder_tests();
   31:     register_elf_analyzer_tests();
   32:     register_pad_input_tests();
   33:     register_ps2_runtime_io_tests();
   34:     register_ps2_runtime_kernel_tests();
   35:     register_ps2_runtime_interrupt_tests();
   36:     register_ps2_memory_tests();
   37:     register_ps2_vu1_tests();
   38:     register_ps2_vu_tests();
   39:     register_ps2_gs_tests();
   40:     register_ps2_iop_tests();
   41:     register_ps2_sif_rpc_tests();
   42:     register_ps2_sif_dma_tests();
   43:     register_ps2_recompiler_tests();
   44:     register_ps2_runtime_expansion_tests();
   45:     register_ps2_float_semantics_tests();
   46:     register_ps2_audio_stream_tests();
   47:     int res = MiniTest::Run();
   48:     std::cout.flush();
   49:     std::cerr.flush();
   50:     std::_Exit(res);
   51: }
--- lines 28-51 ---
   28: 
   29:     register_code_generator_tests();
   30:     register_r5900_decoder_tests();
   31:     register_elf_analyzer_tests();
   32:     register_pad_input_tests();
   33:     register_ps2_runtime_io_tests();
   34:     register_ps2_runtime_kernel_tests();
   35:     register_ps2_runtime_interrupt_tests();
   36:     register_ps2_memory_tests();
   37:     register_ps2_vu1_tests();
   38:     register_ps2_vu_tests();
   39:     register_ps2_gs_tests();
   40:     register_ps2_iop_tests();
   41:     register_ps2_sif_rpc_tests();
   42:     register_ps2_sif_dma_tests();
   43:     register_ps2_recompiler_tests();
   44:     register_ps2_runtime_expansion_tests();
   45:     register_ps2_float_semantics_tests();
   46:     register_ps2_audio_stream_tests();
   47:     int res = MiniTest::Run();
   48:     std::cout.flush();
   49:     std::cerr.flush();
   50:     std::_Exit(res);
   51: }
--- lines 29-51 ---
   29:     register_code_generator_tests();
   30:     register_r5900_decoder_tests();
   31:     register_elf_analyzer_tests();
   32:     register_pad_input_tests();
   33:     register_ps2_runtime_io_tests();
   34:     register_ps2_runtime_kernel_tests();
   35:     register_ps2_runtime_interrupt_tests();
   36:     register_ps2_memory_tests();
   37:     register_ps2_vu1_tests();
   38:     register_ps2_vu_tests();
   39:     register_ps2_gs_tests();
   40:     register_ps2_iop_tests();
   41:     register_ps2_sif_rpc_tests();
   42:     register_ps2_sif_dma_tests();
   43:     register_ps2_recompiler_tests();
   44:     register_ps2_runtime_expansion_tests();
   45:     register_ps2_float_semantics_tests();
   46:     register_ps2_audio_stream_tests();
   47:     int res = MiniTest::Run();
   48:     std::cout.flush();
   49:     std::cerr.flush();
   50:     std::_Exit(res);
   51: }
--- lines 30-51 ---
   30:     register_r5900_decoder_tests();
   31:     register_elf_analyzer_tests();
   32:     register_pad_input_tests();
   33:     register_ps2_runtime_io_tests();
   34:     register_ps2_runtime_kernel_tests();
   35:     register_ps2_runtime_interrupt_tests();
   36:     register_ps2_memory_tests();
   37:     register_ps2_vu1_tests();
   38:     register_ps2_vu_tests();
   39:     register_ps2_gs_tests();
   40:     register_ps2_iop_tests();
   41:     register_ps2_sif_rpc_tests();
   42:     register_ps2_sif_dma_tests();
   43:     register_ps2_recompiler_tests();
   44:     register_ps2_runtime_expansion_tests();
   45:     register_ps2_float_semantics_tests();
   46:     register_ps2_audio_stream_tests();
   47:     int res = MiniTest::Run();
   48:     std::cout.flush();
   49:     std::cerr.flush();
   50:     std::_Exit(res);
   51: }
--- lines 31-51 ---
   31:     register_elf_analyzer_tests();
   32:     register_pad_input_tests();
   33:     register_ps2_runtime_io_tests();
   34:     register_ps2_runtime_kernel_tests();
   35:     register_ps2_runtime_interrupt_tests();
   36:     register_ps2_memory_tests();
   37:     register_ps2_vu1_tests();
   38:     register_ps2_vu_tests();
   39:     register_ps2_gs_tests();
   40:     register_ps2_iop_tests();
   41:     register_ps2_sif_rpc_tests();
   42:     register_ps2_sif_dma_tests();
   43:     register_ps2_recompiler_tests();
   44:     register_ps2_runtime_expansion_tests();
   45:     register_ps2_float_semantics_tests();
   46:     register_ps2_audio_stream_tests();
   47:     int res = MiniTest::Run();
   48:     std::cout.flush();
   49:     std::cerr.flush();
   50:     std::_Exit(res);
   51: }
--- lines 32-51 ---
   32:     register_pad_input_tests();
   33:     register_ps2_runtime_io_tests();
   34:     register_ps2_runtime_kernel_tests();
   35:     register_ps2_runtime_interrupt_tests();
   36:     register_ps2_memory_tests();
   37:     register_ps2_vu1_tests();
   38:     register_ps2_vu_tests();
   39:     register_ps2_gs_tests();
   40:     register_ps2_iop_tests();
   41:     register_ps2_sif_rpc_tests();
   42:     register_ps2_sif_dma_tests();
   43:     register_ps2_recompiler_tests();
   44:     register_ps2_runtime_expansion_tests();
   45:     register_ps2_float_semantics_tests();
   46:     register_ps2_audio_stream_tests();
   47:     int res = MiniTest::Run();
   48:     std::cout.flush();
   49:     std::cerr.flush();
   50:     std::_Exit(res);
   51: }
--- lines 33-51 ---
   33:     register_ps2_runtime_io_tests();
   34:     register_ps2_runtime_kernel_tests();
   35:     register_ps2_runtime_interrupt_tests();
   36:     register_ps2_memory_tests();
   37:     register_ps2_vu1_tests();
   38:     register_ps2_vu_tests();
   39:     register_ps2_gs_tests();
   40:     register_ps2_iop_tests();
   41:     register_ps2_sif_rpc_tests();
   42:     register_ps2_sif_dma_tests();
   43:     register_ps2_recompiler_tests();
   44:     register_ps2_runtime_expansion_tests();
   45:     register_ps2_float_semantics_tests();
   46:     register_ps2_audio_stream_tests();
   47:     int res = MiniTest::Run();
   48:     std::cout.flush();
   49:     std::cerr.flush();
   50:     std::_Exit(res);
   51: }
--- lines 34-51 ---
   34:     register_ps2_runtime_kernel_tests();
   35:     register_ps2_runtime_interrupt_tests();
   36:     register_ps2_memory_tests();
   37:     register_ps2_vu1_tests();
   38:     register_ps2_vu_tests();
   39:     register_ps2_gs_tests();
   40:     register_ps2_iop_tests();
   41:     register_ps2_sif_rpc_tests();
   42:     register_ps2_sif_dma_tests();
   43:     register_ps2_recompiler_tests();
   44:     register_ps2_runtime_expansion_tests();
   45:     register_ps2_float_semantics_tests();
   46:     register_ps2_audio_stream_tests();
   47:     int res = MiniTest::Run();
   48:     std::cout.flush();
   49:     std::cerr.flush();
   50:     std::_Exit(res);
   51: }
--- lines 35-51 ---
   35:     register_ps2_runtime_interrupt_tests();
   36:     register_ps2_memory_tests();
   37:     register_ps2_vu1_tests();
   38:     register_ps2_vu_tests();
   39:     register_ps2_gs_tests();
   40:     register_ps2_iop_tests();
   41:     register_ps2_sif_rpc_tests();
   42:     register_ps2_sif_dma_tests();
   43:     register_ps2_recompiler_tests();
   44:     register_ps2_runtime_expansion_tests();
   45:     register_ps2_float_semantics_tests();
   46:     register_ps2_audio_stream_tests();
   47:     int res = MiniTest::Run();
   48:     std::cout.flush();
   49:     std::cerr.flush();
   50:     std::_Exit(res);
   51: }
--- lines 36-51 ---
   36:     register_ps2_memory_tests();
   37:     register_ps2_vu1_tests();
   38:     register_ps2_vu_tests();
   39:     register_ps2_gs_tests();
   40:     register_ps2_iop_tests();
   41:     register_ps2_sif_rpc_tests();
   42:     register_ps2_sif_dma_tests();
   43:     register_ps2_recompiler_tests();
   44:     register_ps2_runtime_expansion_tests();
   45:     register_ps2_float_semantics_tests();
   46:     register_ps2_audio_stream_tests();
   47:     int res = MiniTest::Run();
   48:     std::cout.flush();
   49:     std::cerr.flush();
   50:     std::_Exit(res);
   51: }
--- lines 37-51 ---
   37:     register_ps2_vu1_tests();
   38:     register_ps2_vu_tests();
   39:     register_ps2_gs_tests();
   40:     register_ps2_iop_tests();
   41:     register_ps2_sif_rpc_tests();
   42:     register_ps2_sif_dma_tests();
   43:     register_ps2_recompiler_tests();
   44:     register_ps2_runtime_expansion_tests();
   45:     register_ps2_float_semantics_tests();
   46:     register_ps2_audio_stream_tests();
   47:     int res = MiniTest::Run();
   48:     std::cout.flush();
   49:     std::cerr.flush();
   50:     std::_Exit(res);
   51: }
--- lines 38-51 ---
   38:     register_ps2_vu_tests();
   39:     register_ps2_gs_tests();
   40:     register_ps2_iop_tests();
   41:     register_ps2_sif_rpc_tests();
   42:     register_ps2_sif_dma_tests();
   43:     register_ps2_recompiler_tests();
   44:     register_ps2_runtime_expansion_tests();
   45:     register_ps2_float_semantics_tests();
   46:     register_ps2_audio_stream_tests();
   47:     int res = MiniTest::Run();
   48:     std::cout.flush();
   49:     std::cerr.flush();
   50:     std::_Exit(res);
   51: }
--- lines 39-51 ---
   39:     register_ps2_gs_tests();
   40:     register_ps2_iop_tests();
   41:     register_ps2_sif_rpc_tests();
   42:     register_ps2_sif_dma_tests();
   43:     register_ps2_recompiler_tests();
   44:     register_ps2_runtime_expansion_tests();
   45:     register_ps2_float_semantics_tests();
   46:     register_ps2_audio_stream_tests();
   47:     int res = MiniTest::Run();
   48:     std::cout.flush();
   49:     std::cerr.flush();
   50:     std::_Exit(res);
   51: }

===== ps2xRuntime\include\ps2_runtime.h =====
--- lines 135-161 ---
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
--- lines 136-162 ---
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
--- lines 264-290 ---
  264:     (void)rdram;
  265:     (void)guestAddr;
  266:     (void)size;
  267:     (void)op;
  268:     (void)ctx;
  269:     // TODO we dont need this anymore so on next release it will be deleted
  270: }
  271: 
  272: class PS2Runtime
  273: {
  274: public:
  275:     struct IoPaths
  276:     {
  277:         std::filesystem::path elfPath;
  278:         std::filesystem::path elfDirectory;
  279:         std::filesystem::path hostRoot;
  280:         std::filesystem::path cdRoot;
  281:         std::filesystem::path mcRoot;
  282:         std::filesystem::path cdImage;
  283:     };
  284: 
  285:     PS2Runtime();
  286:     ~PS2Runtime();
  287: 
  288:     bool initialize(const char *title = "PS2 Game");
  289:     bool syncCoreSubsystems();
  290:     bool loadELF(const std::string &elfPath);
--- lines 277-303 ---
  277:         std::filesystem::path elfPath;
  278:         std::filesystem::path elfDirectory;
  279:         std::filesystem::path hostRoot;
  280:         std::filesystem::path cdRoot;
  281:         std::filesystem::path mcRoot;
  282:         std::filesystem::path cdImage;
  283:     };
  284: 
  285:     PS2Runtime();
  286:     ~PS2Runtime();
  287: 
  288:     bool initialize(const char *title = "PS2 Game");
  289:     bool syncCoreSubsystems();
  290:     bool loadELF(const std::string &elfPath);
  291:     void run();
  292: 
  293:     [[nodiscard]] ps2x::iop::ModuleLoadResult loadIopModule(std::string_view path, const void *arguments = nullptr, uint32_t argumentSize = 0);
  294:     [[nodiscard]] ps2x::iop::ModuleLoadResult loadIopModuleBuffer(uint32_t guestAddress, const void *arguments = nullptr, uint32_t argumentSize = 0);
  295:     [[nodiscard]] bool stopIopModule(int32_t moduleId, int32_t *result = nullptr);
  296:     [[nodiscard]] int32_t findIopModuleByAddress(uint32_t iopAddress) const noexcept;
  297:     [[nodiscard]] ps2x::iop::DebugSnapshot iopDebugSnapshot() const;
  298:     uint32_t allocateIopMemory(uint32_t size, uint32_t alignment = 16u);
  299:     bool freeIopMemory(uint32_t address);
  300:     bool readIopMemory(uint32_t address, void *destination, size_t size) const;
  301:     bool writeIopMemory(uint32_t address, const void *source, size_t size);
  302:     bool zeroIopMemory(uint32_t address, size_t size);
  303:     bool isIopMemoryRange(uint32_t address, size_t size) const;
--- lines 278-304 ---
  278:         std::filesystem::path elfDirectory;
  279:         std::filesystem::path hostRoot;
  280:         std::filesystem::path cdRoot;
  281:         std::filesystem::path mcRoot;
  282:         std::filesystem::path cdImage;
  283:     };
  284: 
  285:     PS2Runtime();
  286:     ~PS2Runtime();
  287: 
  288:     bool initialize(const char *title = "PS2 Game");
  289:     bool syncCoreSubsystems();
  290:     bool loadELF(const std::string &elfPath);
  291:     void run();
  292: 
  293:     [[nodiscard]] ps2x::iop::ModuleLoadResult loadIopModule(std::string_view path, const void *arguments = nullptr, uint32_t argumentSize = 0);
  294:     [[nodiscard]] ps2x::iop::ModuleLoadResult loadIopModuleBuffer(uint32_t guestAddress, const void *arguments = nullptr, uint32_t argumentSize = 0);
  295:     [[nodiscard]] bool stopIopModule(int32_t moduleId, int32_t *result = nullptr);
  296:     [[nodiscard]] int32_t findIopModuleByAddress(uint32_t iopAddress) const noexcept;
  297:     [[nodiscard]] ps2x::iop::DebugSnapshot iopDebugSnapshot() const;
  298:     uint32_t allocateIopMemory(uint32_t size, uint32_t alignment = 16u);
  299:     bool freeIopMemory(uint32_t address);
  300:     bool readIopMemory(uint32_t address, void *destination, size_t size) const;
  301:     bool writeIopMemory(uint32_t address, const void *source, size_t size);
  302:     bool zeroIopMemory(uint32_t address, size_t size);
  303:     bool isIopMemoryRange(uint32_t address, size_t size) const;
  304: 
--- lines 297-323 ---
  297:     [[nodiscard]] ps2x::iop::DebugSnapshot iopDebugSnapshot() const;
  298:     uint32_t allocateIopMemory(uint32_t size, uint32_t alignment = 16u);
  299:     bool freeIopMemory(uint32_t address);
  300:     bool readIopMemory(uint32_t address, void *destination, size_t size) const;
  301:     bool writeIopMemory(uint32_t address, const void *source, size_t size);
  302:     bool zeroIopMemory(uint32_t address, size_t size);
  303:     bool isIopMemoryRange(uint32_t address, size_t size) const;
  304: 
  305:     using DebugUiCallback = void (*)(PS2Runtime &runtime, void *userData);
  306:     void setDebugUiCallbacks(DebugUiCallback initCallback,
  307:                              DebugUiCallback drawCallback,
  308:                              DebugUiCallback shutdownCallback,
  309:                              void *userData);
  310: 
  311:     using RecompiledFunction = void (*)(uint8_t *, R5900Context *, PS2Runtime *);
  312: 
  313:     enum class GuestBranchKind
  314:     {
  315:         DirectJump,
  316:         DirectCall,
  317:         IndirectJump,
  318:         IndirectCall,
  319:         Return,
  320:     };
  321: 
  322:     enum class MissingFunctionPolicy : uint32_t
  323:     {
--- lines 303-329 ---
  303:     bool isIopMemoryRange(uint32_t address, size_t size) const;
  304: 
  305:     using DebugUiCallback = void (*)(PS2Runtime &runtime, void *userData);
  306:     void setDebugUiCallbacks(DebugUiCallback initCallback,
  307:                              DebugUiCallback drawCallback,
  308:                              DebugUiCallback shutdownCallback,
  309:                              void *userData);
  310: 
  311:     using RecompiledFunction = void (*)(uint8_t *, R5900Context *, PS2Runtime *);
  312: 
  313:     enum class GuestBranchKind
  314:     {
  315:         DirectJump,
  316:         DirectCall,
  317:         IndirectJump,
  318:         IndirectCall,
  319:         Return,
  320:     };
  321: 
  322:     enum class MissingFunctionPolicy : uint32_t
  323:     {
  324:         // Strict mode for tests/CI: log the bad target and request the runtime to stop.
  325:         Stop = 0,
  326: 
  327:         // Debug mode: log once, leave ctx->pc on the bad target, and let the caller unwind.
  328:         ContinueToTarget = 1,
  329: 
--- lines 547-557 ---
  547:     uint8_t *m_boundRdram = nullptr;
  548:     uint8_t *m_boundGSVram = nullptr;
  549: };
  550: 
  551: // Generated by ps2xRecomp in ps2xRuntime/src/runner/register_functions.cpp.
  552: extern const uint32_t g_ps2RecompiledFunctionTableBase;
  553: extern const uint32_t g_ps2RecompiledFunctionTableEnd;
  554: extern const uint32_t g_ps2RecompiledFunctionTableSlotCount;
  555: extern PS2Runtime::RecompiledFunction g_ps2RecompiledFunctionTable[];
  556: 
  557: #endif // PS2_RUNTIME_H

===== ps2xRuntime\include\ps2_runtime_macros.h =====
--- lines 902-907 ---
  902: 
  903: // FPU (COP1) operations
  904: #define FPU_SET_ACC(ctx, res) (ctx->f_acc = res)
  905: #define FPU_ADD_S(a, b) ps2_fadd((float)(a), (float)(b))
  906: #define FPU_SUB_S(a, b) ps2_fsub((float)(a), (float)(b))
  907: #define FPU_MUL_S(a, b) ps2_fmul((float)(a), (float)(b))
--- lines 903-908 ---
  903: // FPU (COP1) operations
  904: #define FPU_SET_ACC(ctx, res) (ctx->f_acc = res)
  905: #define FPU_ADD_S(a, b) ps2_fadd((float)(a), (float)(b))
  906: #define FPU_SUB_S(a, b) ps2_fsub((float)(a), (float)(b))
  907: #define FPU_MUL_S(a, b) ps2_fmul((float)(a), (float)(b))
  908: #define FPU_DIV_S(a, b) ps2_fdiv((float)(a), (float)(b))
--- lines 904-909 ---
  904: #define FPU_SET_ACC(ctx, res) (ctx->f_acc = res)
  905: #define FPU_ADD_S(a, b) ps2_fadd((float)(a), (float)(b))
  906: #define FPU_SUB_S(a, b) ps2_fsub((float)(a), (float)(b))
  907: #define FPU_MUL_S(a, b) ps2_fmul((float)(a), (float)(b))
  908: #define FPU_DIV_S(a, b) ps2_fdiv((float)(a), (float)(b))
  909: #define FPU_RSQRT_S(a, b) ps2_frsqrt((float)(a), (float)(b))
--- lines 905-910 ---
  905: #define FPU_ADD_S(a, b) ps2_fadd((float)(a), (float)(b))
  906: #define FPU_SUB_S(a, b) ps2_fsub((float)(a), (float)(b))
  907: #define FPU_MUL_S(a, b) ps2_fmul((float)(a), (float)(b))
  908: #define FPU_DIV_S(a, b) ps2_fdiv((float)(a), (float)(b))
  909: #define FPU_RSQRT_S(a, b) ps2_frsqrt((float)(a), (float)(b))
  910: #define FPU_SQRT_S(a) ps2_fsqrt((float)(a))

===== ps2xRecomp\src\lib\fpu_translator.cpp =====
--- lines 80-87 ---
   80:                 // RSQRT.S fd, fs, ft computes fs / sqrt(ft), not 1 / sqrt(fs).
   81:                 return fmt::format("ctx->f[{}] = FPU_RSQRT_S(ctx->f[{}], ctx->f[{}]);", fd, fs, ft);
   82:             case COP1_S_ADDA:
   83:                 return fmt::format("FPU_SET_ACC(ctx, FPU_ADD_S(ctx->f[{}], ctx->f[{}]));", fs, ft);
   84:             case COP1_S_SUBA:
   85:                 return fmt::format("FPU_SET_ACC(ctx, FPU_SUB_S(ctx->f[{}], ctx->f[{}]));", fs, ft);
   86:             case COP1_S_MULA:
   87:                 return fmt::format("FPU_SET_ACC(ctx, FPU_MUL_S(ctx->f[{}], ctx->f[{}]));", fs, ft);
--- lines 82-89 ---
   82:             case COP1_S_ADDA:
   83:                 return fmt::format("FPU_SET_ACC(ctx, FPU_ADD_S(ctx->f[{}], ctx->f[{}]));", fs, ft);
   84:             case COP1_S_SUBA:
   85:                 return fmt::format("FPU_SET_ACC(ctx, FPU_SUB_S(ctx->f[{}], ctx->f[{}]));", fs, ft);
   86:             case COP1_S_MULA:
   87:                 return fmt::format("FPU_SET_ACC(ctx, FPU_MUL_S(ctx->f[{}], ctx->f[{}]));", fs, ft);
   88:             case COP1_S_MADD:
   89:                 return fmt::format("ctx->f[{}] = FPU_ADD_S(ctx->f_acc, FPU_MUL_S(ctx->f[{}], ctx->f[{}]));", fd, fs, ft);
--- lines 84-91 ---
   84:             case COP1_S_SUBA:
   85:                 return fmt::format("FPU_SET_ACC(ctx, FPU_SUB_S(ctx->f[{}], ctx->f[{}]));", fs, ft);
   86:             case COP1_S_MULA:
   87:                 return fmt::format("FPU_SET_ACC(ctx, FPU_MUL_S(ctx->f[{}], ctx->f[{}]));", fs, ft);
   88:             case COP1_S_MADD:
   89:                 return fmt::format("ctx->f[{}] = FPU_ADD_S(ctx->f_acc, FPU_MUL_S(ctx->f[{}], ctx->f[{}]));", fd, fs, ft);
   90:             case COP1_S_MSUB:
   91:                 return fmt::format("ctx->f[{}] = FPU_SUB_S(ctx->f_acc, FPU_MUL_S(ctx->f[{}], ctx->f[{}]));", fd, fs, ft);
--- lines 86-93 ---
   86:             case COP1_S_MULA:
   87:                 return fmt::format("FPU_SET_ACC(ctx, FPU_MUL_S(ctx->f[{}], ctx->f[{}]));", fs, ft);
   88:             case COP1_S_MADD:
   89:                 return fmt::format("ctx->f[{}] = FPU_ADD_S(ctx->f_acc, FPU_MUL_S(ctx->f[{}], ctx->f[{}]));", fd, fs, ft);
   90:             case COP1_S_MSUB:
   91:                 return fmt::format("ctx->f[{}] = FPU_SUB_S(ctx->f_acc, FPU_MUL_S(ctx->f[{}], ctx->f[{}]));", fd, fs, ft);
   92:             case COP1_S_MADDA:
   93:                 return fmt::format("FPU_SET_ACC(ctx, FPU_ADD_S(ctx->f_acc, FPU_MUL_S(ctx->f[{}], ctx->f[{}])));", fs, ft);
--- lines 88-95 ---
   88:             case COP1_S_MADD:
   89:                 return fmt::format("ctx->f[{}] = FPU_ADD_S(ctx->f_acc, FPU_MUL_S(ctx->f[{}], ctx->f[{}]));", fd, fs, ft);
   90:             case COP1_S_MSUB:
   91:                 return fmt::format("ctx->f[{}] = FPU_SUB_S(ctx->f_acc, FPU_MUL_S(ctx->f[{}], ctx->f[{}]));", fd, fs, ft);
   92:             case COP1_S_MADDA:
   93:                 return fmt::format("FPU_SET_ACC(ctx, FPU_ADD_S(ctx->f_acc, FPU_MUL_S(ctx->f[{}], ctx->f[{}])));", fs, ft);
   94:             case COP1_S_MSUBA:
   95:                 return fmt::format("FPU_SET_ACC(ctx, FPU_SUB_S(ctx->f_acc, FPU_MUL_S(ctx->f[{}], ctx->f[{}])));", fs, ft);
--- lines 90-97 ---
   90:             case COP1_S_MSUB:
   91:                 return fmt::format("ctx->f[{}] = FPU_SUB_S(ctx->f_acc, FPU_MUL_S(ctx->f[{}], ctx->f[{}]));", fd, fs, ft);
   92:             case COP1_S_MADDA:
   93:                 return fmt::format("FPU_SET_ACC(ctx, FPU_ADD_S(ctx->f_acc, FPU_MUL_S(ctx->f[{}], ctx->f[{}])));", fs, ft);
   94:             case COP1_S_MSUBA:
   95:                 return fmt::format("FPU_SET_ACC(ctx, FPU_SUB_S(ctx->f_acc, FPU_MUL_S(ctx->f[{}], ctx->f[{}])));", fs, ft);
   96:             case COP1_S_MAX:
   97:                 return fmt::format("ctx->f[{}] = std::max(ctx->f[{}], ctx->f[{}]);", fd, fs, ft);
--- lines 92-99 ---
   92:             case COP1_S_MADDA:
   93:                 return fmt::format("FPU_SET_ACC(ctx, FPU_ADD_S(ctx->f_acc, FPU_MUL_S(ctx->f[{}], ctx->f[{}])));", fs, ft);
   94:             case COP1_S_MSUBA:
   95:                 return fmt::format("FPU_SET_ACC(ctx, FPU_SUB_S(ctx->f_acc, FPU_MUL_S(ctx->f[{}], ctx->f[{}])));", fs, ft);
   96:             case COP1_S_MAX:
   97:                 return fmt::format("ctx->f[{}] = std::max(ctx->f[{}], ctx->f[{}]);", fd, fs, ft);
   98:             case COP1_S_MIN:
   99:                 return fmt::format("ctx->f[{}] = std::min(ctx->f[{}], ctx->f[{}]);", fd, fs, ft);
