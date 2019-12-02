#include "test.h"
#include "utilities.cpp"

#include "symbolMap.cpp"
#include "codeMap.cpp"
#include "symbolBlockMap.cpp"










int main() {
	vector<symbolBlock> symbolBlockMap;	// Symbol Block Map Vector
	
	std::cout << "Read Symbol Map" << std::endl;
	readSymbolMap( symbolBlockMap );
	
	std::cout << "Shift All Past" << std::endl;
	
	
	/*
	DSPReleaseHalt2__FUl 	JSystem.a dspproc.c
	setup_callback__FUs 	JSystem.a dspproc.c
	DsetupTable__FUlUlUlUlUl 	JSystem.a dspproc.c
	DsetMixerLevel__Ff 	JSystem.a dspproc.c
	DsyncFrame__FUlUlUl 	JSystem.a dspproc.c
	DspHandShake__FPv 	JSystem.a dsptask.c
	DspBoot__FPFPv_v 	JSystem.a dsptask.c
	DSPSendCommands2__FPUlUlPFUs_v 	JSystem.a dsptask.c
	DspInitWork__Fv 	JSystem.a dsptask.c
	DspStartWork__FUlPFUs_v 	JSystem.a dsptask.c
	DspFinishWork__FUs 	JSystem.a dsptask.c
	DSPAddTask 	JSystem.a osdsp.c
	DSPAddPriorTask__FP15STRUCT_DSP_TASK 	JSystem.a osdsp.c
	__DSPHandler 	JSystem.a osdsp_task.c
	DsyncFrame2__FUlUlUl 	JSystem.a osdsp_task.c
	Dsp_Update_Request__Fv 	JSystem.a osdsp_task.c
	Dsp_Running_Check__Fv 	JSystem.a osdsp_task.c
	Dsp_Running_Start__Fv 	JSystem.a osdsp_task.c
	*/
	
	resizeSymbolBlock( symbolBlockMap, "rootCallback__8JASTrackFPv 	JSystem.a JASTrack.cpp", 0xC );
	resizeSymbolBlock( symbolBlockMap, "setCentering__Q32og9newScreen8TitleMsgFQ42og9newScreen8TitleMsg13EnumCentering 	plugProjectOgawaU.a ogTitleMsg.cpp", -0x54 );
	resizeSymbolBlock( symbolBlockMap, "doCreate__Q28Morimura16TChallengeSelectFP10JKRArchive 	plugProjectMorimuraU.a challengeSelect2D.cpp", -0x1C );
	resizeSymbolBlock( symbolBlockMap, "doUpdate__Q28Morimura16TChallengeSelectFv 	plugProjectMorimuraU.a challengeSelect2D.cpp", -0x14 );
	resizeSymbolBlock( symbolBlockMap, "doUpdateStateWait__Q33ebi6Screen7TOptionFv 	plugProjectEbisawaU.a ebiScreenOption.cpp", -0xC );
	resizeSymbolBlock( symbolBlockMap, "doUpdateStateClose__Q33ebi6Screen7TOptionFv 	plugProjectEbisawaU.a ebiScreenOption.cpp", -0xC );
	resizeSymbolBlock( symbolBlockMap, "__ct__7SectionFP10JFWDisplayP7JKRHeapb 	sysGCU.a section.cpp", -0x54 );
	resizeSymbolBlock( symbolBlockMap, "run__7SectionFv 	sysGCU.a section.cpp", -0xA0 );
	makeSymbolBlockUsed( symbolBlockMap, "drawEpilepsy__11BootSectionFR8Graphics sysGCU.a bootSection.cpp" );
	resizeSymbolBlock( symbolBlockMap, "doUpdate__11BootSectionFv 	sysGCU.a bootSection.cpp", 0x1C0 + 0x188 );
	resizeSymbolBlock( symbolBlockMap, "updateLoadResourceFirst__11BootSectionFv 	sysGCU.a bootSection.cpp", -0x88 );
	
	trimUnusedSymbols( symbolBlockMap );
	trimOverlapSymbols( symbolBlockMap );
	realignSymbolBlockMap( symbolBlockMap );
	
	std::cout << "Write Symbol Map" << std::endl;
	writeSymbolMap( symbolBlockMap );
	
	
	
	
	
	
	
//	std::cout << "Read Symbol Map" << std::endl;
//	readSymbolMap( symbolBlockMap );
	
//	std::cout << "Write Symbol Map" << std::endl;
//	writeSymbolMap( symbolBlockMap );

//	std::cout << "Read Code Map" << std::endl;
//	readCodeMap( symbolBlockMap );
	
//	std::cout << "Write Code Map" << std::endl;
//	writeCodeMap( symbolBlockMap );



//	removeCarriageReturns();
}



