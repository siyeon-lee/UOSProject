//일단 스크린에 그리드 그리기	
//16384~16415가 한 줄
//차라리 세로줄을 쭉 그은 다음에 가로줄을 긋자

///////////////////////////세로 줄 긋는 중
(DRAW)
	@SCREEN
	M=1
	D=A+1
	@24576
	M=D
	
	(VIR)
	@24576
	D=M
	A=D
	M=1
	D=A+1
		

	@24576
	M=A-D
	D=M
	M=A-D

	@VIR	//LOOP
	D;JNE
	@VIRTURE
	D;JLE


	///가로줄 긋기 시작하는 포인트 정해
(VIRTURE)
	@15904
	D=A
	@480
	M=D+A

	//줄 긋기 끝나는 포인트 정해
	@15935
	D=A
	@481
	D=D-1
	M=D+A

	//줄긋기 시작
	(ROWSTART)
	@480
	A=M
	M=-1
	D=A+1
	A=D
	M=-1
	@482
	M=D

	(ROW)
	@482
	D=M+1
	A=D
	M=-1
	
	// 끝라인과의 차이를 저장해야함
	@482
	M=D
	@481
	D=M-D
	
	//16864가 다음 라인 시작
	
	@ROW
	D;JGT
	@NEXTROW
	D;JEQ
	
	(NEXTROW)
	@480
	D=M
	D=D+A
	M=D
	@481
	D=M-1
	D=D+A
	M=D
	@24576
	D=A-D
	@ROWSTART
	D;JGT
	@24576
	D=M
	@POINT
	D;JEQ


//사각형 시작 점을 정해줘야해
//20240인데 거기에서 가감가능하게

///////////////////////////////////////////////////////////////
//MAKE STARTING POINT (16,8)
(POINT)
	@20240
	D=A
	@777
	M=D

///////////////////////////////////////////////////////////////////

/////////////////////////
///MAKE RECTANGLE 
(MAKERECTANGLE)
	@480
	M=A
	@16
	M=A


	@777
	A=M
	M=-1
	D=A
	
	@32
	M=D

	(LOOPFORREC)
	@32
	D=M
	D=A+D
	M=D
	A=D
	M=-1
	
	///RAM16에다 저장하기
	@16
	M=M-1
	D=M
	@LOOPFORREC
	D;JGT
	@KEYBOARD
	D;JLE



//////////////////////////////////////////////////////////////////

(DELETERECTANGLE)
	@480
	M=A
	@16
	M=A


	@777
	A=M
	M=1
	D=A
	
	@32
	M=D

	(LOOPFORDELETE)
	@32
	D=M
	D=A+D
	M=D
	A=D
	M=1
	
	///RAM16에다 저장하기


	@16
	M=M-1
	D=M
	@LOOPFORDELETE
	D;JGT

//가로줄 다시 그리기
	@777
	A=M
	M=-1
	D=A
	@480
	D=A+D
	A=D
	M=-1

	@16
	D=M
	@WAITLINE
	D;JLE



////////////////////////////////////////////////////////
//////////키보드 입력받기


(KEYBOARD)
	//키보드 버튼 값은 #111에 저장해둔다
	(START)
	@KBD
	D=M
	@111
	M=D
	@START
	D;JEQ
	//버튼이 눌리면 상자를 지운다
	(CHECK)
	@DELETERECTANGLE
	D;JNE
	
	//민감도를 위한 WAITLINE
	(WAITLINE)
	@KBD
	D=M
	@WAITLINE
	D;JNE



	//왼쪽일까?
	@130
	D=A
	@111
	D=M-D
	@GOTOLEFT
	D;JEQ

	//위쪽일까?
	@131
	D=A
	@111
	D=M-D
	@GOUP
	D;JEQ

	//오른쪽일까?
	@132
	D=A
	@111
	D=M-D
	@GOTORIGHT
	D;JEQ

	//아래쪽일까?
	@133
	D=A
	@111
	D=M-D
	@GODOWN
	D;JEQ



///////////////////////////////////////////////////////////////////
//GO TO LEFT

(GOTORIGHT)	
	@777
	M=M+1
	@MAKERECTANGLE
	D;JMP


(GOTOLEFT)	
	@777
	M=M-1
	@MAKERECTANGLE
	D;JMP
	

(GOUP)
	@480
	D=A
	@777
	M=M-D
	@MAKERECTANGLE
	D;JMP


	
(GODOWN)
	@480
	D=A
	@777
	M=M+D
	@MAKERECTANGLE
	D;JMP
	