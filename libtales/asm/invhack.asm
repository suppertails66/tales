;==============================================================
; WLA-DX banking setup
;==============================================================
.memorymap
defaultslot 0
slotsize $8000
slot 0 $0000
.endme

.rombankmap
bankstotal 1
banksize $8000
banks 1
.endro

;==============================================================
; SDSC tag and SMS rom header
;==============================================================
.sdsctag 1.10,"nullname","nulldesc","nullauthor"

.bank 0 slot 0
.org $0000

; Integer divides D by E
; Result in D, remainder in A
; Clobbers F, B
;    xor a
;    ld b,8
;-:  sla d
;    rla
;    cp e
;    jr c,+
;    sub e
;    inc d
;+:  djnz -

.define currentAreaID $D2AA

.define currentSeaFoxInventoryPos $D034
.define currentInventoryPos $D035
.define currentItem $D036

.define UnlockedItemsBitfieldByte0 $D030
.define UnlockedItemsBitfieldByte1 $D031
.define UnlockedItemsBitfieldByte2 $D032
.define unlockedSeaFoxItemsBitfield $D033

.define ButtonsTriggered $D14A

.define inventoryLowerLimit $6		; min inventory value
.define inventoryUpperLimit $18		; max inventory value + 1

.define seaFoxInventoryLowerLimit $0	; min inventory value
.define seaFoxInventoryUpperLimit $8	; max inventory value + 1

CodeStart:
jp InventoryCodeStart

ObjectIndexTable:
.incbin "objtable.bin" fsize ObjectIndexTableSize

SeaFoxObjectIndexTable:
.incbin "seafoxtable.bin" fsize SeaFoxObjectIndexTableSize

InventoryCodeStart:
ld A,(currentAreaID)			; check if we're using Sea Fox
cp $06
jr z,NextItemBitSearchSeaFoxLoopStart
cp $07
jr z,NextItemBitSearchSeaFoxLoopStart
cp $0B
jr z,NextItemBitSearchSeaFoxLoopStart	; branch if on a Sea Fox map

jr NextItemBitSearchLoopStart

NextItemBitSearchLoopStart:

; Determine next target item slot

; Check which direction player pressed

ld A,(ButtonsTriggered)
and $0C
jr z,NextItemBitSearchLoopMain	; branch if no buttons triggered

ld A,(ButtonsTriggered)
bit 2,A
jr nz,NextItemBitSearchLoopLeft	; branch if left triggered

; Right triggered: decrement search position
NextItemBitSearchLoopRight:
ld A,(currentInventoryPos)
dec A				; move to next lowest item
cp inventoryLowerLimit
jr nc,NextItemBitSearchLoopRightSetLimit ; branch if in valid range
ld A,inventoryUpperLimit
dec A				; load highest valid index
NextItemBitSearchLoopRightSetLimit:
ld (currentInventoryPos),A	; Save current position
jr NextItemBitSearchLoopMain

; Left triggered: increment search position
NextItemBitSearchLoopLeft:
ld A,(currentInventoryPos)
inc A				; move to next highest item
cp inventoryUpperLimit
jr c,NextItemBitSearchLoopLeftSetLimit	; branch if in valid range
ld A,inventoryLowerLimit	; set to lowest valid index
NextItemBitSearchLoopLeftSetLimit:
ld (currentInventoryPos),A	; Save current position

NextItemBitSearchLoopMain:
ld A,(currentInventoryPos)
ld HL,UnlockedItemsBitfieldByte2	; Determine which byte to look at

; Check if we need byte 0
NextItemBitSearchLoopByte0Check:
cp 10h
jr c,NextItemBitSearchLoopByte1Check	; branch if not in byte 0 (10-18)
ld HL,UnlockedItemsBitfieldByte0	; address = byte 0
sub 10h					; A = actual byte position
jr NextItemBitSearchLoopBitCheck

; Check if we need byte 1
NextItemBitSearchLoopByte1Check:
cp 8h
jr c,NextItemBitSearchLoopBitCheck	; branch if not in byte 1 (8-F)
ld HL,UnlockedItemsBitfieldByte1	; address = byte 1
sub 8h					; A = actual byte position

; Otherwise, use byte 0 (already set)

; Check if selected bit is set

NextItemBitSearchLoopBitCheck:
inc A
ld B,A					; B = 1-8

ld A,(HL)	; get unlocked items bitfield
; Rotate selected bit into carry
NextItemBitSearchLoopRotateLoop:
rrca
djnz NextItemBitSearchLoopRotateLoop

; if carry bit is set, done
jr c,nextItemBitSearchLoopDone

; otherwise, continue
jr NextItemBitSearchLoopStart

nextItemBitSearchLoopDone:
ld HL,$A8FE;ObjectIndexTable		; look up chosen position in object index table
ld A,(currentInventoryPos)
ld E,A
ld D,0
add HL,DE
ld A,(HL)		; get ID of selected object
ld (currentItem),A	; write to current item variable
ret



NextItemBitSearchSeaFoxLoopStart:

; Determine next target item slot

; Check which direction player pressed

ld A,(ButtonsTriggered)
and $0C
jr z,NextItemBitSearchSeaFoxLoopMain	; branch if no buttons triggered

ld A,(ButtonsTriggered)
bit 2,A
jr nz,NextItemBitSearchSeaFoxLoopLeft	; branch if left triggered

; Right triggered: decrement search position
NextItemBitSearchSeaFoxLoopRight:
ld A,(currentSeaFoxInventoryPos)
dec A					; move to next lowest item
cp $FF
jr c,SeaFoxRightLimit	; check for underflow (branch if in valid range)
ld A,seaFoxInventoryUpperLimit
dec A					; load highest valid index
SeaFoxRightLimit:
ld (currentSeaFoxInventoryPos),A
jr NextItemBitSearchSeaFoxLoopMain

; Left triggered: increment search position
NextItemBitSearchSeaFoxLoopLeft:
ld A,(currentSeaFoxInventoryPos)
inc A				; move to next highest item
cp seaFoxInventoryUpperLimit
jr c,SeaFoxLeftLimit	; branch if in valid range
ld A,seaFoxInventoryLowerLimit	; set to lowest valid index
SeaFoxLeftLimit:
ld (currentSeaFoxInventoryPos),A

NextItemBitSearchSeaFoxLoopMain:

ld A,(currentSeaFoxInventoryPos)
ld HL,unlockedSeaFoxItemsBitfield

NextItemBitSearchSeaFoxLoopBitCheck:
inc A
ld B,A					; B = 1-8

ld A,(HL)	; get unlocked items bitfield
; Rotate selected bit into carry
NextItemBitSearchSeaFoxLoopRotateLoop:
rrca
djnz NextItemBitSearchSeaFoxLoopRotateLoop



; if carry bit is set, done
jr c,nextItemBitSearchSeaFoxLoopDone

; otherwise, continue
jr NextItemBitSearchSeaFoxLoopStart

nextItemBitSearchSeaFoxLoopDone:
ld HL,$A916;SeaFoxObjectIndexTable		; look up chosen position in object index table
ld A,(currentSeaFoxInventoryPos)
ld E,A
ld D,0
add HL,DE
ld A,(HL)		; get ID of selected object
ld (currentItem),A	; write to current item variable
ret