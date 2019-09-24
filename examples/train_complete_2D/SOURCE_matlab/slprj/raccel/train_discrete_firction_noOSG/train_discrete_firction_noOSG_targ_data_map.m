  function targMap = targDataMap(),

  ;%***********************
  ;% Create Parameter Map *
  ;%***********************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 1;
    sectIdxOffset = 0;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc paramMap
    ;%
    paramMap.nSections           = nTotSects;
    paramMap.sectIdxOffset       = sectIdxOffset;
      paramMap.sections(nTotSects) = dumSection; %prealloc
    paramMap.nTotData            = -1;
    
    ;%
    ;% Auto data (rtP)
    ;%
      section.nData     = 13;
      section.data(13)  = dumData; %prealloc
      
	  ;% rtP.FRONTMOTOR_Value
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtP.REARMOTOR_Value
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtP.UnitDelay1_X0
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% rtP.Raincondition_Value
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% rtP.UnitDelay2_X0
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% rtP.Moldel_P1_Size
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% rtP.Moldel_P1
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 7;
	
	  ;% rtP.Moldel_P2_Size
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 52;
	
	  ;% rtP.Moldel_P2
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 54;
	
	  ;% rtP.Moldel_P3_Size
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 99;
	
	  ;% rtP.Moldel_P3
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 101;
	
	  ;% rtP.Moldel_P4_Size
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 162;
	
	  ;% rtP.Moldel_P4
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 164;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(1) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (parameter)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    paramMap.nTotData = nTotData;
    


  ;%**************************
  ;% Create Block Output Map *
  ;%**************************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 1;
    sectIdxOffset = 0;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc sigMap
    ;%
    sigMap.nSections           = nTotSects;
    sigMap.sectIdxOffset       = sectIdxOffset;
      sigMap.sections(nTotSects) = dumSection; %prealloc
    sigMap.nTotData            = -1;
    
    ;%
    ;% Auto data (rtB)
    ;%
      section.nData     = 11;
      section.data(11)  = dumData; %prealloc
      
	  ;% rtB.mapxmkextn
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtB.jzaqh5q4hs
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 4;
	
	  ;% rtB.lm4vg54kgl
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 5;
	
	  ;% rtB.hmgfwvrapw
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 6;
	
	  ;% rtB.bipku3phqn
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 7;
	
	  ;% rtB.ea35mwnxp3
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 8;
	
	  ;% rtB.o5g53wpycn
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 12;
	
	  ;% rtB.ja011sv0ld
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 102;
	
	  ;% rtB.ehfze2n4rn
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 147;
	
	  ;% rtB.bcfr1o3fhj
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 167;
	
	  ;% rtB.heaby2xbgq
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 175;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(1) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (signal)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    sigMap.nTotData = nTotData;
    


  ;%*******************
  ;% Create DWork Map *
  ;%*******************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 2;
    sectIdxOffset = 1;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc dworkMap
    ;%
    dworkMap.nSections           = nTotSects;
    dworkMap.sectIdxOffset       = sectIdxOffset;
      dworkMap.sections(nTotSects) = dumSection; %prealloc
    dworkMap.nTotData            = -1;
    
    ;%
    ;% Auto data (rtDWork)
    ;%
      section.nData     = 3;
      section.data(3)  = dumData; %prealloc
      
	  ;% rtDWork.mkcbw0czlr
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDWork.kmnd1a0hnp
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 4;
	
	  ;% rtDWork.id4xzvptbk
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 8;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(1) = section;
      clear section
      
      section.nData     = 14;
      section.data(14)  = dumData; %prealloc
      
	  ;% rtDWork.nxtduwqe0i.LoggedData
	  section.data(1).logicalSrcIdx = 3;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDWork.kra51p0ula.LoggedData
	  section.data(2).logicalSrcIdx = 4;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtDWork.owyk10ibx3.LoggedData
	  section.data(3).logicalSrcIdx = 5;
	  section.data(3).dtTransOffset = 2;
	
	  ;% rtDWork.jdgmm4jsbu.LoggedData
	  section.data(4).logicalSrcIdx = 6;
	  section.data(4).dtTransOffset = 3;
	
	  ;% rtDWork.br001kkqdk.LoggedData
	  section.data(5).logicalSrcIdx = 7;
	  section.data(5).dtTransOffset = 4;
	
	  ;% rtDWork.o0jsobo25z.LoggedData
	  section.data(6).logicalSrcIdx = 8;
	  section.data(6).dtTransOffset = 5;
	
	  ;% rtDWork.nbtxt2yzu0.LoggedData
	  section.data(7).logicalSrcIdx = 9;
	  section.data(7).dtTransOffset = 6;
	
	  ;% rtDWork.mij1qormyo.LoggedData
	  section.data(8).logicalSrcIdx = 10;
	  section.data(8).dtTransOffset = 7;
	
	  ;% rtDWork.kh45rl25om.LoggedData
	  section.data(9).logicalSrcIdx = 11;
	  section.data(9).dtTransOffset = 8;
	
	  ;% rtDWork.bxhs1wd3ta.LoggedData
	  section.data(10).logicalSrcIdx = 12;
	  section.data(10).dtTransOffset = 9;
	
	  ;% rtDWork.ngaphobxq2.LoggedData
	  section.data(11).logicalSrcIdx = 13;
	  section.data(11).dtTransOffset = 10;
	
	  ;% rtDWork.ibsdmxafop.LoggedData
	  section.data(12).logicalSrcIdx = 14;
	  section.data(12).dtTransOffset = 11;
	
	  ;% rtDWork.dbxa4jk1at.LoggedData
	  section.data(13).logicalSrcIdx = 15;
	  section.data(13).dtTransOffset = 12;
	
	  ;% rtDWork.icowkllmtt.LoggedData
	  section.data(14).logicalSrcIdx = 16;
	  section.data(14).dtTransOffset = 13;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(2) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (dwork)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    dworkMap.nTotData = nTotData;
    


  ;%
  ;% Add individual maps to base struct.
  ;%

  targMap.paramMap  = paramMap;    
  targMap.signalMap = sigMap;
  targMap.dworkMap  = dworkMap;
  
  ;%
  ;% Add checksums to base struct.
  ;%


  targMap.checksum0 = 673410750;
  targMap.checksum1 = 3614289188;
  targMap.checksum2 = 78516600;
  targMap.checksum3 = 3854323133;

