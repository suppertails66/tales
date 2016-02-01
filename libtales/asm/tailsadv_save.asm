.memorymap
  defaultslot 0
  slotsize $4000
  slot 0 $0000
  slot 1 $4000
  slot 2 $8000
.endme

.rombankmap
  bankstotal 32
  banksize $4000
  banks 32
.endro

.define slot0Offset $0000
.define slot1Offset $4000
.define slot2Offset $8000

; patch to clean TA ROM
.background "tailsadv.gg"

;==========================================================
; Save RAM constants
;==========================================================
.define saveDstAddress $0000 + slot2Offset
.define saveSrcAddress $D024
.define saveSrcLength $20
.define sramPageReg $FFFC
.define sramPageRegOldValue $00
.define sramPageRegNewValue $08	; map into slot 2
.define fileDoesExistToken $FF
.define fileDoesNotExistToken $00
.define fileExistsDstAddress saveDstAddress+saveSrcLength
.define initStringDstAddress fileExistsDstAddress+1
.define eventFlagsByte1 $D02E
.define eventFlagsByte1SeaFoxBit 2
.define seaFoxDockStatus $D042
.define seaFoxDockStatusInDock $02

;==========================================================
; Constants for replacement load function
;==========================================================
.define loadGameStart $1660
.define loadGameEnd loadGameStart + $40
.define currentAreaNum $D2AA
.define worldMapAreaNum $10
.define gameMainLoop $0FE5
.define wantPasswordFlag $D2D0
.define wantPasswordFlagClear $00

; bytes for replacement load function
.unbackground loadGameStart loadGameEnd

;==========================================================
; Constants for replacement save function
;==========================================================
; Location of the actual game save code (has to go in bank 0 or 1 due
; to slot 2 being used to map the SRAM).
; Note that this overwrites the old password generation code.
.define saveGameStart loadGameEnd + 1
.define saveGameEnd saveGameStart + $40
.unbackground saveGameStart saveGameEnd

;==========================================================
; Constants for replacement password function
;==========================================================
; Location of the replacement for the code when "CONT." is selected
; in Tails' House
.define passwordReplaceStart $2C2D3
.define passwordReplaceEnd $2C378
.define passwordReplaceStartBanked $02D3 + slot2Offset

.define delayFrames $052F + slot2Offset
.define openShutter $0537 + slot2Offset
.define startTailsHouseMainMenu $0023 + slot2Offset
.define startTailsHouseDockMenu $0064 + slot2Offset
.define tailsHouseSubscreenIndex $D110
.define tailsHouseMainSubscreenIndex $1
.define tailsHouseDockSubscreenIndex $2

; bytes for replacement save function
.unbackground passwordReplaceStart passwordReplaceEnd

;==========================================================
; Constants for jump to load hack
;==========================================================
.define loadHackJumpStart $534
.define loadHackJumpEnd $538

; bytes for jump to save hack
.unbackground loadHackJumpStart loadHackJumpEnd

;==========================================================
; Constants for init hijack
;==========================================================
.define initHijackStart $35
.define initHijackEnd $37
.define hijackedInitStart saveGameEnd + 1
.define hijackedInitEnd hijackedInitStart + $50
.define resumeInit $04BE

; bytes for init hijack
.unbackground initHijackStart initHijackEnd
.unbackground hijackedInitStart hijackedInitEnd

;==========================================================
; Constants for autosave
;==========================================================
.define autoSaveJumpStart $1160
.define autoSaveJumpEnd autoSaveJumpStart + 2
.define autoSaveStart hijackedInitEnd + 1
.define autoSaveEnd autoSaveStart + $10
.define autoSaveReplaceCall $2643

; bytes for init hijack
.unbackground autoSaveJumpStart autoSaveJumpEnd
.unbackground autoSaveStart autoSaveEnd

;==========================================================
; Hijacked init
;==========================================================
.bank 0 slot 0
.orga hijackedInitStart
.section "hijackedInit" force

; String to check SRAM initialization
sramInitStrStart:
  .db "I can't beat Yukari"
sramInitStrEnd:

hijackedInit:
  
  ; Page in SRAM
  ld a,sramPageRegNewValue
  ld (sramPageReg),a
  
  ; Loop over bytes in SRAM where init string should be
  ld b,sramInitStrEnd-sramInitStrStart
  ld de,sramInitStrStart
  ld hl,initStringDstAddress
  -:
    ld a,(de)
    cp (hl)
    jr nz,initStrCharacterMismatch	; branch if character doesn't match
    inc hl
    inc de
    djnz -
  jr allInitStrCharactersMatched	; successful read: don't initialize SRAM
    
  ; If a character doesn't match, initialize SRAM
  initStrCharacterMismatch:
    ; Zero used portion of SRAM
    ld hl,saveDstAddress
    ld de,saveDstAddress+1
    ld bc,saveSrcLength
    xor a
    ld (hl),a
    ldir
    
    ; Write file-doesn't-exist token to SRAM
    ld a,fileDoesNotExistToken
    ld (fileExistsDstAddress),a
    
    ; Write check string to SRAM
    ld hl,sramInitStrStart
    ld de,initStringDstAddress
    ld bc,sramInitStrEnd-sramInitStrStart
    ldir
  
  allInitStrCharactersMatched:
  
  ; Page out SRAM
  ld a,sramPageRegOldValue
  ld (sramPageReg),a
  
  ; Resume normal init code
  jp resumeInit
.ends

;==========================================================
; Init hijack
;==========================================================
.bank 0 slot 0
.orga initHijackStart
.section "initHijack" force
initHijack:
  jp hijackedInit
.ends

;==========================================================
; Replacement load function. Copies game state information to SRAM.
;==========================================================
.bank 0 slot 0
.orga loadGameStart
.section "loadGame" force
loadGame:
  ; Page in SRAM
  ld a,sramPageRegNewValue
  ld (sramPageReg),a
    
  ; Check if a file exists
  ld a,(fileExistsDstAddress)
  cp fileDoesNotExistToken
  jr z,fileLoaded		; the game helpfully loads the default
				; values beforehand, so if no file exists,
				; we can fall back on them
  
  ; Copy the desired block of memory from SRAM
  ld c,0
  ld bc,saveSrcLength
  ld de,saveSrcAddress
  ld hl,saveDstAddress
  ldir
  
  fileLoaded:
  
  ; Page out SRAM
  ld a,sramPageRegOldValue
  ld (sramPageReg),a
  
  ; Make Sea Fox visible in dock if it's unlocked
  ld hl,eventFlagsByte1
  bit eventFlagsByte1SeaFoxBit,(hl)
  jr z,+
  ld a,seaFoxDockStatusInDock
  ld (seaFoxDockStatus),a
  
  +:
  
  ; Clear the want password screen flag
  xor a
  ld (wantPasswordFlag),a
  
  ; Prepare game to load world map instead of Tails' House
  ld a,worldMapAreaNum
  ld (currentAreaNum),a
  
  jp gameMainLoop
.ends

;==========================================================
; Replacement save function. Copies game state information to SRAM.
;==========================================================
.bank 0 slot 0
.orga saveGameStart
.section "saveGame" force
saveGame:
  ; Page in SRAM
  ld a,sramPageRegNewValue
  ld (sramPageReg),a
  
  ; Copy the desired block of memory to SRAM
  ld c,0
  ld bc,saveSrcLength
  ld de,saveDstAddress
  ld hl,saveSrcAddress
  ldir
    
  ; Mark that a file exists
  ld a,fileDoesExistToken
  ld (fileExistsDstAddress),a
  
  ; Page out SRAM
  ld a,sramPageRegOldValue
  ld (sramPageReg),a
  
  ret
.ends

;==========================================================
; Replacement password function. Changes the behavior of selecting
; "CONT." at Tails' House so it instead saves the game.
;==========================================================
.bank 11 slot 2
.orga passwordReplaceStartBanked
.section "tailsHouseSave" force
tailsHouseSave:
  call delayFrames		; keep shutter closed for a while so it sort of
				; looks like an intentional effect
  call openShutter		; open the shutter
  
  ; Save the game
  call saveGame
  
  ; Check the subscreen index so we know which screen to jump back to
  ld a,(tailsHouseSubscreenIndex)
  cp tailsHouseDockSubscreenIndex
  jr nz, +
    jp startTailsHouseDockMenu	; restart from dock
  +:
    jp startTailsHouseMainMenu	; restart from main menu
  
.ends

;==========================================================
; Jump to load hack. Jumps to custom load routine instead of
; password screen when "CONTINUE" is selected on title screen.
;==========================================================
.bank 0 slot 0
.orga loadHackJumpStart
.section "loadHack" force
loadHack:
  jp loadGame
.ends

;==========================================================
; Autosave
;==========================================================
.bank 0 slot 0
.orga autoSaveStart
.section "autoSave" force
autoSave:
  ; Make the call that was replaced with the call to this code
  call autoSaveReplaceCall
  
  ; Save the game
  call saveGame
  
  ret
  
.ends

.bank 0 slot 0
.orga autoSaveJumpStart
.section "autoSaveJump" force
autoSaveJump:
  ; Call the autosave routine
  call autoSave
.ends
