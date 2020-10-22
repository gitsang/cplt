   1              		.file	"t_virtual2.cpp"
   2              	# GNU C++ (GCC) version 4.8.5 20150623 (Red Hat 4.8.5-39) (x86_64-redhat-linux)
   3              	#	compiled by GNU C version 4.8.5 20150623 (Red Hat 4.8.5-39), GMP version 6.0.0, MPFR version 3.1.
   4              	# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
   5              	# options passed:  -D_GNU_SOURCE t_virtual2.cpp -mtune=generic
   6              	# -march=x86-64 -auxbase-strip t_virtual2.s -g -fverbose-asm
   7              	# options enabled:  -faggressive-loop-optimizations
   8              	# -fasynchronous-unwind-tables -fauto-inc-dec -fbranch-count-reg -fcommon
   9              	# -fdelete-null-pointer-checks -fdwarf2-cfi-asm -fearly-inlining
  10              	# -feliminate-unused-debug-types -fexceptions -ffunction-cse -fgcse-lm
  11              	# -fgnu-runtime -fgnu-unique -fident -finline-atomics -fira-hoist-pressure
  12              	# -fira-share-save-slots -fira-share-spill-slots -fivopts
  13              	# -fkeep-static-consts -fleading-underscore -fmath-errno
  14              	# -fmerge-debug-strings -fmove-loop-invariants -fpeephole
  15              	# -fprefetch-loop-arrays -freg-struct-return
  16              	# -fsched-critical-path-heuristic -fsched-dep-count-heuristic
  17              	# -fsched-group-heuristic -fsched-interblock -fsched-last-insn-heuristic
  18              	# -fsched-rank-heuristic -fsched-spec -fsched-spec-insn-heuristic
  19              	# -fsched-stalled-insns-dep -fshow-column -fsigned-zeros
  20              	# -fsplit-ivs-in-unroller -fstrict-volatile-bitfields -fsync-libcalls
  21              	# -ftrapping-math -ftree-coalesce-vars -ftree-cselim -ftree-forwprop
  22              	# -ftree-loop-if-convert -ftree-loop-im -ftree-loop-ivcanon
  23              	# -ftree-loop-optimize -ftree-parallelize-loops= -ftree-phiprop -ftree-pta
  24              	# -ftree-reassoc -ftree-scev-cprop -ftree-slp-vectorize
  25              	# -ftree-vect-loop-version -funit-at-a-time -funwind-tables -fverbose-asm
  26              	# -fzero-initialized-in-bss -m128bit-long-double -m64 -m80387
  27              	# -maccumulate-outgoing-args -malign-stringops -mfancy-math-387
  28              	# -mfp-ret-in-387 -mfxsr -mglibc -mieee-fp -mlong-double-80 -mmmx -mno-sse4
  29              	# -mpush-args -mred-zone -msse -msse2 -mtls-direct-seg-refs
  30              	
  31              		.text
  32              	.Ltext0:
  33              		.local	_ZStL8__ioinit
  34              		.comm	_ZStL8__ioinit,1,1
  35              		.section	.text._ZN4BaseC2Ev,"axG",@progbits,_ZN4BaseC5Ev,comdat
  36              		.align 2
  37              		.weak	_ZN4BaseC2Ev
  39              	_ZN4BaseC2Ev:
  40              	.LFB972:
  41              		.file 1 "t_virtual2.cpp"
   1:t_virtual2.cpp **** #include <iostream>
   2:t_virtual2.cpp **** 
   3:t_virtual2.cpp **** class Base {
   4:t_virtual2.cpp **** public: 
   5:t_virtual2.cpp ****     Base() {
  42              		.loc 1 5 0
  43              		.cfi_startproc
  44 0000 55       		pushq	%rbp	#
  45              		.cfi_def_cfa_offset 16
  46              		.cfi_offset 6, -16
  47 0001 4889E5   		movq	%rsp, %rbp	#,
  48              		.cfi_def_cfa_register 6
  49 0004 48897DF8 		movq	%rdi, -8(%rbp)	# this, this
  50              	.LBB2:
  51              		.loc 1 5 0
  52 0008 488B45F8 		movq	-8(%rbp), %rax	# this, tmp59
  53 000c 48C70000 		movq	$_ZTV4Base+16, (%rax)	#, this_1(D)->_vptr.Base
  53      000000
  54              	.LBE2:
   6:t_virtual2.cpp ****     }
  55              		.loc 1 6 0
  56 0013 5D       		popq	%rbp	#
  57              		.cfi_def_cfa 7, 8
  58 0014 C3       		ret
  59              		.cfi_endproc
  60              	.LFE972:
  62              		.weak	_ZN4BaseC1Ev
  63              		.set	_ZN4BaseC1Ev,_ZN4BaseC2Ev
  64              		.section	.rodata
  65              	.LC0:
  66 0000 42617365 		.string	"Base"
  66      00
  67              		.section	.text._ZN4Base5printEv,"axG",@progbits,_ZN4Base5printEv,comdat
  68              		.align 2
  69              		.weak	_ZN4Base5printEv
  71              	_ZN4Base5printEv:
  72              	.LFB974:
   7:t_virtual2.cpp **** 
   8:t_virtual2.cpp **** public:
   9:t_virtual2.cpp ****     void print() {
  73              		.loc 1 9 0
  74              		.cfi_startproc
  75 0000 55       		pushq	%rbp	#
  76              		.cfi_def_cfa_offset 16
  77              		.cfi_offset 6, -16
  78 0001 4889E5   		movq	%rsp, %rbp	#,
  79              		.cfi_def_cfa_register 6
  80 0004 4883EC10 		subq	$16, %rsp	#,
  81 0008 48897DF8 		movq	%rdi, -8(%rbp)	# this, this
  10:t_virtual2.cpp ****         std::cout << "Base" << std::endl;
  82              		.loc 1 10 0
  83 000c BE000000 		movl	$.LC0, %esi	#,
  83      00
  84 0011 BF000000 		movl	$_ZSt4cout, %edi	#,
  84      00
  85 0016 E8000000 		call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc	#
  85      00
  86 001b BE000000 		movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi	#,
  86      00
  87 0020 4889C7   		movq	%rax, %rdi	# D.21020,
  88 0023 E8000000 		call	_ZNSolsEPFRSoS_E	#
  88      00
  11:t_virtual2.cpp ****     }
  89              		.loc 1 11 0
  90 0028 C9       		leave
  91              		.cfi_def_cfa 7, 8
  92 0029 C3       		ret
  93              		.cfi_endproc
  94              	.LFE974:
  96              		.section	.rodata
  97              	.LC1:
  98 0005 76426173 		.string	"vBase"
  98      6500
  99              		.section	.text._ZN4Base6vprintEv,"axG",@progbits,_ZN4Base6vprintEv,comdat
 100              		.align 2
 101              		.weak	_ZN4Base6vprintEv
 103              	_ZN4Base6vprintEv:
 104              	.LFB975:
  12:t_virtual2.cpp **** 
  13:t_virtual2.cpp ****     virtual void vprint() {
 105              		.loc 1 13 0
 106              		.cfi_startproc
 107 0000 55       		pushq	%rbp	#
 108              		.cfi_def_cfa_offset 16
 109              		.cfi_offset 6, -16
 110 0001 4889E5   		movq	%rsp, %rbp	#,
 111              		.cfi_def_cfa_register 6
 112 0004 4883EC10 		subq	$16, %rsp	#,
 113 0008 48897DF8 		movq	%rdi, -8(%rbp)	# this, this
  14:t_virtual2.cpp ****         std::cout << "vBase" << std::endl;
 114              		.loc 1 14 0
 115 000c BE000000 		movl	$.LC1, %esi	#,
 115      00
 116 0011 BF000000 		movl	$_ZSt4cout, %edi	#,
 116      00
 117 0016 E8000000 		call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc	#
 117      00
 118 001b BE000000 		movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi	#,
 118      00
 119 0020 4889C7   		movq	%rax, %rdi	# D.21022,
 120 0023 E8000000 		call	_ZNSolsEPFRSoS_E	#
 120      00
  15:t_virtual2.cpp ****     }
 121              		.loc 1 15 0
 122 0028 C9       		leave
 123              		.cfi_def_cfa 7, 8
 124 0029 C3       		ret
 125              		.cfi_endproc
 126              	.LFE975:
 128              		.section	.text._ZN7DerivedC2Ev,"axG",@progbits,_ZN7DerivedC5Ev,comdat
 129              		.align 2
 130              		.weak	_ZN7DerivedC2Ev
 132              	_ZN7DerivedC2Ev:
 133              	.LFB977:
  16:t_virtual2.cpp **** };
  17:t_virtual2.cpp ****  
  18:t_virtual2.cpp **** class Derived : public Base {
  19:t_virtual2.cpp **** public:
  20:t_virtual2.cpp ****     Derived() {
 134              		.loc 1 20 0
 135              		.cfi_startproc
 136 0000 55       		pushq	%rbp	#
 137              		.cfi_def_cfa_offset 16
 138              		.cfi_offset 6, -16
 139 0001 4889E5   		movq	%rsp, %rbp	#,
 140              		.cfi_def_cfa_register 6
 141 0004 4883EC10 		subq	$16, %rsp	#,
 142 0008 48897DF8 		movq	%rdi, -8(%rbp)	# this, this
 143              	.LBB3:
 144              		.loc 1 20 0
 145 000c 488B45F8 		movq	-8(%rbp), %rax	# this, D.21024
 146 0010 4889C7   		movq	%rax, %rdi	# D.21024,
 147 0013 E8000000 		call	_ZN4BaseC2Ev	#
 147      00
 148 0018 488B45F8 		movq	-8(%rbp), %rax	# this, tmp60
 149 001c 48C70000 		movq	$_ZTV7Derived+16, (%rax)	#, this_1(D)->D.20845._vptr.Base
 149      000000
 150              	.LBE3:
  21:t_virtual2.cpp ****     }
 151              		.loc 1 21 0
 152 0023 C9       		leave
 153              		.cfi_def_cfa 7, 8
 154 0024 C3       		ret
 155              		.cfi_endproc
 156              	.LFE977:
 158              		.weak	_ZN7DerivedC1Ev
 159              		.set	_ZN7DerivedC1Ev,_ZN7DerivedC2Ev
 160              		.section	.rodata
 161              	.LC2:
 162 000b 44657269 		.string	"Derived"
 162      76656400 
 163              		.section	.text._ZN7Derived5printEv,"axG",@progbits,_ZN7Derived5printEv,comdat
 164              		.align 2
 165              		.weak	_ZN7Derived5printEv
 167              	_ZN7Derived5printEv:
 168              	.LFB979:
  22:t_virtual2.cpp **** 
  23:t_virtual2.cpp **** public:
  24:t_virtual2.cpp ****     void print(){
 169              		.loc 1 24 0
 170              		.cfi_startproc
 171 0000 55       		pushq	%rbp	#
 172              		.cfi_def_cfa_offset 16
 173              		.cfi_offset 6, -16
 174 0001 4889E5   		movq	%rsp, %rbp	#,
 175              		.cfi_def_cfa_register 6
 176 0004 4883EC10 		subq	$16, %rsp	#,
 177 0008 48897DF8 		movq	%rdi, -8(%rbp)	# this, this
  25:t_virtual2.cpp ****         std::cout << "Derived" << std::endl;
 178              		.loc 1 25 0
 179 000c BE000000 		movl	$.LC2, %esi	#,
 179      00
 180 0011 BF000000 		movl	$_ZSt4cout, %edi	#,
 180      00
 181 0016 E8000000 		call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc	#
 181      00
 182 001b BE000000 		movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi	#,
 182      00
 183 0020 4889C7   		movq	%rax, %rdi	# D.21025,
 184 0023 E8000000 		call	_ZNSolsEPFRSoS_E	#
 184      00
  26:t_virtual2.cpp ****     }
 185              		.loc 1 26 0
 186 0028 C9       		leave
 187              		.cfi_def_cfa 7, 8
 188 0029 C3       		ret
 189              		.cfi_endproc
 190              	.LFE979:
 192              		.section	.rodata
 193              	.LC3:
 194 0013 76446572 		.string	"vDerived"
 194      69766564 
 194      00
 195              		.section	.text._ZN7Derived6vprintEv,"axG",@progbits,_ZN7Derived6vprintEv,comdat
 196              		.align 2
 197              		.weak	_ZN7Derived6vprintEv
 199              	_ZN7Derived6vprintEv:
 200              	.LFB980:
  27:t_virtual2.cpp ****     
  28:t_virtual2.cpp ****     void vprint() {
 201              		.loc 1 28 0
 202              		.cfi_startproc
 203 0000 55       		pushq	%rbp	#
 204              		.cfi_def_cfa_offset 16
 205              		.cfi_offset 6, -16
 206 0001 4889E5   		movq	%rsp, %rbp	#,
 207              		.cfi_def_cfa_register 6
 208 0004 4883EC10 		subq	$16, %rsp	#,
 209 0008 48897DF8 		movq	%rdi, -8(%rbp)	# this, this
  29:t_virtual2.cpp ****         std::cout << "vDerived" << std::endl;
 210              		.loc 1 29 0
 211 000c BE000000 		movl	$.LC3, %esi	#,
 211      00
 212 0011 BF000000 		movl	$_ZSt4cout, %edi	#,
 212      00
 213 0016 E8000000 		call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc	#
 213      00
 214 001b BE000000 		movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi	#,
 214      00
 215 0020 4889C7   		movq	%rax, %rdi	# D.21027,
 216 0023 E8000000 		call	_ZNSolsEPFRSoS_E	#
 216      00
  30:t_virtual2.cpp ****     }
 217              		.loc 1 30 0
 218 0028 C9       		leave
 219              		.cfi_def_cfa 7, 8
 220 0029 C3       		ret
 221              		.cfi_endproc
 222              	.LFE980:
 224              		.text
 225              		.globl	main
 227              	main:
 228              	.LFB981:
  31:t_virtual2.cpp **** };
  32:t_virtual2.cpp ****  
  33:t_virtual2.cpp **** int main() {
 229              		.loc 1 33 0
 230              		.cfi_startproc
 231 0000 55       		pushq	%rbp	#
 232              		.cfi_def_cfa_offset 16
 233              		.cfi_offset 6, -16
 234 0001 4889E5   		movq	%rsp, %rbp	#,
 235              		.cfi_def_cfa_register 6
 236 0004 53       		pushq	%rbx	#
 237 0005 4883EC28 		subq	$40, %rsp	#,
 238              		.cfi_offset 3, -24
 239              	.LBB4:
  34:t_virtual2.cpp ****    Base *p1 = new Base();
 240              		.loc 1 34 0
 241 0009 BF080000 		movl	$8, %edi	#,
 241      00
 242 000e E8000000 		call	_Znwm	#
 242      00
 243 0013 4889C3   		movq	%rax, %rbx	# D.21029, p1.0
 244 0016 4889DF   		movq	%rbx, %rdi	# p1.0,
 245 0019 E8000000 		call	_ZN4BaseC1Ev	#
 245      00
 246 001e 48895DE8 		movq	%rbx, -24(%rbp)	# p1.0, p1
  35:t_virtual2.cpp ****    p1->print();
 247              		.loc 1 35 0
 248 0022 488B45E8 		movq	-24(%rbp), %rax	# p1, tmp73
 249 0026 4889C7   		movq	%rax, %rdi	# tmp73,
 250 0029 E8000000 		call	_ZN4Base5printEv	#
 250      00
  36:t_virtual2.cpp ****    p1->vprint();
 251              		.loc 1 36 0
 252 002e 488B45E8 		movq	-24(%rbp), %rax	# p1, tmp74
 253 0032 488B00   		movq	(%rax), %rax	# p1_3->_vptr.Base, D.21030
 254 0035 488B00   		movq	(%rax), %rax	# *_4, D.21031
 255 0038 488B55E8 		movq	-24(%rbp), %rdx	# p1, tmp75
 256 003c 4889D7   		movq	%rdx, %rdi	# tmp75,
 257 003f FFD0     		call	*%rax	# D.21031
  37:t_virtual2.cpp ****    
  38:t_virtual2.cpp ****    Derived *p2 = new Derived();
 258              		.loc 1 38 0
 259 0041 BF080000 		movl	$8, %edi	#,
 259      00
 260 0046 E8000000 		call	_Znwm	#
 260      00
 261 004b 4889C3   		movq	%rax, %rbx	# D.21029, p2.1
 262 004e 4889DF   		movq	%rbx, %rdi	# p2.1,
 263 0051 E8000000 		call	_ZN7DerivedC1Ev	#
 263      00
 264 0056 48895DE0 		movq	%rbx, -32(%rbp)	# p2.1, p2
  39:t_virtual2.cpp ****    p2->print();
 265              		.loc 1 39 0
 266 005a 488B45E0 		movq	-32(%rbp), %rax	# p2, tmp76
 267 005e 4889C7   		movq	%rax, %rdi	# tmp76,
 268 0061 E8000000 		call	_ZN7Derived5printEv	#
 268      00
  40:t_virtual2.cpp ****    p2->vprint();
 269              		.loc 1 40 0
 270 0066 488B45E0 		movq	-32(%rbp), %rax	# p2, tmp77
 271 006a 488B00   		movq	(%rax), %rax	# p2_8->D.20845._vptr.Base, D.21030
 272 006d 488B00   		movq	(%rax), %rax	# *_9, D.21031
 273 0070 488B55E0 		movq	-32(%rbp), %rdx	# p2, tmp78
 274 0074 4889D7   		movq	%rdx, %rdi	# tmp78,
 275 0077 FFD0     		call	*%rax	# D.21031
  41:t_virtual2.cpp ****    
  42:t_virtual2.cpp ****    Base *p3 = new Derived();
 276              		.loc 1 42 0
 277 0079 BF080000 		movl	$8, %edi	#,
 277      00
 278 007e E8000000 		call	_Znwm	#
 278      00
 279 0083 4889C3   		movq	%rax, %rbx	# D.21029, p3.2
 280 0086 4889DF   		movq	%rbx, %rdi	# p3.2,
 281 0089 E8000000 		call	_ZN7DerivedC1Ev	#
 281      00
 282 008e 48895DD8 		movq	%rbx, -40(%rbp)	# p3.2, p3
  43:t_virtual2.cpp ****    p3->print();
 283              		.loc 1 43 0
 284 0092 488B45D8 		movq	-40(%rbp), %rax	# p3, tmp79
 285 0096 4889C7   		movq	%rax, %rdi	# tmp79,
 286 0099 E8000000 		call	_ZN4Base5printEv	#
 286      00
  44:t_virtual2.cpp ****    p3->vprint();
 287              		.loc 1 44 0
 288 009e 488B45D8 		movq	-40(%rbp), %rax	# p3, tmp80
 289 00a2 488B00   		movq	(%rax), %rax	# p3_13->_vptr.Base, D.21030
 290 00a5 488B00   		movq	(%rax), %rax	# *_14, D.21031
 291 00a8 488B55D8 		movq	-40(%rbp), %rdx	# p3, tmp81
 292 00ac 4889D7   		movq	%rdx, %rdi	# tmp81,
 293 00af FFD0     		call	*%rax	# D.21031
  45:t_virtual2.cpp ****    
  46:t_virtual2.cpp ****    return 0;
 294              		.loc 1 46 0
 295 00b1 B8000000 		movl	$0, %eax	#, D.21032
 295      00
 296              	.LBE4:
  47:t_virtual2.cpp **** } 
 297              		.loc 1 47 0
 298 00b6 4883C428 		addq	$40, %rsp	#,
 299 00ba 5B       		popq	%rbx	#
 300 00bb 5D       		popq	%rbp	#
 301              		.cfi_def_cfa 7, 8
 302 00bc C3       		ret
 303              		.cfi_endproc
 304              	.LFE981:
 306              		.weak	_ZTV7Derived
 307              		.section	.rodata._ZTV7Derived,"aG",@progbits,_ZTV7Derived,comdat
 308              		.align 16
 311              	_ZTV7Derived:
 312 0000 00000000 		.quad	0
 312      00000000 
 313 0008 00000000 		.quad	_ZTI7Derived
 313      00000000 
 314 0010 00000000 		.quad	_ZN7Derived6vprintEv
 314      00000000 
 315              		.weak	_ZTV4Base
 316              		.section	.rodata._ZTV4Base,"aG",@progbits,_ZTV4Base,comdat
 317              		.align 16
 320              	_ZTV4Base:
 321 0000 00000000 		.quad	0
 321      00000000 
 322 0008 00000000 		.quad	_ZTI4Base
 322      00000000 
 323 0010 00000000 		.quad	_ZN4Base6vprintEv
 323      00000000 
 324              		.weak	_ZTS7Derived
 325              		.section	.rodata._ZTS7Derived,"aG",@progbits,_ZTS7Derived,comdat
 328              	_ZTS7Derived:
 329 0000 37446572 		.string	"7Derived"
 329      69766564 
 329      00
 330              		.weak	_ZTI7Derived
 331              		.section	.rodata._ZTI7Derived,"aG",@progbits,_ZTI7Derived,comdat
 332              		.align 16
 335              	_ZTI7Derived:
 336              	# <anonymous>:
 337              	# <anonymous>:
 338 0000 00000000 		.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
 338      00000000 
 339              	# <anonymous>:
 340 0008 00000000 		.quad	_ZTS7Derived
 340      00000000 
 341              	# <anonymous>:
 342 0010 00000000 		.quad	_ZTI4Base
 342      00000000 
 343              		.weak	_ZTS4Base
 344              		.section	.rodata._ZTS4Base,"aG",@progbits,_ZTS4Base,comdat
 347              	_ZTS4Base:
 348 0000 34426173 		.string	"4Base"
 348      6500
 349              		.weak	_ZTI4Base
 350              		.section	.rodata._ZTI4Base,"aG",@progbits,_ZTI4Base,comdat
 351              		.align 16
 354              	_ZTI4Base:
 355              	# <anonymous>:
 356              	# <anonymous>:
 357 0000 00000000 		.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
 357      00000000 
 358              	# <anonymous>:
 359 0008 00000000 		.quad	_ZTS4Base
 359      00000000 
 360              		.text
 362              	_Z41__static_initialization_and_destruction_0ii:
 363              	.LFB990:
 364              		.loc 1 47 0
 365              		.cfi_startproc
 366 00bd 55       		pushq	%rbp	#
 367              		.cfi_def_cfa_offset 16
 368              		.cfi_offset 6, -16
 369 00be 4889E5   		movq	%rsp, %rbp	#,
 370              		.cfi_def_cfa_register 6
 371 00c1 4883EC10 		subq	$16, %rsp	#,
 372 00c5 897DFC   		movl	%edi, -4(%rbp)	# __initialize_p, __initialize_p
 373 00c8 8975F8   		movl	%esi, -8(%rbp)	# __priority, __priority
 374              		.loc 1 47 0
 375 00cb 837DFC01 		cmpl	$1, -4(%rbp)	#, __initialize_p
 376 00cf 7527     		jne	.L9	#,
 377              		.loc 1 47 0 is_stmt 0 discriminator 1
 378 00d1 817DF8FF 		cmpl	$65535, -8(%rbp)	#, __priority
 378      FF0000
 379 00d8 751E     		jne	.L9	#,
 380              		.file 2 "/usr/include/c++/4.8.2/iostream"
   1:/usr/include/c++/4.8.2/iostream **** // Standard iostream objects -*- C++ -*-
   2:/usr/include/c++/4.8.2/iostream **** 
   3:/usr/include/c++/4.8.2/iostream **** // Copyright (C) 1997-2013 Free Software Foundation, Inc.
   4:/usr/include/c++/4.8.2/iostream **** //
   5:/usr/include/c++/4.8.2/iostream **** // This file is part of the GNU ISO C++ Library.  This library is free
   6:/usr/include/c++/4.8.2/iostream **** // software; you can redistribute it and/or modify it under the
   7:/usr/include/c++/4.8.2/iostream **** // terms of the GNU General Public License as published by the
   8:/usr/include/c++/4.8.2/iostream **** // Free Software Foundation; either version 3, or (at your option)
   9:/usr/include/c++/4.8.2/iostream **** // any later version.
  10:/usr/include/c++/4.8.2/iostream **** 
  11:/usr/include/c++/4.8.2/iostream **** // This library is distributed in the hope that it will be useful,
  12:/usr/include/c++/4.8.2/iostream **** // but WITHOUT ANY WARRANTY; without even the implied warranty of
  13:/usr/include/c++/4.8.2/iostream **** // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  14:/usr/include/c++/4.8.2/iostream **** // GNU General Public License for more details.
  15:/usr/include/c++/4.8.2/iostream **** 
  16:/usr/include/c++/4.8.2/iostream **** // Under Section 7 of GPL version 3, you are granted additional
  17:/usr/include/c++/4.8.2/iostream **** // permissions described in the GCC Runtime Library Exception, version
  18:/usr/include/c++/4.8.2/iostream **** // 3.1, as published by the Free Software Foundation.
  19:/usr/include/c++/4.8.2/iostream **** 
  20:/usr/include/c++/4.8.2/iostream **** // You should have received a copy of the GNU General Public License and
  21:/usr/include/c++/4.8.2/iostream **** // a copy of the GCC Runtime Library Exception along with this program;
  22:/usr/include/c++/4.8.2/iostream **** // see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
  23:/usr/include/c++/4.8.2/iostream **** // <http://www.gnu.org/licenses/>.
  24:/usr/include/c++/4.8.2/iostream **** 
  25:/usr/include/c++/4.8.2/iostream **** /** @file include/iostream
  26:/usr/include/c++/4.8.2/iostream ****  *  This is a Standard C++ Library header.
  27:/usr/include/c++/4.8.2/iostream ****  */
  28:/usr/include/c++/4.8.2/iostream **** 
  29:/usr/include/c++/4.8.2/iostream **** //
  30:/usr/include/c++/4.8.2/iostream **** // ISO C++ 14882: 27.3  Standard iostream objects
  31:/usr/include/c++/4.8.2/iostream **** //
  32:/usr/include/c++/4.8.2/iostream **** 
  33:/usr/include/c++/4.8.2/iostream **** #ifndef _GLIBCXX_IOSTREAM
  34:/usr/include/c++/4.8.2/iostream **** #define _GLIBCXX_IOSTREAM 1
  35:/usr/include/c++/4.8.2/iostream **** 
  36:/usr/include/c++/4.8.2/iostream **** #pragma GCC system_header
  37:/usr/include/c++/4.8.2/iostream **** 
  38:/usr/include/c++/4.8.2/iostream **** #include <bits/c++config.h>
  39:/usr/include/c++/4.8.2/iostream **** #include <ostream>
  40:/usr/include/c++/4.8.2/iostream **** #include <istream>
  41:/usr/include/c++/4.8.2/iostream **** 
  42:/usr/include/c++/4.8.2/iostream **** namespace std _GLIBCXX_VISIBILITY(default)
  43:/usr/include/c++/4.8.2/iostream **** {
  44:/usr/include/c++/4.8.2/iostream **** _GLIBCXX_BEGIN_NAMESPACE_VERSION
  45:/usr/include/c++/4.8.2/iostream **** 
  46:/usr/include/c++/4.8.2/iostream ****   /**
  47:/usr/include/c++/4.8.2/iostream ****    *  @name Standard Stream Objects
  48:/usr/include/c++/4.8.2/iostream ****    *
  49:/usr/include/c++/4.8.2/iostream ****    *  The &lt;iostream&gt; header declares the eight <em>standard stream
  50:/usr/include/c++/4.8.2/iostream ****    *  objects</em>.  For other declarations, see
  51:/usr/include/c++/4.8.2/iostream ****    *  http://gcc.gnu.org/onlinedocs/libstdc++/manual/io.html
  52:/usr/include/c++/4.8.2/iostream ****    *  and the @link iosfwd I/O forward declarations @endlink
  53:/usr/include/c++/4.8.2/iostream ****    *
  54:/usr/include/c++/4.8.2/iostream ****    *  They are required by default to cooperate with the global C
  55:/usr/include/c++/4.8.2/iostream ****    *  library's @c FILE streams, and to be available during program
  56:/usr/include/c++/4.8.2/iostream ****    *  startup and termination. For more information, see the section of the
  57:/usr/include/c++/4.8.2/iostream ****    *  manual linked to above.
  58:/usr/include/c++/4.8.2/iostream ****   */
  59:/usr/include/c++/4.8.2/iostream ****   //@{
  60:/usr/include/c++/4.8.2/iostream ****   extern istream cin;		/// Linked to standard input
  61:/usr/include/c++/4.8.2/iostream ****   extern ostream cout;		/// Linked to standard output
  62:/usr/include/c++/4.8.2/iostream ****   extern ostream cerr;		/// Linked to standard error (unbuffered)
  63:/usr/include/c++/4.8.2/iostream ****   extern ostream clog;		/// Linked to standard error (buffered)
  64:/usr/include/c++/4.8.2/iostream **** 
  65:/usr/include/c++/4.8.2/iostream **** #ifdef _GLIBCXX_USE_WCHAR_T
  66:/usr/include/c++/4.8.2/iostream ****   extern wistream wcin;		/// Linked to standard input
  67:/usr/include/c++/4.8.2/iostream ****   extern wostream wcout;	/// Linked to standard output
  68:/usr/include/c++/4.8.2/iostream ****   extern wostream wcerr;	/// Linked to standard error (unbuffered)
  69:/usr/include/c++/4.8.2/iostream ****   extern wostream wclog;	/// Linked to standard error (buffered)
  70:/usr/include/c++/4.8.2/iostream **** #endif
  71:/usr/include/c++/4.8.2/iostream ****   //@}
  72:/usr/include/c++/4.8.2/iostream **** 
  73:/usr/include/c++/4.8.2/iostream ****   // For construction of filebuffers for cout, cin, cerr, clog et. al.
  74:/usr/include/c++/4.8.2/iostream ****   static ios_base::Init __ioinit;
 381              		.loc 2 74 0 is_stmt 1
 382 00da BF000000 		movl	$_ZStL8__ioinit, %edi	#,
 382      00
 383 00df E8000000 		call	_ZNSt8ios_base4InitC1Ev	#
 383      00
 384 00e4 BA000000 		movl	$__dso_handle, %edx	#,
 384      00
 385 00e9 BE000000 		movl	$_ZStL8__ioinit, %esi	#,
 385      00
 386 00ee BF000000 		movl	$_ZNSt8ios_base4InitD1Ev, %edi	#,
 386      00
 387 00f3 E8000000 		call	__cxa_atexit	#
 387      00
 388              	.L9:
 389              		.loc 1 47 0
 390 00f8 C9       		leave
 391              		.cfi_def_cfa 7, 8
 392 00f9 C3       		ret
 393              		.cfi_endproc
 394              	.LFE990:
 397              	_GLOBAL__sub_I_main:
 398              	.LFB991:
 399              		.loc 1 47 0
 400              		.cfi_startproc
 401 00fa 55       		pushq	%rbp	#
 402              		.cfi_def_cfa_offset 16
 403              		.cfi_offset 6, -16
 404 00fb 4889E5   		movq	%rsp, %rbp	#,
 405              		.cfi_def_cfa_register 6
 406              		.loc 1 47 0
 407 00fe BEFFFF00 		movl	$65535, %esi	#,
 407      00
 408 0103 BF010000 		movl	$1, %edi	#,
 408      00
 409 0108 E8B0FFFF 		call	_Z41__static_initialization_and_destruction_0ii	#
 409      FF
 410 010d 5D       		popq	%rbp	#
 411              		.cfi_def_cfa 7, 8
 412 010e C3       		ret
 413              		.cfi_endproc
 414              	.LFE991:
 416              		.section	.init_array,"aw"
 417              		.align 8
 418 0000 00000000 		.quad	_GLOBAL__sub_I_main
 418      00000000 
 419              		.text
 420              	.Letext0:
 421              		.file 3 "<built-in>"
 422              		.file 4 "/usr/include/stdio.h"
 423              		.file 5 "/usr/lib/gcc/x86_64-redhat-linux/4.8.5/include/stddef.h"
 424              		.file 6 "/usr/include/wchar.h"
 425              		.file 7 "/usr/include/c++/4.8.2/cwchar"
 426              		.file 8 "/usr/include/c++/4.8.2/bits/char_traits.h"
 427              		.file 9 "/usr/include/c++/4.8.2/x86_64-redhat-linux/bits/c++config.h"
 428              		.file 10 "/usr/include/c++/4.8.2/clocale"
 429              		.file 11 "/usr/include/c++/4.8.2/bits/ios_base.h"
 430              		.file 12 "/usr/include/c++/4.8.2/cwctype"
 431              		.file 13 "/usr/include/c++/4.8.2/iosfwd"
 432              		.file 14 "/usr/include/time.h"
 433              		.file 15 "/usr/include/c++/4.8.2/ext/new_allocator.h"
 434              		.file 16 "/usr/include/c++/4.8.2/ext/numeric_traits.h"
 435              		.file 17 "/usr/include/c++/4.8.2/debug/debug.h"
 436              		.file 18 "/usr/include/locale.h"
 437              		.file 19 "/usr/include/bits/types.h"
 438              		.file 20 "/usr/include/c++/4.8.2/x86_64-redhat-linux/bits/atomic_word.h"
 439              		.file 21 "/usr/include/wctype.h"
